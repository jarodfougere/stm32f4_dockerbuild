#ifndef RIMOT_COMMAND_PARSE
#define RIMOT_COMMAND_PARSE
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include "rimot_device.h"
#include "task.h"

typedef enum
{
    SERIAL_EVT_init,
    SERIAL_EVT_rx,
    SERIAL_EVT_tx,
    SERIAL_EVT_usbconfig,
}   SERIAL_EVT_t;


typedef enum
{
}   SERIAL_CTX_t;


void serial_task(struct rimot_device *dev, struct task *task);
#endif