#ifndef __SKB_LIST_H__
#define __SKB_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

struct skb_list {
    struct sk_buff *next, *prev;
    uint32 count;
};

extern int32 skb_list_init(struct skb_list *list);
extern int32 skb_list_destroy(struct skb_list *list);
extern int32 skb_list_queue(struct skb_list *list, struct sk_buff *skb);
extern uint32 skb_list_count(struct skb_list *list);
extern struct sk_buff *skb_list_dequeue(struct skb_list *list);
extern struct sk_buff *skb_list_first(struct skb_list *list);
extern struct sk_buff *skb_list_last(struct skb_list *list);
extern int32 skb_list_unlink(struct sk_buff *skb, struct skb_list *list);
extern int32 skb_list_queue_before(struct skb_list *list,
            struct sk_buff *next,
            struct sk_buff *newsk);
extern int32 skb_list_queue_after(struct skb_list *list,
                struct sk_buff *prev,
                struct sk_buff *newsk);

#ifdef __cplusplus
}
#endif

#endif

