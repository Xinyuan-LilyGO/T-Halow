#ifndef _CSKY_DEFS_H_
#define _CSKY_DEFS_H_
#include <assert.h>


#ifdef __cplusplus
extern "C" {
#endif

#define osWaitForever     (-1)

#ifndef ASSERT
#ifdef NDEBUG
#define ASSERT(expr) ((void)0)
#else
extern uint8_t assert_holdup;
void assert_internal(const char *__function, unsigned int __line, const char *__assertion);

#define ASSERT(f)   do {                                                            \
                        if(!(f)) {                                                  \
                            assert_internal(__ASSERT_FUNC, __LINE__, #f); \
                        }                                                           \
                    } while(0)
#endif
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef __inline
#define __inline          inline
#endif

#ifndef __weak
#define __weak            __attribute__((weak))
#endif

#ifndef __alias
#define __alias(f)        __attribute__((alias(#f)))
#endif

#ifndef __at_section
#define __at_section(sec) __attribute__((section(sec)))
#endif

#ifndef __used
#define __used __attribute__((used))
#endif

#ifndef __aligned
#define __aligned(n)      __attribute__((aligned(n)))
#endif

#ifndef __packed
#define __packed          __attribute__((packed))
#endif

#ifndef __init
#define __init            __at_section("INIT.TXT")
#endif

#ifndef __initdata
#define __initdata        __at_section("INIT.DAT")
#endif

#ifndef __rom
#define __rom             __at_section("ROM.TXT")
#endif

#ifndef __romdata
#define __romdata         __at_section("ROM.DAT")
#endif

#ifndef NULL
#define NULL (void *)0
#endif

#ifndef BIT
#define BIT(a) (1u << (a))
#endif

#ifndef offsetof
#define offsetof(type, member) ((long) &((type *) 0)->member)
#endif

#ifndef container_of
#define container_of(ptr, type, member) ({      \
        void *__mptr = (void *)(ptr);                   \
        (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

#ifndef RETURN_ADDR
#define RETURN_ADDR() __builtin_return_address(0)
#endif

#ifndef __always_inline
#define __always_inline inline
#endif

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

size_t cpu_intrpt_save(void);
void   cpu_intrpt_restore(size_t psr);

#define disable_irq()    cpu_intrpt_save()
#define enable_irq(f)    cpu_intrpt_restore(f)

#ifdef __cplusplus
}
#endif
#endif
