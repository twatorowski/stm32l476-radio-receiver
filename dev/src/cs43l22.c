/**
 * @file cs43l22.c
 * 
 * @date 2019-11-05
 * @author twatorowski
 * 
 * @brief CS43L22 DAC Driver Module
 */

#include "assert.h"
#include "err.h"
#include "dev/i2c1.h"
#include "dev/cs43l22.h"
#include "dev/cs43l22_regs.h"
#include "dev/systime.h"
#include "stm32l476/rcc.h"
#include "stm32l476/gpio.h"
#include "sys/atomic.h"
#include "sys/critical.h"
#include "util/elems.h"
#include "util/string.h"
#include "util/strerr.h"

#define DEBUG
#include "debug.h"

/* dac semaphore */
sem_t cs43l22_sem;

/* initialization status */
static int init = ENOINIT;

/* operation type */
static enum operations {
    INIT, PLAY, VOLUME, READ_ID
} operation;

/* stringified operation names */
static const char * operations_str[] = {
    [INIT] = "init", [PLAY] = "play", [VOLUME] = "volume",
    [READ_ID] = "read_id",
};

/* configuration callback */
static cb_t callback;
/* callback argument emitted at the end of the configuration procedure */
static cs43l22_cbarg_t callback_arg;

/* configuration buffer */
static struct cfg_entry {
    /* operation type, read/write */
    uint8_t oper_type;
    /* register address, register value */
    uint8_t addr, value;
} cfg_buf[32], *cfg_ptr, *cfg_end_ptr;

/* configuration entry applied callback */
static int CS43L22_OperationCallback(void *ptr)
{
	/* callback argument */
	i2c1_cbarg_t *a = ptr;

	/* operation ends when there are no more entries to write or an error has 
     * occured in the process */
	if (cfg_ptr == cfg_end_ptr || (a && a->error != EOK)) {
		/* propagate the error condition */
        callback_arg.error = a->error;
        /* read_id operation completed? */
        if (operation == READ_ID)
            callback_arg.id = cfg_buf[0].value;

        /* release the underlying driver i2c */
		Sem_Release(&i2c1_sem);
        /* show message */
		dprintf("cs43l22 operation completed, oper = %d (%s), rc = %d\n", 
            operation, operations_str[operation], a->error);
        /* sync call */
		if (callback == CB_SYNC) {
			callback = CB_NONE;
		/* async call was made? */
		} else if (callback != CB_NONE) {
			callback(&callback_arg);
		}
	/* everything is ok */
	} else if (cfg_ptr != cfg_end_ptr) {
		/* next configuration row */
		struct cfg_entry *c = cfg_ptr++;
        /* perform i2c operation */
		I2C1_Transfer(c->oper_type, CS43L22_ADDR, c->addr, &c->value, 1,
            CS43L22_OperationCallback);
	}

    /* report status */
    return EOK;
}

/* process configuration */
static void CS43L22_OperationPrepare(enum operations oper, cb_t cb, 
    const struct cfg_entry *cfg, int num)
{
    /* how about some sanity checks */
    assert(num < elems(cfg_buf), "cs43l22: number of operatiaons exceeded!");
    /* copy data */
    memcpy(cfg_buf, cfg, num * sizeof(struct cfg_entry));
    /* prepare pointers */
    cfg_ptr = cfg_buf; cfg_end_ptr = cfg_ptr + num;
    /* store the callback */
    callback = cb; operation = oper;
}

/* perform the reset sequence */
static void CS43L22_Reset(void)
{
	/* delay, assert reset */
	SysTime_Delay(5); GPIOE->BSRR = GPIO_BSRR_BR_3;
	/* delay, de-assert reset */
	SysTime_Delay(5); GPIOE->BSRR = GPIO_BSRR_BS_3;
}

/* initialize dac ic */
int CS43L22_Init(void)
{
    /* enter critical section */
	Critical_Enter();

    /* enable gpio */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;

	/* reset moder */
	GPIOE->MODER &= ~GPIO_MODER_MODER3;
	/* set state */
	GPIOE->BSRR = GPIO_BSRR_BR_3;
	/* enable pin */
	GPIOE->MODER |= GPIO_MODER_MODER3_0;

    /* exit critical section */
	Critical_Exit();

    /* assume the initialization stauts is ok so that the init procedures 
     * don't fail */
    init = EOK;
    /* start with the chip reset */
    CS43L22_Reset();
    /* read the identification register */
    cs43l22_cbarg_t *res = CS43L22_ReadID(CB_SYNC);
    /* chip did not respond or who am i does not match! */
    if (res->error != EOK || (res->id & 0xf8) != CS43L22_REG_ID_VALUE)
        init = ECS43L22_NOT_PRESENT;

    /* release the ic semaphore */
    Sem_Release(&cs43l22_sem);
    /* show status */
	dprintf("cs43l22 initstat = %d, %s\n", init, strerr(init));
	/* report status */
	return init;
    /* report the initialization status */
    return init;
}

