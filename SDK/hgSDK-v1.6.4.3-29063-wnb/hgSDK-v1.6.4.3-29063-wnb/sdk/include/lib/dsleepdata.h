#ifndef _HGIC_DSLEEP_DATA_H_
#define _HGIC_DSLEEP_DATA_H_

enum system_sleepdata_id {
    SYSTEM_SLEEPDATA_ID_LMAC,
    SYSTEM_SLEEPDATA_ID_UMAC,
    SYSTEM_SLEEPDATA_ID_PSALIVE,
    SYSTEM_SLEEPDATA_ID_USER0,
    SYSTEM_SLEEPDATA_ID_USER1,
    SYSTEM_SLEEPDATA_ID_MAX,
};

extern void *system_sleepdata_request(uint8 id, uint32 size);
extern void system_sleepdata_reset(void);
extern uint32 system_sleepdata_freesize(void);
#endif
