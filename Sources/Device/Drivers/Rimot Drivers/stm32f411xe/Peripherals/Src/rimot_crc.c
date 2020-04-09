/**
 * @file rimot_crc.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level "driver" for the 
 * CRC (cyclical redundancy checksum) functionality of the microcontroller
 * (stm32f411RE)
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io
 * 
 */

#include "rimot_crc.h"
#include "rimot_crc_register_masks.h"
#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"