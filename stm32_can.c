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
    - Reception Filter
    - Interrupt
*/

FUNCTIONSTATUS canInit()
{
    uint32_t waitTimeout = 0x00000000; //counts from 0 to WAIT_TIMEOUT
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
    }
    

}