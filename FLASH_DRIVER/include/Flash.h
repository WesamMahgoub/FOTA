#ifndef FLASH_H_
#define FLASH_H_

/************************* Types Declaration *************************/

typedef enum
{
	Flash_OK,
	Flash_AddressError,
	Flash_NullPointerError,
	Flah_NOK
}Flash_Error_t;

/************************* Macros *************************/
#define LOCKED	    						(u8)1
#define UNLOCKED							(u8)0


/************************* Mask for Flash Erase Value *************************/
#define FLASH_ERASE_VALUE					(u32)0XFFFFFFFF


/************************* FLASH KEY MASK *************************/
#define FLASH_KEY1							(u32)0X45670123
#define FLASH_KEY2							(u32)0XCDEF89AB


/************************* FLASH OPTION KEY MASK *************************/
#define FLASH_OPTKEY1						(u32)0X08192A3B
#define FLASH_OPTKEY2						(u32)0X4C5D6E7F


/************************* FLASH STATUS MASK *************************/
#define FLASH_EOP							(u32)0X00000001
#define FLASH_BUSY							(u32)0X00010000
#define FLASH_PRG_ERROR      			    (u32)0X00000020
#define FLASH_WR_ERROR      			    (u32)0x00000010


/************************* FLASH CONTROL REGISTER MASK *************************/
#define 		FLASH_START                 (u32)0X00010000
#define 		FLASH_LOCK                  (u32)0X80000000
#define 		FLASH_PROGRAM_EN            (u32)0X00000001
#define 		FLASH_MEM_ERASE				(u32)0X00000004
#define 		FLASH_PER_ERASE				(u32)0X00000002


/************************* MEMORY BOUNDARIES ADDRESS MASKS *************************/
#define 		FLASH_START_ADD              (u32)0X08000000
#define 		FLASH_END_ADD                (u32)0X08010000
#define 		RAM_START_ADD                (u32)0X20000000
#define 		RAM_END_ADD                  (u32)0X20005000


/************************* FUNCTIONS PROTOTYPES *************************/
void Flash_vidLock(void);
void Flash_vidUnLock(void);
void Flash_MassErase(void);

Flash_Error_t Flash_PageErase(u32 page_address);

void Flash_HalfWord(pu16 Copy_pu16StartAddress, u16 Copy_u16Data);

void Flash_FullWord(pu32 Copy_pu32StartAddress , u32 Copy_u32Data);

 #endif
