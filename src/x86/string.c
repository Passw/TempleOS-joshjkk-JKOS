#include "string.h"
#include "stdint.h"

size_t strlen(char *str) {
    size_t len = 0;
    while (*str) {
        str++;
        len++;
    }
    return len - 1;
}