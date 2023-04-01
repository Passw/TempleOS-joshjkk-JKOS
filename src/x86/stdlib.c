#include "stdlib.h"

#define HEAP_SIZ 1024

typedef struct MemBlock
{
    unsigned int size;
    int free;
    struct MemBlock *next;
    struct MemBlock *prev;
} mem_block_t;

static unsigned int heap[HEAP_SIZ];
static unsigned int *heap_end = (unsigned int *)HEAP_SIZ;
static mem_block_t *free_list = (mem_block_t *)heap;

void *_sbrk(unsigned int increment)  {
    unsigned int *prev_heap_end = heap_end;
    heap_end += increment;
    return (void *)prev_heap_end;
}

void init_heap()  {
    free_list->size = sizeof(heap) - sizeof(mem_block_t);
    free_list->free = 1;
    free_list->next = NULL;
    free_list->prev = NULL;
    memset(heap, 0, HEAP_SIZ);
}

void *malloc(size_t size) {
    mem_block_t *cur_block = free_list;
    mem_block_t *best_fit = NULL;

    while (cur_block != NULL) {
        if (cur_block->free && cur_block->size >= size &&
            (best_fit == NULL || cur_block->size < best_fit->size))
            best_fit = cur_block;
            
        cur_block = cur_block->next;
    }

    if (best_fit == NULL) {
        mem_block_t *new_block = (mem_block_t *)_sbrk(size + sizeof(mem_block_t));
        if (new_block == (mem_block_t *) -1)
            return NULL;

        new_block->size = size;
        new_block->free = 0;
        new_block->next = NULL;
        new_block->prev = NULL;
        return (void *)(new_block + 1);
    } else {
        if (best_fit->size > size + sizeof(mem_block_t)) {
            mem_block_t *new_block = (mem_block_t *) ((unsigned int *)best_fit + sizeof(mem_block_t) + size);
            new_block->size = best_fit->size - size - sizeof(mem_block_t);
            new_block->free = 1;
            new_block->next = best_fit->next;
            new_block->prev = best_fit;

            if (best_fit->next != NULL)
                best_fit->next->prev = new_block;

            best_fit->next = new_block;
        }
        best_fit->free = 0;
        return (void *)(best_fit + 1);
    }
}

// TODO: fix this
void free(void *ptr) {
    mem_block_t *block = (mem_block_t *)ptr - 1;
    block->free = 1;

    if (block->prev != NULL && block->prev->free) {
        block->prev->size += sizeof(mem_block_t) + block->size;
        block->prev->next = block->next;

        if (block->next != NULL)
            block->next->prev = block->prev;
        // update the block pointer to point to the new previous block
        block = block->prev;
    }

    if (block->next != NULL && block->next->free) {
        block->size += sizeof(mem_block_t) + block->next->size;
        block->next = block->next->next;
        if (block->next != NULL)
            block->next->prev = block;
    }
}

void *realloc(void *ptr, size_t size) {
    if (ptr == NULL)
        return malloc(size);

    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    struct MemBlock *block = (struct MemBlock *)ptr - 1;
    unsigned int old_size = block->size;
    void *new_ptr = malloc(size);

    if (new_ptr == NULL)
        return NULL;

    size_t copy_size = size < old_size ? size : old_size;
    memcpy(new_ptr, ptr, copy_size);
    free(ptr);

    return new_ptr;
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