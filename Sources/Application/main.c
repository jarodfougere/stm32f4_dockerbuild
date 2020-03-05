#include "main.h"


const char *json[] =
{   
    "{\"GPIO_PIN_UPDATE\": true}",
    "{\"GPIO_DEVICE_INFO\" : 1}",
    "{\"system\":\"info\"}",
    "{\"write\":{\"mode\" : 1}}",
    "{\"GPIO_PIN_CONFIG\":{\"id\" : 1, \"type\" : 2, \"active\":1, \"label\" : 5, \"debounce\": 100}}",
    "{\"system\":\"reset_boot\"}",
    "{\"system\":\"reset_main\"}",
    "{\"write\": {\"pin_info_interval\" : 5}}",
    "{\"write\": {\"hb_interval\" : 5}}",
    NULL
};


extern void (*taskLoop[])(struct rimot_device*);
extern const int32_t num_tasks;

int main(void)
{   
    /* check if we have returned here from bootloader */
    //TODO:
    
    struct rimot_device dev = RIMOT_DEV_DFLT_INITIALIZER;

    /* application architecture is superloop */
    while (1)
    {   
        int32_t task_idx = 0;
        taskLoop[task_idx++ % num_tasks](&dev);
    }
}




