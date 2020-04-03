#ifndef RIMOT_REGISTER_BIT_OPS
#define RIMOT_REGISTER_BIT_OPS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <limits.h> /* CHAR_BIT */

#include "rimot_register_field_sizes.h"

#if (8 != CHAR_BIT)
#error THE PLATFORM WE ARE COMPILING FOR DOESNT HAVE 8 BITS TO A BYTE
#endif /* BIT COUNT CHECK */

#define BITMSK(bit) ((1 << bit))
#define ISBITSET(reg, bit) (BITMSK(bit) == (reg & BITMSK(bit)))


/* I was really proud of this as a clever way to get max val representable */
#define BITMAX(num_bits) (((mcu_word)(~0) << num_bits) ^ ((mcu_word)(~0)))


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_REGISTER_BIT_OPS */