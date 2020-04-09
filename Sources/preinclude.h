/**
 * @file compatiblitity.h
 * @author your name (you@domain.com)
 * @brief  Compatility header to be pre-included to all compilation units.
 * @version 0.1
 * @date 2020-02-26
 * 
 * @copyright Copyright (c) Rimot.io Incorporated 2020
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 */

#ifndef RIMOT_TOOLCHAIN_COMPATIBILITY
#define RIMOT_TOOLCHAIN_COMPATIBILITY
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

/* Cortex definition for processor */
#define ARM_MATH_CM4 


/*******************************************************************************
 *       TOOL CHAIN SPECIFIY KEYWORDS HAVE BEEN ALIASED FOR PORTABILITY
*******************************************************************************/

#if defined(__ICCARM__) /* IAR (EWARM) keywords */

/* declare as weak symbol */
#define weak __weak  

 /* linker will not purge symbol even if not in mainline call tree */
#define used __root 

/* do not word-align aggregate type */
#define packed __packed

#define __this_func__ __func__

#if __STDC_VERSION__ == 199409L /* _Pragma only exists in ISO C99 and later */
#error FOR COMPATIBILITY WITH OTHER TOOLCHAINS, WE DO NOT SUPPORT COMPILER SPECIFIC PRAGMAS. IAR TOOLCHAIN USES A COMPILER SPECIFIC PRAGMA TO PREVENT LINK-TIME OPTIMIZATION OF SYMBOLS BY INLINING. THUS, COMPILATION MUST OCCUR IN COMPILANCE WITH ISO C99 STANDARD OR LATER SO THAT _Pragma can be used to indicate no symbol ininling to icclink.exe
#else
/* Exclude the symbol from compiler optimization-based inlining.
 *
 * WARNING: USE OF PRAGMA REQUIRES It to be the very first attribute preceding 
 * a symbol declaration. 
 */
#define no_inline _Pragma("optimize=no_inline") 
#endif

#elif defined(__GNUC__) /* gnu toolchain */
#define weak __attribute__((__weak__))
#define packed __attribute__((__packed__))
#define used __attribute__((__used__))
#define no_inline __attribute__((noinline))

#define __this_func__ __func__


#else
#warning __ICCARM__ and __GNUC__ check both failed in compatibility.h
#endif /* toolchain detection */


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_TOOLCHAIN_COMPATIBILITY */
