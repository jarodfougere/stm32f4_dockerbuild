#ifndef __USBSERIALTASK_H__
#define __USBSERIALTASK_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

#include "task_defs.h"

void usbSerialTask(const USBSERIALMSGQ_t *Q);


#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __USBSERIALTASK_H__ */
