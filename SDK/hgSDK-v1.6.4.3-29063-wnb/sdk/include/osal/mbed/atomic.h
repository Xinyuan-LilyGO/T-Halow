#ifndef _MBED_ATOMIC_H_
#define _MBED_ATOMIC_H_

typedef struct {
    uint32 counter;
} atomic_t;

typedef struct {
    uint64 counter;
} atomic64_t;


#define atomic64_read(v)        ((v)->counter)
#define atomic_read(v)          ((v)->counter)

#define atomic_set(v,i)        ({ \
        uint32 __mask__ = __disable_irq();\
        ((v)->counter = i); \
        if(!__mask__) __enable_irq();\
    })
#define atomic_inc(v)           ({ \
        uint32 __mask__ = __disable_irq();\
        ((v)->counter++); \
        if(!__mask__) __enable_irq();\
    })
#define atomic_dec(v)           ({ \
        uint32 __mask__ = __disable_irq();\
        ((v)->counter--); \
        if(!__mask__) __enable_irq();\
    })
#define atomic_inc_return(v)    ({\
        uint32 __mask__ = __disable_irq();\
        uint32_t __val__ = (++(v)->counter);\
        if(!__mask__) __enable_irq();\
        __val__;\
    })
#define atomic_dec_return(v)    ({\
        uint32 __mask__ = __disable_irq();\
        uint32_t __val__ = (--(v)->counter);\
        if(!__mask__) __enable_irq();\
        __val__;\
    })
#define atomic_dec_and_test(v)    ({\
        uint32 __mask__ = __disable_irq();\
        uint32_t __val__ = (--(v)->counter == 0);\
        if(!__mask__) __enable_irq();\
        __val__;\
    })
#define atomic_cmpxchg(v,o,n)    ({\
        uint32 __mask__ = __disable_irq();\
        uint32_t __val = (v)->counter;\
        if(__val == o) (v)->counter = n;\
        if(!__mask__) __enable_irq();\
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

