/*
 * Switch.h
 *
 *  Created on: Feb 24, 2023
 *      Author: lenovo
 */

#ifndef HAL_SWITCH_H_
#define HAL_SWITCH_H_


#include "Std_types.h"
#include "Bit_math.h"
#include "Switch_Cfg.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

#define SWITCH_STATE_PRESSED 1
#define SWITCH_STATE_NOT_PRESSED 0

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef enum
{
	Switch_enuOK = 0 ,
	Switch_enuNotOk,
	Switch_enuNullPointer
}Switch_tenuErrorStatus;


/***************************************************************************************************/
/********************************************** APIS ***********************************************/

/*****************************************
 * To initialize Switch pins             *
 * input : void                          *
 * return : error status                 *
 *****************************************/
Switch_tenuErrorStatus switch_Init(void);


/**************************************************************
 * To get the state of the switch                             *
 * input : enum from LED_enuSwitches                          *
 *         address of variable to get the state of switch     *
 * return : error status                                      *
 **************************************************************/
Switch_tenuErrorStatus switch_GetState(LED_tenuSwitches Cpy_Switch, u8 * Cpy_pu8SwitchState);


/*****************************************
 * To handle debouncing                  *
 * input : void                          *
 * return : error status                 *
 *****************************************/
Switch_tenuErrorStatus switch_HandleDebouncing(void);

#endif /* HAL_SWITCH_H_ */
