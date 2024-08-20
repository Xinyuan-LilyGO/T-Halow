// Revision History
// V1.0.0  06/01/2019  First Release, copy from 4001a project
// V1.0.1  07/27/2019  change uart0 to A2/A3
// V1.0.2  02/07/2020  change PIN_SPI_CS to PIN_SPI0_CS
// V1.1.0  03/02/2020  add pa/pa-vmode pin

#ifndef _PIN_NAMES_DEF_H_
#define _PIN_NAMES_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

enum pin_name {
    PA_0  =  0,
    PA_1,
    PA_2,
    PA_3,
    PA_4,
    PA_5,
    PA_6,
    PA_7,
    PA_8,
    PA_9,
    PA_10,
    PA_11,
    PA_12,
    PA_13,
    PA_14,
    PA_15,
    PA_16,
    PA_17,
    PA_18,
    PA_19,
    PA_20,
    PA_21,
    PA_22,
    PA_23,
    PA_24,
    PA_25,
    PA_26,
    PA_27,
    PA_28,
    PA_29,
    PA_30,
    PA_31,
    PB_0,
    PB_1,
    PB_2,
    PB_3,
    PB_4,
    PB_5,
    PB_6,
    PB_7,
    PB_8,
    PB_9,
    PB_10,
    PB_11,
    PB_12,
    PB_13,
    PB_14,
    PB_15,
    PB_16,
    PB_17,
    PB_18,

///////////////////UART PIN DEF/////////////////
    PIN_UART0_RX_A12_F0  =  PA_12,
    PIN_UART0_TX_A13_F0  =  PA_13,
    PIN_UART0_RX_A14_F3  =  PA_14,
    PIN_UART0_TX_A15_F3  =  PA_15,
    PIN_UART0_RX_A2_F4   =  PA_2,
    PIN_UART0_TX_A3_F4   =  PA_3,
    PIN_UART0_RX_A10_F4  =  PA_10,
    PIN_UART0_TX_A11_F4  =  PA_11,
    
    PIN_UART1_RX_A0_F1   =  PA_0,
    PIN_UART1_TX_A1_F1   =  PA_1,
    PIN_UART1_RX_A14_F1  =  PA_14,
    PIN_UART1_TX_A15_F1  =  PA_15,
    PIN_UART1_RX_A12_F3  =  PA_12,
    PIN_UART1_TX_A13_F3  =  PA_13,

    PIN_UART0_RX         =  PIN_UART0_RX_A12_F0,
    PIN_UART0_TX         =  PIN_UART0_TX_A13_F0,

    PIN_UART1_RX         =  PIN_UART1_RX_A0_F1,
    PIN_UART1_TX         =  PIN_UART1_TX_A1_F1,

    STDIO_UART_TX        =  PIN_UART0_TX,
    STDIO_UART_RX        =  PIN_UART0_RX,
    
///////////////////IIC PIN DEF//////////////////
    PIN_IIC_SCL_A12_F1  =  PA_12,
    PIN_IIC_SCL_A0_F4   =  PA_0,
    PIN_IIC_SCL_A14_F4  =  PA_14,
    PIN_IIC_SDA_A13_F1  =  PA_13,
    PIN_IIC_SDA_A1_F4   =  PA_1,
    PIN_IIC_SDA_A15_F4  =  PA_15,
    
