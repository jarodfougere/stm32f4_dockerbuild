/**
 * @file rimot_pin_aliases.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This module provides pin mapping / lookup table functionality
 * for pins on the mcu
 * @version 0.1
 * @date 2020-04-06
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated. All rights reserved.
 * 
 * This software is licensed under the Berkley Software Distribution (BSD) 
 * 3-Clause license. Redistribution and use in source and binary forms, 
 * with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE. 
 */

#include "rimot_pin_aliases.h"


/* 
    "table driven software is a 
    clever way to replace 
    bugs with boredom"

    - Anonymous 
*/

#if defined(STM32F411RE)    /* Production mcu. LQFP64 */
#define PACKAGE_PIN_COUNT 64

// @todo EXACT SAME THING BUT FOR THE TARGET MCU PACKAGE 

#error PLEASE DEFINE THE MCU_PIN_#->PORT MAP IN rimot_gpio.c FOR STM32F411RE

#elif defined(STM32F411VE) /* Eval board MCU, LQFP100 */

static const struct pin_map pin_alias_map[PACKAGE_PIN_COUNT] = 
{
    [MCUPIN_PE2] =  {.port_idx = GPIO_PORT_IDX_E, .bit = 2 },
    [MCUPIN_PE3] =  {.port_idx = GPIO_PORT_IDX_E, .bit = 3 },
    [MCUPIN_PE4] =  {.port_idx = GPIO_PORT_IDX_E, .bit = 4 },
    [MCUPIN_PE5] =  {.port_idx = GPIO_PORT_IDX_E, .bit = 5 },
    [MCUPIN_PE6] =  {.port_idx = GPIO_PORT_IDX_E, .bit = 6 },
    [MCUPIN_PC13] = {.port_idx = GPIO_PORT_IDX_C, .bit = 13},
    [MCUPIN_PC14] = {.port_idx = GPIO_PORT_IDX_C, .bit = 14},
    [MCUPIN_PC15] = {.port_idx = GPIO_PORT_IDX_C, .bit = 15},
    [MCUPIN_PH0] =  {.port_idx = GPIO_PORT_IDX_H, .bit = 0 },
    [MCUPIN_PH1] =  {.port_idx = GPIO_PORT_IDX_H, .bit = 1 },
    [MCUPIN_PC0] =  {.port_idx = GPIO_PORT_IDX_C, .bit = 0 },
    [MCUPIN_PC1] =  {.port_idx = GPIO_PORT_IDX_C, .bit = 1 },
    [MCUPIN_PC2] =  {.port_idx = GPIO_PORT_IDX_C, .bit = 2 },
    [MCUPIN_PC3] =  {.port_idx = GPIO_PORT_IDX_C, .bit = 3 },
    [MCUPIN_PA0] =  {.port_idx = GPIO_PORT_IDX_A, .bit = 0 },
    [MCUPIN_PA1] =  {.port_idx = GPIO_PORT_IDX_A, .bit = 1 },
    [MCUPIN_PA2] =  {.port_idx = GPIO_PORT_IDX_A, .bit = 2 },
    [MCUPIN_PA3] =  {.port_idx = GPIO_PORT_IDX_A, .bit = 3 },
    [MCUPIN_PA4] =  {.port_idx = GPIO_PORT_IDX_A, .bit = 4 },
    [MCUPIN_PA5] =  {.port_idx = GPIO_PORT_IDX_A, .bit = 5 },
    [MCUPIN_PA6] =  {.port_idx = GPIO_PORT_IDX_A, .bit = 6 },
    [MCUPIN_PA7] =  {.port_idx = GPIO_PORT_IDX_A, .bit = 7 },
    [MCUPIN_PC4] =  {.port_idx = GPIO_PORT_IDX_C, .bit = 4 },
    [MCUPIN_PC5] =  {.port_idx = GPIO_PORT_IDX_C, .bit = 5 },
    [MCUPIN_PB0] =  {.port_idx = GPIO_PORT_IDX_B, .bit = 0 },
    [MCUPIN_PB1] =  {.port_idx = GPIO_PORT_IDX_B, .bit = 1 },
    [MCUPIN_PB2] =  {.port_idx = GPIO_PORT_IDX_B, .bit = 2 },
    [MCUPIN_PE7] =  {.port_idx = GPIO_PORT_IDX_E, .bit = 7 },
    [MCUPIN_PE8] =  {.port_idx = GPIO_PORT_IDX_E, .bit = 8 },
    [MCUPIN_PE9] =  {.port_idx = GPIO_PORT_IDX_E, .bit = 9 },
    [MCUPIN_PE10] = {.port_idx = GPIO_PORT_IDX_E, .bit = 10},
    [MCUPIN_PE11] = {.port_idx = GPIO_PORT_IDX_E, .bit = 11},
    [MCUPIN_PE12] = {.port_idx = GPIO_PORT_IDX_E, .bit = 12},
    [MCUPIN_PE13] = {.port_idx = GPIO_PORT_IDX_E, .bit = 13},
    [MCUPIN_PE14] = {.port_idx = GPIO_PORT_IDX_E, .bit = 14},
    [MCUPIN_PE15] = {.port_idx = GPIO_PORT_IDX_E, .bit = 15},
    [MCUPIN_PB10] = {.port_idx = GPIO_PORT_IDX_B, .bit = 10},
    [MCUPIN_PB12] = {.port_idx = GPIO_PORT_IDX_B, .bit = 12},
    [MCUPIN_PB13] = {.port_idx = GPIO_PORT_IDX_B, .bit = 13},
    [MCUPIN_PB14] = {.port_idx = GPIO_PORT_IDX_B, .bit = 14},
    [MCUPIN_PB15] = {.port_idx = GPIO_PORT_IDX_B, .bit = 15},
    [MCUPIN_PD8] =  {.port_idx = GPIO_PORT_IDX_D, .bit = 8 },
    [MCUPIN_PD9] =  {.port_idx = GPIO_PORT_IDX_D, .bit = 9 },
    [MCUPIN_PD10] = {.port_idx = GPIO_PORT_IDX_D, .bit = 10},
    [MCUPIN_PD11] = {.port_idx = GPIO_PORT_IDX_D, .bit = 11},
    [MCUPIN_PD12] = {.port_idx = GPIO_PORT_IDX_D, .bit = 12},
    [MCUPIN_PD13] = {.port_idx = GPIO_PORT_IDX_D, .bit = 13},
    [MCUPIN_PD14] = {.port_idx = GPIO_PORT_IDX_D, .bit = 14},
    [MCUPIN_PD15] = {.port_idx = GPIO_PORT_IDX_D, .bit = 15},
    [MCUPIN_PC6] =  {.port_idx = GPIO_PORT_IDX_C, .bit = 6 },
    [MCUPIN_PC7] =  {.port_idx = GPIO_PORT_IDX_C, .bit = 7 },
    [MCUPIN_PC8] =  {.port_idx = GPIO_PORT_IDX_C, .bit = 8 },
    [MCUPIN_PC9] =  {.port_idx = GPIO_PORT_IDX_C, .bit = 9 },
    [MCUPIN_PA8] =  {.port_idx = GPIO_PORT_IDX_A, .bit = 8 },
    [MCUPIN_PA9] =  {.port_idx = GPIO_PORT_IDX_A, .bit = 9 },
    [MCUPIN_PA10] = {.port_idx = GPIO_PORT_IDX_A, .bit = 10},
    [MCUPIN_PA11] = {.port_idx = GPIO_PORT_IDX_A, .bit = 11},
    [MCUPIN_PA12] = {.port_idx = GPIO_PORT_IDX_A, .bit = 12},
    [MCUPIN_PA13] = {.port_idx = GPIO_PORT_IDX_A, .bit = 13},
    [MCUPIN_PA14] = {.port_idx = GPIO_PORT_IDX_A, .bit = 14},
    [MCUPIN_PA15] = {.port_idx = GPIO_PORT_IDX_A, .bit = 15},
    [MCUPIN_PC10] = {.port_idx = GPIO_PORT_IDX_C, .bit = 10},
    [MCUPIN_PC11] = {.port_idx = GPIO_PORT_IDX_C, .bit = 11},
    [MCUPIN_PC12] = {.port_idx = GPIO_PORT_IDX_C, .bit = 12},
    [MCUPIN_PD0] =  {.port_idx = GPIO_PORT_IDX_D, .bit = 0 },
    [MCUPIN_PD1] =  {.port_idx = GPIO_PORT_IDX_D, .bit = 1 },
    [MCUPIN_PD2] =  {.port_idx = GPIO_PORT_IDX_D, .bit = 2 },
    [MCUPIN_PD3] =  {.port_idx = GPIO_PORT_IDX_D, .bit = 3 },
    [MCUPIN_PD4] =  {.port_idx = GPIO_PORT_IDX_D, .bit = 4 },
    [MCUPIN_PD5] =  {.port_idx = GPIO_PORT_IDX_D, .bit = 5 },
    [MCUPIN_PD6] =  {.port_idx = GPIO_PORT_IDX_D, .bit = 6 },
    [MCUPIN_PD7] =  {.port_idx = GPIO_PORT_IDX_D, .bit = 7 },
    [MCUPIN_PB3] =  {.port_idx = GPIO_PORT_IDX_B, .bit = 3 },
    [MCUPIN_PB4] =  {.port_idx = GPIO_PORT_IDX_B, .bit = 4 },
    [MCUPIN_PB5] =  {.port_idx = GPIO_PORT_IDX_B, .bit = 5 },
    [MCUPIN_PB6] =  {.port_idx = GPIO_PORT_IDX_B, .bit = 6 },
    [MCUPIN_PB7] =  {.port_idx = GPIO_PORT_IDX_B, .bit = 7 },
    [MCUPIN_PB8] =  {.port_idx = GPIO_PORT_IDX_B, .bit = 8 },
    [MCUPIN_PB9] =  {.port_idx = GPIO_PORT_IDX_B, .bit = 9 },
    [MCUPIN_PE0] =  {.port_idx = GPIO_PORT_IDX_E, .bit = 0 },
    [MCUPIN_PE1] =  {.port_idx = GPIO_PORT_IDX_E, .bit = 1 },
};
#else
#error NEITHER STM32F411RE NOR STM32F411VE IS DEFINED. PLEASE SEE rimot_gpio.c
#endif /* PACKAGE BASED PIN ALIASES */


