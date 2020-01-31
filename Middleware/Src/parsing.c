#include "parsing.h"

typedef struct
{
    jsmn_parser tokenizer;
    jsmntok_t tkns[MAX_PARSER_JSMNTOK_CNT];
    int16_t initStatus;
}   jsonParser_t;

static jsonParser_t p;


/* returns a READ ONLY token from the token array (index i) */
jsmntok_t* const getToken(uint32_t i)
{
    return (jsmntok_t* const)&p.tkns[i];
}

/* takes a json string and parses it */
uint32_t parseJSON(const int8_t* const json, uint32_t* const token_count)
{   
    uint32_t status = 0;
    if((void*)0 != json) //if not NULL
    {
        jsmn_parser parser;
        parser.pos = 0;
        parser.toksuper = -1; /* token node 0 has no parent node */
        parser.toknext  = -1; /* init as unknown */
    }

    return status;
}


