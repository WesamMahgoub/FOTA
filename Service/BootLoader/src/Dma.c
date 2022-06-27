/*
 * Dma.c
 *
 *  Created on: May 4, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "Dma.h"
#include "Dma_prv.h"

pcbf Dma1_pcbfManCbf[8];
pcbf Dma2_pcbfManCbf[8];

Dma_tenuErrorStatus Dma_enuInit(Dma_tstrCfg* Copy_strDmaCfg)
{
	Dma_tenuErrorStatus Loc_enuErrorStatus = Dma_enuOk;
	u32 Loc_u32TempVar =0;
	Dma_tRegCfg* Loc_pstrChannel = Copy_strDmaCfg->Dma_tstrCfg_DmaAdd;
	if ((Copy_strDmaCfg->Dma_tstrCfg_DmaAdd ||
			Copy_strDmaCfg->Dma_pu32Mem1Add||
			Copy_strDmaCfg->Dma_pu32Mem2Add||
			Copy_strDmaCfg->Dma_pu32periphAdd)==NULL)
	{
		Loc_enuErrorStatus = Dma_enuNullPtr;
	}
	else if ( Copy_strDmaCfg->Dma_enuChannelID > Dma_Max_Num_Of_Channels)
	{
		Loc_enuErrorStatus=Dma_enuInvalidChannelId;
	}
	else if((Copy_strDmaCfg->Dma_u32NumOfData & DMA_u32DATA_NUM_VALIDATION)!=0)
	{
		Loc_enuErrorStatus =Dma_enuInvalidDataNum;
	}
	else if(Copy_strDmaCfg->Dma_pu32periphAdd == NULL)
	{
		Loc_enuErrorStatus = Dma_enuNullPtr;
	}
	else if(Copy_strDmaCfg->Dma_pu32Mem1Add == NULL)
	{
		Loc_enuErrorStatus = Dma_enuNullPtr;
	}
	//*DMA CONFIGURATION**//
	else
	{
		Loc_u32TempVar = Loc_pstrChannel->Dma_tStreamRegCfg[Copy_strDmaCfg->Dma_enuStreamNum].SxCR;// reading the reg in temp var
		Loc_u32TempVar &=~ DMA_u32CR_CLEAR_MASK;// clearing the desired bits to be configured
		Loc_u32TempVar=(
				((u32)Copy_strDmaCfg->Dma_enuChannelID<<DMA_u8CHSEL_SHIFTING_MASK)|
				(Copy_strDmaCfg->Dma_u32DoubBuffModeCtrl)|
				(Copy_strDmaCfg->Dma_u32CircModeCtrl)|
				(Copy_strDmaCfg->Dma_u32PeriSize)|
				(Copy_strDmaCfg->Dma_u32MemorySize)|
				(Copy_strDmaCfg->Dma_u32TransmissionDir)|
				(Copy_strDmaCfg->Dma_u32SwPriority)|
				(Copy_strDmaCfg->Dma_u32IncMode)|
				(Copy_strDmaCfg->Dma_u32InterruptCtrl)
		);
		/*************************************ASSIGNING THE MEM ADD 1 **************************************/
		Loc_pstrChannel->Dma_tStreamRegCfg[Copy_strDmaCfg->Dma_enuStreamNum].SxM0AR= (Copy_strDmaCfg->Dma_pu32Mem1Add);
		/***********************************ASSIGNING THE PERIPH ADD*****************************************/
		Loc_pstrChannel->Dma_tStreamRegCfg[Copy_strDmaCfg->Dma_enuStreamNum].SxPAR =(Copy_strDmaCfg->Dma_pu32periphAdd);
		/****************************ASSIGN THE MEM ADD IN CASE OF DOUBLE BUFFFER MODE ACTIVATED*************/
		if(Copy_strDmaCfg->Dma_pu32Mem2Add == NULL)
		{
			Loc_enuErrorStatus = Dma_enuNullPtr;
		}
		else
		{
			if((Copy_strDmaCfg->Dma_u32DoubBuffModeCtrl)&DMA_u32GET_DOUBLE_MODE_STATUS)
			{
				Loc_pstrChannel->Dma_tStreamRegCfg[Copy_strDmaCfg->Dma_enuStreamNum].SxM1AR = (Copy_strDmaCfg->Dma_pu32Mem2Add);
			}
		}
		/**************************ASSIGN NUM OF DATA IN THE NDT reg****************************/
		Loc_pstrChannel->Dma_tStreamRegCfg[Copy_strDmaCfg->Dma_enuStreamNum].SxNDTR = (Copy_strDmaCfg->Dma_u32NumOfData);
	}

	return Loc_enuErrorStatus;
}

