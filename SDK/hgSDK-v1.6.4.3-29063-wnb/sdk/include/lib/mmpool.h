#ifndef _HGIC_MMPOOL_H_
#define _HGIC_MMPOOL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"

struct mmpool {
    uint32 size;
    uint8  headsize, tailsize, trace_off, ofchk_off;
    struct list_head free_list;
    struct list_head used_list;
};

#define REGION_CNT (12)
struct mmpool2 {
    uint32 size;
    uint8  headsize, tailsize, trace_off, ofchk_off;
    struct list_head list[REGION_CNT];
    struct list_head used_list;
};

void *mmpool_alloc(struct mmpool *mp, uint32 size, const char *func, int32 line);
int32 mmpool_free(struct mmpool *mp, void *ptr);
int32 mmpool_init(struct mmpool *mp, uint32 addr, uint32 size);
int32 mmpool_free_state(struct mmpool *mp, uint32 *stat_buf, int32 size);
int32 mmpool_used_state(struct mmpool *mp, uint32 *stat_buf, int32 size);
int32 mmpool_add_region(struct mmpool *mp, uint32 addr, uint32 size);

void *mmpool2_alloc(struct mmpool2 *mp, uint32 size, const char *func, int32 line);
void mmpool2_free(struct mmpool2 *mp, void *ptr);
int32 mmpool2_init(struct mmpool2 *mp, uint32 addr, uint32 size);
int32 mmpool2_free_state(struct mmpool2 *mp, uint32 *stat_buf, int32 size);
int32 mmpool2_used_state(struct mmpool2 *mp, uint32 *stat_buf, int32 size);
int32 mmpool2_add_region(struct mmpool2 *mp, uint32 addr, uint32 size);

#ifdef __cplusplus
}
#endif
#endif
