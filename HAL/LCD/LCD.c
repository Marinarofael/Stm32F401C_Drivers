/*
 * LCD.c
 *
 *  Created on: Mar 24, 2023
 *      Author: Marina Wagdy
 */
#include "GPIO.h"
#include "LCD.h"

/********************************************************************************************************/
/********************************************* DEFINES **************************************************/

#define LCD_ONE_LINE 0x00
#define LCD_TWO_LINES 0x08

#define LCD_FONT_5x8 0x00
#define LCD_FONT_5x11 0x04

#define LCD_FUNC_SET_MASK 0x30
#define LCD_COMMAND_FUNCTION_SET ( LCD_FUNC_SET_MASK | LCD_TWO_LINES | LCD_FONT_5x8)

#define LCD_CURSOR_ENABLE 0x02
#define LCD_CURSOR_DISABLE 0x00

#define LCD_CURSOR_BLINK 0x01
#define LCD_CURSOR_UNBLINK 0x00

#define LCD_DISPLAY_MASK 0x0C
#define LCD_COMMAND_DISPLAY ( LCD_DISPLAY_MASK | LCD_CURSOR_BLINK | LCD_CURSOR_ENABLE)

#define LCD_COMMAND_ENTRY_MODE 0x06

#define LCD_BLOCK_SIZE 8
#define LCD_CGRAM_COMMAND_MASK 64
#define LCD_DDRAM_COMMAND_MASK 0x80

#define LCD_COMMAND_CLEAR 0x01

#define LCD_BUFFER_SIZE 1

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef enum
{
	LCD_enuInitFunctionSetStart = 0,
	LCD_enuInitFunctionSetEnd ,
	LCD_enuInitDisplayStart ,
	LCD_enuInitDisplayEnd ,
	LCD_enuInitClearStart ,
	LCD_enuInitClearEnd ,
	LCD_enuInitEntryModeStart ,
	LCD_enuInitEntryModeEnd ,
	LCD_enuInitDone

}LCD_tenuInitSequence;

typedef enum
{
	LCD_enuClearingScreenStart = 0,
	LCD_enuClearingScreenEnd ,
	LCD_enuClearingScreenDone

}LCD_tenuClearingSequence;

typedef enum
{
	LCD_enuPositioningStart = 0,
	LCD_enuPositioningEnd ,
	LCD_enuWritingStart,
	LCD_enuWritingEnd ,
	LCD_enuWritingDone

}LCD_tenuWritingSequence;

typedef struct
{
	u8* String;
	u8 Length;
	lcd_tenuLCDpositionX PositionX;
	lcd_tenuLCDpositionY PositionY;
	u8 CurrentIndex;

}LCD_UserHandler_t;

/***************************************************************************************************/
/****************************************** VARIABLES **********************************************/

static lcd_tenuLCDstate LcdState = LCD_enuNotReady;
static LCD_UserHandler_t LcdWriteStringInfo[LCD_BUFFER_SIZE];
static u8 LcdUsedBuffer = 0;

/***************************************************************************************************/
/******************************* STATIC FUNCTIONS PROTOTYPE ******************************************/

static void InitSequence(void);
static void WriteSequence(void);
static void ClearSequence(void);
static void WriteCommand (u8 Cpy_u8Command);
static void WriteCharacter (u8 Cpy_u8Character);
static void ResetEnablePin(void);

/***************************************************************************************************/
/******************************* FUNCTIONS IMPLEMENTATION ******************************************/

/* implementation of function to initialize LCD pins */
void lcd_Init(void)
{
	u8 Loc_u8Counter = 0;
	gpio_Init_t Loc_gpioCfg;

	for(Loc_u8Counter = 0; Loc_u8Counter < LCD_enuPinNumbers; Loc_u8Counter++)
	{
		Loc_gpioCfg.port = LCD_LcdCfg[Loc_u8Counter].port;
		Loc_gpioCfg.pin = LCD_LcdCfg[Loc_u8Counter].pin;
		Loc_gpioCfg.mode = GPIO_MODE_GP_PUSH_PULL;
		Loc_gpioCfg.speed = GPIO_enuSpeedHigh;

		gpio_InitPin(&Loc_gpioCfg);
	}
	LcdState = LCD_enuNotInit;
}

