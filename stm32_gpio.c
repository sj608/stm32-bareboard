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
    // // PORT A,B reset and clear
    // RCC->APB2RSTR |= RCC_APB2RSTR_IOPARST | RCC_APB2RSTR_IOPBRST | RCC_APB2RSTR_AFIORST;
    // RCC->APB2RSTR &= ~(RCC_APB2RSTR_IOPARST) | ~(RCC_APB2RSTR_IOPBRST) | ~(RCC_APB2RSTR_AFIORST);
    
    // Enable GPIO peripheral clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;

    return SUCCESS;
}

ErrorStatus inputPinInit()
{
    return SUCCESS;
}

ErrorStatus outputPinInit()
{   
    GPIOA->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE2 | GPIO_CRL_MODE3;
    GPIOA->CRL &=  ~(GPIO_CRL_CNF0) & ~(GPIO_CRL_CNF1) & ~(GPIO_CRL_CNF2) & ~(GPIO_CRL_CNF3);
    GPIOA->BRR &= 0;
    return SUCCESS;
}

ErrorStatus canPinInit()
{

    /*
        CAN_TX Alternate function push-pull
        CAN_RX Input floating / input pull-up
        PA12 = Physical pin 33 = TX, PA11 = Physical pin 32= RX 
    */
    AFIO->MAPR &= ~(AFIO_MAPR_CAN_REMAP);
    // Rx pin setup: Input
    GPIOA->CRH &= ~(GPIO_CRH_MODE11);
    GPIOA->CRH |= GPIO_CRH_CNF11 & ~(GPIO_CRH_CNF11_1);
    // Tx pin setup: Output
    GPIOA->CRH |= GPIO_CRH_MODE12;
    GPIOA->CRH &= ~(GPIO_CRH_CNF12);
    
    return SUCCESS;
}