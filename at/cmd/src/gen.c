/**
 * @file gen.c
 * 
 * @date 2019-09-09
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief AT Commands: General commands
 */

#include <stdint.h>
#include <stddef.h>

#include "config.h"
#include "err.h"
#include "at/cmd.h"
#include "at/ntfy.h"
#include "util/stdio.h"

/* process AT command */
static int ATCmdGen_ProcAT(int iface, const char *line, size_t len)
{
	/* try to parse the input string */
	if (sscanf(line, "AT%") != 1)
        return EAT_SYNTAX;
	/* not much to do with such a simple command :-) */
	return EOK;
}

/* set value of the notification mask */
static int ATCmdGen_ProcNotificationMaskSet(int iface, const char *line, 
    size_t len)
{
    /* command parameters */
    uint32_t mask;

    /* parse the input string */
    if (sscanf(line, "AT+NTFY=%i%", &mask) != 2)
        return EAT_SYNTAX;

    /* set the mask */
    return ATNtfy_SetNotificaionMask(iface, mask);
}

/* read current value of the notification mask */
static int ATCmdGen_ProcNotificationMaskRead(int iface, const char *line, 
    size_t len)
{   
    /* notification mask */
    uint32_t mask;

	/* try to parse the input string */
	if (sscanf(line, "AT+NTFY?%") != 1)
		return EAT_SYNTAX;

    /* get current mask value */
    if (ATNtfy_GetNotificationMask(iface, &mask) != EOK)
        return EFATAL;

    /* buffer for the response */
    char res[AT_RES_MAX_LINE_LEN];
    /* render the response */
    size_t res_len = snprintf(res, sizeof(res), "+NTFY: %#010x" AT_LINE_END, 
        mask);
	/* execute command and report status */
	return ATCmd_SendResponse(iface, res, res_len);
}

/* set bits of the notification mask */
static int ATCmdGen_ProcNotificationMaskEnableSet(int iface, const char *line, 
    size_t len)
{
    /* command parameters */
    uint32_t current_mask, mask;

    /* parse the input string */
    if (sscanf(line, "AT+NTFYEN=%i%", &mask) != 2)
        return EAT_SYNTAX;
    /* get current mask value */
    if (ATNtfy_GetNotificationMask(iface, &current_mask) != EOK)
        return EFATAL;

    /* set the mask */
    return ATNtfy_SetNotificaionMask(iface, current_mask | mask);
}

/* clear bits of the notification mask */
static int ATCmdGen_ProcNotificationMaskDisableSet(int iface, const char *line, 
    size_t len)
{
    /* command parameters */
    uint32_t current_mask, mask;

    /* parse the input string */
    if (sscanf(line, "AT+NTFYDIS=%i%", &mask) != 2)
        return EAT_SYNTAX;
    /* get current mask value */
    if (ATNtfy_GetNotificationMask(iface, &current_mask) != EOK)
        return EFATAL;

    /* set the mask */
    return ATNtfy_SetNotificaionMask(iface, current_mask & ~mask);
}

/* generic command list */
const at_cmd_t at_cmd_gen_list[] = {
    /* echo */
    { .cmd = "AT", .func = ATCmdGen_ProcAT },
    /* notifications enable/disable */
    { .cmd = "AT+NTFY=", .func = ATCmdGen_ProcNotificationMaskSet },
    { .cmd = "AT+NTFY?", .func = ATCmdGen_ProcNotificationMaskRead },
    { .cmd = "AT+NTFYEN=", .func = ATCmdGen_ProcNotificationMaskEnableSet },
    { .cmd = "AT+NTFYDIS=", .func = ATCmdGen_ProcNotificationMaskDisableSet },

    /* end of the command list */
    { .cmd = "" },
};

/* initialize general commands submodule */
int ATCmdGen_Init(void)
{
    /* report status */
    return EOK;
}

/* poll general commands submodule */
void ATCmdGen_Poll(void)
{

}