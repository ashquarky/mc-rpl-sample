#include <coreinit/debug.h>
#include <coreinit/dynload.h>

#include "main.h"
#include "patcher.h"

static void apply_patches() {
    // Cemu: Debug -> Logging -> Coreinit Logging (OSReport)
    // Aroma: use https://github.com/wiiu-env/MochaPayload/blob/main/tcp_log_server.py
    OSReport("hello!\n");

    // TODO: make a real PPC patching engine. :3
    const auto grass_sound_type = (uint32_t)patcher_resolve_address(0x104f0918); // converts Cemu address to "real"
    const auto anvil_sound_type = (uint32_t)patcher_resolve_address(0x104f0938); // Works on Cemu and Aroma
    const uint32_t lis_r24 = 0x3f000000;
    const uint32_t lwzu_r4_r24 = 0x84980000;
    // make grass blocks sound like anvils
    patcher_write_u32( // works for code and data
        0x020cabd4, // pass Cemu addresses, conversion is handled in patcher.c
        lis_r24 | grass_sound_type >> 16, // original instruction (sanity check, does nothing if non-matching)
        lis_r24 | anvil_sound_type >> 16 // new instruction
    );
    patcher_write_u32(
        0x020cabdc,
        lwzu_r4_r24 | (uint16_t)grass_sound_type,
        lwzu_r4_r24 | (uint16_t)anvil_sound_type
    );
}

void app_main(const enum patcher_platform platform) {
    patcher_init(platform);
    apply_patches();
}
