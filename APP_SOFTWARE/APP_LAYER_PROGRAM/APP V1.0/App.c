/*
 * App.c
 *
 *  Created on: Jun 30, 2022
 *      Author: dahroug
 */

#include "Std_types.h"
#include "Bit_utils.h"

#include "String.h"
#include "stm32f401cc.h"

#include "Nvic.h"
#include "Systick.h"
#include "Rcc.h"
#include "Gpio.h"
#include "Timer.h"
#include "Uart.h"

#include "HLed.h"

#include "App.h"

/************************************************ Section Constants & configurations ****************************************************/
#define 	NUM_OF_SEGMENTS 		168
#define 	MAX_STRING_CHARS		21
#define 	SPACE_SEGMENTS			3
#define 	CHAR_FRAME_SEGMENTS		5
#define 	NULL_BYTE				0x00
#define 	LED_CHAR_PORT			GPIO_PORTA
/****************************************************************************************************/


/************************************************  Section Global ****************************************************/
u8 Glb_u8SegmentIndex = 0;

u8 Glb_u8ArrOfSegments[NUM_OF_SEGMENTS] = {0};
/****************************************************************************************************/


/****************************************************Section Static functions************************************************/
static void APP_vidUartFunctionality(void)
{

}
/*************************************************************************************************/
static u16 APP_tenuIcuFunctionality (void)
{
	u32     Loc_u32FullRevolutionTicks = 0;
	u16		Loc_u16SegmentTicks        = 0;

	Loc_u32FullRevolutionTicks = TIMER_vidReadTIM11IcuValue();
	Loc_u16SegmentTicks        = (u16)(Loc_u32FullRevolutionTicks/NUM_OF_SEGMENTS);

	Glb_u8SegmentIndex         = 0;

	return Loc_u16SegmentTicks;
}
/*************************************************************************************************/
static void APP_tenuOcuFunctionality (void)
{
	if (Glb_u8SegmentIndex == NUM_OF_SEGMENTS)
	{
		Glb_u8SegmentIndex = 0;
	}
	Gpio_setPortValue(LED_CHAR_PORT, Glb_u8ArrOfSegments[Glb_u8SegmentIndex]);
	Glb_u8SegmentIndex ++;
}
/****************************************************************************************************************************/
static void APP_vidFillChar(u8 charachter)
{
	switch (charachter)
	{
		case 'A':
		{
			u8 A[] = {252,18,17,18,252};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = A[frameByte];
			}
		}
		break;
		case 'B':
		   {
				u8 B[] = {255,137,137,137,118};
				for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
				{
					Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = B[frameByte];
				}
		   }
		break;
		case 'C':
		{
			u8 C[] = {126,129,129,129,66};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = C[frameByte];
			}
		}
		break;
		case 'D':
		 {
			u8 D[] = {255,129,129,129,126};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = D[frameByte];
			}
		 }
		break;

		case 'E':
		{
			u8 E[] = {255,137,137,137,137};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = E[frameByte];
			}
		}
		break;

		case 'F':
		{
			u8 F[] = {255,9,9,9,9};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = F[frameByte];
			}
		}
		break;
		case 'G':
		{
			u8 G[] = {126,129,145,145,114};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = G[frameByte];
			}
		}
		break;
		case 'H':
		{
			u8 H[] = {255,8,8,8,255};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = H[frameByte];
			}
		}
		break;
		case 'I':
		{
			u8 I[] = {129,129,255,129,129};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = I[frameByte];
			}
		}
		break;
		case 'J':
		{
			u8 J[] = {64,129,129,127,1};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = J[frameByte];
			}
		}
		break;
		case 'K':
		{
			u8 K[] = {255,16,40,68,130};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = K[frameByte];
			}
		}
		break;
		case 'L':
		{
			u8 L[] = {255,128,128,128,128};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = L[frameByte];
			}
		}
		break;
		case 'M':
		{
			u8 M[] = {255,2,12,2,255};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = M[frameByte];
			}
		}
		break;
		case 'N':
		{
			u8 N[] = {255,2,4,8,255};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = N[frameByte];
			}
		}
		break;
		case 'O':
		{
			u8 O[] = {126,129,129,129,126};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = O[frameByte];
			}
		}
		break;
		case 'P':
		{
			u8 P[] = {255,17,17,17,14};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = P[frameByte];
			}
		}
		break;

		case 'Q':
		{
			u8 Q[] = {126,129,161,65,190};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = Q[frameByte];
			}
		}
		break;
		case 'R':
		{
			u8 R[] = {255,17,41,73,134};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = R[frameByte];
			}
		}
		break;
		case 'S':
		{
			u8 S[] = {70,137,137,137,114};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = S[frameByte];
			}
		}
		break;
		case 'T':
		{
			u8 T[] = {1,1,255,1,1};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = T[frameByte];
			}
		}
		break;
		case 'U':
		{
			u8 U[] = {127,128,128,128,127};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = U[frameByte];
			}
		}
		break;
		case 'V':
		{
			u8 V[] = {63,64,128,64,63};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = V[frameByte];
			}
		}
		break;
		case 'W':
		{
			u8 W[] = {127,128,96,128,127};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = W[frameByte];
			}
		}
		break;
		case 'X':
		{
			u8 X[] = {199,40,16,40,169};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = X[frameByte];
			}
		}
		break;
		case 'Y':
		{
			u8 Y[] = {7,8,240,8,7};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = Y[frameByte];
			}
		}
		break;
		case 'Z':
		{
			u8 Z[] = {225,177,153,141,135};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = Z[frameByte];
			}
		}
		break;
		case 'a':
		{
			u8 a[] = {28,34,34,28,32};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = a[frameByte];
			}
		}
		break;

		case 'b':
		{
			u8 b[] = {255,144,144,144,96};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = b[frameByte];
			}
		}
		break;

		case 'c':
		{
			u8 c[] = {60,66,66,66,36};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = c[frameByte];
			}
		}
		break;

		case 'd':
		{
			u8 d[] = {69,144,144,144,255};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = d[frameByte];
			}
		}
		break;

		case 'e':
		{
			u8 e[] = {126,137,137,137,78};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = e[frameByte];
			}
		}
		break;

		case 'f':
		{
			u8 f[] = {8,254,9,1,2};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = f[frameByte];
			}
		}
		break;

		case 'g':
		{
			u8 g[] = {70,169,137,137,127};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = g[frameByte];
			}
		}
		break;

		case 'h':
		{
			u8 h[] = {255,16,16,16,224};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = h[frameByte];
			}
		}
		break;
		case 'i':
		{
			u8 i[] = {0,0,253,0,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = i[frameByte];
			}
		}
		break;

		case 'j':
		{
			u8 j[] = {64,128,128,128,125};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = j[frameByte];
			}
		}
		break;
		case 'k':
		{
			u8 k[] = {126,16,40,68,2};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = k[frameByte];
			}
		}
		break;
		case 'l':
		{
			u8 l[] = {0,129,255,128,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = l[frameByte];
			}
		}
		break;
		case 'm':
		{
			u8 m[] = {124,2,124,2,124};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = m[frameByte];
			}
		}
		break;
		case 'n':
		{
			u8 n[] = {124,2,2,2,124};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = n[frameByte];
			}
		}
		break;
		case 'o':
		{
			u8 o[] = {56,68,68,68,56};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = o[frameByte];
			}
		}
		break;
		case 'p':
		{
			u8 p[] = {126,18,18,12,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = p[frameByte];
			}
		}
		break;
		case 'r':
		{
			u8 r[] = {126,8,4,8,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = r[frameByte];
			}
		}
		break;
		case 's':
		{
			u8 s[] = {36,74,82,36,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = s[frameByte];
			}
		}
		break;
		case 't':
		{
			u8 t[] = {8,254,136,64,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = t[frameByte];
			}
		}
		break;
		case 'u':
		{
			u8 u[] = {60,64,64,124,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = u[frameByte];
			}
		}
		break;
		case 'v':
		{
			u8 v[] = {128,32,64,32,28};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = v[frameByte];
			}
		}
		break;
		case 'w':
		{
			u8 w[] = {60,64,96,64,60};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = w[frameByte];
			}
		}
		break;
		case 'x':
		{
			u8 x[] = {220,32,32,220,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = x[frameByte];
			}
		}
		break;
		case 'y':
		{
			u8 y[] = {38,72,72,62,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = y[frameByte];
			}
		}
		break;
		case 'z':
		{
			u8 z[] = {98,82,74,70,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = z[frameByte];
			}
		}
		break;
		case '0':
		{
			u8 zero[] = {126,137,145,161,126};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = zero[frameByte];
			}
		}
		break;
		case '1':
		{
			u8 one[] = {130,129,255,128,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = one[frameByte];
			}
		}
		break;
		case '2':
		{
			u8 two[] = {194,161,145,137,134};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = two[frameByte];
			}
		}
		break;
		case '3':
		{
			u8 three[] = {66,129,137,137,118};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = three[frameByte];
			}
		}
		break;
		case '4':
		{
			u8 four[] = {15,8,8,255,8};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = four[frameByte];
			}
		}
		break;
		case '5':
		{
			u8 five[] = {79,137,137,137,113};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = five[frameByte];
			}
		}
		break;
		case '6':
		{
			u8 six[] = {126,145,145,145,98};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = six[frameByte];
			}
		}
		break;
		case '7':
		{
			u8 seven[] = {1,1,255,17,15};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = seven[frameByte];
			}
		}
		break;
		case '8':
		{
			u8 eight[] = {118,137,137,137,118};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = eight[frameByte];
			}
		}
		break;
		case '9':
		{
			u8 nine[] = {70,137,137,137,126};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = nine[frameByte];
			}
		}
		break;

		/************************************** SPECIAL CHARACHTERS ******************************************/
		case ':':
		{
			u8 colon[] = {0,0,102,0,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = colon[frameByte];
			}
		}
		break;
		case '.':
		{
			u8 dot[] = {0,0,64,0,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = dot[frameByte];
			}
		}
		break;
		case '!':
		{
			u8 not[] = {0,0,191,0,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = not[frameByte];
			}
		}
		break;
		case '"':
		{
			u8 quotation[] = {0,8,4,8,4};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = quotation[frameByte];
			}
		}
		break;
		case '/':
		{
			u8 slash[] = {64,32,16,8,4};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = slash[frameByte];
			}
		}
		break;

		default:
		{
			u8 space[] = {0,0,0,0,0};
			for (u8 frameByte = 0; frameByte<CHAR_FRAME_SEGMENTS; frameByte++)
			{
				Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = space[frameByte];
			}
		}
		break;
	}

	for (u8 spaceIndex = 0; spaceIndex < SPACE_SEGMENTS; spaceIndex++)
	{
		Glb_u8ArrOfSegments[Glb_u8SegmentIndex++] = NULL_BYTE;
	}

}
/****************************************************************************************************/
void  APP_vidInit (void)
{
	/* Is it necessary .....?*/
	Rcc_tenuSelectSysClk(RCC_HSI);

	/* what prescalers .....?*/
	Rcc_tenuConfigBusPinPrescaler(RCC_CFGR_AHB_PRESCALER, RCC_CFGR_APB1_PRESCALER,
			                      RCC_CFGR_APB2_PRESCALER,RCC_CFGR_MCO1_PRESCALER,
								  RCC_CFGR_MCO2_PRESCALER);
	/* which GPIOS*/
	Rcc_tenuControlPeripheral(RCC_AHB1EN_BUS,RCC_AHB1ENR_GPIOA_EN,RCC_PERI_EN);


	Rcc_tenuControlPeripheral(RCC_APB2EN_BUS, RCC_APB2ENR_TIM10_EN,RCC_PERI_EN);
	Rcc_tenuControlPeripheral(RCC_APB2EN_BUS, RCC_APB2ENR_TIM11_EN,RCC_PERI_EN);

	/* which UART*/
	Rcc_tenuControlPeripheral(RCC_APB2EN_BUS, RCC_APB2ENR_USART1_EN,RCC_PERI_EN);

	SYSTICK_vidInit();

	NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	NVIC_EnableIRQ(USART1_IRQn);

	TIMER_vidInitTimers();

	Led_init();

}

