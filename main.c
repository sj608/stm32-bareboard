#include "stm32f10x.h"
#include "stm32_can.h"
#include "stm32_gpio.h"

#define WAIT_TIMEOUT 0x03FF

struct canRxMsg
{
    volatile uint32_t rxMsgL[3];
    volatile uint32_t rxMsgH[3];
    volatile uint32_t rxMsgId[3];
    volatile uint32_t rxMsgDlTS[3];
    volatile uint8_t rxMsgFOV;
    volatile uint8_t rxMsgFUL;
    volatile uint8_t msgCnt;
} canRx0Msg, canRx1Msg;

/*
The FIFO 0 interrupt can be generated by the following events:
– Reception of a new message, FMP0 bits in the CAN_RF0R register are not ‘00’.
– FIFO0 full condition, FULL0 bit in the CAN_RF0R register set.
– FIFO0 overrun condition, FOVR0 bit in the CAN_RF0R register set.
CAN_RF0R
CAN_RI0R
CAN_RDT0R
CAN_RDL0R
CAN_RDH0R
*/
void USB_LP_CAN_RX0_IRQHandler(void)
{   
    uint16_t waitTime = 0x0000;
    uint8_t  messageCnt = 0;

    canRx0Msg.rxMsgFOV = CAN1->RF0R & CAN_RF0R_FOVR0 ? 1 : 0;
    CAN1->RF0R |= CAN1->RF0R & CAN_RF0R_FOVR0 ? CAN_RF0R_FOVR0 : 0;
    canRx0Msg.rxMsgFUL = CAN1->RF0R & CAN_RF0R_FULL0 ? 1 : 0;
    CAN1->RF0R |= CAN1->RF0R & CAN_RF0R_FULL0 ? CAN_RF0R_FULL0 : 0;

    while( (CAN1->RF0R & CAN_RF0R_FMP0)!= 0 && waitTime != WAIT_TIMEOUT)
    {
        CAN1->RF0R |= CAN_RF0R_RFOM0;
        canRx0Msg.rxMsgId[messageCnt-1] = CAN1->sFIFOMailBox[0].RIR;
        canRx0Msg.rxMsgDlTS[messageCnt-1] = CAN1->sFIFOMailBox[0].RDTR;
        canRx0Msg.rxMsgL[messageCnt-1] = CAN1->sFIFOMailBox[0].RDLR;
        canRx0Msg.rxMsgH[messageCnt-1] = CAN1->sFIFOMailBox[0].RDHR;
        messageCnt = (CAN1->RF0R & CAN_RF0R_FMP0);
        messageCnt++;
        waitTime++;
    }
    canRx0Msg.msgCnt = messageCnt;

}

void CAN_RX1_IRQHandler(void)
{

}

void CAN_SCE_IRQHandler(void)
{

}

void receivedMsg(void);

int main(void)
{
    initGPIO();
    outputPinInit();
    canPinInit();
    if(canInit())
    {
      //  GPIOA->BSRR |= GPIO_BSRR_BS0;
    }

   //  while(1)
   //  {
   //      receivedMsg();
   //  }

    return 0;
}


void receivedMsg(void)
{
    struct msgFrame
    {
        uint32_t rxMsgL[3];
        uint32_t rxMsgH[3];
        uint32_t rxMsgId[3];
        uint32_t rxMsgDlTS[3];
        uint8_t rxMsgFOV;
        uint8_t rxMsgFUL;
        uint8_t msgCnt;
    } rxMsg;
    
    if(canRx0Msg.msgCnt != 0)
    {
        rxMsg.msgCnt = canRx0Msg.msgCnt;
    }
    else
    {
        rxMsg.msgCnt = 0;
    }
    
    for(uint8_t i = 0; i < rxMsg.msgCnt; i++)
    {
        rxMsg.rxMsgL[i] = canRx0Msg.rxMsgL[i];
        rxMsg.rxMsgH[i] = canRx0Msg.rxMsgH[i];
        rxMsg.rxMsgId[i] = canRx0Msg.rxMsgId[i];
        rxMsg.rxMsgDlTS[i] = canRx0Msg.rxMsgDlTS[i];
        rxMsg.rxMsgFOV = canRx0Msg.rxMsgFOV;
        rxMsg.rxMsgFUL = canRx0Msg.rxMsgFUL;
    }

    for(uint8_t i = 0; i < rxMsg.msgCnt; i++)
    {
        switch (rxMsg.rxMsgId[i])
        {
        case 0X07FFFA11:
            GPIOA->BSRR |= GPIO_BSRR_BS0;
            break;
        
        case 0X07FF11FA:
            GPIOA->BSRR &= ~(GPIO_BSRR_BS0);
            GPIOA->BSRR |= GPIO_BSRR_BS0;
            break;

        case 0X05FFFA11:
            GPIOA->BSRR |= GPIO_BSRR_BS1;
            break;

        case 0X05FF11FA:
            GPIOA->BSRR &= ~(GPIO_BSRR_BS1);
            GPIOA->BSRR |= GPIO_BSRR_BS1;
            break;
        }
    }

}