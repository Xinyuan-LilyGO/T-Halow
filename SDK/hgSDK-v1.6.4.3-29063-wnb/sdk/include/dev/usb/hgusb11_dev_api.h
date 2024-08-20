#ifndef USB_DEV_API_H
#define USB_DEV_API_H

/// include & define here
#include "hal/usb_device.h"
#include "dev/usb/hgusb11_base.h"
#include "dev/usb/hgusb11_dev_ep0.h"

#ifdef __cplusplus
extern "C" {
#endif
/// extern declare functions here

enum hgusb11_flags {
    HGUSB11_FLAGS_READY,
};

struct hgusb11_hw_dma_st {
    __IO uint32_t EP_TXSTARTADR;
    __IO uint32_t EP_RXSTARTADR;
    __IO uint32_t EP_TXLEN;
    __IO uint32_t EP_RXLEN;
} ;

struct hgusb11_hw_dma_end {
    __I  uint32_t EP_TXADR;
    __I  uint32_t EP_RXADR;
} ;

/**
  * @brief USB2.0
  */

struct hgusb11_dev_hw {
    /* SIE common reg : 0x0 ~ 0xf */
    __IO uint8_t  SIEM_FADDR;
    __IO uint8_t  SIEM_POWER;
    __IO uint8_t  SIEM_INTRTX1;
    __IO uint8_t  SIEM_INTRTX2;
    __IO uint8_t  SIEM_INTRRX1;
    __IO uint8_t  SIEM_INTRRX2;
    __IO uint8_t  SIEM_INTRUSB;
    __IO uint8_t  SIEM_INTRTX1E;
    __IO uint8_t  SIEM_INTRTX2E;
    __IO uint8_t  SIEM_INTRRX1E;
    __IO uint8_t  SIEM_INTRRX2E;
    __IO uint8_t  SIEM_INTRUSBE;
    __IO uint8_t  SIEM_FRAMENUM1;
    __IO uint8_t  SIEM_FRAMENUM2;
    __IO uint8_t  SIEM_INDEX;
    __IO uint8_t  SIEM_DEVCTL;

    /* SIE indexed reg : 0x10 ~ 0x1f */
    __IO uint8_t  SIEM_TXMAXP;
    __IO uint8_t  SIEM_TXCSR1;
    __IO uint8_t  SIEM_TXCSR2;
    __IO uint8_t  SIEM_RXMAXP;
    __IO uint8_t  SIEM_RXCSR1;
    __IO uint8_t  SIEM_RXCSR2;
    __IO uint8_t  SIEM_RXCOUNT1;
    __IO uint8_t  SIEM_RXCOUNT2;
    __IO uint8_t  SIEM_TXTYPE;
    __IO uint8_t  SIEM_TXINTERVAL;
    __IO uint8_t  SIEM_RXTYPE;
    __IO uint8_t  SIEM_RXINTERVAL;
    uint8_t  SIEreserved0[3];
    __IO uint8_t  SIEM_FIFOSIZE;

    /* SIE common reg : 0x20 ~ 0x2f */
    __IO uint8_t  SIEM_FIFO0;
    uint8_t  SIEreserved1[3];
    __IO uint8_t  SIEM_FIFO1;
    uint8_t  SIEreserved2[3];
    __IO uint8_t  SIEM_FIFO2;
    uint8_t  SIEreserved3[3 + 4];

    uint8_t  rsv0[0x200 - 0x30];

    /* DMA common reg */
    __IO uint32_t DMA_INT;         ///0x200
    __IO uint32_t DMA1_CTL;
    __IO uint32_t DMA1_ADDR;
    __IO uint32_t DMA1_CNT;
    uint32_t rsv1;
    __IO uint32_t DMA2_CTL;
    __IO uint32_t DMA2_ADDR;
    __IO uint32_t DMA2_CNT;
    uint32_t rsv2;
    __IO uint32_t DMA3_CTL;
    __IO uint32_t DMA3_ADDR;
    __IO uint32_t DMA3_CNT;
    uint32_t rsv3;
    __IO uint32_t DMA4_CTL;
    __IO uint32_t DMA4_ADDR;
    __IO uint32_t DMA4_CNT;

    uint32_t rsv4[0x100 / 4 - 16];

    /* CPU common reg */
    __IO uint32_t UCFG0;         ///0x300
    __IO uint32_t UCFG1;
    __IO uint32_t UCFG2;
    __IO uint32_t UCFG3;


    __IO uint32_t EP_STATUS;
    __IO uint32_t EP_KICK;
    __IO uint32_t EP_CTL;
    uint32_t rsv5;
    __IO uint32_t EP0_TXSTARTADR;
    __IO uint32_t EP0_RXSTARTADR;
    __IO uint32_t EP0_TXLEN;
    uint32_t rsv6;
    __IO uint32_t EP1_TXSTARTADR;
    __IO uint32_t EP1_RXSTARTADR;
    __IO uint32_t EP1_TXLEN;
    __IO uint32_t EP1_RXLEN;

    __IO uint32_t EP2_TXSTARTADR;
    __IO uint32_t EP2_RXSTARTADR;
    __IO uint32_t EP2_TXLEN;
    __IO uint32_t EP2_RXLEN;

    __I uint32_t  EP0_TXADR;
    __I uint32_t  EP0_RXADR;

    __I uint32_t  EP1_TXADR;
    __I uint32_t  EP1_RXADR;

    __I uint32_t  EP2_TXADR;
    __I uint32_t  EP2_RXADR;

} ;

struct hgusb11_dev {
    struct usb_device       dev;
    struct hgusb11_dev_hw *usb_hw;
    long                    flags;
    usbdev_irq_hdl          irq_hdl;
    struct os_mutex         tx_lock;
    struct os_semaphore     tx_done;
    uint32                  irq_num;
    uint32                  sof_irq_num;
    uint8                  *rx_buff;
    uint32                  rx_len;
    uint32                  opened;
    uint32                  irq_data;
    struct usb_device_cfg   cfg;
    struct os_task          ep0_task;
    struct os_semaphore     ep0_sema;

    /* basic */
    struct hgusb11_dev_chk     usb_chk;
    struct hgusb11_dev_ctrl    usb_ctrl;
    struct hgusb11_dev_info    usb_dev;
    struct hgusb11_audio_ctrl  usb_audio_ctl;
    uint32_t                usb_dma_int;
    uint8_t                 dev_type;
    uint8_t                 usb_exit ;
    uint8_t                 usb_dev_flag ;
    uint8_t                 usb_ep0buf[66];
    uint8_t                 usb_ep0_rxbuf[66];
    uint8_t                 usb_device_descriptor[18];
    uint8_t                 usb_device_qualifier[10];
    uint8_t                 usb_config_all_descriptor[512];
};

/* hgusb11_base */
void hgusb11_switch_otg(struct hgusb11_dev *p_dev);
void hgusb11_switch_host(struct hgusb11_dev *p_dev);
void hgusb11_switch_stable_host(struct hgusb11_dev *p_dev);
void hgusb11_switch_stable_device(struct hgusb11_dev *p_dev);
void hgusb11_switch_stable_otg(struct hgusb11_dev *p_dev);
uint8_t hgusb11_connected(struct hgusb11_dev *p_dev);
uint8_t hgusb11_connected_do(struct hgusb11_dev *p_dev);
void hgusb11_intr_dis(struct hgusb11_dev *p_dev);
void hgusb11_suspend(struct hgusb11_dev *p_dev);
void hgusb11_resume(struct hgusb11_dev *p_dev);
void hgusb11_init_globle(struct hgusb11_dev *p_dev);



/* hgusb11_dev_ep0 */
bool hgusb11_dev_init(struct hgusb11_dev *p_dev);
void hgusb11_dev_ep0_func(struct hgusb11_dev *p_dev);
void hgusb11_dev_intr_init_b(struct hgusb11_dev *p_dev);
void hgusb11_dev_exit(struct hgusb11_dev *p_dev);
void hgusb11_dev_reset(struct hgusb11_dev *p_dev);



/* hgusb11_dev_api */
int32 hgusb11_dev_attach(uint32 dev_id, struct hgusb11_dev *p_dev);
void hgusb11_dev_irq(struct hgusb11_dev *p_dev);
bool hgusb11_dev_ep_rx_kick(struct hgusb11_dev *p_dev, uint8_t ep, uint32_t addr, uint32_t len);
bool hgusb11_dev_ep_tx_kick(struct hgusb11_dev *p_dev, uint8_t ep, uint32_t addr, uint32_t len);
void hgusb11_dev_ep_set_rxrdy(struct hgusb11_dev *p_dev, uint8_t ep);
void hgusb11_dev_ep_set_txrdy(struct hgusb11_dev *p_dev, uint8_t ep);
void hgusb11_dev_hw_init(struct hgusb11_dev *p_dev);
uint32_t hgusb11_dev_ep_get_rx_len(struct hgusb11_dev *p_dev, uint8_t ep);
uint32_t hgusb11_dev_ep_get_tx_len(struct hgusb11_dev *p_dev, uint8_t ep);


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif



#endif /* USB_DEV_API_H */