    PIN_IIC_SCL         =  PIN_IIC_SCL_A12_F1,
    PIN_IIC_SDA         =  PIN_IIC_SDA_A13_F1,
    
///////////////////GMAC PIN DEF/////////////////
    PIN_GMAC_RMII_REF_CLKIN  =  PB_0,
    PIN_GMAC_RMII_RX_ER      =  PB_1,
    PIN_GMAC_RMII_RXD0       =  PB_2,
    PIN_GMAC_RMII_RXD1       =  PB_3,
    PIN_GMAC_RMII_TXD0       =  PB_4,
    PIN_GMAC_RMII_TXD1       =  PB_5,
    PIN_GMAC_RMII_CRS_DV     =  PB_6,
    PIN_GMAC_RMII_TX_EN      =  PB_7,
    PIN_GMAC_RMII_MDIO       =  PA_10,
    PIN_GMAC_RMII_MDC        =  PA_11,
    
///////////////////SDIO PIN DEF/////////////////
    PIN_SDCLK   = PA_6,
    PIN_SDCMD   = PA_7,
    PIN_SDDAT0  = PA_8,
    PIN_SDDAT1  = PA_9,
    PIN_SDDAT2  = PA_10,
    PIN_SDDAT3  = PA_11,
    
///////////////////USB PIN DEF//////////////////
    PIN_USB_DM_ANA  =  PA_12,
    PIN_USB_DP_ANA  =  PA_13,
    
///////////////////SPI PIN DEF//////////////////
    PIN_SPI0_CS_A0_F0    =  PA_0,
    PIN_SPI0_CS_A24_F2   =  PA_24,
    PIN_SPI0_CS_A1_F6    =  PA_1,
    PIN_SPI0_CLK_A1_F0   =  PA_1,
    PIN_SPI0_CLK_A0_F6   =  PA_0,
    PIN_SPI0_IO0_A2_F0   =  PA_2,
    PIN_SPI0_IO0_A3_F6   =  PA_3,
    PIN_SPI0_IO1_A3_F0   =  PA_3,
    PIN_SPI0_IO1_A2_F6   =  PA_2,
    PIN_SPI0_IO2_A30_F0  =  PA_30,
    PIN_SPI0_IO2_A22_F2  =  PA_22,
    PIN_SPI0_IO3_A31_F0  =  PA_31,
    PIN_SPI0_IO3_A23_F2  =  PA_23,
    
    PIN_SPI1_CS_A22_F0   =  PA_22,
    PIN_SPI1_CS_A6_F3    =  PA_6,
    PIN_SPI1_CLK_A23_F0  =  PA_23,
    PIN_SPI1_CLK_A7_F3   =  PA_7,
    PIN_SPI1_IO0_A24_F0  =  PA_24,
    PIN_SPI1_IO0_A8_F3   =  PA_8,
    PIN_SPI1_IO1_A25_F0  =  PA_25,
    PIN_SPI1_IO1_A8_F2   =  PA_8,
    PIN_SPI1_IO1_A9_F3   =  PA_9,
    PIN_SPI1_IO2_A26_F0  =  PA_26,
    PIN_SPI1_IO2_A10_F3  =  PA_10,
    PIN_SPI1_IO3_A27_F0  =  PA_27,
    PIN_SPI1_IO3_A11_F0  =  PA_11,
    
    PIN_SPI3_CLK_A6_F1   =  PA_6,
    PIN_SPI3_MOSI_A7_F1  =  PA_7,
    PIN_SPI3_MISO_A8_F1  =  PA_8,
    PIN_SPI3_CS_A9_F1    =  PA_9,
    
    PIN_SPI0_CS          =  PIN_SPI0_CS_A0_F0,
    PIN_SPI0_CLK         =  PIN_SPI0_CLK_A1_F0,
    PIN_SPI0_IO0         =  PIN_SPI0_IO0_A2_F0,
    PIN_SPI0_IO1         =  PIN_SPI0_IO1_A3_F0,
    PIN_SPI0_IO2         =  PIN_SPI0_IO2_A30_F0,
    PIN_SPI0_IO3         =  PIN_SPI0_IO3_A31_F0,

    PIN_SPI1_CS          =  PIN_SPI1_CS_A6_F3,
    PIN_SPI1_CLK         =  PIN_SPI1_CLK_A7_F3,
    PIN_SPI1_IO0         =  PIN_SPI1_IO0_A8_F3,
    PIN_SPI1_IO1         =  PIN_SPI1_IO1_A9_F3,
    PIN_SPI1_IO2         =  PIN_SPI1_IO2_A10_F3,
    PIN_SPI1_IO3         =  PIN_SPI1_IO3_A11_F0,

