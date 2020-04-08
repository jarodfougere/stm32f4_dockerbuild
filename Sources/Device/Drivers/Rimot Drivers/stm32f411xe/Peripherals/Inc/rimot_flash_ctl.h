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



void flashSetPrefetchBuffer(FLASH_PREFETCH_BUFFER_MODE_t mode);
void flashSetPrefetchDataCacheMode(FLASH_PREFETCH_DATA_CACHE_MODE_t mode);
void flashSetInstructionCacheMode(FLASH_PREFETCH_INSTRUCTION_CACHE_MODE_t mode);



#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_FLASH_CONTROLLER */