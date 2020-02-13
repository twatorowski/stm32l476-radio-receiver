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
#include "dev/await.h"
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

/* operation type */
static enum call_type {
    CT_INIT, CT_PLAY, CT_VOLUME, CT_READ_ID
} call_type;

/* stringified operation names */
static const char * call_type_str[] = {
    [CT_INIT] = "init", [CT_PLAY] = "play", [CT_VOLUME] = "volume",
    [CT_READ_ID] = "read_id",
};

/* configuration callback */
static cb_t callback;
/* callback argument emitted at the end of the configuration procedure */
static cs43l22_cbarg_t callback_arg;

/* configuration buffer */
static struct oper_list_entry {
    /* types of operations */
    enum oper_type {
        /* i2c accesses */
        OT_LOCK, OT_READ, OT_WRITE, OT_RELEASE,
        /* wait and reset */
        OT_WAIT, OT_RESET
    } oper_type;
    union {
        /* argument for the i2c operations */
        struct { uint8_t addr, value; } tfer;
        /* reset and wait arguments */
        struct { int value; } reset;
        struct { int ms; } wait;
    };
} oper_list[32], *oper_list_ptr, *oper_list_end;

/* perform the reset sequence */
static void CS43L22_Reset(int state, cb_t cb)
{
    GPIOE->BSRR = state ? GPIO_BSRR_BR_3 : GPIO_BSRR_BS_3;
    /* give some delay */
    Await_CallMeLater(5, cb, 0);
}

/* configuration entry applied callback */
static int CS43L22_OperationCallback(void *ptr)
{
	/* callback argument */
	i2c1_cbarg_t *arg = ptr;
    /* set the error code if not already set. this way the callback will always 
     * present the initial error value */
    if (callback_arg.error == EOK && arg && arg->error != EOK)
        callback_arg.error = arg->error;

	/* operation ends when there are no more entries to write or an error has 
     * occured in the process */
	if (oper_list_ptr == oper_list_end) {
        /* read_id operation completed? */
        if (call_type == CT_READ_ID)
            callback_arg.id = oper_list[0].tfer.value;

        /* show message */
		dprintf("cs43l22 operation completed, oper = %d (%s), rc = %d\n", 
            call_type, call_type_str[call_type], callback_arg.error);
        /* sync call */
		if (callback == CB_SYNC) {
			callback = CB_NONE;
		/* async call was made? */
		} else if (callback != CB_NONE) {
			callback(&callback_arg);
		}
	/* more work needs to be done */
	} else {
		/* next configuration row */
		struct oper_list_entry *o = oper_list_ptr++;
        /* shorthand for the callback */
        cb_t cb = CS43L22_OperationCallback;
        /* switch on operation type */
        switch (o->oper_type) {
        case OT_LOCK : Sem_Lock(&i2c1_sem, cb); break;
        case OT_RELEASE : Sem_Release(&i2c1_sem); cb(0); break;
        /* i2c operations */
        case OT_READ :
        case OT_WRITE : {
            I2C1_Transfer(o->oper_type == OT_READ ? I2C1_READ : I2C1_WRITE, 
                CS43L22_ADDR, o->tfer.addr, &o->tfer.value, 1, cb);
        } break;
        /* power & reset & wait operation */
        case OT_WAIT : Await_CallMeLater(o->wait.ms, cb, 0); break;
        case OT_RESET : CS43L22_Reset(o->reset.value, cb); break;
        }
	}

    /* report status */
    return EOK;
}

/* process configuration */
static void CS43L22_ExecuteOperationList(enum call_type call, 
    const struct oper_list_entry *operations, int num, cb_t cb)
{
    /* how about some sanity checks */
    assert(num < elems(oper_list), 
        "cs43l22: number of operatiaons exceeded!", call);

    /* copy data */
    memcpy(oper_list, operations, num * sizeof(struct oper_list_entry));
    /* store the call type */
    call_type = call;
    /* prepare pointers */
    oper_list_ptr = oper_list; oper_list_end = oper_list_ptr + num;
    /* store the callback address */
    callback = cb;

    /* initiate the process! */
    CS43L22_OperationCallback(0);
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
    /* release the ic semaphore */
    Sem_Release(&cs43l22_sem);
    /* report the initialization status */
    return EOK;
}

/* read the identification register */
cs43l22_cbarg_t * CS43L22_ReadID(cb_t cb)
{
    /* sync operation? */
	int sync = cb == CB_SYNC;
    /* list of operations */
    const struct oper_list_entry opers[] = {
        /* lock the i2c bus */
        { OT_LOCK },
        /* read the id register contents */
        { OT_READ, .tfer = { CS43L22_REG_ID, 0x00 }},
        /* release the i2c bus */
        { OT_RELEASE },
    };

	/* reset the callback error */
    callback_arg.error = EOK;
    /* store the configuration vector */
    CS43L22_ExecuteOperationList(CT_READ_ID, opers, elems(opers), cb);
    /* sync call waitstate */
    while (sync && callback == CB_SYNC);

    /* report status */
    return sync ? &callback_arg : 0;
}

