#ifndef RIMOT_APPLICATION_PORTIBILITY
#define RIMOT_APPLICATION_PORTIBILITY

#if defined(MCU_APP)
#include "portable_interrupts.h"
#include "target_chipset.h"
        //TODO: CHECK THROUGH VARIOUS PROCESSOR DEFINITIONS AND INCLUDE THE CORRECT ONE. FOR NOW IM JUST INCLUDING THE HEADER FOR THE ARDUINO-NANO-LIKE STM32NUCLEO-F303 (we have a bunch kicking around)
#endif



#endif