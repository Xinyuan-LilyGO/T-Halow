
#ifndef __CSKY_OS_TIMER_H_
#define __CSKY_OS_TIMER_H_
#include "csi_kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

struct os_timer {
    uint32 magic;
    k_timer_handle_t hdl;
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


