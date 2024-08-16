#ifndef __OS_MBED_DEFS_H_
#define __OS_MBED_DEFS_H_
#include "mbed_assert.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef ASSERT
#define ASSERT(f) MBED_ASSERT(f)
#endif

#if   defined ( __CC_ARM )

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
#define __packed          __attribute__((__packed__))
#endif

#elif defined ( __GNUC__ )

#elif defined ( __ICCARM__ )

#elif defined ( __TASKING__ )

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

#ifndef container_of
#define container_of(ptr, type, member) ({      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

#ifndef RETURN_ADDR
#define RETURN_ADDR() __return_address()
#endif

#ifndef __always_inline
#define __always_inline inline
#endif

#define disable_irq()    __disable_irq()
#define enable_irq(f)    if(!f){  __enable_irq(); }

#ifdef __cplusplus
}
#endif
#endif
