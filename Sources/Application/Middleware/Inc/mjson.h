
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>
#include <inttypes.h>
#ifdef TIME_ENABLE
#include <time.h>
#endif /* TIME_ENABLE */

#define UNMATCHED_TOPLEVEL_KEY_IDX -1

#define PROCESSOR_INT int32_t
#define PROCESSOR_UINT uint32_t

typedef enum 
{
    t_integer,
    t_uinteger, 
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
	t_short, 
    t_ushort
}   json_type;

struct json_enum_t 
{
    char    *name;
    int32_t	value;
};

struct json_array_t 
{
    json_type element_type;
    union {
        struct 
        {
            const struct json_attr_t *subtype;
            char *base;
            size_t stride;
        } objects;
        struct 
        {
            char **ptrs;
            char *store;
            int32_t storelen;
        } strings;
        struct 
        {
            int32_t *store;
        } integers;
        struct 
        {
            uint32_t *store;
        } uintegers;
        struct 
        {
            short *store;
        } shorts;
        struct 
        {
            int16_t *store;
        } ushorts;
        struct 
        {   
#if defined(DOUBLE_DECIMAL_PRECISION)
            double *store;
#else
            float *store;
#endif
        } reals;
        struct 
        {
            bool *store;
        } booleans;
    } arr;
    int32_t *count;
    int32_t maxlen;
};

struct json_attr_t 
{
    char *attribute;
    json_type type;
    union 
    {
        int32_t *integer;
        uint32_t *uinteger;
        int16_t *shortint;
        uint16_t *ushortint;
#if defined (DOUBLE_DECIMAL_PRECISION)
        double *real;
#else
        float* real;
#endif
        char *string;
        bool *boolean;
        char *character;
        const struct json_attr_t *attrs;
        const struct json_array_t array;
        size_t offset;
    } addr;
    union 
    {
        int32_t integer;
        uint32_t uinteger;
        int16_t shortint;
        uint16_t ushortint;
#if defined (DOUBLE_DECIMAL_PRECISION)
        double real;
#else
        float real;
#endif
        bool boolean;
        char character;
        char *check;
    } dflt;
    size_t len;
    const struct json_enum_t *map;
    bool nodefault;
};

#define JSON_ATTR_MAX	31	/* max chars in JSON attribute name */
#define JSON_VAL_MAX	512	/* max chars in JSON value part */

#ifdef __cplusplus
extern "C" {
#endif
int32_t json_read_object(   const char *cp, 
                            const struct json_attr_t *attrs,
                            const char **end, 
                            int32_t *matched_key_idx);

int32_t json_read_array(    const char *, 
                            const struct json_array_t *,
                            const char **);
                        
const char *json_error_string(int32_t);

#ifdef TIME_ENABLE
extern time_t timegm(struct tm *tm);
#endif /* TIME_ENABLE */
    
void json_enable_debug(int32_t, FILE *);
#ifdef __cplusplus
}
#endif

#define JSON_ERR_OBSTART	1	/* non-WS when expecting object start */
#define JSON_ERR_ATTRSTART	2	/* non-WS when expecting attrib start */
#define JSON_ERR_BADATTR	3	/* unknown attribute name */
#define JSON_ERR_ATTRLEN	4	/* attribute name too long */
#define JSON_ERR_NOARRAY	5	/* saw [ when not expecting array */
#define JSON_ERR_NOBRAK 	6	/* array element specified, but no [ */
#define JSON_ERR_STRLONG	7	/* string value too long */
#define JSON_ERR_TOKLONG	8	/* token value too long */
#define JSON_ERR_BADTRAIL	9	/* garbage while expecting comma or } or ] */
#define JSON_ERR_ARRAYSTART	10	/* didn't find expected array start */
#define JSON_ERR_OBJARR 	11	/* error while parsing object array */
#define JSON_ERR_SUBTOOLONG	12	/* too many array elements */
#define JSON_ERR_BADSUBTRAIL	13	/* garbage while expecting array comma */
#define JSON_ERR_SUBTYPE	14	/* unsupported array element type */
#define JSON_ERR_BADSTRING	15	/* error while string parsing */
#define JSON_ERR_CHECKFAIL	16	/* check attribute not matched */
#define JSON_ERR_NOPARSTR	17	/* can't support strings in parallel arrays */
#define JSON_ERR_BADENUM	18	/* invalid enumerated value */
#define JSON_ERR_QNONSTRING	19	/* saw quoted value when expecting nonstring */
#define JSON_ERR_NONQSTRING	19	/* didn't see quoted value when expecting string */
#define JSON_ERR_MISC		20	/* other data conversion error */
#define JSON_ERR_BADNUM		21	/* error while parsing a numerical argument */
#define JSON_ERR_NULLPTR	22	/* unexpected null value or attribute pointer */
#define JSON_ERR_NOCURLY	23	/* object element specified, but no { */

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
	.addr.array.maxlen = (int32_t)(sizeof(a)/sizeof(a[0]))

/* json.h ends here */