#ifndef RIMOT_JSON_PARSER
#define RIMOT_JSON_PARSER
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdio.h>
#include <stdbool.h>  
#include <ctype.h>
#include <stdint.h>
#include <inttypes.h> /* safer string to int conversions than stroul */

#ifdef MJSON_TIME_ENABLE
#if    defined(MCU_APP)
#include <time.h>
#else
#error MJSON HAS TIMESTAMPS ENABLED FOR A STANDALONE APPLICATION BUT    \
DOESN'T HAVE A HEADER PROVIDED TO HANDLE TIMESTAMPS. A TIMING           \
MECHANISM SUCH AS RTC A SYSTICK CALL MUST BE PROVIDED.
#endif /* MCU_APP */
#endif /* TIME_ENABLE */

/* -1 IS NOT AN ARRAY INDEX SO THIS IS A SAFE DEFAULT VALUE */
#define UNMATCHED_PARENT_JSON_KEY_IDX -1

/*
 * The type of JSON field for an expected token
 *  
 * ------------------------------------------------------------
 * t_integer : parse the attribute value as a signed integer
 * t_uinteger : parse the attribute value as an unsigned integer
 * t_short : parse the attribute value as a signed short
 * t_ushort : parse the attribute value as an unsigned short
 * t_real : parse the attribute value as a decimal real number 
 * t_string : parse the attribute value as a string
 * t_boolean : parse the attribute value as an unquoted JSON boolean
 * t_character : parse the attribute value as a single quoted character
 * t_time : parse the attribute value as ISO standard time formatting string
 * t_object : parse the attribute value as a child object
 * t_structobject : populate a struct with attributes parsed from the child obj
 * t_array  : parse the attribute value as an array
 * t_check  : confirm the attribute matches a default token value.
 * t_ignore : do not parse the attribute's value
 */
enum json_type
{
    t_integer,
    t_uinteger, 
    t_short, 
    t_ushort,
    t_real,         
	t_string, 
    t_boolean, 
    t_character,
	t_time,         
	t_object,       
    t_structobject, 
    t_array,        
	t_check,        
    t_ignore,       
};


/* 
 * Errors that can happen during the state machine parsing
 * of a json structure.
 * 
 *      Type                        Description
 * ---------------------------------------------------------
 * JERR_OBSTART:	 	 non-WS when expecting object start         
 * JERR_ATTRSTART:	 	 non-WS when expecting attrib start         
 * JERR_BADATTR:	 	 unknown attribute name                     
 * JERR_ATTRLEN:	 	 attribute name too long                    
 * JERR_NOARRAY:	 	 saw [ when not expecting array             
 * JERR_NOBRAK: 	 	 array element specified: but no [          
 * JERR_CURLNOBJ:        saw { when not expecting object }          
 * JERR_STRLONG:	 	 string value too long                      
 * JERR_TOKLONG:	 	 token value too long                       
 * JERR_BADTRAIL:	 	 garbage while expecting comma or } or ]    
 * JERR_ARRSTART:	     didn't find expected array start           
 * JERR_OBJARR: 	 	 error while parsing object array           
 * JERR_SUBTOOLONG:	    too many array elements                    
 * JERR_BADSUBTRAIL: 	 garbage while expecting array comma        
 * JERR_SUBTYPE:	     unsupported array element type             
 * JERR_BADSTRING:	 	 error while string parsing                 
 * JERR_CHECKFAIL:	 	 check attribute not matched                
 * JERR_NOPARSTR:	 	 can't support strings in parallel arrays   
 * JERR_BADENUM:	 	 invalid enumerated value                   
 * JERR_QNONSTRING:	     saw quoted value when expecting nonstring  
 * JERR_NONQSTRING:	     no quoted value when expecting string      
 * JERR_MISC:		 	 other data conversion error                
 * JERR_BADNUM:		     error while parsing a numerical argument   
 * JERR_NULLPTR:	 	 unexpected null value or attribute pointer 
 * JERR_NOCURLY:	 	 object element specified: but no {         
 * JERR_BADARRTRAIL:     bad trailing syntax in array  
 */             
