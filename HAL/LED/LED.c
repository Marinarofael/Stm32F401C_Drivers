#include "GPIO.h"
#include "LED.h"

/***************************************************************************************************/
/******************************* FUNCTIONS IMPLEMENTATION ******************************************/

/* implementation of function to initialize led pin */
LED_tenuErrorStatus led_Init(void)
{

	LED_tenuErrorStatus Loc_enReturn = LED_enuOK ;
	gpio_Init_t Loc_gpioCfg ;
	u8 Loc_u8Counter = 0;
	for(Loc_u8Counter = 0; Loc_u8Counter < LED_enuLedCount; Loc_u8Counter++)
	{
		Loc_gpioCfg.mode = GPIO_MODE_GP_PUSH_PULL;
		Loc_gpioCfg.port = LED_ledcfg[Loc_u8Counter].port;
		Loc_gpioCfg.pin = LED_ledcfg[Loc_u8Counter].pin;
		Loc_gpioCfg.speed = LED_ledcfg[Loc_u8Counter].speed;
		gpio_InitPin(&Loc_gpioCfg);
	}

	return Loc_enReturn;
}

/***************************************************************************************************/

/* implementation of function to set the state of led */
LED_tenuErrorStatus led_SetState(LED_tenuLEDS Cpy_Led, u8 Cpy_LedState)
{
	LED_tenuErrorStatus Loc_enReturn = LED_enuOK ;
	u8 Loc_u8LedCurrentState = 0;

	if(Cpy_LedState == LED_STATE_TOGGLE)
	{
		gpio_GetPinValue(LED_ledcfg[Cpy_Led].port, LED_ledcfg[Cpy_Led].pin, &Loc_u8LedCurrentState);
		gpio_WritePinValue(LED_ledcfg[Cpy_Led].port, LED_ledcfg[Cpy_Led].pin, (Loc_u8LedCurrentState ^ 0b1) ^ LED_ledcfg[Cpy_Led].mode);
	}
	else
	{
		gpio_WritePinValue(LED_ledcfg[Cpy_Led].port, LED_ledcfg[Cpy_Led].pin, Cpy_LedState ^ LED_ledcfg[Cpy_Led].mode);
	}

	return Loc_enReturn;
}

/***************************************************************************************************/
