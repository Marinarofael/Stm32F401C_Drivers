/*
 * UART.c
 *
 *  Created on: Mar 29, 2023
 *      Author: lenovo
 */


#include "UART.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

/* base address of UART instances */
#define UART1_BASE 0x40011000
#define UART2_BASE 0x40004400
#define UART6_BASE 0x40011400

/* pins of UART_CR1*/
#define UART_Enable 0x00002000

/* pins of UART_CR3 */
#define UART_CTSIE 10

/* for Baud Rate */
#define SYSTEM_SPEED 25000000UL
#define UART_DIV_MANTISSA 4

/* pins of UART_SR */
#define UART_PARITY_ERROR_FLAG 0
#define UART_IDLE_LINE_FLAG 4
#define UART_OVERRUN_ERROR_FLAG 3
#define UART_TRANSMISSION_COMPLETE_FLAG 6
#define UART_TX_NOT_EMPTY_FLAG 7
#define UART_RX_NOT_EMPTY_FLAG 5
#define UART_LIN_BREAK_DETECT_FLAG 8

#define UART_CLEAR_MASK 0xFFFF0000

/* for interrupts */
#define UART_TRANSMITTION_COMPLETE_ENABLE 0x00000040
#define UART_TRANSMITTION_COMPLETE_DISABLE 0xFFFFFFBF
#define UART_RX_READY_ENABLE 0x00000020
#define UART_RX_READY_DISABLE 0xFFFFFFDF
#define UART_TX_EMPTY_ENABLE 0x00000080
#define UART_TX_EMPTY_DISABLE 0xFFFFFF7F
#define UART_OVERRUN_ENABLE 0x00000020
#define UART_OVERRUN_DISABLE 0xFFFFFFDF
#define UART_IDLE_LINE_ENABLE 0x00000010
#define UART_IDLE_LINE_DISABLE 0xFFFFFFEF
#define UART_PARITY_ERROR_ENABLE 0x00000100
#define UART_PARITY_ERROR_DISABLE 0xFFFFFEFF
#define UART_BREAK_DETECT_ENABLE 0x00000040
#define UART_BREAK_DETECT_DISABLE 0xFFFFFFBF

/* for lin */
#define UART_CLEAR_STOP_BITS 0xFFFFEFFF
#define

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef struct
{
	u32 USART_SR ;
	u32 USART_DR ;
	u32 USART_BRR ;
	u32 USART_CR1 ;
	u32 USART_CR2 ;
	u32 USART_CR3 ;
	u32 USART_GTPR ;

}UART_t;

typedef enum
{
	UART_enuBusy = 0,
	UART_enuIdle,
	UART_enuNotReady
}UART_tenuUARTstatus;

/***************************************************************************************************/
/******************************************* VARIABLES *********************************************/

UART_t * UART[3] = {
		[UART_enuUART1] = (UART_t *) UART1_BASE,
		[UART_enuUART2] = (UART_t *) UART2_BASE,
		[UART_enuUART6] = (UART_t *) UART6_BASE
};

static u32 UART_EnableInterrupts[UART_enuNumberOfInterrupts] = {
		[UART_enuIdleLine] = UART_IDLE_LINE_ENABLE,
		[UART_enuOverrun] = UART_OVERRUN_ENABLE,
		[UART_enuRXready] = UART_RX_READY_ENABLE,
		[UART_enuTransmissionComplete] = UART_TRANSMITTION_COMPLETE_ENABLE,
		[UART_enuTDRempty] = UART_TX_EMPTY_ENABLE,
		[UART_enuParityError] = UART_PARITY_ERROR_ENABLE,
		[UART_enuBreakdetection] = UART_BREAK_DETECT_ENABLE
};

static u32 UART_DisableInterrupts[UART_enuNumberOfInterrupts] = {
		[UART_enuIdleLine] = UART_IDLE_LINE_DISABLE,
		[UART_enuOverrun] = UART_OVERRUN_DISABLE,
		[UART_enuRXready] = UART_RX_READY_DISABLE,
		[UART_enuTransmissionComplete] = UART_TRANSMITTION_COMPLETE_DISABLE,
		[UART_enuTDRempty] = UART_TX_EMPTY_DISABLE,
		[UART_enuParityError] = UART_PARITY_ERROR_DISABLE,
		[UART_enuBreakdetection] = UART_BREAK_DETECT_DISABLE
};

