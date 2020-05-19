/**
 * @file comms_interface.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief  This module (in combination with its header file of the same name)
 *         provides a communication interface abstraction to the task layer.
 *
 *         The interface bundles the USB periph, buffers, line coding, clocking,
 *         interupts, and line control state into an abstraction that can be
 *         exposed to the task / application layer without exposing the actual
 *         implementation details of the low level drivers themselves.
 * @version 0.1
 * @date 2020-03-19
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

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comms_interface.h"
#if defined(USE_HAL_DRIVER)
#include "middleware_core.h"
#include "usbd_cdc_if.h"
#include "usbd_conf.h"
#include "usbd_desc.h"

#else
#include "middleware_core.h"
#include "rimot_gpio.h"
#include "rimot_interrupts.h"
#include "rimot_pin_aliases.h"
#include "rimot_rcc.h"
#include "rimot_usb.h"

#endif /* USE_HAL_DRIVER */

#if defined(STM32F411VE)
#define USB_VBUS_PIN                  MCUPIN_PA9
#define USB_DATA_POS_PIN              MCUPIN_PA12
#define USB_DATA_NEG_PIN              MCUPIN_PA11
#define COMMS_GPIO_ALTERNATE_MODE_USB GPIO_ALT_FUNC_10

#define DELAY_MS_MAX_DELAY                 UINT_MAX
#define MAX_TX_TRIES                       5
#define COMMS_TRANSMIT_ATTEMPT_INTERVAL_MS 3
#define PRESCALE_PLL_Q                     RCC_PLL_Q_DIV_3
#define PRESCALE_PLL_P                     RCC_PLL_P_DIV_2
#define PRESCALE_PLL_M                     4U
#define PRESCALE_PLL_N                     72U
#define PRESCALE_HCLK                      RCC_HCLK_DIV_1
#define PRESCALE_APB1                      RCC_APB_CLK_DIV_2
#define PRESCALE_APB2                      RCC_APB_CLK_DIV_1

#elif defined(STM32F411RE)
#error comms_interface.c doesn't provide a pin mapping to the USB pins on the microcontroller package for STM32f411re
#endif /* MCU PACKAGE PIN MAPPING SELECTION */

#include "rimot_LL_debug.h"

/* This interface hides the actual buffers from the task layer */
static uint8_t inBuf[COMMS_IF_USER_RX_BUF_SIZE];
static uint8_t outBuf[COMMS_IF_USER_TX_BUF_SIZE];

static void comms_USB_PHY_INIT(void);

#if defined(USE_HAL_DRIVER)
USBD_HandleTypeDef hUsbDeviceFS;
#include "usbd_def.h"
#endif /* USE_HAL_DRIVER */

char *comms_get_command_string(void)
{
    char *commandString = NULL;
#if defined(USE_HAL_DRIVER)

#else
#warning BAREMETAL IMPLEMENTATION HAS BEEN DELETED FOR \
comms_get_command_String

#endif /* USE_HAL_DRIVER */
    return commandString;
}

int comms_tx(char *buf, unsigned int len)
{
    int status = 0;
#if defined(USE_HAL_DRIVER)
/* TESTING */
#else
#warning BAREMETAL CODE IS BLOCKED OUT, FIX LATER.
#if 0
int tx_tries;
    for (tx_tries = 0; tx_tries < MAX_TX_TRIES; tx_tries++)
    {
        switch (CDC_Transmit_FS((uint8_t *)buf, (uint16_t)len))
        {
        case USBD_OK:
        {
            return 0;
        }
        break;
        case USBD_FAIL:
        {
            return 1;
        }
        break;
        case USBD_BUSY:
        {
            delay_ms(COMMS_TRANSMIT_ATTEMPT_INTERVAL_MS);
        }
        break; /* try again */
        default:
        {
            LL_ASSERT(0);
        }
        break;
        }
    }

    /* failure because 5 attempts were done and still no transmit success */
    return 1;
#endif /* IF 0 */
#endif /* USE_HAL_DRIVER */

    return status;
}

static usbProtocolDriver *mydriver;

void comms_init(void)
{
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)

    if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
    {
        LL_ASSERT(0);
    }
    if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
    {
        LL_ASSERT(0);
    }
    if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) !=
        USBD_OK)
    {
        LL_ASSERT(0);
    }
    if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
    {
        LL_ASSERT(0);
    }

