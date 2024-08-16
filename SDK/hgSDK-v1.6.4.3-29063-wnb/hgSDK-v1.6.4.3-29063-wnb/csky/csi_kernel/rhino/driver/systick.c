/*
 * Copyright (C) 2016 YunOS Project. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <k_api.h>
#include <csi_config.h>
#include <soc.h>
#include <drv_timer.h>

typedef struct osTimespec {
    long    tv_sec;
    long    tv_msec;
} osTimespec_t;

uint64_t g_sys_tick_count;
osTimespec_t os_time2;

void systick_handler(void)
{
    g_sys_tick_count++;
    os_time2.tv_msec++;
    if(os_time2.tv_msec > 1000){
        os_time2.tv_sec++;
        os_time2.tv_msec = 0;
    }
    krhino_tick_proc();
}
