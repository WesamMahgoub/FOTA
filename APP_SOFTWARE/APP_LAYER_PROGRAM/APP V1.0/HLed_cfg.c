/*
 * HLed_cfg.c
 *
 *  Created on: Jun 28, 2022
 *      Author: dahroug
 */

#include "Std_types.h"

#include "Gpio.h"

#include "HLed.h"
#include "HLed_cfg.h"

const Led_Cnfg_t Leds[NUM_OF_LEDS] = {

		[OUTTER_LED]= {
						.Port = GPIO_PORTB,
						.Pin =  GPIO_PIN_00,
						.Active_State = LED_u8ACTIVE_STATE_HIGH,
		              },

		[INNER_LED]= {
						.Port = GPIO_PORTB,
						.Pin =  GPIO_PIN_01,
						.Active_State = LED_u8ACTIVE_STATE_HIGH,
		              },

		[CORE_LED]= {
						.Port = GPIO_PORTB,
						.Pin =  GPIO_PIN_02,
						.Active_State = LED_u8ACTIVE_STATE_HIGH,
		              }
};
