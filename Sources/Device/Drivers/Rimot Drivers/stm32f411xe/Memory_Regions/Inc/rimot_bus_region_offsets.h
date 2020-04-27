#ifndef RIMOT_BUS_OFFSETS
#define RIMOT_BUS_OFFSETS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */


#include "rimot_region_base_addresses.h"

/* SEE PAGE 53 OF DATASHEET AND PAGE 38 OF REFERENCE MANUAL */

/* Advanced peripheral bus 1 base */
#define APB1PERIPH_BASE       PERIPH_BASE

/* Advance peripheral bus 2 base */
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)

/* Advanced highspeed bus 1 base */
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)

/* Advanced highspeed bus 2 base */
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x10000000UL)


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_BUS_OFFSETS */
