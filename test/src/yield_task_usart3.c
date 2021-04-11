/**
 * @file yield_task_usart3.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-03-26
 * 
 * @brief Test for the task switching
 *  
 */

#include <stdint.h>

#include "err.h"
#include "dev/usart3.h"
#include "sys/yield.h"

/* 1st task handler */
static void TestYieldTaskUSART3_EchoTask(void *arg)
{
    /* data buffer */
    uint8_t buf[32];

    /* inf loop */
    while (1) {
        /* receive and return the number of bytes that were actually received */
        int bnum = USART3_Recv(buf, sizeof(buf), 1000);
        /* send data over usart */
        if (bnum > 0) {
            USART3_Send("|", 1, 0);
            USART3_Send(buf, bnum, 0);
        /* inform the user that no data was provided */
        } else {
            USART3_Send("no data ;-(\n", 12, 0);
        }
    }
}

/* usart echo with timeout test */
err_t TestYieldTaskUSART3_Init(void)
{
    /* create two tasks */
    Yield_CreateTask(TestYieldTaskUSART3_EchoTask, 0, 512);
    /* return status */
    return EOK;
}