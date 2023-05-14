/*
 * LED.h
 *
 *  Created on: Feb 21, 2023
 *      Author: lenovo
 */

#ifndef LED_H_
#define LED_H_

#include "Std_types.h"
#include "Bit_math.h"
#include "LED_Cfg.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

#define LED_STATE_ON 1
#define LED_STATE_OFF 0
#define LED_STATE_TOGGLE 2

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef enum
{
	LED_enuOK = 0 ,
	LED_enuNotOk,
	LED_enuNullPointer

}LED_tenuErrorStatus;


/***************************************************************************************************/
/********************************************** APIS ***********************************************/

/*****************************************
 * To initialize LED pins                *
 * input : void                          *
 * return : error status                 *
 *****************************************/
LED_tenuErrorStatus led_Init(void);


/**************************************************************
 * To set the state of the led                                *
 * input : object from LEDcfg_t structure                     *
 *         state of led: LED_STATE_ON / LED_STATE_OFF         *
 * return : error status                                      *
 **************************************************************/
LED_tenuErrorStatus led_SetState(LED_tenuLEDS Cpy_Led, u8 Cpy_LedState);


#endif /* LED_H_ */
