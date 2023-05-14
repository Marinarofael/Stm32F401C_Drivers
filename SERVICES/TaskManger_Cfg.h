/*
 * TaskManger_Cfg.h
 *
 *  Created on: Mar 19, 2023
 *      Author: Marina Wagdy
 */

#ifndef TASKMANGER_CFG_H_
#define TASKMANGER_CFG_H_

#include "Std_types.h"

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef void (* Task_CBF) (void);

typedef enum
{
	Task_enuApp1 = 0,
	Task_enuApp2 ,
	//Task_enuApp3 ,
	//Task_enuApp4 ,
	//Task_enuService,
	//Task_enuLcdService,
	//Task_enuLcdApp,
	Task_enuMaxNumber

}Shed_tenuTask;

typedef struct
{
	Shed_tenuTask TaskName;
	Task_CBF TaskCbf;
	u32 TaskPeriodms;
	u32 TaskStartDelay;
}TaskInfo_t;




#endif /* TASKMANGER_CFG_H_ */
