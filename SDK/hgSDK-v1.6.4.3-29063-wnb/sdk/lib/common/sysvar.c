
#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "osal/string.h"
#include "lib/sysvar.h"

uint32 sysvar_mgr[SYSVAR_ID_MAX];

void *sysvar_init(enum sysvar_id id, int size)
{
    if (id < SYSVAR_ID_MAX) {
        if (sysvar_mgr[id] == (uint32)NULL) {
            sysvar_mgr[id] = (uint32)os_malloc(size);
        }
        if (sysvar_mgr[id]) {
            os_memset((void *)sysvar_mgr[id], 0, size);
        }
        return (void *)sysvar_mgr[id];
    }
    return NULL;
}

void *sysvar(enum sysvar_id id)
{
    if (id < SYSVAR_ID_MAX) {
        return (void *)sysvar_mgr[id];
    }
    return NULL;
}

