#include "typesdef.h"
#include "list.h"
#include "dev.h"
#include "devid.h"
#include "osal/sleep.h"
#include "lib/ticker_api.h"
#include "hal/timer_device.h"

void os_sleep_us(int us)
{
#ifdef RTOS_ENABLE    
    uint32 ms = us / 1000;
    us = us % 1000;
    if (ms > 0) {
        os_sleep_ms(ms);
    }
#endif
    delay_us(us);
}

