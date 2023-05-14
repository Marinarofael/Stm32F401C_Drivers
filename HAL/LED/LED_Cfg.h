/*
 * LED_Cfg.h
 *
 *  Created on: Feb 21, 2023
 *      Author: lenovo
 */

#ifndef LED_CFG_H_
#define LED_CFG_H_

#include "GPIO.h"

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef enum
{
	LED_enuSendDone = 0,
	LED_enuReceiveDone,
	LED_enuLedApp2 ,
	/*LED_enuLedApp3 ,
	LED_enuLedApp4 ,*/
	LED_enuLedCount

}LED_tenuLEDS;

typedef enum
{
	LED_enuActiveHigh = 0,
	LED_enuActiveLow ,

}LED_tenuMode;

typedef struct
{
	GPIO_tenuPort port;
	GPIO_tenuPinNumber pin;
	LED_tenuMode mode;
	GPIO_tenuPinSpeed speed;

}LEDcfg_t;

extern const LEDcfg_t LED_ledcfg[LED_enuLedCount];

#endif /* LED_CFG_H_ */
