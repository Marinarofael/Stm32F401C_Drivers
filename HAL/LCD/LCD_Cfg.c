/*
 * LCD_Cfg.c
 *
 *  Created on: Mar 24, 2023
 *      Author: Marina Wagdy
 */

#include "LCD_Cfg.h"

const LCDcfg_t LCD_LcdCfg[LCD_enuPinNumbers] =
{

		[LCD_enuDataPin0] = {
				.port = GPIO_enuPortGPIOB,
				.pin = GPIO_enuPin_0
		},

		[LCD_enuDataPin1] = {
				.port = GPIO_enuPortGPIOB,
				.pin = GPIO_enuPin_1
		},

		[LCD_enuDataPin2] = {
				.port = GPIO_enuPortGPIOB,
				.pin = GPIO_enuPin_2
		},

		[LCD_enuDataPin3] = {
				.port = GPIO_enuPortGPIOB,
				.pin = GPIO_enuPin_3
		},

		[LCD_enuDataPin4] = {
				.port = GPIO_enuPortGPIOB,
				.pin = GPIO_enuPin_4
		},

		[LCD_enuDataPin5] = {
				.port = GPIO_enuPortGPIOB,
				.pin = GPIO_enuPin_5
		},

		[LCD_enuDataPin6] = {
				.port = GPIO_enuPortGPIOB,
				.pin = GPIO_enuPin_6
		},

		[LCD_enuDataPin7] = {
				.port = GPIO_enuPortGPIOB,
				.pin = GPIO_enuPin_7
		},
		[LCD_enuControlPinRS] = {
				.port = GPIO_enuPortGPIOB,
				.pin = GPIO_enuPin_12
		},

		[LCD_enuControlPinRW] = {
				.port = GPIO_enuPortGPIOB,
				.pin = GPIO_enuPin_13
		},

		[LCD_enuControlPinE] = {
				.port = GPIO_enuPortGPIOB,
				.pin = GPIO_enuPin_14
		}


};

