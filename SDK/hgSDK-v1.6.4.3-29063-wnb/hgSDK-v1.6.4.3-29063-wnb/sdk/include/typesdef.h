#ifndef _HUGEIC_TYPES_H_
#define _HUGEIC_TYPES_H_

#ifndef __IO
#define __IO volatile
#endif

#ifndef __I
#define __I volatile const
#endif

#ifndef __O
#define __O volatile
#endif

#ifndef RET_OK
#define RET_OK   0
#endif
#ifndef RET_ERR
#define RET_ERR -1
#endif

#ifndef TRUE
#define TRUE   1
#endif
#ifndef FALSE
#define FALSE  0
#endif

#ifndef ALIGN
#define ALIGN(s,a) (((s)+(a)-1) & ~((a)-1))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

#ifdef __MBED__
#include "osal/mbed/typesdef.h"
#endif

#ifdef __CSKY__
#include "osal/csky/typesdef.h"
#endif

#include "tx_platform.h"
#include "version.h"
#endif
