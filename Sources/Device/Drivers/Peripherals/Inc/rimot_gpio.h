#ifndef RIMOT_MCU_GPIO
#define RIMOT_MCU_GPIO
#ifdef __cplusplus
extern "C"
{
#endif /* C linkage */

#include "rimot_register_padding.h"
#include "rimot_pin_aliases.h"

    /* modes for a given mcu gpio pin */
    typedef enum
    {
        /* Critical that the values are unsigned */
        GPIO_MODE_input = 0U,
        GPIO_MODE_output = 1U,
        GPIO_MODE_alternate = 2U, /* PERIPHERAL FUNCS. */
        GPIO_MODE_analog = 3U,
    } GPIO_MODE_t;

    /* transition speeds for a given mcu gpio pin */
    typedef enum
    {
        GPIO_SPEED_low = 0U,
        GPIO_SPEED_med = 1U,
        GPIO_SPEED_fast = 2U,
        GPIO_SPEED_max = 3U,
    } GPIO_SPEED_t;

    /* output modes for a gvien mcu gpio pin */
    typedef enum
    {
        GPIO_PIN_SUPPLY_MODE_push_pull = 0U,
        GPIO_PIN_SUPPLY_MODE_open_drain = 1U,
    } GPIO_PIN_SUPPLY_MODE_t;

    typedef enum
    {
        GPIO_PIN_PULL_MODE_none = 0,
        GPIO_PIN_PULL_MODE_down = 1,
        GPIO_PIN_PULL_MODE_up = 2,
    } GPIO_PIN_PULL_MODE_t;

    typedef enum
    {
        GPIO_PIN_STATE_low = 0,
        GPIO_PIN_STATE_high = 1,

        /* Need an error value in case of caller breaching contract */
        GPIO_PIN_STATE_err = -1,
    } GPIO_PIN_STATE_t;

    typedef enum
    {
        GPIO_ALT_FUNC_0 = 0,
        GPIO_ALT_FUNC_1 = 1,
        GPIO_ALT_FUNC_2 = 2,
        GPIO_ALT_FUNC_3 = 3,
        GPIO_ALT_FUNC_4 = 4,
        GPIO_ALT_FUNC_5 = 5,
        GPIO_ALT_FUNC_6 = 6,
        GPIO_ALT_FUNC_7 = 7,
        GPIO_ALT_FUNC_8 = 8,
        GPIO_ALT_FUNC_9 = 9,
        GPIO_ALT_FUNC_10 = 10,
        GPIO_ALT_FUNC_11 = 11,
        GPIO_ALT_FUNC_12 = 12,
        GPIO_ALT_FUNC_13 = 13,
        GPIO_ALT_FUNC_14 = 14,
        GPIO_ALT_FUNC_15 = 15,
    } GPIO_ALT_FUNC_t;

    /**
 * @fn gpio_pinLookup
 * @brief Returns a structure that maps a pin number on the
 * MCU to a GPIO port peripheral and the bit in that peripheral's
 * registers corresponding to the mcu pin.
 * 
 * @param pin the number of the pin on the mcu.
 * @return struct pin_map* the mapping structure
 */
    struct pin_map *gpio_pinlookup(uint32_t mcu_pin_number);

    /**
 * @fn gpio_setPinMode
 * @brief Set the pin mode of a given gpio pin
 * 
 * @param mode one of GPIO_MODE_t
 * @param pin  one of MCUPIN_t
 */
    void gpio_setPinMode(MCUPIN_t pin, GPIO_MODE_t mode);

    /**
 * @fn gpio_enablePinClock
 * @brief enables the AHB bus clock for the gpio peripheral corresponding
 * to the mcu pin number.
 * 
 * @param mcu_pin_number : the number of the mcu pin desired to be used as a 
 * gpio
 */
    void gpio_enablePinClock(MCUPIN_t pin);

    /**
 * @fn gpio_setPinSupplyMode
 * @brief sets the current mode of a given pin.
 * 
 * @param pin one of MCUPIN_t
 * @param mode one of GPIO_PIN_SUPPLY_MODE_t
 */
    void gpio_setPinSupplyMode(MCUPIN_t pin, GPIO_PIN_SUPPLY_MODE_t mode);

    /**
 * @fn gpio_setPinPull
 * @brief Set the pullup/pull down mode for a gpio pin
 * 
 * @param pin one of MCUPIN_t
 * @param pullmode one of GPIO_PIN_PULL_MODE_t
 */
    void gpio_setPinPull(MCUPIN_t pin, GPIO_PIN_PULL_MODE_t pullmode);

    /**
 * @fn gpio_setPinSpeed
 * @brief set the pin speed (how quickly it can detect or drive changes
 * in the pin level) for a given pin on the microcontroller package
 * 
 * @param pin one of MCUPIN_t
 * @param speed one of GPIO_SPEED_t
 */
    void gpio_setPinSpeed(MCUPIN_t pin, GPIO_SPEED_t speed);

    /**
 * @fn gpio_setDigitalPinState
 * @brief Set the pin state of an mcu pin. 
 * If the pin mode is NOT output, this will
 * do nothing and immediately return.
 * 
 * @param pin one of MCUPIN_t : the pin on the microcontroller packet
 * @param state one of GPIO_PIN_STATE_t
 */
    void gpio_setDigitalPinState(MCUPIN_t pin, GPIO_PIN_STATE_t state);

    /**
 * @fn gpio_getDigitalPinState
 * @brief Get the pin state of an mcu pin
 * 
 * @param pin one of MCUPIN_t : the pin on the mcu package
 * @return GPIO_PIN_STATE_t the state of the mcu pin
 */
    GPIO_PIN_STATE_t gpio_getDigitalPinState(MCUPIN_t pin);

    /**
 * @fn gpio_setPinAlternateFunc
 * @brief set the pin to an alternate function.
 * If the hardware does not support an alternate function, this will
 * exhibit undefined behaviour. 
 * 
 * @param pin one of MCUPIN_t
 * @param func one of GPIO_ALT_FUNC_t
 */
    void gpio_setPinAlternateFunc(MCUPIN_t pin, GPIO_ALT_FUNC_t func);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_GPIO */
