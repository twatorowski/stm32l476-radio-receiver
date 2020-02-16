/**
 * @file usb_audiosrc.h
 * 
 * @date 2020-02-11
 * @author twatorowski 
 * 
 * @brief USB Audio Source
 */

#ifndef USB_AUDIOSRC_H
#define USB_AUDIOSRC_H

#include <stddef.h>

#include "sys/ev.h"

/** @name USB audio event types */
/** @{ */
/** @brief transmission is done*/
#define USB_AUDIO_SRC_EVARG_TYPE_TXDONE                    0
/** @brief isochronous transfer is incomplete */
#define USB_AUDIO_SRC_EVARG_TYPE_ISOINC                    1
/** @} */

/** @name USB audio working modes */
/** @{ */
/** @brief no audio streaming */
#define USB_AUDIO_SRC_EVARG_MODE_OFF                    0
/** @brief streaming in mono mode */
#define USB_AUDIO_SRC_EVARG_MODE_MONO                   1
/** @brief streaming in stereo mode */
#define USB_AUDIO_SRC_EVARG_MODE_STEREO                 2
/** @} */

/** @brief event argument */
typedef struct usb_audio_evarg {
    /**< current mode of operation */
    int type, mode; 
    /**< data to be provided by the event recipient */
    const void *ptr;
    /**< data size */
    size_t size;
} usb_audio_evarg_t;

/** @brief data request event */
extern ev_t usb_audio_ev;

/**
 * @brief Initialize the audio source support
 * 
 * @return int status code
 */
int USBAudioSrc_Init(void);


/*TODO: */
void USBAudioSrc_Transfer(void *ptr, size_t size);

#endif /* USB_AUDIOSRC_H */
