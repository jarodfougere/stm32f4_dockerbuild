#include <stdio.h>
#include <string.h>

#include "command_parse.h"
#include "middleware.h"


static struct tkn_leaf_table PinCmdTable =
{   
    .size = 3,
    .tbl =
    {
        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "trigger",
                },
            .next_tbl = NULL,
        },
    
        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "id",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "type",
                },
            .next_tbl = NULL,
        },
    }
};
static struct tkn_leaf_table rootPinCmdTable =
{   
    .size = 1,
    .tbl = 
    {   
        {
            .tkn =
            {
                .type = JSMN_OBJECT,
                .str = "",
            },
            .next_tbl = &PinCmdTable,
        },
    },
};
static struct tkn_leaf_table outpostidCmdTable =
{   
    .size = 2,
    .tbl =
    {
        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "020104",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "020103",
                },
            .next_tbl = NULL,
        }
    }
};

static struct tkn_leaf_table pinupdateCmdTable =
{   
    .size = 1,
    .tbl =
    {
        {
            .tkn =
                {
                    .type = JSMN_PRIMITIVE,
                    .str = "true",
                },
            .next_tbl = NULL,
        }
    }
};

static struct tkn_leaf_table ConfigModeTable =
{   
    .size = 12,
    .tbl  = 
    {
        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "id",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "type",
                },
            .next_tbl = NULL,
        },

        {
            .tkn = 
            {
                .type = JSMN_STRING,
                .str = "label",
            },
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "active",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "trigger",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "debounce",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "battType",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "redHigh",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "redLow",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "yellowHigh",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "yellowLow",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "priority",
                },
            .next_tbl = NULL,
        }
    }
};

static struct tkn_leaf_table pinConfigTable =
{   
    .size = 1,
    .tbl  = 
    {
        {
            .tkn =
            {
                .type = JSMN_OBJECT,
                .str = "PINCONFIG_OBJECT",
            },
            .next_tbl = &ConfigModeTable,
        },
    }
};

static struct tkn_leaf_table writeModeTable =
{   
    .size = 2,
    .tbl  = 
    {
        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "pin_info_interval",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "config",
                },
            .next_tbl = NULL,
        },

    }
};

static struct tkn_leaf_table writeCmdTable =
{   
    .size = 1,
    .tbl  = 
    {
        {
            .tkn =
            {
                .type = JSMN_OBJECT,
                .str = "WRITE_OBJECT",
            },
            .next_tbl = &writeModeTable,
        },
    }
};

static struct tkn_leaf_table readCmdTable =
{   
    .size = 4,
    .tbl  = 
    {
        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "hb_interval",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "fwVersion",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "hwVersion",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "pin_info_interval",
                },
            .next_tbl = NULL,
        },
    },
};
static struct tkn_leaf_table systemModeTable =
{   
    .size = 1,
    .tbl = 
    {
        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "mode",
                },
            .next_tbl = NULL,
        },
    }
};

static struct tkn_leaf_table systemCmdTable =
{   
    .size = 4,
    .tbl =
    {
        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "info",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "reset_boot",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "reset_main",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_OBJECT,
                    .str = "MODE_OBJECT",
                },
            .next_tbl = &systemModeTable,
        },
    },
};

static struct tkn_leaf_table rootCmdTable =
{
    .size = 8,
    .tbl =
    {
        {
            .tkn =
            {
                .type = JSMN_STRING,
                .str = "system",
            },
            .next_tbl = &systemCmdTable,
        },

        {
            .tkn =
            {
                .type = JSMN_STRING,
                .str = "read",
            },
            .next_tbl = &readCmdTable,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "write",
                },
            .next_tbl = &writeCmdTable,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "GPIO_PIN_CONFIG",
                },
            .next_tbl = &pinConfigTable,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "GPIO_PIN_UPDATE",
                },
            .next_tbl = &pinupdateCmdTable,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "GPIO_DEVICE_INFO",
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "outpostID",
                },
            .next_tbl = &outpostidCmdTable,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "GPIO_PIN_CMD",
                },
            .next_tbl = &rootPinCmdTable,
        }

    }
};


static struct tkn_leaf_table rootObj =
{   
    .size = 1,
    .tbl = 
    {   
        {
            .tkn =
            {
                .type = JSMN_OBJECT,
                .str = "ROOT_OBJECT",
            },
            .next_tbl = &rootCmdTable,
        },
    },
};


/* RECURSIVE WRAPPER FOR THE PARSING FUNCTION */
static void parse_object(   const char* cmd, 
                            jsmntok_t *tokens, 
                            int32_t start_idx,
                            struct tkn_leaf_table *table);

