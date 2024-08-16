/**
 * @file drivercmd.h
 * @author HUGE-IC Application Team
 * @brief Module driver command function
 * @version 1.0.0
 * @date 2021-8-31
 * 
 * @copyright Copyright (c) 2021 HUGE-IC
 */
#ifndef _DRIVER_CMD_H_
#define _DRIVER_CMD_H_

#include "typesdef.h"

struct driver_cmd_param {
    uint32  cmd;
    uint8  *data;
    uint32  data_len;
    uint8 **resp;
    uint32 *resp_len; 
};

typedef int32(*driver_cmd_hdl)(uint32 priv, struct driver_cmd_param *param);

int32 driver_cmd_hdl_register(driver_cmd_hdl hdl, uint32 data);
int32 driver_cmd_hdl_unregister(driver_cmd_hdl hdl);
int32 driver_cmd_hdl_proc(struct driver_cmd_param *param);

#endif // _DRIVER_CMD_H_