/***************************************************************************************************/

/* implementation of function to clear screen */
lcd_tenuLCDstate lcd_enuWriteStringAsynch(const char * Cpy_String, u8 Cpy_u8StringLength, lcd_tenuLCDpositionX Cpy_enuLCDpositionX, lcd_tenuLCDpositionY Cpy_enuLCDpositionY)
{
	static u8 NextBuffer = 0;
	lcd_tenuLCDstate Loc_enuReturn ;
	u8 Loc_u8Counter = 0;

	if(Cpy_String == NULL)
	{
		Loc_enuReturn = LCD_enuNotOk;
	}
	else if (Cpy_enuLCDpositionX > LCD_enuMaxPositionX)
	{
		Loc_enuReturn = LCD_enuNotOk;
	}
	else if (Cpy_enuLCDpositionY > LCD_enuMaxPositionY)
	{
		Loc_enuReturn = LCD_enuNotOk;
	}
	else
	{
		if((LcdState == LCD_enuIdle) || ((LcdState == LCD_enuBusyWriting ) && (LcdUsedBuffer < LCD_BUFFER_SIZE)))
		{
			LcdState = LCD_enuBusyWriting;
			LcdWriteStringInfo[NextBuffer].String = Cpy_String;
			/*for(Loc_u8Counter = 0; Loc_u8Counter < Cpy_u8StringLength; Loc_u8Counter++)
			{
				LcdWriteStringInfo[NextBuffer].String[Loc_u8Counter] = Cpy_String[Loc_u8Counter];
			}*/
			LcdWriteStringInfo[NextBuffer].Length = Cpy_u8StringLength;
			LcdWriteStringInfo[NextBuffer].PositionX = Cpy_enuLCDpositionX;
			LcdWriteStringInfo[NextBuffer].PositionY = Cpy_enuLCDpositionY;
			LcdWriteStringInfo[NextBuffer].CurrentIndex = 0;
			LcdUsedBuffer++;
			NextBuffer++;
			if(NextBuffer == LCD_BUFFER_SIZE)
			{
				NextBuffer = 0;
			}
			Loc_enuReturn = LCD_enuOk;
		}
		else
		{
			Loc_enuReturn = LcdState;
		}

	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* implementation of function to clear screen */
lcd_tenuLCDstate lcd_ClearScreen(void)
{
	if(LcdState == LCD_enuIdle)
	{
		LcdState = LCD_enuBusyClearingScreen;
	}

	return LcdState;
}

/***************************************************************************************************/

/* implementation of function to manage LCD tasks */
void lcd_Task(void)
{
	if(LcdState == LCD_enuNotInit)
	{
		InitSequence();
	}
	else if(LcdState == LCD_enuBusyWriting)
	{
		WriteSequence();
	}
	else if(LcdState == LCD_enuBusyClearingScreen)
	{
		ClearSequence();
	}
}

/***********************************************************************************************/
/************************* STATIC FUNCTIONS IMPLEMENTATION *************************************/

/* implementation of function to execute initialize sequence of LCD */
static void InitSequence(void)
{
	static LCD_tenuInitSequence InitSequenceState = LCD_enuInitFunctionSetStart;

	switch(InitSequenceState)
	{
	case LCD_enuInitFunctionSetStart :
		WriteCommand(LCD_COMMAND_FUNCTION_SET);
		InitSequenceState = LCD_enuInitFunctionSetEnd;
		break;

	case LCD_enuInitFunctionSetEnd :
		ResetEnablePin();
		InitSequenceState = LCD_enuInitDisplayStart;
		break;

	case LCD_enuInitDisplayStart :
		WriteCommand(LCD_COMMAND_DISPLAY);
		InitSequenceState = LCD_enuInitDisplayEnd;
		break;

	case LCD_enuInitDisplayEnd :
		ResetEnablePin();
		InitSequenceState = LCD_enuInitClearStart;
		break;

	case LCD_enuInitClearStart :
		WriteCommand(LCD_COMMAND_CLEAR);
		InitSequenceState = LCD_enuInitClearEnd;
		break;

	case LCD_enuInitClearEnd :
		ResetEnablePin();
		InitSequenceState = LCD_enuInitEntryModeStart;
		break;

	case LCD_enuInitEntryModeStart :
		WriteCommand(LCD_COMMAND_ENTRY_MODE);
		InitSequenceState = LCD_enuInitEntryModeEnd;
		break;

	case LCD_enuInitEntryModeEnd :
		ResetEnablePin();
		InitSequenceState = LCD_enuInitDone;
		break;

	case LCD_enuInitDone :
		LcdState = LCD_enuIdle;
		break;
	}
}

/***************************************************************************************************/

/* implementation of function to execute write sequence of LCD */
static void WriteSequence(void)
{
	static LCD_tenuWritingSequence WriteSequenceState = LCD_enuPositioningStart ;
	static u8 CurrentBuffer = 0;
	u8 Loc_u8PositionongCommand = 0;

	switch(WriteSequenceState)
	{
	case LCD_enuPositioningStart :
		Loc_u8PositionongCommand = LcdWriteStringInfo[CurrentBuffer].PositionY + LCD_DDRAM_COMMAND_MASK;
		if(LcdWriteStringInfo[CurrentBuffer].PositionX == LCD_enuPositionX_1)
		{
			Loc_u8PositionongCommand += 0x40;
		}
		WriteCommand(Loc_u8PositionongCommand);
		WriteSequenceState = LCD_enuPositioningEnd;
		break;

	case LCD_enuPositioningEnd :
		ResetEnablePin();
		WriteSequenceState = LCD_enuWritingStart;
		break;

	case LCD_enuWritingStart :
		WriteCharacter(LcdWriteStringInfo[CurrentBuffer].String[LcdWriteStringInfo[CurrentBuffer].CurrentIndex]);
		WriteSequenceState = LCD_enuWritingEnd;
		break;

	case LCD_enuWritingEnd :
		ResetEnablePin();
		LcdWriteStringInfo[CurrentBuffer].CurrentIndex++;
		if(LcdWriteStringInfo[CurrentBuffer].CurrentIndex == LcdWriteStringInfo[CurrentBuffer].Length)
		{
			WriteSequenceState = LCD_enuWritingDone;
		}
		else
		{
			WriteSequenceState = LCD_enuWritingStart;
		}
		break;

	case LCD_enuWritingDone :
		LcdUsedBuffer--;
		WriteSequenceState = LCD_enuPositioningStart;
		if(LcdUsedBuffer == 0)
		{
			LcdState = LCD_enuIdle;
		}
		else
		{
			CurrentBuffer++;
			if(CurrentBuffer == LCD_BUFFER_SIZE)
			{
				CurrentBuffer = 0;
			}
		}
		break;
	}
}

/***************************************************************************************************/

/* implementation of function to execute clear sequence of LCD */
static void ClearSequence(void)
{
	static LCD_tenuClearingSequence ClearSequenceState = LCD_enuClearingScreenStart ;

	switch(ClearSequenceState)
	{
	case LCD_enuClearingScreenStart :
		WriteCommand(LCD_COMMAND_CLEAR);
		ClearSequenceState = LCD_enuClearingScreenEnd;
		break;

	case LCD_enuClearingScreenEnd :
		ResetEnablePin();
		ClearSequenceState = LCD_enuClearingScreenDone;
		break;

	case LCD_enuClearingScreenDone :
		ClearSequenceState = LCD_enuClearingScreenStart ;
		LcdState = LCD_enuIdle;
		break;
	}
}

/***************************************************************************************************/

/* implementation of function to write command to LCD */
void WriteCommand (u8 Cpy_u8Command)
{
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuControlPinRS].port, LCD_LcdCfg[LCD_enuControlPinRS].pin, GPIO_enuValueLow);
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuControlPinRW].port, LCD_LcdCfg[LCD_enuControlPinRW].pin, GPIO_enuValueLow);
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuControlPinE].port, LCD_LcdCfg[LCD_enuControlPinE].pin, GPIO_enuValueLow);

	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin0].port, LCD_LcdCfg[LCD_enuDataPin0].pin, GET_BIT(Cpy_u8Command,LCD_enuDataPin0));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin1].port, LCD_LcdCfg[LCD_enuDataPin1].pin, GET_BIT(Cpy_u8Command,LCD_enuDataPin1));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin2].port, LCD_LcdCfg[LCD_enuDataPin2].pin, GET_BIT(Cpy_u8Command,LCD_enuDataPin2));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin3].port, LCD_LcdCfg[LCD_enuDataPin3].pin, GET_BIT(Cpy_u8Command,LCD_enuDataPin3));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin4].port, LCD_LcdCfg[LCD_enuDataPin4].pin, GET_BIT(Cpy_u8Command,LCD_enuDataPin4));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin5].port, LCD_LcdCfg[LCD_enuDataPin5].pin, GET_BIT(Cpy_u8Command,LCD_enuDataPin5));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin6].port, LCD_LcdCfg[LCD_enuDataPin6].pin, GET_BIT(Cpy_u8Command,LCD_enuDataPin6));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin7].port, LCD_LcdCfg[LCD_enuDataPin7].pin, GET_BIT(Cpy_u8Command,LCD_enuDataPin7));

	gpio_WritePinValue(LCD_LcdCfg[LCD_enuControlPinE].port, LCD_LcdCfg[LCD_enuControlPinE].pin, GPIO_enuValueHigh);

}

