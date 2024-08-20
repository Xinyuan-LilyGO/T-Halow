/**
 * @file drivercmd.c
 * @author HUGE-IC Application Team
 * @brief Module driver command function
 * @version 1.0.0
 * @date 2021-8-31
 * 
 * @copyright Copyright (c) 2021 HUGE-IC
 */
#include "lib/drivercmd.h"
#include "list.h"
#include "osal/string.h"
#include "osal/semaphore.h"
#include "osal/mutex.h"

#define DRIVER_CMD_HOOK_MAX (8)

struct driver_cmd_hook {
    uint32          priv;
    driver_cmd_hdl  hdl;
};

static struct driver_cmd_hook drv_hook_mgr[DRIVER_CMD_HOOK_MAX] = {0};


/**
 * @brief Module driver command handler register
 * 
 * @param hdl  Module driver command handler
 * @param data  Module driver data
 * @return int32
 * @retval error code
 * 
 */
int32 driver_cmd_hdl_register(driver_cmd_hdl hdl, uint32 data)
{
    uint8 i;
    uint8 hold = 255; // init an invaild value
    
    if (hdl == NULL) {
        return -EINVAL;
    }
    for (i = 0; i < DRIVER_CMD_HOOK_MAX; ++i) {
        if (drv_hook_mgr[i].hdl == hdl && drv_hook_mgr[i].priv == data) { // duplicate case
            if (hold != 255) { // hold empty idx, need release it
                drv_hook_mgr[i].priv = 0;
                drv_hook_mgr[i].hdl = NULL;
            }
            return -EEXIST;
        }
        if (drv_hook_mgr[i].hdl == NULL && drv_hook_mgr[i].priv == 0 && hold == 255) {
            drv_hook_mgr[i].priv = data;
            drv_hook_mgr[i].hdl = hdl;
            hold = i; // hold empty idx, reduce loop times
        }
    }
    if (hold == 255) {
        return -ENOMEM;
    }
    return 0;
}

/**
 * @brief Module driver command handler unregister
 * 
 * @param hdl  Module driver command handler
 * @return int32
 * @retval error code
 * 
 */
int32 driver_cmd_hdl_unregister(driver_cmd_hdl hdl)
{
    uint8 i;
    
    if (hdl == NULL) {
        return -EINVAL;
    }
    for (i = 0; i < DRIVER_CMD_HOOK_MAX; ++i) {
        if (drv_hook_mgr[i].hdl == hdl) {
            drv_hook_mgr[i].priv = 0;
            drv_hook_mgr[i].hdl = NULL;
            break;
        }
    }
    if (i == DRIVER_CMD_HOOK_MAX) {
        return -EINVAL;
    }
    return 0;
}

/**
 * @brief Module hook set processor
 * 
 * @param param  Module driver command parameter
 * @return int32
 * @retval -MAX_ERRNO  No module driver process
 * 
 */
int32 driver_cmd_hdl_proc(struct driver_cmd_param *param)
{
    int32 ret = -MAX_ERRNO;
    uint8 i;
    for (i = 0; i < DRIVER_CMD_HOOK_MAX; ++i) {
        if (drv_hook_mgr[i].hdl && param) {
            ret = drv_hook_mgr[i].hdl(drv_hook_mgr[i].priv, param);
        }
        if (ret != -MAX_ERRNO) {
            break;
        }
    }
    return ret;
}
