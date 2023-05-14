/*
 * Switch.c
 *
 *  Created on: Feb 24, 2023
 *      Author: lenovo
 */

#include "GPIO.h"
#include "Switch.h"

u8 SwitchState[Switch_enuSwitchCount] = {0};

/***************************************************************************************************/
/******************************* FUNCTIONS IMPLEMENTATION ******************************************/

/* implementation of function to initialize switch pin
Switch_tenuErrorStatus switch_Init(void)
{
	Switch_tenuErrorStatus Loc_enuReturn = Switch_enuOK;
	u8 Loc_u8Counter = 0;
	gpio_Init_t Loc_gpioCfg;

	for(Loc_u8Counter = 0; Loc_u8Counter < Switch_enuSwitchCount; Loc_u8Counter++)
	{
		Loc_gpioCfg.port = Switch_SwitchCfg[Loc_u8Counter].port;
		Loc_gpioCfg.pin = Switch_SwitchCfg[Loc_u8Counter].pin;
		Loc_gpioCfg.speed = Switch_SwitchCfg[Loc_u8Counter].speed;

		if((Switch_SwitchCfg[Loc_u8Counter].mode == Switch_enuExternalPullDown) || (Switch_SwitchCfg[Loc_u8Counter].mode == Switch_enuExternalPullUp))
		{
			Loc_gpioCfg.mode = GPIO_MODE_INPUT_FLOATING;
		}
		else if(Switch_SwitchCfg[Loc_u8Counter].mode == Switch_enuInternalPullDown)
		{
			Loc_gpioCfg.mode = GPIO_MODE_INPUT_PULL_DOWN;
		}
		else if(Switch_SwitchCfg[Loc_u8Counter].mode == Switch_enuInternalPullUp)
		{
			Loc_gpioCfg.mode = GPIO_MODE_INPUT_PULL_UP;
		}

		gpio_InitPin(&Loc_gpioCfg);
	}

	return Loc_enuReturn ;
}*/

/***************************************************************************************************/

/* implementation of function to get the state of switch */
Switch_tenuErrorStatus switch_GetState(LED_tenuSwitches Cpy_Switch, u8 * Cpy_pu8SwitchState)
{
	Switch_tenuErrorStatus Loc_enuReturn = Switch_enuOK;
	//u8 Loc_u8PinValue = 0;

	if(Cpy_pu8SwitchState == NULL)
	{
		Loc_enuReturn = Switch_enuNullPointer;
	}
	else
	{
		* Cpy_pu8SwitchState = SwitchState[Cpy_Switch];
		/*gpio_GetPinValue(Switch_SwitchCfg[Cpy_Switch].port, Switch_SwitchCfg[Cpy_Switch].pin, &Loc_u8PinValue);

		if((Switch_SwitchCfg[Cpy_Switch].mode == Switch_enuExternalPullDown) || (Switch_SwitchCfg[Cpy_Switch].mode == Switch_enuInternalPullDown))
		{
			* Cpy_pu8SwitchState = Loc_u8PinValue;
		}
		else if((Switch_SwitchCfg[Cpy_Switch].mode == Switch_enuExternalPullUp) || (Switch_SwitchCfg[Cpy_Switch].mode == Switch_enuInternalPullUp))
		{
			* Cpy_pu8SwitchState = Loc_u8PinValue ^ 0x01 ;
		}*/
	}
	return Loc_enuReturn ;
}


/***************************************************************************************************/
/* implementation of function to handle debouncing
Switch_tenuErrorStatus switch_HandleDebouncing(void)
{
	Switch_tenuErrorStatus Loc_enuReturn = Switch_enuOK;
	static u8 Loc_arrcounter[Switch_enuSwitchCount] = {0};
	static u8 Loc_arrPrevValue[Switch_enuSwitchCount] = {0};
	u8 Loc_u8CurrentValue = 0, Loc_u8Index = 0;

	for(Loc_u8Index = 0; Loc_u8Index < Switch_enuSwitchCount; Loc_u8Index++)
	{
		gpio_GetPinValue(Switch_SwitchCfg[Loc_u8Index].port, Switch_SwitchCfg[Loc_u8Index].pin, &Loc_u8CurrentValue);
		if(Loc_u8CurrentValue == Loc_arrPrevValue[Loc_u8Index])
		{
			Loc_arrcounter[Loc_u8Index]++;
		}
		else
		{
			Loc_arrcounter[Loc_u8Index] = 0;
		}
		if(Loc_arrcounter[Loc_u8Index] == 5)
		{
			if((Switch_SwitchCfg[Loc_u8Index].mode == Switch_enuExternalPullDown) || (Switch_SwitchCfg[Loc_u8Index].mode == Switch_enuInternalPullDown))
			{
				SwitchState[Loc_u8Index] = Loc_u8CurrentValue;
			}
			else if((Switch_SwitchCfg[Loc_u8Index].mode == Switch_enuExternalPullUp) || (Switch_SwitchCfg[Loc_u8Index].mode == Switch_enuInternalPullUp))
			{
				SwitchState[Loc_u8Index] = Loc_u8CurrentValue ^ 0x01 ;
			}
			Loc_arrcounter[Loc_u8Index] = 0;
		}
		Loc_arrPrevValue[Loc_u8Index] = Loc_u8CurrentValue;
	}

	return Loc_enuReturn ;
}*/
