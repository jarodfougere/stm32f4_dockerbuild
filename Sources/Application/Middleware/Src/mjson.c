/****************************************************************************
NAME
   mjson.c - parse JSON into fixed-extent data structures

DESCRIPTION
   This module parses a large subset of JSON (JavaScript Object
Notation).  Unlike more general JSON parsers, it doesn't use malloc(3)
and doesn't support polymorphism; you need to give it a set of
template structures describing the expected shape of the incoming
JSON, and it will error out if that shape is not matched.  When the
parse succeeds, attribute values will be extracted into static
locations specified in the template structures.

   The "shape" of a JSON object in the type signature of its
attributes (and attribute values, and so on recursively down through
all nestings of objects and arrays).  This parser is indifferent to
the order of attributes at any level, but you have to tell it in
advance what the type of each attribute value will be and where the
parsed value will be stored. The template structures may supply
default values to be used when an expected attribute is omitted.

   The preceding paragraph told one fib.  A single attribute may
actually have a span of multiple specifications with different
syntactically distinguishable types (e.g. string vs. real vs. integer
vs. boolean, but not signed integer vs. unsigned integer).  The parser
will match the right spec against the actual data.

   The dialect this parses has some limitations.  First, it cannot
recognize the JSON "null" value. Second, all elements of an array must
be of the same type. Third, characters may not be array elements (this
restriction could be lifted)

   There are separate entry points for beginning a parse of either
JSON object or a JSON array. JSON "float" quantities are actually
stored as doubles.

   This parser processes object arrays in one of two different ways,
defending on whether the array subtype is declared as object or
structobject.

   Object arrays take one base address per object subfield, and are
mapped into parallel C arrays (one per subfield).  Strings are not
supported in this kind of array, as they don't have a "natural" size
to use as an offset multiplier.

   Structobjects arrays are a way to parse a list of objects to a set
of modifications to a corresponding array of C structs.  The trick is
that the array object initialization has to specify both the C struct
array's base address and the stride length (the size of the C struct).
If you initialize the offset fields with the correct offsetof calls,
everything will work. Strings are supported but all string storage
has to be inline in the struct.

PERMISSIONS
   This file is Copyright (c) 2014 by Eric S. Raymond
   SPDX-License-Identifier: BSD-2-Clause

***************************************************************************/
/* The strptime prototype is not provided unless explicitly requested.
 * We also need to set the value high enough to signal inclusion of
 * newer features (like clock_gettime).  See the POSIX spec for more info:
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_02_01_02 */


/**
 * @file mjson.c
 * @author Carl Mattatall
 * @brief This file is a custom JSON parser for embedded systems based on
 *        the microJson source code. 
 *        Modifications have been made to recursively parse sub-objects.
 *        
 *        Just like with microJson, the user must layout the expected JSON
 *        tree structure in advance. JSON attribute arrays must be NULL pointer
 *        delimited.
 *        
 *        The matched attribute string of the first key for the top-level 
 *        JSON object is stored upon parsing the JSON. This is intended to be
 *        used for indexing into a function array for runtime execution 
 *        based on the matched key.
 * 
 *        integer field widths are intended for a 32bit word len processor
 * @version 0.1
 * @date 2020-02-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#define _XOPEN_SOURCE 600

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
#endif

#include "debug.h"
#include "mjson.h"

#define str_starts_with(s, p) (strncmp(s, p, strlen(p)) == 0)

#ifdef MJSON_DEBUG_ENABLE
static int32_t debuglevel = 0;
static FILE *debugfp = NULL;

void json_enable_debug(int32_t level, FILE *fp)
/* control the level and destination of debug trace messages */
{   
    debuglevel = level;
    debugfp = fp;
}

static void json_trace(int32_t errlevel, const char *fmt, ...)
/* assemble command in printf(3) style */
{
    if (errlevel <= debuglevel)
    {
        char buf[BUFSIZ];
        va_list ap;

        (void)strncpy(buf, "json: ", BUFSIZ - 1);
        buf[BUFSIZ - 1] = '\0';
        va_start(ap, fmt);
        (void)vsnprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), fmt,
                        ap);
        va_end(ap);
        transmit_serial(buf);
    }
}

