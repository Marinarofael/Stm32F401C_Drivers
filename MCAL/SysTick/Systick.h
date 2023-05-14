/*
 * Systick.h
 *
 *  Created on: Mar 8, 2023
 *      Author: Marina Wagdy
 */

#ifndef MCAL_SYSTICK_H_
#define MCAL_SYSTICK_H_

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef enum
{
	STK_enuOK = 0,
	STK_enuNotOk,
	STK_enuNullPointer

}STK_tenuErrorStatus;

typedef enum
{
	STK_enuClkSourceAHBdivideBy8 = 0,
	STK_enuClkSourceAHB

}STK_tenuClkSource;

typedef void (* SystickCbf_t) (void);

/***************************************************************************************************/
/************************************** FUNCTIONS APIS *********************************************/

/*****************************************************
 * To start Systick timer                            *
 * input : void                                      *
 * return : Error status                             *
 *****************************************************/
STK_tenuErrorStatus STK_Start(void);


/*****************************************************
 * To enable Systick timer exception request         *
 * input : void                                      *
 * return : Error status                             *
 *****************************************************/
STK_tenuErrorStatus STK_EnableException(void);


/*****************************************************
 * To disable Systick timer exception request        *
 * input : void                                      *
 * return : Error status                             *
 *****************************************************/
STK_tenuErrorStatus STK_DisableException(void);


/*****************************************************
 * To stop Systick timer                             *
 * input : void                                      *
 * return : Error status                             *
 *****************************************************/
STK_tenuErrorStatus STK_Stop(void);


/*****************************************************
 * To set call back function for Systick timer       *
 * input : function pointer                          *
 * return : Error status                             *
 *****************************************************/
STK_tenuErrorStatus STK_SetCbf(SystickCbf_t NotifyFunction);

/***************************************************************
 * To set count time of Systick timer                          *
 * input : STK_enuClkSourceAHBdivideBy8 /  STK_enuClkSourceAHB *
 * return : Error status                                       *
 ***************************************************************/
STK_tenuErrorStatus STK_SetCountTime(STK_tenuClkSource Cpy_enuClkSource);


/*****************************************************
 * To set period time for Systick timer in msec      *
 * input : Period time in ms                         *
 * return : Error status                             *
 *****************************************************/
STK_tenuErrorStatus STK_SetPeriodTimeMilliSec(u16 Cpy_RequiredClk);


/*****************************************************
 * To set period time for Systick timer in micro sec *
 * input : Period time in micro sec                  *
 * return : Error status                             *
 *****************************************************/
STK_tenuErrorStatus STK_SetPeriodTimeMicroSec(u16 Cpy_RequiredClk);

#endif /* MCAL_SYSTICK_H_ */
