#ifndef __MBED_OS_TASK_H_
#define __MBED_OS_TASK_H_
#include "cmsis_os.h"

#ifdef __cplusplus
extern "C" {
#endif

struct os_task {
    osThreadId     thread_id;
    osThreadDef_t  thread_def;
    os_task_func_t func;
    uint32_t       args;
    int32_t        priority;
};

#ifdef __cplusplus
}
#endif

#endif

