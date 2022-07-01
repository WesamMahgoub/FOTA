
#include "Std_types.h"
#include "diag/Trace.h"
#include "Bit_utils.h"
#include "Rcc.h"
#include "Timer.h"
#include "Gpio.h"

int main(void)
{
	Rcc_tenuSelectSysClk(RCC_HSI);

	Rcc_tenuConfigBusPinPrescaler(RCC_CFGR_AHB_PRESCALER, RCC_CFGR_APB1_PRESCALER,
			                     RCC_CFGR_APB2_PRESCALER, RCC_CFGR_MCO2_PRESCALER,
								 RCC_CFGR_MCO1_PRESCALER);

	Rcc_tenuControlPeripheral(RCC_APB2EN_BUS, RCC_APB2ENR_TIM10_EN,RCC_PERI_EN);
	Rcc_tenuControlPeripheral(RCC_APB2EN_BUS, RCC_APB2ENR_TIM11_EN,RCC_PERI_EN);

	TIMER_vidInitTimers();
	TIMER_vidStartTimers();

  while (1)
    {

    }

  return 0;
}

// ----------------------------------------------------------------------------