/****************************************************************************************************/
void APP_vidSetUp(void)
{
	static Uart_Cfg_t Loc_StaticUartCfg =
	{
	  .Uart_pfCallbackFnc         = APP_vidUartFunctionality,
	  .Uart_pvChannel             = UART_pvUART1,
	  .Uart_u16BaudRate           = 9600,
	  .Uart_u16DataLength         = UART_u16DATA_LENGTH_8BIT,
	  .Uart_u16InterruptsCtrl     = UART_u16INTERRUPT_RXNE,
	  .Uart_u16OverSamplingMode   = UART_u16OVERSAMPLING_BY_16,
	  .Uart_u16ReceivingCtrl      = UART_u16RECIEVER_ENABLE,
	  .Uart_u16StopBits           = UART_u16STOPBIT_1BIT,
	  .Uart_u16TransmittingCtrl   = UART_u16TRANSMITTER_DISABLE
	};

	static GPIO_ChannelPinCfg_t  Loc_staticGpioCharLedCfg =
	{
	  .Mode  = 	  GPIO_OUTPUT_PP,
	  .Pin   =   (GPIO_PIN_00 | GPIO_PIN_01 | GPIO_PIN_02 | GPIO_PIN_03 | GPIO_PIN_04
			                  | GPIO_PIN_05 | GPIO_PIN_06 | GPIO_PIN_07),

	  .Port  =    GPIO_PORTA,
	  .Speed =    GPIO_OSPEEDR_VHS
    };

	static GPIO_ChannelPinCfg_t  Loc_staticGpioEspRxCfg      =
	{
	  .Mode  = 	  GPIO_INPUT_PU,
	  .Pin   =    GPIO_PIN_10,
	  .Port  =    GPIO_PORTA,
	  .Speed =    GPIO_OSPEEDR_VHS
    };

	static GPIO_ChannelPinCfg_t  Loc_staticGpioHallEffectCfg =
	{
	  .Mode  = 	  GPIO_INPUT_PU,
	  .Pin   =    GPIO_PIN_09,
	  .Port  =    GPIO_PORTB,
	  .Speed =    GPIO_OSPEEDR_VHS
    };



	/*UART initialization configuration*/
	Uart_vidInit(&Loc_StaticUartCfg );


	/*GPIO Pins Configuration*/
	Gpio_Init(&Loc_staticGpioCharLedCfg);
	Gpio_Init(&Loc_staticGpioEspRxCfg);
	Gpio_Init(&Loc_staticGpioHallEffectCfg);

	/* Set call backs */
	TIMER_vidSetCallBackIcuTim11(APP_tenuIcuFunctionality);
	TIMER_vidSetCallBackOcuTim10(APP_tenuOcuFunctionality);
}

/****************************************************************************************************/
Std_enuErrorStatus  App_vidDisplayString( pu8 const str)
{
	Std_enuErrorStatus Loc_returnErrorStatusVal = OK;
	u8 Loc_charIndex = 0;

	if ( String_u8GetStrLen(str) > MAX_STRING_CHARS)
	{
		Loc_returnErrorStatusVal = NOK;
	}
	else
	{
		while (str[Loc_charIndex] != '\0')
		{
			APP_vidFillChar(str[Loc_charIndex]);
			Loc_charIndex++;
		}

		Glb_u8SegmentIndex = 0;
	}

	return Loc_returnErrorStatusVal;
}

/*************************************************************************************************/
void APP_vidStartPov(void)
{
	TIMER_vidStartTimers();
}




