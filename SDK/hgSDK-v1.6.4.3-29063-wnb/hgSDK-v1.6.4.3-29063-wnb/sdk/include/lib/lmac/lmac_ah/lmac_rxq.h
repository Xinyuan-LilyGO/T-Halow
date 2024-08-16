#ifndef _LMAC_RXQ_H_
#define _LMAC_RXQ_H_
#include <typesdef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct lmac_frm_info {
    uint8  *addr;
    uint32  len;
};

struct lmac_rxq {
    struct os_semaphore sem;
    struct lmac_frm_info *rxq;
    uint16  wpos;
    uint16  rpos;
    uint32  size;
};

int32 lmac_rxq_init(struct lmac_rxq *rxq, uint8 *qbuf, int32 qsize);

int32 lmac_rxq_put(struct lmac_rxq *rxq, struct lmac_frm_info *frm_info, int32 count);

int32 lmac_rxq_get(struct lmac_rxq *rxq, struct lmac_frm_info *frm_info, int32 count, int32 tmo);

int32 lmac_rxq_free(struct lmac_rxq *rxq);

int32 lmac_rxq_count(struct lmac_rxq *rxq);

#ifdef __cplusplus
}
#endif

#endif

