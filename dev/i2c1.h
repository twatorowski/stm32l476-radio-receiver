/**
 * @file i2c1.h
 * 
 * @date 2019-10-25
 * @author twatorowski
 * 
 * @brief I2C1 driver module
 */

#ifndef DEV_I2C1_H_
#define DEV_I2C1_H_

#include <stddef.h>
#include <stdint.h>

#include "sys/sem.h"

/** @defgroup DEV_I2C1_OPERATIONS I2C1 Operations */
/** @{ */
/** @name I2C Operations */
/** @{ */
/** @brief write register */
#define I2C1_WRITE							    0
/** @brief read register */
#define I2C1_READ							    1
/** @} */
/** @{ */

/** @brief i2c1 bus semaphore */
extern sem_t i2c1_sem;

/** @brief callback argument */
typedef struct {
	/**< error code (@ref ERR_ERROR_CODES) */
	int error;
    /**< performed transfer size */
    size_t size;
} i2c1_cbarg_t;

/** @brief event isr */
void I2C1_I2C1EvIsr(void);
/** @brief error isr */
void I2C1_I2C1ErIsr(void);

/**
 * @brief Initialize I2C1 driver
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int I2C1_Init(void);

/**
 * @brief Perform transfer over the I2C1 interface
 * 
 * @param oper_type type of operation (read/write)
 * @param addr i2c device address
 * @param sub_addr device's regster address
 * @param ptr pointer to read/store data 
 * @param size  size of transfer
 * @param cb callback or CB_SYNC for blocking operation
 * 
 * @return i2c1_cbarg_t * transfer status (for sync calls or async errors)
 */
i2c1_cbarg_t * I2C1_Transfer(int oper_type, uint8_t addr, uint8_t sub_addr, 
    void *ptr, size_t size, cb_t cb);


#endif /* DEV_I2C1_H_ */