    PIN_SPI3_CS          =  PIN_SPI3_CS_A9_F1,
    PIN_SPI3_CLK         =  PIN_SPI3_CLK_A6_F1,
    PIN_SPI3_IO0         =  PIN_SPI3_MOSI_A7_F1,
    PIN_SPI3_IO1         =  PIN_SPI3_MISO_A8_F1,
    
///////////////////RFSPI PIN DEF////////////////
    PIN_RFSPI_MSTR_NSS_F3   =  PA_22,
    PIN_RFSPI_MSTR_MOSI_F3  =  PA_23,
    PIN_RFSPI_MSTR_MISO_F3  =  PA_24,
    PIN_RFSPI_MSTR_CLK_F3   =  PA_25,
    
    PIN_RFSPI_DBG_NSS_F4    =  PA_22,
    PIN_RFSPI_DBG_MOSI_F4   =  PA_23,
    PIN_RFSPI_DBG_MISO_F4   =  PA_24,
    PIN_RFSPI_DBG_CLK_F4    =  PA_25,
    
    PIN_RFSPI_SLV_NSS_F1    =  PA_22,
    PIN_RFSPI_SLV_MOSI_F1   =  PA_23,
    PIN_RFSPI_SLV_MISO_F1   =  PA_24,
    PIN_RFSPI_SLV_CLK_F1    =  PA_25,
    
///////////////////MAC_DBG PIN DEF//////////////
    PIN_MAC_DBG0_A22_F7  =  PA_22,
    PIN_MAC_DBG0_B16_F7  =  PB_16,
    PIN_MAC_DBG0_A3_F8   =  PA_3,
    PIN_MAC_DBG1_A23_F7  =  PA_23,
    PIN_MAC_DBG1_B17_F7  =  PB_17,
    PIN_MAC_DBG1_A2_F8   =  PA_2,
    PIN_MAC_DBG2_B14_F7  =  PB_14,
    PIN_MAC_DBG2_A6_F9   =  PA_6,
    PIN_MAC_DBG3_B15_F7  =  PB_15,
    PIN_MAC_DBG3_A7_F9   =  PA_7,
    PIN_MAC_DBG4_A12_F7  =  PA_12,
    PIN_MAC_DBG4_B12_F7  =  PB_12,
    PIN_MAC_DBG4_A8_F9   =  PA_8,
    PIN_MAC_DBG5_A13_F7  =  PA_13,
    PIN_MAC_DBG5_B13_F7  =  PB_13,
    PIN_MAC_DBG5_A9_F9   =  PA_9,
    PIN_MAC_DBG6_B0_F7   =  PB_0,
    PIN_MAC_DBG6_A10_F9  =  PA_10,
    PIN_MAC_DBG7_B1_F7   =  PB_1,
    PIN_MAC_DBG7_A11_F9  =  PA_11,
    PIN_MAC_DBG8_A4_F9   =  PA_4,
    PIN_MAC_DBG9_A5_F9   =  PA_5,
    
