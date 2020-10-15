#include <stdint.h>
#include <limits.h>
#include <string.h>

#include "systemConfig.h"

#include "cmsis_os.h"
#include "stm32f4xx.h"

#if 0

#define resetPrep(x)                                                           \
    do                                                                         \
    {                                                                          \
        osThreadSuspendAll();                                                  \
    } while (0)

#endif

#define reset(x)                                                               \
    do                                                                         \
    {                                                                          \
        NVIC_SystemReset();                                                    \
    } while (0)


/* clang-format off */

systemConfig_t systemconfig_heap __USED ;
const systemConfig_t systemconfig __USED ;

const systemConfig_t systemconfig_defaults __USED  =
{
  .outpostID = "000000",
  .pinInfoInterval = DEFAULT_DCIN_INFO_INTERVAL_S,
  .runTickInterval = DEFAULT_RUNTICK_INTERVAL_S,

  .digitalIns[0]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 1,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .digitalIns[1]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 2,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }    
  },

  .digitalIns[2]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 3,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .digitalIns[3]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 4,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .digitalIns[4]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 5,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .digitalIns[5]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 6,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .digitalIns[6]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 7,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .digitalIns[7]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 8,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    { 
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .relays[0]      = 
  {
    .cfg = 
    {
      .type      = LATCHING_RELAY,
      .active    = INACTIVE,
      .id        = 1,
      .label     = 0,
      .priority  = 0,
    },

    .interface = 
    {
      .defaultState = OPEN,
      .currentState = OPEN,
      .holdTime = 0
    }
  },

  .relays[1]      = 
  {
    .cfg = 
    {
      .type     = LATCHING_RELAY,
      .active   = INACTIVE,
      .id       = 2,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .defaultState = OPEN,
      .currentState = OPEN,
      .holdTime = 0
    }
  },

  .relays[2]      = 
  {
    .cfg = 
    {
      .type       = LATCHING_RELAY,
      .active     = INACTIVE,
      .id         = 3,
      .label      = 0,
      .priority   = 0,
    },

    .interface = 
    {
      .defaultState = OPEN,
      .currentState = OPEN,
      .holdTime = 0
    }
  },

  .relays[3]      = 
  {
    .cfg = 
    {
      .type       = LATCHING_RELAY,
      .active     = INACTIVE,
      .id         = 4,
      .label      = 0,
      .priority   = 0,
    },

    .interface = 
    { 
      .defaultState = OPEN,
      .currentState = OPEN,
      .holdTime = 0
    }
  },

  .analogIns[0]   = 
  {
    .cfg = 
    {
      .type     = ANALOG_INPUT,
      .active   = INACTIVE,
      .id       = 1,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      /* TODO: When V3.1 comes out, each battery will have a different high side switch so we need firmware to support individual sampling rates */
      .samplePeriod = 15, /* 150 * 100 == 15000ms == 2.5minute */
    }
  },

  .analogIns[1]   = 
  {
    .cfg = 
    {
      .type     = ANALOG_INPUT,
      .active   = INACTIVE,
      .id       = 2,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      /* TODO: When V3.1 comes out, each battery will have a different high side switch so we need firmware to support individual sampling rates */
      .samplePeriod = 15, /* 150 * 100 == 15000ms == 2.5minute */
    }
  },

  .analogIns[2]   = 
  {
    .cfg = 
    {
      .type       = ANALOG_INPUT,
      .active     = INACTIVE,
      .id         = 3,
      .label      = 0,
      .priority   = 0,
    },

    .interface = 
    {
      /* TODO: When V3.1 comes out, each battery will have a different high side switch so we need firmware to support individual sampling rates */
      .samplePeriod = 15, /* 150 * 100 == 15000ms == 2.5minute */

    }
  },

  .analogIns[3]   = 
  {
    .cfg = 
    {
      .type     = ANALOG_INPUT,
      .active   = INACTIVE,
      .id       = 4,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      /* TODO: When V3.1 comes out, each battery will have a different high side switch so we need firmware to support individual sampling rates */
      .samplePeriod = 15, /* 150 * 100 == 15000ms == 2.5minute */
    }
  },
};


