/**
 * @file at.c
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief AT Protocol implementation main file
 */

#include "err.h"
#include "at/cmd.h"
#include "at/ntf.h"
#include "at/rxtx.h"

/* AT protocol at commands interface */
int AT_Init(void)
{
	/* initialize transmission/reception module */
	ATRxTx_Init();
	/* initialize command parser */
	ATCmd_Init();
	/* initialize notifications */
	ATNtf_Init();

	/* report status */
	return EOK;
}

/* test protocol polling */
void AT_Poll(void)
{
	/* poll rx/tx module */
	ATRxTx_Poll();
	/* poll notification stuff */
	ATNtf_Poll();
	/* poll command module */
	ATCmd_Poll();
}
