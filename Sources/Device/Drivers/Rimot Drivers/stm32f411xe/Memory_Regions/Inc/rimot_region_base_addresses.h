#ifndef RIMOT_REGION_BASE_ADDRESSES
#define RIMOT_REGION_BASE_ADDRESSES
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>

/* SEE PAGE 53 OF DATASHEET AND PAGE 38 OF REFERENCE MANUAL */

/* FLASH(up to 1 MB) base address in the alias region */
#define FLASH_BASE            0x08000000UL 

/* SRAM1(128 KB) base address in the alias region */
#define SRAM1_BASE            0x20000000UL 

/* Peripheral base address in the alias region */
#define PERIPH_BASE           0x40000000UL 

/* SRAM1(128 KB) base address in the bit-band region*/
#define SRAM1_BB_BASE         0x22000000UL 

/* Peripheral base address in the bit-band region */
#define PERIPH_BB_BASE        0x42000000UL 

/* Backup SRAM(4 KB) base address in the bit-band region*/
#define BKPSRAM_BB_BASE       0x42480000UL 

/* FLASH end address */
#define FLASH_END             0x0807FFFFUL 

/* Base address of : (up to 528 Bytes) embedded FLASH OTP Area*/
#define FLASH_OTP_BASE        0x1FFF7800UL 

/* End address of : (up to 528 Bytes) embedded FLASH OTP Area */
#define FLASH_OTP_END         0x1FFF7A0FUL 


#define VECT_TAB_OFFSET  0x00


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_REGION_BASE_ADDRESSES */