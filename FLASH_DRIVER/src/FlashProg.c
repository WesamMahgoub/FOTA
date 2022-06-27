#include "STD_TYPES.h"
#include "BIT_UTILS.h"
#include "Flash.h"

/*************************** Flash Registers ***************************/
typedef struct
{
	volatile u32 FLASH_ACR;
	volatile u32 FLASH_KEYR;
	volatile u32 FLASH_OPTKEYR;
	volatile u32 FLASH_SR;
	volatile u32 FLASH_CR;
	volatile u32 FLASH_OPTCR;
}Flash_Reg_t;

#define   MY_FLASH      ((volatile Flash_Reg_t*)0x40023C00)

void Flash_vidLock(void)
{
	MY_FLASH -> FLASH_CR |= FLASH_LOCK;
}
void Flash_vidUnLock(void)
{
	if(MY_FLASH -> FLASH_CR & FLASH_LOCK)
	{
		MY_FLASH -> FLASH_KEYR = FLASH_KEY1;
		MY_FLASH -> FLASH_KEYR = FLASH_KEY2;
	}
}
void Flash_MassErase(void)
{
	while(MY_FLASH -> FLASH_SR & FLASH_BUSY);
	MY_FLASH -> FLASH_CR |= FLASH_MEM_ERASE;
	MY_FLASH -> FLASH_CR |= FLASH_START;
	MY_FLASH -> FLASH_CR &=~ (FLASH_MEM_ERASE);
}

Flash_Error_t Flash_PageErase(u32 page_address)
{
	Flash_Error_t Loc_Error_t = Flash_OK;
	if(page_address >= FLASH_START_ADD && page_address < FLASH_END_ADD)
	{
		while(MY_FLASH -> FLASH_SR & FLASH_BUSY);
		MY_FLASH ->FLASH_CR |= FLASH_PER_ERASE;
		MY_FLASH ->FLASH_ACR = page_address;
		MY_FLASH->FLASH_CR|=FLASH_START;
		MY_FLASH->FLASH_CR &=~(FLASH_PER_ERASE);
	}
	else
	{
		Loc_Error_t = Flash_AddressError;
	}
	return Loc_Error_t;
}

void Flash_HalfWord(pu16 Copy_pu16StartAddress, u16 Copy_u16Data)
{
//	MY_FLASH->FLASH_KEYR = FLASH_KEY2;
	MY_FLASH->FLASH_CR &= 0xFFFFFCFF;
	MY_FLASH->FLASH_CR |= 0x100;
	while(MY_FLASH->FLASH_SR & FLASH_BUSY );
	MY_FLASH->FLASH_CR |= FLASH_PROGRAM_EN;
	*(Copy_pu16StartAddress)=Copy_u16Data;
	while(MY_FLASH->FLASH_SR & FLASH_BUSY );
	MY_FLASH->FLASH_SR |=FLASH_EOP;
	MY_FLASH->FLASH_CR &= ~(FLASH_PROGRAM_EN);
}

void Flash_FullWord(pu32 Copy_pu32StartAddress , u32 Copy_u32Data)
{
//	MY_FLASH->FLASH_KEYR = FLASH_KEY2;
	MY_FLASH->FLASH_CR &= 0xFFFFFCFF;
	MY_FLASH->FLASH_CR |= 0x200;
	while(MY_FLASH->FLASH_SR & FLASH_BUSY );
	MY_FLASH->FLASH_CR |= FLASH_PROGRAM_EN;
	*(Copy_pu32StartAddress)=Copy_u32Data;
	while(MY_FLASH->FLASH_SR & FLASH_BUSY );
	MY_FLASH->FLASH_SR |=FLASH_EOP;
	MY_FLASH->FLASH_CR &= ~(FLASH_PROGRAM_EN);
}


