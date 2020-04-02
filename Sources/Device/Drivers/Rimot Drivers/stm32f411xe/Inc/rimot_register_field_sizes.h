#ifndef RIMOT_MCU_PERIPHERAL_REGS
#define RIMOT_MCU_PERIPHERAL_REGS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>
#include <limits.h>

/* registers that are non volatile */
typedef uint32_t sw_reg;
typedef uint8_t  sw_byte;

/* Padding fields */
typedef uint64_t pad64;
typedef uint32_t pad32;
typedef uint16_t pad16;
typedef uint8_t  pad8;

/* Hardware registers */
typedef volatile sw_reg  hw_reg;    /* hardware can change this */


#if ((CHAR_BIT) == 8) /* Byte size platform portability check */
#define MCU_BYTES_PER_WORD (sizeof(sw_reg)/sizeof(sw_byte))
#define MCU_BYTES_PER_SHORT ((sizeof(mcu_short)/sizeof(sw_byte)))
#define MCU_BITS_PER_BYTE CHAR_BIT
#define MCU_BITS_PER_WORD CHAR_BIT*MCU_BYTES_PER_WORD
#else
#warning CHAR_BIT != 8. A BYTE IS NOT 8 BITS. CRAZY STUFF WILL HAPPEN. \
PLEASE USE uint8_t and int8_t instead of char in your application.
#endif /* BIT COUNT CHECK */

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_PERIPHERAL_REGS */