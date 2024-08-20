/*****************************************************************************
 * Module    : usb
 * File      : usb_dev.h
 * Author    :
 * Function  : USB Device驱动的一些定义
 *****************************************************************************/
#ifndef USB_DEV_H
#define USB_DEV_H

#include "typesdef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define USB_REQUEST_DIRECTION           (p_dev->usb_ctrl.cmd.rtype & 0x80)
#define USB_REQUEST_TYPE                (p_dev->usb_ctrl.cmd.rtype & 0x60)
#define USB_REQUEST_RECIPIENT           (p_dev->usb_ctrl.cmd.rtype & 0x1f)
#define USB_REQUEST_ENDPOINT            BYTE0(p_dev->usb_ctrl.cmd.index)
#define USB_REQUEST_FEATURE_SELECTOR    (p_dev->usb_ctrl.cmd.value)
#define USB_REQUEST_DESCRIPTOR_TYPE     BYTE1(p_dev->usb_ctrl.cmd.value)
#define USB_REQUEST_DESCRIPTOR_INDEX    BYTE0(p_dev->usb_ctrl.cmd.value)
#define USB_REQUEST_LENGTH              (p_dev->usb_ctrl.cmd.length)


struct hgusb11_dev_info {
    uint8_t type;                        //设备类型
    uint8_t set_addr;                    //设地址
    uint8_t cfg_value;                   //Config Value, 用于Set Config与Get Config
    uint8_t cur_state;                   //USB当前状态机
    uint8_t ep0_state;                   //EP0的状态机
    uint8_t ep0_pkt;                     //EP0包大小
    uint8_t *ep0_ptr;                    //当前发送指针
    uint16_t ep0_len;                    //当前发送剩余
    uint8_t isoc_tx_interface;           //ISOC，MIC发送的接口
    uint8_t isoc_tx_enable;              //ISOC使能
    uint8_t isoc_tx_enable_int;          //在中断中配置ISOC使能

    volatile uint8_t ep1_tx_stall;       //ep1 tx stall标志
    volatile uint8_t ep1_rx_stall;       //ep1 rx stall标志
    volatile uint8_t ep1_pipe_stall;     //ep1 Stall的标志
    volatile uint8_t ep2_tx_stall;       //ep1 tx stall标志
    volatile uint8_t ep2_rx_stall;       //ep1 rx stall标志
    volatile uint8_t ep2_pipe_stall;     //ep1 Stall的标志
} ;

struct hgusb11_audio_ctrl {
    uint8_t speaker_mute;
    uint8_t mic_mute;
    uint8_t volume;
/*
    uint8_t *adc_root;
    uint8_t *adc_end;
    uint8_t *adc_ptr;
    int16_t adc_cnt;
    int16_t adc_total;
    int8_t mic_speed;
*/
} ;


#ifdef __cplusplus
}
#endif

#endif
