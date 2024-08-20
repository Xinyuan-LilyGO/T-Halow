#ifndef _CSKY_ATOMIC_H_
#define _CSKY_ATOMIC_H_
#include "csi_core.h"
#include "k_api.h"

typedef struct {
    uint32 counter;
} atomic_t;

typedef struct {
    uint64 counter;
} atomic64_t;


#define atomic64_read(v)        ((v)->counter)
#define atomic_read(v)          ((v)->counter)

#define atomic_set(v,i)        ({ \
        uint32 __mask__ = cpu_intrpt_save();\
        ((v)->counter = i); \
        cpu_intrpt_restore(__mask__);\
    })
#define atomic_inc(v)           ({ \
        uint32 __mask__ = cpu_intrpt_save();\
        ((v)->counter++); \
        cpu_intrpt_restore(__mask__);\
    })
#define atomic_dec(v)           ({ \
        uint32 __mask__ = cpu_intrpt_save();\
        ((v)->counter--); \
        cpu_intrpt_restore(__mask__);\
    })
#define atomic_inc_return(v)    ({\
        uint32 __mask__ = cpu_intrpt_save();\
        uint32_t __val__ = (++(v)->counter);\
        cpu_intrpt_restore(__mask__);\
        __val__;\
    })
#define atomic_dec_return(v)    ({\
        uint32 __mask__ = cpu_intrpt_save();\
        uint32_t __val__ = (--(v)->counter);\
        cpu_intrpt_restore(__mask__);\
        __val__;\
    })
#define atomic_dec_and_test(v)    ({\
        uint32 __mask__ = cpu_intrpt_save();\
        uint32_t __val__ = (--(v)->counter == 0);\
        cpu_intrpt_restore(__mask__);\
        __val__;\
    })
#define atomic_cmpxchg(v,o,n)    ({\
        uint32 __mask__ = cpu_intrpt_save();\
        uint32_t __val = (v)->counter;\
        if(__val == o) (v)->counter = n;\
        cpu_intrpt_restore(__mask__);\
        __val;\
    })

static inline int atomic_add_unless(atomic_t *v, int a, int u)
{
    int c, old;
    c = atomic_read(v);
    while (c != u && (old = atomic_cmpxchg((v), c, c + a)) != c) {
        c = old;
    }
    return c != u;
}


#endif

