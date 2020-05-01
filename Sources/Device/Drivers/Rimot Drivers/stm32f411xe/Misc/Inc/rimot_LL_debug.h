#ifndef RIMOT_LL_DEBUG
#define RIMOT_LL_DEBUG
#ifdef __cplusplus
extern "C"
{
#endif /* C linkage */

#if defined(MCU_APP)
#include <limits.h>
#include <float.h>
#else
#include <stdio.h>
#endif

#include "ATTRIBUTE_PORTABILITY_HEADER.h"

/* Basic assertion semantic for standalone target */
#if !defined(NDEBUG)
#define LL_ASSERT(x) \
    if (!(x))        \
    {                \
        while (1)    \
        {            \
        }            \
    }
#else
#define LLASSERT(x) ;
#endif /* ASSERTION HANG FOR LOW LEVEL IN DEBUG BUILD */

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_LL_DEBUG */
