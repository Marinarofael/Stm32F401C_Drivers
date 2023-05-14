/*
 * NVIC.c
 *
 *  Created on: Mar 2, 2023
 *      Author: lenovo
 */
#include "Std_types.h"
#include "NVIC.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

/* Base address of NVIC */
#define NVIC_BASE 0xE000E100

/* for Application Interrupt and Reset Control Register */
#define AIRCR *((volatile u32 *)0xE000ED0C)
#define VECTKEY_WRITE_ACESS 0x5FA
#define VECTKEY_OFFSET 16
#define PRIGROUP_OFFSET 8
#define AIRCR_CLR_MASK 0x0000F8FF

/* offset to registers */
#define NVIC_REGISTER_OFFSET 32
#define NVIC_PRIORITY_INDEX_OFFSET 4
#define NVIC_PRIORITY_BYTE_OFFSET 8
#define NVIC_PRIORITY_IMPLEMENTED_BITS 4


/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef struct
{
	u32 NVIC_ISER[8];
	u32 Reserved_0[24];
	u32 NVIC_ICER[8];
	u32 Reserved_1[24];
	u32 NVIC_ISPR[8];
	u32 Reserved_2[24];
	u32 NVIC_ICPR[8];
	u32 Reserved_3[24];
	u32 NVIC_IABR[8];
	u32 Reserved_4[56];
	u8  NVIC_IPR[240];
	u32 Reserved_5[644];
	u32 NVIC_STIR;

}NVIC;

/***************************************************************************************************/
/******************************************* VARIABLES *********************************************/

NVIC * NVICptr = (NVIC *) NVIC_BASE ;

/***************************************************************************************************/
/******************************* FUNCTIONS IMPLEMENTATION ******************************************/