#define debug_trace(args) (void)json_trace args
#else
#define debug_trace(args) \
    do                         \
    {                          \
    } while (0)
#endif /* MJSON_DEBUG_ENABLE */

static char *json_target_address(const struct json_attr_t *cursor,
                                 const struct json_array_t *parent,
                                 int32_t offset)
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
            targetaddr = (char *)&cursor->addr.integer[offset];
            break;
        case t_uinteger:
            targetaddr = (char *)&cursor->addr.uinteger[offset];
            break;
        case t_short:
            targetaddr = (char *)&cursor->addr.shortint[offset];
            break;
        case t_ushort:
            targetaddr = (char *)&cursor->addr.ushortint[offset];
            break;
        case t_time:
        case t_real:
            targetaddr = (char *)&cursor->addr.real[offset];
            break;
        case t_string:
            targetaddr = cursor->addr.string;
            break;
        case t_boolean:
            targetaddr = (char *)&cursor->addr.boolean[offset];
            break;
        case t_character:
            targetaddr = (char *)&cursor->addr.character[offset];
            break;
        default:
            targetaddr = NULL;
            break;
        }
    }
    else
        /* tricky case - hacking a member in an array of structures */
        targetaddr =
            parent->arr.objects.base + (offset * parent->arr.objects.stride) +
            cursor->addr.offset;
    debug_trace((1, "Target address for %s (offset %d) is %p\n",
                      cursor->attribute, offset, targetaddr));
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

static int32_t json_internal_read_object(   const char *char_ptr,
                                            const struct json_attr_t *attrs,
                                            const struct json_array_t *parent,
                                            int32_t offset,
                                            const char **end,
                                            int32_t* matched_key_idx)
{
    enum
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
    }   state = 0;
