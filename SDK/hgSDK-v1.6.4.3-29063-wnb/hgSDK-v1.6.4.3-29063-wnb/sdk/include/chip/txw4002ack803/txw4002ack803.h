#ifndef _TXW4002A_DEF_H_
#define _TXW4002A_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LSP_DEFAULT_FREQ
#define  LSP_DEFAULT_FREQ    (20000000)
#endif

/* -------------------------  Interrupt Number Definition  ------------------------ */

enum IRQn
{
    /* ----------------------  SmartL Specific Interrupt Numbers  --------------------- */
    IIC0_IRQn,          // 32
    UART0_IRQn,         // 33
    UART1_IRQn,         // 34
    SPI0_IRQn,          // 35
    SPI1_IRQn,          // 36
    SPI3_IRQn,          // 37
    WDT_IRQn,           // 38
    ADKEY_IRQn,         // 39
    DMAC_IRQn,          // 40
    GPIOA_IRQn,         // 41
    TIM0_IRQn,          // 42
    TIM1_IRQn,          // 43
    TIM2_IRQn,          // 44
    TIM3_IRQn,          // 45
    HGSDIO20_IRQn,      // 46
    PD_TMR_IRQn,        // 47
    TDMA_IRQn,          // 48
    GMAC_IRQn,          // 49
    USB_CTL_IRQn,       // 50
    USB_SOF_IRQn,       // 51
    CE_IRQn,            // 52
    CORET_IRQn,         // 53 for CK803, it's C-timer
    GPIOB_IRQn,         // 54
    LMAC_IRQn,          // 55
    CRC_IRQn,           // 56
    WKPND_IRQn,         // 57
    HGSDIO20_RST_IRQn,  // 58
    SYS_ERR_IRQn,       // 59
    LVD_IRQn,           // 60
    SYS_AES_IRQn,       // 61
    ZH_RFSPI_IRQn,      // 62
    MIPI_IRQn,          // 63
    IRQ_NUM,
} IRQn_Type;


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* --------  Configuration of the CK803 Processor and Core Peripherals  ------- */
#define __CK803_REV               0x0000U   /* Core revision r0p0 */
#define __MPU_PRESENT             0         /* MGU present or not */
#define __VIC_PRIO_BITS           2         /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /* Set to 1 if different SysTick Config is used */

#include "csi_core.h"                     /* Processor and core peripherals */
#include "stdint.h"

////////
#define FLASH_BASE                  ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define SRAM_BASE                   ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE                 ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

/*!< Peripheral device address mapping */
#define APB0_BASE                   PERIPH_BASE
#define APB1_BASE                   (PERIPH_BASE + 0x10000)
#define AHB_BASE                    (PERIPH_BASE + 0x20000)

#define IIC0_BASE                   (APB0_BASE + 0x0000)
#define TDMA_BASE                   (APB0_BASE + 0x1000)
#define HG_UART0_BASE               (APB0_BASE + 0x3000)
#define HG_UART1_BASE               (APB0_BASE + 0x4000)
#define DBGPATH_BASE                (APB0_BASE + 0x5000)
#define SPI0_BASE                   (APB0_BASE + 0x6000)
#define SPI1_BASE                   (APB0_BASE + 0x7000)
#define LMAC_BASE                   (APB0_BASE + 0x8000)
#define SPI3_BASE                   (APB0_BASE + 0x9000)            ///slave
#define EFUSE_BASE                  (APB0_BASE + 0xa000)
#define TDMA2_BASE                  (APB0_BASE + 0xb000)

#define CE_BASE                     (APB1_BASE + 0x0000)
#define MIPI_BASE                   (APB1_BASE + 0x1000)
#define SYS_AES_BASE                (APB1_BASE + 0x2000)
#define WDT_BASE                    (APB1_BASE + 0x3000)
#define RFADCDIG_BASE               (APB1_BASE + 0x4000)
#define HG_TIMER0_BASE              (APB1_BASE + 0x5000)
#define HG_TIMER1_BASE              (APB1_BASE + 0x5010)
#define HG_TIMER2_BASE              (APB1_BASE + 0x5020)
#define HG_TIMER3_BASE              (APB1_BASE + 0x5030)
#define RFSPI_BASE                  (APB1_BASE + 0x6000)
#define HG_CRC32_BASE               (APB1_BASE + 0x7000)
#define PWRDMCTL_BASE               (APB1_BASE + 0x8000)
#define ADKEY_BASE                  (APB1_BASE + 0xa000)
#define ZH_RFSPI_BASE               (APB1_BASE + 0xb000)
#define RFDIGCAL_BASE               (APB1_BASE + 0xd000)
#define M2M_DMA0_BASE               (APB1_BASE + 0xe000)
#define M2M_DMA1_BASE               (APB1_BASE + 0xe000 + 24)

#define DMAC_BASE                   (AHB_BASE + 0x0000)
#define HG_GPIOA_BASE               (AHB_BASE + 0x2000)
#define HG_SDIO20_HOST_BASE         (AHB_BASE + 0x3000)
#define HG_WPHY_AH_BASE             (AHB_BASE + 0x4000)
#define HG_GPIOB_BASE               (AHB_BASE + 0x5000)
#define HG_SYSCTRL_BASE             (AHB_BASE + 0x6000)
#define HG_USB11_DEVICE_BASE        (AHB_BASE + 0x7000)
#define HG_GMAC_BASE                (AHB_BASE + 0x8000)
#define SYS_MNT_BASE                (AHB_BASE + 0x9000)
#define HG_SDIO20_SLAVE_BASE        (AHB_BASE + 0x20000)



/* dma-perip channel define */
#define DMA_CH_I2C0_TX          0
#define DMA_CH_I2C0_RX          1
#define DMA_CH_SPI0_TX          6
#define DMA_CH_SPI0_RX          7
#define DMA_CH_SPI1_TX          8
#define DMA_CH_SPI1_RX          9
#define DMA_CH_UART1_TX         10
#define DMA_CH_UART1_RX         11
#define DMA_CH_SPI3_TX          12
#define DMA_CH_SPI3_RX          13
#define DMA_CH_UART0_TX         14
#define DMA_CH_UART0_RX         15


#define OSC_CLK     32000000UL


enum phy_rf_mode {
    INT_PHY_EXT_RF_MODE = 1, //for ext-rf case
    PHY_RF_NORMAL_MODE  = 2, //tx4001 ic normal case
    INT_RF_EXT_PHY_MODE = 3, //for transceiver case
};


#define LO_FREQ_MIN 730000 //730MHz 
#define LO_FREQ_MAX 930000 //930MHz


#define LMAC_VERSION       59//43:6001, 46:4001, 59:4002a
#define WPHY_AH_HW_VER     3 // 1: 6001 2: 4001 3:MARS
#define RFDIGICALI_HW_VER  2 // 1: 4001 2: MARS

#define MODEM_LTF_BUG_FIX  1
#define DAC_BUG_FIXED      1


#endif
