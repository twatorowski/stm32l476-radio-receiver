/**
 * @file circbuf.h
 * 
 * @date 2019-11-02
 * @author twatorowski
 * 
 * @brief Circular Buffer Implementation. Multiple producer - multiple consumer 
 * model. Thread-safe. No critical sections for architectures that support 
 * exclusive load/store.
 */

#ifndef CIRCBUF_CIRCBUF_H_
#define CIRCBUF_CIRCBUF_H_

#include <stdint.h>

/** @brief abstract circular buffer structure */
typedef struct circbuf {
    /**< complete size of the buffer expressed in number of elements */
    uint32_t size;
    /**< head element index */
    uint32_t head;
    /**< allocation pointer */
    uint32_t head_alloc;
    /**< tail pointer */
    uint32_t tail;
    /**< tail reservation pointer */
    uint32_t tail_reserve;
} circbuf_t;

/** @brief flags for controlling alloc and get behavior */
enum CIRCBUF_FLAGS {
    /**< allocate/get exact number of elements */
    EXACT = 1 << 0
};

/**
 * @brief Return the true index from the alloc/reserve indices that are 
 * calculated w.r.t. buffer size. Also returns the number of elements before the 
 * circular buffer wraps around which is useful since some writes to buffer 
 * elements may need to be split between two 'linear' writes: one before and 
 * one after wrapping 
 * 
 * @param c circular buffer struct
 * @param index alloc/reserve to be processed
 * @param wrap pointer to where to store the number of elements before the 
 * buffer wraps OR 0 if not needed.
 * 
 * @return uint32_t true index
 */
uint32_t Circbuf_Index(circbuf_t *c, uint32_t index, uint32_t *wrap);

/**
 * @brief Producer: Allocate space within circular buffer. This is to be called 
 * before the CircBuf_Push() function. Allocates the @p num elements within the 
 * buffer.Use flags to tell whether you need the excact or 'at most' 'num' 
 * number of elements to be allocated.
 * 
 * @param c circular buffer struct
 * @param num number of elements to be allocated
 * @param alloc returned allocation index. this is the index you may start 
 * writing the data to. Needs to be converted to actual index with respect to 
 * the size field using CircBuf_Index() function.
 * @param flags flags that control the behavior of the allocation
 * 
 * @return uint32_t number of elements allocated
 */
uint32_t CircBuf_Alloc(circbuf_t *c, uint32_t num, uint32_t *alloc, 
    enum CIRCBUF_FLAGS flags);

/**
 * @brief Producer: Push the previously allocated items onto the queue. Calling 
 * that on the first allocated data elements with respect to current head index 
 * value will cause the head pointer to be advanced.
 * 
 * @param c circular buffer struct
 * @param alloc allocation index obtained previously by the CircBuf_Alloc 
 * function
 * 
 * @return int EOK if the head pointer was advanced meaning that the new data 
 * elements are now commited to the buffer and can be obtained by the pop/get 
 * function pair from the consumer side.
 */
int CircBuf_Push(circbuf_t *c, uint32_t alloc);

/**
 * @brief Consumer: Reserve the number of data elements for reading/processing. 
 * Do not remove them from the queue just yet. Flags tell whether you need exact 
 * number of elements or 'at most' number of elements.
 * 
 * @param c circular buffer struct
 * @param num number of elements to be reserved
 * @param reserve index of reserved data from which you may start reading 
 * processing. Needs to be converted to actual index with respect to 
 * the size field using CircBuf_Index() function.
 * @param flags flags that control the behavior of the reservation
 * 
 * @return uint32_t number of elements reserved
 */
uint32_t CircBuf_Reserve(circbuf_t *c, uint32_t num, uint32_t *reserve, 
    enum CIRCBUF_FLAGS flags);

/**
 * @brief Consumer: Pops the previously reserved elements. If reserved elements 
 * were placed just after the `tail` index then a call to this function will 
 * cause the `tail` to be advanced
 * 
 * @param c circular buffer struct
 * @param reserve reserve index as previously obtained by the CircBuf_Reserve() 
 * function
 * 
 * @return int EOK if the function caused the `tail` pointer to advance, meaing 
 * that some elements were freed from the buffer, EBUSY otherwise.
 */
int CircBuf_Pop(circbuf_t *c, uint32_t reserve);

#endif /* CIRCBUF_CIRCBUF_H_ */
