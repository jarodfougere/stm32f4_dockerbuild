#include "parsing.h"

typedef struct
{
    jsmn_parser tokenizer;
    jsmntok_t tkns[MAX_PARSER_JSMNTOK_CNT];
    uint8_t buf[MAX_JSON_STRBUF_LEN];
    int16_t initStatus;
}   jsonParser_t;

static jsonParser_t p;


