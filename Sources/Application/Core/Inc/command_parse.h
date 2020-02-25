#ifndef RIMOT_COMMAND_PARSE
#define RIMOT_COMMAND_PARSE
#include <stdint.h>
#include <string.h>
#include <limits.h>


#include "middleware.h"
#include "rimot_device.h"

/**
 * @brief 
 * 
 * @param command 
 * @return int 
 */
int32_t parse_command(const char *command, struct rimot_device *dev);


#endif