#ifndef COMPILER_ATTRIBUTE_PORTABILITY_HEADER
#define COMPILER_ATTRIBUTE_PORTABILITY_HEADER
#ifdef __cplusplus
extern "C" {
#endif /* C linakge */


/*
 * THE PURPOSE OF THIS FILE IS TO PROVIDE SOME 
 * COMPILER-PORTABILITY FEATURES BETWEEN
 * THE TWO DEVELOPMENT TOOLCHAINS I'VE BEEN USING
 * FOR THE PROJECT (GCC-ARM) (arm-none-eabi-gcc)
 * 
 * and IAR system's arm compiler (iccarm)
 */

#include "cmsis_compiler.h"

/* COMPILER BARRIER TO PREVENT INSTRUCTION REORDERING */
#if !defined(NDEBUG)
#define __COMPILER_BARRIER()                            \
do {                                                    \
    __ISB(); /* Flush pipeline                  */      \
    __DMB(); /* complete all memory accesses    */      \
    __ISB(); /* Complete fetch of new content   */      \
} while(0)                 
#else
#define __COMPILER_BARRIER() ;
#endif


#if defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
  #ifndef __weak
    #define __weak   __attribute__((weak))
  #endif /* __weak */
  #ifndef __packed
    #define __packed __attribute__((__packed__))
  #endif /* __packed */
#endif /* __GNUC__ */


/* Macro to get variable aligned on 4-bytes, for __ICCARM__ the directive "#pragma data_alignment=4" must be used instead */
#if defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
  #ifndef __ALIGN_END
#define __ALIGN_END    __attribute__ ((aligned (4)))
  #endif /* __ALIGN_END */
  #ifndef __ALIGN_BEGIN  
    #define __ALIGN_BEGIN
  #endif /* __ALIGN_BEGIN */
#else
  #ifndef __ALIGN_END
    #define __ALIGN_END
  #endif /* __ALIGN_END */
  #ifndef __ALIGN_BEGIN      
    #if defined   (__CC_ARM)      /* ARM Compiler */
#define __ALIGN_BEGIN    __align(4)
    #elif defined (__ICCARM__)    /* IAR Compiler */
      #define __ALIGN_BEGIN 
    #endif /* __CC_ARM */
  #endif /* __ALIGN_BEGIN */
#endif /* __GNUC__ */


/** 
  * @brief  __RAM_FUNC definition
  */ 
#if defined ( __CC_ARM   )
/* ARM Compiler
   ------------
   RAM functions are defined using the toolchain options. 
   Functions that are executed in RAM should reside in a separate source module.
   Using the 'Options for File' dialog you can simply change the 'Code / Const' 
   area of a module to a memory space in physical RAM.
   Available memory areas are declared in the 'Target' tab of the 'Options for Target'
   dialog. 
*/
#define __RAM_FUNC

#elif defined ( __ICCARM__ )
/* ICCARM Compiler
   ---------------
   RAM functions are defined using a specific toolchain keyword "__ramfunc". 
*/
#define __RAM_FUNC __ramfunc

#elif defined   (  __GNUC__  )
/* GNU Compiler
   ------------
  RAM functions are defined using a specific toolchain attribute 
   "__attribute__((section(".RamFunc")))".
*/
#define __RAM_FUNC __attribute__((section(".RamFunc")))

#endif

/** 
  * @brief  __NOINLINE definition
  */ 
#if defined ( __CC_ARM   ) || defined   (  __GNUC__  )
/* ARM & GNUCompiler 
   ---------------- 
*/
#define __NOINLINE __attribute__ ( (noinline) )

#elif defined ( __ICCARM__ )
/* ICCARM Compiler
   ---------------
*/
#define __NOINLINE _Pragma("optimize = no_inline")

#endif

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* COMPILER_ATTRIBUTE_PORTABILITY_HEADER */


