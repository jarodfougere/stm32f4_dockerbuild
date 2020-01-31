#include <stdio.h>

#include "main.h"

//gcc .\Application\core\Src\*.c  .\Application\Middleware\Src\*.c -I .\Application\Core\Inc\ .\Middleware\Inc\


void main(void)
{
    while(1)
    {
        
    }
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