/********************************DMA Control Function for start/Stop DMA****************************************/
Dma_tenuErrorStatus Dma_enuControl(void* pvidDmaNum,Dma_tenuStreamNum Copy_enuStreamNum, u8 Copy_u8DmaState)
{
	Dma_tenuErrorStatus Loc_enuErrorStatus = Dma_enuOk;
	if(pvidDmaNum == NULL)
	{
		Loc_enuErrorStatus = Dma_enuNullPtr;
	}
	else
	{
		switch(Copy_u8DmaState)
		{
		case DMA_u32STREAM_START:
			((Dma_tRegCfg*)pvidDmaNum)->Dma_tStreamRegCfg[Copy_enuStreamNum].SxCR |=DMA_u32STREAM_START;
			break;
		case DMA_u32STREAM_STOP:
			((Dma_tRegCfg*)pvidDmaNum)->Dma_tStreamRegCfg[Copy_enuStreamNum].SxCR |=DMA_u32STREAM_STOP;
			break;
		default:
			Loc_enuErrorStatus =Dma_enuWrongDmaState;
			break;
		}
	}
	return Loc_enuErrorStatus;
}

/*Fisrt arg should be one of these options
DMA1 / DMA2 --> BASE address
 */
Dma_tenuErrorStatus Dma_enuClearFlags(void* pvidDmaNum, u64 Copy_u64Flags)
{
	Dma_tenuErrorStatus Loc_enuErrorStatus = Dma_enuOk;

	if(pvidDmaNum == NULL)
	{
		Loc_enuErrorStatus = Dma_enuNullPtr;
	}
	else
	{
		((Dma_tRegCfg*)pvidDmaNum)->LIFCR|=(u32)Copy_u64Flags;
		((Dma_tRegCfg*)pvidDmaNum)->HIFCR|=(u32)(Copy_u64Flags>>32);
	}

	return Loc_enuErrorStatus;
}



/********************************Register Call Back Func*********************************/
Dma_tenuErrorStatus Dma_enuRegHalCbf(pu32 pcbf_pHalCallBackFn,pu32* pvidDmaNum, Dma_tenuStreamNum Copy_enuStreanNum)
{
	Dma_tenuErrorStatus Loc_enuErrorStatus = Dma_enuOk;
	if(pcbf_pHalCallBackFn == NULL || pvidDmaNum==NULL)
	{
		Loc_enuErrorStatus = Dma_enuNullPtr;
	}
	else
	{
		if(pvidDmaNum == DMA_1)
		{
			switch (Copy_enuStreanNum)
			{
			case Dma_Stream_0:
				Dma1_pcbfManCbf[Dma_Stream_0]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_1:
				Dma1_pcbfManCbf[Dma_Stream_1]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_2:
				Dma1_pcbfManCbf[Dma_Stream_2]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_3:
				Dma1_pcbfManCbf[Dma_Stream_3]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_4:
				Dma1_pcbfManCbf[Dma_Stream_4]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_5:
				Dma1_pcbfManCbf[Dma_Stream_5]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_6:
				Dma1_pcbfManCbf[Dma_Stream_6]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_7:
				Dma1_pcbfManCbf[Dma_Stream_7]=pcbf_pHalCallBackFn;
				break;
			}
		}
		else if(pvidDmaNum == DMA_2)
		{
			switch (Copy_enuStreanNum)
			{
			case Dma_Stream_0:
				Dma2_pcbfManCbf[Dma_Stream_0]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_1:
				Dma2_pcbfManCbf[Dma_Stream_1]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_2:
				Dma2_pcbfManCbf[Dma_Stream_2]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_3:
				Dma2_pcbfManCbf[Dma_Stream_3]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_4:
				Dma2_pcbfManCbf[Dma_Stream_4]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_5:
				Dma2_pcbfManCbf[Dma_Stream_5]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_6:
				Dma2_pcbfManCbf[Dma_Stream_6]=pcbf_pHalCallBackFn;
				break;
			case Dma_Stream_7:
				Dma2_pcbfManCbf[Dma_Stream_7]=pcbf_pHalCallBackFn;
				break;
			}
		}
		else
		{
			Loc_enuErrorStatus=Dma_enuInvalidDmaNum;
		}
	}
	return Loc_enuErrorStatus;
}
//		switch ((u32)pvidDmaNum)
//		{
//		case (u32)DMA_1:
//				switch (Copy_enuStreanNum)
//				{
//				case Dma_Stream_0:
//					Dma1_pcbfManCbf[Dma_Stream_0]=pcbf_pHalCallBackFn;
//					break;
//				case Dma_Stream_1:
//					Dma1_pcbfManCbf[Dma_Stream_1]=pcbf_pHalCallBackFn;
//					break;
//				case Dma_Stream_2:
//					Dma1_pcbfManCbf[Dma_Stream_2]=pcbf_pHalCallBackFn;
//					break;
//				case Dma_Stream_3:
//					Dma1_pcbfManCbf[Dma_Stream_3]=pcbf_pHalCallBackFn;
//					break;
//				case Dma_Stream_4:
//					Dma1_pcbfManCbf[Dma_Stream_4]=pcbf_pHalCallBackFn;
//					break;
//				case Dma_Stream_5:
//					Dma1_pcbfManCbf[Dma_Stream_5]=pcbf_pHalCallBackFn;
//					break;
//				case Dma_Stream_6:
//					Dma1_pcbfManCbf[Dma_Stream_6]=pcbf_pHalCallBackFn;
//					break;
//				case Dma_Stream_7:
//					Dma1_pcbfManCbf[Dma_Stream_7]=pcbf_pHalCallBackFn;
//					break;
//				}
//		break;
//				case (u32)DMA_2:
//						switch (Copy_enuStreanNum)
//						{
//						case Dma_Stream_0:
//							Dma2_pcbfManCbf[Dma_Stream_0]=pcbf_pHalCallBackFn;
//							break;
//						case Dma_Stream_1:
//							Dma2_pcbfManCbf[Dma_Stream_1]=pcbf_pHalCallBackFn;
//							break;
//						case Dma_Stream_2:
//							Dma2_pcbfManCbf[Dma_Stream_2]=pcbf_pHalCallBackFn;
//							break;
//						case Dma_Stream_3:
//							Dma2_pcbfManCbf[Dma_Stream_3]=pcbf_pHalCallBackFn;
//							break;
//						case Dma_Stream_4:
//							Dma2_pcbfManCbf[Dma_Stream_4]=pcbf_pHalCallBackFn;
//							break;
//						case Dma_Stream_5:
//							Dma2_pcbfManCbf[Dma_Stream_5]=pcbf_pHalCallBackFn;
//							break;
//						case Dma_Stream_6:
//							Dma2_pcbfManCbf[Dma_Stream_6]=pcbf_pHalCallBackFn;
//							break;
//						case Dma_Stream_7:
//							Dma2_pcbfManCbf[Dma_Stream_7]=pcbf_pHalCallBackFn;
//							break;
//						}
//				break;
//		}

