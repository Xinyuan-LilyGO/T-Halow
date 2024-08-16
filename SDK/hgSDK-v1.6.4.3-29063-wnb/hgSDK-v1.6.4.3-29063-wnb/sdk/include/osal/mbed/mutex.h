
#ifndef _MBED_OS_MUTEX_H
#define _MBED_OS_MUTEX_H

#include "cmsis_os.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OS_MUTEX_WAIT_FOREVER osWaitForever

struct os_mutex {
    osMutexId _osMutexId;
    osMutexDef_t _osMutexDef;
#ifdef CMSIS_OS_RTX
#if defined(__MBED_CMSIS_RTOS_CA9) || defined(__MBED_CMSIS_RTOS_CM)
    int32_t _mutex_data[4];
#else
    int32_t _mutex_data[3];
#endif
#endif
};

#ifdef __cplusplus
}
#endif

#endif

