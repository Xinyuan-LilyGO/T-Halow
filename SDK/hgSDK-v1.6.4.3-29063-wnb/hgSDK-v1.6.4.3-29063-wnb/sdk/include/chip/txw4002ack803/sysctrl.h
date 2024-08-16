
// @file    sysctrl.h
// @author  wangying
// @brief   This file contains all the sysctrl defines.

// @Revision History
// V1.0.0  06/01/2019  First Release, copy from 4001a project
// V1.0.1  07/05/2019  delete iis defs, add IO_MAP_RF_SWITCH_MAP0_MSK
// V1.0.2  07/10/2019  change rf funcs(add sysctrl_ext_rf_sel_lo_freq_via_gpio() & config_rf_rx_gain() &sysctrl_ext_rf_set_bw_via_gpio();
//                                     delete sysctrl_internal_rf_set_bw()
// V1.0.3  07/10/2019  delete PMUREG0, delete LVD defs, add power-domain-control defs;
//                     delete RFDIGCAL defs;
// V1.0.4  07/18/2019  add gmac clk cfg functions; fix sysctrl_internal_rf_por_reset()bug
// V1.0.5  07/21/2019  add SYSMONITOR defs
// V1.0.6  07/26/2019  add struct RFDIGCAL temperally
// V1.0.7  08/02/2019  rename SYS_CON0_LO_FREQ_MSK to SYS_CON0_RX_LO_FREQ_MSK according to spec
//                     rename SYS_CON0_LO_FREQ_SHIFT to SYS_CON0_RX_LO_FREQ_SHIFT according to spec
//                     rename sysctrl_internal_rf_sel_rx_lo_freq() to sysctrl_internal_rf_set_rx_lo_freq_idx()
//                     rename sysctrl_ext_rf_sel_rx_lo_freq_via_gpio() to sysctrl_ext_rf_set_rx_lo_freq_idx_via_gpio();
// V1.0.8  08/10/2019  fix IO_MAP_JTAG_MAP_MSK_MSK, add bits in clk_con3, delete bit2 in sys_con2
// V1.0.9  09/26/2019  add sysctrl_clear_fpga_rom(); add pwrdmctl regs & funcs from verify
// V1.1.0  12/11/2019  change sys_get_sysclk() to sys_get_apbclk()
// V1.1.1  01/03/2020  rename sysctrl_internal_rf_set_rx_lo_freq_idx() to sysctrl_internal_rf_sel_rx_lo_freq()
// V1.1.2  01/08/2020  rename to sysctrl_internal_rf_sel_lo_freq()
// V1.1.3  01/29/2020  add enum vccmipi_vol and func pmu_vccmipi_vol_set()
// V1.1.4  01/30/2020  add func pmu_vdd13_ldo_dis()
// V1.1.5  02/06/2020  add func memory_read() & memory_write();
// V1.1.6  02-14-2020  add is_xo_cs_calibed() & xo_cs_store()
//                     add sysctrl_get_xo_drcs() & sysctrl_set_xo_drcs()
//                     add security operation for pd
// V1.1.7  12-30-2020  add sysctrl_set_xo_fx2()

// Define to prevent recursive inclusion //////////////////////////////
#ifndef __SYSCTRL_H__
#define __SYSCTRL_H__

#include "typesdef.h"