    PIN_MAC_DBG0         =  PIN_MAC_DBG0_B16_F7,
    PIN_MAC_DBG1         =  PIN_MAC_DBG1_B17_F7,

///////////////////DBGPATH_DBG PIN DEF///////////
    PIN_DBGPATH_DBG0_A10_F8  =  PA_10,
    PIN_DBGPATH_DBG0_A0_F9   =  PA_0,
    PIN_DBGPATH_DBG1_A11_F8  =  PA_11,
    PIN_DBGPATH_DBG1_A1_F9   =  PA_1,
    PIN_DBGPATH_DBG2_A12_F8  =  PA_12,
    PIN_DBGPATH_DBG2_A2_F9   =  PA_2,
    PIN_DBGPATH_DBG3_A13_F8  =  PA_13,
    PIN_DBGPATH_DBG3_A3_F9   =  PA_3,
    PIN_DBGPATH_DBG4_A22_F6  =  PA_22,
    PIN_DBGPATH_DBG5_A23_F6  =  PA_23,
    PIN_DBGPATH_DBG6_A24_F6  =  PA_24,
    PIN_DBGPATH_DBG7_A25_F6  =  PA_25,
    PIN_DBGPATH_DBG0_B0_F5   =  PB_0,
    PIN_DBGPATH_DBG1_B1_F5   =  PB_1,
    PIN_DBGPATH_DBG2_B2_F5   =  PB_2,
    PIN_DBGPATH_DBG3_B3_F5   =  PB_3,
    PIN_DBGPATH_DBG4_B4_F5   =  PB_4,
    PIN_DBGPATH_DBG5_B5_F5   =  PB_5,
    PIN_DBGPATH_DBG6_B6_F5   =  PB_6,
    PIN_DBGPATH_DBG7_B7_F5   =  PB_7,

///////////////////RF PIN DEF////////////////////
    PIN_EXT_RF_TRX_D0_A14_F0     =  PA_14,
    PIN_EXT_RF_TRX_D1_A15_F0     =  PA_15,
    PIN_EXT_RF_TRX_D2_A16_F0     =  PA_16,
    PIN_EXT_RF_TRX_D3_A17_F0     =  PA_17,
    PIN_EXT_RF_TRX_D4_A18_F0     =  PA_18,
    PIN_EXT_RF_TRX_D5_A19_F0     =  PA_19,
    PIN_EXT_RF_TRX_D6_A20_F0     =  PA_20,
    PIN_EXT_RF_TRX_D7_A21_F0     =  PA_21,
    PIN_EXT_RF_TRX_D8_A26_F1     =  PA_26,
    PIN_EXT_RF_TRX_D9_A27_F1     =  PA_27,
    PIN_EXT_RF_TRX_D10_A28_F1    =  PA_28,
    PIN_EXT_RF_TRX_D11_A29_F1    =  PA_29,
    PIN_EXT_RF_DPD_TX_D0_A4_F1   =  PA_4,
    PIN_EXT_RF_DPD_TX_D1_A5_F1   =  PA_5,
    PIN_EXT_RF_DPD_TX_D2_B0_F1   =  PB_0,
    PIN_EXT_RF_DPD_TX_D3_B1_F1   =  PB_1,
    PIN_EXT_RF_DPD_TX_D4_B2_F1   =  PB_2,
    PIN_EXT_RF_DPD_TX_D5_B3_F1   =  PB_3,
    PIN_EXT_RF_DPD_TX_D6_B4_F1   =  PB_4,
    PIN_EXT_RF_DPD_TX_D7_B8_F1   =  PB_8,
    PIN_EXT_RF_DPD_TX_D8_B14_F1  =  PB_14,
    PIN_EXT_RF_DPD_TX_D9_B15_F1  =  PB_15,

/*******************************************/
/*  for phy-only mode                      */
/*  use RXCLK_IN_B7_F1 & TXCLK_OUT_B12_F0  */
/*  for rf-only mode                       */
/*  use RXCLK_OUT_B7_F1 & RXCLK_IN_B12_F1  */
/*******************************************/
    PIN_RXCLK_IN_B7_F0           =  PB_7,
    PIN_TXCLK_OUT_B12_F0         =  PB_12,
    PIN_RXCLK_OUT_B7_F1          =  PB_7,
    PIN_RXCLK_IN_B12_F1          =  PB_12,
    
    PIN_CLK_IN_B9_F0             =  PB_9,
    PIN_CLK_OUT_B9_F1            =  PB_9,
    PIN_TXNRX_B6_F1              =  PB_6,
    PIN_RX_EN_B10_F3             =  PB_10,
    
