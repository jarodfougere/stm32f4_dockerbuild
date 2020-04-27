#ifndef RIMOT_FLASH_CONTROLLER
#define RIMOT_FLASH_CONTROLLER
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

typedef enum
{
    FLASH_PREFETCH_INSTRUCTION_CACHE_MODE_enabled,
    FLASH_PREFETCH_INSTRUCTION_CACHE_MODE_disabled,
}   FLASH_PREFETCH_INSTRUCTION_CACHE_MODE_t;


typedef enum
{
    FLASH_PREFETCH_DATA_CACHE_MODE_enabled,
    FLASH_PREFETCH_DATA_CACHE_MODE_disabled,
}   FLASH_PREFETCH_DATA_CACHE_MODE_t;


typedef enum
{
    FLASH_PREFETCH_BUFFER_MODE_enabled,
    FLASH_PREFETCH_BUFFER_MODE_disabled,
}   FLASH_PREFETCH_BUFFER_MODE_t;


typedef enum
{
    FLASH_WAIT_CYCLES_0,
    FLASH_WAIT_CYCLES_1,
    FLASH_WAIT_CYCLES_2,
    FLASH_WAIT_CYCLES_3,
    FLASH_WAIT_CYCLES_4,
    FLASH_WAIT_CYCLES_5,
    FLASH_WAIT_CYCLES_6,
    FLASH_WAIT_CYCLES_7,
    FLASH_WAIT_CYCLES_8,
    FLASH_WAIT_CYCLES_9,
    FLASH_WAIT_CYCLES_10,
    FLASH_WAIT_CYCLES_11,
    FLASH_WAIT_CYCLES_12,
    FLASH_WAIT_CYCLES_13,
    FLASH_WAIT_CYCLES_14,
    FLASH_WAIT_CYCLES_15,
}   FLASH_WAIT_CYCLES_t;



void flashSetPrefetchBuffer(FLASH_PREFETCH_BUFFER_MODE_t mode);
void flashSetPrefetchDataCacheMode(FLASH_PREFETCH_DATA_CACHE_MODE_t mode);
void flashSetInstructionCacheMode(FLASH_PREFETCH_INSTRUCTION_CACHE_MODE_t mode);

void flashSetWaitCycles(FLASH_WAIT_CYCLES_t cycles);
void flashUnlockACR(void);
int flash_isBusy(void);


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_FLASH_CONTROLLER */
