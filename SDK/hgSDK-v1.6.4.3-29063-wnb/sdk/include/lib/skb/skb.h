#ifndef _HGIC_SDK_H_
#define _HGIC_SDK_H_

#ifdef CONFIG_UMAC
#include <linux/skbuff.h>
#else
#include <osal/atomic.h>
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

struct sk_buff {
    struct sk_buff *next, *prev, *clone;
    struct list_head used;
    uint8  *tail;
    uint8  *data;
    uint8  *head;
    uint8  *end;
    /* clear below flags when skb free */
    uint16  len;
    uint8   acked:1, cloned:1, lmaced:1, src_in:1;
    uint8   aid;
    uint32  lifetime;
    void   *txinfo;
    void   *sta;
    void   *lastq;
    /////////////////////////////////////
    atomic_t users;
    void (*free)(void *free_priv, struct sk_buff *skb);
    void *free_priv;
};

#define SKB_DEBUG
#ifdef SKB_DEBUG
#define skb_put(skb, l) ({ \
    uint8 *tmp = (skb)->tail;\
    ASSERT((skb)->tail + (l) <= (skb)->end); \
    (skb)->tail += (l);\
    (skb)->len  += (l);\
    tmp;\
    })
#define skb_push(skb, l) ({ \
        ASSERT((skb)->data - (l) >= (skb)->head);\
        (skb)->data -= (l);\
        (skb)->len  += (l);\
        (skb)->data;\
    })
#define skb_pull(skb, l) ({ \
        ASSERT((skb)->len >= (l) && (skb)->data + (l) < (skb)->end);\
        (skb)->len -= (l);\
        (skb)->data += (l);\
        (skb)->data;\
    })
#define skb_reserve(skb, l) ({ \
        ASSERT((skb)->tail + (l) < (skb)->end);\
        (skb)->data += (l);\
        (skb)->tail += (l);\
    })
#else
    static inline uint8 *skb_put(struct sk_buff *skb, uint32 len)
    {
        uint8 *tmp = skb->tail;
        ASSERT(skb->tail + len <= skb->end);
        skb->tail += len;
        skb->len  += len;
        return tmp;
    }

    static inline uint8 *skb_push(struct sk_buff *skb, uint32 len)
    {
        ASSERT(skb->data - len >= skb->head);
        skb->data -= len;
        skb->len  += len;
        return skb->data;
    }

    static inline uint8 *skb_pull(struct sk_buff *skb, uint32 len)
    {
        ASSERT(skb->len >= len && skb->data + len < skb->end);
        skb->len -= len;
        return skb->data += len;
    }

    static inline void skb_reserve(struct sk_buff *skb, int len)
    {
        ASSERT(skb->tail + len < skb->end);
        skb->data += len;
        skb->tail += len;
    }
#endif

    static inline int skb_tailroom(const struct sk_buff *skb)
    {
        return (skb->end - skb->tail);
    }

    static inline unsigned int skb_headroom(const struct sk_buff *skb)
    {
        return skb->data - skb->head;
    }

    static inline int skb_dataroom(const struct sk_buff *skb)
    {
        return (skb->end - skb->data);
    }
    
    static inline struct sk_buff *skb_get(struct sk_buff *skb)
    {
        atomic_inc(&skb->users);
        return skb;
    }

#define dev_alloc_skb(s)          alloc_skb(s)
#define dev_kfree_skb(a)          kfree_skb(a)
#define dev_kfree_skb_any(a)      kfree_skb(a)
    extern struct sk_buff *alloc_skb(unsigned int size);
    extern struct sk_buff *alloc_tx_skb(uint32 size);
    extern void kfree_skb(struct sk_buff *skb);
    extern int skb_free_count(void);
    extern struct sk_buff *_alloc_skb(unsigned int size);
    extern struct sk_buff *_alloc_tx_skb(uint32 size);
    extern void _kfree_skb(struct sk_buff *skb);
    extern int _skb_free_count(void)    ;
    extern struct sk_buff *skb_copy(const struct sk_buff *skb, int flags);
    extern struct sk_buff *skb_clone(struct sk_buff *skb, int priority);
    extern int32 skb_dump_used(uint32 *buf, int32 size);
    extern int32 atcmd_skbdump_hdl(const char *cmd, uint8 *data, int32 len);

#ifdef SKB_POOL_ENABLE
    extern int skb_rxpool_init(uint8 *buff, uint32 size);
    extern int skb_txpool_init(uint8 *buff, uint32 size);
    struct sk_buff *skb_rxpool_alloc(uint32 size);
    struct sk_buff *skb_txpool_alloc(uint32 size);
    int32 skbpool_free_count(void);
#endif

#ifdef __cplusplus
}
#endif
#endif

#endif

