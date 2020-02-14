#ifndef LOWPOWER_COMMAND_PARSE
#define LOWPOWER_COMMAND_PARSE
#include <stdint.h>
#include "parsing.h"

/* declarations for self-referential structures */
struct tkn_leaf_table;
struct tkn_table_entry;

struct tkn_tbl_entry
{
    struct lookup_tkn     tkn;
    struct tkn_leaf_table *next_tbl;
};

struct tkn_leaf_table
{
    int32_t                 size;
    struct  tkn_tbl_entry   tbl[];
};   

/* User-facing function */
void parse_command(const char* cmd);


#endif