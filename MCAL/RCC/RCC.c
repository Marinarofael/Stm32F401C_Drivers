/*
 * RCC.c
 *
 *  Created on: Jan 31, 2023
 *      Author: Marina Wagdy
 */

#include "RCC.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

/* base address of RCC peripheral */
#define RCC_BASE 0x40023800

/* for CFGR register */
#define RCC_SWS_MASK 0b1100
#define RCC_SW_MASK 0b11

/*for CR register */
#define RCC_CR_HSION 0
#define RCC_CR_HSIRDY 1
#define RCC_CR_HSEON 16
#define RCC_CR_HSERDY 17
#define RCC_CR_PLLON 24
#define RCC_CR_PLLRDY 25

/* for PLLCFGR register */
#define RCC_PLLCFGR_PLLM 0
#define RCC_PLLCFGR_PLLN 6
#define RCC_PLLCFGR_PLLP 16
#define RCC_PLLCFGR_PLLSRC 22
#define RCC_PLLCFGR_PLLQ 24

/* for AHB1ENR register */
#define RCC_AHB1ENR_GPIOAEN 0
#define RCC_AHB1ENR_GPIOBEN 1
#define RCC_AHB1ENR_GPIOCEN 2
#define RCC_AHB1ENR_GPIODEN 3
#define RCC_AHB1ENR_GPIOEEN 4
#define RCC_AHB1ENR_GPIOHEN 7
#define RCC_AHB1ENR_CRCEN 12
#define RCC_AHB1ENR_DMA1EN 21
#define RCC_AHB1ENR_DMA2EN 22

/* for AHB2ENR register */
#define RCC_AHB2ENR_OTGFSEN 7

/* for APB1ENR register */
#define RCC_APB1ENR_TIM2EN 0
#define RCC_APB1ENR_TIM3EN 1
#define RCC_APB1ENR_TIM4EN 2
#define RCC_APB1ENR_TIM5EN 3
#define RCC_APB1ENR_WWDGEN 11
#define RCC_APB1ENR_SPI2EN 14
#define RCC_APB1ENR_SPI3EN 15
#define RCC_APB1ENR_USART2EN 17
#define RCC_APB1ENR_I2C1EN 21
#define RCC_APB1ENR_I2C2EN 22
#define RCC_APB1ENR_I2C3EN 23
#define RCC_APB1ENR_PWPEN 28

/* for APB2ENR register */
#define RCC_APB2ENR_TIM1EN 0
#define RCC_APB2ENR_USART1EN 4
#define RCC_APB2ENR_USART6EN 5
#define RCC_APB2ENR_ADC1EN 8
#define RCC_APB2ENR_SDIOEN 11
#define RCC_APB2ENR_SPI1EN 12
#define RCC_APB2ENR_SPI4EN 13
#define RCC_APB2ENR_SYSCFGEN 14
#define RCC_APB2ENR_TIM9EN 16
#define RCC_APB2ENR_TIM10EN 17
#define RCC_APB2ENR_TIM11EN 18

/* for prescalers of AHB bus */
#define RCC_PRESCALER_AHB_CLR_MASK 0x000000F0

/* for prescalers of APB1 bus */
#define RCC_PRESCALER_APB1_CLR_MASK 0x00001C00

/* for prescalers of APB2 bus */
#define RCC_PRESCALER_APB2_CLR_MASK 0x0000E000

/* for checking input prescaler */
#define RCC_PRESCALER_CHECK_MASK 0x00000300
#define APB1_PRESCALER 0x0000200
#define APB2_PRESCALER 0x0000300
#define AHB_PRESCALER 0x00000100

/* for time out checking */
#define RCC_TIMEOUT 200

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef struct RCC_Peripheral
{
	u32 RCC_CR ;
	u32 RCC_PLLCFGR ;
	u32 RCC_CFGR ;
	u32 RCC_CIR ;
	u32 RCC_AHB1RSTR ;
	u32 RCC_AHB2RSTR ;
	u32 Reserved_0 ;
	u32 Reserved_1 ;
	u32 RCC_APB1RSTR ;
	u32 RCC_APB2RSTR ;
	u32 Reserved_2 ;
	u32 Reserved_3 ;
	u32 RCC_AHB1ENR ;
	u32 RCC_AHB2ENR ;
	u32 Reserved_4 ;
	u32 Reserved_5 ;
	u32 RCC_APB1ENR ;
	u32 RCC_APB2ENR ;
	u32 Reserved_6 ;
	u32 Reserved_7 ;
	u32 RCC_AHB1LPENR ;
	u32 RCC_AHB2LPENR ;
	u32 Reserved_8 ;
	u32 Reserved_9 ;
	u32 RCC_APB1LPENR ;
	u32 RCC_APB2LPENR ;
	u32 Reserved_10 ;
	u32 Reserved_11 ;
	u32 RCC_BDCR ;
	u32 RCC_CSR ;
	u32 Reserved_12 ;
	u32 Reserved_13 ;
	u32 RCC_SSCGR ;
	u32 RCC_PLLI2SCFGR ;
	u32 Reserved_14 ;
	u32 RCC_DCKCFGR ;

}RCC;

