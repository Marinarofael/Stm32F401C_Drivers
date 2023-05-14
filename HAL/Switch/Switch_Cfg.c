/*
 * Switch_Cfg.c
 *
 *  Created on: Feb 24, 2023
 *      Author: lenovo
 */

#ifndef SWITCH_CFG_H
#define SWITCH_CFG_H

#include "Switch_Cfg.h"

/***************************************************************************************************/
/****************************************** VARIABLES **********************************************/

const SwitchCfg_t Switch_SwitchCfg[Switch_enuSwitchCount] =
{
		[Switch_enuSwitchApp4] = {
				.port = GPIO_enuPortGPIOA,
				.pin = GPIO_enuPin_5,
				.speed = GPIO_enuSpeedHigh,
				.mode = Switch_enuInternalPullUp
		}
};



#endif /* SWITCH_CFG_H */