#ifdef __cplusplus
extern "C" {
#endif


/** @defgroup SYSCTRL_Exported_Constants
  * @{
  */

typedef struct {
    __IO uint32 IO_MAP;
    __IO uint32 SYS_CON0;
    __IO uint32 SYS_CON1;
    __IO uint32 CLK_CON0;
    __IO uint32 CLK_CON1;
    __IO uint32 CLK_CON2;
    __IO uint32 CLK_CON3;
    __IO uint32 SYS_CON2;
    __IO uint32 RESERVED1;
    __IO uint32 CLK_CON4;
    __IO uint32 SYS_CON11;
    __IO uint32 SYS_KEY;
    __IO uint32 SYS_CON9;
    __IO uint32 HOSC_MNT;
    __IO uint32 AIP_CON0;
    __IO uint32 RESERVED0;
    __IO uint32 SYS_CON3;
    __IO uint32 SYS_CON4;
    __IO uint32 SYS_CON5;
    __IO uint32 SYS_CON6;
    __IO uint32 SYS_CON7;
    __IO uint32 SYS_CON8;
    __IO uint32 SYS_ERR0;
    __IO uint32 SYS_ERR1;
    __IO uint32 WK_CTRL;
    __IO uint32 LP_CTRL;
    __IO uint32 MBIST_CTRL;
    __IO uint32 MBIST_MISR;
    __I  uint32 CHIP_ID;
    __IO uint32 MODE_REG;
    __I  uint32 EFUSE_LOCK;
    __IO uint32 SYS_CON10;
    __IO uint32 MBIST_MISR1;
    __IO uint32 MBIST_MISR2;
    __IO uint32 MBIST_MISR3;
    __IO uint32 MBIST_MISR4;
    __IO uint32 MBIST_MISR5;
    __IO uint32 MBIST_MISR6;
    __IO uint32 MBIST_MISR7;
} SYSCTRL_TypeDef;

#define SYSCTRL                 ((SYSCTRL_TypeDef    *) HG_SYSCTRL_BASE)


#define IO_MAP_EXT_RF_DEBUG_MAP0_MSK             BIT(15)
#define IO_MAP_EXT_PHY_DEBUG_MAP0_MSK            BIT(16)
#define IO_MAP_RFSPI_DEBUG_MAP_MSK               BIT(17)
#define IO_MAP_RF_SPI_MASTER_MAP0_MSK            BIT(21)
#define IO_MAP_RF_SPI_SLAVE_MAP0_MSK             BIT(22)
#define IO_MAP_CLK_TO_IO_MAP0_MSK                BIT(24)
#define IO_MAP_RF_SWITCH_MAP0_MSK                BIT(25)
#define IO_MAP_USB11_TEST_MAP0_MSK               BIT(26)
#define IO_MAP_LVD_TEST_MAP0_MSK                 BIT(27)
#define IO_MAP_MBIST_MAP0_MSK                    BIT(30)
#define IO_MAP_AD9361_MAP_MSK                    BIT(31)

#define SYS_CON0_DAC_IP_TO_RF_MSK                BIT(0)
#define SYS_CON0_RF_BW_SHIFT                     2
#define SYS_CON0_RF_BW_MSK                      (3<<SYS_CON0_RF_BW_SHIFT)
#define SYS_CON0_DAC_OPMI_VDD_SHIFT              4
#define SYS_CON0_DAC_OPMI_VDD_MSK               (3<<SYS_CON0_DAC_OPMI_VDD_SHIFT)
#define SYS_CON0_DAC_OPMQ_VDD_SHIFT              6
#define SYS_CON0_DAC_OPMQ_VDD_MSK               (3<<SYS_CON0_DAC_OPMQ_VDD_SHIFT)
#define SYS_CON0_IDAC_VBOUT_CTL_VDD_SHIFT        8
#define SYS_CON0_IDAC_VBOUT_CTL_VDD_MSK         (3<<SYS_CON0_IDAC_VBOUT_CTL_VDD_SHIFT)
#define SYS_CON0_QDAC_VBOUT_CTL_VDD_SHIFT        10
#define SYS_CON0_QDAC_VBOUT_CTL_VDD_MSK         (3<<SYS_CON0_QDAC_VBOUT_CTL_VDD_SHIFT)
#define SYS_CON0_DAC_TRIMMODI_VDD_SHIFT          12
#define SYS_CON0_DAC_TRIMMODI_VDD_MSK           (3<<SYS_CON0_DAC_TRIMMODI_VDD_SHIFT)
#define SYS_CON0_DAC_TRIMMODQ_VDD_SHIFT          14
#define SYS_CON0_DAC_TRIMMODQ_VDD_MSK           (3<<SYS_CON0_DAC_TRIMMODQ_VDD_SHIFT)
#define SYS_CON0_DAC_TOSELI_SHIFT                16
#define SYS_CON0_DAC_TOSELI_MSK                 (0xf<<SYS_CON0_DAC_TOSELI_SHIFT)
#define SYS_CON0_DAC_TOSELQ_SHIFT                20
#define SYS_CON0_DAC_TOSELQ_MSK                 (0xf<<SYS_CON0_DAC_TOSELQ_SHIFT)
#define SYS_CON0_IDAC_CS_CTL_VDD_MSK             BIT(24)
#define SYS_CON0_IDAC_VBOUT_EN_VDD_MSK           BIT(25)
#define SYS_CON0_QDAC_CS_CTL_VDD_MSK             BIT(26)
#define SYS_CON0_QDAC_VBOUT_EN_VDD_MSK           BIT(27)
#define SYS_CON0_RX_LO_FREQ_SHIFT                28
#define SYS_CON0_RX_LO_FREQ_MSK                 (0xfUL<<SYS_CON0_RX_LO_FREQ_SHIFT)

#define SYS_CON1_AES_SOFT_RST_MSK                BIT(0)
#define SYS_CON1_WDT_SYS_SOFT_RST_MSK            BIT(2)
#define SYS_CON1_SYS_AES_SOFT_RST_MSK            BIT(3)
#define SYS_CON1_TIMER_SOFT_RST_MSK              BIT(4)
#define SYS_CON1_RF_SYS_SPI_SOFT_RST_MSK         BIT(5)
#define SYS_CON1_SPI3_SOFT_RST_MSK               BIT(6)
#define SYS_CON1_SPI1_SOFT_RST_MSK               BIT(7)
#define SYS_CON1_SPI0_SOFT_RST_MSK               BIT(8)
#define SYS_CON1_DBG_DMA_SOFT_RST_MSK            BIT(9)
#define SYS_CON1_UART1_SOFT_RST_MSK              BIT(10)
#define SYS_CON1_UART0_SOFT_RST_MSK              BIT(11)
#define SYS_CON1_USB11_SOFT_RST_MSK              BIT(12)
#define SYS_CON1_TDMA_SOFT_RST_MSK               BIT(13)
#define SYS_CON1_IIC_SOFT_RST_MSK                BIT(14)
#define SYS_CON1_RF_SPI_SOFT_RST_MSK             BIT(15)
#define SYS_CON1_WDT_SOFT_RST_MSK                BIT(16)
#define SYS_CON1_SDIO_SOFT_RST_MSK               BIT(18)
#define SYS_CON1_CRC_SOFT_RST_MSK                BIT(19)
#define SYS_CON1_MAC_SOFT_RST_MSK                BIT(20)
#define SYS_CON1_LF_SOFT_RST_MSK                 BIT(21)
#define SYS_CON1_GPIO_SOFT_RST_MSK               BIT(22)
#define SYS_CON1_MEM_SOFT_RST_MSK                BIT(23)
#define SYS_CON1_MODEM_SOFT_RST_MSK              BIT(24)
#define SYS_CON1_ZHRF_SPI_SOFT_RST_MSK           BIT(25)   
#define SYS_CON1_RF_DIG_CAL_SOFT_RST_MSK         BIT(26)
#define SYS_CON1_OSCCAL_SYS_SOFT_RST_MSK         BIT(27)
#define SYS_CON1_SARADC_SYS_SOFT_RST_MSK         BIT(28)
#define SYS_CON1_GMAC_SYS_SOFT_RST_MSK           BIT(29)
#define SYS_CON1_MIPI_SOFT_RST_MSK               BIT(30)

#define CLK_CON0_SYS_CLK_SEL_SHIFT               0
#define CLK_CON0_SYS_CLK_SEL_MSK                (0x3<<CLK_CON0_SYS_CLK_SEL_SHIFT)
#define CLK_CON0_LF_CLK_SEL_SHIFT                2
#define CLK_CON0_LF_CLK_SEL_MSK                 (0x3<<CLK_CON0_LF_CLK_SEL_SHIFT)
#define CLK_CON0_CLK_TO_IO_SEL_SHIFT             4
#define CLK_CON0_CLK_TO_IO_SEL_MSK              (0x3<<CLK_CON0_CLK_TO_IO_SEL_SHIFT)
#define CLK_CON0_CRCDMA_CLK_DIV_SHIFT            6
#define CLK_CON0_CRCDMA_CLK_DIV_MSK             (0x3<<CLK_CON0_CRCDMA_CLK_DIV_SHIFT)
#define CLK_CON0_SYS_CLK_LF_DIV_SHIFT            8
#define CLK_CON0_SYS_CLK_LF_DIV_MSK             (0xf<<CLK_CON0_SYS_CLK_LF_DIV_SHIFT)
#define CLK_CON0_PLL_LF_DIV_SHIFT                12
#define CLK_CON0_PLL_LF_DIV_MSK                 (0xf<<CLK_CON0_PLL_LF_DIV_SHIFT)
#define CLK_CON0_APLL_LF_DIV_SHIFT               16
#define CLK_CON0_APLL_LF_DIV_MSK                (0xf<<CLK_CON0_APLL_LF_DIV_SHIFT)
#define CLK_CON0_OSC_CALCLK_SEL_MSK              BIT(20)
#define CLK_CON0_CLK_TO_IO_DIV_SHIFT             24
#define CLK_CON0_CLK_TO_IO_DIV_MSK              (0x3f<<CLK_CON0_CLK_TO_IO_DIV_SHIFT)
#define CLK_CON0_LF_CLK_SRC_SEL_SHIFT            30
#define CLK_CON0_LF_CLK_SRC_SEL_MSK             (0x3UL<<CLK_CON0_LF_CLK_SRC_SEL_SHIFT)

#define CLK_CON1_SYS_CLK_DIV_SHIFT               0
#define CLK_CON1_SYS_CLK_DIV_MSK                (0xff<<CLK_CON1_SYS_CLK_DIV_SHIFT)
#define CLK_CON1_APB0CLK_DIV_SHIFT               8
#define CLK_CON1_APB0CLK_DIV_MSK                (0xff<<CLK_CON1_APB0CLK_DIV_SHIFT)
#define CLK_CON1_APB1CLK_DIV_SHIFT               16
#define CLK_CON1_APB1CLK_DIV_MSK                (0xff<<CLK_CON1_APB1CLK_DIV_SHIFT)
#define CLK_CON1_RFSPICLK_DIV_SHIFT              24
#define CLK_CON1_RFSPICLK_DIV_MSK               (0xffUL<<CLK_CON1_RFSPICLK_DIV_SHIFT)

#define CLK_CON2_AES_CLK_EN_MSK                  BIT(0)
#define CLK_CON2_WDT_SYS_CLK_EN_MSK              BIT(2)
#define CLK_CON2_TIMER1_CLK_EN_MSK               BIT(4)
#define CLK_CON2_RF_SYS_SPI_CLK_EN_MSK           BIT(5)
#define CLK_CON2_SPI3_CLK_EN_MSK                 BIT(6)
#define CLK_CON2_SPI1_CLK_EN_MSK                 BIT(7)
#define CLK_CON2_SPI0_CLK_EN_MSK                 BIT(8)
#define CLK_CON2_DBG_DMA_CLK_EN_MSK              BIT(9)
#define CLK_CON2_UART1_CLK_EN_MSK                BIT(10)
#define CLK_CON2_UART0_CLK_EN_MSK                BIT(11)
#define CLK_CON2_USB11_CLK_EN_MSK                BIT(12)
#define CLK_CON2_TDMA_CLK_EN_MSK                 BIT(13)
#define CLK_CON2_IIC_CLK_EN_MSK                  BIT(14)
#define CLK_CON2_ZHRF_SYS_SPI_CLK_EN_MSK         BIT(15)
#define CLK_CON2_WDT_CLK_EN_MSK                  BIT(16)
#define CLK_CON2_TEST_CLK_EN_MSK                 BIT(17)
#define CLK_CON2_CPU_CLK_EN_MSK                  BIT(18) 
#define CLK_CON2_DMA_CLK_EN_MSK                  BIT(19)
#define CLK_CON2_AHB0_CLK_EN_MSK                 BIT(20)
#define CLK_CON2_AHB1_CLK_EN_MSK                 BIT(21)
#define CLK_CON2_SYSAES_CLK_EN_MSK               BIT(22) 
#define CLK_CON2_SDDEV_CLK_EN_MSK                BIT(23)
#define CLK_CON2_CRC_CLK_EN_MSK                  BIT(24)
#define CLK_CON2_GPIO_CLK_EN_MSK                 BIT(25)
#define CLK_CON2_MODEM_CLK_EN_MSK                BIT(26)
#define CLK_CON2_RFSARADC_CLK_EN_MSK             BIT(27)
#define CLK_CON2_RFDAC_CLK_EN_MSK                BIT(28)
#define CLK_CON2_MAC_CLK_EN_MSK                  BIT(29)
#define CLK_CON2_OSC_REFCLK_EN_MSK               BIT(30)
#define CLK_CON2_GMAC_CLKTR_SEL_MSK              BIT(31)

#define CLK_CON3_SRAM0_CLK_EN_MSK                BIT(0)
#define CLK_CON3_SRAM1_CLK_EN_MSK                BIT(1)
#define CLK_CON3_SRAM2_CLK_EN_MSK                BIT(2)
#define CLK_CON3_SRAM3_CLK_EN_MSK                BIT(3)
#define CLK_CON3_SRAM4_CLK_EN_MSK                BIT(4)
#define CLK_CON3_SRAM5_CLK_EN_MSK                BIT(5)
#define CLK_CON3_SRAM6_CLK_EN_MSK                BIT(6)
#define CLK_CON3_SRAM7_CLK_EN_MSK                BIT(7)
#define CLK_CON3_SRAM8_CLK_EN_MSK                BIT(8)
#define CLK_CON3_SRAM9_CLK_EN_MSK                BIT(9)
#define CLK_CON3_SRAM10_CLK_EN_MSK               BIT(10)
#define CLK_CON3_SRAM11_CLK_EN_MSK               BIT(11)
#define CLK_CON3_ROM_CLK_EN_MSK                  BIT(16)
#define CLK_CON3_GMAC_CLK_EN_MSK                 BIT(17)
#define CLK_CON3_MIPI_CLK_EN_MSK                 BIT(18)
#define CLK_CON3_M2MDMA_CLK_EN_MSK               BIT(19)
#define CLK_CON3_SYSMNT_CLK_EN_MSK               BIT(20)
#define CLK_CON3_LVD_DBS_CLK_SEL_SHIFT           21
#define CLK_CON3_LVD_DBS_CLK_SEL_MSK            (3<<CLK_CON3_LVD_DBS_CLK_SEL_SHIFT)
#define CLK_CON3_LVD_DBS_CLK_EN_MSK              BIT(23)

#define SYS_CON2_RT_RESET_EN_MSK                 BIT(0)
#define SYS_CON2_LOCKUP_EN_MSK                   BIT(1)
#define SYS_CON2_NMI_INT_EN_MSK                  BIT(3)
#define SYS_CON2_RXEV_EN_MSK                     BIT(4)
#define SYS_CON2_SWDDBG_MEM_PORTECT_EN_MSK       BIT(5)
#define SYS_CON2_MROM_PROTECT_EN_MSK             BIT(6)
#define SYS_CON2_WDT_SPEED_UP_MSK                BIT(7)
#define SYS_CON2_WDT_PAUSE_MSK                   BIT(8)
#define SYS_CON2_ADC0_ANA_CTRL_SEL_MSK           BIT(9)
#define SYS_CON2_ADC1_ANA_CTRL_SEL_MSK           BIT(10)
#define SYS_CON2_HOSC_LOSS_SW_EN_MSK             BIT(16)
#define SYS_CON2_HOSC_LOSS_NMI_EN_MSK            BIT(17)
#define SYS_CON2_RFADC_DIG_SOFT_EN_MSK           BIT(18)
#define SYS_CON2_RFADC_DIG_EN_SEL_MSK            BIT(19)
#define SYS_CON2_RFADC_DIG_MODE_SEL_MSK          BIT(20)
#define SYS_CON2_RFADC_DIG_DLY_TIME0_SHIFT       21
#define SYS_CON2_RFADC_DIG_DLY_TIME0_MSK        (0x1f<<SYS_CON2_RFADC_DIG_DLY_TIME0_SHIFT)
#define SYS_CON2_RFADC_DIG_DLY_TIME1_SHIFT       26
#define SYS_CON2_RFADC_DIG_DLY_TIME1_MSK        (0x1f<<SYS_CON2_RFADC_DIG_DLY_TIME1_SHIFT)
#define SYS_CON2_RFADC_DIG_SAREN_EDGE_SEL_MSK    BIT(31)

#define CLK_CON4_LOW_RC_CLK_COUNT_SHIFT          0
#define CLK_CON4_LOW_RC_CLK_COUNT_MSK           (0x1fffff<<CLK_CON4_LOW_RC_CLK_COUNT_SHIFT)
#define CLK_CON4_LOW_RC_CLK_COUNT_BUSY_MSK       BIT(21)
#define CLK_CON4_COUNT_PER_SEL_SHIFT             22
#define CLK_CON4_COUNT_PER_SEL_MSK              (0x7<<CLK_CON4_COUNT_PER_SEL_SHIFT)

#define SYS_CON11_SRAM0_HW_PD_EN_MSK             BIT(0)
#define SYS_CON11_SRAM0_PD_ENTER_CNT_SHIFT       1
#define SYS_CON11_SRAM0_PD_ENTER_CNT_MSK        (0x3ff<<SYS_CON11_SRAM0_PD_ENTER_CNT_SHIFT)
#define SYS_CON11_SRAM0_PD_EXIT_CNT_SHIFT        1
#define SYS_CON11_SRAM0_PD_EXIT_CNT_MSK         (0x3<<SYS_CON11_SRAM0_PD_EXIT_CNT_SHIFT)

#define SYS_CON9_DAC_TESTEN_VDD_MSK              BIT(0)
#define SYS_CON9_DAC_LDOTEST_VDD_MSK             BIT(1)
#define SYS_CON9_DAC_CLKSELQ_VDD_MSK             BIT(2)
#define SYS_CON9_DAC_CLKSELI_VDD_MSK             BIT(3)
#define SYS_CON9_DAC_REFSELI_VDD_MSK             BIT(4)
#define SYS_CON9_DAC_REFSELQ_VDD_MSK             BIT(5)
#define SYS_CON9_DAC_IRESVOLI_VDD_SHIFT          6
#define SYS_CON9_DAC_IRESVOLI_VDD_MSK           (0x3f<<SYS_CON9_DAC_IRESVOLI_VDD_SHIFT)
#define SYS_CON9_DAC_IRESVOLQ_VDD_SHIFT          12
#define SYS_CON9_DAC_IRESVOLQ_VDD_MSK           (0x3f<<SYS_CON9_DAC_IRESVOLQ_VDD_SHIFT)
#define SYS_CON9_DAC_VRESVOLI_VDD_SHIFT          18
#define SYS_CON9_DAC_VRESVOLI_VDD_MSK           (0x3f<<SYS_CON9_DAC_VRESVOLI_VDD_SHIFT)
#define SYS_CON9_DAC_VRESVOLQ_VDD_SHIFT          24
#define SYS_CON9_DAC_VRESVOLQ_VDD_MSK           (0x3f<<SYS_CON9_DAC_VRESVOLQ_VDD_SHIFT)

#define HOSC_MNT_LOW_LIMIT_SHIFT                 0
#define HOSC_MNT_LOW_LIMIT_MSK                  (0x3fff<<HOSC_MNT_LOW_LIMIT_SHIFT)
#define HOSC_MNT_HOSC_CLR_PENDING_MSK            BIT(14)
#define HOSC_MNT_HOSC_MNT_EN_MSK                 BIT(15)
#define HOSC_MNT_HIGH_LIMIT_SHIFT                16
#define HOSC_MNT_HIGH_LIMIT_MSK                 (0xffffUL<<HOSC_MNT_HIGH_LIMIT_SHIFT)

#define AIP_CON0_ADC_SAREN_VDD_MSK               BIT(0)
#define AIP_CON0_ADCI_EN_VDD_MSK                 BIT(1)
#define AIP_CON0_ADCQ_EN_VDD_MSK                 BIT(2)
#define AIP_CON0_ADC_TRIM_VDD_MSK                BIT(3)
#define AIP_CON0_ADC_BUFEN_VDD_MSK               BIT(4)
#define AIP_CON0_ADC_LDOEN_VDD_MSK               BIT(5)
#define AIP_CON0_ADC_BIASEN_VDD_MSK              BIT(6)
#define AIP_CON0_ADC_REFEN_VDD_MSK               BIT(7)
#define AIP_CON0_ADC_ISO_VDD_MSK                 BIT(8)
#define AIP_CON0_ADC_REFSEL_VDD_MSK              BIT(9)
#define AIP_CON0_ADC_TEST_VDD_SHIFT              10
#define AIP_CON0_ADC_TEST_VDD_MSK               (0xffff<<AIP_CON0_ADC_TEST_VDD_SHIFT)

#define SYS_CON3_MAC_CLK_SEL_MSK                 BIT(0)
#define SYS_CON3_PLL_FB_DIV_SHIFT                1
#define SYS_CON3_PLL_FB_DIV_MSK                 (0x7f<<SYS_CON3_PLL_FB_DIV_SHIFT)
#define SYS_CON3_PLL_REF_DIV_SHIFT               8
#define SYS_CON3_PLL_REF_DIV_MSK                (0xf<<SYS_CON3_PLL_REF_DIV_SHIFT)
#define SYS_CON3_APLL_REF_DIV_SHIFT              12
#define SYS_CON3_APLL_REF_DIV_MSK               (0xf<<SYS_CON3_APLL_REF_DIV_SHIFT)
#define SYS_CON3_APLL_FB_DIV_SHIFT               16
#define SYS_CON3_APLL_FB_DIV_MSK                (0x7f<<SYS_CON3_APLL_FB_DIV_SHIFT)
#define SYS_CON3_PLL_REFCLK_SEL_MSK              BIT(23)
#define SYS_CON3_APLL_REFCLK_SEL_SHIFT           24
#define SYS_CON3_APLL_REFCLK_SEL_MSK            (0x3<<SYS_CON3_APLL_REFCLK_SEL_SHIFT)
#define SYS_CON3_PLLCLK_SEL_MSK                  BIT(26)
#define SYS_CON3_SDIO_MEM_PD_MSK                 BIT(29)

#define SYS_CON5_ERR_RESP_EN_ICODE_BUS_MSK       BIT(27)
#define SYS_CON5_ERR_RESP_EN_DCODE_BUS_MSK       BIT(28)
#define SYS_CON5_ERR_RESP_EN_AHB2DMA_BUS_MSK     BIT(29)
#define SYS_CON5_ERR_RESP_EN_SDIODEVICE_BUS_MSK  BIT(30)
#define SYS_CON5_ERR_RESP_EN_USB_BUS_MSK         BIT(31)

#define SYS_CON6_ADCPLL_EN_MSK                   BIT(0)
#define SYS_CON6_PLLA_KB_SHIFT                   1
#define SYS_CON6_PLLA_KB_MSK                    (0x7<<SYS_CON6_PLLA_KB_SHIFT)
#define SYS_CON6_PLLA_KG_SHIFT                   4
#define SYS_CON6_PLLA_KG_MSK                    (0x3<<SYS_CON6_PLLA_KG_SHIFT)
#define SYS_CON6_PLLA_LPFRES_SHIFT               6
#define SYS_CON6_PLLA_LPFRES_MSK                (0xf<<SYS_CON6_PLLA_LPFRES_SHIFT)
#define SYS_CON6_PLLA_PFD_D_SHIFT                10
#define SYS_CON6_PLLA_PFD_D_MSK                 (0xf<<SYS_CON6_PLLA_PFD_D_SHIFT)
#define SYS_CON6_PLLA_VSET_MSK                   BIT(14)
#define SYS_CON6_PLLA_CPISET_SHIFT               15
#define SYS_CON6_PLLA_CPISET_MSK                (0x3<<SYS_CON6_PLLA_CPISET_SHIFT)
#define SYS_CON6_PLLA_VCODET_MSK                 BIT(17)
#define SYS_CON6_PLLA_TEST_SHIFT                 18
#define SYS_CON6_PLLA_TEST_MSK                  (0xf<<SYS_CON6_PLLA_TEST_SHIFT)
#define SYS_CON6_RF_POR_MSK                      BIT(23)
#define SYS_CON6_CLR_FPGA_ROM_EN_MSK             BIT(24)
#define SYS_CON6_RF_DIGITAL_32M_CLK_DISABLE_MSK  BIT(25)
#define SYS_CON6_RF_EN_CUT_OFF_MSK               BIT(26)
#define SYS_CON6_AD9361_RF_EN_MODE_MSK           BIT(27)
#define SYS_CON6_AD9361_FDD_TXEN_MSK             BIT(28)
#define SYS_CON6_PORT_RF_POR_EN_MSK              BIT(30)
#define SYS_CON6_PORT_RF_EN_MSK                  BIT(31)

#define SYS_CON7_SYSPLL_EN_MSK                   BIT(0)
#define SYS_CON7_PLLS_KB_SHIFT                   1
#define SYS_CON7_PLLS_KB_MSK                    (0x7<<SYS_CON7_PLLS_KB_SHIFT)
#define SYS_CON7_PLLS_KG_SHIFT                   4
#define SYS_CON7_PLLS_KG_MSK                    (0x3<<SYS_CON7_PLLS_KG_SHIFT)
#define SYS_CON7_PLLS_LPFRES_SHIFT               6
#define SYS_CON7_PLLS_LPFRES_MSK                (0xf<<SYS_CON7_PLLS_LPFRES_SHIFT)
#define SYS_CON7_PLLS_PFD_D_SHIFT                10
#define SYS_CON7_PLLS_PFD_D_MSK                 (0xf<<SYS_CON7_PLLS_PFD_D_SHIFT)
#define SYS_CON7_PLLS_VSET_MSK                   BIT(14)
#define SYS_CON7_PLLS_CPISET_SHIFT               15
#define SYS_CON7_PLLS_CPISET_MSK                (0x3<<SYS_CON7_PLLS_CPISET_SHIFT)
#define SYS_CON7_PLLS_VCODET_MSK                 BIT(17)
#define SYS_CON7_PLLS_TEST_SHIFT                 18
#define SYS_CON7_PLLS_TEST_MSK                  (0xf<<SYS_CON7_PLLS_TEST_SHIFT)
#define SYS_CON7_ADCPLLCLK_DIV18_SEL_MSK         BIT(30)
#define SYS_CON7_PHY_CLK_48M_SEL_MSK             BIT(31)

#define SYS_CON8_QDAC_TESTEN_VDD_SHIFT           0
#define SYS_CON8_QDAC_TESTEN_VDD_MSK            (0xf<<SYS_CON8_QDAC_TESTEN_VDD_SHIFT)
#define SYS_CON8_IDAC_TESTEN_VDD_SHIFT           4
#define SYS_CON8_IDAC_TESTEN_VDD_MSK            (0xf<<SYS_CON8_IDAC_TESTEN_VDD_SHIFT)
#define SYS_CON8_DAC_TESTADEN_VDD_MSK            BIT(8)
#define SYS_CON8_DAC_CON_SEL_MSK                 BIT(9)
#define SYS_CON8_DAC_CON_IQREG_SHIFT             10
#define SYS_CON8_DAC_CON_IQREG_MSK              (3<<SYS_CON8_DAC_CON_IQREG_SHIFT)
#define SYS_CON8_DCOC_CAL_RX_EN_MSK              BIT(30)
#define SYS_CON8_DCOC_CAL_TX_EN_MSK              BIT(31)

#define SYS_ERR0_MROM_PROTECT0_DCODE_REQ_MSK     BIT(0)
#define SYS_ERR0_MROM_PROTECT1_DCODE_REQ_MSK     BIT(1)
#define SYS_ERR0_MROM_PROTECT0_ICODE_REQ_MSK     BIT(2)
#define SYS_ERR0_MROM_PROTECT1_ICODE_REQ_MSK     BIT(3)
#define SYS_ERR0_DMAC_MEM_ERR_MSK                BIT(4)
#define SYS_ERR0_ICODE_MEM_ERR_MSK               BIT(5)
#define SYS_ERR0_DCODE_MEM_ERR_MSK               BIT(6)
#define SYS_ERR0_SYSBUS_MEM_ERR_MSK              BIT(7)
#define SYS_ERR0_TDMA_MEM_ERR_MSK                BIT(8)
#define SYS_ERR0_LMAC_AES_MEM_ERR_MSK            BIT(9)
#define SYS_ERR0_SDIO_MEM_ERR_MSK                BIT(10)
#define SYS_ERR0_LMAC_MEM_ERR_MSK                BIT(12)
#define SYS_ERR0_CRC_MEM_ERR_MSK                 BIT(13)
#define SYS_ERR0_SYSAES_MEM_ERR_MSK              BIT(14)
#define SYS_ERR0_TDMA2_MEM_ERR_MSK               BIT(15)
#define SYS_ERR0_USB_MEM_ERR_MSK                 BIT(16)
#define SYS_ERR0_GMAC_RXRAM_MEM_ERR_MSK          BIT(17)
#define SYS_ERR0_GMAC_TXRAM_MEM_ERR_MSK          BIT(18)
#define SYS_ERR0_GMAC_RXAHB_MEM_ERR_MSK          BIT(19)
#define SYS_ERR0_M2M1_DMARX_MEM_ERR_MSK          BIT(20)
#define SYS_ERR0_M2M1_DMATX_MEM_ERR_MSK          BIT(21)
#define SYS_ERR0_M2M0_DMARX_MEM_ERR_MSK          BIT(22)
#define SYS_ERR0_M2M0_DMATX_MEM_ERR_MSK          BIT(23)
#define SYS_ERR0_GMAC_TXAHB_MEM_ERR_MSK          BIT(24)

#define WK_CTRL_PA26_WKUP_EN_MSK                 BIT(0)
#define WK_CTRL_PA27_WKUP_EN_MSK                 BIT(1)
#define WK_CTRL_PA28_WKUP_EN_MSK                 BIT(2)
#define WK_CTRL_PA29_WKUP_EN_MSK                 BIT(3)
#define WK_CTRL_PA26_WKUP_EDGE_MSK               BIT(8)
#define WK_CTRL_PA27_WKUP_EDGE_MSK               BIT(9)
#define WK_CTRL_PA28_WKUP_EDGE_MSK               BIT(10)
#define WK_CTRL_PA29_WKUP_EDGE_MSK               BIT(11)
#define WK_CTRL_PA26_WKUP_PND_CLR_MSK            BIT(16)
#define WK_CTRL_PA27_WKUP_PND_CLR_MSK            BIT(17)
#define WK_CTRL_PA28_WKUP_PND_CLR_MSK            BIT(18)
#define WK_CTRL_PA29_WKUP_PND_CLR_MSK            BIT(19)
#define WK_CTRL_PA26_WKUP_PND_MSK                BIT(24)
#define WK_CTRL_PA27_WKUP_PND_MSK                BIT(25)
#define WK_CTRL_PA28_WKUP_PND_MSK                BIT(26)
#define WK_CTRL_PA29_WKUP_PND_MSK                BIT(27)

#define LP_CTRL_SLEEP_MODE_MSK                   BIT(0)
#define LP_CTRL_STOPCLK_MSK                      BIT(1)
#define LP_CTRL_RC32K_AUTO_DIS_MSK               BIT(2)
#define LP_CTRL_SRAM0_AUTO_DIS_MSK               BIT(3)
#define LP_CTRL_SRAM1_AUTO_DIS_MSK               BIT(4)
#define LP_CTRL_SRAM2_AUTO_DIS_MSK               BIT(5)
#define LP_CTRL_SRAM3_AUTO_DIS_MSK               BIT(6)
#define LP_CTRL_SRAM4_AUTO_DIS_MSK               BIT(7)
#define LP_CTRL_SRAM5_AUTO_DIS_MSK               BIT(8)
#define LP_CTRL_SRAM6_AUTO_DIS_MSK               BIT(9)
#define LP_CTRL_SRAM7_AUTO_DIS_MSK               BIT(10)
#define LP_CTRL_SRAM8_AUTO_DIS_MSK               BIT(11)
#define LP_CTRL_SRAM9_AUTO_DIS_MSK               BIT(12)
#define LP_CTRL_SRAM10_AUTO_DIS_MSK              BIT(13)
#define LP_CTRL_SRAM11_AUTO_DIS_MSK              BIT(14)
#define LP_CTRL_SLEEP_PD_EN_MSK                  BIT(15)
#define LP_CTRL_ROM_AUTO_DIS_MSK                 BIT(16)
#define LP_CTRL_ROM_PD_MSK                       BIT(17)
#define LP_CTRL_SRAM0_PD_MSK                     BIT(18) //SRAM0 sw pd-data won't lost
#define LP_CTRL_SRAM1_PD_MSK                     BIT(19)
#define LP_CTRL_SRAM2_PD_MSK                     BIT(20)
#define LP_CTRL_SRAM3_PD_MSK                     BIT(21)
#define LP_CTRL_SRAM4_PD_MSK                     BIT(22)
#define LP_CTRL_SRAM5_PD_MSK                     BIT(23)
#define LP_CTRL_SRAM6_PD_MSK                     BIT(24)
#define LP_CTRL_SRAM7_PD_MSK                     BIT(25)
#define LP_CTRL_SRAM8_PD_MSK                     BIT(26)
#define LP_CTRL_SRAM9_PD_MSK                     BIT(27)
#define LP_CTRL_SRAM10_PD_MSK                    BIT(28)
#define LP_CTRL_SRAM11_PD_MSK                    BIT(29)
#define LP_CTRL_FFT_MEM_PD_MSK                   BIT(30)
#define LP_CTRL_MODEM_MEM_PD_MSK                 BIT(31)

#define MBIST_CTRL_SRAM2P_TEST_MSK               BIT(0)
#define MBIST_CTRL_SRAM2P_HOLD_MSK               BIT(1)
#define MBIST_CTRL_SRAM2P_DBGZ_MSK               BIT(2)
#define MBIST_CTRL_SRAM1P_TEST_MSK               BIT(3)
#define MBIST_CTRL_SRAM1P_HOLD_MSK               BIT(4)
#define MBIST_CTRL_SRAM1P_DBGZ_MSK               BIT(5)
#define MBIST_CTRL_SRAM1P_1_TEST_MSK             BIT(6)
#define MBIST_CTRL_SRAM1P_1_HOLD_MSK             BIT(7)
#define MBIST_CTRL_SRAM1P_1_DBGZ_MSK             BIT(8)
#define MBIST_CTRL_RF1P_TEST_MSK                 BIT(9)
#define MBIST_CTRL_RF1P_HOLD_MSK                 BIT(10)
#define MBIST_CTRL_RF1P_DBGZ_MSK                 BIT(11)
#define MBIST_CTRL_RF2P_TEST_MSK                 BIT(12)
#define MBIST_CTRL_RF2P_HOLD_MSK                 BIT(13)
#define MBIST_CTRL_RF2P_DBGZ_MSK                 BIT(14)
#define MBIST_CTRL_ROM_TEST_MSK                  BIT(15)
#define MBIST_CTRL_ROM_HOLD_MSK                  BIT(16)
#define MBIST_CTRL_ROM_SE_MSK                    BIT(17)
#define MBIST_CTRL_MBIST_CLK_EN_MSK              BIT(18)
#define MBIST_CTRL_TST_DONE_MSK                  BIT(19)
#define MBIST_CTRL_FAIL_MSK                      BIT(20)

#define SYS_CON10_CARD_DET_PULL_VAL_SHIFT        0
#define SYS_CON10_CARD_DET_PULL_VAL_MSK         (0xf<<SYS_CON10_CARD_DET_PULL_VAL_SHIFT)
#define SYS_CON10_CARD_DET_PULL_CTRL_MSK         BIT(4)
#define SYS_CON10_GMAC_DMA_EN                    BIT(13)

enum lf_clk_src {
    FROM_HOSC  = 0,
    FROM_RC32K = 2,
    FROM_PB0   = 3,
};

enum lf_clk_count {
    _1024_CYCLE = 0,
    _512_CYCLE  = 1,
    _256_CYCLE  = 2,
    _128_CYCLE  = 3,
    _64_CYCLE   = 4,
    _32_CYCLE   = 5,
    _16_CYCLE   = 6,
    _8_CYCLE    = 7,
};

enum dac_default_state {
    POWER_OFF = 0,
    SLEEP     = 1,
    STAND_BY  = 2,
    POWER_ON  = 3
};

enum rf_bw {
    BW_1M = 0,
    BW_2M = 1,
    BW_4M = 2,
    BW_8M = 3
};

enum rf_parameter_type {
    ADC_CALIB_VAL    = 0,
    TXDCOC_CALIB_VAL = 1,
    TXIMB_CALIB_VAL  = 2,
    RXDCOC_CALIB_VAL = 3,
    RXIMB_CALIB_VAL  = 4,
    FBDCOC_CALIB_VAL = 5,
    FBIMB_CALIB_VAL  = 6,
    XO_CS_VAL        = 7,
    TXGAIN_CALIB_VAL = 8
};

/**
  * @}
  */

/** @defgroup CMU_Exported_Functions
  * @{
  */

void sysctrl_external_xosc_en(uint8 src_sel, uint8 onoff);
void sysctrl_syspll_adc_calib(void);
void sysctrl_adcpll_adc_calib(void);
void sysctrl_syspll_set(uint8 onoff, uint8 plls_ref_div, uint8 plls_ref_sel_div, uint8 plls_fb_div);
void sysctrl_adcpll_set(uint8 enable, uint8 plla_ref_div, uint8 plla_ref_sel_div, uint8 plla_fb_div);
void sysctrl_sysclk_cfg(uint8 pllclk_div3_sel, uint8 sys_clk_sel, uint8 sys_clk_div);
void sysctrl_apbclk_cfg(uint8 apb0clk_div, uint8 apb1clk_div);
void sysctrl_crcdma_clk_cfg(uint8 crcdma_clk_div);
void sysctrl_lf_clk_cfg(void);
void sysctrl_lf_clk_src_sel(enum lf_clk_src src);
void sysctrl_lf_clk_count_set(uint32 count);
#define sysctrl_start_lf_clk_count()            {SYSCTRL->CLK_CON4 |= \
            CLK_CON4_LOW_RC_CLK_COUNT_BUSY_MSK;} 
