#ifndef RIMOT_RELAY_INTERFACE
#define RIMOT_RELAY_INTERFACE
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>

#include "pin_config_interface.h"


#define NUM_RELAY_PINS 4

typedef enum
{
    RELAYPOS_closed = 1,
    RELAYPOS_open = 0,
}   RELAYPOS_t;


typedef enum
{
    RELAY_MODE_toggle = -1,
    RELAY_MODE_countdown,
}   RELAY_MODE_t;


typedef struct gpio_relay_config relayConfig_t;

relayConfig_t* newRelayConfig(GPIO_PIN_ID_t id);
RELAYPOS_t relayGetDfltPos(const relayConfig_t *relay);
RELAYPOS_t relayGetCurrentPos(const relayConfig_t *relay);
uint32_t relayGetHoldTime(const relayConfig_t *relay);
RELAY_MODE_t relayGetMode(const relayConfig_t *relay);
pinCfgCore_t* relayGetPinCfg(const relayConfig_t *relay);
void relaySetDfltPos(relayConfig_t *relay, RELAYPOS_t pos);
void relaySetCurrentPos(relayConfig_t *relay, RELAYPOS_t pos);
void relaySetMode(relayConfig_t *relay, RELAY_MODE_t mode);
int relaySetHoldTime(relayConfig_t *relay, uint32_t holdTime);

#include <stdint.h>


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_RELAY_INTERFACE */