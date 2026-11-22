#pragma once
#include <stdint.h>
#include <string.h>

void SC_KernelCopyData(uint32_t destination, uint32_t source, size_t length);
uint32_t OSGetTitleVersion();
