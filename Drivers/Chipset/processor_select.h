#ifndef PROCESSOR_SELECT
#define PROCESSOR_SELECT
#include <stdint.h>
#if defined(STM32_CHIPSET)
#   if defined(STM32F3xx)    
#       include "stm32f3xx.h"
#   elif defined(STM32L0xx)    
#       include "stm32l0xx.h"
#   else
#       error   "AN STM32 CHIPSET FAMILY DEFINITION HAS NOT BEEN PROVIDED."
                " PLEASE SEE processor_select.h"
#   endif



/* CMSIS DOES NOT PROVIDE SRAM SIZES FOR CHIPSET. 
WE NEED THESE FOR CUSTOM STARTUP CODE */
#   if defined(STM32F3xx)
#       if defined(STM32F301x8)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F302x8)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F302xC)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F302xE)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F303x8)
#           define VECT_TAB_OFFSET  0x0
#           define SRAM_SIZE        48*1024 /* NUCLEO-F303 HAS 48 KiB SRAM */
#           if !defined  (HSE_VALUE) 
#               define HSE_VALUE    ((uint32_t)8000000) 
#           endif 
#           if !defined  (HSI_VALUE)
#               define HSI_VALUE    ((uint32_t)8000000)
#           endif 
#       elif defined(STM32F303xC)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F303xE)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F373xC)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F334x8)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F318xx)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F328xx)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F358xx)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F378xx)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       elif defined(STM32F398xx)
#           error SRAM SIZE HAS NOT BEEN DEFINED FOR THIS PROCESSOR
#       else
#           error   "AN STM32F3xx device definition has not been provided. PLEASE SEE processor_select.h"
#       endif
#   elif defined(STM32L0xx)
#       if defined(STM32L010xB)
#       elif defined(STM32L010x8)
#       elif defined(STM32L010x6)
#       elif defined(STM32L010x4)
#       elif defined(STM32L011xx)
#       elif defined(STM32L021xx)
#       elif defined(STM32L031xx)
#       elif defined(STM32L041xx)
#       elif defined(STM32L051xx)
#       elif defined(STM32L052xx)
#       elif defined(STM32L053xx)
#       elif defined(STM32L062xx)
#       elif defined(STM32L063xx)
#       elif defined(STM32L061xx)
#       elif defined(STM32L071xx)
#       elif defined(STM32L072xx)
#           define VECT_TAB_OFFSET  0x00U
#           define SRAM_SIZE        20*1024 /* stm32l072vz has 20 KiB SRAM */
#           if !defined  (HSE_VALUE)
#               define HSE_VALUE    ((uint32_t)8000000U) 
#           endif 
#           if !defined  (MSI_VALUE)
#               define MSI_VALUE    ((uint32_t)2097152U)
#           endif 
#           if !defined  (HSI_VALUE)
#               define HSI_VALUE    ((uint32_t)16000000U) 
#           endif 
#       elif defined(STM32L073xx)
#       elif defined(STM32L082xx)
#       elif defined(STM32L083xx)
#       elif defined(STM32L081xx)
#       else
#   error "A DEFINITION FOR AN STM32L0xx device has not been provided"
#   endif
#   else
#       error  "AN STM32 CHIPSET FAMILY DEFINITION HAS NOT BEEN PROVIDED."
            " PLEASE SEE processor_select.h"
#   endif
#else
#   error   "A CHIPSET MANUFACTURER DEFINITION HAS NOT BEEN PROVIDED. Please see processor_select.h"






#endif /* chipset manufacturer header guard */
#endif /* processor select header guard */