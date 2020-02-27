#include <stdio.h>

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



int main(void)
{   
    struct rimot_device dev = RIMOT_DEV_DFLT_INITIALIZER;

    /* application architecture is superloop */
    while (1)
    {
    }
}




