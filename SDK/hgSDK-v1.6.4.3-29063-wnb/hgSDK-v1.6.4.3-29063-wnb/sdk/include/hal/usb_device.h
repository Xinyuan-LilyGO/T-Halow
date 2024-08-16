#ifndef _HAL_USB_DEVICE_H_
#define _HAL_USB_DEVICE_H_

#include "hal/usb_ch9.h"

#ifdef __cplusplus
extern "C" {
#endif


enum usb_dev_irqs {
    USB_DEV_RESET_IRQ,
    USB_DEV_SUSPEND_IRQ,
    USB_DEV_RESUME_IRQ,
    USB_DEV_SOF_IRQ,
    USB_DEV_CTL_IRQ,
    USB_EP1_RX_IRQ,
    USB_EP1_TX_IRQ,
    USB_EP2_RX_IRQ,
    USB_EP2_TX_IRQ,
};

enum usb_dev_io_cmd {
    USB_DEV_IO_CMD_AUTO_TX_NULL_PKT_ENABLE,
    USB_DEV_IO_CMD_AUTO_TX_NULL_PKT_DISABLE,
};


struct usb_device_ep_cfg {
    uint8                   ep_id;
    uint8                   ep_type;
    uint8                   ep_dir_tx;
    uint32                  max_packet_size;
};

struct usb_device_cfg {
    uint16                      vid;
    uint16                      pid;
    uint8                       speed;
    uint8                      *p_device_descriptor;
    uint8                      *p_config_descriptor_head;
    void                       *p_config_desc;
    uint16                      config_desc_len;
    uint8                       interface_num;

    uint8                      *p_language_id;
    uint16                      language_id_len;
    uint8                      *p_str_manufacturer;
    uint16                      str_manufacturer_len;
    uint8                      *p_str_product;
    uint16                      str_product_len;
    uint8                      *p_str_serial_number;
    uint16                      str_serial_number_len;

    uint8                       ep_nums;
    struct usb_device_ep_cfg    ep_cfg[8];      /* must same with config_desc */
};

typedef void (*usbdev_irq_hdl)(uint32 irq, uint32 param1, uint32 param2);

struct usb_device {
    struct dev_obj dev;
    uint32 obj;
    int32(*open)(struct usb_device *p_usb_d, struct usb_device_cfg *p_usbdev_cfg);
    int32(*close)(struct usb_device *p_usb_d);
    int32(*read)(struct usb_device *p_usb_d, int8 ep, int8 *buff, uint32 len, int8 sync);
    int32(*write)(struct usb_device *p_usb_d, int8 ep, int8 *buff, uint32 len, int8 sync);
    int32(*ioctl)(struct usb_device *p_usb_d, uint32 cmd, uint32 param);
    int32(*request_irq)(struct usb_device *p_usb_d, usbdev_irq_hdl irqhdl, uint32 data);
};

static inline int32 usb_device_open(struct usb_device *p_usb_d, struct usb_device_cfg *p_usbdev_cfg)
{
    if (p_usb_d && p_usb_d->open) {
        return p_usb_d->open(p_usb_d, p_usbdev_cfg);
    }
    return RET_ERR;
}

static inline int32 usb_device_close(struct usb_device *p_usb_d)
{
    if (p_usb_d && p_usb_d->close) {
        return p_usb_d->close(p_usb_d);
    }
    return RET_ERR;
}

static inline int32 usb_device_write(struct usb_device *p_usb_d, int8 ep, int8 *buff, uint32 len, int8 sync)
{
    if (p_usb_d && p_usb_d->write) {
        return p_usb_d->write(p_usb_d, ep, buff, len, sync);
    }
    return RET_ERR;
}

static inline int32 usb_device_read(struct usb_device *p_usb_d, int8 ep, int8 *buff, uint32 len, int8 sync)
{
    if (p_usb_d && p_usb_d->read) {
        return p_usb_d->read(p_usb_d, ep, buff, len, sync);
    }
    return RET_ERR;
}

static inline int32 usb_device_ioctl(struct usb_device *p_usb_d, uint32 cmd, uint32 param)
{
    if (p_usb_d && p_usb_d->ioctl) {
        return p_usb_d->ioctl(p_usb_d, cmd, param);
    }
    return RET_ERR;
}

static inline int32 usb_device_request_irq(struct usb_device *p_usb_d, usbdev_irq_hdl handle, uint32 data)
{
    if (p_usb_d && p_usb_d->request_irq) {
        return p_usb_d->request_irq(p_usb_d, handle, data);
    }
    return RET_ERR;
}


#ifdef __cplusplus
}
#endif
#endif