static UART_tenuUARTstatus UART_TXstatus[UART_enuNumberOfChannels] = {UART_enuNotReady};
static UART_tenuUARTstatus UART_RXstatus[UART_enuNumberOfChannels] = {UART_enuNotReady};
static u8 * UART_TXbuffer[UART_enuNumberOfChannels] = {NULL};
static u16  UART_TXsize[UART_enuNumberOfChannels]   = {0};
static u16  UART_TXindex[UART_enuNumberOfChannels]  = {0};
static u8 * UART_RXbuffer[UART_enuNumberOfChannels] = {NULL};
static u16  UART_RXsize[UART_enuNumberOfChannels]   = {0};
static u16  UART_RXindex[UART_enuNumberOfChannels]  = {0};

static CallBackFunction UARTcallBackFunctions[UART_enuNumberOfChannels][UART_enuNumberOfInterrupts] = {{NULL}};

/***************************************************************************************************/
/************************************* IMPLEMENTATION OF FUNCTIONS *********************************/

/* implementation of function to initialize UART */
UART_tenuErrorStatus USART_enuInit(UART_Cfg_t * Cpy_pstrUART)
{
	UART_tenuErrorStatus Loc_enuReturn = UART_enuNotOk;
	u16 Loc_u16Register = 0;
	f32 Loc_f32Div = 0;
	u8 Loc_u8OverSampling = 0;

	if(Cpy_pstrUART == NULL)
	{
		Loc_enuReturn = UART_enuNullPointer;
	}
	else if(Cpy_pstrUART->Channel >= UART_enuNumberOfChannels)
	{
		Loc_enuReturn = UART_enuNotOk;
	}
	else
	{
		/* UART control register 1 */
		Loc_u16Register = UART[Cpy_pstrUART->Channel]->USART_CR1 & UART_CLEAR_MASK;
		Loc_u16Register |= Cpy_pstrUART->Mode ;
		Loc_u16Register |= Cpy_pstrUART->Parity ;
		Loc_u16Register |= Cpy_pstrUART->WordLength ;
		Loc_u16Register |= Cpy_pstrUART->OverSamplingMode ;
		UART[Cpy_pstrUART->Channel]->USART_CR1 = Loc_u16Register;

		/* UART control register 2 */
		Loc_u16Register = UART[Cpy_pstrUART->Channel]->USART_CR2 & UART_CLEAR_MASK;
		Loc_u16Register |= Cpy_pstrUART->StopBits ;
		Loc_u16Register |= Cpy_pstrUART->LINstatus ;
		UART[Cpy_pstrUART->Channel]->USART_CR2 = Loc_u16Register;

		Loc_u16Register =  UART[Cpy_pstrUART->Channel]->USART_CR3 & 0xFFFFF000 ;
		SET_BIT(Loc_u16Register,3);
		UART[Cpy_pstrUART->Channel]->USART_CR3 = Loc_u16Register;

		/* UART baud Rate */
		Loc_u8OverSampling = (Cpy_pstrUART->OverSamplingMode) >> 15;
		Loc_f32Div = (u32)(8 * (2 - Loc_u8OverSampling) * Cpy_pstrUART->BaudRate);
		Loc_f32Div = SYSTEM_SPEED / Loc_f32Div;
		Loc_u16Register = (u16)Loc_f32Div << UART_DIV_MANTISSA;
		Loc_f32Div = ((Loc_f32Div - (u16)Loc_f32Div) * 8 * (2 - Loc_u8OverSampling ));
		Loc_u16Register |= (u8) Loc_f32Div;
		UART[Cpy_pstrUART->Channel]->USART_BRR = Loc_u16Register;

		/* UART enable */
		UART[Cpy_pstrUART->Channel]->USART_CR1 |= UART_Enable ;

		/* clear status register */
		UART[Cpy_pstrUART->Channel]->USART_SR = 0;

		UART_TXstatus[Cpy_pstrUART->Channel] = UART_enuIdle;
		UART_RXstatus[Cpy_pstrUART->Channel] = UART_enuIdle;
		Loc_enuReturn = UART_enuOK;
	}
	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to transmit buffer */
UART_tenuErrorStatus USART_enuTransmitBufferZerocpy (UART_tenuChannel Cpy_enuChannel, u8 * Cpy_Buffer , u16 Cpy_BufferSize)
{
	UART_tenuErrorStatus Loc_enuReturn = UART_enuNotOk;

	if(Cpy_Buffer == NULL)
	{
		Loc_enuReturn = UART_enuNullPointer;
	}
	else if(Cpy_enuChannel >= UART_enuNumberOfChannels)
	{
		Loc_enuReturn = UART_enuNotOk;
	}
	else
	{
		if(UART_TXstatus[Cpy_enuChannel] == UART_enuIdle)
		{
			UART_TXbuffer[Cpy_enuChannel] = Cpy_Buffer;
			UART_TXsize[Cpy_enuChannel] = Cpy_BufferSize;
			UART_TXindex[Cpy_enuChannel] = 0;
			UART_TXstatus[Cpy_enuChannel] = UART_enuBusy;
			UART[Cpy_enuChannel]->USART_CR1 |= UART_TRANSMITTION_COMPLETE_ENABLE;
			UART[Cpy_enuChannel]->USART_DR = UART_TXbuffer[Cpy_enuChannel][UART_TXindex[Cpy_enuChannel]];
			UART_TXindex[Cpy_enuChannel]++;
			Loc_enuReturn = UART_enuOK;
		}
	}
	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to transmit buffer */
UART_tenuErrorStatus USART_enuReciveBuffer (UART_tenuChannel Cpy_enuChannel, u8 *Cpy_Buffer , u16 Cpy_BufferSize)
{
	UART_tenuErrorStatus Loc_enuReturn = UART_enuNotOk;

	if(Cpy_Buffer == NULL)
	{
		Loc_enuReturn = UART_enuNullPointer;
	}
	else if(Cpy_enuChannel >= UART_enuNumberOfChannels)
	{
		Loc_enuReturn = UART_enuNotOk;
	}
	else
	{
		if(UART_RXstatus[Cpy_enuChannel] == UART_enuIdle)
		{
			UART_RXbuffer[Cpy_enuChannel] = Cpy_Buffer;
			UART_RXsize[Cpy_enuChannel] = Cpy_BufferSize;
			UART_RXindex[Cpy_enuChannel] = 0;
			UART[Cpy_enuChannel]->USART_CR1 |= UART_RX_READY_ENABLE;
			UART_RXstatus[Cpy_enuChannel] = UART_enuBusy;
			Loc_enuReturn = UART_enuOK;
		}
	}
	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to set notification function */
UART_tenuErrorStatus USART_enuSetNotificationFunction (UART_tenuChannel Cpy_enuChannel, UART_tenuinterrupts Cpy_enuInterruptSource ,CallBackFunction Cpy_CallBackFunc)
{
	UART_tenuErrorStatus Loc_enuReturn = UART_enuOK;

	if(Cpy_CallBackFunc == NULL)
	{
		Loc_enuReturn = UART_enuNullPointer;
	}
	else if (Cpy_enuChannel >= UART_enuNumberOfChannels)
	{
		Loc_enuReturn = UART_enuNotOk;
	}
	else if (Cpy_enuInterruptSource >= UART_enuNumberOfInterrupts)
	{
		Loc_enuReturn = UART_enuNotOk;
	}
	else
	{
		UARTcallBackFunctions[Cpy_enuChannel][Cpy_enuInterruptSource] = Cpy_CallBackFunc;
	}
	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to enable interrupt */
UART_tenuErrorStatus USART_enuInterruptEnable(UART_tenuChannel Cpy_enuChannel, UART_tenuinterrupts Cpy_enuInterrupt)
{
	UART_tenuErrorStatus Loc_enuReturn = UART_enuOK;

	if (Cpy_enuChannel >= UART_enuNumberOfChannels)
	{
		Loc_enuReturn = UART_enuNotOk;
	}
	else if(Cpy_enuInterrupt >= UART_enuNumberOfInterrupts)
	{
		Loc_enuReturn = UART_enuNotOk;
	}
	else
	{
		if(Cpy_enuInterrupt == UART_enuBreakdetection)
		{
			UART[Cpy_enuChannel]->USART_CR2 |= UART_EnableInterrupts[Cpy_enuInterrupt];
		}
		else
		{
			UART[Cpy_enuChannel]->USART_CR1 |= UART_EnableInterrupts[Cpy_enuInterrupt];
		}

	}
	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to disable interrupt */
UART_tenuErrorStatus USART_enuInterruptDisable(UART_tenuChannel Cpy_enuChannel, UART_tenuinterrupts Cpy_enuInterrupt)
{
	UART_tenuErrorStatus Loc_enuReturn = UART_enuOK;

	if (Cpy_enuChannel >= UART_enuNumberOfChannels)
	{
		Loc_enuReturn = UART_enuNotOk;
	}
	else if(Cpy_enuInterrupt >= UART_enuNumberOfInterrupts)
	{
		Loc_enuReturn = UART_enuNotOk;
	}
	else
	{
		if(Cpy_enuInterrupt == UART_enuBreakdetection)
		{
			UART[Cpy_enuChannel]->USART_CR2 &= UART_DisableInterrupts[Cpy_enuInterrupt];
		}
		else
		{
			UART[Cpy_enuChannel]->USART_CR1 &= UART_DisableInterrupts[Cpy_enuInterrupt];
		}
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to enable LIN mode */
void USART_enuBreakDetectionLIN(UART_tenuChannel Cpy_enuChannel, UART_tenuBreakDetectionBits Cpy_enuBreakDetectionBits)
{
	UART[Cpy_enuChannel]->USART_CR2 |= Cpy_enuBreakDetectionBits;
	UART[Cpy_enuChannel]->USART_CR2 |= UART_BREAK_DETECT_ENABLE;
}

/***************************************************************************************************/

/* implementation of function handler of UART1 */
void USART1_IRQHandler(void)
{
	if(GET_BIT(UART[UART_enuUART1]->USART_SR,UART_TRANSMISSION_COMPLETE_FLAG) && (UART_TXstatus[UART_enuUART1] == UART_enuBusy ))
	{
		if(UART_TXindex[UART_enuUART1] < UART_TXsize[UART_enuUART1])
		{
			UART[UART_enuUART1]->USART_DR = UART_TXbuffer[UART_enuUART1][UART_TXindex[UART_enuUART1]];
			UART_TXindex[UART_enuUART1]++;
		}
		else
		{
			UART_TXstatus[UART_enuUART1] = UART_enuIdle;
			CLR_BIT((UART[UART_enuUART1])->USART_SR,UART_TRANSMISSION_COMPLETE_FLAG);
			if(UARTcallBackFunctions[UART_enuUART1][UART_enuTransmissionComplete])
			{
				UARTcallBackFunctions[UART_enuUART1][UART_enuTransmissionComplete]();
			}
		}
	}

	if(GET_BIT(UART[UART_enuUART1]->USART_SR,UART_RX_NOT_EMPTY_FLAG) && (UART_RXstatus[UART_enuUART1] == UART_enuBusy))
	{
		UART_RXbuffer[UART_enuUART1][UART_RXindex[UART_enuUART1]] = (u8)UART[UART_enuUART1]->USART_DR;
		UART_RXindex[UART_enuUART1]++;
		if(UART_RXindex[UART_enuUART1] == UART_RXsize[UART_enuUART1])
		{
			UART[UART_enuUART1]->USART_CR1 &= UART_RX_READY_DISABLE;
			CLR_BIT(UART[UART_enuUART1]->USART_SR,UART_RX_NOT_EMPTY_FLAG);
			UART_RXindex[UART_enuUART1] = 0;
			UART_RXstatus[UART_enuUART1] = UART_enuIdle;
			if(UARTcallBackFunctions[UART_enuUART1][UART_enuRXready])
			{
				UARTcallBackFunctions[UART_enuUART1][UART_enuRXready]();
			}
		}
	}

	if(GET_BIT(UART[UART_enuUART1]->USART_SR,UART_LIN_BREAK_DETECT_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART1][UART_enuBreakdetection])
		{
			UARTcallBackFunctions[UART_enuUART1][UART_enuBreakdetection]();
		}
	}

	if(GET_BIT(UART[UART_enuUART1]->USART_SR,UART_TX_NOT_EMPTY_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART1][UART_enuTDRempty])
		{
			UARTcallBackFunctions[UART_enuUART1][UART_enuTDRempty]();
		}
	}

	if(GET_BIT(UART[UART_enuUART1]->USART_SR,UART_OVERRUN_ERROR_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART1][UART_enuOverrun])
		{
			UARTcallBackFunctions[UART_enuUART1][UART_enuOverrun]();
		}
	}

	if(GET_BIT(UART[UART_enuUART1]->USART_SR,UART_IDLE_LINE_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART1][UART_enuIdleLine])
		{
			UARTcallBackFunctions[UART_enuUART1][UART_enuIdleLine]();
		}
	}

	if(GET_BIT(UART[UART_enuUART1]->USART_SR,UART_PARITY_ERROR_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART1][UART_enuParityError])
		{
			UARTcallBackFunctions[UART_enuUART1][UART_enuParityError]();
		}
	}
}

/***************************************************************************************************/

/* implementation of function handler of UART2 */
void USART2_IRQHandler(void)
{
	if(GET_BIT(UART[UART_enuUART2]->USART_SR,UART_TRANSMISSION_COMPLETE_FLAG) && (UART_TXstatus[UART_enuUART2] == UART_enuBusy ))
	{
		if(UART_TXindex[UART_enuUART2] < UART_TXsize[UART_enuUART2])
		{
			UART[UART_enuUART2]->USART_DR = UART_TXbuffer[UART_enuUART2][UART_TXindex[UART_enuUART2]];
			UART_TXindex[UART_enuUART2]++;
		}
		else
		{
			UART_TXstatus[UART_enuUART2] = UART_enuIdle;
			CLR_BIT((UART[UART_enuUART2])->USART_SR,UART_TRANSMISSION_COMPLETE_FLAG);
			if(UARTcallBackFunctions[UART_enuUART2][UART_enuTransmissionComplete])
			{
				UARTcallBackFunctions[UART_enuUART2][UART_enuTransmissionComplete]();
			}
		}
	}

	if(GET_BIT(UART[UART_enuUART2]->USART_SR,UART_RX_NOT_EMPTY_FLAG) && (UART_RXstatus[UART_enuUART2] == UART_enuBusy))
	{
		UART_RXbuffer[UART_enuUART2][UART_RXindex[UART_enuUART2]] = (u8)UART[UART_enuUART2]->USART_DR;
		UART_RXindex[UART_enuUART2]++;
		if(UART_RXindex[UART_enuUART2] == UART_RXsize[UART_enuUART2])
		{
			UART[UART_enuUART2]->USART_CR1 &= UART_RX_READY_DISABLE;
			CLR_BIT(UART[UART_enuUART2]->USART_SR,UART_RX_NOT_EMPTY_FLAG);
			UART_RXindex[UART_enuUART2] = 0;
			UART_RXstatus[UART_enuUART2] = UART_enuIdle;
			if(UARTcallBackFunctions[UART_enuUART2][UART_enuRXready])
			{
				UARTcallBackFunctions[UART_enuUART2][UART_enuRXready]();
			}
		}
	}

	if(GET_BIT(UART[UART_enuUART2]->USART_SR,UART_LIN_BREAK_DETECT_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART2][UART_enuBreakdetection])
		{
			UARTcallBackFunctions[UART_enuUART2][UART_enuBreakdetection]();
		}
	}

	if(GET_BIT(UART[UART_enuUART2]->USART_SR,UART_TX_NOT_EMPTY_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART2][UART_enuTDRempty])
		{
			UARTcallBackFunctions[UART_enuUART2][UART_enuTDRempty]();
		}
	}

	if(GET_BIT(UART[UART_enuUART2]->USART_SR,UART_OVERRUN_ERROR_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART2][UART_enuOverrun])
		{
			UARTcallBackFunctions[UART_enuUART2][UART_enuOverrun]();
		}
	}

	if(GET_BIT(UART[UART_enuUART2]->USART_SR,UART_IDLE_LINE_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART2][UART_enuIdleLine])
		{
			UARTcallBackFunctions[UART_enuUART2][UART_enuIdleLine]();
		}
	}

	if(GET_BIT(UART[UART_enuUART2]->USART_SR,UART_PARITY_ERROR_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART2][UART_enuParityError])
		{
			UARTcallBackFunctions[UART_enuUART2][UART_enuParityError]();
		}
	}
}

