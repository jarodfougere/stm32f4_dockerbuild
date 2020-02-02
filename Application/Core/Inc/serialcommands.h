#ifndef LOWPOWER_SERIALCOMMANDS
#define LOWPOWER_SERIALCOMMANDS
#include <stdint.h>
#include "parsing.h"

typedef enum
{   
    CMD_TYPE_none,
    CMD_TYPE_no_key,
    CMD_TYPE_key_val,
    CMD_TYPE_key_obj,
    CMD_TYPE_key_arr,
}   CMD_TYPE_t;


typedef struct token_parse_table
{
    token_table_entry_t         tkn;
    struct token_parse_table   *next_table;
    CMD_TYPE_t                  cmd_type;
}   token_parse_table_t;

void handle_command(const char *cmd);
#endif