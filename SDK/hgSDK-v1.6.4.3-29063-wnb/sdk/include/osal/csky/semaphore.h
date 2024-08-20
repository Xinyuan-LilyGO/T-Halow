#ifndef __CSKY_SEMAPHORE_H_
#define __CSKY_SEMAPHORE_H_
#include "csi_kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

struct os_semaphore {
    uint32 magic;
    k_sem_handle_t    hdl;
};

#ifdef __cplusplus
}
#endif

#endif


