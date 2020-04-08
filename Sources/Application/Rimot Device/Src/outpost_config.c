
#include <stdlib.h>
#include <string.h>
#include "outpost_config.h"
#include "rimot_LL_debug.h"


/* You may notice that in the readme, outpost ID must be 6 chars */
/* So there is a 7th char for the nul byte. */
/* Problem is that if I were to store this in the eeprom used on the 
embedded sensor card, I'd need to pack the structure due to issues with 
word alignment differences between the EEPROM and the MCU. 
*/
#define UNASSIGNED_OUTPOST_ID "00000000" /* 8 CHARACTERS for word alignment */

/* This structure contains configuration parameters relating to the outpost */
struct outpost_config_structure
{
    char outpostID[sizeof(UNASSIGNED_OUTPOST_ID)];
    char nulJustInCase;
    /* This is just so string.h operators don't clobber mode in case of bug */
    OUTPOST_MODE_t mode;
};


outpost_config* outpost_configInit(void)
{
    outpost_config *cfg = (outpost_config*)malloc(sizeof(outpost_config));
    LL_ASSERT(NULL != cfg);

    cfg->mode = OUTPOST_MODE_unknown;
    memset((void*)&(cfg->nulJustInCase), '\0', sizeof(cfg->nulJustInCase));
    strncpy(cfg->outpostID, UNASSIGNED_OUTPOST_ID, sizeof(cfg->outpostID));
    return cfg;
}


void outpostCfgSetMode(outpost_config *cfg, OUTPOST_MODE_t mode)
{
    LL_ASSERT(NULL != cfg);
    cfg->mode = mode;
}

OUTPOST_MODE_t outpostCfgGetMode(const outpost_config *cfg)
{
    LL_ASSERT(NULL != cfg);
    return (OUTPOST_MODE_t)cfg->mode;
}


const char * outpostCfgGetIdString(const outpost_config* cfg)
{
    LL_ASSERT(NULL != cfg);
    return (char*)cfg->outpostID;
}


void outpostSetIdString(const outpost_config *cfg, const char *idStr)
{
    LL_ASSERT(NULL != cfg);
    LL_ASSERT(NULL != idStr);
    strncpy((char*)cfg->outpostID, idStr, sizeof(cfg->outpostID));
}




