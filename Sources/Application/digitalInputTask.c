/**
  ******************************************************************************
  * File Name          : doDigitalInputPoll
  * Description        : This file provides code ......
  ******************************************************************************
  *
*/
/* Includes ------------------------------------------------------------------*/

#define MAX_DIGITAL_INPUTS 8
#define DEBOUNCE_COUNTS_CLEARED 0
#define DEBOUNCE_COUNTS_ELAPSED 0xfffffffe

typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
}GPIO_PinState;

typedef struct
{
  uint32_t digitalInputStates;            //The Nth bit represents the state of the N-1th input pin
} digitalInputState_t;
digitalInputState_t pinInfoPayload;

extern const systemConfig_t gpioConfig;

// Called from RTOS timer
static void doDigitalInputPoll()
{
  static uint32_t debounce_counts[MAX_DIGITAL_INPUTS]; /* stores the number of polling intervals a pin has been at its trigger level */

  uint32_t i = 0;
  GPIO_PinState pinState;

    // Check every pin
    do
    {
        /* measure current pin level */
        if (gpioConfig.digitalIns[i].cfg.active == ACTIVE)
        {
          pinState = HAL_GPIO_ReadPin(mcuPins[DIGITAL_INPUT][DIGITAL_INPUT_PIN_IDX(i)].port, mcuPins[DIGITAL_INPUT][DIGITAL_INPUT_PIN_IDX(i)].bit);
          if (pinState == (GPIO_PinState)gpioConfig.digitalIns[i].interface.triglvl)
          {
            /* Test to see if debounce interval is expired */
            if (debounce_counts[i] == gpioConfig.digitalIns[i].interface.debounce)
            {
              /* set the appropriate bit in the payload */
              if (pinState == GPIO_PIN_SET)
              {
                pinInfoPayload.digitalInputStates |= (1 << i);
              }
              else
              {
                pinInfoPayload.digitalInputStates &= ~(1 << i);
              }

              /* set counts to the indicator value so we know the countdown has elapsed */
              debounce_counts[i] = DEBOUNCE_COUNTS_ELAPSED;

            }
            else if (debounce_counts[i] != DEBOUNCE_COUNTS_ELAPSED)
            {
              /* increase debounce counts */
              debounce_counts[i]++;
            }
          }
          else /* pin level is "normal" */
          {
            /* set the appropriate bit in the payload for TX */
            if (pinState == GPIO_PIN_SET)
            {
              /* set the bit for this pin */
              pinInfoPayload.digitalInputStates |= (1 << i);
            }
            else
            {
              /* clear the bit for this pin */
              pinInfoPayload.digitalInputStates &= ~(1 << i);
            }

            /* WE ONLY CLEAR THE DEBOUNCE COUNTS BECAUSE THE PIN HAS RETURNED TO ITS "normal" state */
            debounce_counts[i] = DEBOUNCE_COUNTS_CLEARED;
          }
        }
        else
        {
          /* pin is not active so disable LED and clear debounce counts */
          debounce_counts[i] = DEBOUNCE_COUNTS_CLEARED;
        }
    } while (++i < MAX_DIGITAL_INPUTS);
}