/*DMA1 HANDLERS PROTOTYPES*/

//*The functions which will be regiterd will be in the USARTHAL*//
void DMA1_Stream0_IRQHandler (void)
{
	if(Dma1_pcbfManCbf[Dma_Stream_0])
	{
		Dma1_pcbfManCbf[Dma_Stream_0]();
	}
}
void DMA1_Stream1_IRQHandler (void)
{
	if(Dma1_pcbfManCbf[Dma_Stream_1])
	{
		Dma1_pcbfManCbf[Dma_Stream_1]();
	}
}
void DMA1_Stream2_IRQHandler (void)
{
	if(Dma1_pcbfManCbf[Dma_Stream_2])
	{
		Dma1_pcbfManCbf[Dma_Stream_2]();
	}
}
void DMA1_Stream3_IRQHandler (void)
{
	if(Dma1_pcbfManCbf[Dma_Stream_3])
	{
		Dma1_pcbfManCbf[Dma_Stream_3]();
	}
}
void DMA1_Stream4_IRQHandler (void)
{
	if(Dma1_pcbfManCbf[Dma_Stream_4])
	{
		Dma1_pcbfManCbf[Dma_Stream_4]();
	}
}
void DMA1_Stream5_IRQHandler (void)
{
	if(Dma1_pcbfManCbf[Dma_Stream_5])
	{
		Dma1_pcbfManCbf[Dma_Stream_5]();
	}
}
void DMA1_Stream6_IRQHandler (void)
{
	if(Dma1_pcbfManCbf[Dma_Stream_6])
	{
		Dma1_pcbfManCbf[Dma_Stream_6]();
	}
}
void DMA1_Stream7_IRQHandler (void)
{
	if(Dma1_pcbfManCbf[Dma_Stream_7])
	{
		Dma1_pcbfManCbf[Dma_Stream_7]();
	}
}

/*DMA1 HANDLERS PROTOTYPES*/
void DMA2_Stream0_IRQHandler (void)
{
	if(Dma2_pcbfManCbf[Dma_Stream_0])
	{
		Dma2_pcbfManCbf[Dma_Stream_0]();
	}
}
void DMA2_Stream1_IRQHandler (void)
{
	if(Dma2_pcbfManCbf[Dma_Stream_1])
	{
		Dma2_pcbfManCbf[Dma_Stream_1]();
	}
}
void DMA2_Stream2_IRQHandler (void)
{
	if(Dma2_pcbfManCbf[Dma_Stream_2])
	{
		Dma2_pcbfManCbf[Dma_Stream_2]();
	}
}
void DMA2_Stream3_IRQHandler (void)
{
	if(Dma2_pcbfManCbf[Dma_Stream_3])
	{
		Dma2_pcbfManCbf[Dma_Stream_3]();
	}
}
void DMA2_Stream4_IRQHandler (void)
{
	if(Dma2_pcbfManCbf[Dma_Stream_4])
	{
		Dma2_pcbfManCbf[Dma_Stream_4]();
	}
}
void DMA2_Stream5_IRQHandler (void)
{
	if(Dma2_pcbfManCbf[Dma_Stream_5])
	{
		Dma2_pcbfManCbf[Dma_Stream_5]();
	}
}
void DMA2_Stream6_IRQHandler (void)
{
	if(Dma2_pcbfManCbf[Dma_Stream_6])
	{
		Dma2_pcbfManCbf[Dma_Stream_6]();
	}
}
void DMA2_Stream7_IRQHandler (void)
{
	if(Dma2_pcbfManCbf[Dma_Stream_7])
	{
		Dma2_pcbfManCbf[Dma_Stream_7]();
	}
}


