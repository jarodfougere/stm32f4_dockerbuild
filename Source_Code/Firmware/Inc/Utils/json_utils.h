#ifndef __JSON_UTILS_H__
#define __JSON_UTILS_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

#include <stdint.h>
#include <stdbool.h>
#include "jsmn.h"


/**
 * @brief get the token length of a jsmntok_t;
 *
 * @param tok
 * @return uint32_t the length of the token
 */
uint32_t jutil_toklen(const jsmntok_t *tok);


/**
 * @brief Compare a token with a string
 *
 * @param str char array
 * @param json json string
 * @param tok jsmntok_t instance of a json token parsed from the json string
 * @return true str == tok
 * @return false str != tok
 */
bool jutil_tokcmp(const char *restrict str, const char *json,
                  const jsmntok_t *tok);


/**
 * @brief Check if a jsmntok array constitutes a valid json structure
 *
 * @param tokens token array
 * @param tcnt number of tokens parsed from some arbitrary json string
 * @return true valid
 * @return false invalid
 */
bool isValidJson(const jsmntok_t *tokens, uint_least8_t tcnt);


#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __JSON_UTILS_H__ */
