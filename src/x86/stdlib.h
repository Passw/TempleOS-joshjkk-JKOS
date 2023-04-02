#ifndef STDLIB_H
#define STDLIB_H

#include "stdint.h"

#define INT_HNDLR_CNT 256

typedef struct InterruptFrame {
    int ip;
    int cs;
    int flags;
    int sp;
    int ss;
} int_frame;

typedef void (*int_handler_t)(int_frame *);


void init_heap();

void *malloc(size_t size);

void free(void *ptr);

void *realloc(void *ptr, size_t size);

void *memcpy(void *dest, const void *src, size_t size);

void *memset(void *ptr, int value, size_t size);

char *itoa(int val, int base);

void sleep(unsigned int milli);


unsigned char inb(unsigned short port);

void outb(unsigned short port, unsigned char data);

void reg_int_handler(int_handler_t *int_handlers, unsigned int n, int_handler_t handler);

#endif // STDLIB_H