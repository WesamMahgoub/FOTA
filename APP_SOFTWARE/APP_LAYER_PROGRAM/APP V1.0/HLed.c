/*
 * HLed.c
 *
 *  Created on: Jun 28, 2022
 *      Author: dahroug
 */

#include "Std_types.h"
#include "Bit_utils.h"

#include "Rcc.h"
#include "Gpio.h"

#include "HLed.h"
#include "HLed_cfg.h"

#define RCC_ENABLE_PERI()			switch((u32)Leds[Loc_u8Iterator].Port){\
		case (u32) GPIO_PORTA:\
			RCC_GPIOEN|= RCC_AHB1ENR_GPIOA_EN;\
			break;\
		case (u32) GPIO_PORTB:\
			RCC_GPIOEN|= RCC_AHB1ENR_GPIOB_EN;\
			break;\
		case (u32) GPIO_PORTC:\
			RCC_GPIOEN|= RCC_AHB1ENR_GPIOC_EN;\
			break;\
		case (u32) GPIO_PORTD:\
			RCC_GPIOEN|= RCC_AHB1ENR_GPIOD_EN;\
			break;\
		case (u32) GPIO_PORTE:\
			RCC_GPIOEN|= RCC_AHB1ENR_GPIOE_EN;\
			break;\
		case (u32) GPIO_PORTH:\
			RCC_GPIOEN|= RCC_AHB1ENR_GPIOH_EN;\
			break;\
		}

/*
 * Function:  Led_init
 * --------------------
 * Led Pins Initialization.
 * *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Std_enuErrorStatus ERROR ENUM.
 */
Std_enuErrorStatus Led_init(void)
{
	/*DECLARE RETURN ERROR STATUS VARIABLE*/
	Std_enuErrorStatus Loc_enuReturnStatus = OK;
	/*DECLARE ITERATOR FOR LOOPS*/
	u8 Loc_u8Iterator;
	/*DECLARE MASK TO BE USED FOR RCC*/
	u32 RCC_GPIOEN	= 0;
	/*DECLARE STRUCT TO SET PIN CONFIGS*/
	GPIO_ChannelPinCfg_t Loc_strCfg;
	/*SET PIN CONFIGS*/
	Loc_strCfg.Mode=GPIO_OUTPUT_PP;
	Loc_strCfg.Speed=GPIO_OSPEEDR_VHS;

	/*LOOP TO CHECK USED GPIO TO ENABLE THEIR CLK*/
	for(Loc_u8Iterator = 0 ; Loc_u8Iterator< NUM_OF_LEDS ; Loc_u8Iterator++)
	{
		/*SWITCH CASE TO GET THE MASK*/
		RCC_ENABLE_PERI();
	}
	/*ENABLE CLK FOR USED GPIO*/
	Rcc_tenuControlPeripheral(RCC_AHB1EN_BUS,RCC_GPIOEN,RCC_PERI_EN);
	/*LOOP TO SET LED PINS CONFIGURATIONS*/
	for(Loc_u8Iterator = 0 ; Loc_u8Iterator< NUM_OF_LEDS ; Loc_u8Iterator++)
	{
		Loc_strCfg.Port  = Leds[Loc_u8Iterator].Port;
		Loc_strCfg.Pin  = Leds[Loc_u8Iterator].Pin;
		Gpio_Init(&Loc_strCfg);
	}
	/*RETURN THE ERROR STATUS*/
	return Loc_enuReturnStatus;
}

/*
 * Function:  Led_setState
 * --------------------
 * LED CHANGE STATUS TO BE ON OR OFF
 *
 * Copy_u16LedNum: LED NUMBER TO CHANGE IT'S STATE
 * Copy_u8LedState: DESIRED STATE
 *
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Std_enuErrorStatus ERROR ENUM.
 */

Std_enuErrorStatus Led_setState(u16 Copy_u16LedNum , u8 Copy_u8LedState)
{
	/*DECLARE RETURN ERROR VARIABLE*/
	Std_enuErrorStatus Loc_enuReturnStatus = OK;
	/*STRUCT TO SET LED CONFIGURATIONS*/
	GPIO_ChannelPinCfg_t Loc_strCfg;
	Loc_strCfg.Port  = Leds[Copy_u16LedNum].Port;
	Loc_strCfg.Pin   = Leds[Copy_u16LedNum].Pin;
	Gpio_setPinValue(&Loc_strCfg.Port ,Loc_strCfg.Pin, Copy_u8LedState ^ Leds[Copy_u16LedNum].Active_State);
	return Loc_enuReturnStatus;

}
