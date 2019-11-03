/**
 * @file at.h
 *
 * @date 29.06.2019
 * @author twatorowski
 *
 * @brief 
 */

#ifndef AT_AT_H_
#define AT_AT_H_

/**
 * @brief Initialize AT commands interface support.
 *
 * @return status code (@ref ERR_ERROR_CODES)
 */
int AT_Init(void);

/**
 * @brief Poll AT commands related routines. To be called in main program loop.
 */
void AT_Poll(void);

#endif /* AT_AT_H_ */