/***************************************************************************************************/
/******************************************* VARIABLES *********************************************/

RCC_tenuPeripherals RCC_arrayPeripheralBits[RCC_enuPeripheralNumber] =
{
		[ RCC_enuPeripheralGPIOA ] = RCC_AHB1ENR_GPIOAEN  ,  [ RCC_enuPeripheralGPIOB ] = RCC_AHB1ENR_GPIOBEN ,
		[ RCC_enuPeripheralGPIOC ] = RCC_AHB1ENR_GPIOCEN  ,  [ RCC_enuPeripheralGPIOD ] = RCC_AHB1ENR_GPIODEN ,
		[ RCC_enuPeripheralGPIOE ] = RCC_AHB1ENR_GPIOEEN  ,  [ RCC_enuPeripheralGPIOH ] = RCC_AHB1ENR_GPIOHEN ,
		[ RCC_enuPeripheralCRC   ] = RCC_AHB1ENR_CRCEN    ,  [ RCC_enuPeripheralDMA1  ] = RCC_AHB1ENR_DMA1EN  ,
		[ RCC_enuPeripheralDMA2  ] = RCC_AHB1ENR_DMA2EN   ,  [ RCC_enuPeripheralOTGFS ] = RCC_AHB2ENR_OTGFSEN ,
		[ RCC_enuPeripheralTIM2  ] = RCC_APB1ENR_TIM2EN   ,  [ RCC_enuPeripheralTIM3  ] = RCC_APB1ENR_TIM3EN  ,
		[ RCC_enuPeripheralTIM4  ] = RCC_APB1ENR_TIM4EN   ,  [ RCC_enuPeripheralTIM5  ] = RCC_APB1ENR_TIM5EN  ,
		[ RCC_enuPeripheralWWDG  ] = RCC_APB1ENR_WWDGEN   ,  [ RCC_enuPeripheralSPI2  ] = RCC_APB1ENR_SPI2EN  ,
		[ RCC_enuPeripheralSPI3  ] = RCC_APB1ENR_SPI3EN   ,  [ RCC_enuPeripheralUSART2] = RCC_APB1ENR_USART2EN,
		[ RCC_enuPeripheralI2C1  ] = RCC_APB1ENR_I2C1EN   ,  [ RCC_enuPeripheralI2C2  ] = RCC_APB1ENR_I2C2EN  ,
		[ RCC_enuPeripheralI2C3  ] = RCC_APB1ENR_I2C3EN   ,  [ RCC_enuPeripheralPWP   ] = RCC_APB1ENR_PWPEN   ,
		[ RCC_enuPeripheralTIM1  ] = RCC_APB2ENR_TIM1EN   ,  [ RCC_enuPeripheralUSART1] = RCC_APB2ENR_USART1EN,
		[ RCC_enuPeripheralUSART6] = RCC_APB2ENR_USART6EN ,  [ RCC_enuPeripheralADC1  ] = RCC_APB2ENR_ADC1EN  ,
		[ RCC_enuPeripheralSDIO  ] = RCC_APB2ENR_SDIOEN   ,  [ RCC_enuPeripheralSPI1  ] = RCC_APB2ENR_SPI1EN  ,
		[ RCC_enuPeripheralSPI4  ] = RCC_APB2ENR_SPI4EN   ,  [ RCC_enuPeripheralSYSCFG] = RCC_APB2ENR_SYSCFGEN,
		[ RCC_enuPeripheralTIM9  ] = RCC_APB2ENR_TIM9EN   ,  [ RCC_enuPeripheralTIM10 ] = RCC_APB2ENR_TIM10EN ,
		[ RCC_enuPeripheralTIM11 ] = RCC_APB2ENR_TIM11EN
};

RCC * RCCptr = (RCC * ) RCC_BASE;

/***************************************************************************************************/
/******************************* STATIC FUNCTION PROTOTYPES ****************************************/

static u8 GetSystemClk (void);

/******************************* FUNCTIONS IMPLEMENTATION ******************************************/

