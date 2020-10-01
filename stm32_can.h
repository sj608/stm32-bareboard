#ifndef __STM32_CAN_H
#define __STM32_CAN_H

#include "stm32f10x.h"

typedef enum
{
    SUCCESS = 0,
    ERROR   = 1,
    FAIL    = 2,
} FUNCTIONSTATUS;

FUNCTIONSTATUS canInit();
FUNCTIONSTATUS canDeinit();
FUNCTIONSTATUS receiveMsg();
FUNCTIONSTATUS transmitMSG();

#endif