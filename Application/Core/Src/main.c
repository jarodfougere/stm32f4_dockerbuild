#include <stdio.h>

#include "main.h"

//gcc .\*\*\*.c .\*\*\*\*.c -I .\Application\Core\Inc\ -I .\Application\Port\Inc -I .\Middleware\ -I .\Middleware\Inc\ -I .\Drivers\CMSIS\Device\ST\STM32F3xx\Include\ -I .\Drivers\CMSIS\Core\Include\

void testParse(void);

int main()
{
    while(1)
    {
        testParse();
    }
    return 0;
}


void testParse(void)
{   
    printf("please enter a JSON in the console.\n");
    char msg[250];
    if(NULL != gets(msg))
    {   
        printf("received data >%s<\n", msg);
        // parse the tokens using jsmn

        // do some stuff 

        //get an idea for how JSMN works and make a plan to implement the data parsing module
    }
}