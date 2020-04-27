#ifndef RIMOT_DMA
#define RIMOT_DMA
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

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
