/**
 * @file mjson.c
 * @author Carl Mattatall
 * @brief 
 * This is a custom JSON parser for embedded systems loosely based on
 * the microJson source code. Modifications have been made to handle
 * child objects via recursive parsing. 
 * 
 * @description
 * Just like with microJson, the user must statically provide the 
 * fixed-extent expected JSON structure in advance. In this way, an 
 * allocator is not required (recall : intended for embedded systems).
 * The fixed-extent attribute lists MUST be null terminated.
 *        
 * The matched attribute string of the first key for the top-level 
 * JSON object is stored upon parsing the JSON. This is intended to be
 * used for indexing into a function array for runtime execution 
 * based on the matched key.
 * 
 * @note
 * Hex character escapes in the form of \uXXXX are supported
 * eg: {"myval" : \uffed} or {"myval":\uFFED}. 
 * 
 * Exponential escapes are not supported yet but have been planned
 * in the future.
 *        
 * #####################################################################
 * ###   JSON KEYS (sometimes called attributes) with value "null"   ### 
 * ### cannot be handled properly as of march 26, 2020. Is is the    ###
 * ### responsibility of the json creator (outpost/edge device) in   ###
 * ### the higher level language to ensure that no keys with values  ###
 * ### == "null" are stringified and sent to this module.            ###
 * #####################################################################
 * 
 * @version 0.2
 * @date 2020-02-20
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */


/*
    TODO: Refactor the entire thing to work without using
    uncontrolled label jumps. goto and continue are not 
    really very safe or readable.

    Lower hanging fruit:
        fix all the freaking if-else chains I threw together
        to get an initial working version. Ideally it will
        all become either jumptable (switch) or lookup table
        based.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <math.h> /* for HUGE_VAL */

#if defined(MCU_APP)
#include "drivers.h"
#include "comms_interface.h"
#endif /* MCU APP */

#include "mjson.h"

#define str_starts_with(s, p) (strncmp(s, p, strlen(p)) == 0)

/* cast to char* in case of uint8_t */
#define streq(a, b)  (0 == strcmp((char*)a, (char*)b)) 
#define strneq(a, b) (0 != strcmp((char*)a, (char*)b))

#if !defined(NDEBUG)
#define debug_trace(...) comms_printf(__VA_ARGS__)
#else
/* admittedly this is a pretty ugly way to block out the debug messages */
#define debug_trace(...) do {} while(0);
#endif /* DEBUG BUILD */


static char *json_target_address( const struct json_attr *cursor,
                                  const struct json_array *parent,
                                  int offset)
{
    char *targetaddr = NULL;
    if (parent == NULL || parent->element_type != t_structobject)
    {
        /* ordinary case - use the address in the cursor structure */
        switch (cursor->type)
        {
        case t_ignore:
            targetaddr = NULL;
            break;
        case t_integer:
            targetaddr = (char*)&cursor->addr.integer[offset];
            break;
        case t_uinteger:
            targetaddr = (char*)&cursor->addr.uinteger[offset];
            break;
        case t_short:
            targetaddr = (char*)&cursor->addr.shortint[offset];
            break;
        case t_ushort:
            targetaddr = (char*)&cursor->addr.ushortint[offset];
            break;
        case t_time:
        case t_real:
            targetaddr = (char*)&cursor->addr.real[offset];
            break;
        case t_string:   /* this cast is in case uint8_t is used */
            targetaddr = (char*)cursor->addr.string;
            break;
        case t_boolean:
            targetaddr = (char*)&cursor->addr.boolean[offset];
            break;
        case t_character:
            targetaddr = (char*)&cursor->addr.character[offset];
            break;
        default:
            targetaddr = NULL;
            break;
        }
    }
    else
        /* tricky case - hacking a member in an array of structures */
        targetaddr = parent->arr.objects.base              + 
                     offset * (parent->arr.objects.stride) +
                     cursor->addr.offset;

    debug_trace("Target address for %s (offset %d) is %p\n",
                      cursor->attribute, offset, targetaddr);
    return targetaddr;
}

#ifdef TIME_ENABLE
static double iso8601_to_unix(char *isotime)
/* ISO8601 UTC to Unix UTC */
{
    double usec;
    struct tm tm;

    char *dp = strptime(isotime, "%Y-%m-%dT%H:%M:%S", &tm);
    if (dp == NULL)
    {
        return (double)HUGE_VAL;
    }
    if (*dp == '.')
    {
        usec = strtod(dp, NULL);
    }
    else
    {
        usec = 0;
    }
    return (double)timegm(&tm) + usec;
}
#endif /* TIME_ENABLE */