enum JERR
{
    JERR_OBSTART,	 	/* non-WS when expecting object start         */
    JERR_ATTRSTART,	 	/* non-WS when expecting attrib start         */
    JERR_BADATTR,	 	/* unknown attribute name                     */
    JERR_ATTRLEN,	 	/* attribute name too long                    */
    JERR_NOARRAY,	 	/* saw [ when not expecting array             */
    JERR_NOBRAK, 	 	/* array element specified, but no [          */
    JERR_CURLNOBJ,     /* saw { when not expecting object }          */
    JERR_STRLONG,	 	/* string value too long                      */
    JERR_TOKLONG,	 	/* token value too long                       */
    JERR_BADTRAIL,	 	/* garbage while expecting comma or } or ]    */
    JERR_ARRSTART,	    /* didn't find expected array start           */
    JERR_OBJARR, 	 	/* error while parsing object array           */
    JERR_SUBTOOLONG,	/* too many array elements                    */
    JERR_BADSUBTRAIL, 	/* garbage while expecting array comma        */
    JERR_SUBTYPE,	    /* unsupported array element type             */
    JERR_BADSTRING,	 	/* error while string parsing                 */
    JERR_CHECKFAIL,	 	/* check attribute not matched                */
    JERR_NOPARSTR,	 	/* can't support strings in parallel arrays   */
    JERR_BADENUM,	 	/* invalid enumerated value                   */
    JERR_QNONSTRING,	/* saw quoted value when expecting nonstring  */
    JERR_NONQSTRING,	/* no quoted value when expecting string      */
    JERR_MISC,		 	/* other data conversion error                */
    JERR_BADNUM,		/* error while parsing a numerical argument   */
    JERR_NULLPTR,	 	/* unexpected null value or attribute pointer */
    JERR_NOCURLY,	 	/* object element specified, but no {         */
    JERR_BADARRTRAIL,   /* bad trailing syntax in array               */

    /* 
     * all other errors that I havent made a code
     * for are grouped under this category. 
     */
    JERR_UNKNOWN,     
};

/* 
 * String - value map used in case of string <-> value aliases
 *
 * This helps to allow JSON format changes without breaking backwards
 * compability with existing deployed applications 
 */
struct json_enum 
{
    char    *name;
    int	    value;
};

#if defined(DOUBLE_DECIMAL_PRECISION)
typedef double realval;
#else
typedef float realval;
#endif /* DOUBLE_DECIMAL_PRECISION */

struct json_array 
{
    enum json_type element_type;

    union 
    {
        struct 
        {
            const struct json_attr *subtype;
            char *base;
            size_t stride;
        }   objects;

        struct 
        {
            char **ptrs;
            char *store;
            int storelen;
        }   strings;

        struct 
        {
            int *store;
        }   integers;

        struct 
        {
            unsigned *store;
        }   uintegers;

        struct 
        {
            short *store;
        }   shorts;

        struct 
        {
            short *store;
        }   ushorts;

        struct 
        {   
            realval *store;
        }   reals;

        struct 
        {
            bool *store;
        }   booleans;

    }   arr;
    int *count;
    int maxlen;
};

struct json_attr 
{   
    /* pointer to key string */
    char *attribute; 

    /* the type of key */
    enum json_type type;

    /* address overlay for parsed value */
    union 
    {
        int                    *integer;
        unsigned               *uinteger;
        short                  *shortint;
        unsigned short         *ushortint;
        realval                *real;
        char                   *string;
        bool                   *boolean;
        char                   *character;
        const struct json_attr *attrs;
        const struct json_array array;
        size_t                  offset;
    }   addr;

    /* default values in case of missing keys */
    union 
    {
        int            integer;
        unsigned       uinteger;
        short          shortint;
        unsigned short ushortint;
        realval        real;
        bool           boolean;
        char           character;
        char          *check;    /* default existence check string */
    }   dflt;

    size_t len;
    const struct json_enum *map;
    bool nodefault;
};

#define JSON_KEY_MAXLEN	31	/* max chars in JSON key "string" */
#define JSON_VAL_MAXLEN	512	/* max chars in JSON value "string" */

int json_read_object( const char *cp, 
                      const struct json_attr *attrs,
                      const char **end, 
                      int *matched_key_idx);

int json_read_array( const char *, 
                     const struct json_array *,
                     const char **);
                        
const char *json_error_string(int code);

#ifdef MJSON_TIME_ENABLE
extern time_t timegm(struct tm *tm);
#endif /* MSJON_TIME_ENABLE */
    
void json_enable_debug(int lvl);

/*
 * Use the following macros to declare template initializers for structobject
 * arrays.  Writing the equivalents out by hand is error-prone.
 *
 * STRUCTOBJECT takes a structure name s, and a fieldname f in s.
 *
 * STRUCTARRAY takes the name of a structure array, a pointer to a an
 * initializer defining the subobject type, and the address of an integer to
 * store the length in.
 */
#define STRUCTOBJECT(s, f)	.addr.offset = offsetof(s, f)
#define STRUCTARRAY(a, e, n)                        \
	.addr.array.element_type = t_structobject,      \
	.addr.array.arr.objects.subtype = e,            \
	.addr.array.arr.objects.base = (char*)a,        \
	.addr.array.arr.objects.stride = sizeof(a[0]),  \
	.addr.array.count = n,                          \
	.addr.array.maxlen = (int)(sizeof(a)/sizeof(a[0]))


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_JSON_PARSER */

