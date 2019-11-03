/**
 * @file bl.c
 * 
 * @date 2019-09-27
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief AT Commands: Bootloader Commands
 */

#include <stdint.h>
#include <stddef.h>

#include "config.h"
#include "err.h"
#include "at/cmd.h"
#include "at/ntfy.h"
#include "util/stdio.h"


/* get firmware version */
static int ATCmdBootLoader_ProcGetVersion(int iface, const char *line, 
    size_t size)
{
    return EFATAL;
}

/* write a firmware chunk */
static int ATCmdBootLoader_ProcWrite(int iface, const char *line, size_t len)
{
    return EFATAL;
}

/* start the execution of the firmware */
static int ATCmdBootLodaer_ProcStart(int iface, const char *line, size_t len)
{
    return EFATAL;
}

/* bootloader command list */
const at_cmd_t at_cmd_bl_list[] = {

    /* get version */
    { .cmd = "AT+BLGETVER=", .func = ATCmdBootLoader_ProcGetVersion },
    /* write */
    { .cmd = "AT+BLWRITE=", .func = ATCmdBootLoader_ProcWrite },
    /* run */
    { .cmd = "AT+BLSTART=", .func = ATCmdBootLodaer_ProcStart },

    /* end of the command list */
    { .cmd = "" },
};

/* initialize bootloader commands submodule */
int ATCmdBootLoader_Init(void)
{
    /* report status */
    return EOK;
}

/* poll bootloader commands submodule */
void ATCmdBootloader_Poll(void)
{

}