/***************************************************************************************************/

/* implementation of function to write character to LCD */
static void WriteCharacter (u8 Cpy_u8Character)
{
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuControlPinRS].port, LCD_LcdCfg[LCD_enuControlPinRS].pin, GPIO_enuValueHigh);
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuControlPinRW].port, LCD_LcdCfg[LCD_enuControlPinRW].pin, GPIO_enuValueLow);
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuControlPinE].port, LCD_LcdCfg[LCD_enuControlPinE].pin, GPIO_enuValueLow);

	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin0].port, LCD_LcdCfg[LCD_enuDataPin0].pin, GET_BIT(Cpy_u8Character,LCD_enuDataPin0));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin1].port, LCD_LcdCfg[LCD_enuDataPin1].pin, GET_BIT(Cpy_u8Character,LCD_enuDataPin1));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin2].port, LCD_LcdCfg[LCD_enuDataPin2].pin, GET_BIT(Cpy_u8Character,LCD_enuDataPin2));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin3].port, LCD_LcdCfg[LCD_enuDataPin3].pin, GET_BIT(Cpy_u8Character,LCD_enuDataPin3));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin4].port, LCD_LcdCfg[LCD_enuDataPin4].pin, GET_BIT(Cpy_u8Character,LCD_enuDataPin4));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin5].port, LCD_LcdCfg[LCD_enuDataPin5].pin, GET_BIT(Cpy_u8Character,LCD_enuDataPin5));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin6].port, LCD_LcdCfg[LCD_enuDataPin6].pin, GET_BIT(Cpy_u8Character,LCD_enuDataPin6));
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuDataPin7].port, LCD_LcdCfg[LCD_enuDataPin7].pin, GET_BIT(Cpy_u8Character,LCD_enuDataPin7));

	gpio_WritePinValue(LCD_LcdCfg[LCD_enuControlPinE].port, LCD_LcdCfg[LCD_enuControlPinE].pin, GPIO_enuValueHigh);

}
/***************************************************************************************************/

/* implementation of function to reset enable pin */
void ResetEnablePin(void)
{
	gpio_WritePinValue(LCD_LcdCfg[LCD_enuControlPinE].port, LCD_LcdCfg[LCD_enuControlPinE].pin, GPIO_enuValueLow);
}
