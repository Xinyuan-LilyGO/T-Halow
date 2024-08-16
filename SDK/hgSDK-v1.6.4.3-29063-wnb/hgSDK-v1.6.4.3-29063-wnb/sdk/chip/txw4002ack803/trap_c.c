/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
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

/******************************************************************************
 * @file     trap_c.c
 * @brief    source file for the trap process
 * @version  V1.0
 * @date     12. December 2017
 ******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <csi_config.h>
#include <csi_core.h>
#include <k_api.h>

#define ALIGN(s,a) (((s)+(a)-1) & ~((a)-1))

void trap_dump(char *title, uint32_t stack, uint32_t len)
{
    uint32_t  i   = 0;
    uint32_t *ptr = (uint32_t *)ALIGN(stack, 4);

    printf("\r\nDump %s at 0x%x, len=%d\r\n", title, (uint32_t)ptr, len);
    for (i = 0; i < len / 4; i++) {
        if ((i & 0x3) == 0) {
            if (i) { printf("\r\n"); }
            printf("  0x%08x: ", (uint32_t)(ptr + i));
        }
        printf("  %08x ", ptr[i]);
    }
    printf("\r\n");
}

void trap_c(uint32_t *regs)
{
    int i;
    uint32_t *stack_top;
    uint32_t vec = (__get_PSR() & PSR_VEC_Msk) >> PSR_VEC_Pos;

    printf("---------------------------------------------------------------\r\n");
    printf("CPU Exception: NO.%u\r\n", vec);
    for (i = 0; i < 16; i++) {
        printf("r%d: %08x\t", i, regs[i]);
        if ((i % 4) == 3) {
            printf("\r\n");
        }
    }
    printf("r28 : %08x\r\n", regs[16]);
    printf("epsr: %08x\r\n", regs[17]);
    printf("epc : %08x\r\n", regs[18]);

    printf("\r\nCurTask:%s, stack:0x%08x, size:%d\r\n", g_active_task[0]->task_name,
           (uint32_t)g_active_task[0]->task_stack_base,
           g_active_task[0]->stack_size * sizeof(cpu_stack_t));

    if (*g_active_task[0]->task_stack_base != RHINO_TASK_STACK_OVF_MAGIC) {
        printf("stack damaged **, magic:0x%08x\r\n", *g_active_task[0]->task_stack_base);
    }

    stack_top = g_active_task[0]->task_stack_base + g_active_task[0]->stack_size;
    if (regs[14] > (uint32_t)g_active_task[0]->task_stack_base && regs[14] < (uint32_t)stack_top) {
        trap_dump("Stack", regs[14], (uint32_t)stack_top - regs[14]);
    } else {
        printf("stack damaged (sp:0x%08x, stack: 0x%08x~0x%08x)\r\n", regs[14], (uint32_t)g_active_task[0]->task_stack_base, (uint32_t)stack_top);
    }

    trap_dump("Text",  regs[18] - 64, 128);

#if 0
    mcu_disable_watchdog();
    jtag_map_set(1);
#endif
    while (1);
}