static int json_internal_read_object( const char *char_ptr,
                                      const struct json_attr *attrs,
                                      const struct json_array *parent,
                                      int offset,
                                      const char **end,
                                      int* matched_key_idx)
{   
    /* parsing state machine */
    enum /* untagged. Internal to function */
    {
        init,
        await_attr,
        in_attr,
        await_value,
        in_val_string,
        in_escape,
        in_val_token,
        post_val,
        post_element
    }   state = init; /* start at init phase */

#ifndef NDEBUG  /* These state names are for debug messages */
    char *statenames[] = 
    {
        "init",
        "await_attr",
        "in_attr",
        "await_value",
        "in_val_string",
        "in_escape",
        "in_val_token",
        "post_val",
        "post_element",
    };
#endif /* DEBUG BUILD */

    /* temp character array for the current json key */
    char attrbuf[JSON_KEY_MAXLEN + 1];

    /* pointer to the provisioned json structure attribute list */
    char *pattr = NULL;

    /* temp character array for VALUE of current json key */
    char valbuf[JSON_VAL_MAXLEN + 1];

    /* pointer to the provisioned location to store the parsed value */
    char *pval = NULL;

    /* support escaped hex values (enough space for 4 hex digits and a NUL) */
    char uescape[5]; 

    /* token cursor */
    const struct json_attr *cursor; 

    /* flag to differentiate between 1 and "1" */
    bool value_quoted = false;        

    /* retval for recursive parse of sub objects */
    int substatus;    

    int n;

    /* parsable string length */
    int maxlen = 0;     

    unsigned u; /* parsed value of "escaped" hexadecimal  */
    
    /* ptr to status lookup map */
    const struct json_enum *mp;

    char *lptr;

    /* 
     * parse_internal is recursively called with endptr as a param whenever we 
     * encounter a child object. Thus we should set its value to NULl if this
     * is an internal recursive call
     */
    if (NULL != end)
    {   
        /* 
         * Set endptr to a well-defined value in case of failure so
         * that caller can dereference endptr for debug purposes
         */
        *end = NULL; 
    }

    /* Populate fields with defaults in case they're omitted */
    debug_trace("populating expected json struct with default args.%c",'\r');
    for (cursor = attrs; NULL != cursor->attribute; cursor++)
    {
        if (!cursor->nodefault)
        {
            lptr = json_target_address(cursor, parent, offset);
            if (NULL != lptr)
            {
                switch (cursor->type)
                {
                    case t_integer:
                        memcpy( lptr, 
                                &cursor->dflt.integer, 
                                sizeof(int));
                        break;
                    case t_uinteger:
                        memcpy( lptr, 
                                &cursor->dflt.uinteger, 
                                sizeof(unsigned));
                        break;
                    case t_short:
                        memcpy( lptr, 
                                &cursor->dflt.shortint, 
                                sizeof(short));
                        break;
                    case t_ushort:
                        memcpy( lptr,
                                &cursor->dflt.ushortint,
                                sizeof(unsigned short));
                        break;
                    case t_time:
                    case t_real:
                        memcpy( lptr, 
                                &cursor->dflt.real, 
                                sizeof(realval));
                        break;
                    case t_string:
                        if ((parent != NULL) && 
                            (parent->element_type != t_structobject) && 
                            (offset > 0))
                        {
                            return JERR_NOPARSTR;
                        }
                        lptr[0] = '\0';
                        break;
                    case t_boolean:
                        memcpy( lptr, 
                                &cursor->dflt.boolean, 
                                sizeof(bool));
                        break;
                    case t_character:
                        lptr[0] = cursor->dflt.character;
                        break;
                    
                    /* 
                     * These cases are here because I always compile with -Wall 
                     * and -Wextra but I HAAATE all the pedantic warnings 
                     */
                    case t_object: 
                    case t_structobject:
                    case t_array:
                    case t_check:
                    case t_ignore:
                        break;
                    default:
#if !defined(NDEBUG)
                        while(1)
                        {
                            /* 
                             * programmer forgot to add value to switchcase. Or 
                             * there was an error with parsing logic. either 
                             * way, hang in debug build 
                             */
                        }
#else
                        break;
#endif /* DEBUG BUILD */
                }
            }
        }
    }
    
    /* parse input JSON */
    debug_trace("JSON parse of '%s' begins.\n", char_ptr);
    
    /* GO TO END OF THE STRING */
    for (; *char_ptr != '\0'; char_ptr++)   
    {
        debug_trace( "State %-14s, looking at '%c' (%p)\n",
                      statenames[state], *char_ptr, char_ptr);
        switch(state)
        {
            case init:
                if (isspace((unsigned char)*char_ptr))
                {
                    continue;
                }
                else if ('{' == *char_ptr)
                {
                    state = await_attr;
                }
                else
                {   
                    /* all jsons must have first non-ws char == { */
                    debug_trace("%s\n", json_error_string(JERR_OBSTART));
                    if (NULL != end)
                    {
                        *end = char_ptr;
                    }
                    return JERR_OBSTART;
                }
                break;
            case await_attr: /* we're looking for keys */
                if (isspace((unsigned char)*char_ptr))
                {
                    continue;
                }
                else if ('"' == *char_ptr)  /* found the start of a key */
                {
                    state = in_attr;
                    pattr = attrbuf;
                    if (NULL != end)
                    {
                        *end = char_ptr;
                    }
                }
                else if ('}' == *char_ptr)  /* no more keys in object */
                {
                    break;
                }
                else /* expected a key in obj but found something else */
                {
                    debug_trace("%s\n", json_error_string(JERR_ATTRSTART));
                    if (NULL != end)
                    {
                        *end = char_ptr;
                    }
                    return JERR_ATTRSTART;
                }
                break;
            case in_attr:
                if (NULL == pattr)
                {
                    /* don't update end here, leave at attribute start */
                    return JERR_NULLPTR;
                }
                if ('"' == *char_ptr) /* found the end of the >key< */
                {
                    *pattr++ = '\0';    
                    debug_trace("Collected key: >%s<\n", attrbuf);

                    /* compare the key against the list of valid keys */
                    int key_i = 0;
                    cursor = attrs;
                    for (; NULL != cursor->attribute; cursor++, key_i++) 
                    /* WARNING: WHEN USER IS SETTING UP EXPECTED JSON 
                                STRUCTURE, ATTRIBUTE LISTS MUST BE NULL
                                TERMINATED OR UB WILL OCCUR 
                    */
                    {   
                        debug_trace("Checking with >%s<\n",cursor->attribute);
                        if(streq(cursor->attribute, attrbuf))
                        {   
                            debug_trace(">%s< matches a valid key\n",
                            attrbuf);

                            if(NULL != matched_key_idx)
                            {   

                                /* If trying to match the top level key */
                                if(UNMATCHED_PARENT_JSON_KEY_IDX == 
                                   *matched_key_idx)
                                {   
                                    /* store the index of the matched key */
                                    *matched_key_idx = key_i;
                                    
                                }
                            }
                            break;
                        }
                    }
                    if (NULL == cursor->attribute)
                    {
                        debug_trace(   "%s : %s Attributes begin with %s\n",
                                        json_error_string(JERR_BADATTR),
                                        attrbuf,
                                        attrs->attribute);

                        /* don't update end here, leave at attribute start */
                        return JERR_BADATTR;
                    }

                    /* 
                        this works because we will return upon error 
                        (see above) 
                        if no match for all lookups 
                    */
                    state = await_value;
                    switch(cursor->type)
                    {
                        case t_string:
                        {
                            maxlen = (int)cursor->len - 1;
                        }
                        break;
                        case t_check:
                        {
                            maxlen = (int)strlen(cursor->dflt.check);
                        }
                        break;
                        case t_time: /* fallthrough */
                        case t_ignore:
                        {
                            maxlen = (int)JSON_VAL_MAXLEN;
                        }
                        break;
                        default:
                        {
                            if(NULL != cursor->map)
                            {
                                maxlen = (int)sizeof(valbuf) - 1;
                            }
                        }
                        break;
                    }
                    pval = valbuf;
                }
                else if (pattr >= (attrbuf + JSON_KEY_MAXLEN - 1))
                {
                    debug_trace("%s\n", json_error_string(JERR_ATTRLEN));
                    /* don't update end here, leave at attribute start */
                    return JERR_ATTRLEN;
                }
                else
                {
                    *pattr++ = *char_ptr;
                }
                break;
            case await_value:
                if (isspace((unsigned char)*char_ptr) || (':' == *char_ptr))
                {
                    continue;
                }
                else if ('[' == *char_ptr)
                {
                    if (t_array != cursor->type)
                    {
                        debug_trace("%s\n", json_error_string(JERR_NOARRAY));
                        if (NULL != end)
                        {
                            *end = char_ptr;
                        }
                        return JERR_NOARRAY;
                    }
                    substatus = json_read_array (char_ptr, 
                                                 &cursor->addr.array, 
                                                 &char_ptr);
                    if (0 != substatus) /* return on err */
                    {
                        return substatus;
                    }
                    state = post_element;
                }
                else if (t_array == cursor->type)
                {
                    debug_trace("%s\n", json_error_string(JERR_NOBRAK));
                    if (NULL != end)
                    {
                        *end = char_ptr;
                    }
                    return JERR_NOBRAK;
                }
                else if ('{' == *char_ptr)
                {
                    if (t_object != cursor->type)
                    {
                        debug_trace("%s\n", json_error_string(JERR_CURLNOBJ));
                        if (NULL != end)
                        {
                            *end = char_ptr;
                        }
                        return JERR_NOARRAY;
                    }

                    /* 
                     * TODO: figure out why I didn't put the internal function
                     * call here... maybe it was a mistake? I can't remember.
                     * it's been months since I last touched this :( 
                     */
                    substatus = json_read_object( char_ptr, 
                                                  cursor->addr.attrs, 
                                                  &char_ptr, NULL);
                    if (0 != substatus) /* return on err */
                    {
                        return substatus;
                    }
                    state = post_element;
                }
                else if (cursor->type == t_object)
                {
                    debug_trace("%s\n", json_error_string(JERR_NOCURLY));
                    if (NULL != end)
                    {
                        *end = char_ptr;
                    }
                    return JERR_NOCURLY;
                }
                else if ('"' == *char_ptr)
                {
                    value_quoted = true;
                    state = in_val_string;
                    pval = valbuf;
                }
                else
                {
                    value_quoted = false;
                    state = in_val_token;
                    pval = valbuf;
                    *pval++ = *char_ptr;
                }
                break;
            case in_val_string:
                if (NULL == pval)
                {
                    /* don't update end here, leave at value start */
                    return JERR_NULLPTR;
                }
                if ('\\' == *char_ptr)
                {
                    state = in_escape;
                }
                else if ('"' == *char_ptr)
                {
                    *pval++ = '\0';
                    debug_trace("Collected string value >%s<\n", valbuf);
                    state = post_val;
                }
                else if ((pval > valbuf + JSON_VAL_MAXLEN - 1) || 
                         (pval > valbuf + maxlen))
                {
                    debug_trace("%s\n", json_error_string(JERR_STRLONG));

                    /* don't update end here, leave at value start */
                    return JERR_STRLONG; /*  */
                }
                else
                {
                    *pval++ = *char_ptr;
                }
                break;
            case in_escape:
                if (NULL == pval)
                {
                    /* don't update end here, leave at value start */
                    return JERR_NULLPTR;
                }
                else if ((pval > valbuf + JSON_VAL_MAXLEN - 1) || 
                         (pval > valbuf + maxlen))
                {
                    debug_trace("%s\n", json_error_string(JERR_STRLONG));

                    /* don't update end here, leave at value start */
                    return JERR_STRLONG; /*  */
                }
                switch (*char_ptr)
                {
                case 'b':
                    *pval++ = '\b';
                    break;
                case 'f':
                    *pval++ = '\f';
                    break;
                case 'n':
                    *pval++ = '\n';
                    break;
                case 'r':
                    *pval++ = '\r';
                    break;
                case 't':
                    *pval++ = '\t';
                    break;
                case 'u':
                    /* magic number 4 here is number of escapable hex digits */

                    char_ptr++; /* skip the 'u' */
                    for (n = 0; n < 4 && isxdigit(*char_ptr); n++)
                    {
                        uescape[n] = *char_ptr++;
                    }
                    uescape[n] = '\0'; /* terminate */
                    --char_ptr;
                    /* ECMA-404 says JSON \u must have 4 hex digits */
                    if ((4 != n) || (1 != sscanf(uescape, "%" PRIX32, &u)))
                    {
                        return JERR_BADSTRING;
                    }
                    *pval++ = (unsigned char)u; /* truncate values above 0xff */
                    break;
                default: /* handles double quote and solidus */
                    *pval++ = *char_ptr;
                    break;
                }
                state = in_val_string;
                break;
            case in_val_token:
                if (NULL == pval)
                {
                    /* don't update end here, leave at value start */
                    return JERR_NULLPTR;
                }

                /* delimit end of token */ 
                if ((isspace((unsigned char)*char_ptr)) || 
                                    (',' == *char_ptr)  || 
                                    ('}' == *char_ptr))
                {
                    *pval = '\0';
                    debug_trace("Collected token value >%s<.\n", valbuf);
                    state = post_val;
                    if (('}' == *char_ptr) || (',' == *char_ptr))
                    {
                        --char_ptr;
                    }
                }
                else if (pval > (valbuf + JSON_VAL_MAXLEN - 1))
                {
                    debug_trace("%s\n", json_error_string(JERR_TOKLONG));

                    /* don't update end here, leave at value start */
                    return JERR_TOKLONG;
                }
                else
                {
                    *pval++ = *char_ptr;
                }
                break;
            case post_val:
/*** CONSIDER SCOPING ME HERE ***/

                /*
                * We know that cursor points at the first spec matching
                * the current attribute.  We don't know that it's *the*
                * correct spec; our dialect allows there to be any number
                * of adjacent ones with the same attrname but different
                * types.  Here's where we try to seek forward for a
                * matching type/attr pair if we're not looking at one.
                */
                for (;;)
                {   
                    /* TODO: 
                     * THIS ENTIRE SECTION SHOULD BE REFACTORED AND HAVE THE 
                     * LOGIC MORE CLEARLY LAID OUT 
                     */

                    if (value_quoted && 
                    ((t_string == cursor->type) || (t_time == cursor->type)))
                    {
                        break;
                    }

                    /* if looking for a boolean and found "true" or "false" */
                    if((t_boolean == cursor->type) &&
                       (0 == (streq(valbuf, "true") || streq(valbuf, "false"))))
                    {
                        
                        break;
                    }

                    if (isdigit((unsigned char)valbuf[0]))
                    {   
                        /*
                         * Error if:
                         *  - we're dealing with a real num and DIDNT
                         *    find a decimal
                         * 
                         * - we're dealing with an integer and DID find a 
                         *   decimal
                         */
                        bool isdecimal = (strchr(valbuf, '.') != NULL);
                        if (((isdecimal) && (t_real == cursor->type))     || 
                            ((!isdecimal) && ((t_integer == cursor->type) ||
                            (t_uinteger == cursor->type))))
                        {
                            break;
                        }
                    }
                    
                    if ((NULL == cursor[1].attribute) || 
                        (strneq(cursor[1].attribute, attrbuf)))
                    {
                        break;
                    }
                    ++cursor;
                }
                
                if(value_quoted)
                {
                    switch(cursor->type)
                    {   
                        case t_string:      /* strings require quotes       */
                        case t_character:   /* chars require quotes         */
                        case t_check:       /* check strings require quotes */
                        case t_time:        /* ISO time fmt requires quotes */
                        case t_ignore:      
                        {
                            /* These are all valid types */
                        }
                        break;
                        default:  /* All other types can't be quoted */
                        {
                            /* 
                             * If the quoted value does not map
                             * to an unquoted value 
                             */
                            if(0 == cursor->map)    
                            {   
                                /* 
                                 * We Found a quoted value 
                                 * when we were not supposed to 
                                 */
                                debug_trace("%s\n", 
                                json_error_string(JERR_QNONSTRING));
                                return JERR_QNONSTRING;
                            }
                            else
                            {
                                /*
                                 * Even if the map exists we don't look up
                                 * the mapped value here.
                                 */
                            }
                        }
                        break;
                    }
                }
                else /* value is not quoted */
                {
                    switch(cursor->type)
                    {   
                        case t_string:      /* strings require quotes       */
                        case t_character:   /* chars require quotes         */
                        case t_check:       /* check strings require quotes */
                        case t_time:        /* ISO time fmt requires quotes */
                        case t_ignore:      /* notSureIfIShouldPutThisHere  */
                        {
                            if(0 != cursor->map)
                            {   
                                /* 
                                 * Didn't find a quoted value 
                                 * when were supposed to 
                                 */
                                debug_trace("%s\n", json_error_string(JERR_NONQSTRING));
                                return JERR_NONQSTRING;
                            }
                        }   
                        break;
                        default:    /* Everything else is ok */
                        {
                            /* All the other types aren't supposed to
                               have quotes */
                        }
                        break;
                    }
                }
                
                /* Look up mapped value if it exists */
                if (0 != cursor->map)
                {   
                    /* Go through the map index and attempt a lookup */
                    for (mp = cursor->map; NULL != mp->name; mp++)
                    {   
                        if(streq(mp->name, valbuf))
                        {
                            snprintf( valbuf, 
                                     sizeof(valbuf), 
                                     "%" PRId32, 
                                     mp->value);
                            break;
                        }
                    }

                    if(NULL == mp->name)
                    {
                        /* map doesn't contain a valid reference */
                        debug_trace("%s\n", json_error_string(JERR_BADENUM));
                        return JERR_BADENUM;
                    }
                }

                /* 
                 * Get the value and then 
                 * load it into the place that 
                 * caller has provided to store it 
                 */
                lptr = json_target_address(cursor, parent, offset);
                if (NULL != lptr)
                {
                    switch (cursor->type)
                    {
                        case t_integer:
                        {
                            int tmp = atoi(valbuf);
                            memcpy(lptr, &tmp, sizeof(tmp));
                        }
                        break;
                        case t_uinteger:
                        {
                            unsigned tmp = (unsigned)atoi(valbuf);
                            memcpy(lptr, &tmp, sizeof(tmp));
                        }
                        break;
                        case t_short:
                        {
                            short tmp = atoi(valbuf);
                            memcpy(lptr, &tmp, sizeof(short));
                        }
                        break;
                        case t_ushort:
                        {
                            unsigned short tmp = (unsigned)atoi(valbuf);
                            memcpy(lptr, &tmp, sizeof(unsigned short));
                        }
                        break;
                        case t_time:
                        {
#ifdef TIME_ENABLE
                            {
                                realval tmp = iso8601_to_unix(valbuf);
                                memcpy(lptr, &tmp, sizeof(realval));
                            }
#endif /* TIME_ENABLE */
                        }
                        break;
                        case t_real:
                        {   
                            realval tmp = atof(valbuf);
                            memcpy(lptr, &tmp, sizeof(realval));
                        }
                        break;
                        case t_string:
                        {
                            /* Objects can't own a string   */
                            /* eg: {....} : "mystr"         */
                            /* The above is invalid         */
                            if ((NULL != parent)                        && 
                                (t_structobject !=parent->element_type) &&
                                (offset > 0))
                            {
                                return JERR_NOPARSTR;
                            }
                            else
                            {   
                                /* value length */
                                size_t vl = strlen(valbuf);

                                /* cursor buffer length */
                                size_t cl = cursor->len - 1;
                                memset(lptr, '\0', cl);
                                memcpy(lptr, valbuf, vl < cl ? vl : cl);
                            }
                        }
                        break;
                        case t_boolean:
                        {
                            bool tmp = (strcmp(valbuf, "true") == 0);
                            memcpy(lptr, &tmp, sizeof(bool));
                        }
                        break;
                        case t_character:
                        {
                            if (strlen(valbuf) > 1)
                            {
                                /* don't update end pointer here. */
                                /* leave at attr start for errmsg */
                                return JERR_STRLONG;
                            }
                            else
                            {
                                lptr[0] = valbuf[0];
                            }
                        }
                        break;
                        case t_ignore: /* silences a compiler warning */
                        case t_object: /* silences a compiler warning */
                        case t_structobject:
                        case t_array:
                        {
                            /* do nothing */
                        }
                        break;
                        case t_check:
                        {
                            if(strneq(cursor->dflt.check, valbuf))
                            {   
                                debug_trace("%s %s\n", 
                                json_error_string(JERR_CHECKFAIL), 
                                cursor->dflt.check);

                                /* don't update end pointer here. */
                                /* leave at attr start for errmsg */
                                return JERR_CHECKFAIL;
                            }
                        }
                        break;
                    }
                }
/*** CONSIDER SCOPING ME HERE */
            case post_element:
                if (isspace((unsigned char)*char_ptr))
                {
                    continue;
                }
                else if (',' == *char_ptr)
                {
                    state = await_attr;
                }
                else if ('}' == *char_ptr)
                {
                    ++char_ptr;
                    goto good_parse;
                }
                else
                {   
                    debug_trace("%s\n", json_error_string(JERR_BADSUBTRAIL));
                    if (NULL != end)
                    {
                        *end = char_ptr;
                    }
                    return JERR_BADTRAIL;
                }
                break;
        }   /* endof : switch(state) */
    }

good_parse:
    /* in case there's another object following, consume trailing WS */
    while (isspace((unsigned char)*char_ptr))
    {
        ++char_ptr;
    }
    if (NULL != end)
    {
        *end = char_ptr;
    }
    debug_trace("JSON parse ends%c",'\n');
    return 0;
}


