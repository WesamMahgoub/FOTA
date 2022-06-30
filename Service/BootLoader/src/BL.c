/*
 * BL.c
 *
 *  Created on: Jun 23, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "Bit_utils.h"
#include "BL.h"
#include "Rcc.h"
#include "Gpio.h"
#include "NVIC.h"
#include "Uart.h"
#include "UsartHal.h"
#include "flash.h"

/*flag to call Rx func only once*/
static u8 Loc_u8State = 0;
/*Enum consists of flashing seq*/
static Bl_enuServId_t ServId = Bl_Idle;

volatile Bl_enuMarker_t* const MarkerState=(volatile Bl_enuMarker_t* const)0x08008000;
/*Struct have members of the app info such as
 * 1-Size
 * 2-Add
 * 3-Entry point
 * 4-Crc
 * */
volatile AppInfo_t* const  AppInfo=(volatile AppInfo_t* const) 0x08004000;

/*Buffer, first byte containing seqId "0x34" and the other is for data*/
u8 Bl_u8AppBuff[1025];
/*Flag which will be set from the CBF of the Usart_Rx */
u8 Bl_u8ReqRecieved=FALSE;
//pu8 Uart_firstByte;

u8 Bl_u8gState ;

u32 Bl_u32gSizeCounter;

u8 Bl_u8CrcResult;
u32 Bl_u32FirstAppAdd;
static void Bl_vidSendPosRes(void);
static void Bl_vidSendNegRes(void);
static u8 Bl_u8calc_crc(unsigned char *data, unsigned len);

void BootLoaderInit(void)
{
	Usart_vidHalInit();
	Usart_enuRegRxCompNotifyCbf(BootLoaderRxCbf,USART_BUS_NUMBER_1);
}

void BootLoaderRxCbf(void)
{
	Bl_u8ReqRecieved=TRUE;
}

