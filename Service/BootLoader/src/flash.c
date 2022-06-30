/*
 * flash.c
 *
 *  Created on: May 5, 2022
 *      Author: ahmed
 */

#include "Std_types.h"
#include "flash.h"

#define FLASH_INTERFACE_BASEADDRESS								0x40023C00

typedef struct
{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 OPTCR;
}Flash_Interface_Reg_t;

#define FLASH_INTERFACE										((Flash_Interface_Reg_t*)(FLASH_INTERFACE_BASEADDRESS))

#define FLASH_LOCK											(u32)(0x80000000U)
#define FLASH_EOP_IT_ENABLE									(u32)(0x01000000U)
#define FLASH_ERASE_START									(u32)(0x00010000U)

//Functions Like Macros For Err Checking

#define PARALLELISM_CHECK(value)							((value & ~PARALLELISM_SIZE_64)!=0)

#define SECTOR_CHECK(value)									( (value != FLASH_SECTOR0) &&\
															  (value != FLASH_SECTOR1) &&\
															  (value != FLASH_SECTOR2) &&\
															  (value != FLASH_SECTOR3) &&\
															  (value != FLASH_SECTOR4) &&\
															  (value != FLASH_SECTOR5) &&\
															  (value != FLASH_MASS_ERASE) )


static FlashPtrtoFunc FlachCallBackFunc = NULL;
void FLASH_IRQHandler(void);
//void FlashInit(void)
//{
//	u32  x = 0x55555555;
//	FLASH_INTERFACE->KEYR = 0x45670123;
//
//	FLASH_INTERFACE->KEYR = 0xCDEF89AB;
//
//	FLASH_INTERFACE->CR &= ~0x300U;
//
//	FLASH_INTERFACE->CR |= 0x200U;
//
//	FLASH_INTERFACE->CR |= 0x28U;
//
//	FLASH_INTERFACE->CR |= 0x2;
//
//	FLASH_INTERFACE->CR |= 0x10000;
//
//	//while(!(FLASH_INTERFACE->SR & 0x80000000));
//
//	FLASH_INTERFACE->CR |= 1;
//
//	*(volatile u32*)0x08020004 = x;
//
//	FLASH_INTERFACE->CR &= ~1U;
//
//
//}

void FlashLock(void)
{
	FLASH_INTERFACE->CR |= FLASH_LOCK;
}

void FlashUnlock(void)
{
	FLASH_INTERFACE->KEYR = 0x45670123;

	FLASH_INTERFACE->KEYR = 0xCDEF89AB;
}

FlashErrState_t FlashProgram(u32 Copy_u32ParallelismSize, u32 Copy_u32Data, u32 Copy_u32Address)
{
	FlashErrState_t Loc_enuErr= FalshOk;
	u16 Loc_u16BusyWait=1000;

	if(PARALLELISM_CHECK(Copy_u32ParallelismSize))
	{
		Loc_enuErr = FlashParallelismErr;
	}
	else if(Copy_u32Address < 0x08000000 || Copy_u32Address > 0x0803FFFF)
	{
		Loc_enuErr = FlashAddressErr;
	}
	else if((FLASH_INTERFACE->SR & 0x00010000) != 0)
	{
		Loc_enuErr = FlashBusy;
	}
	else
	{
		FLASH_INTERFACE->CR |= Copy_u32ParallelismSize;

		*(volatile u32*)Copy_u32Address = Copy_u32Data;

		while(Loc_u16BusyWait>0 && ((FLASH_INTERFACE->SR & 0x00010000) != 0))
		{
			Loc_u16BusyWait--;
		}
		if(Loc_u16BusyWait == 0)
		{
			Loc_enuErr=FlashOperrationErr;
		}
		else
		{
			FLASH_INTERFACE->CR &= ~(1U);
		}
	}

	return Loc_enuErr;
}

FlashErrState_t FlashProgramIT(u32 Copy_u32ParallelismSize, u32 Copy_u32Data, u32 Copy_u32Address)
{
	FlashErrState_t Loc_enuErr = FalshOk;
	if(PARALLELISM_CHECK(Copy_u32ParallelismSize))
	{
		Loc_enuErr = FlashParallelismErr;
	}
	else if(Copy_u32Address < 0x08000000 || Copy_u32Address > 0x0803FFFF)
	{
		Loc_enuErr = FlashAddressErr;
	}
	else if((FLASH_INTERFACE->SR & 0x00010000) != 0)
	{
		Loc_enuErr = FlashBusy;
	}
	else
	{
		FLASH_INTERFACE->CR |= Copy_u32ParallelismSize | FLASH_EOP_IT_ENABLE;

		*(volatile u32*)Copy_u32Address = Copy_u32Data;


	}

	return Loc_enuErr;
}

FlashErrState_t FlashErase(u32 Copy_u8SectorNum)
{
	FlashErrState_t Loc_enuErr = FalshOk;
	u16 Loc_u16BusyWait=1000;

	if(SECTOR_CHECK(Copy_u8SectorNum))
	{
		Loc_enuErr = FlashSectorErr;
	}
	else if((FLASH_INTERFACE->SR & 0x00010000) != 0)
	{
		Loc_enuErr = FlashBusy;
	}
	else
	{
		FLASH_INTERFACE->CR |=Copy_u8SectorNum;
		FLASH_INTERFACE->CR |= FLASH_ERASE_START;

		while(Loc_u16BusyWait>0 && ((FLASH_INTERFACE->SR & 0x00010000) != 0))
		{
			Loc_u16BusyWait--;
		}
		if(Loc_u16BusyWait == 0)
		{
			Loc_enuErr=FlashOperrationErr;
		}

	}
	return Loc_enuErr;
}

FlashErrState_t FlashEraseIT(u32 Copy_u8SectorNum)
{
	FlashErrState_t Loc_enuErr = FalshOk;

	if(SECTOR_CHECK(Copy_u8SectorNum))
	{
		Loc_enuErr = FlashSectorErr;
	}
	else if((FLASH_INTERFACE->SR & 0x00010000) != 0)
	{
		Loc_enuErr = FlashBusy;
	}
	else
	{
		FLASH_INTERFACE->CR |=Copy_u8SectorNum | FLASH_EOP_IT_ENABLE;
		FLASH_INTERFACE->CR |= FLASH_ERASE_START;

	}

	return Loc_enuErr;
}

FlashErrState_t FlashCpf(FlashPtrtoFunc Add_ptrCpf)
{
	FlashErrState_t Loc_enuErr;
	if(Add_ptrCpf == NULL)
	{
		Loc_enuErr = FlashNullErr;
	}
	else
	{
		FlachCallBackFunc = Add_ptrCpf;
	}

	return Loc_enuErr;
}


void FLASH_IRQHandler(void)
{
	if((FLASH_INTERFACE->SR & 0x01U) != 0)
	{
		FLASH_INTERFACE->CR &= ~FLASH_EOP_IT_ENABLE;
		if(FlachCallBackFunc != NULL)
		{
			FlachCallBackFunc();
		}

	}
}
