/*
This is a generic inclusion header for the drivers.

It's easier to do it this way and let the linker purge dead code
than to manually build each HAL source module and link

*/ 


#ifndef RIMOT_DRIVERS
#define RIMOT_DRIVERS

#ifdef MCU_APP
#include "stm32f4xx.h"
#endif /* MCU_APP */

#endif /* RIMOT_DRIVERS */