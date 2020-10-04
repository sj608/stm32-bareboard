#ifndef __STM32_GPIO_H
#define __STM32_GPIO_H

#include "stm32f10x.h"

ErrorStatus initGPIO();
ErrorStatus inputPinInit();
ErrorStatus outputPinInit();
ErrorStatus canPinInit();

#endif