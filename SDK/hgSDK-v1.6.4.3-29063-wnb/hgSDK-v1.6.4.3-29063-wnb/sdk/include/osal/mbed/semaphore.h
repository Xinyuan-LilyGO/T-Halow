#ifndef __MBED_SEMAPHORE_H
#define __MBED_SEMAPHORE_H

#include "cmsis_os.h"

#ifdef __cplusplus
extern "C" {
#endif

struct os_semaphore {
    osSemaphoreId    _osSemaphoreId;
    osSemaphoreDef_t _osSemaphoreDef;
#ifdef CMSIS_OS_RTX
    uint32_t _semaphore_data[2];
#endif
};

#ifdef __cplusplus
}
#endif

#endif


