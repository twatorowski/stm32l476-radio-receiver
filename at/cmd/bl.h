/**
 * @file bl.h
 * 
 * @date 2019-09-27
 * @author your name (you@domain.com)
 * 
 * @brief 
 */

#ifndef AT_CMD_BL_H_
#define AT_CMD_BL_H_

#include "at/cmd.h"

/** @brief bootloader command list */
extern const at_cmd_t at_cmd_bl_list[];

/**
 * @brief Initialize bootloader commands submodule
 * 
 * @return int error code (@ref ERR_ERROR_CODES)
 */
int ATCmdBootLoader_Init(void);

/**
 * @brief Poll bootloader commads submodule
 */
void ATCmdBootloader_Poll(void);


#endif /* AT_CMD_BL_H_ */
