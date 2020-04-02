#ifndef RIMOT_DMA
#define RIMOT_DMA
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_region_base_addresses.h"


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



/* SEE PAGE 187 OF REFERENCE MANUAL */
struct dma_regs
{
    hw_reg LISR;
    hw_reg HISR;
    hw_reg LIFCR;
    hw_reg HIFCR;
    struct 
    {
        hw_reg CR;
        hw_reg DR;
        hw_reg PAR;
        hw_reg MAR0;
        hw_reg MAR1;
        hw_reg FCR;
    }   STREAM[NUM_DMA_STREAMS_PER_INSTANCE];
};

/* Instance declaration */
#define DMA1 ((struct dma_regs*) DMA1_BASE)
#define DMA2 ((struct dma_regs*) DMA2_BASE)

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_DMA */