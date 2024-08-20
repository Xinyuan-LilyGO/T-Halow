#ifndef _HGSPI_DW_H_
#define _HGSPI_DW_H_
#include "hal/spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* DW SPI has no CS line. Need to be simulated with GPIO. */
#define HGSPI_DW_CS_GPIO            PIN_SPI0_CS
    
/** @brief DW SPI register structure
  * @{
  */
struct hgspi_dw_hw {
    /*!< Control Register */
    /*!< SPI Control Register 0  (0x0) */
    __IO uint32 CTRLR0;
    /*!< SPI Control Register 1  (0x4) */
    __IO uint32 CTRLR1;
    /*!< Enable Register */
    /*!< SPI Enable Register  (0x8) */
    __IO uint32 SSIENR;
    /*!< SPI Microwire Control Register  (0xC) */
    __IO uint32 MWCR;
    /*!< SPI Slave Enable Register  (0x10) */
    __IO uint32 SER;
    /*!< SPI Baud Rate Select Register  (0x14) */
    __IO uint32 BAUDR;
    /*!< TX and RX FIFO Control Register */
    /*!< SPI Transmit FIFO Threshold Level Register  (0x18) */
    __IO uint32 TXFTLR;
    /*!< SPI Receive  FIFO Threshold Level Register  (0x1C) */
    __IO uint32 RXFTLR;
    /*!< SPI Transmit FIFO Level Register  (0x20) */
    __IO uint32 TXFLR;
    /*!< SPI Receive  FIFO Level Register  (0x24) */
    __IO uint32 RXFLR;
    /*!< SPI Status   Register  (0x28) */
    __IO uint32 SR;
    /*!< Interrupt Enable/Disable/Control Registers */
    /*!< SPI Interrupt Mask Register  (0x2C) */
    __IO uint32 IMR;
    /*!< SPI Interrupt Status Register  (0x30) */
    __IO uint32 ISR;
    /*!< SPI Raw Interrupt Status Register (0x34) */
    __IO uint32 RISR;
    /*!< SPI Transmit FIFO Overflow Interrupt Clear Register  (0x38) */
    __IO uint32 TXOICR;
    /*!< SPI Receive  FIFO Overflow Interrupt Clear Register  (0x3C) */
    __IO uint32 RXOICR;
    /*!< SPI Receive FIFO Underflow Interrupt Clear Register  (0x40) */
    __IO uint32 RXUICR;
    /*!< SPI Multi-Master Interrupt Clear Register  (0x44) */
    __IO uint32 MSTICR;
    /*!< SPI Interrupt Clear Register  (0x48) */
    __IO uint32 ICR;
    /*!< DMA Control Register  (0x4C) */
    __IO uint32 DMACR;
    /*!< DMA Transmit Data Level  (0x50) */
    __IO uint32 DMATDLR;
    /*!< DMA Receive Data Level  (0x54) */
    __IO uint32 DMARDLR;
    /*!< SPI Identification Register  (0x58) */
    __IO uint32 IDR;
    /*!< SPI CoreKit ID Register (Value after Reset : 0x3332322A)  (0x5C) */
    __IO uint32 SSI_VER_ID;
    /*!< Data Register */
    /*!< SPI DATA Register for both Read and Write  (0x60) */
    __IO uint32 DATAREG;
    
    __IO uint32 FIFO[0x23];
    
    __IO uint32 RX_SAMPLE_DLY;
    __IO uint32 SPICTRLR0;
};

struct hgspi_dw {
    struct spi_device       dev;
    struct hgspi_dw_hw     *hw;
    uint32                  irq_num;
    spi_irq_hdl             irq_hdl;
    uint32                  irq_data;
    uint32                  opened;
    uint8                   cs_pin[5]; /*cs gpio pin, max support 4 cs; cs_pin[0] is cs count*/
    /* The following variables are used for dma operations */
    struct dma_device      *dma;
    struct os_semaphore     tx_dma_sema;
    struct os_semaphore     rx_dma_sema;
};

/**
  * @}
  */

/** @defgroup SPI_Register_Constants SPI Register Constants
  * @ingroup  SPI_Driver
  * @brief    SPI register constant table definition
  *
  * @{
  */

/**
  * if this header file is included,
  * will indicate that this designware spi device
  * is used
  */
#define HGSPI_DW_MASTER_SUPPORTED           (0x1)   /*!< Support Designware SPI Master Mode */
#define HGSPI_DW_SLAVE_SUPPORTED            (0x2)   /*!< Support Designware SPI Slave Mode */
/*!< Support Designware SPI Both Master and Slave Mode */
#define HGSPI_DW_BOTH_SUPPORTED             (HGSPI_DW_MASTER_SUPPORTED|HGSPI_DW_SLAVE_SUPPORTED)

#ifndef HGSPI_DW_CALC_FIFO_LEN_ENABLE
#define HGSPI_DW_CALC_FIFO_LEN_ENABLE       (1) /*!< Defaultly enable calculate fifo length */
#endif

