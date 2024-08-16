
#ifndef _MBED_TIMER_H_
#define _MBED_TIMER_H_
#include "cmsis_os.h"

#ifdef __cplusplus
extern "C" {
#endif

struct os_timer {
    osTimerId    _timer_id;
    osTimerDef_t _timer_def;
    uint32_t     timer_data[6];
    uint32_t     expires;
    
    os_timer_func_t cb;
    void        *data;
    uint32_t     trigger_cnt;
    uint32_t     total_time;
    uint32_t     max_time;
};

#ifdef __cplusplus
}
#endif

#endif


