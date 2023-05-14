/*
 * LCD_Cfg.h
 *
 *  Created on: Mar 24, 2023
 *      Author: lenovo
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "GPIO.h"

/********** configuration  for initialization *************/

 /* LCD_ONE_LINE
 	LCD_TWO_LINES*/
 #define LCD_LINES_NO LCD_TWO_LINES

 /* LCD_FONT_5x8
 	LCD_FONT_5x11 */
 #define LCD_FONT LCD_FONT_5x8

 /* LCD_CURSOR_ENABLE
    LCE_CURSOR_DISABLE */
 #define LCD_CURSOR LCD_CURSOR_ENABLE

 /* LCD_CURSOR_BLINK
 	LCD_CURSOR_UNBLINK */
 #define LCD_CURSOR_BLINK_STATE LCD_CURSOR_BLINK

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef enum
{
	LCD_enuDataPin0 = 0,
	LCD_enuDataPin1 ,
	LCD_enuDataPin2 ,
	LCD_enuDataPin3 ,
	LCD_enuDataPin4 ,
	LCD_enuDataPin5 ,
	LCD_enuDataPin6 ,
	LCD_enuDataPin7 ,
	LCD_enuControlPinRS ,
	LCD_enuControlPinRW ,
	LCD_enuControlPinE ,
	LCD_enuPinNumbers
}LCD_tenuLCDpins;

typedef enum
{
	LCD_enuOneLine = 0,
	LCD_enuTwoLines = 0x08
}LCD_tenuLinesNumber;

typedef enum
{
	LCD_enuFont5x8 = 0,
	LCD_enuFont5x11 = 0x04
}LCD_tenuFontSize;

typedef enum
{
	LCD_enuCursorDisable  = 0,
	LCD_enuCursorEnable = 0x02
}LCD_tenuCursorEnable;


typedef struct
{
	GPIO_tenuPort port;
	GPIO_tenuPinNumber pin;
}LCDcfg_t;

typedef struct
{

}LCDoperations;

extern const LCDcfg_t LCD_LcdCfg[LCD_enuPinNumbers];

#endif /* LCD_CFG_H_ */
