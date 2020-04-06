/**
 * @file rimot_dma.c
 * @author Carl Mattatall
 * @brief This source module provides a low-level "driver" for the 
 * DMA peripheral on the stm32f411xe microcontroller
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io
 */

#include "rimot_dma.h"
#include "rimot_dma_register_masks.h"
#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"


#define __HAL_RCC_DMA1_CLK_DISABLE()         (RCC->AHB1ENR &= ~(RCC_AHB1ENR_DMA1EN))
#define __HAL_RCC_DMA2_CLK_DISABLE()         (RCC->AHB1ENR &= ~(RCC_AHB1ENR_DMA2EN))