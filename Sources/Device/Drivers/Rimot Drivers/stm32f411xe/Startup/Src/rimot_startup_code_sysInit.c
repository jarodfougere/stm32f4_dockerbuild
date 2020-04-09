/**
 * @file rimot_startup_code_sysInit.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This file provides the startup code for the function "SystemInit"
 * which is part of the bootstrap call tree before the entry to main.
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include "rimot_cortex_hardware_config.h"

#include "rimot_region_base_addresses.h"

#include "rimot_cortex_header.h"

/**
 * @brief Sets up the minimum configuration in the system control block.
 * @note you wont find this in any of the mainline call tree.
 * It is part of BOOTSTRAP call tree.
 */
void SystemInit(void)   /* DON'T FREAKING TOUCH THIS. NOT EVEN THE NAME */
{
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    /* set CP10 and CP11 Full Access */
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  
#endif

    /* Vector Table Internal FLASH (Update system control block VTAB alias) */
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; 
}