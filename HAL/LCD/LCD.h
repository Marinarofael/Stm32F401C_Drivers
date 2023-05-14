/*
 * LCD.h
 *
 *  Created on: Mar 24, 2023
 *      Author: lenovo
 */

#ifndef LCD_H_
#define LCD_H_

#include "Std_types.h"
#include "LCD_Cfg.h"

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef enum
{
	LCD_enuNotInit = 0,
	LCD_enuIdle ,
	LCD_enuBusyWriting,
	LCD_enuBusyClearingScreen,
	LCD_enuNotOk,
	LCD_enuOk ,
	LCD_enuNotReady

}lcd_tenuLCDstate;

typedef enum
{
	LCD_enuPositionX_0 = 0,
	LCD_enuPositionX_1 ,
	LCD_enuMaxPositionX

}lcd_tenuLCDpositionX;

typedef enum
{
	LCD_enuPositionY_0  = 0,
	LCD_enuPositionY_1 ,
	LCD_enuPositionY_2 ,
	LCD_enuPositionY_3 ,
	LCD_enuPositionY_4 ,
	LCD_enuPositionY_5 ,
	LCD_enuPositionY_6 ,
	LCD_enuPositionY_7 ,
	LCD_enuPositionY_8 ,
	LCD_enuPositionY_9 ,
	LCD_enuPositionY_10 ,
	LCD_enuPositionY_11 ,
	LCD_enuPositionY_12 ,
	LCD_enuPositionY_13 ,
	LCD_enuPositionY_14 ,
	LCD_enuPositionY_15 ,
	LCD_enuMaxPositionY

}lcd_tenuLCDpositionY;

/***************************************************************************************************/
/********************************************** APIS ***********************************************/

/*****************************************
 * To initialize LCD pins                *
 * input : void                          *
 * return : void                         *
 *****************************************/
void lcd_Init(void);

/*****************************************
 * To handle LCD requests                *
 * input : void                          *
 * return : void                         *
 *****************************************/
void lcd_Task(void);

/*****************************************
 * To clear LCD screen                   *
 * input : void                          *
 * return : LCD status                   *
 *****************************************/
lcd_tenuLCDstate lcd_ClearScreen(void);

/*****************************************
 * To write string on screen             *
 * input : const char *                  *
 *         length of string              *
 *         lcd_tenuLCDpositionX          *
 *         lcd_tenuLCDpositionY          *
 * return : LCD status                   *
 *****************************************/
lcd_tenuLCDstate lcd_enuWriteStringAsynch(const char * Cpy_String, u8 Cpy_u8StringLength, lcd_tenuLCDpositionX Cpy_enuLCDpositionX, lcd_tenuLCDpositionY Cpy_enuLCDpositionY);

#endif /* LCD_H_ */
