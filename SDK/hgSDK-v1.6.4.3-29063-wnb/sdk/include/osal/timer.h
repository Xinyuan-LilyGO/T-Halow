
#ifndef __OS_TIMER_H_
#define __OS_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

enum OS_TIMER_MODE {
    OS_TIMER_MODE_ONCE,
    OS_TIMER_MODE_PERIODIC
};

struct os_timer;

typedef void (*os_timer_func_t)(void *arg);

int os_timer_init(struct os_timer *timer, os_timer_func_t func,
                   enum OS_TIMER_MODE mode, void *arg);
int os_timer_start(struct os_timer *timer, unsigned long expires);
int os_timer_stop(struct os_timer *timer);
int os_timer_del(struct os_timer *timer);

#ifdef __cplusplus
}
#endif

#ifdef __MBED__
#include "osal/mbed/timer.h"
#endif

#ifdef __CSKY__
#include "osal/csky/timer.h"
#endif

#endif

