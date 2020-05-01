/**
 * @file rimot_mcu_dbg.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This module provides a low level "driver" for accessing the mcu
 * debug registers on the stm32f411xe Microcontroller
 * @version 0.1
 * @date 2020-04-02
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

#if !defined(USE_HAL_DRIVER)

#include <stdint.h>

#include "rimot_mcu_dbg.h"
#include "rimot_mcu_dbg_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_LL_debug.h"


/* Not ideal but this doesn't actually address relative to a memory region */
#define DBGMCU_BASE 0xE0042000UL 

struct mcu_debug_regs
{   
    /*!< MCU device ID code,               Address offset: 0x00 */
    volatile uint32_t IDCODE; 

    /*!< Debug MCU configuration register, Address offset: 0x04 */
    volatile uint32_t CR;  

    /*!< Debug MCU APB1 freeze register,   Address offset: 0x08 */
    volatile uint32_t APB1FZ;  

    /*!< Debug MCU APB2 freeze register,   Address offset: 0x0C */
    volatile uint32_t APB2FZ;  
};

#define _MCUDBG ((struct mcu_debug_regs*) DBGMCU_BASE)


#endif /* !USE_HAL_DRIVER */
