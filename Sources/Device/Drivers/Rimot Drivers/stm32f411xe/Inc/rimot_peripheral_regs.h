#ifndef RIMOT_MCU_PERIPHERAL_REGS
#define RIMOT_MCU_PERIPHERAL_REGS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>
#include <limits.h>


typedef uint32_t mcu_word;
typedef volatile mcu_word hw_reg;
typedef uint8_t  mcu_byte;

#if CHAR_BIT == 8 /* Bit - byte size portability check */
#define MCU_BYTES_PER_WORD (sizeof(mcu_word)/sizeof(mcu_byte))
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