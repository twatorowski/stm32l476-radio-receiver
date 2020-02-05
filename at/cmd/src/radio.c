/**
 * @file radio.c
 * 
 * @date 2020-02-03
 * @author twatorowski 
 * 
 * @brief AT Commands for controlling the radio part
 */

#include <stdint.h>
#include <stddef.h>

#include "config.h"
#include "err.h"
#include "at/cmd.h"
#include "radio/radio.h"
#include "util/stdio.h"

/* process AT+RADIO= command */
static int ATCmdRadio_ProcFrequencySet(int iface, const char *line, size_t len)
{
    /* placeholder for the frequency value */
    float f;

	/* try to parse the input string */
	if (sscanf(line, "AT+RADIO_TUNE=%e%", &f) != 2)
        return EAT_SYNTAX;
    
	/* not much to do with such a simple command :-) */
	return Radio_SetFrequency(f);
}

/* read the frequency that the radio is tuned to */
static int ATCmdRadio_ProcFrequencyRead(int iface, const char *line, 
    size_t len)
{   
    /* frequency */
    float f;

	/* try to parse the input string */
	if (sscanf(line, "AT+RADIO_TUNE?%") != 1)
		return EAT_SYNTAX;

    /* get the frequency */
    if (Radio_GetFrequency(&f) != EOK)
        return EFATAL;

    /* buffer for the response */
    char res[AT_RES_MAX_LINE_LEN];
    /* render the response */
    size_t res_len = snprintf(res, sizeof(res), 
        "+RADIO_TUNE: %.5e" AT_LINE_END, f);
	/* execute command and report status */
	return ATCmd_SendResponse(iface, res, res_len);
}

/* radio command list */
const at_cmd_t at_cmd_radio_list[] = {
    /* tuning */
    { .cmd = "AT+RADIO_TUNE=", .func = ATCmdRadio_ProcFrequencySet },
    { .cmd = "AT+RADIO_TUNE?", .func = ATCmdRadio_ProcFrequencyRead },

    /* end of the command list */
    { .cmd = "" },
};

/* initialize general commands submodule */
int ATCmdRadio_Init(void)
{
    /* report status */
    return EOK;
}

/* poll general commands submodule */
void ATCmdRadio_Poll(void)
{

}