/*
 * Systick.c
 *
 *  Created on: Mar 8, 2023
 *      Author: Marina Wagdy
 */

#include "Std_types.h"
#include "Bit_math.h"
#include "Systick.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

/* Base address of Systick */
#define SYSTICK_BASE 0xE000E010

/* Systick Enable */
#define STK_ENABLE 0b1
#define STK_DISABLE 0b0

/* Systick exception enable */
#define STK_EXCEPTION_ENABLE 0b10
#define STK_EXCEPTION_DISABLE 0b00

/* Systick clk source*/
#define STK_CLK_SOURCE 2
#define STK_PRESCALER_MASK 0b100
#define STK_SYSTEM_CLK 25000000
#define STK_MILLI_CONVERTER 1000
#define STK_MICRO_CONVERTER 1000000
#define STK_AHB_PRESCALER 8

/***************************************************************************************************/
/******************************************** Types **********************************************/

typedef struct
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
}STK;

/***************************************************************************************************/
/******************************************* VARIABLES *********************************************/

STK * STKptr = (STK *) SYSTICK_BASE;

SystickCbf_t ApplicationCbf = NULL ;

/***************************************************************************************************/
/******************************* FUNCTIONS IMPLEMENTATION ******************************************/

/* implementation of function to start systick timer */
STK_tenuErrorStatus STK_Start()
{
	STK_tenuErrorStatus Loc_enuReturn = STK_enuOK;

	//(STKptr->STK_CTRL) |=  (STK_ENABLE);
	SET_BIT(STKptr->STK_CTRL, 0);

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to stop systick timer */
STK_tenuErrorStatus STK_Stop()
{
	STK_tenuErrorStatus Loc_enuReturn = STK_enuOK;

	//(STKptr->STK_CTRL) |= (STK_DISABLE);
	CLR_BIT(STKptr->STK_CTRL, 0);

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to enable exception in systick timer */
STK_tenuErrorStatus STK_EnableException()
{
	STK_tenuErrorStatus Loc_enuReturn = STK_enuOK;

	//(STKptr->STK_CTRL) |=  (STK_ENABLE << 0x01);
	SET_BIT(STKptr->STK_CTRL, 1);

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to disable exception in systick timer */
STK_tenuErrorStatus STK_DisableException()
{
	STK_tenuErrorStatus Loc_enuReturn = STK_enuOK;

	//(STKptr->STK_CTRL) |=  (STK_EXCEPTION_DISABLE);
	CLR_BIT(STKptr->STK_CTRL, 1);

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to set function ptr */
STK_tenuErrorStatus STK_SetCbf(SystickCbf_t Cpy_NotifyFunction)
{
	STK_tenuErrorStatus Loc_enuReturn = STK_enuOK;

	if(Cpy_NotifyFunction == NULL)
	{
		Loc_enuReturn = STK_enuNullPointer;
	}
	else
	{
		ApplicationCbf = Cpy_NotifyFunction;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to set prescaler */
STK_tenuErrorStatus STK_SetCountTime(STK_tenuClkSource Cpy_enuClkSource)
{
	STK_tenuErrorStatus Loc_enuReturn = STK_enuOK;


	(STKptr->STK_CTRL) |= ( Cpy_enuClkSource << STK_CLK_SOURCE );


	return Loc_enuReturn;

}

/***************************************************************************************************/

/* implementation of function to set load value */

STK_tenuErrorStatus STK_SetPeriodTimeMilliSec(u16 Cpy_RequiredClk)
{
	STK_tenuErrorStatus Loc_enuReturn = STK_enuOK;
	u32 Loc_u32Register = 0;

	Loc_u32Register = STKptr->STK_LOAD;
	if(STKptr->STK_CTRL & STK_PRESCALER_MASK)
	{
		Loc_u32Register = (((u64)Cpy_RequiredClk) * ((u64)STK_SYSTEM_CLK )) / STK_MILLI_CONVERTER ;
	}
	else
	{
		Loc_u32Register = (((u64)Cpy_RequiredClk) * ((u64)STK_SYSTEM_CLK )) / (STK_AHB_PRESCALER * STK_MILLI_CONVERTER);
	}
	STKptr->STK_LOAD = Loc_u32Register;

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to set load value */

STK_tenuErrorStatus STK_SetPeriodTimeMicroSec(u16 Cpy_RequiredClk)
{
	STK_tenuErrorStatus Loc_enuReturn = STK_enuOK;
	u32 Loc_u32Register = 0;

	Loc_u32Register = STKptr->STK_LOAD;
	if(STKptr->STK_CTRL & STK_PRESCALER_MASK)
	{
		Loc_u32Register = (((u64)Cpy_RequiredClk) * ((u64)STK_SYSTEM_CLK )) / STK_MICRO_CONVERTER;
	}
	else
	{
		Loc_u32Register = (((u64)Cpy_RequiredClk) * ((u64)STK_SYSTEM_CLK )) / (STK_AHB_PRESCALER * STK_MICRO_CONVERTER);
	}
	STKptr->STK_LOAD = Loc_u32Register;

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function handler of systick timer */
void SysTick_Handler(void)
{
	if(ApplicationCbf)
	{
		ApplicationCbf();
	}
}
