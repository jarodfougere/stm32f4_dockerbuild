/**
 * @file compatiblitity.h
 * @author your name (you@domain.com)
 * @brief  Compatility header to be pre-included to all compilation units.
 * @version 0.1
 * @date 2020-02-26
 * 
 * @copyright Copyright (c) Rimot.io Incorporated 2020
 * @author Carl Mattatall
 */


/* half of STM32 HAL functions don't include stdint for christ sake.... despite using stdint expanded typedefs.... :/ */
/* its a tangled mess of header dependencies and I refuse to modify all the BSD-4 licenses with an additional rimot disclaimer just to add #include <stdint.h> */

#ifndef RIMOT_TOOLCHAIN_COMPATIBILITY
#define RIMOT_TOOLCHAIN_COMPATIBILITY
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#if !defined(NDEBUG)
#include "debug.h"
#endif

#define SUCCESS_CODE (int32_t)0

#define __IO volatile

#if defined(weak)
    #error >weak< has an existing definition. please resolve befoer including compatibility.h
#endif

#if defined(packed)
    #error >packed< has an existing definition. please resolve befoer including compatibility.h
#endif


/*
I considered doing the following: (but it greatly reduces readability )
#if defined(__ICCARM__)
#defined attr(x) __#x
#elif defined(__GNUC__)
#define attr(x) __attribute__((__#x__))
#endif
it also does NOT guarantee that compiler specific semantics will be portable in the future
*/

/* The two main toolchains being used at rimot for arm work are IAR and arm-none-eabi-gcc */

/* THE PURPOSE OF THIS IS TO PREVENT USE OF COMPILER SPECIFIC PRAGMAS */
#if defined(__ICCARM__) /* IAR (EWARM) keywords */
#define weak __weak
#define used __root
#define packed __packed
#elif defined(__GNUC__) /* gnu toolchain */
#define weak __attribute__((__weak__))
#define packed __attribute__((__packed__))
#define used __attribute__((__used__))
#else
#warning __ICCARM__ and __GNUC__ check both failed in compatibility.h
#endif /* toolchain detection */
#endif /* include guard */
