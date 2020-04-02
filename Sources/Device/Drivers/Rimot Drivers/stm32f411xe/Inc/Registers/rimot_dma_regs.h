#ifndef RIMOT_DMA
#define RIMOT_DMA
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"


#define DMA1_BASE (AHB1PERIPH_BASE + 0x6000UL)
#define DMA2_BASE (AHB1PERIPH_BASE + 0x6400UL)

/* 
 * PUTTING THESE HERE SO I CAN CHECK AGAINST THE ADDRESSES
 * I COMPUTED IN CASE THERES AN ERROR.
 * 
 * DMA2_Stream0_BASE (DMA2_BASE + 0x010UL)
 * DMA2_Stream1_BASE (DMA2_BASE + 0x028UL)
 * DMA2_Stream2_BASE (DMA2_BASE + 0x040UL)
 * DMA2_Stream3_BASE (DMA2_BASE + 0x058UL)
 * DMA2_Stream4_BASE (DMA2_BASE + 0x070UL)
 * DMA2_Stream5_BASE (DMA2_BASE + 0x088UL)
 * DMA2_Stream6_BASE (DMA2_BASE + 0x0A0UL)
 * DMA2_Stream7_BASE (DMA2_BASE + 0x0B8UL)
 *
 * DMA1_Stream0_BASE (DMA1_BASE + 0x010UL)
 * DMA1_Stream1_BASE (DMA1_BASE + 0x028UL)
 * DMA1_Stream2_BASE (DMA1_BASE + 0x040UL)
 * DMA1_Stream3_BASE (DMA1_BASE + 0x058UL)
 * DMA1_Stream4_BASE (DMA1_BASE + 0x070UL)
 * DMA1_Stream5_BASE (DMA1_BASE + 0x088UL)
 * DMA1_Stream6_BASE (DMA1_BASE + 0x0A0UL)
 * DMA1_Stream7_BASE (DMA1_BASE + 0x0B8UL)
 */

/* Indices 0 through 7 */
#define NUM_DMA_STREAMS_PER_INSTANCE (8) 

/* PAGE 187 REFERENCE MANUAL */
struct dma_regs
{   
    hw_reg LISR;     /* Low interrupt status register      */
    hw_reg HISR;     /* High interrupt status register     */
    hw_reg LIFCR;    /* Low interrupt flag clear register  */
    hw_reg HIFCR;    /* High interrupt flag clear register */
    struct           /* DMA Steams */
    {
        hw_reg CR;   /* Configuration register                              */
        hw_reg NDTR; /* Number of data to transfer register.                */
        hw_reg PAR;  /* Parent address reg (where data coming from)         */
        hw_reg MAR0; /* Memory addr register 0                              */
        hw_reg MAR1; /* Memory addr register 1 (used in double buffer mode) */
        hw_reg FCR;  /* FIFO Control Register                               */
    }   STREAM[NUM_DMA_STREAMS_PER_INSTANCE];
};

/* Instance declaration */
#define _DMA1 ((struct dma_regs*) DMA1_BASE)
#define _DMA2 ((struct dma_regs*) DMA2_BASE)

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_DMA */