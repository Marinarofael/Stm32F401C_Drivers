/*
 * GPIO.h
 *
 *  Created on: Feb 15, 2023
 *      Author: lenovo
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "Std_types.h"
#include "Bit_math.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

/* for modes of pins */
#define GPIO_MODE_INPUT_FLOATING          0b00000
#define GPIO_MODE_INPUT_PULL_UP           0b01000
#define GPIO_MODE_INPUT_PULL_DOWN         0b10000
#define GPIO_MODE_GP_OPEN_DRAIN           0b00101
#define GPIO_MODE_GP_OPEN_DRAIN_PULL_UP   0b01101
#define GPIO_MODE_GP_OPEN_DRAIN_PULL_DOWN 0b10101
#define GPIO_MODE_GP_PUSH_PULL            0b00001
#define GPIO_MODE_GP_PUSH_PULL_PULL_UP    0b01001
#define GPIO_MODE_GP_PUSH_PULL_PULL_DOWN  0b10001
#define GPIO_MODE_AF_OPEN_DRAIN           0b00110
#define GPIO_MODE_AF_OPEN_DRAIN_PULL_UP   0b01110
#define GPIO_MODE_AF_OPEN_DRAIN_PULL_DOWN 0b10110
#define GPIO_MODE_AF_PUSH_PULL            0b00010
#define GPIO_MODE_AF_PUSH_PULL_PULL_UP    0b01010
#define GPIO_MODE_AF_PUSH_PULL_PULL_DOWN  0b10010
#define GPIO_MODE_ANALOG                  0b00011

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef enum
{
	GPIO_enuOK = 0 ,
	GPIO_enuNotOk,
	GPIO_enuNullPointer

}GPIO_tenuErrorStatus;

typedef enum {

	GPIO_enuPortGPIOA = 0 ,
	GPIO_enuPortGPIOB ,
	GPIO_enuPortGPIOC ,
	GPIO_enuPortGPIOD ,
	GPIO_enuPortGPIOE ,
	GPIO_enuPortGPIOH

}GPIO_tenuPort;

typedef enum
{
	GPIO_enuPin_0 = 0 ,
	GPIO_enuPin_1 ,
	GPIO_enuPin_2 ,
	GPIO_enuPin_3 ,
	GPIO_enuPin_4 ,
	GPIO_enuPin_5 ,
	GPIO_enuPin_6 ,
	GPIO_enuPin_7 ,
	GPIO_enuPin_8 ,
	GPIO_enuPin_9 ,
	GPIO_enuPin_10 ,
	GPIO_enuPin_11 ,
	GPIO_enuPin_12 ,
	GPIO_enuPin_13 ,
	GPIO_enuPin_14 ,
	GPIO_enuPin_15

}GPIO_tenuPinNumber;

typedef enum
{
	GPIO_enuValueLow = 0 ,
	GPIO_enuValueHigh

}GPIO_tenuPinValue;

typedef enum
{
	GPIO_enuAF0 = 0 ,
	GPIO_enuAF1 ,
	GPIO_enuAF2 ,
	GPIO_enuAF3 ,
	GPIO_enuAF4 ,
	GPIO_enuAF5 ,
	GPIO_enuAF6 ,
	GPIO_enuAF7 ,
	GPIO_enuAF8 ,
	GPIO_enuAF9 ,
	GPIO_enuAF10 ,
	GPIO_enuAF11 ,
	GPIO_enuAF12 ,
	GPIO_enuAF13 ,
	GPIO_enuAF14 ,
	GPIO_enuAF15 ,
	GPIO_enuAF16


}GPIO_tenuAlternatFunction;

typedef enum
{
	GPIO_enuSpeedLow = 0 ,
	GPIO_enuSpeedMedium ,
	GPIO_enuSpeedHigh ,
	GPIO_enuSpeedVeryHigh

}GPIO_tenuPinSpeed;

typedef struct
{
	GPIO_tenuPort port;
	GPIO_tenuPinNumber pin;
	GPIO_tenuPinSpeed speed;
	u8 mode;

}gpio_Init_t;

/***************************************************************************************************/
/********************************************** APIS ***********************************************/

/*****************************************
 * To configure a GPIO pin direction     *
 * input : pointer to struct             *
 * return : error status                 *
 *****************************************/
