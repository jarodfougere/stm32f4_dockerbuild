#ifndef LOWPOWER_PARSING
#define LOWPOWER_PARSING
#include <stdint.h>

#include "jsmn.h"
#define MAX_PARSER_JSMNTOK_CNT 30
#define MAX_JSON_STRBUF_LEN 256




jsmntok_t* const getToken(uint32_t i);



#endif