    PIN_AGC_IDX0_B0_F0           =  PB_0,
    PIN_AGC_IDX0_B13_F2          =  PB_13,
    PIN_AGC_IDX1_B1_F0           =  PB_1,
    PIN_AGC_IDX1_B16_F2          =  PB_16,
    PIN_AGC_IDX2_B2_F0           =  PB_2,
    PIN_AGC_IDX2_B17_F2          =  PB_17,
    PIN_IDX_LATCH_B6_F0          =  PB_6,
    PIN_IDX_LATCH_B8_F0          =  PB_8,
    PIN_IDX_LATCH_A13_F2         =  PA_13,
    
    PIN_AGC_IDX0                 =  PIN_AGC_IDX0_B0_F0,
    PIN_AGC_IDX1                 =  PIN_AGC_IDX1_B1_F0,
    PIN_AGC_IDX2                 =  PIN_AGC_IDX2_B2_F0,
    PIN_IDX_LATCH                =  PIN_IDX_LATCH_B8_F0,
    
    PIN_PA_EN_A10_F1             =  PA_10,
    PIN_PA_EN_A3_F2              =  PA_3,
    PIN_PA_EN_A11_F2             =  PA_11,
    PIN_PA_EN_A12_F2             =  PA_12,
    PIN_PA_EN_B11_F3             =  PB_11,
    PIN_PA_EN_B16_F3             =  PB_16,
    PIN_PA_EN_A23_F5             =  PA_23,
    PIN_PA_EN_B10_F6             =  PB_10,
    PIN_PA_EN_A9_F7              =  PA_9,
    PIN_PA_EN_A24_F7             =  PA_24,
    PIN_PA_EN_A25_F7             =  PA_25,
    PIN_PA_EN_A2_F7              =  PA_2,
    
    PIN_PA_EN                    =  PIN_PA_EN_B16_F3,
    PIN_PA_VMODE                 =  PA_3,
    
    PIN_SWITCH_EN1_B10_F0        =  PB_10,
    PIN_SWITCH_EN1_A0_F2         =  PA_0,
    PIN_SWITCH_EN1_A12_F4        =  PA_12,
    PIN_SWITCH_EN1_A24_F5        =  PA_24,
    PIN_SWITCH_EN1_A10_F7        =  PA_10,
    PIN_SWITCH_EN2_B11_F0        =  PB_11,
    PIN_SWITCH_EN2_A1_F2         =  PA_1,
    PIN_SWITCH_EN2_A13_F4        =  PA_13,
    PIN_SWITCH_EN2_A25_F5        =  PA_25,
    PIN_SWITCH_EN2_A11_F7        =  PA_11,
    
    PIN_SWITCH_EN1               =  PIN_SWITCH_EN1_B10_F0,
    PIN_SWITCH_EN2               =  PIN_SWITCH_EN2_B11_F0,
    
    PIN_RF_POR_B4_F0             =  PB_4,
    PIN_RF_EN_9361_B5_F1         =  PB_5,
    PIN_TRXIQ_B13_F1             =  PB_13,
    
    PIN_MIPI_CLK_B10_F1          =  PB_10,
    PIN_MIPI_CLK_B11_F4          =  PB_11,
    PIN_MIPI_DATA_B11_F1         =  PB_11,
    PIN_MIPI_DATA_B10_F4         =  PB_10,
    PIN_MIPI_VIO_B1_F3           =  PB_1,
    PIN_MIPI_VIO_B12_F3          =  PB_12,
    PIN_MIPI_VIO_B13_F3          =  PB_13,
    
///////////////////OTHER PIN DEF//////////////////
    PIN_CLK_TO_IO_A10_F2  =  PA_10,
    
    PIN_ATT_LE1 = PA_31,//200522 for 4002 husf
    PIN_ATT_LE2 = PA_30,//200522 for 4002 husf
    PIN_ATT_CLK = PA_2,
    PIN_ATT_DAT = PA_3,
};

#ifdef __cplusplus
}
#endif
#endif
