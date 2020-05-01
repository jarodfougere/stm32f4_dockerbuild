/**
 * @file rimot_gpio.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level driver for the
 * GPIO peripheral on the stm32f411re microcontroller
 * @version 0.1
 * @date 2020-04-02
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

#if !defined(USE_HAL_DRIVER)

#include "rimot_rcc.h"
#include "rimot_rcc_register_masks.h"
#include "rimot_gpio.h"
#include "rimot_gpio_register_masks.h"
#include "rimot_bus_region_offsets.h"

#include "rimot_LL_debug.h"

#define GPIO_PORT_BASE (AHB1PERIPH_BASE + 0x00000000U)

struct gpio_port
{
    volatile uint32_t MODER;    /* GPIO port mode register                0x0000    */
    volatile uint32_t OTYPER;   /* GPIO port output type register         0X0004    */
    volatile uint32_t OSPEEDR;  /* GPIO port output speed register        0X0008    */
    volatile uint32_t PUPDR;    /* GPIO port pull-up/pull-down register   0X000C    */
    volatile uint32_t IDR;      /* GPIO port input data register          0X0010    */
    volatile uint32_t ODR;      /* GPIO port output data register         0X0014    */
    volatile uint32_t BSRR;     /* GPIO port bit set/reset register       0X0018    */
    volatile uint32_t LCKR;     /* GPIO port configuration lock register  0X001C    */
    volatile uint32_t AFRL;     /* GPIO alternate function low register   0X0020    */
    volatile uint32_t AFRH;     /* GPIO alternate function high register  0X0024    */
    PAD_BETWEEN(GPIO, 0x0028, 0x0400); /* PAD TO NEXT STRUCT             */
};

struct gpio
{   
    /* Reference this using enum GPIO_PORT_IDX_t */
    struct gpio_port port[8];
};

#define _GPIO ((struct gpio*)GPIO_PORT_BASE)


