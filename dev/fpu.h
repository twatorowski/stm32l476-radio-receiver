/**
 * @file fpu.h
 *
 * @date 29.06.2019
 * @author twatorowski
 *
 * @brief Floating Point Unit Driver
 */

#ifndef DEV_FPU_H_
#define DEV_FPU_H_

#include "err.h"

/**
 * @brief Initialize FPU. Needs to be called before any floating point instruction
 * takses place
 *
 * @return initialization status (@ref ERR_ERROR_CODES)
 */
err_t FPU_Init(void);

#endif /* DEV_FPU_H_ */
