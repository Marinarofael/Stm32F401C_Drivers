/*
 * UART.h
 *
 *  Created on: Mar 29, 2023
 *      Author: lenovo
 */

#ifndef UART_H_
#define UART_H_

#include "Std_types.h"
#include "GPIO.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

/* for baud rate inputs */
#define UART_BAUD_RATE_1200    1200
#define UART_BAUD_RATE_2400    2400
#define UART_BAUD_RATE_9600    9600
#define UART_BAUD_RATE_19200   19200
#define UART_BAUD_RATE_38400   38400
#define UART_BAUD_RATE_57600   57600
#define UART_BAUD_RATE_115200  115200
#define UART_BAUD_RATE_230400  230400
#define UART_BAUD_RATE_460800  460800
#define UART_BAUD_RATE_921600  921600
#define UART_BAUD_RATE_2000000 2000000
#define UART_BAUD_RATE_3000000 3000000

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef void (* CallBackFunction)(void);

typedef enum
{
	UART_enuUART1 = 0,
	UART_enuUART2,
	UART_enuUART6,
	UART_enuNumberOfChannels

}UART_tenuChannel;

typedef enum
{
	UART_enuModeTransmitter = 0x00000008,
	UART_enuModeReceiver    = 0x00000004,
	UART_enuModeTransmitterAndReceiver = 0x0000000C
}UART_tenuMode;

typedef enum
{
	UART_enuEnableLIN = 0x00004000,
	UART_enuDisableLIN = 0x00000000
}UART_tenuLINmode;

typedef enum
{
	UART_enuStopBit_1      = 0x00000000,
	UART_enuStopBit_half   = 0x00001000,
	UART_enuStopBit_2      = 0x00002000,
	UART_enuStopBit_1_half = 0x00003000
}UART_tenuStopBits;

typedef enum
{
	UART_enuDisableParity = 0x00000000,
	UART_enuEvenParity    = 0x00000400,
	UART_enuOddParity     = 0x00000600
}UART_tenuParitySelection;

typedef enum
{
	UART_enuDataBits_8 = 0x00000000,
	UART_enuDataBits_9 = 0x00001000

}UART_tenuWordLength;

typedef enum
{
	UART_enuSampling_16 = 0x00000000 ,
	UART_enuSampling_8  = 0x00008000

}UART_tenuOverSamplingMode;

typedef enum
{
	UART_enuIdleLine			 = 0,
	UART_enuOverrun				,
	UART_enuRXready				,
	UART_enuTransmissionComplete ,
	UART_enuTDRempty			 ,
	UART_enuParityError,
	UART_enuBreakdetection,
	UART_enuNumberOfInterrupts
}UART_tenuinterrupts;

typedef enum
{
	UART_enuLINbreakDetection_10Bits = 0x00000000,
	UART_enuLINbreakDetection_11Bits = 0x00000020
}UART_tenuBreakDetectionBits;

typedef struct
{

	UART_tenuChannel Channel;
	UART_tenuStopBits StopBits;
	UART_tenuParitySelection Parity;
	UART_tenuWordLength WordLength;
	UART_tenuOverSamplingMode OverSamplingMode;
	UART_tenuMode Mode;
	UART_tenuLINmode LINstatus;
	u32 BaudRate;

}UART_Cfg_t;

typedef enum
{
	UART_enuOK = 0 ,
	UART_enuNotOk,
	UART_enuNullPointer

}UART_tenuErrorStatus;


/***************************************************************************************************/
/********************************************** APIS ***********************************************/

/*****************************************
 * To configure UART                     *
 * input : pointer to struct             *
 * return : error status                 *
 *****************************************/
UART_tenuErrorStatus USART_enuInit(UART_Cfg_t * Cpy_pstrUART) ;

/*****************************************
 * To transmit buffer                    *
 * input : UART_tenuChannel              *
 *         pointer to buffer             *
 *         size of buffer                *
 * return : error status                 *
 *****************************************/
UART_tenuErrorStatus USART_enuTransmitBufferZerocpy (UART_tenuChannel Cpy_enuChannel, u8 *Cpy_Buffer , u16 Cpy_BufferSize);

/*****************************************
 * To receive buffer                     *
 * input : UART_tenuChannel              *
 *         pointer to buffer             *
 *         size of buffer                *
 * return : error status                 *
 *****************************************/
UART_tenuErrorStatus USART_enuReciveBuffer (UART_tenuChannel Cpy_enuChannel ,u8 *Cpy_Buffer , u16 Cpy_BufferSize);

/*****************************************
 * To set notification functions         *
 * input : UART_tenuChannel              *
 *         Cpy_enuInterruptSource        *
 *         CallBackFunction              *
 * return : error status                 *
 *****************************************/
UART_tenuErrorStatus USART_enuSetNotificationFunction (UART_tenuChannel Cpy_enuChannel, UART_tenuinterrupts Cpy_enuInterruptSource ,CallBackFunction Cpy_CallBackFunc);

/*****************************************
 * To enable interrupt                   *
 * input : UART_tenuinterrupts           *
 *         UART_tenuChannel              *
 * return : error status                 *
 *****************************************/
UART_tenuErrorStatus USART_enuInterruptEnable(UART_tenuChannel Cpy_enuChannel, UART_tenuinterrupts Cpy_enuInterrupt);

/*****************************************
 * To disable interrupt                  *
 * input : UART_tenuinterrupts           *
 *         UART_tenuChannel              *
 * return : error status                 *
 *****************************************/
UART_tenuErrorStatus USART_enuInterruptDisable(UART_tenuChannel Cpy_enuChannel, UART_tenuinterrupts Cpy_enuInterrupt);

/*****************************************
 * To start LIN break                    *
 * input : UART_tenuBreakDetectionBits   *
 * return : void                         *
 *****************************************/
void USART_enuBreakDetectionLIN(UART_tenuChannel Cpy_enuChannel, UART_tenuBreakDetectionBits Cpy_enuBreakDetectionBits);

#endif /* UART_H_ */
