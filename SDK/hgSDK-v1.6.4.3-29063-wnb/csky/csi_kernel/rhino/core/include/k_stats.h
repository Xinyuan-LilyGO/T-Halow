/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#ifndef K_STATS_H
#define K_STATS_H

#if (RHINO_CONFIG_SYSTEM_STATS > 0)
void kobj_list_init(void);
#endif

#if (RHINO_CONFIG_TASK_STACK_OVF_CHECK > 0)
/**
 * This function will check task stack overflow
 */
void krhino_stack_ovf_check(void);
#endif

#if (RHINO_CONFIG_TASK_SCHED_STATS > 0)
/**
 * This function will reset task schedule stats
 */
void krhino_task_sched_stats_reset(void);
/**
 * This function will get task statistic data
 */
void krhino_task_sched_stats_get(void);
#endif

#if (RHINO_CONFIG_HW_COUNT > 0)
void krhino_overhead_measure(void);
#endif

#if (RHINO_CONFIG_CPU_USAGE_STATS > 0)
uint32_t krhino_get_cpu_usage(void);
#endif

#endif /* K_STATS_H */

