#include "patcher.h"
#include "syscalls.h"

#include <string.h>
#include <coreinit/debug.h>
#include <coreinit/cache.h>
#include <coreinit/memorymap.h>
#include <coreinit/dynload.h>

#include "util.h"

static enum patcher_platform platform;
static const char* RPL_NAME = "Minecraft.Client.rpx";
static uint32_t text_segment = 0x02000000;
static uint32_t data_segment = 0x10000000;

// Convert a "Cemu address" to the real one (does nothing on Cemu)
void* patcher_resolve_address(const uint32_t addr) {
    if (addr >= 0x10000000) {
        return (void*)(addr - 0x10000000 + data_segment);
    } else {
        return (void*)(addr - 0x02000000 + text_segment);
    }
}

// Patches data in the game binary (text or data). Use patcher_resolve_address first
static void patcher_write(void* destination, const void* source, const size_t length) {
    if (platform == Aroma) {
        DCStoreRange((void*)source, length);

        const auto src = OSEffectiveToPhysical((uint32_t)source);
        const auto dest = OSEffectiveToPhysical((uint32_t)destination);

        SC_KernelCopyData(dest, src, length);

        DCFlushRangeNoSync(destination, length);
        ICInvalidateRange(destination, length);
    } else if (platform == Cemu) {
        // yes, really!
        memcpy(destination, source, length);
    }
}

// Patch an int or PPC instruction in the game. Pass Cemu addresses in.
bool patcher_write_u32(const uint32_t destination, const uint32_t original, const uint32_t replacement) {
    void* destination_real = patcher_resolve_address(destination);

    auto current = *(uint32_t*)destination_real;
    if (current != original) {
        OSReport("Invalid patch for %08x: expected %08x, found %08x\n", destination, original, current);
        return false;
    }

    patcher_write(destination_real, &replacement, sizeof(replacement));

    current = *(uint32_t*)destination_real;
    if (current != replacement) {
        OSReport("Patch attempt failed for %08x: expected %08x, found %08x\n", destination, replacement,
                 current);
        return false;
    }

    return true;
}

void patcher_init(const enum patcher_platform platform_in) {
    platform = platform_in;

    // we're done
    if (platform == Cemu) return;

    const int rpl_count = OSDynLoad_GetNumberOfRPLs();
    if (!rpl_count) {
        OSReport("Couldn't get RPL info!\n");
        return;
    }

    OSDynLoad_NotifyData rpl_info[rpl_count];
    if (!OSDynLoad_GetRPLInfo(0, rpl_count, rpl_info)) {
        OSReport("Couldn't get RPL info!\n");
        return;
    }
    for (int i = 0; i < rpl_count; i++) {
        if (!str_ends_with(rpl_info[i].name, RPL_NAME)) continue;

        data_segment = rpl_info[i].dataAddr;
        text_segment = rpl_info[i].textAddr;
        OSReport("Found %s (data %08x/text %08x)\n", rpl_info[i].name, data_segment, text_segment);
        break;
    }
}
