#ifndef LOWPOWER_SERIALCOMMANDS
#define LOWPOWER_SERIALCOMMANDS
#include <stdint.h>
#include "parsing.h"




typedef struct token_parse_table
{
    token_table_entry_t         tkn;
    struct token_parse_table   *next_table;
}   token_parse_table_t;

void handle_command(const char *cmd);
#endif