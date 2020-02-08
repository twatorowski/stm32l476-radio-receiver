/**
 * @file radio.c
 * 
 * @date 2020-02-05
 * @author twatorowski 
 * 
 * @brief AT Notifications: Radio.
 */

#include <stdint.h>
#include <stddef.h>

#include "compiler.h"
#include "config.h"
#include "err.h"
#include "at/ntf.h"
#include "at/rxtx.h"
#include "base64/base64.h"
#include "util/elems.h"
#include "util/minmax.h"
#include "util/string.h"

/* iqdata buffer */
static struct iqdata {
    /* samples buffer */
    struct iqdata_iq { float i, q; } PACKED ALIGNED(8) buf[128];
    /* pointers */
    uint32_t head, tail;
} iqdata;

/* polling for the iq samples */
static void ATNtfRadio_IQSamplesPoll(void)
{
    /* data sent? */
	int sent = 0;
    /* response buffer */
    char buf[AT_RES_MAX_LINE_LEN] = "+RADIO_IQ: ";
    /* current len of the response */
    int len = sizeof("+RADIO_IQ: ") - 1;
    
    /* notification mask */
    uint32_t mask;
    /* get mask for all notifications */
    ATNtf_GetNotificationORMask(&mask);
	/* notification is disabled? */
	if (!(mask & AT_NTF_MASK_RADIO_IQ))
		iqdata.tail = iqdata.head;
    /* no samples are stored */
    if (iqdata.head - iqdata.tail < 16)
        return;

    /* get the number data characters that can be put into the response */
    int max_chars = sizeof(buf) - len - sizeof(AT_LINE_END);
    /* convert to maximal number of representable bytes when base64 is used */
    int max_bytes = (max_chars / 4) * 3;
    /* get tail index */
    int t = iqdata.tail % elems(iqdata.buf);
    /* limit the number of iq pairs to be sent in current line while not 
     * wrapping within the circular buffer */
    int max_iqs = min(iqdata.head - iqdata.tail, 
        min(elems(iqdata.buf) - t, max_bytes / sizeof(struct iqdata_iq)));

    /* encode data in base64 */
    int b64_len = Base64_Encode(iqdata.buf + t, 
       sizeof(struct iqdata_iq) * max_iqs, buf + len, max_chars);
    /* append the line ending sequence */
    memcpy(buf + len + b64_len, AT_LINE_END, sizeof(AT_LINE_END));

    /* send response */
	for (int iface = 0; iface < ATRXTX_IFACENUM; iface++) {
        /* get notification mask for given interface */
        ATNtf_GetNotificationMask(iface, &mask);
		/* notifications enabled for given interface? */
		if ((mask & AT_NTF_MASK_RADIO_IQ)) {
			/* send the actual data */
			sent |= ATRxTx_SendResponse(iface, 1, buf, len + b64_len + 
                sizeof(AT_LINE_END) - 1) == EOK;
		}
	}

    /* data was sent, update the buffer */
    if (sent)
        iqdata.tail += max_iqs;
}

/* initialize radio notifications submodule */
int ATNtfRadio_Init(void)
{
    /* report status */
    return EOK;
}

/* poll radio notifications submodule */
void ATNtfRadio_Poll(void)
{
    /* polling for the iq samples */
    ATNtfRadio_IQSamplesPoll();
}

/* store the iq data samples in at notifications buffer */
int ATNtfRadio_PutIQSamples(const float *i, const float *q, int num)
{
    /* notification mask placeholder */
    uint32_t mask;

    /* get mask for all notifications */
    ATNtf_GetNotificationORMask(&mask);
	/* radio data notifications enabled? */
	if (!(mask & AT_NTF_MASK_RADIO_IQ))
		return EOK;
    /* no space in buffer */
    if (num > elems(iqdata.buf) - (iqdata.head - iqdata.tail))
        return EFATAL;
    
    /* head element index */
    int h = iqdata.head % elems(iqdata.buf);
    /* number of elements to be stored before wrapping */
    int bwrap = min(num, elems(iqdata.buf) - h);
    /* number of elements to be stored after wrapping */
    int awrap = num - bwrap;

    /* store before wrapping */
    for (; bwrap ; bwrap--, h++) {
        iqdata.buf[h].i = *i++; iqdata.buf[h].q = *q++;
    }
    /* store after wrapping */
    for (h = 0; awrap; awrap--, h++) {
        iqdata.buf[h].i = *i++; iqdata.buf[h].q = *q++;
    }

    /* update the head pointer */
    iqdata.head += num;
    /* report status */
	return EOK;
}