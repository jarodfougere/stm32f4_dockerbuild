#include <stdio.h>

#include "main.h"
#include "middleware.h"
#include "command_parse.h"



const char* json[] = 
{   
    "{\"system\":\"info\"}",
    "{\"system\":\"reset_boot\"}",
    "{\"system\":\"reset_main\"}",
    "{\"system\":{\"mode\" : 1}}",
    "{\"read\":\"hb_interval\"}",
    "{\"read\":\"pin_info_interval\"}",
    "{\"read\":\"fwVersion\"}",
    "{\"read\":\"hwVersion\"}",
    "{\"write\": {\"pin_info_interval\" : 5}}",
    "{\"write\": {\"hb_interval\" : 5}}",
    "{\"write\": {\"config\" : true}}",
    "{\"GPIO_PIN_CONFIG\":{\"id\" : 1, \"type\" : 2, \"active\":1, \"label\" : 5, \"debounce\": 100}}",
    "{\"GPIO_PIN_UPDATE\": true}",
    "{\"GPIO_DEVICE_INFO\"}",
};



int main(int32_t argc, char *argv[])
{   
    return 0;
}




