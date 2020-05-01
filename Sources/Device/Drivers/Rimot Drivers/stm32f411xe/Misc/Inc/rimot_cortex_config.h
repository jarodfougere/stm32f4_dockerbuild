#ifndef RIMOT_CORTEX_CONFIG
#define RIMOT_CORTEX_CONFIG
#ifdef __cplusplus
extern "C"
{
#endif /* C linkage */
#if defined(MCU_APP)

#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#if !defined(USE_HAL_DRIVER)
#include "ATTRIBUTE_PORTABILITY_HEADER.h"

/* For DSP We will use CMSIS-provided arm_math.h for cm4 (eabi armV7) */
#define ARM_MATH_CM4

#if defined(MCU_APP)

#include <stdint.h>

/* DO NOT RENAME OR TOUCH THESE. EVER!!!!! */
#if !defined(__CM4_REV)
#define __CM4_REV 1U
#else
#error A CMSIS PACK HAS ALREADY DEFINED __CM4_REV
#endif /* __CM4_REV */

#if !defined(__NVIC_PRIO_BITS)
#define __NVIC_PRIO_BITS 4U /* This is needed for CMSIS cortex compliance. */
#else
#error A CMSIS PACK HAS ALREADY DEFINED __NVIC_PRIO_BITS
#endif /* __NVIC_PRIO_BITS */

#if !defined(__FPU_PRESENT)
#define __FPU_PRESENT 1U /* (single precision) */
#else
#error A CMSIS PACK HAS ALREADY DEFINED __FPU_PRESENT
#endif

#if !defined(__Vendor_SysTickConfig)
#define __Vendor_SysTickConfig 0U
#else
#error A CMSIS PACK HAS ALREADY DEFINED __Vendor_SysTickConfig
#endif /* VENDOR SYSTICK CONFIG */

#if !defined(__MPU_PRESETN)
#define __MPU_PRESENT 1U
#else
#error A CMSIS PACK HAS ALREADY DEFINED __MPU_PRESENT
#endif

#endif /* USE_HAL_DRIVER */

/****************/
/* PCB SPECIFIC */
/****************/
#if defined(STM32F411VE)
#if defined(HSE_VALUE)
#error HSE_VALUE IS ALREADY DEFINED, \
PLEASE RESOLVE THE PREPROCESSOR CONFLICT BEFORE BUILDING
#else
#define HSE_VALUE ((uint32_t)8000000) /* 8 MHZ XTAL on the eval board */
#endif                                /* HSE_VALUE */
#elif defined(STM32F411RE)
#if defined(HSE_VALUE)
#error HSE_VALUE IS ALREADY DEFINED, \
PLEASE RESOLVE THE PREPROCESSOR CONFLICT BEFORE BUILDING
#else
#define HSE_VALUE ((uint32_t)12000000) /* 12 MHZ XTAL on the eval board */
#endif                                 /* HSE VALUE */
#else
#error STM32F411RE OR STM32F411VE MUST BE DEFINED
#endif /* MCU PACKAGE */

/* HSI RC oscillator is embedded */
#if defined(HSI_VALUE)
#error HSI_VALUE IS ALREADY DEFINED, \
PLEASE RESOLVE THE PREPROCESSOR CONFLICT BEFORE BUILDING
#else
#define HSI_VALUE ((uint32_t)16000000U) /* 16 MHz internal RC oscillator */
#endif                                  /* HSI_VALUE */

#endif /* MCU_APP */

#if defined(MCU_APP)
#if defined(STM32F411VE) || defined(STM32F411RE)
#else
#error EITHER STM32F411VE OR STM32F411RE MUST BE DEFINED
#endif
#else
#ifndef __MY__PROJECT_BUILD_TYPE_WARNING
#define __MY__PROJECT_BUILD_TYPE_WARNING
#warning ===============================================================================\
Building the rimot-lowpower-sensorboard project as a hosted application.     \n\
Interrupts and real-time behaviour will not be present in the final binary.  \n\
===============================================================================
#endif /* BUILD TYPE WARNING */
#endif /* MCU PACKAGE DEFINITION CHECK */

#define UID_BASE 0x1FFF7A10UL       /*Unique device ID register base address */
#define FLASHSIZE_BASE 0x1FFF7A22UL /*!< FLASH Size register base address       */
#define PACKAGE_BASE 0x1FFF7BF0UL   /*!< Package size register base address     */

#if !defined(USE_HAL_DRIVER)
/* DONT TOUCH THIS */
#include "core_cm4.h"

#endif /* NOT DEFINED, USE_HAL_DRIVER */

#endif /* MCU_APP */
#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_CORTEX_CONFIG */
