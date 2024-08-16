
#ifndef _CSKY_MSG_QUEUE_H_
#define _CSKY_MSG_QUEUE_H_
#include "csi_kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

struct os_msgqueue {
    uint32 magic;
    k_msgq_handle_t hdl;
};

#ifdef __cplusplus
}
#endif

#endif


