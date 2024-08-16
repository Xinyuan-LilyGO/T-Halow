
#ifndef _OS_MSG_QUEUE_H_
#define _OS_MSG_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

struct os_msgqueue;

int32 os_msgq_init(struct os_msgqueue *msgq, int32 size);
uint32 os_msgq_get(struct os_msgqueue *msgq, int32 tmo_ms);
int32 os_msgq_put(struct os_msgqueue *msgq, uint32 data, int32 tmo_ms);
int32 os_msgq_del(struct os_msgqueue *msgq);
int32 os_msgq_cnt(struct os_msgqueue *msgq);

#ifdef __cplusplus
}
#endif

#ifdef __MBED__
#include "osal/mbed/msgqueue.h"
#endif

#ifdef __CSKY__
#include "osal/csky/msgqueue.h"
#endif


#ifndef OS_MSGQ_DEF
#define OS_MSGQ_DEF(name, size) struct os_msgqueue name;
#endif

#ifndef osWaitForever
#define osWaitForever 0xFFFFFFFFu
#endif

#endif