void parse_command(const char* cmd)
{   
    int32_t token_count = 0;
    switch (parseJSON((const int8_t *)cmd, &token_count))
    {
        case PARSE_STATUS_OK:
            //Proceed to traverse the parse tree.
            break;
        case PARSE_STATUS_INVALID_CHARACTER:
            transmit_serial("{\"error\":\"invalid character in json: >%s<\"}\r\n", cmd);
            return;
        case PARSE_STATUS_NOT_ENOUGH_TOKENS:
            transmit_serial("{\"error\":\"Not enough allocated jsmn tokens to parse json: >%s<\"}\r\n", cmd);  
            return;
        case PARSE_STATUS_NULL_JSON_STRING:
            transmit_serial("{\"error\":\"JSON String is a null character array...\"}\r\n", cmd);
            return;
        case PARSE_STATUS_PARTIAL_JSON_STRING:
            transmit_serial("{\"error\":\"Received partial json: >%s<\"}\r\n", cmd);
            return;
        default:
#                   ifdef DEBUG
            transmit_serial("ERROR: DEFAULT CASE IN PARSE_STATUS_t retval for parseJSON.\n");
#                   endif
        return;
    }
    parse_object(cmd, getTokenArr(), 0, &rootObj);
}




static void parse_object(   const char* cmd, 
                            jsmntok_t *tkns, 
                            int32_t start_idx,
                            struct tkn_leaf_table *tbl)
{   
    //int32_t tbl_idx         = 0 ;           //tracks lookup table traversal
    int32_t         batch_idx = start_idx;                
    const int32_t   end_idx   = batch_idx + tkns[batch_idx].size;
    do
    {
        switch(tkns[batch_idx].type)
        {   
            case JSMN_ARRAY:
                {
#                   ifdef DEBUG
                    transmit_serial("CRITICAL. ARRAY : ");
                    tprint(cmd, &tkns[batch_idx]);
                    transmit_serial(" is an empty array!\n");
#                   endif
                    return;
                }
            case JSMN_OBJECT:
                if(0 == tkns[batch_idx].size) //validate empty array
                {
                    if(((tkns[batch_idx].parent < 0) && (0 == batch_idx)) 
                    || ((tkns[batch_idx].parent >= 0) &&  
                    JSMN_STRING == (tkns[tkns[batch_idx].parent].type)))
                    {   
                        transmit_serial("CURRENT TOKEN :");
                        tprint(cmd, &tkns[batch_idx]);
                        transmit_serial("  is type OBJECT. Now parsing object!\n");
                        parse_object(cmd, tkns, batch_idx += 1, tbl);
                    }
                    else
                    {
#                       ifdef DEBUG
                        transmit_serial("JSON Parent check failed on line %d of %s\n", __LINE__, __FILE__);
#                       endif
                    } 
                }
                else
                {
                    #ifdef DEBUG
                    transmit_serial("token :");
                    tprint(cmd, &tkns[batch_idx]);
                    transmit_serial(" has 0 size\n");
                    #endif
                }
                
                break;
            case JSMN_STRING:
                
                //determine if the "string" is a key or a value
                if(0 == tkns[batch_idx].size)
                {
                    /* token is a value (it owns no other tokens) */
                    transmit_serial("JSMN_STRING token:");
                    tprint(cmd, &tkns[batch_idx]);
                    transmit_serial(" is a VALUE\n");
                }
                if(1 == tkns[batch_idx].size)
                {
                    transmit_serial("JSMN_STRING token:");
                    tprint(cmd, &tkns[batch_idx]);
                    transmit_serial(" is a KEY\n");
                }
                else
                {
                    //WTF IS HAPPENING 
    #               ifdef DEBUG
                    transmit_serial("VERY STRANGE ERROR in %s, line %d\n", __FILE__, __LINE__);
    #               endif
                }
                break;
            case JSMN_PRIMITIVE:
                if(0 == tkns[batch_idx].size)
                {
                    transmit_serial("JSMN_PRIMITIVE token:");
                    tprint(cmd, &tkns[batch_idx]);
                    transmit_serial(" is a VALUE\n");  
                }
                else
                {
#                   ifdef DEBUG
                    transmit_serial("ERROR!!! JSMN_PRIMITIVES CANNOT BE KEYS. CURRENT TOKEN:");
                    tprint(cmd, &tkns[batch_idx]);
                    transmit_serial("\n");
#                   endif
                }
                break;
            default:
            #               ifdef DEBUG
                transmit_serial("ERROR: DEFAULT CASE OCCURRED IN file %s, line %u\n", __FILE__, __LINE__);
            #               endif
                break;
        }
    } while (++batch_idx < end_idx);



    #if 0
    do
    {   
        batch_size = tokens[tkn_idx].size;
        switch(tokens[tkn_idx].type)
        {
            case JSMN_OBJECT:
            case JSMN_ARRAY:
                do
                {
                    
                } while (++batch_idx < batch_size);
                break;
            case JSMN_STRING:

                break;
            case JSMN_PRIMITIVE:

                break;
            default:
            #               ifdef DEBUG
                transmit_serial("ERROR: DEFAULT CASE OCCURRED IN file %s, line %u\n", __FILE__, __LINE__);
            #               endif
                break;
        }
    } while (++tkn_idx < token_count);

    #endif
}
