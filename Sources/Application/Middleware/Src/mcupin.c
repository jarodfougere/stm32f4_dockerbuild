#if defined(MCU_APP)
#include "drivers.h" 
#include "mcupin.h"

void writepin(const struct mcu_pin *pin, enum pinstate state)
{   
    switch (state)
    {
        case PIN_SET:
        case PIN_RST:
            HAL_GPIO_WritePin(pin->port, pin->bit, state);
            break;
        case PIN_TOGGLE:
            HAL_GPIO_TogglePin(pin->port, pin->bit);
            break;
        default:
            #if !defined(NDEBUG)
            FORCE_ASSERT
            #endif
        break;
    }
}


enum pinstate readpin(const struct mcu_pin *pin)
{
    return HAL_GPIO_ReadPin(pin->port, pin->bit);
}


#endif