void gpio_enablePinClock(MCUPIN_t pin)
{   
    switch(pin_aliasLookup(pin).port_idx)
    {
        case GPIO_PORT_IDX_A:
        {
            rccEnablePeriphClock(RCC_PERIPH_CLOCK_gpioa);
        }
        break;
        case GPIO_PORT_IDX_B:
        {
            rccEnablePeriphClock(RCC_PERIPH_CLOCK_gpiob);
        }
        break;
        case GPIO_PORT_IDX_C:
        {
            rccEnablePeriphClock(RCC_PERIPH_CLOCK_gpioc);
        }
        break;
        case GPIO_PORT_IDX_D:
        {
            rccEnablePeriphClock(RCC_PERIPH_CLOCK_gpiod);
        }
        break;
        case GPIO_PORT_IDX_E:
        {
            rccEnablePeriphClock(RCC_PERIPH_CLOCK_gpioe);
        }
        break;
        case GPIO_PORT_IDX_H:
        {
            rccEnablePeriphClock(RCC_PERIPH_CLOCK_gpioh);
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}



void gpio_setPinMode(MCUPIN_t pin, GPIO_MODE_t mode)
{   
    struct pin_map map = pin_aliasLookup(pin);

    struct gpio *testgpio = _GPIO;
    struct gpio_port testport = testgpio->port[map.port_idx];

    _GPIO->port[map.port_idx].MODER &= ~MODER(map.bit);
    switch(mode)
    {   
        /* VALID MODES */
        case GPIO_MODE_alternate:
        case GPIO_MODE_analog:
        case GPIO_MODE_input:
        case GPIO_MODE_output:
        {
            _GPIO->port[map.port_idx].MODER |= mode << MODER_POS(map.bit);
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}



void gpio_setPinSupplyMode(MCUPIN_t pin, GPIO_PIN_SUPPLY_MODE_t mode)
{   
    struct pin_map map = pin_aliasLookup(pin);
    _GPIO->port[map.port_idx].OTYPER &= ~OTYPER(map.bit);
    switch(mode)
    {
        case GPIO_PIN_SUPPLY_MODE_open_drain:
        case GPIO_PIN_SUPPLY_MODE_push_pull:
        {
            _GPIO->port[map.port_idx].OTYPER |= mode << OTYPER_POS(map.bit);
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}


void gpio_setPinPull(MCUPIN_t pin, GPIO_PIN_PULL_MODE_t pullmode)
{
    struct pin_map map = pin_aliasLookup(pin);
    _GPIO->port[map.port_idx].PUPDR &= PUPDR(map.bit);
    switch(pullmode)
    {
        case GPIO_PIN_PULL_MODE_down:
        case GPIO_PIN_PULL_MODE_up:
        case GPIO_PIN_PULL_MODE_none:
        {
            _GPIO->port[map.port_idx].PUPDR |= pullmode << PUPDR_POS(map.bit);
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}


void gpio_setPinSpeed(MCUPIN_t pin, GPIO_SPEED_t speed)
{   
    struct pin_map map = pin_aliasLookup(pin);
    _GPIO->port[map.port_idx].OSPEEDR &= ~OSPEEDR(map.bit);
    switch(speed)
    {
        case GPIO_SPEED_fast:
        case GPIO_SPEED_max:
        case GPIO_SPEED_low:
        case GPIO_SPEED_med:
        {
            _GPIO->port[map.port_idx].OSPEEDR |= speed << OSPEEDR_POS(map.bit);
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}



void gpio_setDigitalPinState(MCUPIN_t pin, GPIO_PIN_STATE_t state)
{
    struct pin_map map = pin_aliasLookup(pin);

    /* Required so order of volatile access is clearly defined */
    uint32_t tempreg = _GPIO->port[map.port_idx].MODER;
    tempreg &= MODER(map.bit);
    tempreg >>= MODER_POS(map.bit);

    switch((GPIO_MODE_t)tempreg)
    {   
        /* Digital Write is meaningless in this context */
        case GPIO_MODE_alternate:
        case GPIO_MODE_analog:
        case GPIO_MODE_input:
        {   
            /* Do nothing */
            return;
        }
        break;
        case GPIO_MODE_output:
        {
            switch(state)
            {
                case GPIO_PIN_STATE_low:
                {
                    _GPIO->port[map.port_idx].BSRR |= BSRR_RST(map.bit);
                }
                break;
                case GPIO_PIN_STATE_high:
                {
                    _GPIO->port[map.port_idx].BSRR |= BSRR_SET(map.bit);
                }
                break;
                default:
                {
                    LL_ASSERT(0);
                }
                break;
            }
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}


GPIO_PIN_STATE_t gpio_getDigitalPinState(MCUPIN_t pin)
{   
    GPIO_PIN_STATE_t state = GPIO_PIN_STATE_err;
    struct pin_map map = pin_aliasLookup(pin);

    /* Required so order of volatile access is clearly defined */
    uint32_t tempreg = _GPIO->port[map.port_idx].MODER;
    tempreg &= MODER(map.bit);
    tempreg >>= MODER_POS(map.bit);

    switch((GPIO_MODE_t)tempreg)
    {   
        case GPIO_MODE_input:
        {   
            /* cast so compiler stops compplaining */
            state = (GPIO_PIN_STATE_t)(!!(_GPIO->port[map.port_idx].IDR & 
                                                            IDR(map.bit)));
        }
        break;
        case GPIO_MODE_output:
        {   
            /* cast so compiler stops compplaining */
            state = (GPIO_PIN_STATE_t)(!!(_GPIO->port[map.port_idx].ODR & 
                                                            ODR(map.bit)));
        }
        break;
        case GPIO_MODE_alternate:
        case GPIO_MODE_analog:
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
    return state;
}



void gpio_setPinAlternateFunc(MCUPIN_t pin, GPIO_ALT_FUNC_t func)
{   
    struct pin_map map = pin_aliasLookup(pin);
    switch(func)
    {
        case GPIO_ALT_FUNC_0:
        case GPIO_ALT_FUNC_1:
        case GPIO_ALT_FUNC_2:
        case GPIO_ALT_FUNC_3:
        case GPIO_ALT_FUNC_4:
        case GPIO_ALT_FUNC_5:
        case GPIO_ALT_FUNC_6:
        case GPIO_ALT_FUNC_7:
        case GPIO_ALT_FUNC_8:
        case GPIO_ALT_FUNC_9:
        case GPIO_ALT_FUNC_10:
        case GPIO_ALT_FUNC_11:
        case GPIO_ALT_FUNC_12:
        case GPIO_ALT_FUNC_13:
        case GPIO_ALT_FUNC_14:
        case GPIO_ALT_FUNC_15:
        {   
            uint32_t bitpos = AFR_POS(map.bit);
            if(map.bit > AFRL_PINBIT_MAX)
            {
                /* We write to AFRH */
                _GPIO->port[map.port_idx].AFRH &= ~(AFR(map.bit));
                _GPIO->port[map.port_idx].AFRH |= func << bitpos;
            }
            else
            {
                /* We write to AFRL */
                _GPIO->port[map.port_idx].AFRL &= ~(AFR(map.bit));
                _GPIO->port[map.port_idx].AFRL |= func << bitpos;
            }
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}


#endif /* !USE_HAL_DRIVER */

