#ifndef STDLIB_H
#define STDLIB_H

#include "stdint.h"

void init_heap();

void *malloc(size_t size);

void free(void *ptr);

void *realloc(void *ptr, size_t size);

void *memcpy(void *dest, const void *src, size_t size);

void *memset(void *ptr, int value, size_t size);

char *itoa(int val, int base);

#endif // STDLIB_H