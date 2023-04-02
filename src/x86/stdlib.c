#include "stdlib.h"

#define HEAP_SIZ 1024

static char heap[HEAP_SIZ];

typedef struct MemBlock {
    size_t size;
    int free;
} block_t;

static block_t *heap_start = (block_t *) heap;

static void split_block(block_t *block, size_t size) {
    block_t *new_block = (block_t *)((char *)block + sizeof(block_t) + size);
    new_block->size = block->size - sizeof(block_t) - size;
    new_block->free = 1;
    block->size = size;
    block->free = 0;
}

void *malloc(size_t size) {
    block_t *block = heap_start;

    while (block->size != 0) {
        if (block->free && block->size >= size) {
            if (block->size > size + sizeof(block_t))
                split_block(block, size);
            block->free = 0;
            return (void *)(block + 1);
        }
        block = (block_t *)((char *)block + sizeof(block_t) + block->size);
    }
    return NULL;
}

void free(void *ptr) {
    if (ptr == NULL)
        return;

    block_t *block = (block_t *)ptr - 1;
    block->free = 1;

    block_t *prev_block = heap_start;
    while (prev_block->size != 0) {
        block_t *next_block = (block_t *)((char *)prev_block + sizeof(block_t) + prev_block->size);
        if (prev_block->free && next_block->free) {
            prev_block->size += sizeof(block_t) + next_block->size;
            block = prev_block;
        } else
            prev_block = next_block;
    }
}

void *memcpy(void *dest, const void *src, size_t size) {
    const char *s = src;
    char *d = dest;
    for (size_t i = 0; i < size; i++)
        d[i] = s[i];
    return dest;
}

void *memset(void *ptr, int value, size_t size) {
    unsigned char *p = ptr;
    while (size--)
        *p++ = (unsigned char)value;
    return ptr;
}

char* itoa(int val, int base) {
    static char buf[32] = { 0 };
    int i = 30;
    for(; val && i; --i, val /= base)
        buf[i] = "0123456789abcdef"[val % base];
    return &buf[i + 1];
}

void sleep(unsigned int milli) {
    unsigned int i = 0; 
    unsigned int j = 0;
    for (i = 0; i < milli; i++) {
        for (j = 0; j < 100000; j++) {
            // Do nothing
        }
    }
}


unsigned char inb(unsigned short port) {
    unsigned char value;
    __asm__ __volatile__("inb %1, %0" : "=a" (value) : "dN" (port));
    return value;
}

void outb(unsigned short port, unsigned char data) {
    __asm__ __volatile__("outb %0, %1" : : "a" (data), "dN" (port));
}

void reg_int_handler(int_handler_t *int_handlers, unsigned int n, int_handler_t handler) {
    int_handlers[n] = handler;
}