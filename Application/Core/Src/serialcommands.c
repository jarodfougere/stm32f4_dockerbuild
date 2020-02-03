#include <stdio.h>
#include <string.h>

#include "serialcommands.h"
#include "middlewares.h"


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
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },
    
        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "id",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "type",
                    .size = 0, //curENTLY NOT USED
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
                .size = 0, //not curently used
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
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "020103",
                    .size = 0, //curENTLY NOT USED
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
                    .size = 0, //curENTLY NOT USED
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
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "type",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn = 
            {
                .type = JSMN_STRING,
                .str = "label",
                .size = 0,
            },
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "active",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "trigger",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "debounce",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "battType",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "redHigh",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "redLow",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "yellowHigh",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "yellowLow",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "priority",
                    .size = 0, //curENTLY NOT USED
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
                .size = 0, //curENTLY NOT USED
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
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "config",
                    .size = 0, //curENTLY NOT USED
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
                .size = 0, //curENTLY NOT USED
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
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "fwVersion",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "hwVersion",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "pin_info_interval",
                    .size = 0, //curENTLY NOT USED
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
                    .size = 0, //curENTLY NOT USED
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
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "reset_boot",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "reset_main",
                    .size = 0, //curENTLY NOT USED
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_OBJECT,
                    .str = "MODE_OBJECT",
                    .size = 1, //curENTLY NOT USED
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
                .size = 0,
            },
            .next_tbl = &systemCmdTable,
        },

        {
            .tkn =
            {
                .type = JSMN_STRING,
                .str = "read",
                .size = 0,
            },
            .next_tbl = &readCmdTable,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "write",
                    .size = 0,
                },
            .next_tbl = &writeCmdTable,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "GPIO_PIN_CONFIG",
                    .size = 0,
                },
            .next_tbl = &pinConfigTable,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "GPIO_PIN_UPDATE",
                    .size = 0,
                },
            .next_tbl = &pinupdateCmdTable,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "GPIO_DEVICE_INFO",
                    .size = 0,
                },
            .next_tbl = NULL,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "outpostID",
                    .size = 0,
                },
            .next_tbl = &outpostidCmdTable,
        },

        {
            .tkn =
                {
                    .type = JSMN_STRING,
                    .str = "GPIO_PIN_CMD",
                    .size = 0,
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
                .size = 0, //not curently used
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

    /* the curent token we are trying to match in the tree */
    jsmntok_t *cur_tkn;

    if (PARSE_STATUS_OK == parseJSON((const int8_t *)cmd, &token_count))
    {   
        printf("%s was tokenized successfully!\n", cmd);

        /* tracks path traversed in the parse tree */
        int32_t  leaf[token_count];
        uint32_t t = 0;
        printf("token_count = %d before forloop\n", token_count);
        for (t = 0; t < token_count; t++)
        {   
            cur_tkn = getToken(t);
            int32_t max_leaves = cur_node->size;
            memset(leaf, 0, sizeof(leaf));

            /* case where the token is a value */
            /* WARNING: THIS WILL COMPLETELY BREAK IF VALUES ARE QUOTED */
            if(0 == cur_tkn->size && JSMN_STRING != cur_tkn->type)
            {
                leaf[t] = -1; //dummyval
            }
            else
            {
                #ifdef DEBUG
                printf("\ncurrent token:\n");
                int x;
                for(x = cur_tkn->start; x < cur_tkn->end; x++)
                {
                    printf("%c", cmd[x]);
                }
                printf("\ncurrent token.type = %d\n current token.size = %d\n", cur_tkn->type, cur_tkn->size);
                printf("max_leaves = %d, t = %d\n\n", max_leaves, t);
                #endif

                for(leaf[t] = 0; leaf[t] < max_leaves; leaf[t]++)
                {   
                    printf("leaf = %d,  t = %d, node.tkn.str = >%s<\n", leaf[t], t, cur_node->tbl[leaf[t]].tkn.str);

                    struct tkn_leaf_table *next_tbl = cur_node->tbl[leaf[t]].next_tbl;

                    /* first validate token type */
                    if (cur_tkn->type == cur_node->tbl[leaf[t]].tkn.type)
                    {   
                        printf("TYPE MATCH\n");



                        if( JSMN_ARRAY == cur_node->tbl[leaf[t]].tkn.type ||
                            JSMN_OBJECT == cur_node->tbl[leaf[t]].tkn.type)
                        {
                            /* 
                                If the token is a "object" type (ie contains tokens) 
                                THEN we don't compare the token string but 
                                proceed to the lookup table of acceptable keys/vals
                                for said object
                                */
                                printf("matched token type OBJECT/ARRAY! moving node to next table!\n");
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
                            printf("token type of >%s< is PRIMITIVE OR STRING\n", cur_node->tbl[leaf[t]].tkn.str);


                            if(TKN_STREQ(cmd, cur_tkn, cur_node->tbl[leaf[t]].tkn.str))
                            {   
                                printf("CURRENT TOKEN MATCHES >%s<\n",cur_node->tbl[leaf[t]].tkn.str);

                                if(cur_node->tbl[leaf[t]].next_tbl == NULL)
                                {   
                                    //Jarod TODO: exec function lookup, param passing, and execution
                                    printf("\n##########\n");
                                    printf("successfully traversed parse tree for >%s<\n", cmd);
                                    unsigned int y;
                                    for( y = 0; y < token_count; y++)
                                    {   
                                        printf("leaf[%d] = %d\n", y, leaf[y]);
                                    }

                                    printf("##########\n\n");
                                }
                                else
                                {   
                                    printf("token string match but not done parsing. moving node to next table\n");
                                    /* 
                                    token type and string match so we proceed to the corresponding leaf in the parse tree 
                                    */
                                    cur_node = next_tbl;
                                }

                                /* match found so terminate current tree loop */
                                break;
                            }
                            else
                            {
                                printf("NO STRING MATCH\n");
                            }
                        } 
                        else
                        {
                            /* critical. This should never happen */
                            #ifdef DEBUG
                                //Jarod TODO: debug mode error handle of some sort
                                printf("DEFAULT CASE HANDLE COMMAND");
                            #endif
                        }
                    }
                    else
                    {
                        printf("NO TYPE MATCH\n");
                    }
                }

                /* if all leaves at curent tree level checked, error message */
                if(leaf[t] == max_leaves)
                {
                    /* we DID NOT FIND A MATCH IN THE TABLE */
                    printf("NO MATCH\n");
                    break;
                }
            }

        }
    }
    else
    {
        printf("%s error parsing!\n", cmd);
    }
}
