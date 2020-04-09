#ifndef RIMOT_LL_DEBUG
#define RIMOT_LL_DEBUG
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */


/* Basic assertion semantic for standalone target */
#if !defined(NDEBUG)
#define LL_ASSERT(x)        do                  \
                            {                   \
                                if(!(x))        \
                                {               \
                                    while(1)    \
                                    {           \
                                                \
                                    }           \
                                }               \
                            }   while(0)
#else 
#define LLASSERT(x)         do                  \
                            {                   \
                                if(!(x))        \
                                {               \
                                    while(0)    \
                                    {           \
                                                \
                                    }           \
                                }               \
                            }   while(0)
#endif /* ASSERTION HANG FOR LOW LEVEL IN DEBUG BUILD */


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_LL_DEBUG */