/**
 * @file cmd.c
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief Commands part of the AT protocol
 */

#include <stdint.h>
#include <stddef.h>
#include "config.h"
#include "err.h"
#include "at/cmd.h"
#include "at/rxtx.h"
#include "util/elems.h"
#include "util/stdio.h"
#include "util/string.h"
#include "util/strerr.h"

/* all the command providers go here */
#include "at/cmd/gen.h"
#include "at/cmd/bl.h"

/* last used interface for commands that generate responses in later time */
static int last_iface;

/* list of all lists of supported commands */
static const at_cmd_t *cmd_lists[] = {
    at_cmd_gen_list,
    at_cmd_bl_list,
};

/* returns true if character is a whitespace (0xff is a special case for uart
 * filtration) */
static int ATCmd_IsWhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
			c == '\f' || c == '\v' || c ==	0xff);
}

/* normalize line: remove all whitespace characters, convert to upper-case */
static void ATCmd_NormalizeLine(char *line)
{
	/* source and destination pointers */
	char *s; char *d;
	/* remove all whitespace characters, convert all characters to upper case */
	for (s = d = line; *s; s++) {
		/* skip over whitespaces */
		if (ATCmd_IsWhitespace(*s))
			continue;
		/* copy */
		*d = *s;
		/* advance pointer */
		d++;
	}
	/* terminate string */
	*d = '\0';
}

/* returns the length of the command word (with command type characters like "=" or
 * "=?" or "?": AT-> 2 */
static size_t ATCmd_GetCommandLength(const char *line)
{
	/* currently examined character pointer */
	const char *p = line;

	/* skip over all characters that are not like '=' or '?' */
	while (*p && *p != '=' && *p != '?')
		p++;

	/* test command? */
	if (*p == '=' && *(p+1) == '?') {
		p += 2;
	/* set/read command */
	} else if (*p == '=' || *p == '?') {
		p++;
	}

	/* report the size */
	return (size_t) (p - line);
}

/* initialize command parser module */
int ATCmd_Init(void)
{
    /* overall status code */
    int rc = EOK;

    /* initialize all the commands submodules */
    rc |= ATCmdGen_Init();
    rc |= ATCmdBootLoader_Init();

	/* report status */
	return EOK;
}

/* polling done by AT protocol routines */
void ATCmd_Poll(void)
{
    /* poll all submodules */
    /* general commands */
    ATCmdGen_Poll();
    ATCmdBootloader_Poll();
}

/* parser input */
int ATCmd_Input(int iface, char *line)
{
	/* processing status */
	int i, found = 0, rc = EFATAL; size_t len, cmd_len;

	/* get rid of whitespace characters */
	ATCmd_NormalizeLine(line);
	/* get the line length */
	len = strlen(line);

	/* get the command length, store the command word (upper case version)
	 * in the cmd buffer */
	cmd_len = ATCmd_GetCommandLength(line);
	/* convert the command to upper case */
	for (uint32_t i = 0; i < cmd_len; i++)
		if (line[i] >= 'a' && line[i] <= 'z')
			line[i] &= ~0x20;

	/* store last used interface */
	last_iface = iface;

	/* check every command from the list of lists */
	for (i = 0; i < (int)elems(cmd_lists) && !found; i++) {
        /* command pointer shorthand */
        const at_cmd_t *c;
        /* until we reach the empty command field (meaning that the command 
         * list has ended) */
        for (c = cmd_lists[i]; *c->cmd && !found; c++) {
            /* no match in length? */
            if (strlen(c->cmd) != cmd_len) {
			    continue;
            /* got a match? */
            } else if (memcmp(c->cmd, line, cmd_len) == 0) {
                /* mark as found */
                found = 1;
                /* process! */
                rc = c->func(iface, line, len);
            }
        }
	}
    /* unknown command */
    if (!found) {
        rc = EAT_UNKNOWN_CMD;
    /* executed command returned fatal error with no specifics? */
    } else if (rc == EFATAL) {
        rc = EAT_EXEC;
    }
	/* if the commands returns EBUSY that means that we shall refrain for 
     * sending the status as the command will do it all by itself when the time 
     * comes */
	if (rc != EBUSY)
		rc |= ATCmd_SendGeneralResponse(iface, rc);

	/* report status */
	return rc;
}

/* send OK on EOK or ERROR on any other value of rc */
int ATCmd_SendGeneralResponse(int iface, int rc)
{
    /* buffer */
    char res[AT_RES_MAX_LINE_LEN]; size_t len;
    /* render the string */
    if (rc == EOK) {
        len = snprintf(res, sizeof(res), "OK" AT_LINE_END);
    } else {
        len = snprintf(res, sizeof(res), "ERROR: %d, %s" AT_LINE_END, rc, 
            strerr(rc));
    }
	/* send data */
	return ATRxTx_SendResponse(iface, 0, res, len);
}

/* Sends a response over given interface */
int ATCmd_SendResponse(int iface, const char *str, size_t len)
{
    /* send */
    return ATRxTx_SendResponse(iface, 0, str, len);
}