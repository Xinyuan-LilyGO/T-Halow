#ifndef __OS_IRQ_H_
#define __OS_IRQ_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*irq_handle)(void *data);
struct sys_hwirq {
    void *data;
    irq_handle handle;
    uint32 trig_cnt;
    uint32 tot_time;
    uint32 max_time;
};

int32 request_irq(uint32 irq_num, irq_handle handle, void *data);
int32 release_irq(uint32 irq_num);
void irq_status(void);
#define irq_enable(irq)  NVIC_EnableIRQ((irq))
#define irq_disable(irq) NVIC_DisableIRQ((irq))

#ifdef __cplusplus
}
#endif
#endif
