

/**
 * @file main.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief  The low-power-sensorcard firmware application mainline starts here.
 * If a different scheduling algorithm is used, this source module is where we
 * would write it.
 *
 * @note
 * High-level architecture is a round-robin event loop.
 *
 * In the future, if real-time performance is required, a scheduler can be
 * integrated (such as freeRTOS or chibiOS) or implemented to call each task's
 * handler as part of an RMA scheduling algorithm using systick as a timeslice
 * rather than simply executing in a round-robin.
 *
 * Each task is responsible for executing based on the device state and its
 * task state (ready, blocked, suspended)
 * Tasks can signal each other to request or release peripheral resources as
 * many peripheral drivers have been configured to operate in a non-blocking
 * fashion with interrupts signaling peripheral process completion.
 *
 * 90 % of request and release for resources will be for the SPI peripheral and
 * the ADC since SPI is shared by temp, humidity, and eeprom, with ADC
 * being shared by battery monitoring, RF detection, and the analog output of
 * the sparkfun motion detection module.
 *
 * @version 0.3
 * @date 2020-03-05
 *
 * @copyright Copyright (c) 2020 Rimot.io Incorporated. All rights reserved.
 *
 * This software is licensed under the Berkley Software Distribution (BSD)
 * 3-Clause license. Redistribution and use in source and binary forms,
 * with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "main.h"
#include "rimot_device.h"
#include "task.h"

#if !defined(USE_HAL_DRIVER)
/**
 * @note Thomas, this is where I will be including headers for driver testing.
 *  - Carl
 */
#include "rimot_LL_debug.h"
#include "rimot_cortex.h"
#include "rimot_flash_ctl.h"
#include "rimot_gpio.h"
#include "rimot_interrupts.h"
#include "rimot_power_control.h"
#include "rimot_rcc.h"
#include "rimot_usb.h"

#endif /* USE_HAL_DRIVER */

#if defined(__GNUC__)
#if !defined(MCU_APP)
__stdcall
#endif /* HOST APPLCIATION CHECK */
#endif /* GNUC */
    int
    main(void)
{

#if !defined(USE_HAL_DRIVER)
    /**
     * @note Thomas, this is where I will be testing the drivers.
     * - Carl
     */
    middleware_init_core();

    usbProtocolDriver *mydriver;
    mydriver = usbProtocolDriverInit(NULL);

#if 0
#if defined(STM32F411VE)
    /* Turn on green LED on eval board */
    gpio_enablePinClock(MCUPIN_PD12);
    gpio_setPinMode(MCUPIN_PD12, GPIO_MODE_output);
    gpio_setPinPull(MCUPIN_PD12, GPIO_PIN_PULL_MODE_none);
    gpio_setPinSpeed(MCUPIN_PD12, GPIO_SPEED_max);
    gpio_setPinSupplyMode(MCUPIN_PD12, GPIO_PIN_SUPPLY_MODE_push_pull);
    gpio_setDigitalPinState(MCUPIN_PD12, GPIO_PIN_STATE_high);

    /* Turn on Red LED */
    gpio_enablePinClock(MCUPIN_PD13);
    gpio_setPinMode(MCUPIN_PD13, GPIO_MODE_output);
    gpio_setPinPull(MCUPIN_PD13, GPIO_PIN_PULL_MODE_none);
    gpio_setPinSpeed(MCUPIN_PD13, GPIO_SPEED_max);
    gpio_setPinSupplyMode(MCUPIN_PD13, GPIO_PIN_SUPPLY_MODE_push_pull);
    gpio_setDigitalPinState(MCUPIN_PD13, GPIO_PIN_STATE_high);

    gpio_enablePinClock(MCUPIN_PD14);
    gpio_setPinMode(MCUPIN_PD14, GPIO_MODE_output);
    gpio_setPinPull(MCUPIN_PD14, GPIO_PIN_PULL_MODE_none);
    gpio_setPinSpeed(MCUPIN_PD14, GPIO_SPEED_max);
    gpio_setPinSupplyMode(MCUPIN_PD14, GPIO_PIN_SUPPLY_MODE_push_pull);
    gpio_setDigitalPinState(MCUPIN_PD14, GPIO_PIN_STATE_high);

    gpio_enablePinClock(MCUPIN_PD15);
    gpio_setPinMode(MCUPIN_PD15, GPIO_MODE_output);
    gpio_setPinPull(MCUPIN_PD15, GPIO_PIN_PULL_MODE_none);
    gpio_setPinSpeed(MCUPIN_PD15, GPIO_SPEED_max);
    gpio_setPinSupplyMode(MCUPIN_PD15, GPIO_PIN_SUPPLY_MODE_push_pull);
    gpio_setDigitalPinState(MCUPIN_PD15, GPIO_PIN_STATE_high);

#endif /* EVAL BOARD TURN ON GREEN LIGHT */
#endif

    while (0 != usbDeviceInit(mydriver))
    {
        /* Wait for USB to enumerate correctly */
    }

    while (1)
    {
        /* Catch end of application code */
    }

#else
    virtualDev *dev = virtualDevInit();
    /* virtual device structure */

    /* tasks that the event loop will service */
    unsigned int numTasks = 0;
    task_t *     tasks[20];
    tasks[numTasks] = taskInit(&system_task);
    numTasks++;
    tasks[numTasks] = taskInit(&usb_task);
    numTasks++;
    tasks[numTasks] = taskInit(&battery_task);
    numTasks++;
    tasks[numTasks] = taskInit(&digital_input_task);
    numTasks++;
    tasks[numTasks] = taskInit(&relay_task);
    numTasks++;
    tasks[numTasks] = taskInit(&motion_task);
    numTasks++;
    tasks[numTasks] = taskInit(&temperature_task);
    numTasks++;
    tasks[numTasks] = taskInit(&humidity_task);
    numTasks++;
    tasks[numTasks] = taskInit(&rf_task);
    numTasks++;
    tasks[numTasks] = taskInit(&analytics_task);
    numTasks++;

    while (1)
    {
        /* Just run through the event loop */
        unsigned int t;
        for (t = 0; t < numTasks; t = (t + 1) % numTasks)
        {
            taskCallHandler(tasks[t], dev);
        }
    }
#endif /* USE_HAL_DRIVER */
}
