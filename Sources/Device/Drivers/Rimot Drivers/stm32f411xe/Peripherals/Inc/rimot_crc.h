#ifndef RIMOT_MCU_CRC
#define RIMOT_MCU_CRC
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

#define CRC_BASE (AHB1PERIPH_BASE + 0x3000UL)


/* PAGE 68 STM32F411 REFERENCE MANUAL */
struct crc_regs
{           
    hw_reg DR;  /* Data register.            */
    hw_reg IDR; /* Independent data register */
    hw_reg CR;  /* Control register          */
};

#define CRC_IDR_MSK (0x000000FF) /* Only first 8 bits are used */

#define _CRC ((struct crc_regs*) CRC_BASE)


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_CRC */