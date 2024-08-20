
#include "typesdef.h"
#include "list.h"
#include "dev.h"
#include "devid.h"
#include "osal/string.h"
#include "hal/uart.h"
#include "lib/sysheap.h"

#include "csi_core.h"
#include "drv_usart.h"

#ifdef MPOOL_ALLOC

void *krhino_mm_alloc(size_t size, void *caller)
{
#ifdef MEM_TRACE
    return _os_malloc_t(size, caller, 0);
#else
    return _os_malloc(size);
#endif
}

void krhino_mm_free(void *ptr)
{
    os_free(ptr);
}

void k_mm_init(void)
{
    sysheap_init((void *)SYS_HEAP_START, SYS_HEAP_SIZE);
}

#endif

