#include "gpio_interface.h"

const uint8_t max_pin_index[NUM_PIN_TYPES] = 
{   
    /* subtract 1 because arrays start at 0 */
    NUM_DIGITAL_INPUTS - 1,
    NUM_RELAYS - 1,
    NUM_BATTERIES - 1,
};


/* index offset for a given pin type */
const uint8_t pin_index_base[NUM_PIN_TYPES] = 
{
    0,                
    NUM_DIGITAL_INPUTS,
    NUM_RELAYS,
};

static int validate_pin_command(struct pinCommand *cmd);
static int validate_pin_config(struct pinConfig *cfg);


int update_pin_config(struct pinConfig *cfg)
{
    int status = validate_pin_config(cfg);
    if(0 == status)
    {

    }



    return status;
}


/* PUBLIC FUNCTIONS */
int update_pin_command(struct pinCommand *cmd)
{
    int status = validate_pin_command(cmd);
    if(0 == status)
    {

    }

    return status;
}




/* PRIVATE WORKER FUNCTIONS */
static int validate_pin_config(struct pinConfig *cfg)
{
    int is_valid = 0;

    //TODO: DO STUFF TO VALIDATE THE PIN CONFIG

    return is_valid;
}



static int validate_pin_command(struct pinCommand *cmd)
{
    int is_valid = 0;

    //TODO: DO STUFF TO VALIDATE THE PIN COMMAND

    return is_valid;
}








