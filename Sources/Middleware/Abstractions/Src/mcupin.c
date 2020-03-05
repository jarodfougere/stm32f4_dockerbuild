#if defined(MCU_APP)
#include "drivers.h"
#include "mcupin.h"

void writepin(const struct mcu_pin *pin, enum pinstate state)
{
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
}

enum pinstate readpin(const struct mcu_pin *pin)
{
    if (NULL != pin && NULL != pin->port)
    {
        switch (HAL_GPIO_ReadPin(pin->port, pin->bit))
        {
        case GPIO_PIN_SET:
            return PIN_SET;
            break; /* redundant but explicitly deny fallthrough */
        case GPIO_PIN_RESET:
            return PIN_RST;
            break; /* redundant but explicitly deny fallthrough */
        default:
#if !defined(NDEBUG)
            while (1)
            {
                /* hang forever */
            }
#else
            /* return invalid so that calling module sees err */
            return (enum pinstate)(-1);
#endif
            break;
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
#endif
    }
}

#endif
