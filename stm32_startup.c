#include <stdint.h>
#include "stm32f10x.h"

#define SRAM_START 0x20000000U
#define SRAM_SIZE (20*1024) //20KB
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END

extern uint32_t end_of_text;
extern uint32_t start_of_data;
extern uint32_t end_of_data;
extern uint32_t start_of_bss;
extern uint32_t end_of_bss;

int main(void);

void Reset_Handler(void);
// Alias attribute is used to trigger defaultHandler (common) function
// Weak attribute is used to give programmer ability to override the function if required
void NMI_Handler(void) __attribute__((weak, alias("defaultHandler")));
void HardFault_Handler(void) __attribute__((weak, alias("defaultHandler")));
void MemManage_Handler(void) __attribute__((weak, alias("defaultHandler")));
void BusFault_Hanlder(void) __attribute__((weak, alias("defaultHandler")));
void UsageFault_Handler(void) __attribute__((weak, alias("defaultHandler")));
void SVCCall_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DebugMonitor_Handler(void) __attribute__((weak, alias("defaultHandler")));
void PendSV_Handler(void) __attribute__((weak, alias("defaultHandler")));
void SysTick_Handler(void) __attribute__((weak, alias("defaultHandler")));
void WWDG_Handler(void) __attribute__((weak, alias("defaultHandler")));
void PVD_Handler(void) __attribute__((weak, alias("defaultHandler")));
void TAMPER_Handler(void) __attribute__((weak, alias("defaultHandler")));
void RTC_Handler(void) __attribute__((weak, alias("defaultHandler")));
void FLASH_Handler(void) __attribute__((weak, alias("defaultHandler")));
void RCC_Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI0_Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI1_Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI2_Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI3_Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI4_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1_Channel1_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1_Channel2_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1_Channel3_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1_Channel4_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1_Channel5_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1_Channel6_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1_Channel7_Handler(void) __attribute__((weak, alias("defaultHandler")));
void ADC1_2_Handler(void) __attribute__((weak, alias("defaultHandler")));
void CAN1_TX_Handler(void) __attribute__((weak, alias("defaultHandler")));
void CAN1_RX0_Handler(void) __attribute__((weak, alias("defaultHandler")));
void CAN1_RX1_Handler(void) __attribute__((weak, alias("defaultHandler")));
void CAN1_SCE_Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI9_5_Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM1_BRK_Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM1_UP_Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM1_TRG_COM_Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM1_CC_Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM2_Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM3_Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM4_Handler(void) __attribute__((weak, alias("defaultHandler")));
void I2C1_EV_Handler(void) __attribute__((weak, alias("defaultHandler")));
void I2C1_ER_Handler(void) __attribute__((weak, alias("defaultHandler")));
void I2C2_EV_Handler(void) __attribute__((weak, alias("defaultHandler")));
void I2C2_ER_Handler(void) __attribute__((weak, alias("defaultHandler")));
void SPI1_Handler(void) __attribute__((weak, alias("defaultHandler")));
void SPI2_Handler(void) __attribute__((weak, alias("defaultHandler")));
void USART1_Handler(void) __attribute__((weak, alias("defaultHandler")));
void USART2_Handler(void) __attribute__((weak, alias("defaultHandler")));
void USART3_Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI15_10_Handler(void) __attribute__((weak, alias("defaultHandler")));
void RTCAlarm_Handler(void) __attribute__((weak, alias("defaultHandler")));
void OTG_FS_WKUP_Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM5_Handler(void) __attribute__((weak, alias("defaultHandler")));
void SPI3_Handler(void) __attribute__((weak, alias("defaultHandler")));
void USART4_Handler(void) __attribute__((weak, alias("defaultHandler")));
void USART5_Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM6_Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM7_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2_Channel1_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2_Channel2_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2_Channel3_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2_Channel4_Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2_Channel5_Handler(void) __attribute__((weak, alias("defaultHandler")));
void ETH_Handler(void) __attribute__((weak, alias("defaultHandler")));
void ETH_WKUP_Handler(void) __attribute__((weak, alias("defaultHandler")));
void CAN2_TX_Handler(void) __attribute__((weak, alias("defaultHandler")));
void CAN2_RX0_Handler(void) __attribute__((weak, alias("defaultHandler")));
void CAN2_RX1_Handler(void) __attribute__((weak, alias("defaultHandler")));
void CAN2_SCE_Handler(void) __attribute__((weak, alias("defaultHandler")));
void OTG_FS_Handler(void) __attribute__((weak, alias("defaultHandler")));


