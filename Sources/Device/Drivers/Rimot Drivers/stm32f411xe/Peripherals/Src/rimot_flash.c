/**
 * @file rimot_flash.c
 * @author Carl Mattatall
 * @brief This source module provides a low level "driver" for the 
 * FLASH access control peripheral on the STM32f411RE microcontrlller
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include "rimot_flash_ctl.h"
#include "rimot_flash_register_masks.h"
#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"