#ifndef HGSPI_DW_MAX_FIFO_LENGTH
#define HGSPI_DW_MAX_FIFO_LENGTH            (256)   /*!< Max FIFO depth for designware SPI device */
#endif

#ifndef HGSPI_DW_MIN_FIFO_LENGTH
#define HGSPI_DW_MIN_FIFO_LENGTH            (2) /*!< Min FIFO depth for designware SPI device */
#endif


/**
  * @name    DesignWare SPI HAL CTRL0 Macros
  * @brief   DesignWare SPI hal ctrl0 macros,
  *  include dfs, scph, scppl, tmod, etc
  * @{
  */
#define HGSPI_DW_CTRLR0_DFS_MASK            (0xf)

#define HGSPI_DW_CTRLR0_SC_OFS              (6)
#define HGSPI_DW_CTRLR0_SC_MASK             (0xC0)
#define HGSPI_DW_CTRLR0_SCPH_HIGH           (0x40)
#define HGSPI_DW_CTRLR0_SCPH_LOW            (0)
#define HGSPI_DW_CTRLR0_SCPOL_HIGH          (0x80)
#define HGSPI_DW_CTRLR0_SCPOL_LOW           (0)

#define HGSPI_DW_CTRLR0_FRF_MOTOROLA        (0x0)
#define HGSPI_DW_CTRLR0_FRF_TI              (0x10)
#define HGSPI_DW_CTRLR0_FRF_MICROWIRE       (0x20)

#define HGSPI_DW_CTRLR0_SLV_OE_DISABLE      (1<<10)
#define HGSPI_DW_CTRLR0_SLV_OE_ENABLE       (0)


/**
  * @}
  */

/**
  * @name    DesignWare SPI HAL ISR Flags
  * @brief   DesignWare SPI hal Interrupt Status Flags
  * @{
  */
#define HGSPI_DW_TX_OVERFLOW_ERROR          (0x2)
#define HGSPI_DW_RX_UNDERFLOW_ERROR         (0x4)
#define HGSPI_DW_RX_OVERFLOW_ERROR          (0x8)

#define HGSPI_DW_ISR_RX_FIFO_INT_MASK       (0x10)
#define HGSPI_DW_ISR_TX_FIFO_INT_MASK       (0x1)
#define HGSPI_DW_ISR_TX_OVERFLOW_INT_MASK   (0x2)
#define HGSPI_DW_ISR_RX_UNDERFLOW_INT_MASK  (0x4)
#define HGSPI_DW_ISR_RX_OVERFLOW_INT_MASK   (0x8)
/**
  * @}
  */

/**
  * @name    DesignWare SPI HAL SR Flags
  * @brief   DesignWare SPI hal Status Flags
  * @{
  */
#define HGSPI_DW_SR_DCOL                    (0x40)
#define HGSPI_DW_SR_TXE                     (0x20)
#define HGSPI_DW_SR_RFF                     (0x10)
#define HGSPI_DW_SR_RFNE                    (0x8)
#define HGSPI_DW_SR_TFE                     (0x4)
#define HGSPI_DW_SR_TFNF                    (0x2)
#define HGSPI_DW_SR_BUSY                    (0x1)
/**
  * @}
  */

/**
  * @name    DesignWare SPI DMACR
  * @brief   DesignWare SPI DMA control register
  * @{
  */
#define HGSPI_DW_DMACR_RDMAE_EN             (0x01)
#define HGSPI_DW_DMACR_TDMAE_EN             (0x02)
/**
  * @}
  */

/**
  * @name    DesignWare SPI HAL SSI Enable Macros
  * @brief   DesignWare SPI hal ssi enable macros
  * @{
  */
#define HGSPI_DW_SSI_ENABLE                 (1) /*!< SSI Enable */
#define HGSPI_DW_SSI_DISABLE                (0) /*!< SSI Disable */
/**
  * @}
  */

#define HGSPI_DW_SSI_IDLE                   (1)
#define HGSPI_DW_SPI_TRANSMIT               (1)
#define HGSPI_DW_SPI_RECEIVE                (2)
#define HGSPI_DW_SSI_MASTER                 (1)
#define HGSPI_DW_SSI_SLAVE                  (0)

/**
  * @brief   DesignWare SPI driver macros used in spi driver
  */
/** convert DesignWare frequence to divisor */
#define HGSPI_DW_FREQ2DV(perifreq, spifreq)       ((perifreq) / (spifreq))


/**
  * @brief   DesignWare SPI interrupt callback routines select macros definitions
  */
#define HGSPI_DW_RDY_SND                    (1U)    /*!< ready to send callback */
#define HGSPI_DW_RDY_RCV                    (2U)    /*!< ready to receive callback */
#define HGSPI_DW_RDY_XFER                   (3U)    /*!< ready to transfer callback */

/**
  * @}
  */

