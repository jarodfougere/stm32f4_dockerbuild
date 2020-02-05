#ifndef LOWPOWER_APPLICATION_PORTIBILITY
#define LOWPOWER_APPLICATION_PORTIBILITY

#   if defined(EXTERAL_PROCESSOR)
        #include "portable_interrupts.h"
#       include "target_system.h"
        //TODO: CHECK THROUGH VARIOUS PROCESSOR DEFINITIONS AND INCLUDE THE CORRECT ONE. FOR NOW IM JUST INCLUDING THE HEADER FOR THE ARDUINO-NANO-LIKE STM32NUCLEO-F303 (we have a bunch kicking around)
#       include "stm32f303x8"
#   endif



#endif