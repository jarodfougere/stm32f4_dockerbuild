#ifndef LOWPOWER_TARGET_SYSTEM
#define LOWPOWER_TARGET_SYSTEM
#if defined(MCU_APP)
#if defined(STM32F3xx)
#   include "stm32f3xx.h"
#elif defined(STM32L0xx)
#   include "stm32l0xx.h"
#elif defined(STM32F4xx)
#   include "stm32f4xx.h"
#elif defined(STM32F7xx)
#   include "stm32f7xx.h"
#elif defined(STM32F0xx)
#   include "stm32f0xx.h"
#endif
#endif
#endif