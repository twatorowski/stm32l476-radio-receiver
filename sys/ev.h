/**
 * @file ev.h
 *
 * @date 29.06.2019
 * @author twatorowski
 *
 * @brief System Event
 */

#ifndef SYS_EV_H_
#define SYS_EV_H_

#include "config.h"
#include "sys/cb.h"

/** @brief system event */
typedef struct {
	/**< callbacks */
	cb_t cb[EV_MAX_CB];
} ev_t;

/**
 * @brief Generate an event with argument
 *
 * @param ev an event structure on which the notification will be broadcasted to all
 * subscribers
 * @param arg notification argument
 */
void Ev_Notify(ev_t *ev, void *arg);

/**
 * @brief Register callback and become a subscriber to event notifications
 *
 * @param ev event to which one wants to subscribe
 * @param callback function to be called when event notification arises
 *
 * @return registration status (@ref ERR_ERROR_CODES)
 */
int Ev_RegisterCallback(ev_t *ev, cb_t callback);

/**
 * @brief Unsubscribe from event notifications.
 *
 * @param ev event to unsubscribe from.
 * @param callback to be unsubscribed
 *
 * @return un-registration error code (@ref ERR_ERROR_CODES)
 */
int Ev_UnregisterCallback(ev_t *ev, cb_t callback);

#endif /* SYS_EV_H_ */
