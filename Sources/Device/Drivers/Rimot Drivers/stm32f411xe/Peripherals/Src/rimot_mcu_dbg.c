/**
 * @file rimot_mcu_dbg.c
 * @author Carl Mattatall
 * @brief This module provides a low level "driver" for accessing the mcu
 * debug registers on the stm32f411xe Microcontroller
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include "rimot_mcu_dbg.h"
#include "rimot_mcu_dbg_register_masks.h"
#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"