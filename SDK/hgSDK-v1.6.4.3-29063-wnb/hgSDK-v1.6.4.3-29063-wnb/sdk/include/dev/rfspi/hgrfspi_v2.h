#ifndef _HGRFSPI_V2_DEVICE_H_
#define _HGRFSPI_V2_DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

// Register Address: 'h0000
#define SPI_CFG_SPI_ENDIRQ_EN_MSK                    0x08000000
#define SPI_CFG_SPI_ENDIRQ_EN_SHIFT                  27
#define SPI_CFG_RXSEL_MSK                            0x07000000
#define SPI_CFG_RXSEL_SHIFT                          24
#define SPI_CFG_DIV_CNT_MSK                          0x00ff0000
#define SPI_CFG_DIV_CNT_SHIFT                        16
#define SPI_CFG_SPI_TDRQ_EN_MSK                      0x00008000
#define SPI_CFG_SPI_TDRQ_EN_SHIFT                    15
#define SPI_CFG_SPI_RDRQ_EN_MSK                      0x00004000
#define SPI_CFG_SPI_RDRQ_EN_SHIFT                    14
#define SPI_CFG_SPI_TIRQ_EN_MSK                      0x00002000
#define SPI_CFG_SPI_TIRQ_EN_SHIFT                    13
#define SPI_CFG_SPI_RIRQ_EN_MSK                      0x00001000
#define SPI_CFG_SPI_RIRQ_EN_SHIFT                    12
#define SPI_CFG_TX_BUS_SEL_MSK                       0x00000800
#define SPI_CFG_TX_BUS_SEL_SHIFT                     11
#define SPI_CFG_RX_BUS_SEL_MSK                       0x00000400
#define SPI_CFG_RX_BUS_SEL_SHIFT                     10
#define SPI_CFG_TXFIFOEN_MSK                         0x00000200
#define SPI_CFG_TXFIFOEN_SHIFT                       9
#define SPI_CFG_RXFIFOEN_MSK                         0x00000100
#define SPI_CFG_RXFIFOEN_SHIFT                       8
#define SPI_CFG_DFS_MSK                              0x000000c0
#define SPI_CFG_DFS_SHIFT                            6
#define SPI_CFG_WIREMODE_MSK                         0x00000030
#define SPI_CFG_WIREMODE_SHIFT                       4
#define SPI_CFG_SPIMODE_MSK                          0x0000000c
#define SPI_CFG_SPIMODE_SHIFT                        2
#define SPI_CFG_HARDTRIG_MSK                         0x00000002
#define SPI_CFG_HARDTRIG_SHIFT                       1
#define SPI_CFG_SLAVE_MSK                            0x00000001
#define SPI_CFG_SLAVE_SHIFT                          0

// Register Address: 'h0004
#define SPI_CTL_SPI_NSS_MSK                          0x00000008
#define SPI_CTL_SPI_NSS_SHIFT                        3
#define SPI_CTL_RFSPI_MFP_MSK                        0x00000004
#define SPI_CTL_RFSPI_MFP_SHIFT                      2
#define SPI_CTL_SPIEN_MSK                            0x00000003
#define SPI_CTL_SPIEN_SHIFT                          0

// Register Address: 'h0008
#define SPI_RX_BC_RX_BC_STA_MSK                      0xffff0000
#define SPI_RX_BC_RX_BC_STA_SHIFT                    16
#define SPI_RX_BC_RX_BC_CFG_MSK                      0x0000ffff
#define SPI_RX_BC_RX_BC_CFG_SHIFT                    0

