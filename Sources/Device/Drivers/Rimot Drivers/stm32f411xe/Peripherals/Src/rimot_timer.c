/**
 * @file rimot_timer.c
 * @author Carl Mattatall
 * @brief This source module provides a low level driver for
 * interfacing with the timers on the stm32f411re microcontroller
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include "rimot_timer.h"
#include "rimot_timer_register_masks.h"
#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"