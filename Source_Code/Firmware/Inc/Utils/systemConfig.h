#ifndef __SYSTEMCONFIG_H__
#define __SYSTEMCONFIG_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

#include <stdint.h>

#define DEVICE_NAME_STRING "Rimot Low Power Outpost"
#define FWID_RELEASE "0.1"
#define HWVERSION_MAJOR 1
#define HWVERSION_MINOR 0

extern uint32_t heartbeat_reporting_interval;
extern uint32_t dcin_periodic_timer_interval;


void jumpToBootloader(void);
void systemReset(void);


#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __SYSTEMCONFIG_H__ */
