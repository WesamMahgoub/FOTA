#include "Std_types.h"

#include "App.h"

int main(void)
{
  u8 helloMsg[] = "HELLO ITI POV";

  APP_vidInit();
  APP_vidSetUp();
  App_vidDisplayString(helloMsg);
  APP_vidStartPov();

  while (1)
    {
       // Add your code here.
    }

  return 0;
}


// ----------------------------------------------------------------------------