#define sysctrl_wait_lf_clk_count_cmplt()       {while(SYSCTRL->CLK_CON4 & \
            CLK_CON4_LOW_RC_CLK_COUNT_BUSY_MSK);} 
void sysctrl_lf_clk_per_count_set(enum lf_clk_count per_count);
void sysctrl_rfspi_clk_div_cfg(uint8 rfspi_clk_div);
void sysctrl_clk_output_to_pa29_cfg(uint8 clock_to_io_sel, uint8 clk_to_io_div);

#define sysctrl_cipher_engine_clk_open()        {SYSCTRL->CLK_CON2 |= CLK_CON2_AES_CLK_EN_MSK;}
#define sysctrl_cipher_engine_clk_close()       {SYSCTRL->CLK_CON2 &= ~CLK_CON2_AES_CLK_EN_MSK;}
#define sysctrl_wdt_clk_open()                  {SYSCTRL->CLK_CON2 |= CLK_CON2_WDT_SYS_CLK_EN_MSK;\
        SYSCTRL->CLK_CON2 |= CLK_CON2_WDT_CLK_EN_MSK;}
#define sysctrl_wdt_clk_close()                 {SYSCTRL->CLK_CON2 &= ~CLK_CON2_WDT_SYS_CLK_EN_MSK;\
        SYSCTRL->CLK_CON2 &= ~CLK_CON2_WDT_CLK_EN_MSK;}
#define sysctrl_timer_clk_open()                {SYSCTRL->CLK_CON2 |= CLK_CON2_TIMER1_CLK_EN_MSK;}
#define sysctrl_timer_clk_close()               {SYSCTRL->CLK_CON2 &= ~CLK_CON2_TIMER1_CLK_EN_MSK;}
#define sysctrl_rf_spi_clk_open()               {SYSCTRL->CLK_CON2 |= CLK_CON2_RF_SYS_SPI_CLK_EN_MSK;}
#define sysctrl_rf_spi_clk_close()              {SYSCTRL->CLK_CON2 &= ~CLK_CON2_RF_SYS_SPI_CLK_EN_MSK;}
#define sysctrl_spi3_clk_open()                 {SYSCTRL->CLK_CON2 |= CLK_CON2_SPI3_CLK_EN_MSK;}
#define sysctrl_spi3_clk_close()                {SYSCTRL->CLK_CON2 &= ~CLK_CON2_SPI3_CLK_EN_MSK;}
#define sysctrl_spi1_clk_open()                 {SYSCTRL->CLK_CON2 |= CLK_CON2_SPI1_CLK_EN_MSK;}
#define sysctrl_spi1_clk_close()                {SYSCTRL->CLK_CON2 &= ~CLK_CON2_SPI1_CLK_EN_MSK;}
#define sysctrl_spi0_clk_open()                 {SYSCTRL->CLK_CON2 |= CLK_CON2_SPI0_CLK_EN_MSK;}
#define sysctrl_spi0_clk_close()                {SYSCTRL->CLK_CON2 &= ~CLK_CON2_SPI0_CLK_EN_MSK;}
#define sysctrl_dbgpath_clk_open()              {SYSCTRL->CLK_CON2 |= CLK_CON2_DBG_DMA_CLK_EN_MSK;}
#define sysctrl_dbgpath_clk_close()             {SYSCTRL->CLK_CON2 &= ~CLK_CON2_DBG_DMA_CLK_EN_MSK;}
#define sysctrl_uart1_clk_open()                {SYSCTRL->CLK_CON2 |= CLK_CON2_UART1_CLK_EN_MSK;}
#define sysctrl_uart1_clk_close()               {SYSCTRL->CLK_CON2 &= ~CLK_CON2_UART1_CLK_EN_MSK;}
#define sysctrl_uart0_clk_open()                {SYSCTRL->CLK_CON2 |= CLK_CON2_UART0_CLK_EN_MSK;}
#define sysctrl_uart0_clk_close()               {SYSCTRL->CLK_CON2 &= ~CLK_CON2_UART0_CLK_EN_MSK;}
#define sysctrl_usb11_clk_open()                {SYSCTRL->CLK_CON2 |= CLK_CON2_USB11_CLK_EN_MSK;}
#define sysctrl_usb11_clk_close()               {SYSCTRL->CLK_CON2 &= ~CLK_CON2_USB11_CLK_EN_MSK;}
#define sysctrl_tdma_clk_open()                 {SYSCTRL->CLK_CON2 |= CLK_CON2_TDMA_CLK_EN_MSK;}
#define sysctrl_tdma_clk_close()                {SYSCTRL->CLK_CON2 &= ~CLK_CON2_TDMA_CLK_EN_MSK;}
#define sysctrl_iic_clk_open()                  {SYSCTRL->CLK_CON2 |= CLK_CON2_IIC_CLK_EN_MSK;}
#define sysctrl_iic_clk_close()                 {SYSCTRL->CLK_CON2 &= ~CLK_CON2_IIC_CLK_EN_MSK;}
#define sysctrl_zhrf_spi_clk_open()             {SYSCTRL->CLK_CON2 |= CLK_CON2_ZHRF_SYS_SPI_CLK_EN_MSK;}
#define sysctrl_zhrf_spi_clk_close()            {SYSCTRL->CLK_CON2 &= ~CLK_CON2_ZHRF_SYS_SPI_CLK_EN_MSK;}
#define sysctrl_ext_clk_from_pa28_open()        {SYSCTRL->CLK_CON2 |= CLK_CON2_TEST_CLK_EN_MSK;}
#define sysctrl_ext_clk_from_pa28_close()       {SYSCTRL->CLK_CON2 &= ~CLK_CON2_TEST_CLK_EN_MSK;}
#define sysctrl_cpu_clk_open()                  {SYSCTRL->CLK_CON2 |= CLK_CON2_CPU_CLK_EN_MSK;}
#define sysctrl_cpu_clk_close()                 {SYSCTRL->CLK_CON2 &= ~CLK_CON2_CPU_CLK_EN_MSK;}
#define sysctrl_dma_clk_open()                  {SYSCTRL->CLK_CON2 |= CLK_CON2_DMA_CLK_EN_MSK;}
#define sysctrl_dma_clk_close()                 {SYSCTRL->CLK_CON2 &= ~CLK_CON2_DMA_CLK_EN_MSK;}
#define sysctrl_sysaes_clk_open()               {SYSCTRL->CLK_CON2 |= CLK_CON2_SYSAES_CLK_EN_MSK;}
#define sysctrl_sysaes_clk_close()              {SYSCTRL->CLK_CON2 &= ~CLK_CON2_SYSAES_CLK_EN_MSK;}
#define sysctrl_sddev_clk_open()                {SYSCTRL->CLK_CON2 |= CLK_CON2_SDDEV_CLK_EN_MSK;}
#define sysctrl_sddev_clk_close()               {SYSCTRL->CLK_CON2 &= ~CLK_CON2_SDDEV_CLK_EN_MSK;}
#define sysctrl_crc_clk_open()                  {SYSCTRL->CLK_CON2 |= CLK_CON2_CRC_CLK_EN_MSK;}
#define sysctrl_crc_clk_close()                 {SYSCTRL->CLK_CON2 &= ~CLK_CON2_CRC_CLK_EN_MSK;}
#define sysctrl_gpio_clk_open()                 {SYSCTRL->CLK_CON2 |= CLK_CON2_GPIO_CLK_EN_MSK;}
#define sysctrl_gpio_clk_close()                {SYSCTRL->CLK_CON2 &= ~CLK_CON2_GPIO_CLK_EN_MSK;}
#define sysctrl_modem_clk_open()                {SYSCTRL->CLK_CON2 |= CLK_CON2_MODEM_CLK_EN_MSK;}
#define sysctrl_modem_clk_close()               {SYSCTRL->CLK_CON2 &= ~CLK_CON2_MODEM_CLK_EN_MSK;}
#define sysctrl_rf_saradc_clk_open()            {SYSCTRL->CLK_CON2 |= CLK_CON2_RFSARADC_CLK_EN_MSK;}
#define sysctrl_rf_saradc_clk_close()           {SYSCTRL->CLK_CON2 &= ~CLK_CON2_RFSARADC_CLK_EN_MSK;}
#define sysctrl_rf_dac_clk_open()               {SYSCTRL->CLK_CON2 |= CLK_CON2_RFDAC_CLK_EN_MSK;}
#define sysctrl_rf_dac_clk_close()              {SYSCTRL->CLK_CON2 &= ~CLK_CON2_RFDAC_CLK_EN_MSK;}
#define sysctrl_mac_clk_open()                  {SYSCTRL->CLK_CON2 |= CLK_CON2_MAC_CLK_EN_MSK;}
#define sysctrl_mac_clk_close()                 {SYSCTRL->CLK_CON2 &= ~CLK_CON2_MAC_CLK_EN_MSK;}
#define sysctrl_osc_refclk_open()               {SYSCTRL->CLK_CON2 |= CLK_CON2_OSC_REFCLK_EN_MSK;}
#define sysctrl_osc_refclk_close()              {SYSCTRL->CLK_CON2 &= ~CLK_CON2_OSC_REFCLK_EN_MSK;}

