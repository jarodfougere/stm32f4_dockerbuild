#ifndef LOWPOWER_PARSING
#define LOWPOWER_PARSING

#include "jsmn.h"
#define MAX_PARSER_JSMNTOK_CNT 30
#define MAX_JSON_STRBUF_LEN 256


typedef struct
{
    jsmn_parser tokenizer;
    jsmntok_t tkns[MAX_PARSER_JSMNTOK_CNT];
    uint8_t buf[MAX_JSON_STRBUF_LEN];
    int16_t initStatus;
}   jsonParser_t;

#endif