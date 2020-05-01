#ifndef RIMOT_MCU_PERIPHERAL_REGS
#define RIMOT_MCU_PERIPHERAL_REGS
#ifdef __cplusplus
extern "C"
{
#endif /* C linkage */
#if defined(MCU_APP)

#include <stdint.h>
#include <limits.h>

#include "ATTRIBUTE_PORTABILITY_HEADER.h"

#define __PADDING_WORD_ALIGNMENT 4
#define __PAD_ABS(a, b) (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))
#define __PAD_MIN(a, b) (((a) > (b)) ? (b) : (a))
#define __PAD_MAX(a, b) (((a) > (b)) ? (a) : (b))

#define PAD_BETWEEN(NAME, a, b) uint8_t _##NAME##_struct_base_offset_##a##_##to##_##b##_##padding[((a - b) > 0) ? (((uint32_t)(a - b) / \
                                                                                                                    sizeof(uint8_t)) -  \
                                                                                                                   1)                   \
                                                                                                                : (((uint32_t)(b - a) / sizeof(uint8_t)) - 1)]

#define PAD_WITH_BYTES(a, b) uint8_t \
    _##a##_##b##_align               \
        [__PAD_ABS((a), (b)) - (__PADDING_WORD_ALIGNMENT)]

#endif /* MCU_APP */
#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_PERIPHERAL_REGS */