/* initialize the dac */
cs43l22_cbarg_t * CS43L22_Initialize(cb_t cb)
{
    /* sync operation? */
	int sync = cb == CB_SYNC;
    /* list of operations */
    const struct oper_list_entry opers[] = {
        /* do the reset sequence */
        { OT_RESET, .reset.value = 1 },
        { OT_RESET, .reset.value = 0 },
        /* add some waitstate */
        { OT_WAIT, .wait.ms = 10 },

        /* lock the i2c bus */
        { OT_LOCK },
        /* keep in power down state */
        { OT_WRITE, .tfer = { CS43L22_REG_POWER_CTL_1, 0x01 }},
        /* select headphones port */
        { OT_WRITE, .tfer = { CS43L22_REG_POWER_CTL_2, 0xAF }},
        /* set clocking information */
        { OT_WRITE, .tfer = { CS43L22_REG_CLOCKING_CTL, 0x22 }},
        /* Set the Slave Mode and the audio Standard */
        { OT_WRITE, .tfer = { CS43L22_REG_IFACE_CTL_1, 0x00 }},
        /* SCLK = MCLK */
        { OT_WRITE, .tfer = { CS43L22_REG_IFACE_CTL_2, 0x01 }},
        /* write master volume registers */
        { OT_WRITE, .tfer = { CS43L22_REG_MASTER_A_VOL, 0x18 }},
        { OT_WRITE, .tfer = { CS43L22_REG_MASTER_B_VOL, 0x18 }},
        /* Disable the analog soft ramp */
        { OT_WRITE, .tfer = { CS43L22_REG_ANA_ZC_SR, 0x00 }},

        /* initialization as perscribed by the datasheet */
        { OT_WRITE, .tfer = { 0x00, 0x99 }},
        { OT_WRITE, .tfer = { 0x47, 0x80 }},
        { OT_WRITE, .tfer = { 0x32, 0x80 }},
        { OT_WRITE, .tfer = { 0x32, 0x00 }},
        { OT_WRITE, .tfer = { 0x00, 0x00 }},
        /* release the i2c bus */
        { OT_RELEASE },
    };

	/* reset the callback error */
    callback_arg.error = EOK;
    /* store the configuration vector */
    CS43L22_ExecuteOperationList(CT_INIT, opers, elems(opers), cb);
    /* sync call waitstate */
    while (sync && callback == CB_SYNC);

    /* report status */
    return sync ? &callback_arg : 0;
}

/* start the playback */
cs43l22_cbarg_t * CS43L22_Play(cb_t cb)
{
    /* sync operation? */
	int sync = cb == CB_SYNC;
    /* list of operations */
    const struct oper_list_entry opers[] = {
        /* lock the i2c bus */
        { OT_LOCK },
        /* power on the codec */
        { OT_WRITE, .tfer = { CS43L22_REG_POWER_CTL_1, 0x9E }},
        /* release the i2c bus */
        { OT_RELEASE },
    };

	/* reset the callback error */
    callback_arg.error = EOK;
    /* store the configuration vector */
    CS43L22_ExecuteOperationList(CT_PLAY, opers, elems(opers), cb);
    /* sync call waitstate */
    while (sync && callback == CB_SYNC);

    /* report status */
    return sync ? &callback_arg : 0;
}

/* set the volume level */
cs43l22_cbarg_t * CS43L22_SetVolume(int db, cb_t cb)
{
    /* sync operation? */
	int sync = cb == CB_SYNC;
    /* list of operations */
    const struct oper_list_entry opers[] = {
        /* lock the i2c bus */
        { OT_LOCK },
        /* power on the codec */
        { OT_WRITE, .tfer = { CS43L22_REG_MASTER_A_VOL, db / 2 }},
        { OT_WRITE, .tfer = { CS43L22_REG_MASTER_B_VOL, db / 2 }},
        /* release the i2c bus */
        { OT_RELEASE },
    };

    /* check the parameter */
    if (db > 12 || db < -102) {
        callback_arg.error = ECS43L22_UNSUPPORTED_VOLUME;
    /* reset error */
    } else {
        callback_arg.error = EOK;
    }

    /* got an error already? report to the caller */
    if (callback_arg.error != EOK)
        return !sync ? (void *)(cb(&callback_arg), 0) : &callback_arg;

	/* reset the callback error */
    callback_arg.error = EOK;
    /* store the configuration vector */
    CS43L22_ExecuteOperationList(CT_VOLUME, opers, elems(opers), cb);
    /* sync call waitstate */
    while (sync && callback == CB_SYNC);

    /* report status */
    return sync ? &callback_arg : 0;
}