#else
    /*
     * Inject delay function into USb module
     * (REQUIRED TO IMPLEMENT TIMING IN HW STACK)
     */
    usbDriver_setDelayFunc(&delay_ms);

    /* Initialize core USB driver (USB hardware / timing stack) */
    mydriver = usbProtocolDriverInit(NULL);

    /*  Initialize USB device mode in OTG peripheral */
    while (0 != usbDeviceInit(mydriver))
    {
        /* Wait for USB to enumerate correctly */
    }

    /**
     * @note EVERYTHING BELOW ARE ON THE TODO LIST [ CARL , MAY 19, 2020 ]
     */

    /* Initialize USB CDC class interface params */

    /* Launch USB CDC class interface driver */

    /* Link CDC class interface driver to USB HW driver */

    /* Reset the USB peripheral so host Acks the Re-Up */

    /* We are now ready to have the device act as a virtual COM port */

#endif /* USE_HAL_DRIVER */
#else
    comms_printf("executed comms_init%c", '\n');
#endif /* MCU_APP */
}

static void comms_USB_PHY_INIT(void)
{

#if defined(USE_HAL_DRIVER)
#warning NO HAL_IMPLEMENTATION FOR comms_USB_PHY_INIT
#else
    /* Configure VBUS pin */
    gpio_enablePinClock(USB_VBUS_PIN);
    gpio_setPinMode(USB_VBUS_PIN, GPIO_MODE_input);
    gpio_setPinPull(USB_VBUS_PIN, GPIO_PIN_PULL_MODE_none);
    gpio_setPinAlternateFunc(USB_VBUS_PIN, COMMS_GPIO_ALTERNATE_MODE_USB);

    /* Configure D- pin */
    gpio_enablePinClock(USB_DATA_NEG_PIN);
    gpio_setPinMode(USB_DATA_NEG_PIN, GPIO_MODE_alternate);
    gpio_setPinPull(USB_DATA_NEG_PIN, GPIO_PIN_PULL_MODE_none);
    gpio_setPinSupplyMode(USB_DATA_NEG_PIN, GPIO_PIN_SUPPLY_MODE_push_pull);
    gpio_setPinSpeed(USB_DATA_NEG_PIN, GPIO_SPEED_max);
    gpio_setPinAlternateFunc(USB_DATA_NEG_PIN, COMMS_GPIO_ALTERNATE_MODE_USB);

    /* Configure D+ pin */
    gpio_enablePinClock(USB_DATA_POS_PIN);
    gpio_setPinMode(USB_DATA_POS_PIN, GPIO_MODE_alternate);
    gpio_setPinPull(USB_DATA_POS_PIN, GPIO_PIN_PULL_MODE_none);
    gpio_setPinSupplyMode(USB_DATA_POS_PIN, GPIO_PIN_SUPPLY_MODE_push_pull);
    gpio_setPinSpeed(USB_DATA_POS_PIN, GPIO_SPEED_max);
    gpio_setPinAlternateFunc(USB_DATA_POS_PIN, COMMS_GPIO_ALTERNATE_MODE_USB);

    /* Start USB Peripheral clock (assumes prescalers already set) */
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_usb);

    /* Configure interrupt preemption in NVIC and unmask ISR */
    interruptSetPrio(OTG_FS_IRQn, NVIC_PREEMPTION_PRIO_0, NVIC_SUBPRIO_0);
    interruptSetState(OTG_FS_IRQn, INTERRUPT_STATE_enabled);
#endif /* USE_HAL_DRIVER */
}

