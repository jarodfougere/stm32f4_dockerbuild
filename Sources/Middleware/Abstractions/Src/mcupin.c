/**
 * @file mcupin.c
 * @author Carl Mattatall
 * @brief This module provides functionality for an "mcu pin" abstraction
 * that combines the overlay of a GPIO port bit mask / CR / CFGR for that
 * port.
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorportated
 */

#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
#include "stm32f4xx.h"      /* CMSIS definitions */ 
#include "stm32f4xx_hal.h"  /* stm32 hal apis */
#else
#include "rimot_gpio.h"
#endif 
#include "mcupin.h"

void writepin(const struct mcu_pin *pin, enum pinstate state)
{   
#if defined(USE_HAL_DRIVER)
    switch (state)
    {
    case PIN_SET:
        HAL_GPIO_WritePin(pin->port, pin->bit, GPIO_PIN_SET);
    case PIN_RST:
        HAL_GPIO_WritePin(pin->port, pin->bit, GPIO_PIN_RESET);
        break;
    case PIN_TOGGLE:
        HAL_GPIO_TogglePin(pin->port, pin->bit);
        break;
    default:
#if !defined(NDEBUG)
        while (1)
        {
            /* hang forever */
        }
#endif
        break;
    }
#else   /* DEBUG BUILD */

    /* REMOVE ME WHEN YOU IMPLEMENT A BAREMETAL DRIVER LAYER */
    #warning NO BAREMETAL IMPLEMENTATION HAS BEEN PROVIDED FOR writepin 

#endif  /* HAL OR BAREMETAL */
}


enum pinstate readpin(const struct mcu_pin *pin)
{   
#if defined(USE_HAL_DRIVER)
    if (NULL != pin && NULL != pin->port)
    {
        switch (HAL_GPIO_ReadPin(pin->port, pin->bit))
        {
        case GPIO_PIN_SET:
            return PIN_SET;
            break;
        case GPIO_PIN_RESET:
            return PIN_RST;
            break;
        default:
#if !defined(NDEBUG)
            while (1)
            {
                /* hang forever */
            }
#else
            /* return invalid so that caller can check for error */
            return (enum pinstate)(-1);
            break;
#endif  /* DEBUG BUILD */
        }
    }
    else
    {
#if !defined(NDEBUG)
        while (1)
        {
            /* hang forever */
        }
#else
        return (enum pinstate)(-1);
#endif  /* DEBUG BUILD */
    }
#else
    #warning NO BAREMETAL IMPLEMENTATION HAS BEEN PROVIDED FOR readpin
    /* REMOVE ME WHEN YOU IMPLEMENT A BAREMETAL DRIVER LAYER */

#endif  /* HAL OR BAREMETAL */
}

#endif
