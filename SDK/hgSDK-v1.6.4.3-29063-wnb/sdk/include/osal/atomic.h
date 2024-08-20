
#ifndef _OS_ATOMIC_H_
#define _OS_ATOMIC_H_
#include "typesdef.h"
#include "osal/irq.h"

#ifdef __MBED__
#include "osal/mbed/atomic.h"
#endif

#ifdef __CSKY__
#include "osal/csky/atomic.h"
#endif

#endif


