#include "typesdef.h"
#include "csi_core.h"
#include <k_api.h>
#include "osal/string.h"
#include "lib/ticker_api.h"

#ifndef ASSERT_HOLDUP
#define ASSERT_HOLDUP 0
#endif

uint8_t assert_holdup = ASSERT_HOLDUP;
void assert_internal(const char *__function, unsigned int __line, const char *__assertion)
{
    uint32_t in_int = __in_interrupt();
    ktask_t *task = csi_kernel_task_get_cur();

    enable_print();
    if (assert_holdup) {
        mcu_disable_watchdog();
        jtag_map_set(1);
    }

    if(!in_int && task){
        csi_kernel_task_dump(task);
    }

    do {
        printf("[%s]: assertation \"%s\" failed: function: %s, line %d\r\n", 
                  (in_int ? "Interrupt" : task->task_name), __assertion, __function, __line);
        if(in_int){
            delay_us(1000*1000);
        }else{
            os_sleep(5);
        }
    } while (assert_holdup);
}

