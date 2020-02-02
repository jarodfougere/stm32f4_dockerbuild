#include <string.h>

#include "parsing.h"

typedef struct
{
    jsmn_parser p;
    jsmntok_t   tkns[MAX_PARSER_JSMNTOK_CNT];
    int16_t     initStatus;
}   jsonParser_t;

static jsonParser_t parser;


jsmntok_t* getToken(uint32_t i)
{   
    /* retval */
    jsmntok_t* tkn;

    /* if parsing didnt fail */
    if(0 < parser.initStatus) 
    {   
        /* if access index is inside array of tokens */
        /* cast is because we've done boundary check on value of initStatus */
        if(i < (uint32_t)parser.initStatus)   
        {
            tkn = &parser.tkns[i];
        }
        else
        {
            tkn = NULL;
        }
    }
    return tkn;
}

uint32_t parseJSON(const int8_t* json, uint32_t* const token_count)
{   
    uint32_t status = PARSE_STATUS_OK;
    if((void*)0 != json) //validate received char ptr
    {   
        //reset the parsing params
        parser.p.pos = 0;
        parser.p.toknext = 0;
        parser.p.toksuper = -1; //top node has no parent node 
        
        parser.initStatus = jsmn_parse(&parser.p, (const char*)json, 
                                        strlen((const char*)json), 
                                        parser.tkns, 
                                        MAX_PARSER_JSMNTOK_CNT);
        if(parser.initStatus < 0)
        {
            switch((jsmnerr_t)parser.initStatus)
            {
                case JSMN_ERROR_INVAL:
                    status = PARSE_STATUS_INVALID_CHARACTER;
                break;
                case JSMN_ERROR_NOMEM:
                    status = PARSE_STATUS_NOT_ENOUGH_TOKENS;
                break;
                case JSMN_ERROR_PART:
                    status = PARSE_STATUS_PARTIAL_JSON_STRING;
                break;
            }
        }
        else
        {   
            //WARNING: this suffers from possible problems RE integer promotion //when initstatus > 2^16 -1. (in practice this should never occur)
            *token_count = parser.initStatus;
        }
    }
    else
    {
        status = PARSE_STATUS_NULL_JSON_STRING;
    }

    if(PARSE_STATUS_OK != status)
    {   
        /* wipe parser on error */
        *token_count = 0;
        memset(&parser.tkns, 0, sizeof(jsmntok_t)*MAX_PARSER_JSMNTOK_CNT);
    }
    return status;
}


