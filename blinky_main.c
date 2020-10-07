#include "stm32f10x.h"
#define LEDPORT (GPIOA)
#define LED1 (0)
#define ENABLE_GPIO_CLOCK (RCC->APB2ENR |= RCC_APB2ENR_IOPAEN)
#define _MODER    CRL
#define GPIOMODER (GPIO_CRL_MODE0_0)




void ms_delay(int ms)
{
   while (ms-- > 0) {
      volatile int x=500;
      while (x-- > 0)
         __asm("nop");
   }
}

//Alternates blue and green LEDs quickly
int main(void)
{
    ENABLE_GPIO_CLOCK;              // enable the clock to GPIO
    LEDPORT->_MODER |= GPIOMODER;   // set pins to be general purpose output
    for (;;) 
    {
    ms_delay(2000);
    LEDPORT->ODR ^= (1<<LED1);  // toggle diodes
    }

    return 0;
}
