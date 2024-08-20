
#ifndef _OS_TASK_H_
#define _OS_TASK_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum  {
    OS_TASK_PRIORITY_IDLE         = 0,
    OS_TASK_PRIORITY_LOW          = 0x10,
    OS_TASK_PRIORITY_BELOW_NORMAL = 0x20,
    OS_TASK_PRIORITY_NORMAL       = 0x30,
    OS_TASK_PRIORITY_ABOVE_NORMAL = 0x40,
    OS_TASK_PRIORITY_HIGH         = 0x50,
    OS_TASK_PRIORITY_REALTIME     = 0x60,
    OS_TASK_PRIORITY_ISR          = 0xFF,
} OS_TASK_PRIORITY;

#define OS_TASK_INIT(name, task, func, data, prio, stksize) do { \
        os_task_init((const uint8 *)name, task, (os_task_func_t)func, (uint32)data); \
        os_task_set_stacksize(task, stksize); \
        os_task_set_priority(task, prio); \
        os_task_run(task);\
    }while(0)

struct os_task;

struct os_task_time {
    uint32 id;
    const uint8 *name;
    uint32 time;
    uint32 arg;
};

typedef void (*os_task_func_t)(void *arg);

int32 os_task_init(const uint8 *name, struct os_task *task, os_task_func_t func, uint32 data);
int32 os_task_priority(struct os_task *task);
int32 os_task_stacksize(struct os_task *task);
int32 os_task_set_priority(struct os_task *task, uint8 priority);
int32 os_task_set_stacksize(struct os_task *task, int32 stack_size);
int32 os_task_run(struct os_task *task);
int32 os_task_stop(struct os_task *task);
int32 os_task_del(struct os_task *task);
int32 os_task_runtime(struct os_task_time *tsk_times, int32 count);
void os_task_dump(void *hdl);
struct os_task *os_task_current(void);

#ifdef __cplusplus
}
#endif

#ifdef __MBED__
#include "osal/mbed/task.h"
#endif

#ifdef __CSKY__
#include "osal/csky/task.h"
#endif

#endif



