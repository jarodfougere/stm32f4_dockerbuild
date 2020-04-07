#ifndef RIMOT_OUTPOST_CONFIG
#define RIMOT_OUTPOST_CONFIG
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */


/* You may notice that in the readme, outpost ID must be 6 chars */
/* So there is a 7th char for the nul byte. */
/* Problem is that if I were to store this in the eeprom used on the 
embedded sensor card, I'd need to pack the structure due to issues with 
word alignment differences between the EEPROM and the MCU. 
*/
#define UNASSIGNED_OUTPOST_ID "00000000" /* 8 CHARACTERS for word alignment */

/* States that the outpost can be in */
typedef enum
{
    OUTPOST_MODE_lowpower,
    OUTPOST_MODE_active,
    OUTPOST_MODE_sleep,
}   OUTPOST_MODE_t;


/* This structure contains configuration parameters relating to the outpost */
struct outpost_config
{
    char outpostID[sizeof(UNASSIGNED_OUTPOST_ID)];
};

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_OUTPOST_CONFIG */