//stm32F103C8 has total 83 exceptions, but we may not be using every exception
//Define ones that you would use 
//__attribute__((section ("Section Name"))) : common compiler attribute to place the object in special section
uint32_t vectors[] __attribute__((section (".isr_vector"))) = {
    STACK_START,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemManage_Handler,
    (uint32_t)&BusFault_Hanlder,
    (uint32_t)&UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t)&SVCCall_Handler,
    (uint32_t)&DebugMonitor_Handler,
    0,
    (uint32_t)&PendSV_Handler,
    (uint32_t)&SysTick_Handler,
    (uint32_t)&WWDG_Handler,
    (uint32_t)&PVD_Handler,
    (uint32_t)&TAMPER_Handler,
    (uint32_t)&RTC_Handler,
    (uint32_t)&FLASH_Handler,
    (uint32_t)&RCC_Handler,
    (uint32_t)&EXTI0_Handler,
    (uint32_t)&EXTI1_Handler,
    (uint32_t)&EXTI2_Handler,
    (uint32_t)&EXTI3_Handler,
    (uint32_t)&EXTI4_Handler,
    (uint32_t)&DMA1_Channel1_Handler,
    (uint32_t)&DMA1_Channel2_Handler,
    (uint32_t)&DMA1_Channel3_Handler,
    (uint32_t)&DMA1_Channel4_Handler,
    (uint32_t)&DMA1_Channel5_Handler,
    (uint32_t)&DMA1_Channel6_Handler,
    (uint32_t)&DMA1_Channel7_Handler,
    (uint32_t)&ADC1_2_Handler,
    (uint32_t)&CAN1_TX_Handler,
    (uint32_t)&CAN1_RX0_Handler,
    (uint32_t)&CAN1_RX1_Handler,
    (uint32_t)&CAN1_SCE_Handler,
    (uint32_t)&EXTI9_5_Handler,
    (uint32_t)&TIM1_BRK_Handler,
    (uint32_t)&TIM1_UP_Handler,
    (uint32_t)&TIM1_TRG_COM_Handler,
    (uint32_t)&TIM1_CC_Handler,
    (uint32_t)&TIM2_Handler,
    (uint32_t)&TIM3_Handler,
    (uint32_t)&TIM4_Handler,
    (uint32_t)&I2C1_EV_Handler,
    (uint32_t)&I2C1_ER_Handler,
    (uint32_t)&I2C2_EV_Handler,
    (uint32_t)&I2C2_ER_Handler,
    (uint32_t)&SPI1_Handler,
    (uint32_t)&SPI2_Handler,
    (uint32_t)&USART1_Handler,
    (uint32_t)&USART2_Handler,
    (uint32_t)&USART3_Handler,
    (uint32_t)&EXTI15_10_Handler,
    (uint32_t)&RTCAlarm_Handler,
    (uint32_t)&OTG_FS_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)&TIM5_Handler,
    (uint32_t)&SPI3_Handler,
    (uint32_t)&USART4_Handler,
    (uint32_t)&USART5_Handler,
    (uint32_t)&TIM6_Handler,
    (uint32_t)&TIM7_Handler,
    (uint32_t)&DMA2_Channel1_Handler,
    (uint32_t)&DMA2_Channel2_Handler,
    (uint32_t)&DMA2_Channel3_Handler,
    (uint32_t)&DMA2_Channel4_Handler,
    (uint32_t)&DMA2_Channel5_Handler,
    (uint32_t)&ETH_Handler,
    (uint32_t)&ETH_WKUP_Handler,
    (uint32_t)&CAN2_TX_Handler,
    (uint32_t)&CAN2_RX0_Handler,
    (uint32_t)&CAN2_RX1_Handler,
    (uint32_t)&CAN2_SCE_Handler,
    (uint32_t)&OTG_FS_Handler

};


// void NMIHandler(void)
// {

// }
// Defualt (common) handler to use instead of however many exception handler
void defaultHandler(void)
{
    while(1);
}

void Reset_Handler(void)
{
    // copy .data section to SRAM
    uint32_t size = (uint32_t)&end_of_data - (uint32_t)&start_of_data;
    uint8_t *pDst = (uint8_t*)&start_of_data;
    uint8_t *pSrc = (uint8_t*)&end_of_text;
    for(uint32_t i = 0; i<size; i++)
    {
        *pDst = *pSrc++;
    }
    // Init the .bss section to zero in SRAM
    size = (uint32_t)&end_of_bss - (uint32_t)&start_of_bss;
    pDst = (uint8_t*)&start_of_bss;
    for(uint32_t i = 0; i<size; i++)
    {
        *pDst = 0;
    }
    /*
        After each device reset, all peripheral clocks are disabled (except for the SRAM and FLITF).
        Before using a peripheral you have to enable its clock in the RCC_AHBENR,
        RCC_APB2ENR or RCC_APB1ENR register. 
    */
    // call init funtion of standard libary function (only using standard libray such as scanf or string related )
    // call main()
    SystemInit(); //setting SYSCLK = 72Mhz, HCLK = 72Mhz, PCLK1(APB1) = 36Mhz , PCLK2(APB2) = 72Mhz
    main();
}