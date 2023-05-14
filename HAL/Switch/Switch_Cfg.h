/*
 * Switch_Cfg.h
 *
 *  Created on: Feb 24, 2023
 *      Author: lenovo
 */

#ifndef HAL_SWITCH_CFG_H_
#define HAL_SWITCH_CFG_H_

#include "GPIO.h"

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef enum
{
	Switch_enuSwitchApp4 = 0 ,
	Switch_enuSwitchCount

}LED_tenuSwitches;

typedef enum
{
	Switch_enuInternalPullUp = 0 ,
	Switch_enuInternalPullDown ,
	Switch_enuExternalPullUp ,
	Switch_enuExternalPullDown

}Switch_tenuMode;

typedef struct
{
	GPIO_tenuPort port;
	GPIO_tenuPinNumber pin;
	Switch_tenuMode mode;
	GPIO_tenuPinSpeed speed;

}SwitchCfg_t;

extern const SwitchCfg_t Switch_SwitchCfg[Switch_enuSwitchCount];

#endif /* HAL_SWITCH_CFG_H_ */
