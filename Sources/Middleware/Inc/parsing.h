#ifndef LOWPOWER_PARSING
#define LOWPOWER_PARSING
#include <stdint.h>
#include <string.h> /* macro for token strequal uses strncmp */

#include "jsmn.h"
#define MAX_PARSER_JSMNTOK_CNT  40
#define MAX_JSON_STRBUF_LEN     256
#define MAX_TOKEN_STRINGLEN     32

#define PARSE_STATUS_OK                     0
#define PARSE_STATUS_NOT_ENOUGH_TOKENS      1
#define PARSE_STATUS_NULL_JSON_STRING       2
#define PARSE_STATUS_PARTIAL_JSON_STRING    3
#define PARSE_STATUS_INVALID_CHARACTER      4


#define TOKEN_STRLEN(tkn) (tkn.end - tkn.start)
#define TKN_STREQ(json, tkn, sub_str) (0 == strncmp((const char*)json + tkn.start, (const char*)sub_str, TOKEN_STRLEN(tkn)))

struct lookup_tkn
{
    jsmntype_t                  type;
    char                        str[MAX_TOKEN_STRINGLEN];
};


/* 
returns a token pointer from the token array (index i) 

IF CALLED AFTER A PARSING ERROR, returns NULL.
if called with index > num_parsed_tokens, returns NULL
*/
jsmntok_t* getToken(uint32_t i);

jsmntok_t* getTokenArr(void);


/* 
takes a json string and parses it 
RETURN STATUS IS ONE OF:
- PARSE_STATUS_OK                     
- PARSE_STATUS_NOT_ENOUGH_TOKENS      
- PARSE_STATUS_NULL_JSON_STRING       
- PARSE_STATUS_PARTIAL_JSON_STRING    
- PARSE_STATUS_INVALID_CHARACTER

ON ERROR, @param2 (token_count is set to 0)
*/
uint32_t parseJSON(const int8_t* json, uint32_t* const token_count);

#endif