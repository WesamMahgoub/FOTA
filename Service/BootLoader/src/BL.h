/*
 * BL.h
 *
 *  Created on: Jun 23, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef BL_H_
#define BL_H_


#define SESSION_CONTROL			(0X10)// Ecu will know that we should start flashing
#define DOWNLOAD_REQUEST		(0X34)
#define TRANSFER_DATA			(0X36)
#define TRANSFER_EXIT			(0X37)
#define CHECK_CRC				(0X31)


#define TRUE	1
#define FALSE	0

typedef enum
{
	Bl_Idle,
	Bl_DownloadRequest,
	Bl_TransferData,
	Bl_TransferExit,
	Bl_CheckCRC
}Bl_enuServId_t;

typedef enum
{
	Bl_FlashingState = 0xAAAAAAAA,
	Bl_AppExist = 0x55555555,
	Bl_MarkerIdle
}Bl_enuMarker_t;

typedef struct
{
	u32 size; // size of the app
	pu32 add; // the start add of the app
	void (*entry)(void); // entry point of the app

}AppInfo_t;

void BootLoaderInit(void);
void BootLoaderFlashingSeq(void);
void BootLoaderRxCbf(void);


#endif /* BL_H_ */
