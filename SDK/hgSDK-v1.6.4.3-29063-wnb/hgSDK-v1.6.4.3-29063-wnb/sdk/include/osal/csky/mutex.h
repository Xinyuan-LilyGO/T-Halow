
#ifndef __CSKY_MUTEX_H_
#define __CSKY_MUTEX_H_
#include "csi_kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OS_MUTEX_WAIT_FOREVER osWaitForever

struct os_mutex {
    uint32 magic;
    k_mutex_handle_t hdl;
};

#ifdef __cplusplus
}
#endif

#endif

