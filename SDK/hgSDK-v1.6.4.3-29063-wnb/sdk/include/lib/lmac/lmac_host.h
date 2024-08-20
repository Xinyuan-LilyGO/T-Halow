#ifndef _LMAC_HOST_H_
#define _LMAC_HOST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hgic.h"

#define HGICS_DACK

struct lmac_host {
    uint8  stop: 1, config:1;
    uint8  pad;
    uint16 cookie;

    struct mac_bus  *bus;
    struct lmac_ops *ops;

    struct skb_list     cmd_list;
    struct os_semaphore cmd_sema;
    struct os_task      cmd_task;

#ifdef HGICS_DACK
    struct skb_list     tx_status_list;
    struct os_semaphore tx_status_sema;
    struct os_task      tx_status_task;
#endif
    uint32 last_cookie;
    struct os_timer cfgtimer;
};

int32 lmac_host_init(int32 if_type, struct lmac_ops *ops);

#ifdef __cplusplus
}
#endif

#endif

