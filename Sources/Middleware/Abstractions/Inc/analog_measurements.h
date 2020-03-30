#ifndef RIMOT_ANALOG_MEASUREMENTS
#define RIMOT_ANALOG_MEASUREMENTS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

void adc_init(void);

#define VALID_ANALOG_MEASUREMENT (0)
#define INVALID_ANALOG_MEASUREMENT (1)


/* ADC */
#define ADC_FS_VOLTAGE (3.000) /* externel 3.00V voltage reference, ADR363 */
#define ADC_FS_MIN (0x0000)
#define ADC_FS_MAX (0x0FFF) /* 12-bits */
#define ADC_FS_RANGE (ADC_FS_MAX - ADC_FS_MIN)

#define ADC_REF_1V ((uint16_t)((ADC_FS_RANGE) *     (1.00 / ADC_FS_VOLTAGE)))
#define ADC_REF_2V ((uint16_t)((ADC_FS_RANGE) *     (2.00 / ADC_FS_VOLTAGE)))

/* Macro to convert adc vals to voltage */
#define ADC_TO_VOLTAGE(x) \
(ADC_FS_VOLTAGE * ((float)x) / ((float)(ADC_FS_RANGE)))










#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_ANALOG_MEASUREMENTS */