#ifndef _HGIC_UMAC_H_
#define _HGIC_UMAC_H_
#include "lib/lmac/lmac.h"
#include "lib/lmac/hgic.h"
#include "lib/umac/umac_config.h"
#ifdef __cplusplus
extern "C" {
#endif

enum umac_ops_type {
    UMAC_OPS_HOST,
    UMAC_OPS_LOCAL,
};

enum umac_ops_local_type {
    UMAC_OPS_LOCAL_TYPE_LWIP,
    UMAC_OPS_LOCAL_TYPE_GMAC,
};

struct umac_ops {
    int   type;
    void *priv;
    int (*recv_data)(struct umac_ops *ops, unsigned char *data, unsigned int len);
};

int umac_init(void);
void umac_xmit(struct sk_buff *skb, int len);
int umac_rx(struct sk_buff *skb);
void umac_tx(struct sk_buff *skb);
void umac_event_notify(struct net_device *dev, int event_id, char *args, int len);
void umac_dump_hex(uint8 *buf, int len);
void umac_set_ops(struct umac_ops *ops);
int umac_wdev_init(struct lmac_ops *ops, int dev_id);
void umac_status_print(void);
struct umac_ops *umac_ops_host_init(int bus_type);
struct umac_ops *umac_ops_local_init(int type);
void umac_netdev_xmit(struct sk_buff *skb);
void umac_netdev_recieve(struct sk_buff *skb);
#ifdef __cplusplus
}
#endif

#endif

