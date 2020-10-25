#include <stdint.h>
#include <limits.h>
#include <string.h>

#include "systemConfig.h"

#include "cmsis_os.h"
#include "stm32f4xx.h"


/** @note IF YOU ADD THREADS TO FREERTOS.C, THEY MUST BE ADDED HERE AS WELL */
extern osThreadId_t defaultTaskHandle;
extern osThreadId_t usbSerialTaskHandle;
extern osThreadId_t digitalInputTaskHandle;
extern osThreadId_t digitalOutputTaskHandle;
extern osThreadId_t analogInputTaskHandle;
extern osThreadId_t rfSensorTaskHandle;
extern osThreadId_t mothSensorTaskHandle;


/**
 * @brief Perform RTOS deinit and peripheral deInitialization
 * in preparation for power cycle
 */
static void resetPrep(void);


/**
 * @brief use the NVIC to perform a system reset
 */
static void reset(void);

/* clang-format off */
systemConfig_t systemconfig_heap __USED;
const systemConfig_t systemconfig __USED;



#if defined (__ICCARM__) && defined(__GNUC__) /* USING ICCARM EWARM */
#warning PLACEMENT FOR SYSTEMCONFIG DEFAULTS NOT IMPLEMENTED IN ICCARM
#elif defined (__GNUC__) /* gcc with eabi or linux-eabi */
const systemConfig_t systemconfig_defaults __USED __attribute__ ((section ("sysconfig_defaults"))) =
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


#if defined (__ICCARM__) && defined(__GNUC__) /* USING ICCARM EWARM */
const systemConfig_t systemconfig @ DATA_EEPROM_BASE =
#elif defined (__GNUC__) /* gcc with eabi or linux-eabi */
const systemConfig_t systemconfig __USED __attribute__ ((section ("sysconfig_eeprom"))) =
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
    __HAL_RCC_RTC_DISABLE();
    resetPrep();
    reset();
}


void systemReset(void)
{
    resetPrep();
    reset();
}


bool should_bootjump(void)
{
#if defined(USE_HAL_DRIVER)
    if (RTC->BKP0R)
    {
        return true;
    }
    else
    {
        return false;
    }
#else
#warning NO IMPLEMENTATION PROVIDED FOR should_bootjump without STM32 HAL APIs
#endif
}


void bootjump(void)
{
#if defined(USE_HAL_DRIVER)
    __HAL_RCC_RTC_ENABLE();
    RTC->BKP0R = 0; /* clear bootjump bit for next cycle */
    __HAL_RCC_RTC_DISABLE();

    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t               PAGEError;

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_MASSERASE;
    EraseInitStruct.Banks     = FLASH_BANK_1;
    HAL_FLASH_Unlock();
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) == HAL_OK)
    {
    }
    else
    {
        /** @todo NEED A BACKOUT PROCEDURE. REALLY NOT SURE WHAT WE SHOULD DO
         * HERE.
         *
         * MAYBE BEFORE ERASING WE SHOULD READ THE MEMORY BACK OUT OF THE FLASH
         * WORD-BYTE-WORD AND TRANSMIT THE BYTES OVER CDC TO THE MCU (WITH ACK /
         * NAK CONFIRMS AND SOME SORT OF CHECKSUM)
         */
    }
    HAL_FLASH_Lock();

    /* Jump to start of bootloader in system memory */
    void (*SysMemBootJump)(void);
    volatile uint32_t addr = 0x1FF00000;
    SysMemBootJump         = (void (*)(void))(*((uint32_t *)(addr + 4)));
    SysMemBootJump();
#else
#warning NO IMPLEMENTATION HAS BEEN PROVIDED FOR bootjump without STM32 HAL APIS
#endif
}


static void resetPrep(void)
{
    osThreadSuspend(defaultTaskHandle);
    osThreadSuspend(usbSerialTaskHandle);
    osThreadSuspend(digitalInputTaskHandle);
    osThreadSuspend(digitalOutputTaskHandle);
    osThreadSuspend(analogInputTaskHandle);
    osThreadSuspend(rfSensorTaskHandle);
    osThreadSuspend(mothSensorTaskHandle);

    /** @todo ADD MORE STUFF HERE AS REQUIRED */
}


static void reset(void)
{
#if defined(USE_HAL_DRIVER)
    NVIC_SystemReset();
#else
#warning NO IMPLEMENTATION HAS BEEN PROVIDED FOR reset without STM32 HAL APIs
#endif
}