/* read the identification register */
cs43l22_cbarg_t * CS43L22_ReadID(cb_t cb)
{
    /* sync operation? */
	int sync = cb == CB_SYNC;
    /* configuration vector */
    const struct cfg_entry cfg[] = {
        /* read the id register contents */
        { I2C1_READ, CS43L22_REG_ID, 0x00 },
    };

	/* handle module not initialized situations */
    callback_arg.error = init;
    /* got the initial error? */
    if (callback_arg.error) {
        /* async call errors get handled here */
        if (!sync) cb(&callback_arg);
    /* no initial call errors */
    } else {
        /* store the configuration vector */
        CS43L22_OperationPrepare(READ_ID, cb, cfg, elems(cfg));
        /* acquire the lock to the i2c bus so that the configuration can be sent 
         * to the dac */
        Sem_Lock(&i2c1_sem, CS43L22_OperationCallback);
        /* sync call waitstate */
        while (sync && callback == CB_SYNC);
    }

	/* report status */
	return sync ? &callback_arg : 0;
}

/* initialize the dac */
cs43l22_cbarg_t * CS43L22_Initialize(cb_t cb)
{
    /* sync operation? */
	int sync = cb == CB_SYNC;
    /* configuration vector */
    const struct cfg_entry cfg[] = {
        /* keep in power down state */
        { I2C1_WRITE, CS43L22_REG_POWER_CTL_1, 0x01 },
        /* select headphones port */
        { I2C1_WRITE, CS43L22_REG_POWER_CTL_2, 0xAF },
        /* set clocking information */
        { I2C1_WRITE, CS43L22_REG_CLOCKING_CTL, 0x20 },
        /* Set the Slave Mode and the audio Standard */
        { I2C1_WRITE, CS43L22_REG_IFACE_CTL_1, 0x00 },
        /* write master volume registers */
        { I2C1_WRITE, CS43L22_REG_MASTER_A_VOL, 0x18 },
        { I2C1_WRITE, CS43L22_REG_MASTER_B_VOL, 0x18 },
        /* Disable the analog soft ramp */
        { I2C1_WRITE, CS43L22_REG_ANA_ZC_SR, 0x00 },

        /* initialization as perscribed by the datasheet */
        { I2C1_WRITE, 0x00, 0x99 },
        { I2C1_WRITE, 0x47, 0x80 },
        { I2C1_WRITE, 0x32, 0x80 },
        { I2C1_WRITE, 0x32, 0x00 },
        { I2C1_WRITE, 0x00, 0x00 },
    };

	/* handle module not initialized situations */
    callback_arg.error = init;
    /* got the initial error? */
    if (callback_arg.error) {
        /* async call errors get handled here */
        if (!sync) cb(&callback_arg);
    /* no initial call errors */
    } else {
        /* store the configuration vector */
        CS43L22_OperationPrepare(INIT, cb, cfg, elems(cfg));
        /* start with the chip reset */
        CS43L22_Reset();
        /* acquire the lock to the i2c bus so that the configuration can be sent 
         * to the dac */
        Sem_Lock(&i2c1_sem, CS43L22_OperationCallback);
        /* sync call waitstate */
        while (sync && callback == CB_SYNC);
    }

	/* report status */
	return sync ? &callback_arg : 0;
}

/* start the playback */
cs43l22_cbarg_t * CS43L22_Play(cb_t cb)
{
    /* sync operation? */
	int sync = cb == CB_SYNC;
    /* configuration vector */
    const struct cfg_entry cfg[] = {
        /* power on the codec */
        { I2C1_WRITE, CS43L22_REG_POWER_CTL_1, 0x9E },
    };

	/* handle module not initialized situations */
    callback_arg.error = init;
    /* got the initial error? */
    if (callback_arg.error) {
        /* async call errors get handled here */
        if (!sync) cb(&callback_arg);
    /* no initial call errors */
    } else {
        /* store the configuration vector */
        CS43L22_OperationPrepare(PLAY, cb, cfg, elems(cfg));
        /* acquire the lock to the i2c bus so that the configuration can be sent 
         * to the dac */
        Sem_Lock(&i2c1_sem, CS43L22_OperationCallback);
        /* sync call waitstate */
        while (sync && callback == CB_SYNC);
    }

	/* report status */
	return sync ? &callback_arg : 0;
}

/* set the volume level */
cs43l22_cbarg_t * CS43L22_Volume(int db, cb_t cb)
{
    /* sync operation? */
	int sync = cb == CB_SYNC;

    /* check the parameter */
    if (db > 12 || db < -102) {
        callback_arg.error = ECS43L22_UNSUPPORTED_VOLUME;
    /* handle initialization errors */
    } else {
        callback_arg.error = init;
    }
    
    /* configuration vector */
    const struct cfg_entry cfg[] = {
        /* power on the codec */
        { I2C1_WRITE, CS43L22_REG_MASTER_A_VOL, db / 2 },
        { I2C1_WRITE, CS43L22_REG_MASTER_B_VOL, db / 2 },
    };

    /* got the initial error? */
    if (callback_arg.error) {
        /* async call errors get handled here */
        if (!sync) cb(&callback_arg);
    /* no initial call errors */
    } else {
        /* store the configuration vector */
        CS43L22_OperationPrepare(VOLUME, cb, cfg, elems(cfg));
        /* acquire the lock to the i2c bus so that the configuration can be sent 
         * to the dac */
        Sem_Lock(&i2c1_sem, CS43L22_OperationCallback);
        /* sync call waitstate */
        while (sync && callback == CB_SYNC);
    }

	/* report status */
	return sync ? &callback_arg : 0;
}