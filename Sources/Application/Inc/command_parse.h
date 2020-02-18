#ifndef LOWPOWER_COMMAND_PARSE
#define LOWPOWER_COMMAND_PARSE
#include <stdint.h>
#include "middleware.h"

struct commands
{
    char systemCommand[20];
    char readCommand[20];
}   serial_cmds;



int parse_command(const char *command);


#endif