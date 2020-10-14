#include "gpio.h"
#include <stdint.h>

void MX_GPIO_Init(void)
{
  /* GPIO Ports Clock Enable  - WHAT IS THIS FOR????? */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

// Write default state on digital outputs - Do this before configuring the pins as output
  HAL_GPIO_WritePin(DO0_GPIO_Port, DO0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DO1_GPIO_Port, DO1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DO2_GPIO_Port, DO2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DO3_GPIO_Port, DO3_Pin, GPIO_PIN_RESET);


/* INIT GPIOB (OUTPUT PINS) */
  GPIO_InitStruct.Pin = DO0_Pin | DO1_Pin | DO2_Pin | DO3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* INIT GPIOB (INPUT PINS)*/
  GPIO_InitStruct.Pin = MOTION_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* INIT GPIOC (INPUT PINS)*/
  GPIO_InitStruct.Pin = DI0_Pin | DI1_Pin | DI2_Pin | DI3_Pin | DI4_Pin | DI5_Pin | DI6_Pin | DI7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}