#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "Std_types.h"
#include "BL.h"
#include "UsartHal.h"


//char arr[11]={'a','b','d','e','l','r','a','h','m','a','n'};
char arr1[11];

void notification(void);

int main(void)
{

	Usart_vidHalInit();
	Usart_enuRegRxCompNotifyCbf(notification,Usart_enuBusNum1);
//  while (1)
//    {
	    Usart_enuRecieveBufferSync(arr1,11,Usart_enuBusNum1);
//    }
	  while (1);
}

void notification(void)
{
	trace_printf("%s",arr1);
}


