/**
 * @file queue.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-11
 * 
 * @brief Queue
 */

#include <stdint.h>
#include <stddef.h>

#include "sys/heap.h"
#include "sys/queue.h"
#include "sys/time.h"
#include "sys/yield.h"
#include "util/minmax.h"
#include "util/string.h"

/* create queue that can hold up to 'count' elements of size 'size' */
queue_t * Queue_Create(size_t size, uint32_t count)
{
    /* allocate the memory for the queue */
    queue_t *q = Heap_Malloc(sizeof(queue_t));
    /* unable to allocate */
    if (!q)
        return 0;
    
    /* allocate memory for the queue's buffer */
    void *ptr = Heap_Malloc(size * count);
    /* unable to allocate? */
    if (!ptr) {
        Heap_Free(q); return 0;
    }
    
    /* initialize queue data structure */
    *q = (queue_t) { .ptr = ptr, .size = size, .count =  count, 
        .head = 0, .tail = 0 };

    /* return the pointer to the queue descriptor */
    return q;
}

/* release the heap memory used by the queue */
void Queue_Destroy(queue_t *q)
{
    /* free up the queue's memory */
    Heap_Free(q->ptr);
    Heap_Free(q);
}

/* get number of used queue elements */
size_t Queue_GetUsed(queue_t *q)
{
    /* this is simply equal to the difference in counters */
    return q->head - q->tail;
}

/* return the number of free elements in the queue */
size_t Queue_GetFree(queue_t *q)
{
    /* subtract the number of used elements form the maximal count */
    return q->count - Queue_GetUsed(q);
}

/* drop 'count' number of elements */
size_t Queue_Drop(queue_t *q, size_t count)
{
    /* sanity limits */
    size_t max_to_drop = min(count, Queue_GetUsed(q));
    /* advance the tail pointer */
    q->tail += max_to_drop;
    /* return the number of elements dropped */
    return max_to_drop;
}

/* write as much as you can to the queue without waiting for free space */
size_t Queue_Put(queue_t *q, const void *ptr, size_t count)
{
    /* byte-wise source data pointer */
    const uint8_t *p8 = ptr;

    /* limit the number of elements that we can write */
    size_t to_write = min(count, Queue_GetFree(q));
    /* get the head element index */
    size_t head_idx = q->head % q->count;
    /* check where the wrapping occurs */
    size_t to_wrap = q->count - head_idx;
    /* apply limitation */
    to_wrap = min(to_wrap, to_write);

    /* do the write */
    memcpy(q->ptr + head_idx * q->size, p8, to_wrap * q->size);
    memcpy(q->ptr, p8 + to_wrap * q->size, (to_write - to_wrap) * q->size);
    /* commit the change to the queue */
    q->head += to_write;
    /* return the actual number of the elements written */
    return to_write;
}

/* write elements to the queue */
size_t Queue_PutWait(queue_t *q, const void *ptr, size_t count, dtime_t timeout)
{
    /* number of elements written so far */
    size_t written = 0;
    /* current timestamp */
    time_t ts = time(0);

    /* this loop will write the data chunk by chunk. */
    do {
        /* do thw write to the queue, see how much we've written */
        written += Queue_Put(q, (const uint8_t *)ptr + written, 
            count - written);
        /* need to write some more? */
        if (written != count) {
            /* timeout support */
            if (timeout && dtime(time(0), ts) > timeout) {
                break;
            }
            /* no timeout, play the waiting game */
            Yield();
        }
    /* still need to reiterate? */
    } while (written != count);

    /* return number of written elements */
    return written;
}

/* read the data from the queue but do not advance it's contents */
size_t Queue_Peek(queue_t *q, void *ptr, size_t count)
{
    /* byte-wise destination data pointer */
    uint8_t *p8 = ptr;

    /* limit the number of elements that we can read */
    size_t to_read = min(count, Queue_GetUsed(q));
    /* get the tail element index */
    size_t tail_idx = q->tail % q->count;
    /* check where the wrapping occurs */
    size_t to_wrap = q->count - tail_idx;
    /* apply limitation */
    to_wrap = min(to_wrap, to_read);

    /* do the reading */
    memcpy(p8, q->ptr + tail_idx * q->size, to_wrap * q->size);
    memcpy(p8 + to_wrap * q->size, q->ptr, (to_read - to_wrap) * q->size);
    /* return the actual number of the elements read */
    return to_read;
}

/* read the data from the queue and drop it after the read */
size_t Queue_Get(queue_t *q, void *ptr, size_t count)
{
    /* read the data from the queue */
    size_t read = Queue_Peek(q, ptr, count);
    /* and then drop it */
    Queue_Drop(q, read);
    /* return the number of elements read */
    return read;
}

/* wait for the dta to become available and read it */
size_t Queue_GetWait(queue_t *q, void *ptr, size_t count, dtime_t timeout)
{
    /* number of elements read so far */
    size_t read = 0;
    /* current timestamp */
    time_t ts = time(0);

    /* loop as long an nore data is to be read from the queue */
    do {
        /* do thw write to the queue, see how much we've written */
        read += Queue_Get(q, (uint8_t *)ptr + read, count - read);
        /* need to write some more? */
        if (read != count) {
            /* timeout support */
            if (timeout && dtime(time(0), ts) > timeout) {
                break;
            }
            /* no timeout, play the waiting game */
            Yield();
        }
    } while (read != count);

    /* return the number of elements read */
    return read;
}