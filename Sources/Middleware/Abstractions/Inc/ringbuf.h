#ifndef CARLS_RINGBUF
#define CARLS_RINGBUF
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */


typedef unsigned char ring_var;


struct ringbuf 
{
    ring_var *base;
    ring_var *end;
    ring_var *in;
    ring_var *out;
    unsigned int in_cnt;
    unsigned int out_cnt;
};





/**
 * @brief   Transmits bytes OUT of src and INTO dst. Stops when src is empty,
 * or dst is full.
 * @param src The source ring buffer
 * @param dst The destination ring buffer
 * @return int the number of bytes copied.
 */
int ringbuf_xfer(struct ringbuf *dst, const struct ringbuf *src);


/**
 * @brief   Transmits cnt bytes OUT of src and INTO dst. Stops when src is
 * empty, dst is full, or cnt is reached.
 * @param dst  The destination ring buffer
 * @param src  The source ring buffer
 * @param cnt  The number of bytes to transfer from source to destination
 * @return int The number of bytes transferred from source to destination
 */
int ringbuf_xnfer(struct ringbuf *dst, const struct ringbuf *src, size_t cnt);


/**
 * @brief Copies the OUT bytes of src into the OUT bytes of dst,
 * 
 * @param dst 
 * @param src 
 * @return int 
 */
int ringbuf_cpyout(struct ringbuf *dst, const struct ringbuf *src);


/**
 * @brief Copies the 
 * 
 * @param dst 
 * @param src 
 * @param cnt 
 * @return int 
 */
int ringbuf_cpynout(struct ringbuf *dst, const struct ringbuf *src, size_t cnt);


int ringbufncpyin


int ringcpyin(st)



#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* CARLS_RINGBUF */