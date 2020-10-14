#ifndef __SYSTEMCONFIG_H__
#define __SYSTEMCONFIG_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

#include <stdint.h>

#define USER_DEVICE_NAME_SIZE 50

#define DEVICE_NAME_STRING "Rimot Low Power Sensor Card"
#define DEVICE_MODEL_STRING "Low Power Sensor Card V1"
#define FWID_RELEASE "0.1"
#define HWVERSION_MAJOR 1
#define HWVERSION_MINOR 0


extern uint32_t heartbeat_reporting_interval;
extern uint32_t dcin_periodic_timer_interval;
extern uint32_t runtick;

#define MIN_HEARTBEAT_REPORTING_INTERVAL_S 30
#define MIN_DCIN_PERIODIC_TIMER_INTERVAL_S 30

#define MAX_DIGITAL_INS 8
#define MAX_DIGITAL_OUTS 4
#define MAX_ANALOG_INS 4
#define MAX_RF_SENSORS 2
#define MAX_MOTH_SENSORS 1


void jumpToBootloader(void);
void systemReset(void);


/**
 * @brief Set the device name
 *
 * @param new_name the new name for the device
 * @return int 0 on success, -1 on failure
 */
int setDeviceName(const char *new_name);

/**
 * @brief Get the Device Name
 *
 * @return char* device name
 */
char *getDeviceName(void);


#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __SYSTEMCONFIG_H__ */
