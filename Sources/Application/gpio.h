#include "stm32l0xx_hal.h"

// Digital Inputs (EVAL and Target cards)
#define DI0_Pin GPIO_PIN_0
#define DI0_GPIO_Port GPIOC
#define DI1_Pin GPIO_PIN_1
#define DI1_GPIO_Port GPIOC
#define DI2_Pin GPIO_PIN_2
#define DI2_GPIO_Port GPIOC
#define DI3_Pin GPIO_PIN_3
#define DI3_GPIO_Port GPIOC
#define DI4_Pin GPIO_PIN_4
#define DI4_GPIO_Port GPIOC
#define DI5_Pin GPIO_PIN_5
#define DI5_GPIO_Port GPIOC
#define DI6_Pin GPIO_PIN_6
#define DI6_GPIO_Port GPIOC
#define DI7_Pin GPIO_PIN_7
#define DI7_GPIO_Port GPIOC

// Digital Outputs (EVAL Card)
#define DO0_Pin GPIO_PIN_12
#define DO0_GPIO_Port GPIOB
#define DO1_Pin GPIO_PIN_13
#define DO1_GPIO_Port GPIOB
#define DO2_Pin GPIO_PIN_14
#define DO2_GPIO_Port GPIOB
#define DO3_Pin GPIO_PIN_15
#define DO3_GPIO_Port GPIOB

// Motion Input (Target and Eval)
#define MOTION_Pin GPIO_PIN_8
#define MOTION_GPIO_Port GPIOB

// Analog Inputs
#define BATTERY_0_Pin GPIO_PIN_6
#define BATTERY_0_GPIO_Port GPIOA
#define BATTERY_1_Pin GPIO_PIN_7
#define BATTERY_1_GPIO_Port GPIOA
#define BATTERY_2_Pin GPIO_PIN_0
#define BATTERY_2_GPIO_Port GPIOB
#define BATTERY_3_Pin GPIO_PIN_1
#define BATTERY_3_GPIO_Port GPIOB
#define RF1_FWD_Pin GPIO_PIN_0
#define RF1_FWD_GPIO_Port GPIOA
#define RF1_REF_Pin GPIO_PIN_1
#define RF1_REF_GPIO_Port GPIOA
#define RF2_FWD_Pin GPIO_PIN_4
#define RF2_FWD_GPIO_Port GPIOA
#define RF2_REF_Pin GPIO_PIN_5
#define RF2_REF_GPIO_Port GPIOA
