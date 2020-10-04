#include "stm32f10x.h"
#include "stm32_can.h"
#include "stm32_gpio.h"





int main(void)
{
    initGPIO();
    canPinInit();
    canInit();
    
    return 0;
}