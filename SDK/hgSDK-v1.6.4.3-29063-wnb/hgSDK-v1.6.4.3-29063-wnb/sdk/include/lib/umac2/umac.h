#ifndef _HGIC_UMAC_H_
#define _HGIC_UMAC_H_
#include "lib/lmac/lmac.h"
#include "lib/lmac/hgic.h"
#include "umac_config.h"
#ifdef __cplusplus
extern "C" {
#endif

int umac_init(void);
int umac_config_read(const char *name, char *buff, int size);
int umac_config_write(const char *name, char *buff, int size);

int wpas_init(void);
int wpas_start(char *ifname);
int wpas_stop(char *ifname);
int wpas_cli(char *ifname, char *cmd, char *reply_buff, int reply_len);

int hapd_init(void);
int hapd_start(char *ifname);
int hapd_stop(char *ifname);
int hapd_cli(char *ifname, char *cmd, char *reply_buff, int reply_len);

#ifdef __cplusplus
}
#endif

#endif

