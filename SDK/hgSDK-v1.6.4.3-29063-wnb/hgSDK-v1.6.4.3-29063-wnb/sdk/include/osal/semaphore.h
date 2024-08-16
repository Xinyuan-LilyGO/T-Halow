#ifndef __OS_SEMAPHORE_H
#define __OS_SEMAPHORE_H

#ifdef __cplusplus
extern "C" {
#endif

struct os_semaphore;

int32 os_sema_init(struct os_semaphore *sem, int32 val);
int32 os_sema_del(struct os_semaphore *sem);
int32 os_sema_down(struct os_semaphore *sem, int32 tmo_ms);
int32 os_sema_up(struct os_semaphore *sem);
int32 os_sema_count(struct os_semaphore *sem);

#ifdef __cplusplus
}
#endif

#ifdef __MBED__
#include "osal/mbed/semaphore.h"
#endif

#ifdef __CSKY__
#include "osal/csky/semaphore.h"
#endif

#ifndef osWaitForever
#define osWaitForever 0xFFFFFFFFu
#endif
#endif

