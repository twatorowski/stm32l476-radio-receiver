/**
 * @file ntfy.h
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief 
 */

#ifndef AT_NTFY_H_
#define AT_NTFY_H_

#include <stdint.h>
#include <stddef.h>

/** @defgroup AT_NTFY_NTFY_MASK Notification mask bit fields definitions */
/** @{ */
/** @name Notification mask bit fields definitions */
/** @{ */
/** @brief debug notifications */
#define AT_NTFY_MASK_DEBUG                              (0x00000001)
#define AT_NTFY_MASK_MAIN_TRACKER                       (0x00000002)
#define AT_NTFY_MASK_GPS_MON                            (0x00000004)
#define AT_NTFY_MASK_NMEA                               (0x00000008)

/** @} */
/** @} */

/**
 * @brief Initialize notification generation module
 *
 * @return initialization status error code (@ref ERR_ERROR_CODES)
 */
int ATNtfy_Init(void);

/**
 * @brief Polling function of the notification generation module. To be called within
 * AT_Poll().
 */
void ATNtfy_Poll(void);

/**
 * @brief This function shall invoke the notification data drainage, which will in
 * turn produce notification strings and try to put them within the output buffer. To
 * be called by the ATRxTx drivers at the end of transmission.
 */
void ATNtfy_DrainData(void);

/**
 * @brief Sets the notification mask, enabling or disabling the notifications on
 * selected interface.
 *
 * @param iface interface ID
 * @param mask notification mask as per @ref AT_NTFY_NTFY_MASK
 *
 * @return status code (@ref ERR_ERROR_CODES)
 */
int ATNtfy_SetNotificaionMask(int iface, uint32_t mask);
/**
 * @brief Gets the value of the currently set notification mask for selected
 * interface.
 *
 * @param iface interface ID (@ref AT_RXTX_IFACE)
 * @param mask pointer to store the mask value to (@ref AT_NTFY_NTFY_MASK)
 *
 * @return status code (@ref ERR_ERROR_CODES)
 */
int ATNtfy_GetNotificationMask(int iface, uint32_t *mask);


/**
 * @brief Get the orr'ed value of the notification mask for all of 
 * the interfaces 
 * 
 * @param mask pointer to where to store the mask value
 * 
 * @return int status code (@ref ERR_ERROR_CODES)
 */
int ATNtfy_GetNotificationORMask(uint32_t *mask);

/**
 * @brief Sends a notification over given interface
 * 
 * @param iface interface is @ref AT_RXTX_IFACE
 * @param str notification string
 * @param len length of the string
 * 
 * @return int status code (@ref ERR_ERROR_CODES)
 */
int ATNtfy_SendNotification(int iface, const char *str, size_t len);

#endif /* AT_NTFY_H_ */