#define sysctrl_gmac_clk_sel_rc32k()            {SYSCTRL->CLK_CON2 &= ~CLK_CON2_GMAC_CLKTR_SEL_MSK;}
#define sysctrl_gmac_clk_sel_clk_from_io()      {SYSCTRL->CLK_CON2 |= CLK_CON2_GMAC_CLKTR_SEL_MSK;}

#define sysctrl_sram_clk_open(val)              {SYSCTRL->CLK_CON3 |= val;}
#define sysctrl_sram_clk_close(val)             {SYSCTRL->CLK_CON3 &= ~val;}

#define sysctrl_ext_clk_from_pb9_open()         {SYSCTRL->SYS_CON3 |= SYS_CON3_MAC_CLK_SEL_MSK;}
#define sysctrl_ext_clk_from_pb9_close()        {SYSCTRL->SYS_CON3 &= ~SYS_CON3_MAC_CLK_SEL_MSK;}

#define sysctrl_pllclk_div_by_2()               {SYSCTRL->SYS_CON3 &= ~SYS_CON3_PLLCLK_SEL_MSK;}
#define sysctrl_pllclk_div_by_3()               {SYSCTRL->SYS_CON3 |= SYS_CON3_PLLCLK_SEL_MSK;}

#define sysctrl_gmac_clk_open()                 {SYSCTRL->CLK_CON3 |= CLK_CON3_GMAC_CLK_EN_MSK;}
#define sysctrl_gmac_clk_close()                {SYSCTRL->CLK_CON3 &= ~CLK_CON3_GMAC_CLK_EN_MSK;}
#define sysctrl_mipi_clk_open()                 {SYSCTRL->CLK_CON3 |= CLK_CON3_MIPI_CLK_EN_MSK;}
#define sysctrl_mipi_clk_close()                {SYSCTRL->CLK_CON3 &= ~CLK_CON3_MIPI_CLK_EN_MSK;}
#define sysctrl_m2mdma_clk_open()               {SYSCTRL->CLK_CON3 |= CLK_CON3_M2MDMA_CLK_EN_MSK;}
#define sysctrl_m2mdma_clk_close()              {SYSCTRL->CLK_CON3 &= ~CLK_CON3_M2MDMA_CLK_EN_MSK;}
#define sysctrl_sysmnt_clk_open()               {SYSCTRL->CLK_CON3 |= CLK_CON3_SYSMNT_CLK_EN_MSK;}
#define sysctrl_sysmnt_clk_close()              {SYSCTRL->CLK_CON3 &= ~CLK_CON3_SYSMNT_CLK_EN_MSK;}
#define sysctrl_lvd_dbs_clk_open()              {SYSCTRL->CLK_CON3 |= CLK_CON3_LVD_DBS_CLK_EN_MSK;}
#define sysctrl_lvd_dbs_clk_close()             {SYSCTRL->CLK_CON3 &= ~CLK_CON3_LVD_DBS_CLK_EN_MSK;}

#define sysctrl_gmac_dma_enable()               {SYSCTRL->SYS_CON10 |= SYS_CON10_GMAC_DMA_EN;}
#define sysctrl_gmac_dma_disable()              {SYSCTRL->SYS_CON10 &= ~SYS_CON10_GMAC_DMA_EN;}

int32 sys_get_apbclk(void);
int32 sys_get_sysclk(void);
int32 sys_set_sysclk(uint32 system_clk);

/**
  * @}
  */

/** @defgroup RMU_Exported_Functions
  * @{
  */

#define sysctrl_cipher_engine_resst()            {SYSCTRL->SYS_CON1 &= ~SYS_CON1_AES_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_AES_SOFT_RST_MSK;}
#define sysctrl_wdt_reset()                      {SYSCTRL->SYS_CON1 &= ~SYS_CON1_WDT_SYS_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 &= ~SYS_CON1_WDT_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_WDT_SYS_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_WDT_SOFT_RST_MSK;}
#define sysctrl_sysaes_reset()                   {SYSCTRL->SYS_CON1 &= ~SYS_CON1_SYS_AES_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_SYS_AES_SOFT_RST_MSK;}
#define sysctrl_timer_reset()                    {SYSCTRL->SYS_CON1 &= ~SYS_CON1_TIMER_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_TIMER_SOFT_RST_MSK;}
#define sysctrl_rfspi_reset()                    {SYSCTRL->SYS_CON1 &= ~SYS_CON1_RF_SYS_SPI_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 &= ~SYS_CON1_RF_SPI_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_RF_SYS_SPI_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_RF_SPI_SOFT_RST_MSK;}
#define sysctrl_spi0_reset()                     {SYSCTRL->SYS_CON1 &= ~SYS_CON1_SPI0_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_SPI0_SOFT_RST_MSK;}
#define sysctrl_spi1_reset()                     {SYSCTRL->SYS_CON1 &= ~SYS_CON1_SPI1_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_SPI1_SOFT_RST_MSK;}
#define sysctrl_spi3_reset()                     {SYSCTRL->SYS_CON1 &= ~SYS_CON1_SPI3_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_SPI3_SOFT_RST_MSK;}
#define sysctrl_dbgpath_reset()                  {SYSCTRL->SYS_CON1 &= ~SYS_CON1_DBG_DMA_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_DBG_DMA_SOFT_RST_MSK;}
#define sysctrl_uart0_reset()                    {SYSCTRL->SYS_CON1 &= ~SYS_CON1_UART0_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_UART0_SOFT_RST_MSK;}
#define sysctrl_uart1_reset()                    {SYSCTRL->SYS_CON1 &= ~SYS_CON1_UART1_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_UART1_SOFT_RST_MSK;}
#define sysctrl_usb11_reset()                    {SYSCTRL->SYS_CON1 &= ~SYS_CON1_USB11_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_USB11_SOFT_RST_MSK;}
#define sysctrl_tdma_reset()                     {SYSCTRL->SYS_CON1 &= ~SYS_CON1_TDMA_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_TDMA_SOFT_RST_MSK;}
#define sysctrl_iic_reset()                      {SYSCTRL->SYS_CON1 &= ~SYS_CON1_IIC_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_IIC_SOFT_RST_MSK;}
#define sysctrl_sdio_reset()                     {SYSCTRL->SYS_CON1 &= ~SYS_CON1_SDIO_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_SDIO_SOFT_RST_MSK;}
#define sysctrl_crc_reset()                      {SYSCTRL->SYS_CON1 &= ~SYS_CON1_CRC_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_CRC_SOFT_RST_MSK;}
#define sysctrl_mac_reset()                      {SYSCTRL->SYS_CON1 &= ~SYS_CON1_MAC_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_MAC_SOFT_RST_MSK;}
#define sysctrl_lf_reset()                       {SYSCTRL->SYS_CON1 &= ~SYS_CON1_LF_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_LF_SOFT_RST_MSK;}
#define sysctrl_gpio_reset()                     {SYSCTRL->SYS_CON1 &= ~SYS_CON1_GPIO_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_GPIO_SOFT_RST_MSK;}
#define sysctrl_mbist_reset()                    {SYSCTRL->SYS_CON1 &= ~SYS_CON1_MEM_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_MEM_SOFT_RST_MSK;}
#define sysctrl_modem_reset()                    {SYSCTRL->SYS_CON1 &= ~SYS_CON1_MODEM_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_MODEM_SOFT_RST_MSK;}
#define sysctrl_zhrf_spi_rst()                   {SYSCTRL->SYS_CON1 &= ~SYS_CON1_ZHRF_SPI_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_ZHRF_SPI_SOFT_RST_MSK;}
#define sysctrl_rf_dig_cal_rst()                 {SYSCTRL->SYS_CON1 &= ~SYS_CON1_RF_DIG_CAL_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_RF_DIG_CAL_SOFT_RST_MSK;}
#define sysctrl_osccal_rst()                     {SYSCTRL->SYS_CON1 &= ~SYS_CON1_OSCCAL_SYS_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_OSCCAL_SYS_SOFT_RST_MSK;}
#define sysctrl_saradc_rst()                     {SYSCTRL->SYS_CON1 &= ~SYS_CON1_SARADC_SYS_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_SARADC_SYS_SOFT_RST_MSK;}
#define sysctrl_gmac_sys_rst()                   {SYSCTRL->SYS_CON1 &= ~SYS_CON1_GMAC_SYS_SOFT_RST_MSK;\
                                                  os_sleep_us(1);                                      \
                                                  SYSCTRL->SYS_CON1 |= SYS_CON1_GMAC_SYS_SOFT_RST_MSK; \
                                                  os_sleep_us(1);}
#define sysctrl_mipi_rst()                       {SYSCTRL->SYS_CON1 &= ~SYS_CON1_MIPI_SOFT_RST_MSK;\
        SYSCTRL->SYS_CON1 |= SYS_CON1_MIPI_SOFT_RST_MSK;}

/**
  * @}
  */

/** @defgroup Bus Error Response Functions
  * @{
  */
int32 sysctrl_err_resp_usb_bus(uint8 enable);
int32 sysctrl_err_resp_icode_bus(uint8 enable);
int32 sysctrl_err_resp_dcode_bus(uint8 enable);
int32 sysctrl_err_resp_ahb2dma_bus(uint8 enable);
int32 sysctrl_err_resp_sdiodevice_bus(uint8 enable);
int32 sysctrl_err_resp_disable(void);

/**
  * @}
  */
        
        
/** @defgroup WDT_Exported_Functions
  * @{
  */

#define sysctrl_wdt_reset_system_enable()       {SYSCTRL->SYS_CON2 |= SYS_CON2_WDT_RESET_EN_MSK;}
#define sysctrl_wdt_reset_system_disable()      {SYSCTRL->SYS_CON2 &= ~SYS_CON2_WDT_RESET_EN_MSK;}

/**
  * @}
  */

/** @defgroup INTERNAL_RF_Exported_Functions
  * @{
  */

#define sysctrl_internal_rf_por_set_high()      {SYSCTRL->SYS_CON6 |= SYS_CON6_RF_POR_MSK;}
#define sysctrl_internal_rf_por_set_low()       {SYSCTRL->SYS_CON6 &= ~SYS_CON6_RF_POR_MSK;}
#define sysctrl_internal_rf_por_reset()         do {sysctrl_internal_rf_por_set_low();\
                                                    sysctrl_internal_rf_por_set_high();} while(0)

#define sysctrl_internal_rf_32_disable()        {SYSCTRL->SYS_CON6 |= SYS_CON6_RF_DIGITAL_32M_CLK_DISABLE_MSK;}
#define sysctrl_internal_rf_32_enable()         {SYSCTRL->SYS_CON6 &= ~SYS_CON6_RF_DIGITAL_32M_CLK_DISABLE_MSK;}
#define sysctrl_internal_rf_en_cut_off()        {SYSCTRL->SYS_CON6 &= ~SYS_CON6_RF_EN_CUT_OFF_MSK;}
#define sysctrl_internal_rf_en_connected()      {SYSCTRL->SYS_CON6 |= SYS_CON6_RF_EN_CUT_OFF_MSK;}

#define sysctrl_ad9361_rf_en_set_tdd_mode()     {SYSCTRL->SYS_CON6 &= ~SYS_CON6_AD9361_RF_EN_MODE_MSK;}
#define sysctrl_ad9361_rf_en_set_fdd_mode()     {SYSCTRL->SYS_CON6 |= SYS_CON6_AD9361_RF_EN_MODE_MSK;}
#define sysctrl_ad9361_rf_rx_en_set_tdd_mode()  {SYSCTRL->SYS_CON6 &= ~SYS_CON6_AD9361_FDD_TXEN_MSK;}
#define sysctrl_ad9361_rf_rx_en_set_fdd_mode()  {SYSCTRL->SYS_CON6 |= SYS_CON6_AD9361_FDD_TXEN_MSK;}

//only active in rf_slave_only mode
#define sysctrl_rf_pa_en_output_from_pb16()     {SYSCTRL->SYS_CON6 &= ~SYS_CON6_PA_EN_MAP1_MSK;}
#define sysctrl_rf_pa_en_output_from_pa14()     {SYSCTRL->SYS_CON6 |= SYS_CON6_PA_EN_MAP1_MSK;}
#define sysctrl_rf_por_ctrl_by_pb4_disable()    {SYSCTRL->SYS_CON6 &= ~SYS_CON6_PORT_RF_POR_EN_MSK;}
#define sysctrl_rf_por_ctrl_by_pb4_enable()     {SYSCTRL->SYS_CON6 |= SYS_CON6_PORT_RF_POR_EN_MSK;}

void sysctrl_dac_init(void);
#define sysctrl_dac2adc_loopback_disable()      {SYSCTRL->SYS_CON8 &= ~SYS_CON8_DAC_TESTADEN_VDD_MSK;}
#define sysctrl_dac2adc_loopback_enable()       {SYSCTRL->SYS_CON8 |= SYS_CON8_DAC_TESTADEN_VDD_MSK;}
#define sysctrl_dac_ctrl_by_lmac_hw()           {SYSCTRL->SYS_CON8 &= ~SYS_CON8_DAC_CON_SEL_MSK;}
#define sysctrl_dac_ctrl_by_sw()                {SYSCTRL->SYS_CON8 |= SYS_CON8_DAC_CON_SEL_MSK;}
int32 sysctrl_set_dac_default_state(enum dac_default_state dac_state);

