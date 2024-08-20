#include "typesdef.h"
#include "errno.h"
#include "list.h"
#include "dev.h"
#include "osal/task.h"
#include "osal/sleep.h"
#include "osal/string.h"
#include "hal/dma.h"
#include "lib/common.h"

struct dma_device *m2mdma = NULL;

__weak void   system_sleepdata_reset(void){};
__weak void  *system_sleepdata_request(uint8 id, uint32 size) { return 0; }
__weak uint32 system_sleepdata_freesize(void) { return 0; }

void cpu_loading_print(uint8 all)
{
    uint32 i = 0;
    uint32 diff_tick = 0;
    uint32 count = 32;
    struct os_task_time tsk_runtime[OS_TASK_COUNT + 1];
    static uint32 cpu_loading_tick = 0;
    uint32 jiff = os_jiffies();

    count = os_task_runtime(tsk_runtime, OS_TASK_COUNT + 1);
    diff_tick = DIFF_JIFFIES(cpu_loading_tick, jiff);
    cpu_loading_tick = jiff;

    os_printf("-----------------------------------------------\r\n");
    os_printf("Task Runtime Statistic, interval:%dms\r\n", diff_tick);
    os_printf("-----------------------------------------------\r\n");
    for (i = 0; i < count && i < OS_TASK_COUNT + 1; i++) {
        if (tsk_runtime[i].time > 0 || all) {
            os_printf("%2d  %-16s %2d%% (%5d) (%p)\r\n",
                      tsk_runtime[i].id,
                      tsk_runtime[i].name ? tsk_runtime[i].name : (const uint8 *)"----",
                      (tsk_runtime[i].time * 100) / diff_tick,
                      tsk_runtime[i].time, tsk_runtime[i].arg);
        }
    }
    os_printf("-----------------------------------------------\r\n");
}

int strncasecmp(const char *s1, const char *s2, int n)
{
    size_t i = 0;
    
    for (i = 0; i < n && s1[i] && s2[i]; i++) {
        if (s1[i] == s2[i] || s1[i] + 32 == s2[i] || s1[i] - 32 == s2[i]) {
        } else {
            break;
        }
    }
    return (i != n);
}

int strcasecmp(const char *s1, const char *s2)
{
    while (*s1 || *s2) {
        if (*s1 == *s2 || *s1 + 32 == *s2 || *s1 - 32 == *s2) {
            s1++; s2++;
        } else {
            return -1;
        }
    }
    return 0;
}

void hw_memcpy(void *dest, const void *src, uint32 size)
{
    if (dest && src) {
        if (m2mdma && size > 45) {
            dma_memcpy(m2mdma, dest, src, size);
        } else {
            os_memcpy(dest, src, size);
        }
    }
}

void hw_memset(void *dest, uint8 val, uint32 n)
{
    if (dest) {
        if (m2mdma && n > 12) {
            dma_memset(m2mdma, dest, val, n);
        } else {
            os_memset(dest, val, n);
        }
    }
}

void sdk_version(uint32 *sdk_ver, uint32 *svn_ver, uint32 *app_ver)
{
    *sdk_ver = SDK_VERSION;
    *svn_ver = SVN_VERSION;
    *app_ver = APP_VERSION;
}

__weak int32 customer_driver_data_proc(uint8 *data, uint32 len)
{
    return -ESRCH;
}
