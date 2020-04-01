#ifndef RIMOT_DMA
#define RIMOT_DMA
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_peripheral_regs.h"

#define NUM_DMA_STREAMS 8 /* Indices 0 through 7 */

/* SEE PAGE 187 OF REFERENCE MANUAL */
struct dma_stream
{
    mcu_word CR;
    mcu_word DR;
    mcu_word PAR;
    mcu_word MAR0;
    mcu_word MAR1;
    mcu_word FCR;
};


struct dma_peripheral
{
    mcu_word LISR;
    mcu_word HISR;
    mcu_word LIFCR;
    mcu_word HIFCR;
    struct dma_stream stream[NUM_DMA_STREAMS];
};

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_DMA */