/** @defgroup HGSPI_DW_Exported_Constants SPI Exported Constants
  * @ingroup  HGSPI_DW_Driver
  * @brief    SPI external constant definition
  * @{
  */

/**
  * @brief SPI wire mode enum type, consistent with the spec definition
  */
enum hgspi_dw_wire_mode {
    /*! The effective bus of the SPI module is CS, CLK, MOSI, MISO.
     */
    HGSPI_DW_NORMAL_MODE                = 0,
    /*! The active bus of the SPI module is CS, CLK, IO0, IO1. Among them IO0
     *  and IO1 are bidirectional IO.
     */
    HGSPI_DW_DUAL_MODE                  = 1,
    /*! The active bus of the SPI module is CS, CLK, IO0, IO1, IO2, IO3. Among
     *  them, IO0 to IO4 are bidirectional IO.
     */
    HGSPI_DW_QUAD_MODE                  = 2,
};

/**
  * @brief SPI mode enum type, consistent with the spec definition.
  * @note SPI_MODE_0 represents the first valid rising edge to start data acquisition.
  *       SPI_MODE_1 represents the second valid falling edge to start data acquisition.
  *       SPI_MODE_2 represents the first valid falling edge to start data acquisition.
  *       SPI_MODE_3 represents the second valid rising edge to start data acquisition.
  */
  
#define HGSPI_DW_CTRLR0_SC_MASK           (0xC0)
/** SPI Clock Mode */
enum hgspi_dw_clk_mode {
    HGSPI_DW_CPOL_0_CPHA_0 = 0,  /*!< Inactive state of serial clock is low, serial clock toggles in middle of first data bit */
    HGSPI_DW_CPOL_0_CPHA_1 = 1,  /*!< Inactive state of serial clock is low, serial clock toggles at start of first data bit  */
    HGSPI_DW_CPOL_1_CPHA_0 = 2,  /*!< Inactive state of serial clock is high, serial clock toggles in middle of first data bit */
    HGSPI_DW_CPOL_1_CPHA_1 = 3,  /*!< Inactive state of serial clock is high, serial clock toggles at start of first data bit */

    HGSPI_DW_CLK_MODE_0    = HGSPI_DW_CPOL_0_CPHA_0,  /*!< Equal to \ref SPI_CPOL_0_CPHA_0 */
    HGSPI_DW_CLK_MODE_1    = HGSPI_DW_CPOL_0_CPHA_1,  /*!< Equal to \ref SPI_CPOL_0_CPHA_1 */
    HGSPI_DW_CLK_MODE_2    = HGSPI_DW_CPOL_1_CPHA_0,  /*!< Equal to \ref SPI_CPOL_1_CPHA_0 */
    HGSPI_DW_CLK_MODE_3    = HGSPI_DW_CPOL_1_CPHA_1   /*!< Equal to \ref SPI_CPOL_1_CPHA_1 */
};

#define HGSPI_DW_CTRLR0_TMOD_MASK      (0x300)
enum hgspi_dw_mode {
    HGSPI_DW_TMOD_TRANSMIT_RECEIVE =       (0),
    HGSPI_DW_TMOD_TRANSMIT_ONLY    =   (0x100),
    HGSPI_DW_TMOD_RECEIVE_ONLY     =   (0x200),
    HGSPI_DW_TMOD_EEPROM_READ_ONLY =   (0x300),
};

enum hgspi_dw_int_msk {
    HGSPI_DW_IMR_FINISH    =       (0x40),  /*!< Completion of sequential transmission, when CS is pulled up, the interrupt is triggered. */
    HGSPI_DW_IMR_MSTIM     =       (0x20),  /*!< Multi-Master Contention Interrupt Mask */
    HGSPI_DW_IMR_RXFIM     =       (0x10),  /*!< Receive FIFO Full Interrupt Mask */
    HGSPI_DW_IMR_RXOIM     =       (0x08),  /*!< Receive FIFO Overflow Interrupt Mask */
    HGSPI_DW_IMR_RXUIM     =       (0x04),  /*!< Receive FIFO Underflow Interrupt Mask */
    HGSPI_DW_IMR_TXOIM     =       (0x02),  /*!< Transmit FIFO Overflow Interrupt Mask */
    HGSPI_DW_IMR_TXEIM     =       (0x01),  /*!< Transmit FIFO Empty Interrupt Mask */

    HGSPI_DW_IMR_XFER      =       (HGSPI_DW_IMR_TXEIM | HGSPI_DW_IMR_RXFIM |
                                    HGSPI_DW_IMR_TXOIM | HGSPI_DW_IMR_RXOIM |
                                    HGSPI_DW_IMR_RXUIM)
};

/**
  * @}
  */

int32 dmac_search_src_id(uint32 addr);
int32 dmac_search_dest_id(uint32 addr);
int32 hgspi_dw_attach(uint32 dev_id, struct hgspi_dw *p_spi);

#ifdef __cplusplus
}
#endif

#endif /* _HGSPI_DW_H_ */
