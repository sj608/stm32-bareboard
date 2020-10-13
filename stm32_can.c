#include "stm32f10x.h"
#include "stm32_can.h"

#define WAIT_TIMEOUT 0xFFFFF


/* 
Initialize CAN settings
1.  Mode of operation
    - In SLEEP mode by default
    - Set INRQ and clear SLEEP in CAN_MCR
    - Wait for INAK bit in CAN_MSR to be set by hardware
    CAN_MCR: reset value = 0x0001 0002
    CAN_MSR: reset value = 0x0000 0002
    CAN_BTR: reset value = 0x0123 0000
2.  Bit Rate & Bit timing
3.  Transmit Settings
    - Interrupt
4.  Receive Settings
    -Two Receive FIFO with 3 message box
    - Reception Filter
        - 14 [13:0] banks: 32-bit*2 filter register
        - Mode: list or mask
        - scale: Dual 16-bit or Single 32-bit
        - filter Assignment
    - Interrupt
*/

ErrorStatus canInit(void)
{
    uint32_t waitTimeout = 0x00000000; //counts from 0 to WAIT_TIMEOUT

    RCC->APB1RSTR |= RCC_APB1RSTR_CAN1RST;
    RCC->APB1RSTR &= ~(RCC_APB1RSTR_CAN1RST);
    RCC->APB1ENR &= ~(RCC_APB1ENR_USBEN);
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;

    // reset CAN_MCR register = 0x0001 0002
    CAN1->MCR |= CAN_MCR_RESET;
    // Exit Sleep mode
    CAN1->MCR &= ~((uint32_t)CAN_MCR_SLEEP);
    // Init mode request
    CAN1->MCR |= CAN_MCR_INRQ;
    // wait for INAK, time-out value needed, Hardware waits until current CAN activity stops
    while( ((CAN1->MSR & CAN_MSR_INAK) != CAN_MSR_INAK) && (waitTimeout != WAIT_TIMEOUT))
    {
        waitTimeout++;
    }
    waitTimeout = 0;
    if((CAN1->MSR & CAN_MSR_INAK) != CAN_MSR_INAK)
    {
        // check if acknowledged by hardware
        return ERROR;
    }
    else
    {
        // set rest of MCR
        // Disable Time Triggered Comm, Enable Automatic bus-off recovery,Enable Automatic Wakeup 
        CAN1->MCR &= ~((uint32_t)CAN_MCR_TTCM);
        CAN1->MCR |= CAN_MCR_ABOM | CAN_MCR_AWUM;
        // Atomatic retransmission, Enable Receive FIFO locked mode, Transmit FIFO priorit
        CAN1->MCR &= ~((uint32_t)CAN_MCR_NART);
        CAN1->MCR &= ~((uint32_t)CAN_MCR_RFLM);
        CAN1->MCR |= CAN_MCR_TXFP;
    }
    
    // Identifier filtering
    // Init mode for filter
    CAN1->FMR |= CAN_FMR_FINIT;
    // activate banck [3:0]
    CAN1->FA1R &= ~(CAN_FA1R_FACT0) & ~(CAN_FA1R_FACT1) & ~(CAN_FA1R_FACT2) & ~(CAN_FA1R_FACT3);
    // Setting List mode
    CAN1->FM1R&= ~CAN_FM1R_FBM0 & ~CAN_FM1R_FBM1 & ~CAN_FM1R_FBM2 & ~CAN_FM1R_FBM3;
    // Setting Single 32-bit scale config
    CAN1->FS1R|= CAN_FS1R_FSC0 | CAN_FS1R_FSC1 | CAN_FS1R_FSC2 | CAN_FS1R_FSC3;
    // assign bank [3:2] to FIFO1
    CAN1->FFA1R|= CAN_FFA1R_FFA2 | CAN_FFA1R_FFA3;

    // FIFO0
    CAN1->sFilterRegister[0].FR1 = 0X00111111;
    CAN1->sFilterRegister[0].FR2 = 0x00FFFFFF;
    CAN1->sFilterRegister[1].FR1 = 0X00111111;
    CAN1->sFilterRegister[1].FR2 = 0x00FFFFFF;
    // FIFO1
    CAN1->sFilterRegister[2].FR1 = 0X14FFFA11;
    CAN1->sFilterRegister[2].FR2 = 0x14FF11FA;
    CAN1->sFilterRegister[3].FR1 = 0X10FFFA11;
    CAN1->sFilterRegister[3].FR2 = 0x10FF11FA;
    // activate banck [3:0]
    CAN1->FA1R |= CAN_FA1R_FACT0 | CAN_FA1R_FACT1 | CAN_FA1R_FACT2 | CAN_FA1R_FACT3;
    // Activate filter
    CAN1->FMR &= ~(CAN_FMR_FINIT);

    // ERROR Interrupt Enable: Interrupt on Change in Error status register and Last Error Code
    // Refer to vector table inside stm32_startup.c file to interrupt handler name
    // CAN1->IER |= CAN_IER_ERRIE | CAN_IER_LECIE;
    // // FIFO1 Interrupt
    // CAN1->IER |= CAN_IER_FOVIE1 | CAN_IER_FFIE1 | CAN_IER_FMPIE1;
    // // FIFO0 Interrupt
    // CAN1->IER |= CAN_IER_FOVIE0 | CAN_IER_FFIE0 | CAN_IER_FMPIE0;

    // Bit timing
    /*
        Refer to Page 670 of Reference manual RM008
        Normal Operation with Loop back mode disabled
        250KBPS = baud rate = 1 / NominalBitTime
        NominalBitTime = 1*T_q + T_BS1 + T_BS2 = 16Tq = 4us, Tq = 250ns
        T_BS1 = T_q * (TS1[3:0] + 1) 13Tq
        T_BS2 = T_q * (TS2[2:0] + 1) 2 Tq
        APB regeister must be configured to enable Clock for CAN
        T_q = (BRP[9:0] + 1) / t_pclk (t_pclk = 32Mhz(max)) = 250ns, 1/250ns = 4MHz therefore BRP+1 should be 8, BRP = 7


    */  
    CAN1->BTR &= ~((uint32_t)CAN_BTR_SILM);
    CAN1->BTR &= ~((uint32_t)CAN_BTR_LBKM);
    // SJW = 1
    CAN1->BTR |= CAN_BTR_SJW & 0x00000000;
    // Segment 1 = 12
    CAN1->BTR |= CAN_BTR_TS1 & 0x000C0000;
    // Segment 2 = 1
    CAN1->BTR |= CAN_BTR_TS2 & 0x00100000;
    // BRP = 7
    CAN1->BTR |= CAN_BTR_BRP & 0x00000007;

    // Clear InitRequest to enter Normal Mode
    CAN1->MCR &= ~((uint32_t)CAN_MCR_INRQ);
    // INAK is 1, wait for hardware to cleare the bit
    while(((CAN1->MSR & CAN_MSR_INAK) == CAN_MSR_INAK) && (waitTimeout != WAIT_TIMEOUT))
    {
        waitTimeout++;
        // GPIOA->BSRR |= GPIO_BSRR_BS0;
    }
    if((CAN1->MSR & CAN_MSR_INAK) == CAN_MSR_INAK)
    {   
        // INAK is not cleared return Error
        return ERROR;
    }
    CAN1->MCR &= ~CAN_MCR_SLEEP;

    return SUCCESS;
}

ErrorStatus receiveMsg(void)
{

    return SUCCESS;
}

ErrorStatus transmitMsg(void)
{
    return SUCCESS;
}