GPIO_tenuErrorStatus gpio_InitPin(gpio_Init_t * Cpy_strPin);


/*************************************************************************************************************
 * To configure a GPIO pin value                                                                             *
 * input : port (GPIO_enuGPIOA/ GPIO_enuGPIOB/ GPIO_enuGPIOC/ GPIO_enuGPIOD/ GPIO_enuGPIOE/ GPIO_enuGPIOH)   *
 *         pin number ( GPIO_enuPin_X where X from 0 to 15)                                                  *
 *         pin value ( GPIO_enuPinLow / GPIO_enuPinHigh)                                                     *
 * return : error status                                                                                     *
 *************************************************************************************************************/
GPIO_tenuErrorStatus gpio_WritePinValue(GPIO_tenuPort Cpy_enuPort, GPIO_tenuPinNumber Cpy_enuPinNumber, GPIO_tenuPinValue Cpy_enuPinValue );


/*************************************************************************************************************
 * To get a GPIO pin value                                                                                   *
 * input : port (GPIO_enuGPIOA/ GPIO_enuGPIOB/ GPIO_enuGPIOC/ GPIO_enuGPIOD/ GPIO_enuGPIOE/ GPIO_enuGPIOH)   *
 *         pin number ( GPIO_enuPin_X where X from 0 to 15)                                                  *
 *         pointer to variable to get the pin value in it                                                    *
 * return : error status                                                                                     *
 *************************************************************************************************************/
GPIO_tenuErrorStatus gpio_GetPinValue(GPIO_tenuPort Cpy_enuPort, GPIO_tenuPinNumber Cpy_enuPinNumber, GPIO_tenuPinValue *Cpy_enuPinValue );


/*************************************************************************************************************
 * To select alternate function                                                                              *
 * input : port (GPIO_enuGPIOA/ GPIO_enuGPIOB/ GPIO_enuGPIOC/ GPIO_enuGPIOD/ GPIO_enuGPIOE/ GPIO_enuGPIOH)   *
 *         pin number ( GPIO_enuPin_X where X from 0 to 15)                                                  *
 *         alternate function                                                      *
 * return : error status                                                                                     *
 *************************************************************************************************************/
GPIO_tenuErrorStatus gpio_SelectAF(GPIO_tenuPort Cpy_enuPort, GPIO_tenuPinNumber Cpy_enuPinNumber, GPIO_tenuAlternatFunction Cpy_enuAF );


/*************************************************************************************************************
 * To configure a GPIO port value                                                                            *
 * input : port (GPIO_enuGPIOA/ GPIO_enuGPIOB/ GPIO_enuGPIOC/ GPIO_enuGPIOD/ GPIO_enuGPIOE/ GPIO_enuGPIOH)   *
 *         port value (according to user's application)                                                      *
 * return : error status                                                                                     *
 *************************************************************************************************************/
GPIO_tenuErrorStatus gpio_SetPortValue(GPIO_tenuPort Cpy_enuPort, u16 Cpy_u16PortValue);


/*************************************************************************************************************
 * To get a GPIO port value                                                                                  *
 * input : port (GPIO_enuGPIOA/ GPIO_enuGPIOB/ GPIO_enuGPIOC/ GPIO_enuGPIOD/ GPIO_enuGPIOE/ GPIO_enuGPIOH)   *
 *         pointer to get the port value                                                                     *
 * return : error status                                                                                     *
 *************************************************************************************************************/
GPIO_tenuErrorStatus gpio_GetPortValue(GPIO_tenuPort Cpy_enuPort, u16 * Cpy_pu16PortValue);


/*************************************************************************************************************
 * To configure a GPIO pins value                                                                            *
 * input : port (GPIO_enuGPIOA/ GPIO_enuGPIOB/ GPIO_enuGPIOC/ GPIO_enuGPIOD/ GPIO_enuGPIOE/ GPIO_enuGPIOH)   *
 *         array of pin values ( GPIO_enuPinLow / GPIO_enuPinHigh)                                           *
 * return : error status                                                                                     *
 *************************************************************************************************************/
GPIO_tenuErrorStatus gpio_SetPinsValue(GPIO_tenuPort Cpy_enuPort, GPIO_tenuPinValue Cpy_enuarrayValues[16]);
#endif /* GPIO_H_ */