// Register Address: 'h000c
#define SPI_STA_SPI_END_PEND_MSK                     0x00000400
#define SPI_STA_SPI_END_PEND_SHIFT                   10
#define SPI_STA_TX_IRQ_PEND_MSK                      0x00000200
#define SPI_STA_TX_IRQ_PEND_SHIFT                    9
#define SPI_STA_RX_IRQ_PEND_MSK                      0x00000100
#define SPI_STA_RX_IRQ_PEND_SHIFT                    8
#define SPI_STA_TX_FIFO_FULL_MSK                     0x00000080
#define SPI_STA_TX_FIFO_FULL_SHIFT                   7
#define SPI_STA_TX_FIFO_EMPTY_MSK                    0x00000040
#define SPI_STA_TX_FIFO_EMPTY_SHIFT                  6
#define SPI_STA_RX_FIFO_FULL_MSK                     0x00000020
#define SPI_STA_RX_FIFO_FULL_SHIFT                   5
#define SPI_STA_RX_FIFO_EMPTY_MSK                    0x00000010
#define SPI_STA_RX_FIFO_EMPTY_SHIFT                  4
#define SPI_STA_TX_FIFO_ERROR_MSK                    0x00000008
#define SPI_STA_TX_FIFO_ERROR_SHIFT                  3
#define SPI_STA_RX_FIFO_ERROR_MSK                    0x00000004
#define SPI_STA_RX_FIFO_ERROR_SHIFT                  2
#define SPI_STA_SPI_BUSY_MSK                         0x00000001
#define SPI_STA_SPI_BUSY_SHIFT                       0

// Register Address: 'h0020
#define SPI_TX_BC_TX_BC_STA_MSK                      0xffff0000
#define SPI_TX_BC_TX_BC_STA_SHIFT                    16
#define SPI_TX_BC_TX_BC_CFG_MSK                      0x0000ffff
#define SPI_TX_BC_TX_BC_CFG_SHIFT                    0


#define ZH_RFSPI_MSTR_MOD                            0

#define MODE_0                                     ((uint32)0 << 2)
#define MODE_1                                     ((uint32)1 << 2)
#define MODE_2                                     ((uint32)2 << 2)
#define MODE_3                                     ((uint32)3 << 2)

#define NORM_WIRE                                  ((uint32)0 << 4)
#define TRI3_WIRE                                  ((uint32)1 << 4)
#define DUAL_WIRE                                  ((uint32)2 << 4)
#define QUAD_WIRE                                  ((uint32)3 << 4)

#define DFS_08_BIT                                 ((uint32)0 << 6)
#define DFS_16_BIT                                 ((uint32)1 << 6)
#define DFS_24_BIT                                 ((uint32)2 << 6)
#define DFS_32_BIT                                 ((uint32)3 << 6)

#define DMA_08_BIT                                 ((uint32)0 << 28)
#define DMA_16_BIT                                 ((uint32)1 << 28)
#define DMA_24_BIT                                 ((uint32)2 << 28)
#define DMA_32_BIT                                 ((uint32)3 << 28)

#define DFLT_DIV_CNT                               ((uint32)0xf << 16)

#define DFLT_RX_DELAY                              ((uint32)0x4 << 24)

#define MODE_DISABLE                                 0
#define MODE_RX_ONLY                                 1
#define MODE_TX                                      2
#define MODE_TX_RX                                   3


#define READ_IND                                     0
#define WRITE_IND                                    BIT(31)


/**
  * @breif huge-ic RFSPI_V2 register definition
  */
struct hgrfspi_v2_hw {
    __IO uint32 SPI_CFG;
    __IO uint32 SPI_CTL;
    __IO uint32 SPI_RX_BC;
    __IO uint32 SPI_STA;
    __IO uint32 SPI_WDATA;
    __I  uint32 SPI_RDATA;
    __IO uint32 DMA_TX_ADDR;
    __IO uint32 DMA_RX_ADDR;
    __IO uint32 SPI_TX_BC;
    __IO uint32 SPI_TX_START;
    __IO uint32 SPI_RX_START;
};

struct hgrfspi_v2 {
    struct rfspi_device dev;
    struct hgrfspi_v2_hw *hw;
    uint32 opened;
    uint32 tx_data;
    uint16 rx_data;
    uint8  rx_dly;
};

int32 hgrfspi_v2_attach(uint32 dev_id, struct hgrfspi_v2 *rfspi);

#ifdef __cplusplus
}
#endif


#endif



