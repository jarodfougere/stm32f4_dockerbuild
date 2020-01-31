#include <stdint.h>
#include "serialcommands.h"
#include "middlewares.h"
#include "parsing.h"





void handle_command(const char* cmd) 
{
    uint_fast8_t token_count;
    parseJSON(cmd, &token_count))


    if (PARSE_STATUS_OK == parseJSON(cmd, &token_count))
    {
        //INSERT BRANCH DECISIONS
        uint_fast8_t tkn_i = 0;

        for (tkn_i = 0; tkn_i < token_count; tkn_i++)
        {
            if(0 == tkn_i && JSMN_OBJECT != getToken(i)->.type)
            {
                break;
            }
            else
            {

            }
        }
    }


    if (parser.initStatus > 0 && parser.tkns[tknIdex].type == JSMN_OBJECT &&            parser.tkns[++tknIdex].type == JSMN_STRING)
    {
        /* SYSTEM INFO */
        if (CURRENT_KEY_EQUAL("systick"))
        {
            printf("Recieved \"systick\" token");
        } else if (CURRENT_KEY_EQUAL("rfdetect"))
        {
            printf("Recieved \"rfdetect\" token");
        } 
        else if (CURRENT_KEY_EQUAL("value"))
        {
            printf("Recieved \"value\" token"); 
        } 
        else if (CURRENT_KEY_EQUAL("RF_CONFIG"))
        {
            printf("Recieved \"RF_CONFIG\" token"); 
        } 
        else if (CURRENT_KEY_EQUAL("system"))
        {
            printf("Recieved \"system\" token"); 
        } 
        else if (CURRENT_KEY_EQUAL("read"))
        {
            printf("Recieved \"read\" token"); 
        } 
        else if (CURRENT_KEY_EQUAL("write"))
        {
            printf("Recieved \"write\" token"); 
        } 
        else if (CURRENT_KEY_EQUAL("GPIO_PIN_CONFIG"))
        {
            printf("Recieved \"GPIO_PIN_CONFIG\" token"); 
        } 
        else if (CURRENT_KEY_EQUAL("GPIO_PIN_UPDATE"))
        {
            printf("Recieved \"GPIO_PIN_UPDATE\" token");
        } 
        else if (CURRENT_KEY_EQUAL("GPIO_PIN_INFO"))
        {
            printf("Recieved \"GPIO_PIN_INFO\" token");
        } 
        else if (CURRENT_KEY_EQUAL("GPIO_PIN_CMD"))
        {
            printf("Recieved \"GPIO_PIN_CMD\" token");
        }
        else {
            printf("This JSON is not valid");
        }
    }
}