/* implementation of function to get the currently used clock for the system */
RCC_tenuErrorStatus RCC_enuGetSystemClk(RCC_tenuSystemClk * Add_PenuSystemClk)
{
	RCC_tenuErrorStatus Loc_enuReturn = RCC_enuOK;

	if(Add_PenuSystemClk == NULL)
	{
		Loc_enuReturn = Rcc_enuNullPointer;
	}
	else
	{
		* Add_PenuSystemClk = GetSystemClk();
	}

	return Loc_enuReturn ;
}

/***************************************************************************************************/

/* implementation of function to enable peripheral clk */
RCC_tenuErrorStatus RCC_enuEnablePeripheralClk (RCC_tenuPeripherals Cpy_enuPeripheral, RCC_tenuPeripheralStatus Cpy_enuPeripheralStatus)
{
	RCC_tenuErrorStatus Loc_enuReturn = RCC_enuOK;
	if((Cpy_enuPeripheral >= 0) && (Cpy_enuPeripheral <= 8))
	{
		if(Cpy_enuPeripheralStatus == RCC_enuEnable)
		{
			RCCptr->RCC_AHB1ENR |= ( 1 << RCC_arrayPeripheralBits[Cpy_enuPeripheral]);
		}
		else if(Cpy_enuPeripheralStatus == RCC_enuDisable)
		{
			RCCptr->RCC_AHB1ENR &= ~( 1 << RCC_arrayPeripheralBits[Cpy_enuPeripheral]);
		}
	}
	else if(Cpy_enuPeripheral == 9)
	{
		if(Cpy_enuPeripheralStatus == RCC_enuEnable)
		{
			RCCptr->RCC_AHB2ENR |= ( 1 <<  RCC_arrayPeripheralBits[Cpy_enuPeripheral]);
		}
		else if(Cpy_enuPeripheralStatus == RCC_enuDisable)
		{
			RCCptr->RCC_AHB2ENR &= ~( 1 << RCC_arrayPeripheralBits[Cpy_enuPeripheral]);
		}
	}
	else if((Cpy_enuPeripheral >= 10) && (Cpy_enuPeripheral <= 21))
	{
		if(Cpy_enuPeripheralStatus == RCC_enuEnable)
		{
			RCCptr->RCC_APB1ENR |= ( 1 << RCC_arrayPeripheralBits[Cpy_enuPeripheral]);
		}
		else if(Cpy_enuPeripheralStatus == RCC_enuDisable)
		{
			RCCptr->RCC_APB1ENR &= ~( 1 << RCC_arrayPeripheralBits[Cpy_enuPeripheral]);
		}
	}
	else if((Cpy_enuPeripheral >= 22) && (Cpy_enuPeripheral <= 32))
	{
		if(Cpy_enuPeripheralStatus == RCC_enuEnable)
		{
			RCCptr->RCC_APB2ENR |= ( 1 << RCC_arrayPeripheralBits[Cpy_enuPeripheral]);
		}
		else if(Cpy_enuPeripheralStatus == RCC_enuDisable)
		{
			RCCptr->RCC_APB2ENR &= ~( 1 << RCC_arrayPeripheralBits[Cpy_enuPeripheral]);
		}
	}
	else
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to set the prescaler of APB1 bus */
RCC_tenuErrorStatus RCC_enuSetPrescalerAPB1 (u32 Cpy_u8PrescalerAPB1)
{
	RCC_tenuErrorStatus Loc_enuReturn = RCC_enuOK;
	u32 Loc_u32Register = RCCptr->RCC_CFGR;
	u32 Loc_u32CheckInput = Cpy_u8PrescalerAPB1;
	Loc_u32CheckInput &= RCC_PRESCALER_CHECK_MASK;
	if(Loc_u32CheckInput != APB1_PRESCALER)
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else
	{
		Loc_u32Register &= (~RCC_PRESCALER_APB1_CLR_MASK);
		Cpy_u8PrescalerAPB1 &= (~RCC_PRESCALER_CHECK_MASK);
		Loc_u32Register |= Cpy_u8PrescalerAPB1;
		RCCptr->RCC_CFGR = Loc_u32Register;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to set the prescaler of APB2 bus */
RCC_tenuErrorStatus RCC_enuSetPrescalerAPB2 (u32 Cpy_u8PrescalerAPB2)
{
	RCC_tenuErrorStatus Loc_enuReturn = RCC_enuOK;
	u32 Loc_u32Register = RCCptr->RCC_CFGR;
	u32 Loc_u32CheckInput = Cpy_u8PrescalerAPB2;
	Loc_u32CheckInput &= RCC_PRESCALER_CHECK_MASK;
	if(Loc_u32CheckInput != APB2_PRESCALER)
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else
	{
		Loc_u32Register &= (~RCC_PRESCALER_APB2_CLR_MASK);
		Cpy_u8PrescalerAPB2 &= (~RCC_PRESCALER_CHECK_MASK);
		Loc_u32Register |= Cpy_u8PrescalerAPB2;
		RCCptr->RCC_CFGR = Loc_u32Register;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/
RCC_tenuErrorStatus RCC_enuSetPrescalerAHB (u32 Cpy_u8PrescalerAHB)
{
	RCC_tenuErrorStatus Loc_enuReturn = RCC_enuOK;
	u32 Loc_u32Register = RCCptr->RCC_CFGR;
	u32 Loc_u32CheckInput = Cpy_u8PrescalerAHB;
	Loc_u32CheckInput &= RCC_PRESCALER_CHECK_MASK;
	if(Loc_u32CheckInput != AHB_PRESCALER)
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else
	{
		Loc_u32Register &= (~RCC_PRESCALER_AHB_CLR_MASK);
		Cpy_u8PrescalerAHB &= (~RCC_PRESCALER_CHECK_MASK);
		Loc_u32Register |= Cpy_u8PrescalerAHB;
		RCCptr->RCC_CFGR = Loc_u32Register;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to check the clock status if ready of not */
RCC_tenuErrorStatus RCC_enuCheckClkStatus (RCC_tenuSystemClk Cpy_enuSystemClk)
{
	RCC_tenuErrorStatus Loc_enuReturn = RCC_enuNotOk;
	u8 Loc_u8TimeOutCounter = 0;

	switch(Cpy_enuSystemClk)
	{
	case RCC_enuHSIoscillator :
		while((!GET_BIT(RCCptr->RCC_CR, RCC_CR_HSIRDY)) && (Loc_u8TimeOutCounter < RCC_TIMEOUT))
		{
			Loc_u8TimeOutCounter++;
		}
		if(GET_BIT(RCCptr->RCC_CR, RCC_CR_HSIRDY))
			Loc_enuReturn = RCC_enuOK;
		break;

	case RCC_enuHSEoscillator :
		while((!GET_BIT(RCCptr->RCC_CR, RCC_CR_HSERDY)) && (Loc_u8TimeOutCounter < RCC_TIMEOUT))
		{
			Loc_u8TimeOutCounter++;
		}
		if(GET_BIT(RCCptr->RCC_CR, RCC_CR_HSERDY))
			Loc_enuReturn = RCC_enuOK;
		break;

	case RCC_enuPLL :
		while((!GET_BIT(RCCptr->RCC_CR, RCC_CR_PLLRDY)) && (Loc_u8TimeOutCounter < RCC_TIMEOUT))
		{
			Loc_u8TimeOutCounter++;
		}
		if(GET_BIT(RCCptr->RCC_CR, RCC_CR_PLLRDY))
			Loc_enuReturn = RCC_enuOK;
		break;

	default :
		Loc_enuReturn = RCC_enuNotOk ;
	}
	return Loc_enuReturn ;
}

/***************************************************************************************************/

/* implementation of function to enable HSI oscillator */
RCC_tenuErrorStatus RCC_enuEnableHSI(void)
{
	RCCptr->RCC_CR |= ( 1 << RCC_CR_HSION);
	return RCC_enuCheckClkStatus(RCC_enuHSIoscillator);
}

/***************************************************************************************************/

/* implementation of function to disable HSI oscillator */
RCC_tenuErrorStatus RCC_enuDisableHSI(void)
{
	RCC_tenuErrorStatus Loc_enuReturn = RCC_enuNotOk;
	RCC_tenuSystemClk Loc_enuCurrentSource;

	Loc_enuCurrentSource = GetSystemClk();
	if(Loc_enuCurrentSource == RCC_enuHSIoscillator)
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else
	{
		RCCptr->RCC_CR &= ~( 1 << RCC_CR_HSION);
		Loc_enuReturn = RCC_enuOK;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to enable HSE oscillator */
RCC_tenuErrorStatus RCC_enuEnableHSE(void)
{
	RCCptr->RCC_CR |= ( 1 << RCC_CR_HSEON);
	return RCC_enuCheckClkStatus(RCC_enuHSEoscillator);
}

/***************************************************************************************************/

/* implementation of function to disable HSE oscillator */
RCC_tenuErrorStatus RCC_enuDisableHSE(void)
{
	RCC_tenuErrorStatus Loc_enuReturn = RCC_enuNotOk;
	RCC_tenuSystemClk Loc_enuCurrentSource;

	Loc_enuCurrentSource = GetSystemClk();
	if(Loc_enuCurrentSource == RCC_enuHSEoscillator)
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else
	{
		RCCptr->RCC_CR &= ~( 1 << RCC_CR_HSEON);
		Loc_enuReturn = RCC_enuOK;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to enable PLL with given frequency */
RCC_tenuErrorStatus RCC_enuEnablePLL(void)
{
	RCCptr->RCC_CR |= ( 1 << RCC_CR_PLLON);
	return RCC_enuCheckClkStatus(RCC_enuPLL);
}

/***************************************************************************************************/

/* implementation of function to disable PLL oscillator */
RCC_tenuErrorStatus RCC_enuDisablePLL(void)
{
	RCC_tenuErrorStatus Loc_enuReturn = RCC_enuNotOk;
	RCC_tenuSystemClk Loc_enuCurrentSource;

	Loc_enuCurrentSource = GetSystemClk();
	if(Loc_enuCurrentSource == RCC_enuPLL)
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else
	{
		RCCptr->RCC_CR &= ~(1 << RCC_CR_PLLON);
		Loc_enuReturn = RCC_enuOK;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function for configuration of PLL prescalers */
RCC_tenuErrorStatus RCC_enuConfigurationPLL(RCC_tenuSystemClk Cpy_enuPLLsource, u8 Cpy_u8DivFacMainPll_M, u16 Cpy_u16MulFacVCO_N, RCC_tenuValuePLLP Cpy_u8DivFacMainSys_P, u8 Cpy_u8DivFacUSB_Q)
{
	RCC_tenuErrorStatus Loc_enuReturn = RCC_enuNotOk;

	u32 Loc_u8TempRegister = 0;

	if (GET_BIT(RCCptr->RCC_CR, RCC_CR_PLLON))
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else if (!((Cpy_enuPLLsource == RCC_enuHSEoscillator) || (Cpy_enuPLLsource == RCC_enuHSIoscillator)))
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else if ((Cpy_u8DivFacMainPll_M < 2) || (Cpy_u8DivFacMainPll_M > 63))
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else if ((Cpy_u16MulFacVCO_N < 192) || (Cpy_u16MulFacVCO_N > 432))
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else if ((Cpy_u8DivFacMainSys_P < 0) || (Cpy_u8DivFacMainSys_P > 4))
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else if((Cpy_u8DivFacUSB_Q < 2) || (Cpy_u8DivFacUSB_Q > 15))
	{
		Loc_enuReturn = RCC_enuNotOk;
	}
	else
	{
		Loc_u8TempRegister = RCCptr->RCC_PLLCFGR;
		Loc_u8TempRegister |= (Cpy_enuPLLsource << RCC_PLLCFGR_PLLSRC);    // set source of PLL
		Loc_u8TempRegister |= (Cpy_u8DivFacMainPll_M << RCC_PLLCFGR_PLLM); // set division factor M
		Loc_u8TempRegister |= (Cpy_u16MulFacVCO_N << RCC_PLLCFGR_PLLN);    // set multiplication factor N
		Loc_u8TempRegister |= (Cpy_u8DivFacMainSys_P << RCC_PLLCFGR_PLLP); // set division factor P
		Loc_u8TempRegister |= (Cpy_u8DivFacUSB_Q << RCC_PLLCFGR_PLLQ);     // set division factor Q
		RCCptr->RCC_PLLCFGR |= Loc_u8TempRegister;

	}
	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to set the chosen clock for the system */
RCC_tenuErrorStatus RCC_enuSetSystemClk (RCC_tenuSystemClk Cpy_enuSystemClk)
{
	RCC_tenuErrorStatus Loc_enuReturn = RCC_enuNotOk;
	u8 Loc_u8Register = 0;

	Loc_u8Register = RCCptr->RCC_CFGR & (~ RCC_SW_MASK);
	Loc_u8Register |= Cpy_enuSystemClk ;
	RCCptr->RCC_CFGR = Loc_u8Register;

	if(Cpy_enuSystemClk == GetSystemClk())
	{
		Loc_enuReturn = RCC_enuOK;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/
/*************************STATIC FUNCTIONS IMPLEMENTATION ******************************************/

static u8 GetSystemClk (void)
{
	u8 Loc_u8Register;
	Loc_u8Register = RCCptr->RCC_CFGR;
	Loc_u8Register = ((Loc_u8Register & RCC_SWS_MASK) >> 2);
	return Loc_u8Register;
}
