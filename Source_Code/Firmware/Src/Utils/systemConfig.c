#include <stdint.h>
#include <limits.h>
#include <string.h>

#include "systemConfig.h"

#include "stm32f4xx.h"

static char device_name[USER_DEVICE_NAME_SIZE + 1] = "Unnamed";

char *getDeviceName(void)
{
    return device_name;
}


int setDeviceName(const char *new_name)
{
    if (new_name == NULL || strlen(new_name) > USER_DEVICE_NAME_SIZE)
    {
        return -1; /* too large */
    }
    else
    {
        strcpy(device_name, new_name);
        return 0;
    }
}


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
