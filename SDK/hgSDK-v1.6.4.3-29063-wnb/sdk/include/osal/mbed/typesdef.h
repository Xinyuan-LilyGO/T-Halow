
#ifndef _OS_MBED_TYPESDEF_H_
#define _OS_MBED_TYPESDEF_H_
#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif


#if   defined ( __CC_ARM )
#include <stdint.h>
#include <stddef.h>

typedef int8_t     int8;
typedef int16_t    int16;
typedef int32_t    int32;
typedef int64_t    int64;

typedef uint8_t    uint8;
typedef uint16_t   uint16;
typedef uint32_t   uint32;
typedef uint64_t   uint64;

#elif defined ( __ICCARM__ )

#elif defined ( __GNUC__ )

#endif

#ifdef __cplusplus
}
#endif

#include "byteshift.h"
#endif


