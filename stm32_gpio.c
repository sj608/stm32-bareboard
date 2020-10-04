#include "stm32_gpio.h"

/* 
Each of the general-purpose I/O ports has two 32-bit configuration registers (GPIOx_CRL,
GPIOx_CRH), two 32-bit data registers (GPIOx_IDR, GPIOx_ODR), a 32-bit set/reset
register (GPIOx_BSRR), a 16-bit reset register (GPIOx_BRR) and a 32-bit locking register
(GPIOx_LCKR).
Subject to the specific hardware characteristics of each I/O port listed in the datasheet, each
port bit of the General Purpose IO (GPIO) Ports, can be individually configured by software
in several modes:
• Input floating
• Input pull-up
• Input-pull-down
• Analog
• Output open-drain
• Output push-pull
• Alternate function push-pull
• Alternate function open-drain
*/


ErrorStatus initGPIO()
{   
    // PORT A,B reset and clear
    RCC->APB2RSTR |= RCC_APB2RSTR_IOPARST | RCC_APB2RSTR_IOPBRST;
    RCC->APB2RSTR &= ~(RCC_APB2RSTR_IOPARST) | ~(RCC_APB2RSTR_IOPBRST);
    
    // Enable GPIO peripheral clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN;

    return SUCCESS;
}

ErrorStatus inputPinInit()
{
    return SUCCESS;
}

ErrorStatus outputPinInit()
{
    return SUCCESS;
}

ErrorStatus canPinInit()
{

    /*
        CAN_TX Alternate function push-pull
        CAN_RX Input floating / input pull-up
        PA12 = Physical pin 33 = TX, PA11 = Physical pin 32= RX 
    */
    AFIO->MAPR |= ~(AFIO_MAPR_CAN_REMAP);
    // Tx pin setup: output
    GPIOA->CRH |= GPIO_CRH_MODE11;
    GPIOA->CRH |= GPIO_CRH_CNF11 & ~(GPIO_CRH_CNF11_0);
    // Rx pin setup: Input
    GPIOA->CRH &= ~(GPIO_CRH_MODE12);
    
    return SUCCESS;
}