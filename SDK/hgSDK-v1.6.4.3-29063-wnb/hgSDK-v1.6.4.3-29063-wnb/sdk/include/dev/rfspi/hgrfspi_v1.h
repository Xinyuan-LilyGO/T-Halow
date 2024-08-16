#ifndef _HGRFSPI_V1_DEVICE_H_
#define _HGRFSPI_V1_DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define RF_SPI_OP_MODE_MSK           BIT(0)
#define CLOCK_FREQ_SEL_MSK           BIT(1)
#define TVER_MSK                     BIT(7)
#define RST_MSK                      BIT(8)
#define CLKOUT_MSK                   BIT(9)
#define RX_DLY_SHIFT                 12
#define RX_DLY_MSK                  (0xf<<RX_DLY_SHIFT)               //only valid in tx4001
#define RF_SPI_PD_MSK                BIT(31)
#define RF_SPI_WR_IND_MSK            BIT(31)
#define RF_SPI_ADDR_SHIFT            16
#define RF_SPI_ADDR_MSK             (0x7fffUL<<RF_SPI_ADDR_SHIFT)
#define RF_SPI_WDATA_SHIFT           0
#define RF_SPI_WDATA_MSK            (0xffff<<RF_SPI_WDATA_SHIFT)
#define RF_SPI_RDATA_SHIFT           0
#define RF_SPI_RDATA_MSK            (0x0000ffff<<RF_SPI_RDATA_SHIFT)

#define READ_IND                     0
#define WRITE_IND                    BIT(31)


/**
  * @breif huge-ic RF_SPI_V1 register definition
  */
struct hgrfspi_v1_hw {
    __IO uint32 SPI_CFG;
    __IO uint32 SPI_WDATA;
    __I  uint32 SPI_RDATA;
};

struct hgrfspi_v1 {
    struct rfspi_device dev;
    struct hgrfspi_v1_hw *hw;
    uint32 opened;
    uint8  rx_dly;
};

int32 hgrfspi_v1_attach(uint32 dev_id, struct hgrfspi_v1 *rfspi);

#ifdef __cplusplus
}
#endif


#endif



