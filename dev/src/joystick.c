/**
 * @file joystick.c
 * 
 * @date 2019-11-06
 * @author twatorowski 
 * 
 * @brief Joystick driver module that supports the 4-way joystick present on 
 * the stm32l4-discovery board.
 */

#include "err.h"
#include "dev/await.h"
#include "dev/extimux.h"
#include "dev/joystick.h"
#include "stm32l476/rcc.h"
#include "stm32l476/gpio.h"
#include "stm32l476/syscfg.h"
#include "stm32l476/exti.h"
#include "stm32l476/nvic.h"
#include "sys/critical.h"
#include "sys/ev.h"

#define DEBUG
#include "debug.h"

/* joystick event */
ev_t joystick_ev;
/* repeated keypress */
static int last_status, repeat_cnt;

/* called from the interrupt or the await module */
static int Joystick_KeyPressCallback(void *arg)
{
    /* get joystick status */
    int status = Joystick_GetStatus();

    /* something is pressed */
    if (status) {
        /* build up event argument */
	    joystick_evarg_t ea = { .status = status };
        /* notify */
        Ev_Notify(&joystick_ev, &ea);
        /* fresh update */
        if (last_status != status) {
            /* reset the repetition counter */
            repeat_cnt = 0;
            /* monitor joystick state */
            Await_CallMeLater(500, Joystick_KeyPressCallback, 0);
        /* repeated start */
        } else {
            int delay;
            /* update the repeat counter */
            repeat_cnt++;
            /* repetition speed adjustments */
            if (repeat_cnt > 30) {
                delay = 10;
            } else if (repeat_cnt > 10) {
                delay = 30;
            } else {
                delay = 100;
            }
            /* re-schedule monitoring */
            Await_CallMeLater(delay, Joystick_KeyPressCallback, 0);
        }
    /* reset the repeat counter */
    } else {
        repeat_cnt = 0;
    }
    /* update the status */
    last_status = status;
    /* report status */
    return EOK;
}

/* interrupt for exti 0-3 and 5 */
void Joystick_Exti0_3_5Isr(void)
{
	/* clear interrupt */
	EXTI->PR1 = EXTI_PR1_PIF1 | EXTI_PR1_PIF2 | EXTI_PR1_PIF3 | 
        EXTI_PR1_PIF5;

    /* start the processing */
    Await_CallMeLater(0, Joystick_KeyPressCallback, 0);
}

/* initialize buttons support */
int Joystick_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable gpios */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	/* enable syscfg */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* pa5 - down, pa3 - up, pa1 - left, pa2 - right */
	GPIOA->MODER &= ~(GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | 
        GPIO_MODER_MODER3 | GPIO_MODER_MODER5);
	/* enable pull down */
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_1 | GPIO_PUPDR_PUPDR2_1 | 
        GPIO_PUPDR_PUPDR3_1 | GPIO_PUPDR_PUPDR5_1;

	/* route exti0-3 to port a */
	SYSCFG->EXTICR1 = (SYSCFG->EXTICR1 & ~( SYSCFG_EXTICR1_EXTI1 | 
        SYSCFG_EXTICR1_EXTI2 | SYSCFG_EXTICR1_EXTI3)) |
        SYSCFG_EXTICR1_EXTI1_PA | SYSCFG_EXTICR1_EXTI2_PA | 
        SYSCFG_EXTICR1_EXTI3_PA;
	/* route exti5 to port a*/
	SYSCFG->EXTICR2 = (SYSCFG->EXTICR2 & ~SYSCFG_EXTICR2_EXTI5) |
			SYSCFG_EXTICR2_EXTI5_PA;

	/* configure for falling edge detection */
	EXTI->RTSR1 |= EXTI_RTSR1_RT1 | EXTI_RTSR1_RT2 | EXTI_RTSR1_RT3 | 
        EXTI_RTSR1_RT5;
    EXTI->FTSR1 &= ~(EXTI_FTSR1_FT1 | EXTI_FTSR1_FT2 | EXTI_FTSR1_FT3 | 
        EXTI_FTSR1_FT5);
	/* enable interrupts */
	EXTI->IMR1 |= EXTI_IMR1_IM1 | EXTI_IMR1_IM2 | EXTI_IMR1_IM3 | EXTI_IMR1_IM5;

	/* set interrupt priority */
	NVIC_SETINTPRI(STM32_INT_EXTI1, 0xf0);
	NVIC_SETINTPRI(STM32_INT_EXTI2, 0xf0);
	NVIC_SETINTPRI(STM32_INT_EXTI3, 0xf0);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_EXTI1);
	NVIC_ENABLEINT(STM32_INT_EXTI2);
	NVIC_ENABLEINT(STM32_INT_EXTI3);

	/* exit critical section */
	Critical_Exit();
	/* report status */
	return EOK;
}

/* report button status */
int Joystick_GetStatus(void)
{
	/* button bit mask */
	int mask = 0;

	/* joy left */
	if (GPIOA->IDR & GPIO_IDR_IDR_1)
		mask |= JOYSTICK_STATUS_LEFT;

	/* joy right */
	if (GPIOA->IDR & GPIO_IDR_IDR_2)
		mask |= JOYSTICK_STATUS_RIGHT;

	/* joy up */
	if (GPIOA->IDR & GPIO_IDR_IDR_3)
		mask |= JOYSTICK_STATUS_UP;

	/* joy down */
	if (GPIOA->IDR & GPIO_IDR_IDR_5)
		mask |= JOYSTICK_STATUS_DOWN;

	/* report button state */
	return mask;
}
