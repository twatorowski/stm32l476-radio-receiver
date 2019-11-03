/**
 * @file rxtx_usart2.c
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief Implementation of RX/TX routines for the USART1
 */

#include <stdint.h>
#include <stddef.h>

#include "config.h"
#include "err.h"
#include "dev/usart2.h"
#include "at/cmd.h"
#include "at/rxtx.h"
#include "at/ntfy.h"
#include "sys/atomic.h"
#include "util/elems.h"
#include "util/minmax.h"
#include "util/string.h"
#include "version.h"

/* current buffer offset */
static volatile uint32_t rx_buf_offs, tx_head, tx_head_alloc, tx_tail;
/* buffer */
static uint8_t rx_buf[512 + 32], tx_buf[2048];

/* usart transmission complete callback */
static int ATRxTxUSART2_USART1TxCallback(void *ptr)
{
    /* callback argument */
    usart2_cbarg_t *arg = ptr;
	/* extract size */
	size_t size = arg ? arg->size : 0;

	/* update tail pointer */
	tx_tail += size;
	/* get the number of bytes buffered */
	size_t bytes_buffered = tx_head - tx_tail;

	/* no more data to push? */
	if (!bytes_buffered) {
		/* release the semaphore */
		Sem_Release(&usart2tx_sem);
	/* still got some data buffered */
	} else {
		/* tail pointer as buffer index */
		uint32_t tail = tx_tail % elems(tx_buf);
		/* get the number of bytes before the buffer wraps around */
		size_t bytes_wrap = elems(tx_buf) - tail;
		/* limit to the number of bytes buffered */
		bytes_wrap = min(bytes_wrap, bytes_buffered);
		/* send the data */
		USART2_Send(tx_buf + tail, bytes_wrap, ATRxTxUSART2_USART1TxCallback);
	}
    
    /* report status */
    return EOK;
}

/* reception completed? */
static int ATRxTxUSART2_USART1RxCallback(void *ptr)
{
    /* callback argument */
    usart2_cbarg_t *arg = ptr;
	/* extract data size */
	size_t a = 0, b = 0, size = arg ? arg->size : 0;

	/* complete buffered data size */
	size = size + rx_buf_offs, rx_buf_offs = 0;
	/* parsing loop */
	while (b != size) {
		/* look for ending '\n' */
		for (; b < size && rx_buf[b] != '\n'; b++);

		/* complete sentence found? */
		if (b != size) {
			/* zero terminate */
			rx_buf[b] = '\0';
			/* input data */
			ATCmd_Input(ATRXTX_IFACE_USART2, (char *)rx_buf);
			/* move the pointer */
			a = b = b + 1;
		/* incomplete string found */
		} else {
			/* copy sentence part to the beginning of the buffer */
			memcpy(rx_buf, rx_buf + a, b - a);
			/* store current buffer offset */
			rx_buf_offs = b - a;
		}
	}

	/* fail safe: drop buffer if there is no space for further characters */
	if (rx_buf_offs + 1 >= sizeof(rx_buf) - 1)
		rx_buf_offs = 0;

	/* re-enable reception (we use one byte less for 0 termination) */
	USART2_Recv(rx_buf + rx_buf_offs, sizeof(rx_buf) - rx_buf_offs - 1,
			ATRxTxUSART2_USART1RxCallback);
    
    /* report status */
    return EOK;
}

/* reception transmission module interface */
int ATRxTxUSART2_Init(void)
{
	/* lock the reception semaphore and start reception */
	Sem_Lock(&usart2rx_sem, ATRxTxUSART2_USART1RxCallback);
    Sem_Lock(&usart2tx_sem, ATRxTxUSART2_USART1TxCallback);
	/* report status */
	return EOK;
}

/* interface polling */
void ATRxTxUSART2_Poll(void)
{

}

/* store line in internal buffer and send it */
int ATRxTxUSART2_SendResponse(int is_notify, const char *str, size_t len)
{
    /* allocation index, number of free bytes, number of bytes before 
     * wrapping occurs */
    uint32_t alloc, free, wrap;

	/* try to update allocation index */
	do {
		/* load current value of the allocation index */
		alloc = Atomic_LDR32((uint32_t *)&tx_head_alloc);
        /* current number of free elements in buffer */
        free = elems(tx_buf) - (alloc - tx_tail);
        /* no space (notifications must leave a space for normal responses */
        if ((len > free) || (is_notify && len + AT_RES_MAX_LINE_LEN > free))
            return EFATAL;
	/* try to write back */
	} while (Atomic_STR32((uint32_t *)&tx_head_alloc, alloc + len) != EOK);

	/* bytes till buffer wraps */
	wrap = elems(tx_buf) - alloc % elems(tx_buf);
    /* no wrapping */
    if (len < wrap) {
        /* single meory copy will do */
        memcpy(tx_buf + alloc % elems(tx_buf), str, len);
    /* wrapping occured */
    } else {
        /* store data before and after the wrapping */
        memcpy(tx_buf + alloc % elems(tx_buf), str, wrap);
        memcpy(tx_buf, str + wrap, len - wrap);
    }

    /* allocated memory follows directly the head pointer? */
    if (alloc == tx_head) {
        /* tx_head_alloc may still be changed by callers that have higher
		 * priority */
        Atomic_MOV32(&tx_head, &tx_head_alloc);
        /* restart transmission */
        if (Sem_Lock(&usart2tx_sem, CB_NONE) == EOK)
			 ATRxTxUSART2_USART1TxCallback(0);
    }

	/* report success */
	return EOK;
}
