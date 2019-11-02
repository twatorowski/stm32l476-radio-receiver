/**
 * @file circbuf.c
 * 
 * @date 2019-11-02
 * @author twatorowski
 * 
 * @brief Circular Buffer Implementation. Multiple producer - multiple consumer 
 * model. Thread-safe. No critical sections for architectures that support 
 * exclusive load/store.
 */

#include <stdint.h>

#include "circbuf/circbuf.h"
#include "sys/atomic.h"

/* return the true index from the alloc/reserve indices that are calculated 
 * w.r.t. buffer size. Returns the number of elements before the circular 
 * buffer wraps around which is useful since some writes to buffer elements may 
 * need to be split between two 'linear' writes: one before and one after 
 * wrapping */
uint32_t Circbuf_Index(circbuf_t *c, uint32_t index, uint32_t *wrap)
{   
    /* get the true index */
    uint32_t true_index = index % c->size;
    /* get the number of elements before the circular buffer wraps */
    if (wrap) 
        *wrap = c->size - true_index;
    /* return the true index */
    return true_index;
}

/* allocate the number of elements of the buffer. return the index of the 
 * starting element. the 'alloc' index (returned by the pointer) is to be used 
 * with push function */
uint32_t CircBuf_Alloc(circbuf_t *c, uint32_t num, uint32_t *alloc, 
    enum CIRCBUF_FLAGS flags)
{
    /* try to allocate space for new data to be stored within circular buffer */
    do {
        /* read current allocation pointer */
        *alloc = Atomic_LDR32(&c->head_alloc);
        /* get the number of free elements */
        uint32_t free = c->size - (*alloc - c->tail);
        /* running low on free space? */
        if (free < num)
            num = flags & EXACT ? 0 : free;
    /* store the updated alloc value */
    } while (Atomic_STR32(&c->head_alloc, *alloc + num) != EOK);

    /* memory was allocated, report success! */
    return EOK;
}

/* commit the previously allocated space. after that it is the sole duty of the 
 * consumer to get the data out of the buffer and process it. Function will 
 * return EOK if the data pushed caued the 'head' index to move, meaning that it 
 * was the first data after the head pointer */
int CircBuf_Push(circbuf_t *c, uint32_t alloc)
{
    /* status to be returned */
    int rc = EBUSY;

	/* we are putting the data just after the head pointer? this comparison is
	 * safe since only the first caller that allocated memory is allowed to 
     * update head and first caller has region->start equal to head */
    if (c->head == alloc) {
        /* report 'EOK' if we are the first chunk of data allocated in the 
         * buffer */
        rc = EOK;
        /* tx_head_alloc may still be changed by callers that have higher
		 * priority so moving one value to another may be a subject of a race
		 * condition */
        do {
            Atomic_LDR32(&c->head);
        /* this store will only succeed when there was no interrupts in 
         * between the load and store instructions */
        } while (Atomic_STR32(&c->head, c->head_alloc) != EOK);
    }
    /* report status */
    return rc;
}

/* Reserve the number of data elements for reading/processing. Do not pop them 
 * just yet */
uint32_t CircBuf_Reserve(circbuf_t *c, uint32_t num, uint32_t *reserve, 
    enum CIRCBUF_FLAGS flags)
{
    /* try to get at most the 'num' elements from the buffer */
    do {
        /* read current allocation pointer */
        *reserve = Atomic_LDR32(&c->tail_reserve);
        /* get the number of occupied buffer elements */
        uint32_t used = (c->head_alloc - c->tail);
        /* running low on elements? */
        if (used < num)
            num = flags & EXACT ? 0 : used;
    /* store the updated alloc value */
    } while (Atomic_STR32(&c->tail_reserve, *reserve + num) != EOK);

    /* return the number of elements actually obtained */
    return num;
}

/* pop the number of elements that were previously obtained with get function */
int CircBuf_Pop(circbuf_t *c, uint32_t reserve)
{
    /* status to be returned */
    int rc = EBUSY;

    /* the caller 'got' to the first entries from the queue? if so then it is 
     * his responsibility to advance the tail pointer */
    if (c->tail == reserve) {
        /* report 'EOK' if we are the first chunk of data located just after 
         * the tail pointer */
        rc = EOK;
        /* tail_reserve might be changed by the higher priority routines, this 
         * loop ensures the atomicity of the copying tail_reserve to tail */
        do {
            Atomic_LDR32(&c->tail);
        /* this store will only succeed when there was no interrupts in 
         * between the load and store instructions */
        } while (Atomic_STR32(&c->tail, c->tail_reserve) != EOK);
    }

    /* report status */
    return rc;
}