#ifdef MJSON_DEBUG_ENABLE
    char *statenames[] = {
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
#endif /* MJSON_DEBUG_ENABLE */
    char attrbuf[JSON_ATTR_MAX + 1];
    char *pattr = NULL;
    char valbuf[JSON_VAL_MAX + 1];
    char *pval = NULL;

    char uescape[5]; /* enough space for 4 hex digits and a NUL */
    const struct json_attr_t *cursor; /* token cursor */
    bool value_quoted = false;        /* differentiates between 1 and "1" */

    int32_t substatus;                    /* retval for sub objects */
    int32_t n;
    int32_t maxlen = 0;                   /* parsable string length */
    uint32_t u;
    const struct json_enum_t *mp;
    char *lptr;

    if (end != NULL)
    {
        *end = NULL; /* give it a well-defined value on parse failure */
    }

    /* stuff fields with defaults in case they're omitted in the JSON input */
    debug_trace((1, "populating expected json structure with default args.\n"));
    for (cursor = attrs; cursor->attribute != NULL; cursor++)
    {
        if (!cursor->nodefault)
        {
            lptr = json_target_address(cursor, parent, offset);
            if (lptr != NULL)
                switch (cursor->type)
                {
                    case t_integer:
                        memcpy(lptr, &cursor->dflt.integer, sizeof(int32_t));
                        break;
                    case t_uinteger:
                        memcpy(lptr, &cursor->dflt.uinteger, sizeof(uint32_t));
                        break;
                    case t_short:
                        memcpy(lptr, &cursor->dflt.shortint, sizeof(int16_t));
                        break;
                    case t_ushort:
                        memcpy(lptr,&cursor->dflt.ushortint,sizeof(uint16_t));
                        break;
                    case t_time:
                    case t_real:
#if defined(DOUBLE_DECIMAL_PRECISION)
                        memcpy(lptr, &cursor->dflt.real, sizeof(double));
#else
                        memcpy(lptr, &cursor->dflt.real, sizeof(float));
#endif
                        break;
                    case t_string:
                        if (parent != NULL && parent->element_type != t_structobject && offset > 0)
                        {
                            return JSON_ERR_NOPARSTR;
                        }
                        lptr[0] = '\0';
                        break;
                    case t_boolean:
                        memcpy(lptr, &cursor->dflt.boolean, sizeof(bool));
                        break;
                    case t_character:
                        lptr[0] = cursor->dflt.character;
                        break;
                    case t_object: /* silences a compiler warning */
                    case t_structobject:
                    case t_array:
                    case t_check:
                    case t_ignore:
                        break;
                }
        }
    }
    
    /* parse input JSON */
    debug_trace((1, "JSON parse of '%s' begins.\n", char_ptr));
    for (; *char_ptr != '\0'; char_ptr++)   /* go through each character in the string */
    {
        debug_trace((2, "State %-14s, looking at '%c' (%p)\n",
                          statenames[state], *char_ptr, char_ptr));
        switch (state)
        {
            case init:
                if (isspace((unsigned char)*char_ptr))
                {
                    continue;
                }
                else if (*char_ptr == '{')
                {
                    state = await_attr;
                }
                else
                {
                    debug_trace((1,
                                    "Non-WS when expecting object start.\n"));
                    if (end != NULL)
                    {
                        *end = char_ptr;
                    }
                    return JSON_ERR_OBSTART;
                }
                break;
            case await_attr:
                if (isspace((unsigned char)*char_ptr))
                {
                    continue;
                }
                else if (*char_ptr == '"')  /* found the start of a key */
                {
                    state = in_attr;
                    pattr = attrbuf;
                    if (end != NULL)
                    {
                        *end = char_ptr;
                    }
                }
                else if (*char_ptr == '}')
                {
                    break;
                }
                else
                {
                    debug_trace((1, "Non-WS when expecting attribute in obj.\n"));
                    if (end != NULL)
                    {
                        *end = char_ptr;
                    }
                    return JSON_ERR_ATTRSTART;
                }
                break;
            case in_attr:
                if (pattr == NULL)
                {
                    /* don't update end here, leave at attribute start */
                    return JSON_ERR_NULLPTR;
                }
                if (*char_ptr == '"') /* found the end of the >key< */
                {
                    *pattr++ = '\0';    
                    debug_trace((1, "Collected attribute name %s\n",
                                    attrbuf));

                    /* compare the key against the list of valid keys */
                    int32_t key_i = 0;
                    for (cursor = attrs; cursor->attribute != NULL; cursor++, key_i++) 
                    /* WARNING: WHEN USER IS SETTING UP EXPECTED JSON 
                                STRUCTURE, ATTRIBUTE LISTS MUST BE NULL
                                TERMINATED OR UB WILL OCCUR 
                    */
                    {   
                        debug_trace((2, "Checking against %s\n",
                                        cursor->attribute));
                        if (strcmp(cursor->attribute, attrbuf) == 0)
                        {   
                            debug_trace((1, "%s matches a valid key\n",
                            attrbuf));

                            if(NULL != matched_key_idx)
                            {   

                                /* If trying to match the top level key */
                                if(UNMATCHED_TOPLEVEL_KEY_IDX == *matched_key_idx)
                                {   
                                    /* store the index of the matched key */
                                    *matched_key_idx = key_i;
                                    
                                }
                            }
                            break;
                        }
                    }
                    if (cursor->attribute == NULL)
                    {
                        debug_trace((1,
                                        "Unknown attribute name '%s'"
                                        " (attributes begin with '%s').\n",
                                        attrbuf, attrs->attribute));
                        /* don't update end here, leave at attribute start */
                        return JSON_ERR_BADATTR;
                    }

                    /* 
                        this works because we will return upon error 
                        (see above) 
                        if no match for all lookups 
                    */
                    state = await_value;
                    if (cursor->type == t_string)
                    {
                        maxlen = (int32_t)cursor->len - 1;
                    }
                    else if (cursor->type == t_check)
                    {
                        maxlen = (int32_t)strlen(cursor->dflt.check);
                    }
                    else if (cursor->type == t_time || cursor->type == t_ignore)
                    {
                        maxlen = JSON_VAL_MAX;
                    }
                    else if (cursor->map != NULL)
                    {
                        maxlen = (int32_t)sizeof(valbuf) - 1;
                    }
                    pval = valbuf;
                }
                else if (pattr >= attrbuf + JSON_ATTR_MAX - 1)
                {
                    debug_trace((1, "Attribute name too long.\n"));
                    /* don't update end here, leave at attribute start */
                    return JSON_ERR_ATTRLEN;
                }
                else
                {
                    *pattr++ = *char_ptr;
                }
                break;
            case await_value:
                if (isspace((unsigned char)*char_ptr) || *char_ptr == ':')
                {
                    continue;
                }
                else if (*char_ptr == '[')
                {
                    if (cursor->type != t_array)
                    {
                        debug_trace((1,
                                        "Saw [ when not expecting array.\n"));
                        if (end != NULL)
                        {
                            *end = char_ptr;
                        }
                        return JSON_ERR_NOARRAY;
                    }
                    substatus = json_read_array(char_ptr, &cursor->addr.array, &char_ptr);
                    if (substatus != 0)
                    {
                        return substatus;
                    }
                    state = post_element;
                }
                else if (cursor->type == t_array)
                {
                    debug_trace((1,
                                    "Array element was specified, but no [.\n"));
                    if (end != NULL)
                    {
                        *end = char_ptr;
                    }
                    return JSON_ERR_NOBRAK;
                }
                else if (*char_ptr == '{')
                {
                    if (cursor->type != t_object)
                    {
                        debug_trace((1,
                                        "Saw { when not expecting object.\n"));
                        if (end != NULL)
                        {
                            *end = char_ptr;
                        }
                        return JSON_ERR_NOARRAY;
                    }
                    substatus = json_read_object(char_ptr, cursor->addr.attrs, &char_ptr, NULL);
                    if (substatus != 0)
                    {
                        return substatus;
                    }
                    state = post_element;
                }
                else if (cursor->type == t_object)
                {
                    debug_trace((1,
                                    "Object element was specified, but no {.\n"));
                    if (end != NULL)
                    {
                        *end = char_ptr;
                    }
                    return JSON_ERR_NOCURLY;
                }
                else if (*char_ptr == '"')
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
                if (pval == NULL)
                {
                    /* don't update end here, leave at value start */
                    return JSON_ERR_NULLPTR;
                }
                if (*char_ptr == '\\')
                {
                    state = in_escape;
                }
                else if (*char_ptr == '"')
                {
                    *pval++ = '\0';
                    debug_trace((1, "Collected string value %s\n", valbuf));
                    state = post_val;
                }
                else if (pval > valbuf + JSON_VAL_MAX - 1 || pval > valbuf + maxlen)
                {
                    debug_trace((1, "String value too long.\n"));
                    /* don't update end here, leave at value start */
                    return JSON_ERR_STRLONG; /*  */
                }
                else
                {
                    *pval++ = *char_ptr;
                }
                break;
            case in_escape:
                if (pval == NULL)
                {
                    /* don't update end here, leave at value start */
                    return JSON_ERR_NULLPTR;
                }
                else if (pval > valbuf + JSON_VAL_MAX - 1 || pval > valbuf + maxlen)
                {
                    debug_trace((1, "String value too long.\n"));
                    /* don't update end here, leave at value start */
                    return JSON_ERR_STRLONG; /*  */
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
                        return JSON_ERR_BADSTRING;
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
                if (pval == NULL)
                {
                    /* don't update end here, leave at value start */
                    return JSON_ERR_NULLPTR;
                }

                /* delimit end of token */ 
                if (isspace((unsigned char)*char_ptr) || *char_ptr == ',' || *char_ptr == '}')
                {
                    *pval = '\0';
                    debug_trace((1,"Collected token value %s.\n", valbuf));
                    state = post_val;
                    if (*char_ptr == '}' || *char_ptr == ',')
                    {
                        --char_ptr;
                    }
                }
                else if (pval > valbuf + JSON_VAL_MAX - 1)
                {
                    debug_trace((1, "Token value too long.\n"));
                    /* don't update end here, leave at value start */
                    return JSON_ERR_TOKLONG;
                }
                else
                {
                    *pval++ = *char_ptr;
                }
                break;
            case post_val:
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
                    int32_t seeking = cursor->type;

                    if (value_quoted && (cursor->type == t_string || cursor->type == t_time))
                    {
                        break;
                    }

                    if ((strcmp(valbuf, "true") == 0 || strcmp(valbuf, "false") == 0) && seeking == t_boolean)
                    {
                        break;
                    }

                    if (isdigit((unsigned char)valbuf[0]))
                    {
                        bool decimal = strchr(valbuf, '.') != NULL;
                        if ((decimal && seeking == t_real) || 
                            (!decimal && (seeking == t_integer || seeking == t_uinteger)))
                        {
                            break;

                        }
                    }
                    
                    if (cursor[1].attribute == NULL || strcmp(cursor[1].attribute, attrbuf) != 0)
                    {
                        break;
                    }
                    ++cursor;
                }
                
                if (value_quoted && (cursor->type != t_string && cursor->type != t_character && cursor->type != t_check && cursor->type != t_time && cursor->type != t_ignore && cursor->map == 0))
                {
                    debug_trace((1, "Saw quoted value when expecting"
                                        " non-string.\n"));
                    return JSON_ERR_QNONSTRING;
                }

                if (!value_quoted && (cursor->type == t_string || cursor->type == t_check || cursor->type == t_time || cursor->map != 0))
                {
                    debug_trace((1, "Didn't see quoted value when expecting"
                                        " string.\n"));
                    return JSON_ERR_NONQSTRING;
                }

                if (cursor->map != 0)
                {
                    for (mp = cursor->map; mp->name != NULL; mp++)
                    {
                        if (strcmp(mp->name, valbuf) == 0)
                        {
                            goto foundit;
                        }
                    }
                    debug_trace((1, "Invalid enumerated value string %s.\n",
                                    valbuf));
                    return JSON_ERR_BADENUM;
                foundit:
                    (void)snprintf(valbuf, sizeof(valbuf), "%" PRId32, mp->value);
                }
                lptr = json_target_address(cursor, parent, offset);

                if (lptr != NULL)
                {
                    switch (cursor->type)
                    {
                        case t_integer:
                        {
                            int32_t tmp = atoi(valbuf);
                            memcpy(lptr, &tmp, sizeof(int32_t));
                        }
                        break;
                        case t_uinteger:
                        {
                            uint32_t tmp = (uint32_t)atoi(valbuf);
                            memcpy(lptr, &tmp, sizeof(uint32_t));
                        }
                        break;
                        case t_short:
                        {
                            int16_t tmp = atoi(valbuf);
                            memcpy(lptr, &tmp, sizeof(int16_t));
                        }
                        break;
                        case t_ushort:
                        {
                            uint16_t tmp = (uint32_t)atoi(valbuf);
                            memcpy(lptr, &tmp, sizeof(uint16_t));
                        }
                        break;
                        case t_time:
    #ifdef TIME_ENABLE
                        {
                            double tmp = iso8601_to_unix(valbuf);
                            memcpy(lptr, &tmp, sizeof(double));
                        }
    #endif /* TIME_ENABLE */
                        break;
                        case t_real:
                        {   
#if defined(DOUBLE_DECIMAL_PRECISION)
                            double tmp = atof(valbuf);
                            memcpy(lptr, &tmp, sizeof(double));
#else
                            float tmp = atof(valbuf);
                            memcpy(lptr, &tmp, sizeof(float));
#endif
                        }
                        break;
                        case t_string:
                            if (parent != NULL && parent->element_type != t_structobject && offset > 0)
                            {
                                return JSON_ERR_NOPARSTR;
                            }
                            else
                            {
                                size_t vl = strlen(valbuf), cl = cursor->len - 1;
                                memset(lptr, '\0', cl);
                                memcpy(lptr, valbuf, vl < cl ? vl : cl);
                            }
                            break;
                        case t_boolean:
                        {
                            bool tmp = (strcmp(valbuf, "true") == 0);
                            memcpy(lptr, &tmp, sizeof(bool));
                        }
                        break;
                        case t_character:
                            if (strlen(valbuf) > 1)
                            {
                                /* don't update end here, leave at value start */
                                return JSON_ERR_STRLONG;
                            }
                            else
                            {
                                lptr[0] = valbuf[0];
                            }
                            break;
                        case t_ignore: /* silences a compiler warning */
                        case t_object: /* silences a compiler warning */
                        case t_structobject:
                        case t_array:
                            break;
                        case t_check:
                            if (strcmp(cursor->dflt.check, valbuf) != 0)
                            {
                                debug_trace((1, "Required attribute value %s"
                                                    " not present.\n",
                                                cursor->dflt.check));
                                /* don't update end here, leave at start of attribute */
                                return JSON_ERR_CHECKFAIL;
                            }
                            break;
                    }
                }
            /* INTENTONAL FALLTHROUGH */

            case post_element:
                if (isspace((unsigned char)*char_ptr))
                {
                    continue;
                }
                else if (*char_ptr == ',')
                {
                    state = await_attr;
                }
                else if (*char_ptr == '}')
                {
                    ++char_ptr;
                    goto good_parse;
                }
                else
                {
                    debug_trace((1,"Garbage while expecting comma or }\n"));
                    if (end != NULL)
                    {
                        *end = char_ptr;
                    }
                    return JSON_ERR_BADTRAIL;
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
    if (end != NULL)
    {
        *end = char_ptr;
    }
    debug_trace((1, "JSON parse ends.\n"));
    return 0;
}

int32_t json_read_array(const char *char_ptr, const struct json_array_t *arr,
                    const char **end)
{
    int32_t substatus, offset, arrcount;
    char *tp;

    if (end != NULL)
    {
        *end = NULL; /* give it a well-defined value on parse failure */
    }

    debug_trace((1, "Entered json_read_array()\n"));

    while (isspace((unsigned char)*char_ptr))
    {
        char_ptr++;
    }
    if (*char_ptr != '[')
    {
        debug_trace((1, "Didn't find expected array start\n"));
        return JSON_ERR_ARRAYSTART;
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
    if (*char_ptr == ']')
    {
        goto breakout;
    }

    for (offset = 0; offset < arr->maxlen; offset++)
    {
        char *ep = NULL;
        debug_trace((1, "Looking at %s\n", char_ptr));
        switch (arr->element_type)
        {
            case t_string:
                if (isspace((unsigned char)*char_ptr))
                {
                    char_ptr++;
                }
                if (*char_ptr != '"')
                {
                    return JSON_ERR_BADSTRING;
                }
                else
                {
                    ++char_ptr;
                }
                arr->arr.strings.ptrs[offset] = tp;
                for (; tp - arr->arr.strings.store < arr->arr.strings.storelen;
                    tp++)
                    if (*char_ptr == '"')
                    {
                        ++char_ptr;
                        *tp++ = '\0';
                        goto stringend;
                    }
                    else if (*char_ptr == '\0')
                    {
                        debug_trace((1,
                                        "Bad string syntax in string list.\n"));
                        return JSON_ERR_BADSTRING;
                    }
                    else
                    {
                        *tp = *char_ptr++;
                    }
                debug_trace((1, "Bad string syntax in string list.\n"));
                return JSON_ERR_BADSTRING;
            stringend:
                break;
            case t_object:
            case t_structobject:
                substatus =
                    json_internal_read_object(  char_ptr, 
                                                arr->arr.objects.subtype, 
                                                arr,
                                                offset, 
                                                &char_ptr, NULL);
                if (substatus != 0)
                {
                    if (end != NULL)
                    {
                        end = &char_ptr;
                    }
                    return substatus;
                }
                break;
            case t_integer:
                arr->arr.integers.store[offset] = (int32_t)strtol(char_ptr, &ep, 0);
                if (ep == char_ptr)
                {
                    return JSON_ERR_BADNUM;
                }
                else
                {
                    char_ptr = ep;
                }
                break;
            case t_uinteger:
                arr->arr.uintegers.store[offset] = (unsigned)strtoul(char_ptr, &ep,0);
                if (ep == char_ptr)
                {
                    return JSON_ERR_BADNUM;
                }
                else
                {
                    char_ptr = ep;
                }
                break;
            case t_short:
                arr->arr.shorts.store[offset] = (int16_t)strtol(char_ptr, &ep, 0);
                if (ep == char_ptr)
                {
                    return JSON_ERR_BADNUM;
                }
                else
                {
                    char_ptr = ep;
                }
                break;
            case t_ushort:
                arr->arr.ushorts.store[offset] = (uint16_t)strtol(char_ptr, &ep, 0);
                if (ep == char_ptr)
                {
                    return JSON_ERR_BADNUM;
                }
                else
                {
                    char_ptr = ep;
                }
                break;
            case t_time:
    #ifdef TIME_ENABLE
                if (*char_ptr != '"')
                {
                    return JSON_ERR_BADSTRING;
                }
                else
                {
                    ++char_ptr;
                }
                arr->arr.reals.store[offset] = iso8601_to_unix((char *)char_ptr);
                if (arr->arr.reals.store[offset] >= HUGE_VAL)
                {
                    return JSON_ERR_BADNUM;
                }
                while (*char_ptr && *char_ptr != '"')
                {
                    char_ptr++;
                }
                if (*char_ptr != '"')
                {
                    return JSON_ERR_BADSTRING;
                }
                else
                {
                    ++char_ptr;
                }
                break;
    #endif /* TIME_ENABLE */
            case t_real:
#if defined(DOUBLE_DECIMAL_PRECISION)
                arr->arr.reals.store[offset] = strtod(char_ptr, &ep);
#else
                arr->arr.reals.store[offset] = (float)strtod(char_ptr, &ep);
#endif
                if (ep == char_ptr)
                {
                    return JSON_ERR_BADNUM;
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
                    char_ptr += 4;
                }
                else if (str_starts_with(char_ptr, "false"))
                {
                    arr->arr.booleans.store[offset] = false;
                    char_ptr += 5;
                }
                break;
            case t_character:
            case t_array:
            case t_check:
            case t_ignore:
                debug_trace((1, "Invalid array subtype.\n"));
                return JSON_ERR_SUBTYPE;
        }
        arrcount++;
        if (isspace((unsigned char)*char_ptr))
        {
            char_ptr++;
        }
        if (*char_ptr == ']')
        {
            debug_trace((1, "End of array found.\n"));
            goto breakout;
        }
        else if (*char_ptr == ',')
            char_ptr++;
        else
        {
            debug_trace((1, "Bad trailing syntax on array.\n"));
            return JSON_ERR_BADSUBTRAIL;
        }
    }
    debug_trace((1, "Too many elements in array.\n"));
    if (end != NULL)
    {
        *end = char_ptr;
    }
    return JSON_ERR_SUBTOOLONG;
breakout:
    if (arr->count != NULL)
    {
        *(arr->count) = arrcount;
    }
    if (end != NULL)
    {
        *end = char_ptr;
    }
    debug_trace((1, "leaving json_read_array() with %d elements\n",
                      arrcount));
    return 0;
}

int32_t json_read_object(const char *char_ptr, const struct json_attr_t *attrs,
                     const char **end, int32_t *matched_key_idx)
{
    int32_t st;
    debug_trace((1, "json_read_object() sees '%s'\n", char_ptr));
    st = json_internal_read_object(char_ptr, attrs, NULL, 0, end, matched_key_idx);
    return st;
}

const char *json_error_string(int32_t err)
{
    const char *errors[] = {
        "unknown error while parsing JSON",
        "non-whitespace when expecting object start",
        "non-whitespace when expecting attribute start",
        "unknown attribute name",
        "attribute name too long",
        "saw [ when not expecting array",
        "array element specified, but no [",
        "string value too long",
        "token value too long",
        "garbage while expecting comma or } or ]",
        "didn't find expected array start",
        "error while parsing object array",
        "too many array elements",
        "garbage while expecting array comma",
        "unsupported array element type",
        "error while string parsing",
        "check attribute not matched",
        "can't support strings in parallel arrays",
        "invalid enumerated value",
        "saw quoted value when expecting nonstring",
        "didn't see quoted value when expecting string",
        "other data conversion error",
        "unexpected null value or attribute pointer",
        "object element specified, but no {",
    };

    if (err <= 0 || err >= (int32_t)(sizeof(errors) / sizeof(errors[0])))
    {
        return errors[0];
    }
    else
    {
        return errors[err];
    }
}

/* end */
