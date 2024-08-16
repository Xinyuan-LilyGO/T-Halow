#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "dev.h"
#include "osal/mutex.h"

struct dev_mgr {
    struct list_head head;
    struct os_mutex  mutex;
    uint32 inited;
};

static struct dev_mgr s_dev_mgr;

__init int32 dev_init()
{
    os_mutex_init(&s_dev_mgr.mutex);
    INIT_LIST_HEAD(&s_dev_mgr.head);
    s_dev_mgr.inited = 1;
    return RET_OK;
}

struct dev_obj *dev_get(int32 dev_id)
{
    struct dev_obj *dev = NULL;
    struct dev_obj *pos = NULL;

    if (!s_dev_mgr.inited) { return NULL; }
    os_mutex_lock(&s_dev_mgr.mutex, OS_MUTEX_WAIT_FOREVER);
    list_for_each_entry(pos, &s_dev_mgr.head, list) {
        if (pos->dev_id == dev_id) {
            dev = pos;
            break;
        }
    }
    os_mutex_unlock(&s_dev_mgr.mutex);
    return dev;
}

int32 dev_register(uint32 dev_id, struct dev_obj *device)
{
    struct dev_obj *dev = NULL;

    if ((!s_dev_mgr.inited) || (device == NULL)) {
        return RET_ERR;
    }

    dev = dev_get(dev_id);
    if (dev) {
        return -EEXIST;
    }

    device->dev_id = dev_id;
    os_mutex_lock(&s_dev_mgr.mutex, OS_MUTEX_WAIT_FOREVER);
    list_add_tail(&device->list, &s_dev_mgr.head);
    os_mutex_unlock(&s_dev_mgr.mutex);
    return RET_OK;
}

int32 dev_unregister(struct dev_obj *device)
{
    struct dev_obj *dev = NULL;

    if ((!s_dev_mgr.inited) || (device == NULL)) {
        return RET_ERR;
    }

    dev = dev_get(device->dev_id);
    if (dev) {
        os_mutex_lock(&s_dev_mgr.mutex, OS_MUTEX_WAIT_FOREVER);
        list_del(&dev->list);
        os_mutex_unlock(&s_dev_mgr.mutex);
    }
    return RET_OK;
}

