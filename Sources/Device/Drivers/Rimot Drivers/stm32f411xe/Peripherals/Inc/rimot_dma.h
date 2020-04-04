#ifndef RIMOT_DMA
#define RIMOT_DMA
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/*
 *******************************************************************************
 *
 * DMA Features (PAGE 166)
 * 
 *     • Dual AHB master bus architecture, one dedicated to memory accesses
 *       and one dedicated to peripheral accesses.
 *     • AHB slave programming interface supporting only 32-bit accesses
 *     • 8 streams for each DMA controller, up to 8 channels (requests) per 
 *       stream
 *     • Four-word depth 32 first-in, first-out memory buffers (FIFOs) per 
 *       stream, that can be used in FIFO mode or direct mode:
 *         – FIFO mode: with threshold level software selectable between 1/4,
 *           1/2 or 3/4 of the FIFO size
 *         – Direct mode Each DMA request immediately initiates a transfer 
 *           from/to the memory. When it is configured in direct mode (FIFO
 *           disabled), to transfer data in memory-toperipheral mode, the DMA 
 *           preloads only one data from the memory to the internal DMA 
 *           controller (DMA) RM0383 166/844 RM0383 Rev 3 FIFO to ensure an
 *           immediate data transfer as soon as a DMA request is triggered by
 *           a peripheral.
 *     • Each stream can be configured by hardware to be:
 *         – a regular channel that supports peripheral-to-memory, 
 *           memory-to-peripheral and memory-to-memory transfers
 *         – a double buffer channel that also supports double buffering on
 *           the memory side
 *     • Each of the 8 streams are connected to dedicated hardware DMA
 *       channels (requests)
 *     • Priorities between DMA stream requests are software-programmable (4 
 *       levels consisting of very high, high, medium, low) or hardware in
 *       case of equality (request 0 has priority over request 1, etc.)
 *     • Each stream also supports software trigger for memory-to-memory 
 *       transfers (only available for the DMA2 controller)
 *     • Each stream request can be selected among up to 8 possible channel
 *       requests. This selection is software-configurable and allows several
 *       peripherals to initiate DMA requests
 *     • The number of data items to be transferred can be managed either by 
 *       the DMA controller or by the peripheral:
 *         – DMA flow controller: the number of data items to be transferred 
 *           is softwareprogrammable from 1 to 65535
 *         – Peripheral flow controller: the number of data items to be 
 *           transferred is unknown and controlled by the source or the 
 *           destination peripheral that signals the end of the transfer by 
 *           hardware
 *     • Independent source and destination transfer width (byte, half-word,
 *       word): when the data widths of the source and destination are not 
 *       equal, the DMA automatically packs/unpacks the necessary transfers to 
 *       optimize the bandwidth. This feature is only available in FIFO mode
 *     • Incrementing or non-incrementing addressing for source and destination
 *     • Supports incremental burst transfers of 4, 8 or 16 beats. The size of 
 *       the burst is software-configurable, usually equal to half the FIFO 
 *       size of the peripheral
 *     • Each stream supports circular buffer management
 *     • 5 event flags (DMA Half Transfer, DMA Transfer complete, DMA Transfer 
 *       Error, DMA FIFO Error, Direct Mode Error) logically ORed together in
 *       a single interrupt request for each stream
 * 
 *******************************************************************************
 *
 * DMA transactions
 * 
 * A DMA transaction consists of a sequence of a given number of data
 * transfers. The number of data items to be transferred and their width
 * (8-bit, 16-bit or 32-bit) are softwareprogrammable.
 * Each DMA transfer consists of three operations:
 *     • A loading from the peripheral data register or a location in memory, 
 *     addressed through the DMA_SxPAR or DMA_SxM0AR register
 *     • A storage of the data loaded to the peripheral data register or a 
 *     location in memory addressed through the DMA_SxPAR or DMA_SxM0AR 
 *     register
 *     • A post-decrement of the DMA_SxNDTR register, which contains the 
 *     number of transactions that still have to be performed After an event, 
 *     the peripheral sends a request signal to the DMA controller. The DMA
 *     controller serves the request depending on the channel priorities. As 
 *     soon as the DMA controller accesses the peripheral, an Acknowledge 
 *     signal is sent to the peripheral by the DMA controller. The peripheral 
 *     releases its request as soon as it gets the Acknowledge signal from the
 *     DMA controller. Once the request has been deasserted by the peripheral,
 *     the DMA controller releases the Acknowledge signal. If there are more
 *     requests, the peripheral can initiate the next transaction.
 * 
 *******************************************************************************
 * 
 * Arbiter
 * 
 * An arbiter manages the 8 DMA stream requests based on their priority for 
 * each of the two AHB master ports (memory and peripheral ports) and launches
 * the peripheral/memory access sequences.
 * Priorities are managed in two stages:
 *     • Software: each stream priority can be configured in the DMA_SxCR 
 *     register. There are four levels:
 *     – Very high priority
 *     – High priority
 *     – Medium priority
 *     – Low priority
 * • Hardware: If two requests have the same software priority level, the 
 *   stream with the lower number takes priority over the stream with the higher
 *   number. For example, Stream 2 takes priority over Stream 4
 * 
 *******************************************************************************
 *
 * DMA streams
 * 
 * Each of the 8 DMA controller streams provides a unidirectional transfer 
 * link between a source and a destination. Each stream can be configured to 
 * perform:
 *     • Regular type transactions: memory-to-peripherals, 
 *       peripherals-to-memory or memoryto-memory transfers
 *     • Double-buffer type transactions: double buffer transfers using two 
 *       memory pointers for the memory (while the DMA is reading/writing from/
 *       to a buffer, the application can write/read to/from the other buffer).
 *
 * The amount of data to be transferred (up to 65535) is programmable and 
 * related to the source width of the peripheral that requests the DMA 
 * transfer connected to the peripheral AHB port. The register that contains 
 * the amount of data items to be transferred is decremented after each 
 * transaction.
 * 
 *******************************************************************************
 * 
 * Stream configuration procedure
 * 
 * The following sequence should be followed to configure a DMA stream x 
 * (where x is the stream number):
 *
 *     1. If the stream is enabled, disable it by resetting the EN bit in the 
 *        DMA_SxCR register, Then read this bit in order to confirm that there 
 *        is no ongoing stream operation. Writing this bit to 0 is not 
 *        immediately effective since it is actually written to 0 once all the 
 *        current transfers have finished. When the EN bit is read as 0, this 
 *        means that the stream is ready to be configured. It is therefore 
 *        necessary to wait for the EN bit to be cleared before starting any 
 *        stream configuration. All the stream dedicated bits set in the 
 *        status register (DMA_LISR and DMA_HISR) from the previous data block 
 *        DMA transfer should be cleared before the stream can be re-enabled.
 *
 *     2. Set the peripheral port register address in the DMA_SxPAR register. 
 *        The data will be moved from/ to this address to/ from the peripheral 
 *        port after the peripheral event.
 *
 *     3. Set the memory address in the DMA_SxMA0R register (and in the 
 *        DMA_SxMA1R register in the case of a double buffer mode). The data 
 *        will be written to or read from this memory after the peripheral 
 *        event.
 *
 *     4. Configure the total number of data items to be transferred in the 
 *        DMA_SxNDTR register. After each peripheral event or each beat of the 
 *        burst, this value is decremented.
 *
 *     5. Select the DMA channel (request) using CHSEL[2:0] in the DMA_SxCR 
 *        register.
 *
 *     6. If the peripheral is intended to be the flow controller and if it 
 *        supports this feature, set the PFCTRL bit in the DMA_SxCR register.
 *
 *     7. Configure the stream priority using the PL[1:0] bits in the DMA_SxCR 
 *        register.
 *     8. Configure the FIFO usage (enable or disable, threshold in   
 *        transmission and reception)
 *
 *     9. Configure the data transfer direction, peripheral and memory   
 *        incremented/fixed mode, single or burst transactions, peripheral and 
 *        memory data widths, Circular mode, Double buffer mode and interrupts 
 *        after half and/or full transfer, and/or errors in thE DMA_SxCR 
 *        register
 *
 *     10. Activate the stream by setting the EN bit in the DMA_SxCR register.
 *
 * As soon as the stream is enabled, it can serve any DMA request from the 
 * peripheral connected to the stream. Once half the data have been 
 * transferred on the AHB destination port, the half-transfer flag (HTIF) is 
 * set and an interrupt is generated if the half-transfer interrupt enable bit 
 * (HTIE) is set. At the end of the transfer, the transfer complete flag 
 * (TCIF) is set and an interrupt is generated if the transfer complete 
 * interrupt enable bit (TCIE) is set.
 *
 * ############################################################################
 * ###                                 Warning:                             ###
 * ###                                                                      ###
 * ###   To switch off a peripheral connected to a DMA stream request, it   ###
 * ###   request, it is mandatory to, first, switch off the DMA stream to   ###
 * ###   which the peripheral is connected, then to wait for EN bit = 0.    ###
 * ###                                                                      ###
 * ###          Only then can the peripheral be safely disabled.            ###
 * ############################################################################
 *
 *******************************************************************************
 * 
 */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"


#define DMA1_BASE (AHB1PERIPH_BASE + 0x6000UL)
#define DMA2_BASE (AHB1PERIPH_BASE + 0x6400UL)

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


/*
 * The DMA Transfer size.
 * DMA_XFER_SIZE_byte = 8 bits transferred at a time
 * DMA_XFER_SIZE_halfword = 16 bits transferred at a time
 * DMA_XFER_SIZE_word = 32 bits transferred at a time
 */
typedef enum
{
    DMA_XFER_SIZE_byte,
    DMA_XFER_SIZE_halfword,
    DMA_XFER_SIZE_word,
}   DMA_XFER_SIZE_t;


typedef enum
{
    DMA_CB_TYPE_xfer_done,
    DMA_CB_TYPE_xfer_half,
    DMA_CB_TYPE_xfer_err,
    DMA_CB_TYPE_bufferflow,
    DMA_CB_TYPE_direct_err,
}   DMA_CB_TYPE_t;


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_DMA */