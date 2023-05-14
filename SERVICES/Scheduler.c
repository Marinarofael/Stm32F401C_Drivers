/*
 * Scheduler.c
 *
 *  Created on: Mar 18, 2023
 *      Author: Marina Wagdy
 */
#include "Std_types.h"
#include "TaskManger_Cfg.h"
#include "Systick.h"
#include "RCC.h"
#include "GPIO.h"
#include "LED.h"
#include "NVIC.h"
#include "UART.h"
//#include "Switch.h"
#include "LCD.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

#define SCHEDULER_TICK 2
#define FLAG_ENABLED 1
#define FLAG_DISABLED 0

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef struct
{
	TaskInfo_t * TaskInfo;
	u32 TaskRemainTimems;
}Task_t;


/***************************************************************************************************/
/******************************************* VARIABLES *********************************************/

static u8 SchedFlag = FLAG_DISABLED;
static Task_t Sched_TaskArr[Task_enuMaxNumber] = {{NULL}};
extern const TaskInfo_t Sched_TaskInfoArr[Task_enuMaxNumber];

/***************************************************************************************************/
/******************************* STATIC FUNCTION PROTOTYPES ****************************************/

static void Scheduler(void);
static void TickCBF(void);
static void AppInit(void);

/***************************************************************************************************/
/************************************* IMPLEMENTATION OF FUNCTIONS *********************************/

/* implementation of scheduler initialization function */
void Sched_init(void)
{
	u8 Loc_u8Index = 0;

	AppInit();
	STK_EnableException();
	STK_SetCbf(TickCBF);
	STK_SetCountTime(STK_enuClkSourceAHBdivideBy8);
	STK_SetPeriodTimeMilliSec(SCHEDULER_TICK);

	for(Loc_u8Index = 0; Loc_u8Index < Task_enuMaxNumber; Loc_u8Index++)
	{
		if(Sched_TaskArr[Loc_u8Index].TaskInfo == NULL)
		{
			Sched_TaskArr[Loc_u8Index].TaskInfo = &Sched_TaskInfoArr[Loc_u8Index];
			Sched_TaskArr[Loc_u8Index].TaskRemainTimems = Sched_TaskInfoArr[Loc_u8Index].TaskStartDelay;
		}
	}
}

/***************************************************************************************************/

/* implementation of scheduler start function */
void Sched_start(void)
{
	STK_Start();
	while(1)
	{
		if(SchedFlag == FLAG_ENABLED)
		{
			Scheduler();
			SchedFlag = FLAG_DISABLED;
		}
	}
}


/***************************************************************************************************/
/*************************STATIC FUNCTIONS IMPLEMENTATION ******************************************/

/* implementation of scheduler function */
static void Scheduler(void)
{
	u8 Loc_u8Index = 0;

	for(Loc_u8Index = 0; Loc_u8Index < Task_enuMaxNumber; Loc_u8Index++)
	{
		if(Sched_TaskArr[Loc_u8Index].TaskInfo)
		{
			if(Sched_TaskArr[Loc_u8Index].TaskRemainTimems == 0)
			{
				Sched_TaskArr[Loc_u8Index].TaskInfo->TaskCbf();
				Sched_TaskArr[Loc_u8Index].TaskRemainTimems = Sched_TaskArr[Loc_u8Index].TaskInfo->TaskPeriodms;
			}
			Sched_TaskArr[Loc_u8Index].TaskRemainTimems -= SCHEDULER_TICK;
		}
	}
}

/***************************************************************************************************/

/* implementation of systick call back function */
static void TickCBF(void)
{
	if(SchedFlag == FLAG_DISABLED)
	{
		SchedFlag = FLAG_ENABLED;
	}
	else
	{
		// CPU overload exceeds 100%
	}
}

/***************************************************************************************************/

/* implementation of applications initialize function */
static void AppInit(void)
{
	gpio_Init_t gpio_object = {
			.port = GPIO_enuPortGPIOA,
			.pin = GPIO_enuPin_9,
			.mode = GPIO_MODE_AF_PUSH_PULL,
			.speed = GPIO_enuSpeedVeryHigh
		};
	UART_Cfg_t uartObject = {
			.Channel = UART_enuUART1,
			.StopBits = UART_enuStopBit_1,
			.Parity = UART_enuDisableParity,
			.WordLength = UART_enuDataBits_8,
			.OverSamplingMode = UART_enuSampling_8,
			.Mode = UART_enuModeTransmitter,
			.BaudRate = UART_BAUD_RATE_9600
		};
	RCC_enuEnableHSE();
	RCC_enuSetSystemClk(RCC_enuHSEoscillator);
	RCC_enuEnablePeripheralClk(RCC_enuPeripheralGPIOA,RCC_enuEnable);
	//RCC_enuEnablePeripheralClk(RCC_enuPeripheralGPIOA,RCC_enuEnable);
	//RCC_enuEnablePeripheralClk(RCC_enuPeripheralGPIOB,RCC_enuEnable);
	//RCC_enuEnablePeripheralClk(RCC_enuPeripheralGPIOC,RCC_enuEnable);
	led_Init();
	//switch_Init();
	//lcd_Init();
	RCC_enuEnablePeripheralClk(RCC_enuPeripheralUSART1,RCC_enuEnable);
	RCC_enuEnablePeripheralClk(RCC_enuPeripheralUSART6,RCC_enuEnable);

	gpio_SelectAF(GPIO_enuPortGPIOA,GPIO_enuPin_9,GPIO_enuAF7);
	gpio_SelectAF(GPIO_enuPortGPIOA,GPIO_enuPin_10,GPIO_enuAF7);
	gpio_SelectAF(GPIO_enuPortGPIOA,GPIO_enuPin_11,GPIO_enuAF8);
	gpio_SelectAF(GPIO_enuPortGPIOA,GPIO_enuPin_12,GPIO_enuAF8);
	NVIC_EnableIRQ(NVIC_IRQ_USART1);
	NVIC_EnableIRQ(NVIC_IRQ_USART6);
	gpio_InitPin(&gpio_object);
	gpio_object.pin = GPIO_enuPin_11;
	gpio_object.mode = GPIO_MODE_INPUT_FLOATING;
	gpio_InitPin(&gpio_object);
//	gpio_object.pin = GPIO_enuPin_10;
//	gpio_InitPin(&gpio_object);
//	gpio_object.pin = GPIO_enuPin_12;
//	gpio_InitPin(&gpio_object);
	USART_enuInit(&uartObject);
	uartObject.Channel = UART_enuUART6;
	uartObject.Mode = UART_enuModeReceiver;
	USART_enuInit(&uartObject);
}