int32 memory_read(enum rf_parameter_type rf_para, uint32 val_buf[], uint8 wordcnt);
int32 memory_write(enum rf_parameter_type rf_para, uint32 val_buf[], uint8 wordcnt);
int32 is_xo_cs_calibed(void);
int32 xo_cs_store(uint8 xo_cs_val);
int32 sysctrl_get_xo_drcs(void);
int32 sysctrl_set_xo_drcs(uint16 xo_drcs);
int32 sysctrl_set_xo_fx2(uint8 on_off);
void adc_cfg_reg_wr(uint8 addr, uint32 data);
uint32 adc_cfg_reg_rd(uint8 addr);
int32 is_adc_calibed(void);
void adc_init(void);
int32 adc_calib_res_store(void);
void adc_calib_res_restore(void);
void rfadc_calib_mode_soft_test(void);
#define adc_set_trim_mode()                     {SYSCTRL->SYS_CON2 &= ~SYS_CON2_RFADC_DIG_MODE_SEL_MSK;}
#define adc_set_norm_mode()                     {SYSCTRL->SYS_CON2 |= SYS_CON2_RFADC_DIG_MODE_SEL_MSK;}
#define adc_dig_sel_hw_ctrl()                   {SYSCTRL->SYS_CON2 &= ~SYS_CON2_RFADC_DIG_EN_SEL_MSK;}
#define adc_dig_sel_sw_ctrl()                   {SYSCTRL->SYS_CON2 |= SYS_CON2_RFADC_DIG_EN_SEL_MSK;}
#define adc_dig_sw_ctrl_dis()                   {SYSCTRL->SYS_CON2 &= ~SYS_CON2_RFADC_DIG_SOFT_EN_MSK;}
#define adc_dig_sw_ctrl_en()                    {SYSCTRL->SYS_CON2 |= SYS_CON2_RFADC_DIG_SOFT_EN_MSK;}
#define adc_ana_sel_sw_ctrl()                   {SYSCTRL->SYS_CON2 &= ~SYS_CON2_ADC0_ANA_CTRL_SEL_MSK;}
#define adc_ana_sel_hw_ctrl()                   {SYSCTRL->SYS_CON2 |= SYS_CON2_ADC0_ANA_CTRL_SEL_MSK;}

int32 sysctrl_internal_rf_sel_lo_freq(uint8 lo_freq_idx);
int32 sysctrl_ext_rf_set_rx_lo_freq_idx_via_gpio(uint8 lo_freq_idx);
int32 sysctrl_ext_rf_set_bw_via_gpio(enum rf_bw bw);
int32 sysctrl_ext_rf_set_bw_gain_via_gpio(enum rf_bw bw,uint8 rx_gain_value);

#define switch_clr_rxdcoc_calib_mode()          {SYSCTRL->SYS_CON8 &= ~SYS_CON8_DCOC_CAL_RX_EN_MSK;}
#define switch_set_rxdcoc_calib_mode()          {SYSCTRL->SYS_CON8 |= SYS_CON8_DCOC_CAL_RX_EN_MSK;}
#define switch_clr_txdcoc_calib_mode()          {SYSCTRL->SYS_CON8 &= ~SYS_CON8_DCOC_CAL_TX_EN_MSK;}
#define switch_set_txdcoc_calib_mode()          {SYSCTRL->SYS_CON8 |= SYS_CON8_DCOC_CAL_TX_EN_MSK;}

int32 tx_digi_gain_store(uint16 tx_digi_gain);

/**
  * @}
  */

/** @defgroup SYSTEM_Exported_Functions
  * @{
  */
#if SYS_KEY_OPT_EN
#define sysctrl_unlock()                        do {SYSCTRL->SYS_KEY = 0x3fac87e4;} while(0)
#define sysctrl_lock()                          do {SYSCTRL->SYS_KEY = 0;} while(0)
#define SYSCTRL_REG_OPT_INIT()                  do { sysctrl_lock(); } while(0)
#define SYSCTRL_REG_OPT(expr)                   do {uint32 flag=disable_irq(); sysctrl_unlock(); expr; sysctrl_lock(); enable_irq(flag);} while(0)
#define EFUSE_REG_OPT(expr)                     do {uint32 flag=disable_irq(); SYSCTRL->SYS_KEY = 0x4c5de9b3; expr; sysctrl_lock(); enable_irq(flag);} while(0)
#else
#define sysctrl_unlock()
#define sysctrl_lock()
#define SYSCTRL_REG_OPT_INIT()                  do { SYSCTRL->SYS_KEY = 0x3fac87e4; } while(0)
#define SYSCTRL_REG_OPT(expr)                   do { expr; } while(0)
#define EFUSE_REG_OPT(expr)                     do {uint32 flag=disable_irq(); SYSCTRL->SYS_KEY = 0x4c5de9b3; expr; SYSCTRL->SYS_KEY = 0x3fac87e4; enable_irq(flag);} while(0)
#endif
#define sysctrl_mem_dis_as_stopclk_en()         {SYSCTRL->LP_CTRL |= 0xfff8;}
#define sysctrl_mem_pd_enable(val)              {SYSCTRL->LP_CTRL |= val;}
#define sysctrl_mem_pd_disable(val)             {SYSCTRL->LP_CTRL &= ~val;}
#define sysctrl_enter_sleep()                   {SYSCTRL->LP_CTRL |= LP_CTRL_SLEEP_MODE_MSK;}
#define sysctrl_enter_sleep_pd()                {SYSCTRL->LP_CTRL |= LP_CTRL_SLEEP_MODE_MSK | LP_CTRL_SLEEP_PD_EN_MSK;}
#define sysctrl_stop_cpu_clk()                  {SYSCTRL->LP_CTRL |= LP_CTRL_STOPCLK_MSK;}
#define sysctrl_sram0_hw_pd_en()                {SYSCTRL->SYS_CON11 |= (2 << SYS_CON11_SRAM0_PD_ENTER_CNT_SHIFT) \
                                                                    |  (0 << SYS_CON11_SRAM0_PD_EXIT_CNT_SHIFT)  \
                                                                    |   SYS_CON11_SRAM0_HW_PD_EN_MSK;}
#define sysctrl_wakeup_enable(pin_idx)          {SYSCTRL->WK_CTRL |= WK_CTRL_PA##pin_idx##_WKUP_EN_MSK;}
#define sysctrl_wakeup_disable(pin_idx)         {SYSCTRL->WK_CTRL &= ~WK_CTRL_PA##pin_idx##_WKUP_EN_MSK;}
#define sysctrl_wakeup_set_riss_edge(pin_idx)   {SYSCTRL->WK_CTRL &= ~WK_CTRL_PA##pin_idx##_WKUP_EDGE_MSK;}
#define sysctrl_wakeup_set_fall_edge(pin_idx)   {SYSCTRL->WK_CTRL |= WK_CTRL_PA##pin_idx##_WKUP_EDGE_MSK;}
#define sysctrl_wakeup_pnd_clr(pin_idx)         {SYSCTRL->WK_CTRL |= WK_CTRL_PA##pin_idx##_WKUP_PND_CLR_MSK;}
#define sysctrl_wakeup_get_pnd(pin_idx)         (SYSCTRL->WK_CTRL & WK_CTRL_PA##pin_idx##_WKUP_PND_MSK)
#define sysctrl_clear_fpga_rom()                {SYSCTRL->SYS_CON6 |= SYS_CON6_CLR_FPGA_ROM_EN_MSK;\
                                                 *((volatile uint32 *)0x0) = 0;\
                                                 *((volatile uint32 *)0x4) = 0;}
#define sysctrl_get_chip_id()                   (uint16)(SYSCTRL->CHIP_ID)

/**
  * @}
  */

///** @defgroup SYSMONITOR MACRO-DEF & Exported_Functions
//  * @{
//  */
typedef struct
{
    __IO uint32 CHx_LMT_L;
    __IO uint32 CHx_LMT_H;
    __IO uint32 CHx_ERR_ADR;
         uint32 RESERVEDx;
} SYS_MNT_CH_TypeDef;

typedef struct
{
    __IO uint32 CTRL;
    __IO uint32 PND;
    __O  uint32 CLR;
    __IO uint32 RD;
    __IO uint32 WR;
         uint32 RESERVED0[3];
    __IO uint32 CPU_PC0;
    __IO uint32 CPU_PC1;
    __IO uint32 CPU_PC2;
    __IO uint32 CPU_PC3; 
         uint32 RESERVED1[4];
    SYS_MNT_CH_TypeDef SYS_MNT_CH[21];
} SYS_MNT_TypeDef;

#define SYSMNT                  ((SYS_MNT_TypeDef    *) SYS_MNT_BASE)

#define SYSMONITOR_CP_CAP_EN()                 (SYSMNT->CTRL |= (1UL << 22))
#define SYSMONITOR_INT_EN()                    (SYSMNT->CTRL |= (1UL << 21))
#define SYSMONITOR_CLEAR_REGISTER()            (SYSMNT->CLR = 0)

enum sysmonitor_chan{
    SYSMONITOR_CH0_TDMA_DMA                  = 0,
    SYSMONITOR_CH1_AES_DMA                   = 1,
    SYSMONITOR_CH2_SDIO_DMA                  = 2,
    SYSMONITOR_CH3_USB11_OLD_DMA             = 3,
    SYSMONITOR_CH4_LMAC_DMA                  = 4,
    SYSMONITOR_CH5_CRC_DMA                   = 5,
    SYSMONITOR_CH6_SYS_AES_DMA               = 6,
    SYSMONITOR_CH7_TDMA2_DMA                 = 7,
    SYSMONITOR_CH8_USB11_NOW_DMA             = 8,
    SYSMONITOR_CH9_GMAC_RXRAM_DMA            = 9,
    SYSMONITOR_CH10_GMAC_TXRAM_DMA           = 10,
    SYSMONITOR_CH11_GMAC_TX_AHB_MASTER_DMA   = 11,
    SYSMONITOR_CH12_GPDMA_DMA                = 12,
    SYSMONITOR_CH13_M2M1_DMA0                = 13,
    SYSMONITOR_CH14_M2M1_DMA1                = 14,
    SYSMONITOR_CH15_CPU_I_CODE_BUS_DMA       = 15,
    SYSMONITOR_CH16_CPU_D_CODE_BUS_DMA       = 16,
    SYSMONITOR_CH17_CPU_SYSBUS_BUS_DMA       = 17,
    SYSMONITOR_CH18_M2M0_DMA0                = 18,
    SYSMONITOR_CH19_M2M0_DMA1                = 19,
    SYSMONITOR_CH20_GMAC_RX_AHB_MASTER_DMA   = 20,
    SYSMONITOR_CH_MAX,
};

typedef struct
{
    /*! System monitor channel set
     */
    enum sysmonitor_chan  sysmonitor_ch;
    /*! Chx low limited address 
     */
    uint32           chx_limit_low;
    /*! Chx high limited address
     */
    uint32           chx_limit_high;
} SYSMONITOR_CFG;

void sys_monitor_chan_config(SYSMONITOR_CFG *p_sysmonitor);
void sys_monitor_reset(void);


/** @defgroup RFADCDIG MACRO-DEF & Exported_Functions
  * @{
  */

typedef struct {
    __IO uint32 RFADCDIGCON;
} RFADCDIG_TypeDef;

#define RFADCDIG                ((RFADCDIG_TypeDef *) RFADCDIG_BASE)

#define RFADCDIGCON_ACS_ON_MSK                   BIT(0)
#define RFADCDIGCON_ACS_RW_MSK                   BIT(1)
#define RFADCDIGCON_ACS_ADDR_SHIFT               2
#define RFADCDIGCON_ACS_ADDR_MSK                (0x1f<<RFADCDIGCON_ACS_ADDR_SHIFT)
#define RFADCDIGCON_ACS_DATA_SHIFT               7
#define RFADCDIGCON_ACS_DATA_MSK                (0x3fffff<<RFADCDIGCON_ACS_DATA_SHIFT)

#define ADCOUTSEL 0 // 0: output data after calibration; 1: output data before calibration

/**
  * @}
  */

/** @defgroup EFUSE MACRO-DEF & Exported_Functions
  * @{
  */

typedef struct {
    __IO uint32 EFUSE_CON;
    __IO uint32 EFUSE_TIME_CON0;
    __IO uint32 EFUSE_TIME_CON1;
    __IO uint32 EFUSE_STATUS;
    __IO uint32 EFUSE_ADDR_CNT;
    __IO uint32 EFUSE_DATA;
} EFUSE_TypeDef;

#define EFUSE                   ((EFUSE_TypeDef *) EFUSE_BASE)
/* efuse timing define */
#define LL_EFUSE_POWER_FREQ                 100000          /* 10us */
#define LL_EFUSE_PROGRAM_FREQ               100000          /* 10us (9~11uS) */
#define LL_EFUSE_READ_FREQ                  10000000       /* 100ns ( > 36ns)  */

uint16 sysctrl_efuse_config_and_read(uint32 start_addr, uint8 *p_buf, uint16 len);
void rf_para_efuse_check_valid(void);

/**
  * @}
  */

///** @defgroup PWRDMCTL (power domain control) MACRO-DEF & Exported_Functions
//  * @{
//  */

typedef struct {
    __IO uint32 LVD_CON;
    __IO uint32 LVD_CON1;
    __IO uint32 LVD_CON2;
    __I  uint32 RESERVE0;
    __IO uint32 CORE_PMUCON0;
    __IO uint32 CORE_PMUCON1;
    __IO uint32 CORE_PMUCON2;
    __IO uint32 CORE_PMUCON3;
    __IO uint32 CORE_PMUCON4;
    __IO uint32 CORE_PMUCON5;
    __IO uint32 CORE_RFCON0;
    __IO uint32 CORE_RFCON1;
    __IO uint32 CORE_PMUCON6;
    __IO uint32 CORE_PMUCON7;
    __IO uint32 CORE_PMUCON8;
    __I  uint32 RESERVE1[17];
    __IO uint32 CORE_TMRCON;
    __IO uint32 CORE_TMRPR;
    __IO uint32 CORE_TMRRPT;
    __IO uint32 CORE_TMRTRIM;
    __I  uint32 RESERVE2[4];
    __IO uint32 CORE_WKCON;
    __I  uint32 RESERVE3[3];
    __IO uint32 CORE_SECCON;
    __IO uint32 CORE_SECDAT;
    __IO uint32 CORE_SECADR;
    __IO uint32 CORE_SECKEY;
} PWRDMCTL_TypeDef;

#define PWRDMCTL          ((PWRDMCTL_TypeDef *) PWRDMCTL_BASE)

enum vdd_vol {
    VDD_0P77V  = 0,
    VDD_0P83V  = 1,
    VDD_0P88V  = 2,
    VDD_0P94V  = 3,
    VDD_0P99V  = 4,
    VDD_1P05V  = 5,
    VDD_1P10V  = 6,
    VDD_1P15V  = 7,
};

enum vdd13_vol {
    VDD13_1P1V   = 0,
    VDD13_1P155V = 1,
    VDD13_1P21V  = 2,
    VDD13_1P265V = 3,
    VDD13_1P32V  = 4,
    VDD13_1P375V = 5,
    VDD13_1P43V  = 6,
    VDD13_1P485V = 7,
};

enum vref_vol {
    VREF_P627V  = 0,
    VREF_P635V  = 1,
    VREF_P643V  = 2,
    VREF_P651V  = 3,
    VREF_P659V  = 4,
    VREF_P667V  = 5,
    VREF_P676V  = 6,
    VREF_P684V  = 7,
};

enum vccmipi_vol {
    VCCMIPI_1P2V = 0,
    VCCMIPI_1P5V = 1,
    VCCMIPI_1P8V = 2,
    VCCMIPI_2P5V = 3,
    VCCMIPI_3P3V = 4,
};

enum ldo_mode {
    LDO_CAP_FREE_MODE = 0,
    LDO_CAP_MODE      = 1,
};

