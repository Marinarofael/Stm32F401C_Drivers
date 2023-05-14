#include "GPIO.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

/* base address of GPIO instances */
#define GPIOA_BASE 0x40020000
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800
#define GPIOD_BASE 0x40020C00
#define GPIOE_BASE 0x40021000
#define GPIOH_BASE 0x40021C00

/* clear masks */
#define GPIO_SPEED_CLR_MASK 0b11
#define GPIO_MODE_CLR_MASK 0b00011
#define GPIO_OTYPE_CLR_MASK 0b00100
#define GPIO_PUPD_CLR_MASK 0b11000
#define GPIO_AF_CLR_MASK 0b1111

/* local macros */
#define MODE_GP_OUTPUT 1
#define MODE_AF  2
#define RESET_PIN_NUMBER_OFFSET 16

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef struct GPIO_Peripheral
{
	u32 GPIO_MODER ;
	u32 GPIO_OTYPER ;
	u32 GPIO_OSPEEDR ;
	u32 GPIO_PUPDR ;
	u32 GPIO_IDR ;
	u32 GPIO_ODR ;
	u32 GPIO_BSRR ;
	u32 GPIO_LCKR ;
	u32 GPIO_AFRL ;
	u32 GPIO_AFRH ;
	
}GPIO_t;

/***************************************************************************************************/
/******************************************* VARIABLES *********************************************/

GPIO_t * GPIO[6] = {

		[GPIO_enuPortGPIOA] = (GPIO_t *) GPIOA_BASE,
		[GPIO_enuPortGPIOB] = (GPIO_t *) GPIOB_BASE,
		[GPIO_enuPortGPIOC] = (GPIO_t *) GPIOC_BASE,
		[GPIO_enuPortGPIOD] = (GPIO_t *) GPIOD_BASE,
		[GPIO_enuPortGPIOE] = (GPIO_t *) GPIOE_BASE,
		[GPIO_enuPortGPIOH] = (GPIO_t *) GPIOH_BASE

};


/***************************************************************************************************/
/************************************* IMPLEMENTATION OF FUNCTIONS *********************************/

/* implementation of function to initiate the configuration of pin directions */
GPIO_tenuErrorStatus gpio_InitPin(gpio_Init_t * Cpy_strPin)
{
	GPIO_tenuErrorStatus Loc_enuReturn = GPIO_enuOK;
	u32 Loc_u32Register = 0;
	u8 Loc_u8Temp = 0;
	u8 Loc_u8PinNumber = ( Cpy_strPin->pin ) * 2;
	if(Cpy_strPin == NULL)
	{
		Loc_enuReturn = GPIO_enuNullPointer;
	}
	else
	{
		Loc_u32Register = (GPIO[Cpy_strPin->port])->GPIO_OSPEEDR;
		Loc_u32Register &= ~(GPIO_SPEED_CLR_MASK << Loc_u8PinNumber);
		Loc_u32Register	|= (Cpy_strPin->speed) << Loc_u8PinNumber ;
		(GPIO[Cpy_strPin->port])->GPIO_OSPEEDR = Loc_u32Register;

		Loc_u32Register = (GPIO[Cpy_strPin->port])->GPIO_MODER;
		Loc_u32Register &= ~(GPIO_SPEED_CLR_MASK << Loc_u8PinNumber);
		Loc_u8Temp = Cpy_strPin->mode & GPIO_MODE_CLR_MASK ;
		Loc_u32Register	|= Loc_u8Temp << Loc_u8PinNumber ;
		(GPIO[Cpy_strPin->port])->GPIO_MODER = Loc_u32Register;

		if((Loc_u8Temp == MODE_GP_OUTPUT) || (Loc_u8Temp == MODE_AF))
		{
			Loc_u8Temp = (Cpy_strPin->mode & GPIO_OTYPE_CLR_MASK) >> 2 ;
			(GPIO[Cpy_strPin->port])->GPIO_OTYPER = Loc_u8Temp << (Cpy_strPin->pin) ;
		}

		Loc_u32Register = (GPIO[Cpy_strPin->port])->GPIO_PUPDR;
		Loc_u32Register &= ~(GPIO_SPEED_CLR_MASK << Loc_u8PinNumber);
		Loc_u8Temp = (Cpy_strPin->mode & GPIO_PUPD_CLR_MASK) >> 3 ;
		Loc_u32Register	|= Loc_u8Temp << Loc_u8PinNumber ;
		(GPIO[Cpy_strPin->port])->GPIO_PUPDR = Loc_u32Register;
	}
	return Loc_enuReturn ;
}


