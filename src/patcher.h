#pragma once

#include <stdint.h>

enum patcher_platform {
    Aroma,
    Cemu,
};

void patcher_init(enum patcher_platform platform);
bool patcher_write_u32(uint32_t destination, uint32_t original, uint32_t replacement);
void* patcher_resolve_address(uint32_t addr);
