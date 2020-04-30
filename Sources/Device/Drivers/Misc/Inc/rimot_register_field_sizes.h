#ifndef RIMOT_MCU_PERIPHERAL_REGS
#define RIMOT_MCU_PERIPHERAL_REGS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#if defined(MCU_APP)

#include <stdint.h>
#include <limits.h>

#include "ATTRIBUTE_PORTABILITY_HEADER.h"

#define __PADDING_WORD_ALIGNMENT 4
#define __PAD_ABS(a,b) (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))
#define __PAD_MIN(a,b) (((a) > (b)) ? (b) : (a))
#define __PAD_MAX(a,b) (((a) > (b)) ? (a) : (b))

/* Padding fields */
typedef uint64_t pad64;
typedef uint32_t pad32;
typedef uint16_t pad16;
typedef uint8_t  pad8;

/* Structure field padding macro */
#define PAD_BETWEEN(NAME, a,b) pad8 _ ## NAME ## _struct_base_offset_ ## a ## _\
## to ## _ ## b ## _ ## padding[((a - b) > 0) ? (((uint32_t)(a - b)/ \
sizeof(pad8)) - 1) : (((uint32_t)(b - a)/sizeof(pad8)) - 1)]

#define PAD_WITH_BYTES(a, b) uint8_t                              \
_______ ## a ## __ ## b ##_align                                  \
[                                                                 \
__PAD_ABS((a), (b)) - (__PADDING_WORD_ALIGNMENT)                  \
]

/* 
 * We subtract word alignment (in bytes) because
 * the compiler needs to align the lower field 
 * of the padded region 
 */

#endif /* MCU_APP */
#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_PERIPHERAL_REGS */
