#include <stdio.h>
#include <string.h>

#include "serialcommands.h"
#include "middlewares.h"





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
                .size = 0, //CURRENTLY NOT USED
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
        //Jarod TODO: populate next
    },

    {
        //Jarod TODO: populate next
    },

    {
        //Jarod TODO: populate next
    }
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
        memset(leaf_i, 0, sizeof(leaf_i));

        uint32_t tkn_i = 0;
        for (tkn_i = 0; tkn_i < token_count; tkn_i++)
        {
            curr_tkn = getToken(tkn_i);
            /* if we have reached the end of parsing */
            if (curr_node->next_table == NULL)
            {   
                
            }
            else
            {
                /* 
                    go through each leaf node in the tree and
                    compare with the current token 
                */
                do
                {
                    /* first validate token type */
                    if (curr_tkn->type ==
                        curr_node[leaf_i[tkn_i]].tkn.type)
                    {   
                        if(JSMN_OBJECT == curr_node[leaf_i[tkn_i]].tkn.type || JSMN_ARRAY == curr_node[leaf_i[tkn_i]].tkn.type)
                        {   
                            /* 
                            If the token is a "object" type (ie contains tokens) 
                            THEN we don't compare the token string but 
                            proceed to the lookup table of acceptable keys/vals
                            for said object
                            */
                            curr_node = curr_node->next_table;
                        }

                        /* 
                        If the token is a key or a value, 
                        we should compare the string 
                        */
                        else
                        {
                            if(0 == strncmp(&cmd[curr_tkn->start],                           curr_node->tkn.str,                              TOKEN_STRLEN(curr_tkn)))
                            {
                                /* token type and string match so we proceed to the corresponding leaf in the parse tree */
                                curr_node = curr_node->next_table;
                            }
                            else
                            {
                                /* the token strings are not equal */

                                //TODO: some sort of error message?
                            } 
                        }
                    }
                    else 
                    {
                        /* go to next leaf in current tree level */
                        leaf_i[tkn_i] += 1;
                    }
                } while (curr_node->next_table != NULL);
            }
        }
    }
    else
    {
        printf("%s error parsing!\n", cmd);
    }
}
