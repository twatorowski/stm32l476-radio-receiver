/**
 * @file alloc.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-02
 * 
 * @brief Dynamic memory allocation
 */

#include <stdint.h>
#include <stddef.h>

#include "err.h"
#include "compiler.h"
#include "config.h"

/* allocated block of memory */
typedef struct block {
    /* is the block used? */
    int used;
    /* size of this block */
    size_t size;
    /* pointers to next or previous node */
    struct block *prev, *next;
    /* memory */
    uint8_t mem[];
} block_t;

/* heap memory */
static uint8_t ALIGNED(4) heap[SYS_HEAP_SIZE];

/* initialize dynamic memory allocation */
err_t Heap_Init(void)
{
    /* initiate a single block within the heap space */
    block_t *b = (void *)heap;
    
    /* setup block to */
    b->size = sizeof(heap);
    /* there is no next nor previous block wrt to this one */
    b->prev = b->next = 0;
    /* mark as free */
    b->used = 0;

    /* return status */
    return EOK;
}

/* allocate block of memory */
void * Heap_Malloc(size_t size)
{   
    /* pointers used during the search for the best fitting block */
    block_t *b, *best_fit = 0;
    /* align to words, make room for descriptor */
    size = ((size + 3) & ~0x3) + sizeof(block_t);

    /* go through linked list */
    for (b = (block_t *)heap; b; b = b->next) {
        /* skip over used blocks */
        if (b->used)
            continue;
        /* update best fit if there is no best fit or current best fit is much 
         * larger than currently visited block */
        if (!best_fit || (b->size >= size && b->size < best_fit->size))
            /* no better match can be expected */
            if ((best_fit = b)->size == size)
                break;
    }

    /* nothing was found */
    if (!best_fit)
        return 0;

    /* check if it's worth to split the block into two smaller ones */
    if (best_fit->size >= size + 2 * sizeof(block_t)) {
        /* create a pointer to the new block */
        block_t *new_block = (block_t *)((uintptr_t)best_fit + size);
        /* fill in */
        new_block->prev = best_fit;
        new_block->next = best_fit->next;
        new_block->size = best_fit->size - size;
        new_block->used = 0;
        /* re-adjust the best fit block */
        best_fit->next = new_block;
        best_fit->size = size;
    }

    /* mark as used */
    best_fit->used = 1;
    /* return the pointer to the memory area */
    return best_fit->mem;
}

/* free previously allocated block of memory */
void Heap_Free(void *ptr)
{
    /* compute the block address */
    block_t *b = (block_t *)((uintptr_t)ptr - sizeof(block_t));
    /* clear block used flag */
    b->used = 0;
    
    /* join with next segment if it's free */
    if (b->next && b->next->used == 0)
        b->size += b->next->size, b->next  = b->next->next;
    /* join with previous segment if it's free */
    if (b->prev && b->prev->used == 0)
        b->prev->size += b->size, b->prev->next = b->next;
}