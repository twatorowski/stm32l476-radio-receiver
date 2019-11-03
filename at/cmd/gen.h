/**
 * @file gen.h
 * 
 * @date 2019-09-09
 * @author your name (you@domain.com)
 * 
 * @brief AT Commands: General commands
 */

#ifndef AT_CMD_GEN_H_
#define AT_CMD_GEN_H_

#include "at/cmd.h"

/** @brief generic command list */
extern const at_cmd_t at_cmd_gen_list[];

/**
 * @brief Initialize general commands submodule
 * 
 * @return int error code (@ref ERR_ERROR_CODES)
 */
int ATCmdGen_Init(void);

/**
 * @brief Poll general commands submodule
 */
void ATCmdGen_Poll(void);

#endif /* AT_CMD_GEN_H_ */
