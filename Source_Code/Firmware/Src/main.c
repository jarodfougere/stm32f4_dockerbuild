/**
 * @file main.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief Entry point into example CDC application for STM32F411Discovery
 * @version 0.1
 * @date 2020-10-04
 *
 * @copyright Copyright (c) Rimot.io 2020
 *
 * @note
 *          toolchain : arm-none-eabi 6.3.1
 *          build-system : cmake with Unix Makefile generator
 *
 *          I will provide a docker build image so the build
 *          system is consistent independent of changes to the
 *          host (building) system
 *
 */

#include <stdint.h>
#include <string.h>

#include "main.h"
#include "gpio.h"

#include "cmsis_os.h"
#include "stm32f4xx.h"

#include "usbd_cdc_if.h"
#include "usb_device.h"

void MX_FREERTOS_Init(void);
void SystemClock_Config(void);

static void check_bootloader_jump(void);

int main(void)
{
    check_bootloader_jump();
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();

    // MX_I2C1_Init();
    // MX_I2S2_Init();
    // MX_I2S3_Init();
    // MX_SPI1_Init();

    MX_FREERTOS_Init();
    osKernelStart();
    while (1)
    {
    }
}


void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 192;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 8;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    PeriphClkInitStruct.PLLI2S.PLLI2SN = 200;
    PeriphClkInitStruct.PLLI2S.PLLI2SM = 5;
    PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        HAL_IncTick();
    }
}


static void check_bootloader_jump(void)
{
    /** @todo IMPLEMENT */
}


void Error_Handler(void)
{
    while (1)
    {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line
       number, tex: printf("Wrong parameters value: file %s on line %d\r\n",
       file, line) */
}
#endif /* USE_FULL_ASSERT */
