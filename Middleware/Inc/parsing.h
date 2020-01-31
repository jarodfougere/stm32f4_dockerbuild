#ifndef LOWPOWER_PARSING
#define LOWPOWER_PARSING
#include <stdint.h>

#include "jsmn.h"
#define MAX_PARSER_JSMNTOK_CNT 30
#define MAX_JSON_STRBUF_LEN 256



/* returns a READ ONLY token from the token array (index i) */
jsmntok_t* const getToken(uint32_t i);

/* takes a json string and parses it */
uint32_t parseJSON(const int8_t* const json, uint32_t* const token_count);


#endif