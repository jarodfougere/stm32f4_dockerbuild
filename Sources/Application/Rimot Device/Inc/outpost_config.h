#ifndef RIMOT_OUTPOST_CONFIG
#define RIMOT_OUTPOST_CONFIG

#define UNASSIGNED_OUTPOST_ID "00000000" /* 8 CHARACTERS */


struct outpost_config
{
    char outpostID[sizeof(UNASSIGNED_OUTPOST_ID)];
};

#define OUTPOST_CFG_DFLT_INITIALIZER {          \
    .outpostID = UNASSIGNED_OUTPOST_ID,         \
}                                               \

#endif