/***************************************************************************************************/

/* implementation of function handler of UART6 */
void USART6_IRQHandler(void)
{

	if(GET_BIT((UART[UART_enuUART6])->USART_SR,UART_TRANSMISSION_COMPLETE_FLAG) && (UART_TXstatus[UART_enuUART6] == UART_enuBusy))
	{
		if(UART_TXindex[UART_enuUART6] < UART_TXsize[UART_enuUART6])
		{
			UART[UART_enuUART6]->USART_DR = UART_TXbuffer[UART_enuUART6][UART_TXindex[UART_enuUART6]];
			UART_TXindex[UART_enuUART6]++;
		}
		else
		{
			UART_TXstatus[UART_enuUART6] = UART_enuIdle;
			CLR_BIT((UART[UART_enuUART6])->USART_SR,UART_TRANSMISSION_COMPLETE_FLAG);
			//UART[UART_enuUART6]->USART_CR1 &= UART_TRANSMITTION_COMPLETE_DISABLE;
			if(UARTcallBackFunctions[UART_enuUART6][UART_enuTransmissionComplete])
			{
				UARTcallBackFunctions[UART_enuUART6][UART_enuTransmissionComplete]();
			}
		}
	}

	if(GET_BIT(UART[UART_enuUART6]->USART_SR,UART_RX_NOT_EMPTY_FLAG) && (UART_RXstatus[UART_enuUART6] == UART_enuBusy))
	{
		UART_RXbuffer[UART_enuUART6][UART_RXindex[UART_enuUART6]] = (u8)UART[UART_enuUART6]->USART_DR;
		UART_RXindex[UART_enuUART6]++;
		if(UART_RXindex[UART_enuUART6] == UART_RXsize[UART_enuUART6])
		{
			UART[UART_enuUART6]->USART_CR1 &= UART_RX_READY_DISABLE;
			CLR_BIT(UART[UART_enuUART6]->USART_SR,UART_RX_NOT_EMPTY_FLAG);
			UART_RXindex[UART_enuUART6] = 0;
			UART_RXstatus[UART_enuUART6] = UART_enuIdle;
			if(UARTcallBackFunctions[UART_enuUART6][UART_enuRXready])
			{
				if(*UART_RXbuffer[UART_enuUART6] == 'a')
				{
					UARTcallBackFunctions[UART_enuUART6][UART_enuRXready]();
				}
			}
		}
	}

	if(GET_BIT(UART[UART_enuUART6]->USART_SR,UART_LIN_BREAK_DETECT_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART6][UART_enuBreakdetection])
		{
			UARTcallBackFunctions[UART_enuUART6][UART_enuBreakdetection]();
		}
	}

	if(GET_BIT(UART[UART_enuUART6]->USART_SR,UART_TX_NOT_EMPTY_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART6][UART_enuTDRempty])
		{
			UARTcallBackFunctions[UART_enuUART6][UART_enuTDRempty]();
		}
	}

	if(GET_BIT(UART[UART_enuUART6]->USART_SR,UART_OVERRUN_ERROR_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART6][UART_enuOverrun])
		{
			UARTcallBackFunctions[UART_enuUART6][UART_enuOverrun]();
		}
	}

	if(GET_BIT(UART[UART_enuUART6]->USART_SR,UART_IDLE_LINE_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART6][UART_enuIdleLine])
		{
			UARTcallBackFunctions[UART_enuUART6][UART_enuIdleLine]();
		}
	}

	if(GET_BIT(UART[UART_enuUART6]->USART_SR,UART_PARITY_ERROR_FLAG))
	{
		if(UARTcallBackFunctions[UART_enuUART6][UART_enuParityError])
		{
			UARTcallBackFunctions[UART_enuUART6][UART_enuParityError]();
		}
	}

}