struct pin_map pin_aliasLookup(uint32_t mcu_pin_number)
{       
#if !defined(NDEBUG)    /* In debug build we're validating the lookup index */
    switch(mcu_pin_number)
    {
    case MCUPIN_PE2  :
    case MCUPIN_PE3  :
    case MCUPIN_PE4  :
    case MCUPIN_PE5  :
    case MCUPIN_PE6  :
    case MCUPIN_PC13 :
    case MCUPIN_PC14 :
    case MCUPIN_PC15 :
    case MCUPIN_PH0  :
    case MCUPIN_PH1  :
    case MCUPIN_PC0  :
    case MCUPIN_PC1  :
    case MCUPIN_PC2  :
    case MCUPIN_PC3  :
    case MCUPIN_PA0  :
    case MCUPIN_PA1  :
    case MCUPIN_PA2  :
    case MCUPIN_PA3  :
    case MCUPIN_PA4  :
    case MCUPIN_PA5  :
    case MCUPIN_PA6  :
    case MCUPIN_PA7  :
    case MCUPIN_PC4  :
    case MCUPIN_PC5  :
    case MCUPIN_PB0  :
    case MCUPIN_PB1  :
    case MCUPIN_PB2  :
    case MCUPIN_PE7  :
    case MCUPIN_PE8  :
    case MCUPIN_PE9  :
    case MCUPIN_PE10 :
    case MCUPIN_PE11 :
    case MCUPIN_PE12 :
    case MCUPIN_PE13 :
    case MCUPIN_PE14 :
    case MCUPIN_PE15 :
    case MCUPIN_PB10 :
    case MCUPIN_PB12 :
    case MCUPIN_PB13 :
    case MCUPIN_PB14 :
    case MCUPIN_PB15 :
    case MCUPIN_PD8  :
    case MCUPIN_PD9  :
    case MCUPIN_PD10 :
    case MCUPIN_PD11 :
    case MCUPIN_PD12 :
    case MCUPIN_PD13 :
    case MCUPIN_PD14 :
    case MCUPIN_PD15 :
    case MCUPIN_PC6  :
    case MCUPIN_PC7  :
    case MCUPIN_PC8  :
    case MCUPIN_PC9  :
    case MCUPIN_PA8  :
    case MCUPIN_PA9  :
    case MCUPIN_PA10 :
    case MCUPIN_PA11 :
    case MCUPIN_PA12 :
    case MCUPIN_PA13 :
    case MCUPIN_PA14 :
    case MCUPIN_PA15 :
    case MCUPIN_PC10 :
    case MCUPIN_PC11 :
    case MCUPIN_PC12 :
    case MCUPIN_PD0  :
    case MCUPIN_PD1  :
    case MCUPIN_PD2  :
    case MCUPIN_PD3  :
    case MCUPIN_PD4  :
    case MCUPIN_PD5  :
    case MCUPIN_PD6  :
    case MCUPIN_PD7  :
    case MCUPIN_PB3  :
    case MCUPIN_PB4  :
    case MCUPIN_PB5  :
    case MCUPIN_PB6  :
    case MCUPIN_PB7  :
    case MCUPIN_PB8  :
    case MCUPIN_PB9  :
    case MCUPIN_PE0  :
    case MCUPIN_PE1  :
        return pin_alias_map[mcu_pin_number];
        break;
    default:
        while(1)
        {
            /* HANG SO PROGRAMMER CAN FIND THE LOGIC ERROR */
        }
    }
#else
    return pin_alias_map[mcu_pin_number];
#endif /* DEBUG BUILD */
}
