#ifndef _HUGE_IC_WPAS_H_
#define _HUGE_IC_WPAS_H_
int wpas_init(void);
int wpas_start(char *ifname);
int wpas_stop(char *ifname);
void _wpas_start(void *eloop_ctx, void *timeout_ctx);
void _wpas_stop(void *eloop_ctx, void *timeout_ctx);
struct sk_buff *wpas_proc_ctrl_msg(void *wpas, struct sk_buff *skb, int *err);
#endif
