/*
 * RCC.h
 *
 *  Created on: Mar 2, 2023
 *      Author: lenovo
 */

#ifndef NVIC_H_
#define NVIC_H_



/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef enum
{
	NVIC_enuOK = 0,
	NVIC_enuNotOk,
	NVIC_enuNullPointer
}NVIC_tenuErrorStatus;

typedef enum
{
	NVIC_enuPRIGROUP_16Preemption_0Subgroup = 0,
	NVIC_enuPRIGROUP_8Preemption_2Subgroup = 4,
	NVIC_enuPRIGROUP_4Preemption_4Subgroup,
	NVIC_enuPRIGROUP_2Preemption_8Subgroup,
	NVIC_enuPRIGROUP_0Preemption_16Subgroup

}NVIC_PRIGROUP_t;

typedef enum
{
	NVIC_PriorityLevel_0 = 0,
	NVIC_PriorityLevel_1,
	NVIC_PriorityLevel_2,
	NVIC_PriorityLevel_3,
	NVIC_PriorityLevel_4,
	NVIC_PriorityLevel_5,
	NVIC_PriorityLevel_6,
	NVIC_PriorityLevel_7,
	NVIC_PriorityLevel_8,
	NVIC_PriorityLevel_9,
	NVIC_PriorityLevel_10,
	NVIC_PriorityLevel_11,
	NVIC_PriorityLevel_12,
	NVIC_PriorityLevel_13,
	NVIC_PriorityLevel_14,
	NVIC_PriorityLevel_15

}NVIC_PriorityLevel_t;

typedef enum
{
	NVIC_IRQ_WWDG = 0,
	NVIC_IRQ_EXTI16_PVD,
	NVIC_IRQ_EXTI21_TAMP_STAMP,
	NVIC_IRQ_EXTI22_RTC_WKUP,
	NVIC_IRQ_FLASH,
	NVIC_IRQ_RCC,
	NVIC_IRQ_EXTI0,
	NVIC_IRQ_EXTI1,
	NVIC_IRQ_EXTI2,
	NVIC_IRQ_EXTI3,
	NVIC_IRQ_EXTI4,
	NVIC_IRQ_DMA1_Stream0,
	NVIC_IRQ_DMA1_Stream1,
	NVIC_IRQ_DMA1_Stream2,
	NVIC_IRQ_DMA1_Stream3,
	NVIC_IRQ_DMA1_Stream4,
	NVIC_IRQ_DMA1_Stream5,
	NVIC_IRQ_DMA1_Stream6,
	NVIC_IRQ_ADC,
	NVIC_IRQ_EXTI9_5 = 23,
	NVIC_IRQ_TIM1_BRK_TIM9,
	NVIC_IRQ_TIM1_UP_TIM10,
	NVIC_IRQ_TIM1_TRG_COM_TIM11,
	NVIC_IRQ_TIM1_CC,
	NVIC_IRQ_TIM2,
	NVIC_IRQ_TIM3,
	NVIC_IRQ_TIM4,
	NVIC_IRQ_I2C1_EV,
	NVIC_IRQ_I2C1_ER,
	NVIC_IRQ_I2C2_EV,
	NVIC_IRQ_I2C2_ER,
	NVIC_IRQ_SPI1,
	NVIC_IRQ_SPI2,
	NVIC_IRQ_USART1,
	NVIC_IRQ_USART2,
	NVIC_IRQ_EXTI15_10 = 40,
	NVIC_IRQ_EXTI17_RTC_Alarm,
	NVIC_IRQ_EXTI18_OTG_FS_WKUP,
	NVIC_IRQ_DMA1_Stream7 = 47,
	NVIC_IRQ_SDIO = 49,
	NVIC_IRQ_TIM5,
	NVIC_IRQ_SPI3,
	NVIC_IRQ_DMA2_Stream0 = 56,
	NVIC_IRQ_DMA2_Stream1,
	NVIC_IRQ_DMA2_Stream2,
	NVIC_IRQ_DMA2_Stream3,
	NVIC_IRQ_DMA2_Stream4,
	NVIC_IRQ_OTG_FS = 67,
	NVIC_IRQ_DMA2_Stream5,
	NVIC_IRQ_DMA2_Stream6,
	NVIC_IRQ_DMA2_Stream7,
	NVIC_IRQ_USART6,
	NVIC_IRQ_I2C3_EV,
	NVIC_IRQ_I2C3_ER,
	NVIC_IRQ_FPU = 81,
	NVIC_IRQ_SPI4 = 84

}NVIC_IRQ_t;