int json_read_array(const char *char_ptr, const struct json_array *arr,
                    const char **end)
{
    int substatus, offset, arrcount;
    char *tp;

    if (NULL != end)
    {
        *end = NULL; /* give it a well-defined value on parse failure */
    }

    debug_trace("Entered json_read_array()%c",'\n');

    while (isspace((unsigned char)*char_ptr))
    {
        char_ptr++;
    }
    if ('[' != *char_ptr)
    {   
        debug_trace("%s\n", json_error_string(JERR_ARRSTART));
        return JERR_ARRSTART;
    }
    else
    {
        char_ptr++;
    }

    tp = arr->arr.strings.store;
    arrcount = 0;

    /* Check for empty array */
    while (isspace((unsigned char)*char_ptr))
    {
        char_ptr++;
    }
    if (']' == *char_ptr)
    {
        goto breakout;
    }

    for (offset = 0; offset < arr->maxlen; offset++)
    {
        char *ep = NULL;
        debug_trace("Looking at %s\n", char_ptr);
        switch (arr->element_type)
        {
            case t_string:
                if (isspace((unsigned char)*char_ptr))
                {
                    char_ptr++;
                }
                if ('"' != *char_ptr)
                {
                    return JERR_BADSTRING;
                }
                else
                {
                    ++char_ptr;
                }
                arr->arr.strings.ptrs[offset] = tp;
                for (; tp - arr->arr.strings.store < arr->arr.strings.storelen;
                    tp++)
                {
                    if ('"' == *char_ptr)
                    {
                        ++char_ptr;
                        *tp++ = '\0';
                        goto stringend;
                    }
                    else if ('\0' == *char_ptr)
                    {
                        debug_trace("%s\n", json_error_string(JERR_BADSTRING));
                        return JERR_BADSTRING;
                    }
                    else
                    {
                        *tp = *char_ptr++;
                    }
                }
                    debug_trace("%s\n", json_error_string(JERR_BADSTRING));
                    return JERR_BADSTRING;

            stringend:
                break;
            case t_object:      /* fallthrough */
            case t_structobject:

                /* RECURSIVE CALL TO PARSE CHILD OBJECT */
                substatus =
                    json_internal_read_object(  char_ptr, 
                                                arr->arr.objects.subtype, 
                                                arr,
                                                offset, 
                                                &char_ptr, NULL);
                if (0 != substatus)
                {
                    if (NULL != end)
                    {   
                        /* leave endptr at where the error occurred */
                        end = &char_ptr;
                    }
                    return substatus;
                }
                break;
            case t_integer:
                arr->arr.integers.store[offset] = (int)strtol(char_ptr, &ep, 0);
                if (ep == char_ptr)
                {
                    return JERR_BADNUM;
                }
                else
                {
                    char_ptr = ep;
                }
                break;
            case t_uinteger:
                arr->arr.uintegers.store[offset] = 
                                    (unsigned)strtoul(char_ptr, &ep,0);
                if (ep == char_ptr)
                {
                    return JERR_BADNUM;
                }
                else
                {
                    char_ptr = ep;
                }
                break;
            case t_short:
                arr->arr.shorts.store[offset] = (short)strtol(char_ptr, &ep, 0);
                if (ep == char_ptr)
                {
                    return JERR_BADNUM;
                }
                else
                {
                    char_ptr = ep;
                }
                break;
            case t_ushort:
                arr->arr.ushorts.store[offset] = 
                                    (unsigned short)strtol(char_ptr, &ep, 0);
                if (ep == char_ptr)
                {
                    return JERR_BADNUM;
                }
                else
                {
                    char_ptr = ep;
                }
                break;
            case t_time:
#ifdef TIME_ENABLE
                if ('"' != *char_ptr)
                {
                    return JERR_BADSTRING;
                }
                else
                {
                    ++char_ptr;
                }

                arr->arr.reals.store[offset] =iso8601_to_unix((char *)char_ptr);

                if (arr->arr.reals.store[offset] >= HUGE_VAL)
                {
                    return JERR_BADNUM;
                }
                while ((NULL != char_ptr) && ('"' != *char_ptr))
                {
                    char_ptr++;
                }
                if ('"' != *char_ptr) /* we hit NULL */
                {
                    return JERR_BADSTRING;
                }
                else
                {
                    ++char_ptr;
                }
                break;
#endif /* TIME_ENABLE */
            case t_real:
                arr->arr.reals.store[offset] = (realval)strtod(char_ptr, &ep);
                if (ep == char_ptr)
                {
                    return JERR_BADNUM;
                }
                else
                {
                    char_ptr = ep;
                }
                break;
            case t_boolean:
                if (str_starts_with(char_ptr, "true"))
                {
                    arr->arr.booleans.store[offset] = true;
                    char_ptr += strlen("true");
                }
                else if (str_starts_with(char_ptr, "false"))
                {
                    arr->arr.booleans.store[offset] = false;
                    char_ptr += strlen("false");
                }
                break;
            case t_character:
            case t_array:
            case t_check:
            case t_ignore:
                debug_trace("%s\n", json_error_string(JERR_SUBTYPE));
                return JERR_SUBTYPE;
        }
        arrcount++;

        if (isspace((unsigned char)*char_ptr))
        {
            char_ptr++;
        }
        if (']' == *char_ptr)
        {
            debug_trace("End of array found.%c", '\n');
            goto breakout;
        }
        else if (',' == *char_ptr)
            char_ptr++;
        else
        {   
            debug_trace("%s\n", json_error_string(JERR_BADARRTRAIL));
            return JERR_BADSUBTRAIL;
        }
    }
    debug_trace("%s\n", json_error_string(JERR_SUBTOOLONG));
    if (NULL != end)
    {
        *end = char_ptr;
    }
    return JERR_SUBTOOLONG;

breakout:
    if (NULL != arr->count)
    {
        *(arr->count) = arrcount;
    }
    if (NULL != end)
    {
        *end = char_ptr;
    }
    debug_trace("leaving json_read_array() with %d elements\n", arrcount);
    return 0;
}

