#include <stdio.h>

#include "main.h"
#include "debug.h"
#include "middleware.h"
#include "command_parse.h"
#include "rimot_device.h"

const char *json[] =
{   
    "{\"system\":\"info\"}",
    "{\"write\":{\"mode\" : 1}}",
    "{\"GPIO_PIN_CONFIG\":{\"id\" : 1, \"type\" : 2, \"active\":1, \"label\" : 5, \"debounce\": 100}}",
    "{\"system\":\"reset_boot\"}",
    "{\"system\":\"reset_main\"}",
    "{\"read\":\"hb_interval\"}",
    "{\"read\":\"pin_info_interval\"}",
    "{\"read\":\"fwVersion\"}",
    "{\"read\":\"hwVersion\"}",
    "{\"write\": {\"pin_info_interval\" : 5}}",
    "{\"write\": {\"hb_interval\" : 5}}",
    "{\"GPIO_PIN_UPDATE\": true}",
    "{\"GPIO_DEVICE_INFO\"}",
};


int main(void)
{   
    struct rimot_device device = RIMOT_DEVICE_DEFAULTS;
    
    int i;
    for(i = 0; i < 15; i++)
    {
        int status = parse_command(json[i], &device);
        if(0 != status)
        {
            break;
        }
    }
    return 0;
}




