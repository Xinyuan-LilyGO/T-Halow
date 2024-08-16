
#ifndef __OS_SLEEP_H_
#define __OS_SLEEP_H_

#ifdef __MBED__
#include "osal/mbed/sleep.h"
#endif

#ifdef __CSKY__
#include "osal/csky/sleep.h"
#endif

#define DIFF_JIFFIES(j1,j2) ((j1)<=(j2)?(j2)-(j1):(j2)+0xFFFFFFFF-(j1))
#define TIME_AFTER(a,b)     ((int32)(b) - (int32)(a) < 0)
void os_sleep(int sec);
void os_sleep_ms(int msec);
extern void os_sleep_us(int us);
unsigned int os_jiffies(void);
void os_systime(struct timespec *tm);
void delay_us(uint32 n);

#endif

