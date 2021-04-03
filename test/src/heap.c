/**
 * @file heap.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-03
 * 
 * @brief Test for the heap implementation
 */

#include "sys/heap.h"
#include "util/elems.h"

/* allocation sizes */
static size_t alloc_size[] = {
    1, 10, 100, 20, 40, 2, 60
};

/* test heap implementation */
err_t TestHeap_Init(void)
{
    /* allocated pointers */
    void *ptrs[elems(alloc_size)];

    /* allocate memory */
    for (int i = 0; i < elems(alloc_size); i++)
        ptrs[i] = Heap_Malloc(alloc_size[i]);

    /* free up what was previously allocated */
    for (int i = 0; i < elems(alloc_size); i++)
        Heap_Free(ptrs[i]),  ptrs[i] = 0;
    
    /* report status */
    return EOK;
}