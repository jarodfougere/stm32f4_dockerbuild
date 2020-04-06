#ifndef RIMOT_MCU_PERIPHERAL_REGS
#define RIMOT_MCU_PERIPHERAL_REGS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>
#include <limits.h>

/* Microcontroller word size */
typedef uint32_t mcu_word;
typedef uint64_t mcu_long;
typedef uint16_t mcu_short;
typedef uint8_t  mcu_byte;

/* Padding fields */
typedef uint64_t pad64;
typedef uint32_t pad32;
typedef uint16_t pad16;
typedef uint8_t  pad8;

/* Structure field padding macro */
#define PAD_BETWEEN(NAME, a,b) pad8 _ ## NAME ## _struct_base_offset_ ## a ## _\
## to ## _ ## b ## _ ## padding[((a - b) > 0) ? ((((unsigned)a - (unsigned)b)/ \
sizeof(pad8)) - 1) : ((((unsigned)b - (unsigned)a)/sizeof(pad8)) - 1)]

/* SOFTWARE LONG */
typedef mcu_long sw_long;
typedef mcu_word sw_reg;
typedef mcu_byte sw_byte;

/* Hardware registers (can change without compiler being aware */
typedef volatile mcu_byte hw_byte;
typedef volatile mcu_word hw_reg;    
typedef volatile mcu_long hw_wide_reg;   /* Wide register (hi and lo words) */

/* If I ever have to write code for a DSP again where a byte is 9 bits  */
/* I'll cry myself to sleep                                             */
#if (8 == (CHAR_BIT))
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