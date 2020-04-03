#ifndef ___RIMOT_MCU_DEBUG
#define ___RIMOT_MCU_DEBUG
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

/* Not ideal but this doesn't actually address relative to a memory region */
#define DBGMCU_BASE 0xE0042000UL 

struct mcu_debug_regs
{   
    /*!< MCU device ID code,               Address offset: 0x00 */
    hw_reg IDCODE; 

    /*!< Debug MCU configuration register, Address offset: 0x04 */
    hw_reg CR;  

    /*!< Debug MCU APB1 freeze register,   Address offset: 0x08 */
    hw_reg APB1FZ;  

    /*!< Debug MCU APB2 freeze register,   Address offset: 0x0C */
    hw_reg APB2FZ;  
};

#define _MCUDBG ((struct mcu_debug_regs*) DBGMCU_BASE)

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* ___RIMOT_MCU_DEBUG */ 
