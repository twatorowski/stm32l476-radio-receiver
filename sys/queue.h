/**
 * @file queue.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-11
 * 
 * @brief Queue
 */

#ifndef _SYS_QUEUE_H
#define _SYS_QUEUE_H

#include <stdint.h>
#include <stddef.h>

#include "sys/time.h"

/** queue block */
typedef struct queue {
    /* size of the single element */
    size_t size;
    /* number of elements that can fit into the buffer */
    int count;
    /** pointer to queue buffer, byte-wise */
    uint8_t *ptr;
    /** head counter */
    size_t head;
    /** tail counter */
    size_t tail;
} queue_t;

/**
 * @brief Allocate memory for the queue and initialize it's contents
 * 
 * @param size size of single element to be placed on the queue
 * @param count number of elements
 * 
 * @return queue_t * queue descriptor pointer or null if no memory is 
 * available 
 */
queue_t * Queue_Create(size_t size, uint32_t count);

/**
 * @brief Frees the memory used by the queue
 * 
 * @param q queue descriptor pointer
 */
void Queue_Destroy(queue_t *q);

/**
 * @brief Returns the number of queue elements that are occupied
 * 
 * @param q queue descriptor pointer
 *
 * @return size_t number of used queue elements
 */
size_t Queue_GetUsed(queue_t *q);

/**
 * @brief Returns the number of free elements in the queue 
 * 
 * @param q queue descriptor pointer
 *
 * @return size_t number of free elements
 */
size_t Queue_GetFree(queue_t *q);

/**
 * @brief drop 'count' number of elements from the queue
 * 
 * @param q queue descriptor pointer
 * 
 * @param count number of elements to drop
 * 
 * @return size_t actual number of elements dropped
 */
size_t Queue_Drop(queue_t *q, size_t count);

/**
 * @brief Writes elements to the queue. As many as can be written at given 
 * moment.
 * 
 * @param q queue descriptor pointer
 * @param ptr pointer to the data to be written
 * @param count number of elements to be written
 *
 * @return size_t 
 */
size_t Queue_Put(queue_t *q, const void *ptr, size_t count);

/**
 * @brief Put new elements to the queue, Wait for all elements to be put or t
 * timeout occurs
 * 
 * @param q queue descriptor pointer
 * @param ptr pointer to the data to be written
 * @param count number of elements to be written
 * @param timeout timeout expressed in system ticks
 * 
 * @return size_t number of elements put before timeout occurred
 */
size_t Queue_PutWait(queue_t *q, const void *ptr, size_t count, dtime_t timeout);

/**
 * @brief read the data from the queue but do not drop it afterwards.
 * 
 * @param q queue descriptor pointer
 * @param ptr pointer to the data to be written
 * @param count maximal number of elements to be read
 * 
 * @return size_t actual number of elements read
 */
size_t Queue_Peek(queue_t *q, void *ptr, size_t count);

/**
 * @brief Read the data from the queue and drop it afterwards.
 * 
 * @param q queue descriptor pointer
 * @param ptr pointer to the data to be written
 * @param count maximal number of elements to be read
 * 
 * @return size_t actual number of elements read
 */
size_t Queue_Get(queue_t *q, void *ptr, size_t count);

/**
 * @brief Try to read count elements from the queue. If there is not enough data
 * within the queue then wait and continue reading when data comes by. Waiting
 * is constrained by timeout value
 * 
 * @param q queue descriptor pointer
 * @param ptr pointer to the data to be written
 * @param count maximal number of elements to be read
 * @param time read timeout in system ticks
 *
 * @return size_t size_t actual number of elements read
 */
size_t Queue_GetWait(queue_t *q, void *ptr, size_t count, dtime_t time);

#endif /* _SYS_QUEUE_H */
