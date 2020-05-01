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

#include <stdint.h>

#include "rimot_crc.h"
#include "rimot_crc_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"

#include "rimot_register_padding.h"
#include "rimot_bus_region_offsets.h"

#define CRC_BASE (AHB1PERIPH_BASE + 0x3000UL)

#define CRC_IDR_MSK (0x000000FF) /* Only first 8 bits are used */

#define _CRC ((struct crc_regs *)CRC_BASE)

/* PAGE 68 STM32F411 REFERENCE MANUAL */
struct crc_regs
{
    volatile uint32_t DR;  /* Data register.            */
    volatile uint32_t IDR; /* Independent data register */
    volatile uint32_t CR;  /* Control register          */
};
