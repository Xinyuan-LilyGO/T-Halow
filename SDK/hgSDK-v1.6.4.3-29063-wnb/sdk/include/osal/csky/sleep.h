
#ifndef __CSKY_SLEEP_H_
#define __CSKY_SLEEP_H_
#include "csi_kernel.h"
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_HZ CONFIG_SYSTICK_HZ

#define os_jiffies_to_msecs(j) (j)
#define os_msecs_to_jiffies(m) (m)

#ifdef __cplusplus
}
#endif

#endif