/* function to enable certain IRQ */
NVIC_tenuErrorStatus NVIC_EnableIRQ(NVIC_IRQ_t Cpy_IRQ)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;
	u8 Loc_u8Index = 0;
	u8 Loc_u8BitNumber = 0;

	Loc_u8Index = Cpy_IRQ / NVIC_REGISTER_OFFSET;
	Loc_u8BitNumber = Cpy_IRQ % NVIC_REGISTER_OFFSET;
	NVICptr->NVIC_ISER[Loc_u8Index] = 1 << Loc_u8BitNumber ;

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to disable certain IRQ */
NVIC_tenuErrorStatus NVIC_DisableIRQ(NVIC_IRQ_t Cpy_IRQ)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;
	u8 Loc_u8Index = 0;
	u8 Loc_u8BitNumber = 0;

	Loc_u8Index = Cpy_IRQ / NVIC_REGISTER_OFFSET;
	Loc_u8BitNumber = Cpy_IRQ % NVIC_REGISTER_OFFSET;
	NVICptr->NVIC_ICER[Loc_u8Index] = 1 << Loc_u8BitNumber ;

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to set pending of certain IRQ */
NVIC_tenuErrorStatus NVIC_SetPendingIRQ(NVIC_IRQ_t Cpy_IRQ)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;
	u8 Loc_u8Index = 0;
	u8 Loc_u8BitNumber = 0;

	Loc_u8Index = Cpy_IRQ / NVIC_REGISTER_OFFSET;
	Loc_u8BitNumber = Cpy_IRQ % NVIC_REGISTER_OFFSET;
	NVICptr->NVIC_ISPR[Loc_u8Index] = 1 << Loc_u8BitNumber ;

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to clear pending of certain IRQ */
NVIC_tenuErrorStatus NVIC_ClearPendingIRQ(NVIC_IRQ_t Cpy_IRQ)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;
	u8 Loc_u8Index = 0;
	u8 Loc_u8BitNumber = 0;

	Loc_u8Index = Cpy_IRQ / NVIC_REGISTER_OFFSET;
	Loc_u8BitNumber = Cpy_IRQ % NVIC_REGISTER_OFFSET;
	NVICptr->NVIC_ICPR[Loc_u8Index] = 1 << Loc_u8BitNumber ;

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to get pending of certain IRQ */
NVIC_tenuErrorStatus NVIC_GetPendingIRQ(NVIC_IRQ_t Cpy_IRQ, u8 * Cpy_pu8PendingValue)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;
	u8 Loc_u8Index = 0;
	u8 Loc_u8BitNumber = 0;

	if(Cpy_pu8PendingValue == NULL)
	{
		 Loc_enuReturn = NVIC_enuNullPointer;
	}
	else
	{
		Loc_u8Index = Cpy_IRQ / NVIC_REGISTER_OFFSET;
		Loc_u8BitNumber = Cpy_IRQ % NVIC_REGISTER_OFFSET;
		*Cpy_pu8PendingValue = (NVICptr->NVIC_ICPR[Loc_u8Index] >> Loc_u8BitNumber) & 0x01 ;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to get active status of certain IRQ */
NVIC_tenuErrorStatus NVIC_GetActiveIRQ(NVIC_IRQ_t Cpy_IRQ, u8 * Cpy_pu8ActiveStatus)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;
	u8 Loc_u8Index = 0;
	u8 Loc_u8BitNumber = 0;

	if(Cpy_pu8ActiveStatus == NULL)
	{
		 Loc_enuReturn = NVIC_enuNullPointer;
	}
	else
	{
		Loc_u8Index = Cpy_IRQ / NVIC_REGISTER_OFFSET;
		Loc_u8BitNumber = Cpy_IRQ % NVIC_REGISTER_OFFSET;
		*Cpy_pu8ActiveStatus = (NVICptr->NVIC_IABR[Loc_u8Index] >> Loc_u8BitNumber) & 0x01 ;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to set the group priority bits */
NVIC_tenuErrorStatus NVIC_SetGroupPriority(NVIC_PRIGROUP_t Cpy_enuPRIGROUP)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;
	u32 Loc_u32Register = 0;

	Loc_u32Register = AIRCR & AIRCR_CLR_MASK;
	Loc_u32Register |= (VECTKEY_WRITE_ACESS << VECTKEY_OFFSET);
	Loc_u32Register |= (Cpy_enuPRIGROUP << PRIGROUP_OFFSET);
	AIRCR = Loc_u32Register;

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to set the priority of interrupt or exception  */
NVIC_tenuErrorStatus NVIC_SetPriorityIRQ(NVIC_IRQ_t Cpy_IRQ, NVIC_PriorityLevel_t Cpy_enuPriorityLevel)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;

	NVICptr->NVIC_IPR[Cpy_IRQ] = Cpy_enuPriorityLevel << NVIC_PRIORITY_IMPLEMENTED_BITS;

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to get the priority of interrupt or exception  */
NVIC_tenuErrorStatus NVIC_GetPriorityIRQ(NVIC_IRQ_t Cpy_IRQ , u8 * Cpy_pu8PendingValue)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;

	if(Cpy_pu8PendingValue == NULL)
	{
		Loc_enuReturn = NVIC_enuNullPointer;
	}
	else
	{
	*Cpy_pu8PendingValue = 	NVICptr->NVIC_IPR[Cpy_IRQ] >> NVIC_PRIORITY_IMPLEMENTED_BITS;
	}

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to set software triggered interrupt request  */
NVIC_tenuErrorStatus NVIC_SetSWTriggeredIRQ(NVIC_IRQ_t Cpy_IRQ)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;

	NVICptr->NVIC_STIR = Cpy_IRQ;

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to prevent the activation of all IRQs  */
NVIC_tenuErrorStatus NVIC_DisableAllIRQs(void)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;

	__asm__("CPSID i");

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to prevent the activation of exceptions except NMI  */
NVIC_tenuErrorStatus NVIC_DisableAllExceptions(void)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;

	__asm__("CPSID f");

	return Loc_enuReturn;
}

/***************************************************************************************************/

/* function to define the base priority for exception processing
NVIC_tenuErrorStatus NVIC_DefineBasePriority(NVIC_PriorityLevel_t Cpy_enuPriorityLevel)
{
	NVIC_tenuErrorStatus Loc_enuReturn = NVIC_enuOK;

	__asm__("MOV R1, #Cpy_enuPriorityLevel");
	__asm__(" MSR BASEPRI, R1");

	return Loc_enuReturn;
}*/
