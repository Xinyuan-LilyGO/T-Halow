/**
  ******************************************************************************
  * @file    ad936x.h
  * @author  
  * @version V1.0.2
  * @date    01.25.2019
  * @brief   This file contains all the IIC firmware functions.
  * Revision History
  * (1) 06.27.2018   First Release liuhuimin
  * (2) 01.17.2019   modified for sdk hushifei
  * (3) 01.25.2019   fix __AD936X_H__ by wangying
  ******************************************************************************
**/	 
#ifndef __AD936X_H__
#define __AD936X_H__

struct hg_ad936x {
    struct rf_device             dev;
    struct rfspi_device         *spi;  //what if the attached dev is spi_v2 ? 
    uint8  reset_io;
};

int32 hg_ad9361_attach(uint32 dev_id, struct hg_ad936x *hg936x);

#endif
