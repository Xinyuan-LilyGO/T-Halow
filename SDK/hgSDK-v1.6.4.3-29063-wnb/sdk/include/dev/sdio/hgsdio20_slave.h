#ifndef _HGSDIO20_SLAVE_H_
#define _HGSDIO20_SLAVE_H_
#include "hal/sdio_slave.h"

#ifdef __cplusplus
extern "C" {
#endif

enum hgsdio20_flags {
    hgsdio20_flags_ready,
    hgsdio20_flags_tx_start,
    hgsdio20_flags_txerr,
};

enum hgsdio20_speed_unit {
    hgsdio20_speedu_100Kbps = 0,
    hgsdio20_speedu_1Mbps   = 1,
    hgsdio20_speedu_10Mbps  = 2,
    hgsdio20_speedu_100Mbps = 3,
};

enum hgsdio20_speed_value {
    hgsdio20_speedv_1_0 = 1,
    hgsdio20_speedv_1_2 = 2,
    hgsdio20_speedv_1_3 = 3,
    hgsdio20_speedv_1_5 = 4,
    hgsdio20_speedv_2_0 = 5,
    hgsdio20_speedv_2_5 = 6,
    hgsdio20_speedv_3_0 = 7,
    hgsdio20_speedv_3_5 = 8,
    hgsdio20_speedv_4_0 = 9,
    hgsdio20_speedv_4_5 = 10,
    hgsdio20_speedv_5_0 = 11,
    hgsdio20_speedv_5_5 = 12,
    hgsdio20_speedv_6_0 = 13,
    hgsdio20_speedv_7_0 = 14,
    hgsdio20_speedv_8_0 = 15,
};

#define HGSDIO20_CISTPL_NULL            (0x0)
#define HGSDIO20_CISTPL_CHECKSUM        (0x10)
#define HGSDIO20_CISTPL_VERS_1          (0x15)
#define HGSDIO20_CISTPL_ALTSTR          (0x16)
#define HGSDIO20_CISTPL_MANFID          (0x20)
#define HGSDIO20_TPLMID_MANF            (0xA012)
#define HGSDIO20_TPLMID_CARD            (0x6001)

#define HGSDIO20_CISTPL_FUNCID          (0x21)
#define HGSDIO20_TPLFID_FUNCTION        (0xc)
#define HGSDIO20_TPLFID_SYSINIT         (0x0)


#define HGSDIO20_CISTPL_FUNCE           (0x22)
#define HGSDIO20_TPLFE_TYPE             (0x0)
#define HGSDIO20_TPLFE_FN0_BLK_SIZE     (0x800)
#define HGSDIO20_TPLFE_MAX_TRAN_SPEED   ((hgsdio20_speedv_5_0<<3)|hgsdio20_speedu_10Mbps)

#define HGSDIO20_TPLFE_TYPE1            (0x1)
#define HGSDIO20_TPLFE_FUNCTION_INFO    (0x1)
#define HGSDIO20_TPLFE_STD_IO_REV       (0x20)
#define HGSDIO20_TPLFE_CARD_PSN         (0x0)
#define HGSDIO20_TPLFE_CSA_SIZE         (0x0)

#define HGSDIO20_TPLFE_CSA_PROPERTY          (0x3)
#define HGSDIO20_TPLFE_MAX_BLK_SIZE          (0x800)
#define HGSDIO20_TPLFE_OCR                   (0x00ff8000)
#define HGSDIO20_TPLFE_OP_MIN_PWR            (0x8)
#define HGSDIO20_TPLFE_OP_AVG_PWR            (0xa)
#define HGSDIO20_TPLFE_OP_MAX_PWR            (0xf)
#define HGSDIO20_TPLFE_SB_MIN_PWR            (0x0)
#define HGSDIO20_TPLFE_SB_AVG_PWR            (0x0)
#define HGSDIO20_TPLFE_SB_MAX_PWR            (0x0)

#define HGSDIO20_TPLFE_MIN_BW                (0x0)
#define HGSDIO20_TPLFE_OPT_BW                (0x0)
#define HGSDIO20_TPLFE_ENABLE_TIMEOUT_VAL    (0x0)
#define HGSDIO20_TPLFE_SP_AVG_PWR_3_3V       (0x0)
#define HGSDIO20_TPLFE_SP_MAX_PWR_3_3V       (0x0)
#define HGSDIO20_TPLFE_HP_AVG_PWR_3_3V       (0x0)
#define HGSDIO20_TPLFE_HP_MAX_PWR_3_3V       (0x0)
#define HGSDIO20_TPLFE_LP_AVG_PWR_3_3V       (0x0)
#define HGSDIO20_TPLFE_LP_MAX_PWR_3_3V       (0x0)

#define HGSDIO20_CISTPL_SDIO_STD             (0x91)
#define HGSDIO20_TPLSDIO_STD_ID              (0x7)
#define HGSDIO20_TPLSDIO_STD_TYPE            (0x0)
#define HGSDIO20_TPLSDIO_STD_DATA            (0x0)


#define HGSDIO20_CISTPL_SDIO_EXT             (0x92)
#define HGSDIO20_END_OF_A_TUPLE_CHAIN        (0xff)

#define HGSDIO20_CCCR_REVISION(n)     (((n)&0xf) << 0)
#define HGSDIO20_SDIO_REVISION(n)     (((n)&0xf) << 4)
#define HGSDIO20_SD_REVISION(n)       (((n)&0xf) << 8)
#define HGSDIO20_IO_DEVICE_CODE1(n)   (((n)&0xf) << 12)
#define HGSDIO20_CSA_SURPPORT1                  (1 << 16)
#define HGSDIO20_EXTENDED_IO_DEVICE_CODE1(n)      ((n)&0xff) << 17)
#define HGSDIO20_SPS                  (1 << 25)
#define HGSDIO20_SHS                  (1 << 26)
#define HGSDIO20_SMPC                 (1 << 27)

#define HGSDIO20_FUNCTION_READY        (0x1)
#define HGSDIO20_FUN1_TX_READY         (0x2)

#define HGSDIO20_SCSI                  (0x4)
#define HGSDIO20_SDC                   (0x8)
#define HGSDIO20_SMB                   (0x10)
#define HGSDIO20_S4MI                  (0x80)
#define HGSDIO20_OCR                   (0xff8000)

#define HGSDIO20_CARD_RDY              (0x400)

#define HGSDIO20_RX_TRANS_OVER         (0x1)
#define HGSDIO20_TX_TRANS_OVER         (0x2)
#define HGSDIO20_TX_TRANS_ERR          (0x4)
#define HGSDIO20_RESET_SOFT_INT        (0x8)
#define HGSDIO20_FUN1_RESET_INT        (0x10)
#define HGSDIO20_RX_DMA_CPLT_INT       (0x20)
#define HGSDIO20_RX_DATA_CRC_ERR_INT   (0x40)

#define HGSDIO20_RX_INT_EN             (0x1)
#define HGSDIO20_TX_INT_EN             (0x2)
#define HGSDIO20_TX_ERR_INT_EN         (0x4)
#define HGSDIO20_SOFT_RST_INT_EN       (0x8)
#define HGSDIO20_FUN1_RST_INT_EN       (0x10)
#define HGSDIO20_RX_DMA_CPLT_INT_EN    (0x20)
#define HGSDIO20_RX_DAT_CRC_ERR_INT_EN (0x40)

#define HGSDIO20_VALID                 (0x1)

#if !defined (TX4001A)
#define HGSDIO20_MIX_FUNC_INTID_PATCH           (0x80000000)
#define HGSDIO20_MIX_FUNC_PENDING_PATCH         (0x40000000)
#define HGSDIO20_MIX_FUNC_SRW_PATCH             (0x20000000)

#define HGSDIO20_MIX_FUNC_RX_LEN_LIMIT_EN       (0x08000000)
#define HGSDIO20_MIX_FUNC_USER_REG2_HOSTINT_EN  (0x04000000)
#define HGSDIO20_MIX_FUNC_USER_REG1_HOSTINT_EN  (0x02000000)
#define HGSDIO20_MIX_FUNC_USER_REG0_HOSTINT_EN  (0x01000000)

#define HGSDIO20_USER_FUNC0_SET(dev, val) (dev)->USER_FUNC0=(val)
#define HGSDIO20_USER_FUNC1_SET(dev, val) (dev)->USER_FUNC1=(val)
#define HGSDIO20_USER_FUNC2_SET(dev, val) (dev)->USER_FUNC2=(val)
#else
#define HGSDIO20_USER_FUNC0_SET(dev, val)
#define HGSDIO20_USER_FUNC1_SET(dev, val)
#define HGSDIO20_USER_FUNC2_SET(dev, val)
#endif

struct hgsdio20_slave_hw {
    __IO uint32 DATA_PORT;
    __IO uint32 INT_ID;
    __IO uint32 CIS_FUNC0_ADDR;
    __IO uint32 CIS_FUNC1_ADDR;
    __IO uint32 CSA_ADDR;
    __IO uint32 READ_ADDR;
    __IO uint32 WRITE_ADDR;
    __IO uint32 AHB_TRANS_CNT;
    __IO uint32 SDIO_TRANS_CNT;
    __IO uint32 CIA;
    __IO uint32 PROGRAM;
    __IO uint32 INT_STATUS;
    __IO uint32 INT_ENABLE;
    __IO uint32 OCR;
    __IO uint32 CLK_WK;
    __IO uint32 AHB_BURST_SIZE;
    __IO uint32 AHB_SOFT_RESET;
    __IO uint32 SDIO_TRANS_ADDR;      /* RO: SDIO host cmd address */
#if !defined (TX4001A)
    __IO uint32 USER_FUNC0;           /* RW: user define register, RO for host */
    __IO uint32 USER_FUNC1;           /* RW: user define register, RO for host */
    __IO uint32 USER_FUNC2;           /* RW: user define register, RO for host */
    __IO uint32 MIX_FUNC3;            /* RW: user define register, -- for host */
    __IO uint32 DMA_CNT_CTRL;         /* RW: user define register, -- for host */
    __IO uint32 DMA_FINISH_CNT;       /* RW: user define register, -- for host */
    __I  uint32 FN1_BLOCK_SIZE;       /* RO: user define register, -- for host */
    __I  uint32 FN1_BLOCK_NUM;        /* RO: user define register, -- for host */
#endif
};

struct hgsdio20_slave {
    struct sdio_slave dev;
    struct hgsdio20_slave_hw *hw;
    sdio_slave_irq_hdl irq_hdl;
    uint32 irq_data;
    struct os_mutex tx_lock;
    struct os_semaphore tx_done;
    struct os_timer rst_timer;
    uint32 irq_num;
    uint32 rst_irq_num;
    uint8 *rx_buff;
    uint32 rx_len;
    uint32 opened:1, init:2 ;
    uint32 block_size;
    uint16 manufacture_id;
    uint16 device_id;
    enum sdio_slave_speed speed;
    //uint8  func0_cis[20];
    //uint8  func1_cis[56];
    uint8 *  func0_cis;
    uint8 *  func1_cis;
    uint32 flags;
    uint64 active_tick;
    uint32 reset_cnt;
};

int32 hgsdio20_slave_attach(uint32 dev_id, struct hgsdio20_slave *slave);

#ifdef __cplusplus
}
#endif

#endif /* _HGSDIO20_SLAVE_H_ */

