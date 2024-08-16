#ifndef _HG_TDMA_DEVICE_H_
#define _HG_TDMA_DEVICE_H_


#ifdef __cplusplus
extern "C" {
#endif

#define TDMA_CTRL_START_MSK     BIT(0)
#define TDMA_CTRL_ABORT_MSK     BIT(1)
#define TDMA_CTRL_MODE_MSK      BIT(2)
#define TDMA_CTRL_IRQ_EN_MSK    BIT(3)
#define TDMA_CTRL_RELD_MSK      BIT(4)
#define TDMA_STATUS_PD_MSK      BIT(0)
#define TDMA_LEN_MSK            0x000FFFFF
#define TDMA_TRLEN_MSK          0x000FFFFF

/**
  * @breif huge-ic TDMA register definition
  */
struct hgtdma_hw {
    __IO uint32 TDMA_CTRL;
    __IO uint32 TDMA_STATUS;
    __IO uint32 TDMA_STADDR;
    __IO uint32 TDMA_LEN;
    __I  uint32 TDMA_REM;
    __IO uint32 TDMA_TRLEN;
    __I  uint32 TDMA_TRADDR;
};

struct hgtdma {
    struct tdma_device dev;
    struct hgtdma_hw *hw;
    uint32 irq_num;
};

int32 hgtdma_attach(uint32 dev_id, struct hgtdma *tdma);

#ifdef __cplusplus
}
#endif


#endif