int json_read_object( const char *char_ptr, 
                      const struct json_attr *attrs,
                      const char **end, 
                      int *matched_key_idx)
{
    debug_trace("json_read_object() sees '%s'\n", char_ptr);
    return json_internal_read_object(char_ptr, 
                                     attrs, 
                                     NULL, 
                                     0, 
                                     end, 
                                     matched_key_idx);
}


/* Error messages for error codes that can be set during parsing */
static const char *jerrs[] = 
{   
    [JERR_UNKNOWN]      = "UNKOWN JERR ERROR CODE.",
    [JERR_OBSTART]      = "non-whitespace when expecting object start",
    [JERR_ATTRSTART]    = "non-whitespace when expecting attribute start",
    [JERR_BADATTR]      = "unknown attribute name",
    [JERR_ATTRLEN]      = "attribute name too long",
    [JERR_NOARRAY]      = "saw [ when not expecting array",
    [JERR_CURLNOBJ]     = "saw { when not expecting object",
    [JERR_NOBRAK]       = "array element specified, but no [",
    [JERR_STRLONG]      = "string value too long",
    [JERR_TOKLONG]      = "token value too long",
    [JERR_BADTRAIL]     = "garbage while expecting comma or } or ]",
    [JERR_ARRSTART]     = "didn't find expected array start",
    [JERR_OBJARR]       = "error while parsing object array",
    [JERR_SUBTOOLONG]   = "too many array elements",
    [JERR_BADSUBTRAIL]  = "garbage while expecting array comma",
    [JERR_BADARRTRAIL]  = "Bad trailing syntax on array",
    [JERR_SUBTYPE]      = "invalid or unexpected array element type",
    [JERR_BADSTRING]    = "error while string parsing",
    [JERR_CHECKFAIL]    = "required attribute not present",
    [JERR_NOPARSTR]     = "can't support strings in parallel arrays",
    [JERR_BADENUM]      = "invalid enumerated value",
    [JERR_QNONSTRING]   = "saw quoted value when expecting nonstring",
    [JERR_NONQSTRING]   = "didn't see quoted value when expecting string",
    [JERR_MISC]         = "other data conversion error",
    [JERR_NULLPTR]      = "unexpected null value or attribute pointer",
    [JERR_NOCURLY]      = "object element specified, but no {",
};


const char *json_error_string(int code)
{
    if(code < sizeof(jerrs)/sizeof(jerrs[0]))
    {
        return jerrs[JERR_UNKNOWN];
    }
    else
    {
        return jerrs[code];
    }
}