/***************************************************************************************************/

/* implementation of function to write pin value */
GPIO_tenuErrorStatus gpio_WritePinValue(GPIO_tenuPort Cpy_enuPort, GPIO_tenuPinNumber Cpy_enuPinNumber, GPIO_tenuPinValue Cpy_enuPinValue )
{
	GPIO_tenuErrorStatus Loc_enuReturn = GPIO_enuOK;

	switch(Cpy_enuPinValue)
	{
	case GPIO_enuValueLow :
		GPIO[Cpy_enuPort]->GPIO_BSRR = 1 << (Cpy_enuPinNumber + RESET_PIN_NUMBER_OFFSET);
		break;

	case GPIO_enuValueHigh :
		GPIO[Cpy_enuPort]->GPIO_BSRR = 1 << Cpy_enuPinNumber ;
		break;

	default :
		Loc_enuReturn = GPIO_enuNotOk;
	}
	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to get pin value */
GPIO_tenuErrorStatus gpio_GetPinValue(GPIO_tenuPort Cpy_enuPort, GPIO_tenuPinNumber Cpy_enuPinNumber, GPIO_tenuPinValue * Cpy_enuPinValue )
{
	GPIO_tenuErrorStatus Loc_enuReturn = GPIO_enuOK;
	u16 Loc_u16Register = 0;

	if(Cpy_enuPinValue == NULL)
	{
		Loc_enuReturn = GPIO_enuNullPointer;
	}
	else
	{
		Loc_u16Register = GPIO[Cpy_enuPort]->GPIO_IDR;
		* Cpy_enuPinValue = (Loc_u16Register >> Cpy_enuPinNumber) & 0x01;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to select alternate function */
GPIO_tenuErrorStatus gpio_SelectAF(GPIO_tenuPort Cpy_enuPort, GPIO_tenuPinNumber Cpy_enuPinNumber, GPIO_tenuAlternatFunction Cpy_enuAF )
{
	GPIO_tenuErrorStatus Loc_enuReturn = GPIO_enuOK;
	u32 Loc_u32Register = 0;
	u8 Loc_u8PinNumber = 0;

	if(Cpy_enuPinNumber <= GPIO_enuPin_7)
	{
		Loc_u8PinNumber = Cpy_enuPinNumber * 4;
		Loc_u32Register = GPIO[Cpy_enuPort]->GPIO_AFRL;
		Loc_u32Register &= ~(GPIO_AF_CLR_MASK << Loc_u8PinNumber);
		Loc_u32Register |= (Cpy_enuAF << Loc_u8PinNumber);
		GPIO[Cpy_enuPort]->GPIO_AFRL = Loc_u32Register;
	}
	else if((Cpy_enuPinNumber >= GPIO_enuPin_8 ) || (Cpy_enuPinNumber <= GPIO_enuPin_15))
	{
		Loc_u8PinNumber = (Cpy_enuPinNumber - 8) * 4;
		Loc_u32Register = GPIO[Cpy_enuPort]->GPIO_AFRH;
		Loc_u32Register &= ~(GPIO_AF_CLR_MASK << Loc_u8PinNumber);
		Loc_u32Register |= (Cpy_enuAF << Loc_u8PinNumber);
		GPIO[Cpy_enuPort]->GPIO_AFRH = Loc_u32Register;
	}
	else
	{
		Loc_enuReturn = GPIO_enuNotOk;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

GPIO_tenuErrorStatus gpio_SetPortValue(GPIO_tenuPort Cpy_enuPort, u16 Cpy_u16PortValue)
{
	GPIO_tenuErrorStatus Loc_enuReturn = GPIO_enuOK;

	GPIO[Cpy_enuPort]->GPIO_ODR = Cpy_u16PortValue;

	return Loc_enuReturn;
}

/***************************************************************************************************/

GPIO_tenuErrorStatus gpio_GetPortValue(GPIO_tenuPort Cpy_enuPort, u16 * Cpy_pu16PortValue)
{
	GPIO_tenuErrorStatus Loc_enuReturn = GPIO_enuOK;

	if(Cpy_pu16PortValue == NULL)
	{
		Loc_enuReturn = GPIO_enuNullPointer;
	}
	else
	{
		*Cpy_pu16PortValue = GPIO[Cpy_enuPort]->GPIO_IDR;
	}

	return Loc_enuReturn;
}