void BootLoaderFlashingSeq(void)
{
	switch(ServId)
	{
	case  Bl_Idle:

		if(*MarkerState == Bl_AppExist)
		{
			if(AppInfo->entry)
			{
				AppInfo->entry();
			}

		}/*do not have app*/
		else if(Loc_u8State==0 && (AppInfo->entry == 0xffffffff))
		{
			Usart_enuRecieveBufferZc(Bl_u8AppBuff,1,USART_BUS_NUMBER_1);
			Loc_u8State = 1;
		}
		// marker not .entry

		// we are coming from the app
		// the condition of the flag not used
		else if(Loc_u8State==0 && *MarkerState == Bl_FlashingState)
		{
			/*the application received SESSION CONTROL */
			Usart_enuRecieveBufferZc(Bl_u8AppBuff,1,USART_BUS_NUMBER_1);
			ServId = Bl_DownloadRequest;

		}
		/*command received */
		else if(Loc_u8State==1 && Bl_u8ReqRecieved == TRUE)
		{
			Bl_u8ReqRecieved = FALSE;
			Loc_u8State= FALSE;

			/*right command */
			if(Bl_u8AppBuff[0] == SESSION_CONTROL)
			{
				Bl_u8gState = SESSION_CONTROL;
				//send pos ack
				ServId = Bl_DownloadRequest;
				/*write on the MarkerState BL_Flashing*/
			}
			/*wrong command*/
			else
			{
				Bl_vidSendNegRes();
			}
		}
		break;

	case Bl_DownloadRequest:
//		FlashUnlock();
		if(Loc_u8State==0)
		{
			Usart_enuRecieveBufferZc(&Bl_u8AppBuff,1,USART_BUS_NUMBER_1);
			Bl_vidSendPosRes();
			Loc_u8State = 1;
		}
		else if(Loc_u8State==1 && Bl_u8ReqRecieved == TRUE)
		{
			Bl_u8ReqRecieved = FALSE;

			if(Bl_u8AppBuff[0] == DOWNLOAD_REQUEST)
			{
				// 16 bec each member is word which 4 bytes
				Usart_enuRecieveBufferZc(Bl_u8AppBuff,8,USART_BUS_NUMBER_1);
				Bl_u8gState = DOWNLOAD_REQUEST;
				Bl_vidSendPosRes();
				Loc_u8State=2;
			}
			else
			{
				Bl_vidSendNegRes();
				Loc_u8State = 0;
				ServId = Bl_Idle;
			}

		}
		else if(Loc_u8State == 2 && Bl_u8ReqRecieved == TRUE)
		{
			Loc_u8State = 0;
			Bl_u8ReqRecieved = 0;
			u32 size = 	Bl_u8AppBuff[0]|((u32)Bl_u8AppBuff[1])<<8|((u32)Bl_u8AppBuff[2])<<16|  ((u32) Bl_u8AppBuff[3]) <<24;
			u32 entry  = 	Bl_u8AppBuff[4]|((u32)Bl_u8AppBuff[5])<<8|((u32)Bl_u8AppBuff[6])<<16|((u32)Bl_u8AppBuff[7])<<24;
			/*Erasing sector 1 for the APPINFO*/
			FlashErase(FLASH_SECTOR1);
			/*Erasing sector 2 for the MARKER*/
			FlashErase(FLASH_SECTOR2);
			FlashProgram(PARALLELISM_SIZE_32,size,&AppInfo->size);
			FlashProgram(PARALLELISM_SIZE_32,0,AppInfo->add);
			FlashProgram(PARALLELISM_SIZE_32,entry,AppInfo->entry);

			Bl_u32gSizeCounter = AppInfo->size;
			/*we should here erase apsector*/
			FlashErase(FLASH_SECTOR5);

			ServId = Bl_TransferData;
		}
		break;

	case Bl_TransferData:
		;
		static u32 var=0;
		static u8 Counter = 0;
		if(Loc_u8State==0)
		{
			Usart_enuRecieveBufferZc(&Bl_u8AppBuff,1,USART_BUS_NUMBER_1);
			Bl_vidSendPosRes(); // for download request is done
			Loc_u8State = 1;
		}

		else if( Bl_u8ReqRecieved == TRUE && Loc_u8State == 1)
		{
			if (Bl_u8AppBuff[0] == TRANSFER_DATA )
			{
				Bl_u8gState = Bl_u8AppBuff[0];
				Loc_u8State = 2 ;
			}
			else /*wrong command*/
			{
				Bl_vidSendNegRes();
				Loc_u8State = 0;
			}
		}
		// Bl_u8ReqRecieved is still TRUE
		else if(Loc_u8State == 2 && Bl_u8ReqRecieved == TRUE)
		{
			//var=Bl_u8AppBuff[Counter]|((u32)Bl_u8AppBuff[Counter+1])<<8|((u32)Bl_u8AppBuff[Counter+2])<<16|((u32) Bl_u8AppBuff[Counter+3]) <<24;
			//FlashProgram(PARALLELISM_SIZE_32,var,0x08020000+AppInfo->add+Counter);
			if(Bl_u32gSizeCounter <= 1025 && Bl_u32gSizeCounter > 0)
			{
				Usart_enuRecieveBufferZc(&Bl_u8AppBuff , Bl_u32gSizeCounter , USART_BUS_NUMBER_1);

			}
			else
			{
				Usart_enuRecieveBufferZc(&Bl_u8AppBuff , 1025 , USART_BUS_NUMBER_1);
			}
			Bl_vidSendPosRes();
			/*Enable the Rx Interrupt to receive Buffer with size of the Application */
			Bl_u8ReqRecieved = FALSE;
			Loc_u8State = 3;
		}

		else if(Loc_u8State == 3 && Bl_u8ReqRecieved == TRUE)/*flashing*/
		{
			// this condition to enter once at the beginning of 1k block
			if(Counter == 0)
			{
				Bl_u8CrcResult= Bl_u8calc_crc(&Bl_u8AppBuff, 1024);/*should be calculated once*/
			}
			//*checking on CRC*//
			if(Bl_u8AppBuff[1024] != Bl_u8CrcResult)
			{
				Bl_vidSendNegRes();
				Loc_u8State = 2;
			}
			else
			{
				/*CRC is good, let's flash*/
				if(Bl_u32gSizeCounter>1024)
				{
					var=Bl_u8AppBuff[Counter]|((u32)Bl_u8AppBuff[Counter+1])<<8|((u32)Bl_u8AppBuff[Counter+2])<<16|  ((u32) Bl_u8AppBuff[Counter+3]) <<24;
					FlashProgram(PARALLELISM_SIZE_32,var,0x08020000+AppInfo->add+Counter);

					Counter+=4;
					if (Counter == 1024 )
					{
						Bl_u32gSizeCounter = Bl_u32gSizeCounter - 1024;
						/*update add of the app info --> where I am standing in the flash*/
						FlashProgram(PARALLELISM_SIZE_32,AppInfo->size - Bl_u32gSizeCounter,&AppInfo->add);
						Counter =  0 ;
						Bl_vidSendPosRes();
						Loc_u8State = 2;// for recieving another buffer
					}

				}
				/*the last part*/
				else if(Bl_u32gSizeCounter <= 1024 && Bl_u32gSizeCounter > 0)
				{
					/*Here we should flash Bl_u32gSizeCounter*/
					FlashProgram(PARALLELISM_SIZE_32,Bl_u32gSizeCounter,0x08020000+AppInfo->add+Counter);
					Counter += 4;
					if (Counter == Bl_u32gSizeCounter )
					{
						Counter =  0 ;
						Loc_u8State = 0;
						Bl_vidSendPosRes();
						ServId = Bl_TransferExit;
					}
				}
			}

		}



		break;
	case Bl_TransferExit:
		if(Loc_u8State==0)
		{
			Usart_enuRecieveBufferZc(&Bl_u8AppBuff,1,USART_BUS_NUMBER_1);
			Loc_u8State = 1;
		}
		else if(Loc_u8State==1 && Bl_u8ReqRecieved == TRUE)
		{
			Bl_u8ReqRecieved = FALSE;

			if(Bl_u8AppBuff[0] == TRANSFER_EXIT)
			{
				/* update marker with app exist */
				/*update entry point */
				FlashProgram(PARALLELISM_SIZE_32,Bl_AppExist,MarkerState);
				FlashLock();
				// 16 bec each member is word which 4 bytes
				Bl_u8gState = TRANSFER_EXIT;
				Bl_vidSendPosRes();
				ServId = Bl_Idle;
			}
			else
			{
				// I have doubt about this assignation
				ServId =Bl_TransferExit ;
				Bl_vidSendNegRes();
			}
		}
		break;
	}
}


