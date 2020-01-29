#include "processor_select.h"
#if defined (STM32L0xx)
    SystemCoreClock = 2097152U; /* 32.768 kHz * 2^6 */
    const uint8_t AHBPrescTable[16] = 
    {
        0U, 
        0U, 
        0U, 
        0U, 
        0U, 
        0U, 
        0U, 
        0U, 
        1U, 
        2U, 
        3U, 
        4U, 
        6U, 
        7U, 
        8U, 
        9U
    };

    const uint8_t APBPrescTable[8] = 
    {
        0U, 
        0U, 
        0U, 
        0U, 
        1U, 
        2U, 
        3U, 
        4U
    };

    const uint8_t PLLMulTable[9] = 
    {
        3U, 
        4U, 
        6U, 
        8U, 
        12U, 
        16U, 
        24U, 
        32U, 
        48U
    };

#elif defined (STM32F3xx)
    uint32_t SystemCoreClock = 8000000;
    const uint8_t AHBPrescTable[16] = 
    {
        0, 
        0, 
        0, 
        0, 
        0, 
        0, 
        0, 
        0, 
        1, 
        2, 
        3, 
        4, 
        6, 
        7, 
        8, 
        9
    };
    const uint8_t APBPrescTable[8]  = 
    {
        0, 
        0, 
        0, 
        0, 
        1, 
        2, 
        3, 
        4
    };
#else
    
#endif
  