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

/** @name USB audio working modes */
/** @{ */
/** @brief no audio streaming */
#define USB_AUDIO_SRC_MODE_OFF                    0
/** @brief streaming in mono mode */
#define USB_AUDIO_SRC_MODE_MONO                   1
/** @brief streaming in stereo mode */
#define USB_AUDIO_SRC_MODE_STEREO                 2
/** @} */

/** @brief event argument */
typedef struct usb_audio_evarg {
    /**< current mode of operation */
    int mode;
} usb_audio_evarg_t;

/** @brief data request event */
extern ev_t usb_audio_ev;

/**
 * @brief Initialize the audio source support
 * 
 * @return int status code
 */
int USBAudioSrc_Init(void);

/**
 * @brief Store audio samples within the usb buffer
 * 
 * @param l left channel data holding array
 * @param r right channel data holding array
 * @param num number of pairs of samples
 * 
 * @return int number of pairs of samples that were stored within the buffer
 */
int USBAudioSrc_PutSamples(const int32_t *l, const int32_t *r, int num);

#endif /* USB_AUDIOSRC_H */
