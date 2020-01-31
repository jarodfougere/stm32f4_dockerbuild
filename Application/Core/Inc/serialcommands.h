#ifndef LOWPOWER_SERIALCOMMANDS
#define LOWPOWER_SERIALCOMMANDS

#include "parsing.h"

typedef enum
{   
    CMD_TYPE_none,
    CMD_TYPE_no_key,
    CMD_TYPE_key_val,
    CMD_TYPE_key_obj,
    CMD_TYPE_key_arr,
}   CMD_TYPE_t;

typedef struct
{
    parse_table_entry_t     tbl;
    parse_table_entry_t     *next_table;
    CMD_TYPE_t              cmd_type;
}   parse_table_t;







#endif