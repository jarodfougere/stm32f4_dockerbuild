/**
 * @file json_utils.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief File to provide a set of json and jsmn token manipulation functions
 * @version 0.1
 * @date 2020-10-14
 *
 * @copyright Copyright (c) 2020
 */

#include <stdint.h>
#include <limits.h>
#include <string.h>

#include "json_utils.h"


uint32_t jutil_toklen(const jsmntok_t *tok)
{
    uint32_t len = 0;
    if (tok != NULL)
    {
        uint_least64_t tokstart = tok->start;
        uint_least64_t tokend   = tok->end;
        if (tokend >= 0 && tokstart >= 0)
        {
            if (tokend - tokstart < UINT32_MAX)
            {
                len = tokend - tokstart;
            }
        }
    }
    return len;
}


bool jutil_tokcmp(const char *str, const uint8_t *json, const jsmntok_t *tok)
{
    bool result = false;
    if (str == NULL && tok == NULL)
    {
        result = true;
    }
    else
    {
        uint32_t least_size = jutil_toklen(tok);
        uint32_t slen       = strlen(str);
        if (least_size < slen)
        {
            least_size = slen;
        }

        /* actually compare them */
        if (strncmp((const char *)str, (char *)&json[tok->start], least_size) ==
            0)
        {
            result = true;
        }
        else
        {
            result = false;
        }
    }
    return result;
}


bool isValidJson(const jsmntok_t *tokens, uint_least8_t tcnt)
{
    if (tokens == NULL || tcnt < 1)
    {
        return false;
    }
    else if (tokens[0].type == JSMN_OBJECT && tokens[1].type == JSMN_STRING)
    {
        return true;
    }
    else
    {
        return false;
    }
}


char *jutil_tokcpy(char *dst, uint_least16_t bufsize, const uint8_t *json,
                   const jsmntok_t *tkn)
{
    char *result = NULL;
    if (dst != NULL && json != NULL && tkn != NULL)
    {
        result = strncpy(dst, (char *)&json[tkn->start], bufsize);
    }
    return result;
}
