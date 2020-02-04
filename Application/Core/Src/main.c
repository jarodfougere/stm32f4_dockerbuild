#include <stdio.h>

#include "main.h"
#include "middlewares.h"
#include "serialcommands.h"

void testParse(void);

int main(void)
{   
    printf("HELLO WORLD\n");
    //testParse();    
    return 0;
}


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

void testParse(void)
{   
    unsigned int j;
    for(j = 0; j < sizeof(json)/sizeof(json[0]); j++)
    {
        handle_command(json[j]);
    }
}