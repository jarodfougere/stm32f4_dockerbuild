#include <stdio.h>
#include <string.h>

#include "serialcommands.h"
#include "middlewares.h"


static token_parse_table_t writeModeTable[] =
{
    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "pin_info_interval",
                .size = 0, //CURRENTLY NOT USED
            },
        .next_table = NULL,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "config",
                .size = 0, //CURRENTLY NOT USED
            },
        .next_table = NULL,
    },
};

static token_parse_table_t writeCmdTable[] =
{
    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "",
                .size = 0, //CURRENTLY NOT USED
            },
        .next_table = writeModeTable,
    },
};

static token_parse_table_t readCmdTable[] =
{
    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "hb_interval",
                .size = 0, //CURRENTLY NOT USED
            },
        .next_table = NULL,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "fwVersion",
                .size = 0, //CURRENTLY NOT USED
            },
        .next_table = NULL,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "hwVersion",
                .size = 0, //CURRENTLY NOT USED
            },
        .next_table = NULL,
    },

    {
        .tkn =
            {
                .type = JSMN_OBJECT,
                .str = "pin_info_interval",
                .size = 0, //CURRENTLY NOT USED
            },
        .next_table = NULL,
    },
};
static token_parse_table_t systemModeTable[] =
{
    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "mode",
                .size = 0, //CURRENTLY NOT USED
            },
        .next_table = NULL,
    },
};

static token_parse_table_t systemCmdTable[] =
{
    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "info",
                .size = 0, //CURRENTLY NOT USED
            },
        .next_table = NULL,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "reset_boot",
                .size = 0, //CURRENTLY NOT USED
            },
        .next_table = NULL,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "reset_main",
                .size = 0, //CURRENTLY NOT USED
            },
        .next_table = NULL,
    },

    {
        .tkn =
            {
                .type = JSMN_OBJECT,
                .str = "",
                .size = 1, //CURRENTLY NOT USED
            },
        .next_table = systemModeTable,
    },
};

static token_parse_table_t rootCmdTable[] =
{
    //system
    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "system",
                .size = 0,
            },
        .next_table = systemCmdTable,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "read",
                .size = 0,
            },
        .next_table = readCmdTable,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "write",
                .size = 0,
            },
        .next_table = writeCmdTable,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "GPIO_PIN_CONFIG",
                .size = 0,
            },
        //.next_table = pinconfigCmdTable,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "GPIO_PIN_UPDATE",
                .size = 0,
            },
        //.next_table = pinupdateCmdTable,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "GPIO_DEVICE_INFO",
                .size = 0,
            },
        //.next_table = devinfoCmdTable,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "outpostID",
                .size = 0,
            },
        //.next_table = pinconfigCmdTable,
    },

    {
        .tkn =
            {
                .type = JSMN_STRING,
                .str = "GPIO_PIN_CONFIG",
                .size = 0,
            },
        //.next_table = pinCmdTable,
    },
};

static token_parse_table_t rootObj =
{
    .tkn =
        {
            .type = JSMN_OBJECT,
            .str = "",
            .size = 0, //not currently used
        },
    .next_table = rootCmdTable,
};


void handle_command(const char *cmd)
{
    /* the number of tokens that were parsed from the json */
    uint32_t token_count;

    /* the node index in the parse tree */
    const token_parse_table_t *curr_node = &rootObj;

    /* the current token we are trying to match in the tree */
    jsmntok_t *curr_tkn;


    if (PARSE_STATUS_OK == parseJSON((const int8_t *)cmd, &token_count))
    {   
        printf("%s was parsed successfully!\n", cmd);

        /* tracks path traversed in the parse tree */
        int32_t leaf_i[token_count];

        uint32_t tkn_i = 0;
        for (tkn_i = 0; tkn_i < token_count; tkn_i++)
        {
            curr_tkn = getToken(tkn_i);
            const int32_t node_cnt = sizeof(curr_node)/sizeof(curr_node[0]);
            for(leaf_i[tkn_i] = 0; leaf_i[tkn_i] < node_cnt; leaf_i[tkn_i]++)
            {
                /* first validate token type */
                if (curr_tkn->type == curr_node[leaf_i[tkn_i]].tkn.type)
                {   
                    switch(curr_node[leaf_i[tkn_i]].tkn.type)
                    {
                        case JSMN_OBJECT:
                        /* FALLTHROUGH */
                        case JSMN_ARRAY:
                            /* 
                            If the token is a "object" type (ie contains tokens) 
                            THEN we don't compare the token string but 
                            proceed to the lookup table of acceptable keys/vals
                            for said object
                            */
                            curr_node = curr_node->next_table;
                        break;
                        case JSMN_STRING:
                        /* FALLTHROUGH */
                        case JSMN_PRIMITIVE:
                            /* 
                            If the token is a key or a value, 
                            we should compare the string 
                            */
                            if(TKN_STREQ(cmd, curr_tkn, curr_node->tkn.str))
                            {   
                                if(curr_node->next_table == NULL)
                                {   
                                    //Jarod TODO: exec function lookup, param passing, and execution
                                    break;
                                }
                                else
                                {   
                                    /* 
                                    token type and string match so we proceed to the corresponding leaf in the parse tree */
                                    curr_node = curr_node->next_table;
                                }
                            }
                        break;
                        default:
                            /* critical. This should never happen */
                            #ifdef DEBUG
                                //Jarod TODO: debug mode error handle of some sort
                                printf("DEFAULT CASE HANDLE COMMAND");
                            #endif
                        break;
                    }
                }
                else
                {
                    //types did not match. ERROR MESSAGE
                }
            }

            /* if all leaves at current tree level checked, error message */
            if(leaf_i[tkn_i] == node_cnt)
            {
                /* we DID NOT FIND A MATCH IN THE TABLE */

                //Jarod TODO: figure out what to do here.
            }
        }
    }
    else
    {
        printf("%s error parsing!\n", cmd);
    }
}
