/**
 * @file radio.h
 * 
 * @date 2020-02-03
 * @author twatorowski 
 * 
 * @brief 
 */

#ifndef AT_CMD_RADIO_H
#define AT_CMD_RADIO_H

#include "at/cmd.h"

/** @brief radio command list */
extern const at_cmd_t at_cmd_radio_list[];

/**
 * @brief initialize radio commands submodule
 * 
 * @return int status
 */
int ATCmdRadio_Init(void);

/**
 * @brief poll radio commands submodule 
 */
void ATCmdRadio_Poll(void);

#endif /* AT_CMD_RADIO_H */
