
#ifndef _MBED_MSG_QUEUE_H_
#define _MBED_MSG_QUEUE_H_

#include "cmsis_os.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OS_MSGQ_DEF(name, sz) \
    static int32 os_msgqueue_pool_##name [4+(sz)];\
    struct os_msgqueue name = {.pool = os_msgqueue_pool_##name, .size = sz };

struct os_msgqueue {
    void *pool;
    int32 size;
    osMessageQId    _osMsgqId;
    osMessageQDef_t _osMsgqDef;
};

#ifdef __cplusplus
}
#endif

#endif