#if defined (__ICCARM__) && defined(__GNUC__) /* USING ICCARM EWARM */
const systemConfig_t systemconfig @ DATA_EEPROM_BASE =
#elif defined (__GNUC__) /* gcc with eabi or linux-eabi */
const systemConfig_t systemconfig __attribute__ ((section ("sysconfig_eeprom"))) =
#endif
{
  .outpostID = "000000",
  .pinInfoInterval = DEFAULT_DCIN_INFO_INTERVAL_S,
  .runTickInterval = DEFAULT_RUNTICK_INTERVAL_S,
  .digitalIns[0]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 1,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }

  },

  .digitalIns[1]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 2,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }    
  },

  .digitalIns[2]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 3,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .digitalIns[3]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 4,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .digitalIns[4]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 5,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .digitalIns[5]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 6,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .digitalIns[6]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 7,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .digitalIns[7]  = 
  {
    .cfg = 
    {
      .type     = DIGITAL_INPUT,
      .active   = INACTIVE,
      .id       = 8,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    { 
      .triglvl = FALLING,
      .debounce = 0
    }
  },

  .relays[0]      = 
  {
    .cfg = 
    {
      .type      = LATCHING_RELAY,
      .active    = INACTIVE,
      .id        = 1,
      .label     = 0,
      .priority  = 0,
    },

    .interface = 
    {
      .defaultState = OPEN,
      .currentState = OPEN,
      .holdTime = 0
    }
  },

  .relays[1]      = 
  {
    .cfg = 
    {
      .type     = LATCHING_RELAY,
      .active   = INACTIVE,
      .id       = 2,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      .defaultState = OPEN,
      .currentState = OPEN,
      .holdTime = 0
    }
  },

  .relays[2]      = 
  {
    .cfg = 
    {
      .type       = LATCHING_RELAY,
      .active     = INACTIVE,
      .id         = 3,
      .label      = 0,
      .priority   = 0,
    },

    .interface = 
    {
      .defaultState = OPEN,
      .currentState = OPEN,
      .holdTime = 0
    }
  },

  .relays[3]      = 
  {
    .cfg = 
    {
      .type       = LATCHING_RELAY,
      .active     = INACTIVE,
      .id         = 4,
      .label      = 0,
      .priority   = 0,
    },

    .interface = 
    { 
      .defaultState = OPEN,
      .currentState = OPEN,
      .holdTime = 0
    }
  },

  .analogIns[0]   = 
  {
    .cfg = 
    {
      .type     = ANALOG_INPUT,
      .active   = INACTIVE,
      .id       = 1,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      /* TODO: When V3.1 comes out, each battery will have a different high side switch so we need firmware to support individual sampling rates */
      .samplePeriod = 15, /* 150 * 100 == 15000ms == 2.5minute */
    }
  },

  .analogIns[1]   = 
  {
    .cfg = 
    {
      .type     = ANALOG_INPUT,
      .active   = INACTIVE,
      .id       = 2,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      /* TODO: When V3.1 comes out, each battery will have a different high side switch so we need firmware to support individual sampling rates */
      .samplePeriod = 15, /* 150 * 100 == 15000ms == 2.5minute */
    }
  },

  .analogIns[2]   = 
  {
    .cfg = 
    {
      .type       = ANALOG_INPUT,
      .active     = INACTIVE,
      .id         = 3,
      .label      = 0,
      .priority   = 0,
    },

    .interface = 
    {
      /* TODO: When V3.1 comes out, each battery will have a different high side switch so we need firmware to support individual sampling rates */
      .samplePeriod = 15, /* 150 * 100 == 15000ms == 2.5minute */

    }
  },

  .analogIns[3]   = 
  {
    .cfg = 
    {
      .type     = ANALOG_INPUT,
      .active   = INACTIVE,
      .id       = 4,
      .label    = 0,
      .priority = 0,
    },

    .interface = 
    {
      /* TODO: When V3.1 comes out, each battery will have a different high side switch so we need firmware to support individual sampling rates */
      .samplePeriod = 15, /* 150 * 100 == 15000ms == 2.5minute */
    }
  },
};

/* clang-format on */


static char device_name[USER_DEVICE_NAME_SIZE + 1] = "Unnamed";

char *getDeviceName(void)
{
    return device_name;
}


int setDeviceName(const char *new_name)
{
    if (new_name == NULL || strlen(new_name) > USER_DEVICE_NAME_SIZE)
    {
        return -1; /* too large */
    }
    else
    {
        strcpy(device_name, new_name);
        return 0;
    }
}


void jumpToBootloader(void)
{
    __HAL_RCC_RTC_ENABLE();
    RTC->BKP0R = 0xF0CA;
    // resetPrep();
    reset();
}


void systemReset(void)
{
    // resetPrep();
    reset();
}