enum alwayson_clk {
    RC256K   = 0,
    PCLK     = 1,
    RC32K    = 2,
    XOSC_32M = 3,
};

enum vcclvd_vol {
    VCCLVD_1P9  = 0,
    VCCLVD_2P04,
    VCCLVD_2P18,
    VCCLVD_2P33,
    VCCLVD_2P47,
    VCCLVD_2P61,
    VCCLVD_2P75,
    VCCLVD_2P90
};

#define LVD_CON_LVD13AEN_VDD_MSK                  BIT(0)
#define LVD_CON_LVD13DEN_VDD_MSK                  BIT(1)
#define LVD_CON_LVDVCCEN_VDD_MSK                  BIT(2)
#define LVD_CON_LVDVDDEN_VDD_MSK                  BIT(3)
#define LVD_CON_VDDOCEN_VDD_MSK                   BIT(4)
#define LVD_CON_LVD13ASET_VDD_SHIFT               5
#define LVD_CON_LVD13ASET_VDD_MSK                (0x3<<LVD_CON_LVD13ASET_VDD_SHIFT)
#define LVD_CON_LVD13DSET_VDD_SHIFT               7
#define LVD_CON_LVD13DSET_VDD_MSK                (0x3<<LVD_CON_LVD13DSET_VDD_SHIFT)
#define LVD_CON_LVDVDDSET_VDD_SHIFT               9
#define LVD_CON_LVDVDDSET_VDD_MSK                (0x3<<LVD_CON_LVDVDDSET_VDD_SHIFT)
#define LVD_CON_LVDVCCSET_VDD_SHIFT               11
#define LVD_CON_LVDVCCSET_VDD_MSK                (0x7<<LVD_CON_LVDVCCSET_VDD_SHIFT)
#define LVD_CON_VDDOCSET_VDD_SHIFT                14
#define LVD_CON_VDDOCSET_VDD_MSK                 (0x3<<LVD_CON_VDDOCSET_VDD_SHIFT)
#define LVD_CON_LVD13A_RST_EN_MSK                 BIT(16)
#define LVD_CON_LVD13D_RST_EN_MSK                 BIT(17)
#define LVD_CON_LVDVCC_RST_EN_MSK                 BIT(18)
#define LVD_CON_LVDVDD_RST_EN_MSK                 BIT(19)
#define LVD_CON_VDDOC_RST_EN_MSK                  BIT(20)
#define LVD_CON_LVD_OE_MSK                        BIT(21)
#define LVD_CON_13BOC_PD_EN_MSK                   BIT(22)
#define LVD_CON_13COC_PD_EN_MSK                   BIT(23)
#define LVD_CON_LVD13A_PD_MSK                     BIT(24)
#define LVD_CON_LVD13D_PD_MSK                     BIT(25)
#define LVD_CON_LVDVCC_PD_MSK                     BIT(26)
#define LVD_CON_LVDVDD_PD_MSK                     BIT(27)
#define LVD_CON_VDDOC_PD_MSK                      BIT(28)
#define LVD_CON_13COC_PD_MSK                      BIT(29)
#define LVD_CON_13BOC_PD_MSK                      BIT(30)
#define LVD_CON_MIPIOC_PD_MSK                     BIT(31)

#define LVD_CON1_LVDVCC_DBS_HI_LIMIT_SHIFT        0
#define LVD_CON1_LVDVCC_DBS_HI_LIMIT_MSK         (0x7f<<LVD_CON1_LVDVCC_DBS_HI_LIMIT_SHIFT)
#define LVD_CON1_LVDVCC_DBS_LO_LIMIT_SHIFT        7
#define LVD_CON1_LVDVCC_DBS_LO_LIMIT_MSK         (0x7f<<LVD_CON1_LVDVCC_DBS_LO_LIMIT_SHIFT)
#define LVD_CON1_LVDVDD_DBS_HI_LIMIT_SHIFT        14
#define LVD_CON1_LVDVDD_DBS_HI_LIMIT_MSK         (0x7f<<LVD_CON1_LVDVDD_DBS_HI_LIMIT_SHIFT)
#define LVD_CON1_LVDVDD_DBS_LO_LIMIT_SHIFT        21
#define LVD_CON1_LVDVDD_DBS_LO_LIMIT_MSK         (0x7f<<LVD_CON1_LVDVDD_DBS_LO_LIMIT_SHIFT)
#define LVD_CON1_LVDVCC_BPS_EN_MSK                BIT(28)
#define LVD_CON1_LVDVDD_BPS_EN_MSK                BIT(29)
#define LVD_CON1_LVDVCC_SYNC_DIS_MSK              BIT(30)
#define LVD_CON1_MIPIOC_RST_EN_MSK                BIT(31)

#define LVD_CON2_LVD13A_DBS_HI_LIMIT_SHIFT        0
#define LVD_CON2_LVD13A_DBS_HI_LIMIT_MSK         (0x7f<<LVD_CON2_LVD13A_DBS_HI_LIMIT_SHIFT)
#define LVD_CON2_LVD13A_DBS_LO_LIMIT_SHIFT        7
#define LVD_CON2_LVD13A_DBS_LO_LIMIT_MSK         (0x7f<<LVD_CON2_LVD13A_DBS_LO_LIMIT_SHIFT)
#define LVD_CON2_LVD13D_DBS_HI_LIMIT_SHIFT        14
#define LVD_CON2_LVD13D_DBS_HI_LIMIT_MSK         (0x7f<<LVD_CON2_LVD13D_DBS_HI_LIMIT_SHIFT)
#define LVD_CON2_LVD13D_DBS_LO_LIMIT_SHIFT        21
#define LVD_CON2_LVD13D_DBS_LO_LIMIT_MSK         (0x7f<<LVD_CON2_LVD13D_DBS_LO_LIMIT_SHIFT)
#define LVD_CON2_LVD13A_BPS_EN_MSK                BIT(28)
#define LVD_CON2_LVD13D_BPS_EN_MSK                BIT(29)

#define CORE_PMUCON0_PD_CORE_EN_MSK               BIT(0)
#define CORE_PMUCON0_PD_RF_EN_MSK                 BIT(1)
#define CORE_PMUCON0_LVD_DBS_SEL_MSK              BIT(2)
#define CORE_PMUCON0_CORE_RST_FAST_EN_MSK         BIT(3)
#define CORE_PMUCON0_PD_SEQ_MSK                   BIT(4)
#define CORE_PMUCON0_BOOT_CLK_SEL_MSK             BIT(5)
#define CORE_PMUCON0_CLK_CFG_SEL_SHIFT            6
#define CORE_PMUCON0_CLK_CFG_SEL_MSK             (0x3<<CORE_PMUCON0_CLK_CFG_SEL_SHIFT)
#define CORE_PMUCON0_VDD_LO_SEL_SHIFT             8
#define CORE_PMUCON0_VDD_LO_SEL_MSK              (0x7<<CORE_PMUCON0_VDD_LO_SEL_SHIFT)
#define CORE_PMUCON0_VDD_HI_SEL_SHIFT             11
#define CORE_PMUCON0_VDD_HI_SEL_MSK              (0x7<<CORE_PMUCON0_VDD_HI_SEL_SHIFT)
#define CORE_PMUCON0_VDDSET_BYPASS_MSK            BIT(14)
#define CORE_PMUCON0_PDTMRCLKSEL_MSK              BIT(15)
#define CORE_PMUCON0_OSC_HW_TRIM_EN_MSK           BIT(17)
#define CORE_PMUCON0_OSC_EN_MSK                   BIT(18)
#define CORE_PMUCON0_CORE_RF_LATCH_EN_MSK         BIT(19)
#define CORE_PMUCON0_CORE_IO_LATCH_EN_MSK         BIT(20)
#define CORE_PMUCON0_XOSC_CLK_CNT_SHIFT           22
#define CORE_PMUCON0_XOSC_CLK_CNT_MSK            (0x3ffUL<<CORE_PMUCON0_XOSC_CLK_CNT_SHIFT)

#define CORE_PMUCON1_PWRD_CNT_SHIFT               0
#define CORE_PMUCON1_PWRD_CNT_MSK                (0x3f<<CORE_PMUCON1_PWRD_CNT_SHIFT)
#define CORE_PMUCON1_PWRD1_CNT_SHIFT              8
#define CORE_PMUCON1_PWRD1_CNT_MSK               (0x3f<<CORE_PMUCON1_PWRD1_CNT_SHIFT)
#define CORE_PMUCON1_VDD_LO_CNT_SHIFT             16
#define CORE_PMUCON1_VDD_LO_CNT_MSK              (0xff<<CORE_PMUCON1_VDD_LO_CNT_SHIFT)
#define CORE_PMUCON1_VDD_HI_CNT_SHIFT             24
#define CORE_PMUCON1_VDD_HI_CNT_MSK              (0xff<<CORE_PMUCON1_VDD_HI_CNT_SHIFT)

#define CORE_PMUCON2_RF_ISO_EN_CNT_SHIFT          0
#define CORE_PMUCON2_RF_ISO_EN_CNT_MSK           (0x3<<CORE_PMUCON2_RF_ISO_EN_CNT_SHIFT)
#define CORE_PMUCON2_RF_PWRR_CNT_SHIFT            2
#define CORE_PMUCON2_RF_PWRR_CNT_MSK             (0x3f<<CORE_PMUCON2_RF_PWRR_CNT_SHIFT)
#define CORE_PMUCON2_RF_PWRR1_CNT_SHIFT           8
#define CORE_PMUCON2_RF_PWRR1_CNT_MSK            (0x3f<<CORE_PMUCON2_RF_PWRR1_CNT_SHIFT)
#define CORE_PMUCON2_RF_PWRD_CNT_SHIFT            14
#define CORE_PMUCON2_RF_PWRD_CNT_MSK             (0x3f<<CORE_PMUCON2_RF_PWRD_CNT_SHIFT)
#define CORE_PMUCON2_RF_PWRD1_CNT_SHIFT           20
#define CORE_PMUCON2_RF_PWRD1_CNT_MSK            (0x3f<<CORE_PMUCON2_RF_PWRD1_CNT_SHIFT)
#define CORE_PMUCON2_RF_ISO_DIS_CNT_SHIFT         26
#define CORE_PMUCON2_RF_ISO_DIS_CNT_MSK          (0x3<<CORE_PMUCON2_RF_ISO_DIS_CNT_SHIFT)

#define CORE_PMUCON3_CORE_ISO_MSK                 BIT(0)
#define CORE_PMUCON3_CORE_PWRDOWN_MSK             BIT(3)
#define CORE_PMUCON3_CORE_PWRDOWN1_MSK            BIT(4)
#define CORE_PMUCON3_CORE_PWRDOWNACK_MSK          BIT(5)
#define CORE_PMUCON3_CORE_PWRDOWNACK1_MSK         BIT(6)
#define CORE_PMUCON3_CORE_PD_PND_MSK              BIT(7)
#define CORE_PMUCON3_RF_ISO_MSK                   BIT(8)
#define CORE_PMUCON3_RF_PWRDOWN_MSK               BIT(11)
#define CORE_PMUCON3_RF_PWRDOWN1_MSK              BIT(12)
#define CORE_PMUCON3_RF_PWRDOWNACK_MSK            BIT(13)
#define CORE_PMUCON3_RF_PWRDOWNACK1_MSK           BIT(14)
#define CORE_PMUCON3_RF_PD_PND_MSK                BIT(15)
#define CORE_PMUCON3_RF_LATCH_CPU_MSK             BIT(16)
#define CORE_PMUCON3_IO_LATCH_CPU_MSK             BIT(17)
#define CORE_PMUCON3_XOSC_STM_SHIFT               29
#define CORE_PMUCON3_XOSC_STM_MSK                (0x7UL<<CORE_PMUCON3_XOSC_STM_SHIFT)

#define CORE_PMUCON4_VDDLCEN_MSK                  BIT(0)
#define CORE_PMUCON4_TSENSOR_EN_MSK               BIT(1)
#define CORE_PMUCON4_VREFEN_MSK                   BIT(2)
#define CORE_PMUCON4_VREFFAST_MSK                 BIT(3)
#define CORE_PMUCON4_IREFEN_MSK                   BIT(4)
#define CORE_PMUCON4_VDDBSET_SHIFT                5
#define CORE_PMUCON4_VDDBSET_MSK                 (0x7<<CORE_PMUCON4_VDDBSET_SHIFT)
#define CORE_PMUCON4_VDDSET_SHIFT                 8
#define CORE_PMUCON4_VDDSET_MSK                  (0x7<<CORE_PMUCON4_VDDSET_SHIFT)
#define CORE_PMUCON4_TSENSSET_SHIFT               11
#define CORE_PMUCON4_TSENSSET_MSK                (0x3<<CORE_PMUCON4_TSENSSET_SHIFT)
#define CORE_PMUCON4_VREFSET_SHIFT                13
#define CORE_PMUCON4_VREFSET_MSK                 (0x7<<CORE_PMUCON4_VREFSET_SHIFT)
#define CORE_PMUCON4_VCCMIPISET_SHIFT             16
#define CORE_PMUCON4_VCCMIPISET_MSK              (0x7<<CORE_PMUCON4_VCCMIPISET_SHIFT)
#define CORE_PMUCON4_VDD13BSET_SHIFT              19
#define CORE_PMUCON4_VDD13BSET_MSK               (0x7<<CORE_PMUCON4_VDD13BSET_SHIFT)
#define CORE_PMUCON4_VDD13CSET_SHIFT              22
#define CORE_PMUCON4_VDD13CSET_MSK               (0x7<<CORE_PMUCON4_VDD13CSET_SHIFT)
#define CORE_PMUCON4_VDD13CEN_MSK                 BIT(25)
#define CORE_PMUCON4_MIPIPGEN_MSK                 BIT(26)
#define CORE_PMUCON4_VCCMIPIEN_MSK                BIT(27)
#define CORE_PMUCON4_TESTSET_SHIFT                28
#define CORE_PMUCON4_TESTSET_MSK                 (0xfUL<<CORE_PMUCON4_TESTSET_SHIFT)

#define CORE_PMUCON5_LPSET_SHIFT                  0
#define CORE_PMUCON5_LPSET_MSK                   (0x7<<CORE_PMUCON5_LPSET_SHIFT)
#define CORE_PMUCON5_PMU_REF_VDD_SHIFT            3
#define CORE_PMUCON5_PMU_REF_VDD_MSK             (0x3f<<CORE_PMUCON5_PMU_REF_VDD_SHIFT)
#define CORE_PMUCON5_PMU_MIPIOCEN_VDD_MSK         BIT(11)

#define CORE_RFCON0_HXOSC_EN_MSK                  BIT(0)
#define CORE_RFCON0_VREF_EXT_EN_MSK               BIT(1)
#define CORE_RFCON0_XOPD_EN_MSK                   BIT(2)
#define CORE_RFCON0_XOPD_TEN_MSK                  BIT(3)
#define CORE_RFCON0_XO_ATE_EN_MSK                 BIT(4)
#define CORE_RFCON0_XO_ENLDO_MSK                  BIT(5)
#define CORE_RFCON0_XO_ENREF_MSK                  BIT(6)
#define CORE_RFCON0_XO_FX2_EN_MSK                 BIT(7)
#define CORE_RFCON0_XO_GM_EN_MSK                  BIT(8)
#define CORE_RFCON0_XO_CTI_SHIFT                  9
#define CORE_RFCON0_XO_CTI_MSK                   (0x1f<<CORE_RFCON0_XO_CTI_SHIFT)
#define CORE_RFCON0_XO_CTO_SHIFT                  14
#define CORE_RFCON0_XO_CTO_MSK                   (0x1f<<CORE_RFCON0_XO_CTO_SHIFT)
#define CORE_RFCON0_XO_CS_SHIFT                   19
#define CORE_RFCON0_XO_CS_MSK                    (0x1f<<CORE_RFCON0_XO_CS_SHIFT)
#define CORE_RFCON0_XO_DR_SHIFT                   24
#define CORE_RFCON0_XO_DR_MSK                    (0xffUL<<CORE_RFCON0_XO_DR_SHIFT)

