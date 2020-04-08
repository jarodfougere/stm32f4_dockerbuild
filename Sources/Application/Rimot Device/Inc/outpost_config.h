#ifndef RIMOT_OUTPOST_CONFIG
#define RIMOT_OUTPOST_CONFIG
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */



/* States that the outpost can be in */
typedef enum
{   
    OUTPOST_MODE_unknown,   
    OUTPOST_MODE_lowpower,
    OUTPOST_MODE_active,
    OUTPOST_MODE_sleep,
}   OUTPOST_MODE_t;


typedef struct outpost_config_structure outpost_config;

outpost_config* outpost_configInit(void);
void outpostCfgSetMode(outpost_config *cfg, OUTPOST_MODE_t mode);
OUTPOST_MODE_t outpostCfgGetMode(const outpost_config *cfg);
const char * outpostCfgGetIdString(const outpost_config* cfg);
void outpostSetIdString(const outpost_config *cfg, const char *idStr);


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_OUTPOST_CONFIG */