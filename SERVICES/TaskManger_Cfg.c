/*
 * TaskManger_Cfg.c
 *
 *  Created on: Mar 18, 2023
 *      Author: Marina Wagdy
 */
#include "Std_types.h"
#include "TaskManger_Cfg.h"
#include "Systick.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

#define TASK_PRIORITY_0 0
#define TASK_PRIORITY_1 1
#define TASK_PRIORITY_2 2
#define TASK_PRIORITY_3 3
#define TASK_PRIORITY_4 4

//extern void TASK_Led1App(void);
//extern void TASK_Led2App(void);
extern void TASK_Led3App(void);
extern void TASK_UartApp(void);
//extern void TASK_Led4App(void);
//extern void TASK_SwitchService(void);
//extern void Task_LcdApp(void);
//extern void lcd_Task(void);

/***************************************************************************************************/
/******************************************* VARIABLES *********************************************/

const TaskInfo_t Sched_TaskInfoArr[Task_enuMaxNumber] =
{
	[TASK_PRIORITY_0] = {
			.TaskName = Task_enuApp1,
			.TaskCbf = TASK_UartApp,
			.TaskPeriodms = 1000,
			.TaskStartDelay = 0
	},

	[TASK_PRIORITY_1] = {
			.TaskName = Task_enuApp2,
			.TaskCbf = TASK_Led3App,
			.TaskPeriodms = 1000,
			.TaskStartDelay = 0
	},

/*	[TASK_PRIORITY_2] = {
			.TaskName = Task_enuApp3,
			.TaskCbf = TASK_Led3App,
			.TaskPeriodms = 500,
			.TaskStartDelay = 1000
	},

	[TASK_PRIORITY_3] = {
			.TaskName = Task_enuApp4,
			.TaskCbf = TASK_Led4App,
			.TaskPeriodms = 20,
			.TaskStartDelay = 0
	},

	[TASK_PRIORITY_4] = {
			.TaskName = Task_enuService,
			.TaskCbf = TASK_SwitchService,
			.TaskPeriodms = 5,
			.TaskStartDelay = 0
	},
	[TASK_PRIORITY_0] = {
			.TaskName = Task_enuLcdService,
			.TaskCbf = lcd_Task,
			.TaskPeriodms = 2,
			.TaskStartDelay = 50
	},
	[TASK_PRIORITY_1] = {
			.TaskName = Task_enuLcdApp,
			.TaskCbf = Task_LcdApp,
			.TaskPeriodms = 1000,
			.TaskStartDelay = 1000
	}*/
};

