#include <stdio.h>
#include <string.h>

#include "serialcommands.h"
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


void handle_command(const char *cmd)
{
    /* the number of tokens that were parsed from the json */
    uint32_t token_count;

    /* the node index in the parse tree */
    const struct tkn_leaf_table *cur_node = &rootObj;

    if (PARSE_STATUS_OK == parseJSON((const int8_t *)cmd, &token_count))
    {   
        const jsmntok_t *tkns = getTokenArr();

        /* tracks path traversed in the parse tree */
        int32_t  leaf[MAX_PARSER_JSMNTOK_CNT];
        memset(leaf, 0, sizeof(leaf));
        
        uint32_t t = 0;
        int32_t tkns_left = 0;

        for(t = 0; t < token_count; t++)
        {
            
        }


        do
        {   
            tkns_left += tkns[t].size;
            int32_t max_leaves = cur_node->size;

            for(leaf[t] = 0; leaf[t] < max_leaves; leaf[t]++)
            {   
                if(cur_node->tbl[leaf[t]].tkn.type == tkns[t].type)
                {
                    if( JSMN_OBJECT == tkns[t].type || 
                        JSMN_ARRAY == tkns[t].type)
                    {
                        cur_node = cur_node->tbl[leaf[t]].next_tbl;
                        /* we dont string compare for objects */
                        break;
                    }
                    else 
                    if( JSMN_STRING    == tkns[t].type ||
                        JSMN_PRIMITIVE == tkns[t].type)
                    {   
                        if(1 == tkns[t].size)
                        {   
                            /* we are dealing with a key */
                            if(TKN_STREQ(cmd, tkns[t], cur_node->tbl[leaf[t]].tkn.str))
                            {

                                if(cur_node->tbl[leaf[t]].next_tbl == NULL)
                                {

                                }
                                else
                                {
                                    cur_node = cur_node->tbl[leaf[t]].next_tbl;
                                }
                                break;
                            }
                            else
                            {
                                /* TYPE MATCHES BUT STRING DOES NOT MATCH */
                            }
                        }
                        else if(0 == tkns[t].size )
                        {   
                            /* we are dealing with a value */

                        }
                        else
                        {
                            /* CIRITAL, THIS SHOULD NEVER OCCUR */
                            while(1)
                            {
                                transmit_serial("WEFWEwewefe");
                            }
                        }
                    }
                    else
                    {   
                        /* CRITICAL, THIS SHOULD NEVER HAPPEN */
                        while(1)
                        {
                            transmit_serial("WEFW");
                        }
                    }
                }
                else
                {

                }
            }
            

            t++; /* advance token index */
        } while (!(tkns_left < 0));

#if 0
            
        for (t = 0; t < token_count; t++)
        {   
            cur_tkn = getToken(t);

            num_processed_tokens += cur_tkn->size;
            int32_t max_leaves = cur_node->size;

            /* case where the token is a value */
            /* WARNING: THIS WILL COMPLETELY BREAK IF VALUES ARE QUOTED */
            if(0 == cur_tkn->size && JSMN_STRING != cur_tkn->type)
            {
                leaf[t] = -1; //dummyval
            }
            else
            {
                #ifdef DEBUG
                transmit_serial("\ncurrent token:\n");
                int x;
                for(x = cur_tkn->start; x < cur_tkn->end; x++)
                {
                    transmit_serial("%c", cmd[x]);
                }
                transmit_serial("\ncurrent token.type = %d\n current token.size = %d\n", cur_tkn->type, cur_tkn->size);
                transmit_serial("max_leaves = %d, t = %d\n\n", max_leaves, t);
                #endif

                for(leaf[t] = 0; leaf[t] < max_leaves; leaf[t]++)
                {   
                    transmit_serial("leaf = %d,  t = %d, node.tkn.str = >%s<\n", leaf[t], t, cur_node->tbl[leaf[t]].tkn.str);

                    struct tkn_leaf_table *next_tbl = cur_node->tbl[leaf[t]].next_tbl;

                    /* first validate token type */
                    if (cur_tkn->type == cur_node->tbl[leaf[t]].tkn.type)
                    {   
                        transmit_serial("TYPE MATCH\n");

                        if( JSMN_ARRAY ==  cur_node->tbl[leaf[t]].tkn.type ||
                            JSMN_OBJECT == cur_node->tbl[leaf[t]].tkn.type)
                        {
                            /* 
                                If the token is a "object" type (ie contains tokens) 
                                THEN we don't compare the token string but 
                                proceed to the lookup table of acceptable keys/vals
                                for said object
                                */
                                transmit_serial("matched token type OBJECT/ARRAY! moving node to next table!\n");
                                cur_node = next_tbl;

                                /* match found so terminate current tree loop */
                                break;
                        }    
                        else if(      
                        JSMN_PRIMITIVE == cur_node->tbl[leaf[t]].tkn.type ||  JSMN_STRING    == cur_node->tbl[leaf[t]].tkn.type)
                        {
                            /* 
                            If the token is a key or a value, 
                            we should compare the string 
                            */
                            transmit_serial("token type of >%s< is PRIMITIVE OR STRING\n", cur_node->tbl[leaf[t]].tkn.str);

                            if(TKN_STREQ(cmd, cur_tkn, cur_node->tbl[leaf[t]].tkn.str))
                            {   
                                transmit_serial("CURRENT TOKEN MATCHES >%s<\n",cur_node->tbl[leaf[t]].tkn.str);

                                if(cur_node->tbl[leaf[t]].next_tbl == NULL)
                                {   
                                    //Jarod TODO: exec function lookup, param passing, and execution
                                    transmit_serial("\n##########\n");
                                    transmit_serial("successfully traversed parse tree for >%s<\n", cmd);
                                    unsigned int y;
                                    for( y = 0; y < token_count; y++)
                                    {   
                                        transmit_serial("leaf[%d] = %d\n", y, leaf[y]);
                                    }

                                    transmit_serial("##########\n\n");
                                    
                                }
                                else
                                {   
                                    transmit_serial("token string match but not done parsing. moving node to next table\n");
                                    /* 
                                    token type and string match so we proceed to the corresponding leaf in the parse tree 
                                    */
                                    cur_node = next_tbl;
                                }

                                /* match found so terminate leaf loop */
                                break;
                            }
                            else
                            {
                                transmit_serial("NO STRING MATCH\n");
                            }
                        } 
                        else
                        {
                            /* critical. This should never happen */
                            #ifdef DEBUG
                                //Jarod TODO: debug mode error handle of some sort
                                transmit_serial("DEFAULT CASE HANDLE COMMAND");
                            #endif
                        }
                    }
                    else
                    {
                        transmit_serial("NO TYPE MATCH\n");
                    }
                }

                /* if all leaves at curent tree level checked, error message */
                if(leaf[t] == max_leaves)
                {
                    /* we DID NOT FIND A MATCH IN THE TABLE */
                    transmit_serial("NO MATCH\n");
                    break;
                }
                else
                {
                    transmit_serial("terminated token loop by finding match!\n");
                }

        }

#endif
    }
    else
    {
        transmit_serial("%s error parsing!\n", cmd);
    }
}
