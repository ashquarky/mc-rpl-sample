#include "util.h"

#include <string.h>

// https://stackoverflow.com/a/63921254
bool str_ends_with(const char* str, const char* suffix) {
    const size_t str_len = strlen(str);
    const size_t suffix_len = strlen(suffix);

    return str_len >= suffix_len &&
        !memcmp(str + str_len - suffix_len, suffix, suffix_len);
}
