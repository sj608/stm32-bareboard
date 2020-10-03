#ifndef __STM32_CAN_H
#define __STM32_CAN_H

#include "stm32f10x.h"

ErrorStatus canInit();
ErrorStatus canDeinit();
ErrorStatus receiveMsg();
ErrorStatus transmitMsg();

#endif