static void Bl_vidSendPosRes(void)
{

	Usart_enuHalSendDataSync(0x7F , Usart_enuBusNum1);
	trace_printf("pos");
}
static void Bl_vidSendNegRes(void)
{
	Usart_enuHalSendDataSync(0x10 + Bl_u8gState , Usart_enuBusNum1);
}

static u8 Bl_u8calc_crc(unsigned char *data, unsigned len)
{
	char crc = 0;
	for ( int i = 0 ; i < len; i++ )
		crc = crc ^ data[i];
	return crc;
}


//			else
//			{
//
//				/*static counter = 0;*/
//				/*Here we should calculate CRC by changing state of servId to crccheck*/
//				/* and we will have if else
//				 * if condition is flase then send neg ack
//				 *
//				 * else
//				 * 	the logic below
//				 * */
//				/*Here we should flash 1024 bytes*/
//
//				/*we should flash all the 1K before proceeding */
//				/*counter += 4*/
//				/*flasfWord(0x08020000+appinfo->add+counter,buffer[counter]);*/
//				//				if (counter == 1024 )
//				//				{
//				//					Bl_u32gSizeCounter = Bl_u32gSizeCounter - 1024;
//				// 					/*appinfo->add = app->info->size- Bl_u32gSizeCounter*/
//				//					counter =  0 ;
//				//					Bl_vidSendPosRes();
//				//				}
//			}