#define CORE_RFCON1_ANATOP_EN_MSK                 BIT(0)
#define CORE_RFCON1_XOPD_SEL_SHIFT                1
#define CORE_RFCON1_XOPD_SEL_MSK                 (0x7<<CORE_RFCON0_XOPD_SEL_SHIFT)
#define CORE_RFCON1_XO_VBG_VSEL_SHIFT             4
#define CORE_RFCON1_XO_VBG_VSEL_MSK              (0x7<<CORE_RFCON1_XO_VBG_VSEL_SHIFT)
#define CORE_RFCON1_XO_DL_SEL_SHIFT               8
#define CORE_RFCON1_XO_DL_SEL_MSK                (0xf<<CORE_RFCON1_XO_DL_SEL_SHIFT)
#define CORE_RFCON1_XO_LDO_SEL_SHIFT              12
#define CORE_RFCON1_XO_LDO_SEL_MSK               (0xf<<CORE_RFCON1_XO_LDO_SEL_SHIFT)
#define CORE_RFCON1_XO_HYS_SHIFT                  16
#define CORE_RFCON1_XO_HYS_MSK                   (0x1f<<CORE_RFCON1_XO_HYS_SHIFT)

#define CORE_PMUCON6_LATCH_CNT_SHIFT              0
#define CORE_PMUCON6_LATCH_CNT_MSK               (0x3<<CORE_PMUCON6_LATCH_CNT_SHIFT)
#define CORE_PMUCON6_ISO_EN_CNT_SHIFT             2
#define CORE_PMUCON6_ISO_EN_CNT_MSK              (0x3<<CORE_PMUCON6_ISO_EN_CNT_SHIFT)
#define CORE_PMUCON6_PWRR_CNT_SHIFT               8
#define CORE_PMUCON6_PWRR_CNT_MSK                (0x3f<<CORE_PMUCON6_PWRR_CNT_SHIFT)
#define CORE_PMUCON6_PWRR1_CNT_SHIFT              16
#define CORE_PMUCON6_PWRR1_CNT_MSK               (0x3f<<CORE_PMUCON6_PWRR1_CNT_SHIFT)
#define CORE_PMUCON6_LATCH_DIS_CNT_SHIFT          22
#define CORE_PMUCON6_LATCH_DIS_CNT_MSK           (0x3<<CORE_PMUCON6_LATCH_DIS_CNT_SHIFT)
#define CORE_PMUCON6_CLKS_CNT_SHIFT               24
#define CORE_PMUCON6_CLKS_CNT_MSK                (0xf<<CORE_PMUCON6_CLKS_CNT_SHIFT)
#define CORE_PMUCON6_ISO_DIS_CNT_SHIFT            28
#define CORE_PMUCON6_ISO_DIS_DIS_CNT_MSK         (0xf<<CORE_PMUCON6_ISO_DIS_CNT_SHIFT)

#define CORE_PMUCON8_JTAG_MAP_SHIFT               0
#define CORE_PMUCON8_JTAG_MAP_MSK                (0xf<<CORE_PMUCON8_JTAG_MAP_SHIFT)
#define CORE_PMUCON8_VDD13A_ST_DLY_SHIFT          4
#define CORE_PMUCON8_VDD13A_ST_DLY_MSK           (0x1ff<<CORE_PMUCON8_VDD13A_ST_DLY_SHIFT)

#define CORE_TMRCON_CORETMREN_MSK                 BIT(0)
#define CORE_TMRCON_CORETMRRPTEN_MSK              BIT(1)
#define CORE_TMRCON_CORETMRPND_MSK                BIT(2)
#define CORE_TMRCON_CORETMRPND1_MSK               BIT(3)
#define CORE_TMRCON_COREPNDIE_MSK                 BIT(4)

#define CORE_TMRPR_CORETMRPR_SHIFT                0
#define CORE_TMRPR_CORETMRPR_MSK                 (0xffff<<CORE_TMRPR_CORETMRPR_SHIFT)

#define CORE_TMRRPT_COREPRTCNT_SHIFT              0
#define CORE_TMRRPT_COREPRTCNT_MSK               (0x1fffffff<<CORE_TMRRPT_COREPRTCNT_SHIFT)
#define CORE_TMRRPT_COREPRTCNTSUB_SHIFT           29
#define CORE_TMRRPT_COREPRTCNTSUB_MSK            (0x7UL<<CORE_TMRRPT_COREPRTCNTSUB_SHIFT)

#define CORE_TMRTRIM_SWTRIMEN_MSK                 BIT(0)
#define CORE_TMRTRIM_HSCOUNTPR_SHIFT              1
#define CORE_TMRTRIM_HSCOUNTPR_MSK               (0x3fffff<<CORE_TMRTRIM_HSCOUNTPR_SHIFT)

#define CORE_WKCON_WKUP_EN_MSK                    BIT(0)
#define CORE_WKCON_WKUP_EDGE_MSK                  BIT(1)
#define CORE_WKCON_WKUP_SEL_SHIFT                 2
#define CORE_WKCON_WKUP_SEL_MSK                  (0x3f<<CORE_WKCON_WKUP_SEL_SHIFT)
#define CORE_WKCON_WKUP_PND_MSK                   BIT(8)
#define CORE_WKCON_WKUP_IE_MSK                    BIT(9)
#define CORE_WKCON_WK_MCLR_RST_EN_MSK             BIT(10)
#define CORE_WKCON_WK_LVD_INT_EN_MSK              BIT(11)
#define CORE_WKCON_WK_LVD_RST_EN_MSK              BIT(12)
#define CORE_WKCON_WK_MCLR_RST_PNDS_MSK           BIT(13)
#define CORE_WKCON_WK_LVD_INT_PNDS_MSK            BIT(14)
#define CORE_WKCON_WK_LVD_RST_PNDS_MSK            BIT(15)
#define CORE_WKCON_CLEAR_PND_MSK                  BIT(16)
#define CORE_WKCON_CLEAR_MCLR_PND_MSK             BIT(17)
#define CORE_WKCON_CLEAR_LVD_INT_PND_MSK          BIT(18)
#define CORE_WKCON_CLEAR_LVD_RST_PND_MSK          BIT(19)

#define CORE_SECCON_PMUSEC_SEL                    BIT(0)

void pmu_pd_lvd_vcc_vol_set_sec(enum vcclvd_vol vol);
void pmu_vdd13a_lpwr_det_vol_set(uint8 vol_value);
void pmu_vdd13d_lpwr_det_vol_set(uint8 vol_value);
void pmu_vdd_lpwr_det_vol_set(uint8 vol_value);
void pmu_vcca_lpwr_det_vol_set(uint8 vol_value);
void pmu_vdd_oc_det_cur_set(uint8 cur_value);
void pmu_vdd_vol_set_sec(enum vdd_vol vol_value);
void pmu_vdd13b_vol_set_sec(enum vdd13_vol vol_value);
void pmu_vdd13c_vol_set_sec(enum vdd13_vol vol_value);
void pmu_vdd_ldo_bias_cur_set(uint8 cur_value);
void pmu_tsensor_chan_sel_sec(uint8 chan_idx);
void pmu_vref_vol_set_sec(enum vref_vol vol_value);
void pmu_vccmipi_vol_set_sec(enum vccmipi_vol vol_value);
void pmu_vdd13_ldo_dis_sec(void);
void pmu_xo_vbg_set_sec(uint8 xo_vbg);
void pmu_test_chan_sel(uint8 chan_idx);
void pmu_vcc_efuse_ldo_mod_sel(enum ldo_mode mode);
int pmu_vdd13a_stable_delay(uint16 dly);
int pmu_vdd13a_stable_delay_sec(uint16 dly);

#define pmu_pd_core_en()                        {PWRDMCTL->CORE_PMUCON0 |= CORE_PMUCON0_PD_CORE_EN_MSK;}
#define pmu_pd_rf_en()                          {PWRDMCTL->CORE_PMUCON0 |= CORE_PMUCON0_PD_RF_EN_MSK;}
#define pmu_pd_lvd_dbs_sel_core_dbs_clk()       {PWRDMCTL->CORE_PMUCON0 &= ~CORE_PMUCON0_LVD_DBS_SEL_MSK;}
#define pmu_pd_lvd_dbs_sel_256k()               {PWRDMCTL->CORE_PMUCON0 |= CORE_PMUCON0_LVD_DBS_SEL_MSK;}
#define pmu_pd_reset_fast_en()                  {PWRDMCTL->CORE_PMUCON0 |= CORE_PMUCON0_CORE_RST_FAST_EN_MSK;}
#define pmu_pd_boot_clk_sel_256k()              {PWRDMCTL->CORE_PMUCON0 &= ~CORE_PMUCON0_BOOT_CLK_SEL_MSK;}
#define pmu_pd_boot_clk_sel_32m()               {PWRDMCTL->CORE_PMUCON0 |= CORE_PMUCON0_BOOT_CLK_SEL_MSK;}
#define pmu_pd_vdd_set_bypass()                 {PWRDMCTL->CORE_PMUCON0 |= CORE_PMUCON0_VDDSET_BYPASS_MSK;}
#define pmu_pd_timer_clk_sel_256k()             {PWRDMCTL->CORE_PMUCON0 &= ~CORE_PMUCON0_PDTMRCLKSEL_MSK;}
#define pmu_pd_rc256k_hw_trim_en()              {PWRDMCTL->CORE_PMUCON0 |= CORE_PMUCON0_OSC_HW_TRIM_EN_MSK;}
#define pmu_pd_pwr_down_osc_en()                {PWRDMCTL->CORE_PMUCON0 |= CORE_PMUCON0_OSC_EN_MSK;}
#define pmu_pd_check_core_pd_pnd()              (PWRDMCTL->CORE_PMUCON3 & CORE_PMUCON3_CORE_PD_PND_MSK)
#define pmu_pd_clear_core_pd_pnd()              {PWRDMCTL->CORE_PMUCON3 |= CORE_PMUCON3_CORE_PD_PND_MSK;}
#define pmu_pd_check_rf_pd_pnd()                (PWRDMCTL->CORE_PMUCON3 & CORE_PMUCON3_RF_PD_PND_MSK)
#define pmu_pd_clear_rf_pd_pnd()                {PWRDMCTL->CORE_PMUCON3 |= CORE_PMUCON3_RF_PD_PND_MSK;}
#define pmu_pd_rf_latch_cpu_by_hw()             {PWRDMCTL->CORE_PMUCON3 |= CORE_PMUCON3_RF_LATCH_CPU_MSK;}
#define pmu_pd_io_latch_cpu_by_hw()             {PWRDMCTL->CORE_PMUCON3 |= CORE_PMUCON3_IO_LATCH_CPU_MSK;}
#define pmu_pd_get_xosc_status()               ((PWRDMCTL->CORE_PMUCON3 & CORE_PMUCON3_XOSC_STM_MSK)>>CORE_PMUCON3_XOSC_STM_SHIFT)
#define pmu_pd_set_anatop_en()                  {PWRDMCTL->CORE_RFCON1 |= CORE_RFCON1_ANATOP_EN_MSK;}
#define pmu_pd_timer_en()                       {PWRDMCTL->CORE_TMRCON |= CORE_TMRCON_CORETMREN_MSK;}
#define pmu_pd_timer_check_pnd()                (PWRDMCTL->CORE_TMRCON & CORE_TMRCON_CORETMRPND_MSK)
#define pmu_pd_timer_clear_pnd()                {PWRDMCTL->CORE_TMRCON &= ~CORE_TMRCON_CORETMRPND_MSK;}
#define pmu_pd_timer_check_pnd1()               (PWRDMCTL->CORE_TMRCON & CORE_TMRCON_CORETMRPND1_MSK)
#define pmu_pd_timer_clear_pnd1()               {PWRDMCTL->CORE_TMRCON &= ~CORE_TMRCON_CORETMRPND1_MSK;}
#define pmu_pd_timer_irq_en()                   {PWRDMCTL->CORE_TMRCON |= CORE_TMRCON_COREPNDIE_MSK;}
#define pmu_pd_timer_get_trim_clk_cnt()        ((PWRDMCTL->CORE_TMRPR & CORE_TMRPR_CORETMRPR_MSK) >> CORE_TMRPR_CORETMRPR_SHIFT)
#define pmu_pd_timer_get_hspeed_clk_cnt()      ((PWRDMCTL->CORE_TMRTRIM & CORE_TMRTRIM_HSCOUNTPR_MSK) >> CORE_TMRTRIM_HSCOUNTPR_SHIFT)
#define pmu_pd_rc256k_sw_trim_en()              {PWRDMCTL->CORE_TMRTRIM |= CORE_TMRTRIM_SWTRIMEN_MSK;}
#define pmu_pd_rc256k_sw_trim_get_busy()        (PWRDMCTL->CORE_TMRTRIM & CORE_TMRTRIM_SWTRIMEN_MSK)
#define pmu_pd_io_wkup_en()                     {PWRDMCTL->CORE_WKCON |= CORE_WKCON_WKUP_EN_MSK;}
#define pmu_pd_io_wkup_sel_rs_edge()            {PWRDMCTL->CORE_WKCON &= ~CORE_WKCON_WKUP_EDGE_MSK;}
#define pmu_pd_io_wkup_sel_fl_edge()            {PWRDMCTL->CORE_WKCON |= CORE_WKCON_WKUP_EDGE_MSK;}
#define pmu_pd_io_wkup_check_pnd()              (PWRDMCTL->CORE_WKCON & CORE_WKCON_WKUP_PND_MSK)
#define pmu_pd_io_wkup_clear_pnd()              {PWRDMCTL->CORE_WKCON |= CORE_WKCON_CLEAR_PND_MSK;}
#define pmu_pd_mclr_rst_check_pnd()             (PWRDMCTL->CORE_WKCON & CORE_WKCON_WK_MCLR_RST_PNDS_MSK)
#define pmu_pd_mclr_rst_clr_pnd()               (PWRDMCTL->CORE_WKCON |= CORE_WKCON_WK_MCLR_RST_PNDS_MSK)

void pmu_pd_alwayson_clk_cfg_sel(enum alwayson_clk clk);
void pmu_pd_alwayson_clk_cfg_sel_sec(enum alwayson_clk clk);
void pmu_pd_timer_trim_time_unit_set(uint8 x_ms);
void pmu_pd_timer_timeout_set(uint32 x_ms);
void pmu_pd_xosc_pre_coarse_set(uint8 cnt);
void pmu_pd_xosc_pre_fine_set(uint16 cnt);
int pmu_pd_io_wkup_sel_pin(uint8 pin_name);
int pmu_pd_io_wkup_sel_pin_sec(uint8 pin_name);
int jtag_map_set(uint8 val);

#define pmu_vdd_limit_cur_enable()              {PWRDMCTL->CORE_PMUCON4 &= ~CORE_PMUCON4_VDDLCEN_MSK;} //=0:enable
#define pmu_vdd_limit_cur_disable()             {PWRDMCTL->CORE_PMUCON4 |= CORE_PMUCON4_VDDLCEN_MSK;}
#define pmu_vref_open()                         {PWRDMCTL->CORE_PMUCON4 |= CORE_PMUCON4_VREFEN_MSK;}
#define pmu_vref_close()                        {PWRDMCTL->CORE_PMUCON4 &= ~CORE_PMUCON4_VREFEN_MSK;}
#define pmu_vref_fast_enable()                  {PWRDMCTL->CORE_PMUCON4 |= CORE_PMUCON4_VREFFAST_MSK;}
#define pmu_vref_fast_disable()                 {PWRDMCTL->CORE_PMUCON4 &= ~CORE_PMUCON4_VREFFAST_MSK;}
#define pmu_iref_open()                         {PWRDMCTL->CORE_PMUCON4 |= CORE_PMUCON4_IREFEN_MSK;}
#define pmu_iref_close()                        {PWRDMCTL->CORE_PMUCON4 &= ~CORE_PMUCON4_IREFEN_MSK;}

