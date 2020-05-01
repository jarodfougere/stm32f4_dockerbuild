/**
 * @file rimot_dma.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low-level "driver" for the 
 * DMA peripheral on the stm32f411xe microcontroller
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io
 */
#include <stdint.h>

#include "rimot_dma.h"
#include "rimot_dma_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_LL_debug.h"

#define DMA1_BASE (AHB1PERIPH_BASE + 0x6000UL)
#define DMA2_BASE (AHB1PERIPH_BASE + 0x6400UL)

/* Indices 0 through 7 */
#define NUM_DMA_STREAMS_PER_INSTANCE (8) 

/* PAGE 187 REFERENCE MANUAL */
struct dma_regs
{   
    volatile uint32_t LISR;     /* Low interrupt status register      */
    volatile uint32_t HISR;     /* High interrupt status register     */
    volatile uint32_t LIFCR;    /* Low interrupt flag clear register  */
    volatile uint32_t HIFCR;    /* High interrupt flag clear register */
    struct           /* DMA Steams */
    {
        volatile uint32_t CR;   /* Configuration register                              */
        volatile uint32_t NDTR; /* Number of data to transfer register.                */
        volatile uint32_t PAR;  /* Parent address reg (where data coming from)         */
        volatile uint32_t MAR0; /* Memory addr register 0                              */
        volatile uint32_t MAR1; /* Memory addr register 1 (used in double buffer mode) */
        volatile uint32_t FCR;  /* FIFO Control Register                               */
    }   STREAM[NUM_DMA_STREAMS_PER_INSTANCE];
};

/* Instance declaration */
#define _DMA1 ((struct dma_regs*) DMA1_BASE)
#define _DMA2 ((struct dma_regs*) DMA2_BASE)


#if !defined(USE_HAL_DRIVER)
void DMA1_Stream0_IRQHandler(void)
{

}

void DMA1_Stream1_IRQHandler(void)
{

}

void DMA1_Stream2_IRQHandler(void)
{

}

void DMA1_Stream3_IRQHandler(void)
{

}

void DMA1_Stream4_IRQHandler(void)
{

}

void DMA1_Stream5_IRQHandler(void)
{

}

void DMA1_Stream6_IRQHandler(void)
{

}


void DMA1_Stream7_IRQHandler(void)
{

}




void DMA2_Stream0_IRQHandler(void)
{

}

void DMA2_Stream1_IRQHandler(void)
{

}

void DMA2_Stream2_IRQHandler(void)
{

}

void DMA2_Stream3_IRQHandler(void)
{

}

void DMA2_Stream4_IRQHandler(void)
{

}

void DMA2_Stream5_IRQHandler(void)
{

}

void DMA2_Stream6_IRQHandler(void)
{

}

void DMA2_Stream7_IRQHandler(void)
{

}
#endif