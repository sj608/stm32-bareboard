#include "stm32f10x.h"
#include "stm32_can.h"

#define WAIT_TIMEOUT 0xFFFF


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

FUNCTIONSTATUS canInit()
{
    uint32_t waitTimeout = 0x00000000; //counts from 0 to WAIT_TIMEOUT
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
    
    if((CAN1->MSR & CAN_MSR_INAK) != CAN_MSR_INAK)
    {
        // check if acknowledged by hardware
        return FAIL;
    }
    else
    {
        // set rest of MCR
        // Disable Time Triggered Comm, Enable Automatic bus-off recovery,Enable Automatic Wakeup 
        CAN1->MCR &= ~((uint32_t)CAN_MCR_TTCM);
        CAN1->MCR |= CAN_MCR_ABOM | CAN_MCR_AWUM;
        // Atomatic retransmission, Enable Receive FIFO locked mode, Transmit FIFO priorit
        CAN1->MCR &= ~((uint32_t)CAN_MCR_NART);
        CAN1->MCR |= CAN_MCR_RFLM | CAN_MCR_TXFP;
    }
    
    // Identifier filtering
    // Init mode for filter
    CAN1->FMR |= CAN_FMR_FINIT;
    // activate banck [3:0]
    CAN1->FA1R |= CAN_FA1R_FACT0 | CAN_FA1R_FACT1 | CAN_FA1R_FACT2 | CAN_FA1R_FACT3;
    // assign bank [3:2] to FIFO1
    CAN1->FFA1R|= CAN_FFA1R_FFA2 | CAN_FFA1R_FFA3;
    // Setting List mode
    CAN1->FM1R|= CAN_FM1R_FBM0 | CAN_FM1R_FBM1 | CAN_FM1R_FBM2 | CAN_FM1R_FBM3;
    // Setting Single 32-bit scale config
    CAN1->FS1R|= CAN_FS1R_FSC0 | CAN_FS1R_FSC1 | CAN_FS1R_FSC2 | CAN_FS1R_FSC3;

    CAN1->sFilterRegister[0]
    // Interrupt Setting
    // Bit timing

}