int comms_set_payload(const char *format, ...)
{
    int status = 0;
#if defined(USE_HAL_DRIVER)

#else
#warning BAREMETAL COMMS_sET_PAYLOAD is blocked out. fix later
#if 0
    int status = 0;
    va_list args;
    va_start(args, format);
    int Len;
    int UserBytesLoaded;
    const char delimStrCheck[] = {RIMOT_USB_STRING_DELIM, '\0'};

    /* load buffer with printf formatting of payload */
    Len = vsnprintf((char *)outBuf, sizeof(outBuf), format, args);

    /* Tack on payload delimiter */
    strcat((char *)outBuf, delimStrCheck);
    Len += sizeof(delimStrCheck);

    UserBytesLoaded = Len;

    /* Load the payload into CDC TX endpoint */
    if (USBD_OK == CDC_set_payload(&Len))
    {
        /* Wipe the user payload buffer if it's loaded correctly */
        memset(outBuf, 0, sizeof(outBuf));
    }
    else
    {
        if (UserBytesLoaded != Len)
        {
            /* 
             * Payload would fit in user buffer but 
             * there are too many payloads in USB OUT
             * endpoint already to queue the transmit.
            */
            status = 2;

            /**
              * @todo
              * 
              * IF OUTPOST STATE IS ACTIVE, WE CAN TRANSMIT A PAYLOAD
              * AND TRY TO LOAD THE DESIRED PAYLOAD NOW THAT THERE
              * IS MORE ROOM IN THE CDC INTERFACE OUT ENDPOINT.
              * 
              * BUT IF OUTPOST IS ASLEEP, THERES NOTHING WE CAN DO OTHER
              * THAN INCREASING THE SIZE OF THE CDC INTERFACE PAYLOAD BUFFER.
              */
        }
        else
        {
            /* Couldn't load the payload into CDC TX OUT buffer (wont' fit) */
            status = 1;
        }
    }
    va_end(args);
#endif /* IF 0 */
#endif /* USE_HAL_DRIVER */
    return status;
}

int comms_send_payloads(unsigned int num_payloads, unsigned int ms)
{
    int payloadsSent = 0;
#if defined(USE_HAL_DRIVER)

#else
#warning COMMS_SEND_PAYLOADS is blocked out for baremetal. fix me.
#if 0
    /*
     * @todo THIS CAN BE MADE MUCH BETTER.
     * 
     * CURRENTLY WHEN CALLER TRIES TO TRANSMIT MORE PAYLOADS 
     * THAN ARE LOADED INTO THE BUFFER, WE RETURN 0 TO INDICATE 
     * NONE HAVE BEEN TRANSMITTED.
     * 
     * REALLY, WE NEED A SEPARATE STATUS WHICH FUNCTIONS LIKE A 
     * "WARNING", INDICATING TO THE CALLER THAT ALL THEIR PAYLOADS
     * WERE TRANSMITTED BUT THAT THEY TRIED TO TRANSMIT A PAYLOAD
     * THAT EITHER WAS NOT QUEUED SUCCESSFULLY OR THAT THEY LOST 
     * TRACK OF THE NUMBER OF PAYLOADS THEY HAD STORED.
     */
    int tx_successes = 0;
    unsigned int i;
    unsigned int payloads_to_tx;
    unsigned int actual_delay;

    /* delay check */
    if (ms < COMMS_TRANSMIT_ATTEMPT_INTERVAL_MS)
    {
        actual_delay = COMMS_TRANSMIT_ATTEMPT_INTERVAL_MS;
    }
    else
    {
        actual_delay = ms;
    }

    /* payload count check */
    if (num_payloads > CDC_peek_num_payloads_out())
    {
        /**  
          * @note 
          * If caller wants to transmit more payloads 
          * than they have queued, 
          * only transmit what is available. 
          * 
          * @todo should indicate to caller than this scenario has occurred.
          */
        payloads_to_tx = CDC_peek_num_payloads_out();
    }
    else
    {
        payloads_to_tx = num_payloads;
    }

    /* transmit payloads */
    for (i = 0; i < payloads_to_tx; i++)
    {
        USBD_StatusTypeDef status = USBD_OK;

        /* payload attempt loop */
        int tries = 0;
        for (; (tries < MAX_TX_TRIES) && (status != USBD_FAIL); tries++)
        {

            status = (USBD_StatusTypeDef)CDC_transmit_payload();
            if (USBD_OK == status)
            {
                tx_successes++;
                break;
            }
            else
            {
                delay_ms(actual_delay);
            }
        }

        if (USBD_FAIL == status)
        {
            LL_ASSERT(0);
            /* do nothing */
        }
    }
    return tx_successes;
#endif /* IF 0 */
#endif /* USE_HAL_DRIVER */
    return payloadsSent;
}
