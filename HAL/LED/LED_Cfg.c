/*
 * LED_Cfg.c
 *
 *  Created on: Feb 21, 2023
 *      Author: lenovo
 */

#include "LED_Cfg.h"


/***************************************************************************************************/
/****************************************** VARIABLES **********************************************/


const LEDcfg_t LED_ledcfg[LED_enuLedCount] =
{
	[LED_enuSendDone] = {
		.port = GPIO_enuPortGPIOA ,
		.pin = GPIO_enuPin_0 ,
		.mode = LED_enuActiveHigh ,
		.speed = GPIO_enuSpeedHigh
	},

	[LED_enuReceiveDone] = {
			.port = GPIO_enuPortGPIOA ,
			.pin = GPIO_enuPin_1 ,
			.mode = LED_enuActiveHigh ,
			.speed = GPIO_enuSpeedHigh
		},


	[LED_enuLedApp2] = {
		.port = GPIO_enuPortGPIOA ,
		.pin = GPIO_enuPin_2 ,
		.mode = LED_enuActiveHigh ,
		.speed = GPIO_enuSpeedHigh
	},
/*
	[LED_enuLedApp3] = {
		.port = GPIO_enuPortGPIOA ,
		.pin = GPIO_enuPin_2 ,
		.mode = LED_enuActiveHigh ,
		.speed = GPIO_enuSpeedHigh
	},

	[LED_enuLedApp4] = {
		.port = GPIO_enuPortGPIOA ,
		.pin = GPIO_enuPin_3 ,
		.mode = LED_enuActiveHigh ,
		.speed = GPIO_enuSpeedHigh
	}*/
};


