/*
 * flash.h
 *
 *  Created on: May 5, 2022
 *      Author: ahmed
 */

#ifndef FLASH_H_
#define FLASH_H_


typedef enum
{
	FalshOk,
	FlashNullErr,
	FlashParallelismErr,
	FlashDataErr,
	FlashSectorErr,
	FlashAddressErr,
	FlashOperrationErr,
	FlashBusy,
}FlashErrState_t;

typedef void (*FlashPtrtoFunc)(void);

#define FLASH_SECTOR0						(u32)(0x00000002U)
#define FLASH_SECTOR1						(u32)(0x0000000AU)
#define FLASH_SECTOR2						(u32)(0x00000012U)
#define FLASH_SECTOR3						(u32)(0x0000001AU)
#define FLASH_SECTOR4						(u32)(0x00000022U)
#define FLASH_SECTOR5						(u32)(0x0000002AU)
#define FLASH_MASS_ERASE					(u32)(0x00000004U)


#define PARALLELISM_SIZE_8					(u32)(0x00000001U)
#define PARALLELISM_SIZE_16					(u32)(0x00000101U)
#define PARALLELISM_SIZE_32					(u32)(0x00000201U)
#define PARALLELISM_SIZE_64					(u32)(0x00000301U)


void FlashLock(void);

void FlashUnlock(void);

FlashErrState_t FlashProgram(u32 Copy_u32ParallelismSize, u32 Copy_u32Data, u32 Copy_u32Address);

FlashErrState_t FlashProgramIT(u32 Copy_u32ParallelismSize, u32 Copy_u32Data, u32 Copy_u32Address);

FlashErrState_t FlashErase(u32 Copy_u8SectorNum);

FlashErrState_t FlashEraseIT(u32 Copy_u8SectorNum);

FlashErrState_t FlashCpf(FlashPtrtoFunc Add_ptrCpf);







void FlashMain(void);


#endif /* FLASH_H_ */
