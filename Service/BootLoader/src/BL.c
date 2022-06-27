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


u32 Bl_u32FirstAppAdd;
static void Bl_vidSendPosRes(void);
static void Bl_vidSendNegRes(void);


void BootLoaderInit(void)
{
	Usart_enuRegRxCompNotifyCbf(BootLoaderRxCbf,USART_BUS_NUMBER_1);
	Usart_vidHalInit();
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

		/*do not have app*/
		if(Loc_u8State==0 && (AppInfo->entry == (pu32)0xffffffff))
		{
			Usart_enuRecieveBufferZc(Bl_u8AppBuff,1,USART_BUS_NUMBER_1);
			Loc_u8State = 1;
		}
		// marker not .entry

		// we are coming from the app
		// the condition of the flag not used
		else if(Loc_u8State==0 && AppInfo->entry == 0xAAAAAAAA)
		{
			// Todo
			// servId = Download req
			// we will flash new app
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
				Bl_vidSendPosRes();
				ServId = Bl_DownloadRequest;
				/*write on the MarkerState BL_Flashing*/

			}
			/*wrong command*/
			else
			{
				Loc_u8State= 0;
				Bl_vidSendNegRes();
			}
		}
		else if(*MarkerState == Bl_AppExist)
		{
			if(AppInfo->entry)
			{
				AppInfo->entry();
			}
		}
		break;


	case Bl_DownloadRequest:
		if(Loc_u8State==0)
		{
			Usart_enuRecieveBufferZc(&Bl_u8AppBuff,1,USART_BUS_NUMBER_1);
			Loc_u8State = 1;
		}
		else if(Loc_u8State==1 && Bl_u8ReqRecieved == TRUE)
		{
			Bl_u8ReqRecieved = FALSE;

			if(Bl_u8AppBuff[0] == DOWNLOAD_REQUEST)
			{
				// 16 bec each member is word which 4 bytes
				Usart_enuRecieveBufferZc(Bl_u8AppBuff,16,USART_BUS_NUMBER_1);
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
			AppInfo->size = 	Bl_u8AppBuff[0]|Bl_u8AppBuff[1]<<8|Bl_u8AppBuff[2]<<16|Bl_u8AppBuff[3]<<24;
			AppInfo->add  = 	Bl_u8AppBuff[4]|Bl_u8AppBuff[5]<<8|Bl_u8AppBuff[6]<<16|Bl_u8AppBuff[7]<<24;
			AppInfo->entry=  Bl_u8AppBuff[8]|Bl_u8AppBuff[9]<<8|Bl_u8AppBuff[10]<<16|Bl_u8AppBuff[11]<<24;
			AppInfo->crc  = 	Bl_u8AppBuff[12]|Bl_u8AppBuff[13]<<8|Bl_u8AppBuff[14]<<16|Bl_u8AppBuff[15]<<24;

			Bl_u32gSizeCounter = AppInfo->size;
			Bl_u32FirstAppAdd = AppInfo->add;

			/*we should here erase sector*/

			ServId = Bl_TransferData;
		}
		break;

	case Bl_TransferData:
		if(Loc_u8State==0)
		{
			Usart_enuRecieveBufferZc(&Bl_u8AppBuff,1025,USART_BUS_NUMBER_1);

			if(Bl_u8AppBuff[0] == Bl_TransferData)
			{
				if(Bl_u32gSizeCounter <= 1024 && Bl_u32gSizeCounter > 0)
				{
					Usart_enuRecieveBufferZc(&Bl_u8AppBuff , Bl_u32gSizeCounter , USART_BUS_NUMBER_1);
				}
				else
				{
					Usart_enuRecieveBufferZc(&Bl_u8AppBuff , 1024 , USART_BUS_NUMBER_1);
					//trace_printf("Interrupt enabled\n");
				}
				Bl_u8gState = Bl_u8AppBuff[0];
				/*Enable the Rx Interrupt to receive Buffer with size of the Application */
				Loc_u8State = 2;
				Bl_u8ReqRecieved = 0;
			}
			else
			{
				Bl_vidSendNegRes();
				ServId = SESSION_CONTROL;
				Loc_u8State = 0;
			}
		}
		else if(Loc_u8State == 2 && Bl_u8ReqRecieved == TRUE)
		{
			Bl_u8ReqRecieved = FALSE;
			Loc_u8State = 0;
			if(Bl_u32gSizeCounter <= 1024 && Bl_u32gSizeCounter > 0)
			{
				/*Here we should flash Bl_u32gSizeCounter*/
				Bl_vidSendPosRes();
				ServId = Bl_TransferExit;
				Loc_u8State = 0;
				break;
			}
			else
			{
				/*Here we should flash 1024 bytes*/
				Bl_u32gSizeCounter = Bl_u32gSizeCounter - 1024;
			}
			Bl_vidSendPosRes();
			trace_printf("Remaining %d bytes\n",Bl_u32gSizeCounter);
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
				// 16 bec each member is word which 4 bytes
				Bl_u8gState = TRANSFER_EXIT;
				Bl_vidSendPosRes();
			}
			else
			{
				// I have doubt about this assignation
				ServId =Bl_Idle ;
				Bl_vidSendNegRes();
			}
		}
		break;
	case Bl_CheckCRC:

		break;
	}
}


static void Bl_vidSendPosRes(void)
{
	Usart_enuHalSendDataSync(0x7F , Usart_enuBusNum1);
}
static void Bl_vidSendNegRes(void)
{
	Usart_enuHalSendDataSync(0x10 + Bl_u8gState , Usart_enuBusNum1);
}