#define lvd_vdd13a_low_pwr_det_open()           {PWRDMCTL->LVD_CON |= LVD_CON_LVD13AEN_VDD_MSK;}
#define lvd_vdd13a_low_pwr_det_close()          {PWRDMCTL->LVD_CON &= ~LVD_CON_LVD13AEN_VDD_MSK;}
#define lvd_vdd13d_low_pwr_det_open()           {PWRDMCTL->LVD_CON |= LVD_CON_LVD13DEN_VDD_MSK;}
#define lvd_vdd13d_low_pwr_det_close()          {PWRDMCTL->LVD_CON &= ~LVD_CON_LVD13DEN_VDD_MSK;}
#define lvd_vcc_low_pwr_det_open()              {PWRDMCTL->LVD_CON |= LVD_CON_LVDVCCEN_VDD_MSK;}
#define lvd_vcc_low_pwr_det_close()             {PWRDMCTL->LVD_CON &= ~LVD_CON_LVDVCCEN_VDD_MSK;}
#define lvd_vdd_low_pwr_det_open()              {PWRDMCTL->LVD_CON |= LVD_CON_LVDVDDEN_VDD_MSK;}
#define lvd_vdd_low_pwr_det_close()             {PWRDMCTL->LVD_CON &= ~LVD_CON_LVDVDDEN_VDD_MSK;}
#define lvd_vdd_over_cur_det_open()             {PWRDMCTL->LVD_CON |= LVD_CON_VDDOCEN_VDD_MSK;}
#define lvd_vdd_over_cur_det_close()            {PWRDMCTL->LVD_CON &= ~LVD_CON_VDDOCEN_VDD_MSK;}

void tsensor_open(void);
void tsensor_close(void);
void pmu_iref_en_sec(void);
void pmu_iref_dis_sec(void);

static void core_sec_opt_func(uint32 a, uint32 b){
    PWRDMCTL->CORE_SECADR = (a); 
    PWRDMCTL->CORE_SECDAT = (b); 
    PWRDMCTL->CORE_SECKEY = (~0x3fac87e4);
    __NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();
}

#define LVDCON                                  (0x00)
#define LVDCON1                                 (0x04)
#define LVDCON2                                 (0x08)
#define PMUCON0                                 (0x10)
#define PMUCON1                                 (0x14)
#define PMUCON2                                 (0x18)
#define PMUCON3                                 (0x1c)
#define PMUCON4                                 (0x20)
#define PMUCON5                                 (0x24)
#define RFCON0                                  (0x28)
#define RFCON1                                  (0x2c)
#define PMUCON6                                 (0x30)
#define PMUCON7                                 (0x34)
#define PMUCON8                                 (0x38)
#define TMRCON                                  (0x80)
#define TMRPR                                   (0x84)
#define TMRRPT                                  (0x88)
#define TMRTRIM                                 (0x8c)
#define WKCON                                   (0xa0)
#define SECCON                                  (0xb0)
#define SECDAT                                  (0xb4)
#define SECADR                                  (0xb8)
#define SECKEY                                  (0xbc)
#define CORE_SEC_OPT(a, b)                      do{core_sec_opt_func(a, b);\
                                                }while(0);
#define pd_reg_sec_opt_en()                     {CORE_SEC_OPT(SECCON, 1);}
#define pd_reg_sec_opt_dis()                    {CORE_SEC_OPT(SECCON, 0);}
#define CORE_SEC_OPT_B(reg, data)  \
                              do { \
                                  if (PWRDMCTL->CORE_SECCON & 0x1) { \
                                      PWRDMCTL->CORE_SECADR = (uint32)&reg - (uint32)&PWRDMCTL->LVD_CON;\
                                      PWRDMCTL->CORE_SECDAT = (data);\
                                      PWRDMCTL->CORE_SECKEY = (~0x3fac87e4);\
                                  } else {\
                                      reg = data;\
                                  }\
                              } while(0)

void pmu_pd_timer_clear_pnd_sec(void);
void pmu_pd_timer_clear_pnd1_sec(void);
void pmu_pd_timer_trim_time_unit_set_sec(uint8 x_ms);
void pmu_pd_rc256k_sw_trim_en_sec(void);
void pmu_pd_rc256k_hw_trim_en_sec(void);
void pmu_pd_timer_clk_sel_256k_sec(void);
void pmu_pd_timer_timeout_set_sec(uint32 x_ms);
void pmu_pd_xosc_pre_coarse_set_sec(uint8 cnt);
void pmu_pd_xosc_pre_fine_set_sec(uint16 cnt);
void pmu_pd_timer_irq_en_sec(void);
void pmu_pd_timer_en_sec(void);
void pmu_pd_clear_core_pd_pnd_sec(void);
void pmu_pd_clear_rf_pd_pnd_sec(void);
void pmu_pd_rf_latch_cpu_by_hw_sec(void);
void pmu_pd_io_latch_cpu_by_hw_sec(void);
void pmu_pd_core_en_sec(void);
void pmu_pd_rf_en_sec(void);
void pmu_pd_lvd_dbs_sel_256k_sec(void);
void pmu_pd_pwr_down_osc_en_sec(void);
void pmu_pd_io_wkup_clear_pnd_sec(void);
void pmu_pd_boot_clk_sel_256k_sec(void);
void pmu_pd_io_wkup_en_sec(void);
void pmu_pd_io_wkup_sel_rs_edge_sec(void);
void pmu_pd_io_wkup_sel_fl_edge_sec(void);
void pmu_pd_io_wkup_ie_sec(void);
void pmu_pd_mclr_rst_en_sec(void);
void pmu_pd_mclr_rst_clear_pnd_sec(void);
void xo_set_cs_sec(uint8 xo_cs);
void xo_set_ct_sec(uint8 xo_ct);
void xo_set_dr_sec(uint8 xo_dr);
void pd_hxosc_en_sec(uint8 onoff);
void pmu_pd_set_anatop_en_sec(void);
void pmu_pd_set_anatop_dis_sec(void);

#define xo_get_cs()          ((PWRDMCTL->CORE_RFCON0 & CORE_RFCON0_XO_CS_MSK) >> CORE_RFCON0_XO_CS_SHIFT)
#define xo_get_dr()          ((PWRDMCTL->CORE_RFCON0 & CORE_RFCON0_XO_DR_MSK) >> CORE_RFCON0_XO_DR_SHIFT)

/** @defgroup ADKEY_MACRO-DEF & Exported_Functions
  * @{
  */

typedef struct {
    __IO uint32 ADKEY_CON;
    __IO uint32 ADKEY_BAUD;
    __IO uint32 ADKEY_DATA;
} ADKEY_TypeDef;

#define ADKEY     ((ADKEY_TypeDef *) ADKEY_BASE)

#define ADKEY_CON_ADKEY_SEL_SHIFT                0
#define ADKEY_CON_ADKEY_SEL_MSK                 (0x3f<<ADKEY_CON_ADKEY_SEL_SHIFT)
#define ADKEY_CON_ADKEY_BIASEN_MSK               BIT(6)
#define ADKEY_CON_ADKEY_HVDECT_MSK               BIT(7)
#define ADKEY_CON_ADKEY_ADCEN_MSK                BIT(8)
#define ADKEY_CON_ADKEY_LDOTEN_MSK               BIT(9)
#define ADKEY_CON_ADKEY_DACTEN_MSK               BIT(10)
#define ADKEY_CON_ADKEY_VCCATEN_MSK              BIT(11)
#define ADKEY_CON_ADKEY_DIGITALEN_MSK            BIT(12)
#define ADKEY_CON_ADKEY_INTEN_MSK                BIT(13)
#define ADKEY_CON_ADKEY_SAMPDON_MSK              BIT(14)
#define ADKEY_CON_ADKEY_AINHV_MSK                BIT(15)
#define ADKEY_CON_ADKEY_PERIOD_SHIFT             16
#define ADKEY_CON_ADKEY_PERIOD_MSK              (0xffff0000)

#define ADKEY_BAUD_ADKEY_BAUD_SHIFT              0
#define ADKEY_BAUD_ADKEY_BAUD_MSK               (0xfffffff<<ADKEY_BAUD_ADKEY_BAUD_SHIFT)
#define ADKEY_BAUD_BUFFER_EN_MSK                 BIT(28)
#define ADKEY_BAUD_CMPEN_MSK                     BIT(29)
#define ADKEY_BAUD_ADKEY_LDOEN_MSK               BIT(30)

#define ADKEY_DATA_ADKEY_DATA_SHIFT              0
#define ADKEY_DATA_ADKEY_DATA_MSK               (0x3ff<<ADKEY_DATA_ADKEY_DATA_SHIFT)

enum adkey_ain_idx {
    AIN0    =  0,
    AIN1    =  1,
    AIN2    =  2,
    AIN3    =  3,
    AIN4    =  4,
    AIN5    =  5,
    ADAIN6  =  6,
    ADAIN7  =  7,
    ADAIN8  =  8,
    ADAIN9  =  9,
    ADAIN10 =  10,
    ADAIN11 =  11,
    AIN6    =  31,
    AIN7    =  47
};

int32 adkey_select_channel(enum adkey_ain_idx idx);
#define adkey_bias_enable()            {ADKEY->ADKEY_CON |= ADKEY_CON_ADKEY_BIASEN_MSK;}
#define adkey_bias_disable()           {ADKEY->ADKEY_CON &= ~ADKEY_CON_ADKEY_BIASEN_MSK;}
#define adkey_over_vol_det_enable()    {ADKEY->ADKEY_CON |= ADKEY_CON_ADKEY_HVDECT_MSK;}
#define adkey_over_vol_det_disable()   {ADKEY->ADKEY_CON &= ~ADKEY_CON_ADKEY_HVDECT_MSK;}
#define adkey_adc_enable()             {ADKEY->ADKEY_CON |= ADKEY_CON_ADKEY_ADCEN_MSK;}
#define adkey_adc_disable()            {ADKEY->ADKEY_CON &= ~ADKEY_CON_ADKEY_ADCEN_MSK;}
#define adkey_ldo_test_enable()        {ADKEY->ADKEY_CON |= ADKEY_CON_ADKEY_LDOTEN_MSK;}
#define adkey_ldo_test_disable()       {ADKEY->ADKEY_CON &= ~ADKEY_CON_ADKEY_LDOTEN_MSK;}
#define adkey_dac_test_enable()        {ADKEY->ADKEY_CON |= ADKEY_CON_ADKEY_DACTEN_MSK;}
#define adkey_dac_test_disable()       {ADKEY->ADKEY_CON &= ~ADKEY_CON_ADKEY_DACTEN_MSK;}
#define adkey_vcca_test_enable()       {ADKEY->ADKEY_CON |= ADKEY_CON_ADKEY_VCCATEN_MSK;}
#define adkey_vcca_test_disable()      {ADKEY->ADKEY_CON &= ~ADKEY_CON_ADKEY_VCCATEN_MSK;}
#define adkey_logic_enable()           {ADKEY->ADKEY_CON |= ADKEY_CON_ADKEY_DIGITALEN_MSK;}
#define adkey_logic_disable()          {ADKEY->ADKEY_CON &= ~ADKEY_CON_ADKEY_DIGITALEN_MSK;}
#define adkey_intr_enable()            {ADKEY->ADKEY_CON |= ADKEY_CON_ADKEY_INTEN_MSK;}
#define adkey_intr_disable()           {ADKEY->ADKEY_CON &= ~ADKEY_CON_ADKEY_INTEN_MSK;}
#define adkey_check_done()             (ADKEY->ADKEY_CON & ADKEY_CON_ADKEY_SAMPDON_MSK)
#define adkey_clear_done()             {ADKEY->ADKEY_CON &= ~ADKEY_CON_ADKEY_SAMPDON_MSK;}
#define adkey_get_over_vol()           (ADKEY->ADKEY_CON & ADKEY_CON_ADKEY_AINHV_MSK)
void adkey_set_period(uint16 period);
void adkey_set_baud(uint32 baud);
#define adkey_buffer_enable()          {ADKEY->ADKEY_BAUD |= ADKEY_BAUD_BUFFER_EN_MSK;}
#define adkey_buffer_disable()         {ADKEY->ADKEY_BAUD &= ~ADKEY_BAUD_BUFFER_EN_MSK;}
#define adkey_comparer_enable()        {ADKEY->ADKEY_BAUD |= ADKEY_BAUD_CMPEN_MSK;}
#define adkey_comparer_disable()       {ADKEY->ADKEY_BAUD &= ~ADKEY_BAUD_CMPEN_MSK;}
#define adkey_ldo_enable()             {ADKEY->ADKEY_BAUD |= ADKEY_BAUD_ADKEY_LDOEN_MSK;}
#define adkey_ldo_disable()            {ADKEY->ADKEY_BAUD &= ~ADKEY_BAUD_ADKEY_LDOEN_MSK;}
#define adkey_get_data()               (ADKEY->ADKEY_DATA & ADKEY_DATA_ADKEY_DATA_MSK)
void adkey_init(void);
void tsensor_ref_get_from_efuse(void);
int32 tsensor_meas(uint8 sensor_idx);
float vcc_meas(void);
float vdd13b_meas(void);
float vdd13c_meas(void);
float io_input_meas(void);
uint32 io_input_meas_mv(void);

void mcu_reset(void);
void mcu_disable_watchdog(void);
void mcu_feed_watchdog(void);
void lvd_irq_handler(void *data);
void sysctrl_efuse_mac_addr_calc(uint8 *addr_buf);
uint16 sysctrl_efuse_get_customer_id(void);
uint8 sysctrl_efuse_get_vref(void);
uint8 sysctrl_efuse_get_xo_vbg(void);
uint8 sysctrl_efuse_get_xtal_id(void);
uint8 sysctrl_efuse_get_bios_id(void);
uint8 sysctrl_efuse_get_xo_cs(void);
uint8 sysctrl_efuse_get_xo_ct(void);
uint8 sysctrl_efuse_get_tx_analog_gain_mcs7(void);
uint8 sysctrl_efuse_get_tx_analog_gain_mcs3(void);
uint8 sysctrl_efuse_get_tx_analog_gain_mcs0(void);
int8 sysctrl_efuse_get_test_temp(void);
uint8 sysctrl_efuse_get_module_type(void);
uint8 sysctrl_efuse_get_vdd13_trim_valid(void);
uint8 sysctrl_efuse_get_vdd13b_trim(void);
uint8 sysctrl_efuse_get_vdd13c_trim(void);
uint8 sysctrl_efuse_get_dcn(void);
uint32 sysctrl_efuse_get_smt_dat(void);
uint8 sysctrl_efuse_get_module_crc(void);
int8 sysctrl_efuse_crc_check(void);

void pd_timer_init(void);
void pd_timer_start(uint32 x_ms);
void lf_timer_init(void);
void system_enter_sleep(void);
void system_exit_sleep(void);

/**
  * @}
  */

int32 gpio_enable(uint32 pin, uint8 on_off);


typedef struct
{
    __IO uint32_t RFDCOCCON0;
    __IO uint32_t RFDCOCCON1;
    __IO uint32_t RFDCOCCON2;
    __IO uint32_t RFDCOCCON3;
    __IO uint32_t RFDCOCCON4;
    __IO uint32_t RFPWRCON0;
    __IO uint32_t RFPWRCON1;
    __IO uint32_t RFPWRCON2;
    __IO uint32_t XOSCDFMCON0;
    __IO uint32_t XOSCDFMCON1;
    __IO uint32_t XOSCDFMCON2;
} RFDIGCAL_TypeDef;

#define RFDIGCAL                ((RFDIGCAL_TypeDef *) RFDIGCAL_BASE)


#define MODULE_TYPE_750M        1
#define MODULE_TYPE_900M        2
#define MODULE_TYPE_860M        3
#define MODULE_TYPE_750M_8305E  4
#define MODULE_TYPE_810M        5
#define MODULE_TYPE_850M        0x10

#define EFUSE_VREF              49
#define EFUSE_VREF_SHIFT        0
#define EFUSE_VREF_MSK          0x7

struct efuse_param {
    uint8  bios_id;
    uint8  xtal_id;
    int8   crc_check;
    int8   rf_valid_flag;
    uint8  vref;
    uint8  tx_ana_gain_mcs7;
    int8   tx_power_max;
    uint8  module_type;
    uint8  dcn;
    int8   smt_temp;
};
extern struct efuse_param module_efuse_info;

#ifdef __cplusplus
}
#endif

#endif //__SYSCTRL_H__

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2019 HUGE-IC *****END OF FILE****/
