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
void NMI_Handler                (void) __attribute__ ((weak, alias("defaultHandler")));
void HardFault_Handler          (void) __attribute__ ((weak, alias("defaultHandler")));
void MemManage_Handler          (void) __attribute__ ((weak, alias("defaultHandler")));
void BusFault_Handler           (void) __attribute__ ((weak, alias("defaultHandler")));
void UsageFault_Handler         (void) __attribute__ ((weak, alias("defaultHandler")));
void SVC_Handler                (void) __attribute__ ((weak, alias("defaultHandler")));
void DebugMon_Handler           (void) __attribute__ ((weak, alias("defaultHandler")));
void PendSV_Handler             (void) __attribute__ ((weak, alias("defaultHandler")));
void SysTick_Handler            (void) __attribute__ ((weak, alias("defaultHandler")));
void WWDG_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void PVD_IRQHandler             (void) __attribute__ ((weak, alias("defaultHandler")));
void TAMP_STAMP_IRQHandler      (void) __attribute__ ((weak, alias("defaultHandler")));
void RTC_WKUP_IRQHandler        (void) __attribute__ ((weak, alias("defaultHandler")));
void RCC_IRQHandler             (void) __attribute__ ((weak, alias("defaultHandler")));
void EXTI0_IRQHandler           (void) __attribute__ ((weak, alias("defaultHandler")));
void EXTI1_IRQHandler           (void) __attribute__ ((weak, alias("defaultHandler")));
void EXTI2_IRQHandler           (void) __attribute__ ((weak, alias("defaultHandler")));
void EXTI3_IRQHandler           (void) __attribute__ ((weak, alias("defaultHandler")));
void EXTI4_IRQHandler           (void) __attribute__ ((weak, alias("defaultHandler")));
void DMA1_Channel1_IRQHandler   (void) __attribute__ ((weak, alias("defaultHandler")));
void DMA1_Channel2_IRQHandler   (void) __attribute__ ((weak, alias("defaultHandler")));
void DMA1_Channel3_IRQHandler   (void) __attribute__ ((weak, alias("defaultHandler")));
void DMA1_Channel4_IRQHandler   (void) __attribute__ ((weak, alias("defaultHandler")));
void DMA1_Channel5_IRQHandler   (void) __attribute__ ((weak, alias("defaultHandler")));
void DMA1_Channel6_IRQHandler   (void) __attribute__ ((weak, alias("defaultHandler")));
void DMA1_Channel7_IRQHandler   (void) __attribute__ ((weak, alias("defaultHandler")));
void ADC_IRQHandler             (void) __attribute__ ((weak, alias("defaultHandler")));
void USB_HP_CAN_TX_IRQHandler   (void) __attribute__ ((weak, alias("defaultHandler")));
void USB_LP_CAN_RX0_IRQHandler  (void) __attribute__ ((weak, alias("defaultHandler")));
void CAN_RX1_IRQHandler         (void) __attribute__ ((weak, alias("defaultHandler")));
void CAN_SCE_IRQHandler         (void) __attribute__ ((weak, alias("defaultHandler")));
void EXTI9_5_IRQHandler         (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM1_BRK_IRQHandler        (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM1_UP_IRQHandler         (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM1_TRG_COM_IRQHandler    (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM1_CC_IRQHandler         (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM2_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM3_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM4_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void I2C1_EV_IRQHandler         (void) __attribute__ ((weak, alias("defaultHandler")));
void I2C1_ER_IRQHandler         (void) __attribute__ ((weak, alias("defaultHandler")));
void I2C2_EV_IRQHandler         (void) __attribute__ ((weak, alias("defaultHandler")));
void I2C2_ER_IRQHandler         (void) __attribute__ ((weak, alias("defaultHandler")));
void SPI1_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void SPI2_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void USART1_IRQHandler          (void) __attribute__ ((weak, alias("defaultHandler")));
void USART2_IRQHandler          (void) __attribute__ ((weak, alias("defaultHandler")));
void USART3_IRQHandler          (void) __attribute__ ((weak, alias("defaultHandler")));
void EXTI15_10_IRQHandler       (void) __attribute__ ((weak, alias("defaultHandler")));
void RTC_Alarm_IRQHandler       (void) __attribute__ ((weak, alias("defaultHandler")));
void USB_Wakeup_IRQHandler      (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM8_BRK_IRQHandler        (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM8_UP_IRQHandler         (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM8_TRG_COM_IRQHandler    (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM8_CC_IRQHandler         (void) __attribute__ ((weak, alias("defaultHandler")));
void ADC3_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void FSMC_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void SDIO_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM5_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void SPI3_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void UART4_IRQHandler           (void) __attribute__ ((weak, alias("defaultHandler")));
void UART5_IRQHandler           (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM6_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void TIM7_IRQHandler            (void) __attribute__ ((weak, alias("defaultHandler")));
void DMA2_Channel1_IRQHandler   (void) __attribute__ ((weak, alias("defaultHandler")));
void DMA2_Channel2_IRQHandler   (void) __attribute__ ((weak, alias("defaultHandler")));
void DMA2_Channel3_IRQHandler   (void) __attribute__ ((weak, alias("defaultHandler")));
void DMA2_Channel4_5_IRQHandler (void) __attribute__ ((weak, alias("defaultHandler")));


//stm32F103C8 has total 83 exceptions, but we may not be using every exception
//Define ones that you would use 
//__attribute__((section ("Section Name"))) : common compiler attribute to place the object in special section
uint32_t vectors[] __attribute__((section (".isr_vector"))) = 
{
    STACK_START,
    (uint32_t)Reset_Handler,
    (uint32_t)NMI_Handler,
    (uint32_t)HardFault_Handler,
    (uint32_t)MemManage_Handler,
    (uint32_t)BusFault_Handler,
    (uint32_t)UsageFault_Handler,
    0, // reserved
    0, // reserved
    0, // reserved
    0, // reserved
    (uint32_t)SVC_Handler,
    (uint32_t)DebugMon_Handler,
    0, // reserved
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
    (uint32_t)WWDG_IRQHandler,
    (uint32_t)PVD_IRQHandler,
    (uint32_t)TAMP_STAMP_IRQHandler,
    (uint32_t)RTC_WKUP_IRQHandler,
    0, // Flash global interrupt
    (uint32_t)RCC_IRQHandler,
    (uint32_t)EXTI0_IRQHandler,
    (uint32_t)EXTI1_IRQHandler,
    (uint32_t)EXTI2_IRQHandler,
    (uint32_t)EXTI3_IRQHandler,
    (uint32_t)EXTI4_IRQHandler,
    (uint32_t)DMA1_Channel1_IRQHandler,
    (uint32_t)DMA1_Channel2_IRQHandler,
    (uint32_t)DMA1_Channel3_IRQHandler,
    (uint32_t)DMA1_Channel4_IRQHandler,
    (uint32_t)DMA1_Channel5_IRQHandler,
    (uint32_t)DMA1_Channel6_IRQHandler,
    (uint32_t)DMA1_Channel7_IRQHandler,
    (uint32_t)ADC_IRQHandler,
    (uint32_t)USB_HP_CAN_TX_IRQHandler,
    (uint32_t)USB_LP_CAN_RX0_IRQHandler,
    (uint32_t)CAN_RX1_IRQHandler,
    (uint32_t)CAN_SCE_IRQHandler,
    (uint32_t)EXTI9_5_IRQHandler,
    (uint32_t)TIM1_BRK_IRQHandler,
    (uint32_t)TIM1_UP_IRQHandler,
    (uint32_t)TIM1_TRG_COM_IRQHandler,
    (uint32_t)TIM1_CC_IRQHandler,
    (uint32_t)TIM2_IRQHandler,
    (uint32_t)TIM3_IRQHandler,
    (uint32_t)TIM4_IRQHandler,
    (uint32_t)I2C1_EV_IRQHandler,
    (uint32_t)I2C1_ER_IRQHandler,
    (uint32_t)I2C2_EV_IRQHandler,
    (uint32_t)I2C2_ER_IRQHandler,
    (uint32_t)SPI1_IRQHandler,
    (uint32_t)SPI2_IRQHandler,
    (uint32_t)USART1_IRQHandler,
    (uint32_t)USART2_IRQHandler,
    (uint32_t)USART3_IRQHandler,
    (uint32_t)EXTI15_10_IRQHandler,
    (uint32_t)RTC_Alarm_IRQHandler,
    (uint32_t)USB_Wakeup_IRQHandler,
    (uint32_t)TIM8_BRK_IRQHandler,
    (uint32_t)TIM8_UP_IRQHandler,
    (uint32_t)TIM8_TRG_COM_IRQHandler,
    (uint32_t)TIM8_CC_IRQHandler,
    (uint32_t)ADC3_IRQHandler,
    (uint32_t)FSMC_IRQHandler,
    (uint32_t)SDIO_IRQHandler,
    (uint32_t)TIM5_IRQHandler,
    (uint32_t)SPI3_IRQHandler,
    (uint32_t)UART4_IRQHandler,
    (uint32_t)UART5_IRQHandler,
    (uint32_t)TIM6_IRQHandler,
    (uint32_t)TIM7_IRQHandler,
    (uint32_t)DMA2_Channel1_IRQHandler,
    (uint32_t)DMA2_Channel2_IRQHandler,
    (uint32_t)DMA2_Channel3_IRQHandler,
    (uint32_t)DMA2_Channel4_5_IRQHandler,
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