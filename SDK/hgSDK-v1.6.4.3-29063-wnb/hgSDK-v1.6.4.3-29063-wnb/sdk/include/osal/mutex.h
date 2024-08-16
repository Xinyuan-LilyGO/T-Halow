#ifndef _OS_MUTEX_H_
#define _OS_MUTEX_H_

#ifdef RTOS_ENABLE
#ifdef __cplusplus
extern "C" {
#endif

struct os_mutex;

int32 os_mutex_init(struct os_mutex *mutex);
int32 os_mutex_lock(struct os_mutex *mutex, int32 tmo);
int32 os_mutex_unlock(struct os_mutex *mutex);
int32 os_mutex_del(struct os_mutex *mutex);

#ifdef __cplusplus
}
#endif

#ifdef __MBED__
#include "osal/mbed/mutex.h"
#endif

#ifdef __CSKY__
#include "osal/csky/mutex.h"
#endif
#else
struct os_mutex { uint32 val; };
#define os_mutex_init(m) (0)
#define os_mutex_lock(m, t) (0)
#define os_mutex_unlock(m) (0)
#define os_mutex_del(m) (0)
#endif
#endif
