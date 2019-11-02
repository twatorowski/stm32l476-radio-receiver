/**
 * @file usart2.c
 * 
 * @date 2019-11-02
 * @author twatorowski
 * 
 * @brief Test for USART2. Does the echo using callbacks.
 */

#include <stdint.h>

#include "assert.h"
#include "err.h"
#include "dev/usart2.h"

/* test buffer */
static uint8_t buf[32];
/* transfer size */
static size_t t_size;

/* transmission done callback */
static int TestUSART2_TxDoneCallback(void *ptr);
/* transmitter semaphore lock acquired */
static int TestUSART2_TxLockCallback(void *ptr);
/* something got received callback */
static int TestUSART2_RxDoneCallback(void *ptr);
/* reception lock acquired */
static int TestUSART2_RxLockCallback(void *ptr);

/* transmission done callback */
static int TestUSART2_TxDoneCallback(void *ptr)
{
    /* release the transmitter */
    Sem_Release(&usart2tx_sem);
    /* restart the process by acquiring the receiver semaphore */
    Sem_Lock(&usart2rx_sem, TestUSART2_RxLockCallback);
    /* report callback status */
    return EOK;
}

/* transmitter semaphore lock acquired */
static int TestUSART2_TxLockCallback(void *ptr)
{
    /* start the transmission */
    USART2_Send(buf, t_size, TestUSART2_TxDoneCallback);
    /* report callback status */
    return EOK;
}

/* something got received callback */
static int TestUSART2_RxDoneCallback(void *ptr)
{   
    /* cast callback pointer */
    usart2_cbarg_t *arg = ptr;

    /* store the size of received data */
    t_size = arg->size;
    /* nothing was received? */
    if (t_size == 0) {
        /* restart the recepion */
        USART2_Recv(buf, sizeof(buf), TestUSART2_RxDoneCallback);
    /* got something? */
    } else {
        /* release the   receiver */
        Sem_Release(&usart2rx_sem);
        /* lock the transmitter */
        Sem_Lock(&usart2tx_sem, TestUSART2_TxLockCallback);
    }

    /* report callback status */
    return EOK;
}

/* reception lock acquired */
static int TestUSART2_RxLockCallback(void *ptr)
{
    /* start the reception */
    USART2_Recv(buf, sizeof(buf), TestUSART2_RxDoneCallback);
    /* report callback status */
    return EOK;
}

/* initialize test */
int TestUSART2_Init(void)
{   
    /* start the process by acquiring the receiver semaphore */
    Sem_Lock(&usart2rx_sem, TestUSART2_RxLockCallback);
    /* return status */
    return EOK;
}

/* poll test */
void TestUSART2_Poll(void)
{

}
