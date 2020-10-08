#ifndef __COMPILER_H__
#define __COMPILER_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */



#if defined(__ICCARM__) && defined(__GNUC__)


#elif defined(__GNUC__)


#endif


#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __COMPILER_H__ */