/***************************************************************************************************/
/************************************** FUNCTIONS APIS *********************************************/

/*****************************************************
 * To enable an interrupt or exception               *
 * input : NVIC_IRQ_t                                *
 * return : Error status                             *
 * ***************************************************/
NVIC_tenuErrorStatus NVIC_EnableIRQ(NVIC_IRQ_t Cpy_IRQ);


/*****************************************************
 * To disable an interrupt or exception              *
 * input : NVIC_IRQ_t                                *
 * return : Error status                             *
 * ***************************************************/
NVIC_tenuErrorStatus NVIC_DisableIRQ(NVIC_IRQ_t Cpy_IRQ);


/*******************************************************
 * To set the pending status of interrupt or exception *
 * input : NVIC_IRQ_t                                  *
 * return : Error status                               *
 * *****************************************************/
NVIC_tenuErrorStatus NVIC_SetPendingIRQ(NVIC_IRQ_t Cpy_IRQ);


/*********************************************************
 * To clear the pending status of interrupt or exception *
 * input : NVIC_IRQ_t                                    *
 * return : Error status                                 *
 * *******************************************************/
NVIC_tenuErrorStatus NVIC_ClearPendingIRQ(NVIC_IRQ_t Cpy_IRQ);


/*******************************************************
 * To get the pending status of interrupt or exception *
 * input : NVIC_IRQ_t                                  *
 *       : pointer to get the pending status           *
 * return : Error status                               *
 * *****************************************************/
NVIC_tenuErrorStatus NVIC_GetPendingIRQ(NVIC_IRQ_t Cpy_IRQ , u8 * Cpy_pu8PendingValue);


/*******************************************************
 * To get the active status of interrupt or exception  *
 * input : NVIC_IRQ_t                                  *
 *       : pointer to get the active status            *
 * return : Error status                               *
 * *****************************************************/
NVIC_tenuErrorStatus NVIC_GetActiveIRQ(NVIC_IRQ_t Cpy_IRQ , u8 * Cpy_pu8ActiveStatus);


/*******************************************************
 * To set the group priority bits                      *
 * input : NVIC_PRIGROUP_t 							   *
 * return : Error status                               *
 * *****************************************************/
NVIC_tenuErrorStatus NVIC_SetGroupPriority(NVIC_PRIGROUP_t Cpy_enuPRIGROUP);


/*******************************************************
 * To set the priority of interrupt or exception       *
 * input : NVIC_IRQ_t 								   *
 *       : NVIC_PriorityLevel_t                        *
 * return : Error status                               *
 * *****************************************************/
NVIC_tenuErrorStatus NVIC_SetPriorityIRQ(NVIC_IRQ_t Cpy_IRQ, NVIC_PriorityLevel_t Cpy_enuPriorityLevel);


/*******************************************************
 * To get the priority of interrupt or exception       *
 * input : NVIC_IRQ_t                                  *
 *       : pointer to get the priority                 *
 * return : Error status                               *
 * *****************************************************/
NVIC_tenuErrorStatus NVIC_GetPriorityIRQ(NVIC_IRQ_t Cpy_IRQ , u8 * Cpy_pu8PendingValue);


/*******************************************************
 * To set software triggered interrupt request         *
 * input : NVIC_IRQ_t 								   *
 * return : Error status                               *
 * *****************************************************/
NVIC_tenuErrorStatus NVIC_SetSWTriggeredIRQ(NVIC_IRQ_t Cpy_IRQ);


/*******************************************************
 * To prevent the activation of all IRQs               *
 * input : void      								   *
 * return : Error status                               *
 * *****************************************************/
NVIC_tenuErrorStatus NVIC_DisableAllIRQs(void);


/*******************************************************
 * To prevent the activation of exceptions except NMI  *
 * input : void                         			   *
 * return : Error status                               *
 * *****************************************************/
NVIC_tenuErrorStatus NVIC_DisableAllExceptions(void);


/********************************************************
 * To define the base priority for exception processing *
 * input : NVIC_PriorityLevel_t      		     	    *
 * return : Error status                                *
 * ******************************************************/
//NVIC_tenuErrorStatus NVIC_DefineBasePriority(NVIC_PriorityLevel_t Cpy_enuPriorityLevel);
#endif /* NVIC_H_ */
