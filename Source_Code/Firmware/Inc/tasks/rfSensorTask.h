#ifndef __RADIOFREQUENCYTASK_H__
#define __RADIOFREQUENCYTASK_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

#include "task_defs.h"

void rfSensorTask(const RFSENSORMSGQ_t *Q);

#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __RADIOFREQUENCYTASK_H__ */
