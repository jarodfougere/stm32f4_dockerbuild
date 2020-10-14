#include <stdint.h>
#include <limits.h>

#include "systemConfig.h"

#include "stm32f4xx.h"

void jumpToBootloader(void)
{
    __HAL_RCC_RTC_ENABLE();
    RTC->BKP0R = 0xF0CA;
    NVIC_SystemReset();
}


void systemReset(void)
{
    NVIC_SystemReset();
}
