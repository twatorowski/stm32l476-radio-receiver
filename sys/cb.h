/**
 * @file cb.h
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief System callback definition
 */

#ifndef SYS_CB_H_
#define SYS_CB_H_

/* callback */
typedef int (*cb_t) (void *);

/** @defgroup SYS_CB Callback special values */
/** @{ */
/** @name special callback values */
/** @{ */
/** @brief No callback (synchronous operation requested) */
#define CB_SYNC								(cb_t)(0)
/** @brief No callback provided (async operation requested) */
#define CB_NONE								(cb_t)(-1)
/** @} */
/** @} */

#endif /* SYS_CB_H_ */
