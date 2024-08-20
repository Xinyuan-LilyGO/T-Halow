
// @file    pin_function.c
// @author  wangying
// @brief   This file contains all the mars pin functions.

// Revision History
// V1.0.0  06/01/2019  First Release, copy from 4001a project
// V1.0.1  07/05/2019  add lmac pin-func
// V1.0.2  07/06/2019  add sdio pull-up regs config
// V1.0.3  07/09/2019  add agc/rx-bw/lo-freq-idx gpio control
// V1.0.4  07/18/2019  change gpio-agc default index to 5
// V1.0.5  07/19/2019  uart1 only init tx
// V1.0.6  07/23/2019  add uart-rx pull-up resistor config
// V1.0.7  07/24/2019  switch-en1 disable; delete fdd/tdd macro-def switch
// V1.0.8  07/26/2019  not use pb17 for mac debug for it is used to reset ext-rf
// V1.0.9  07/29/2019  add function dbg_pin_func()
// V1.1.0  02/11/2020  add spi-pin-function
// V1.1.1  02/27/2020  fix uart1 pin-function
// V1.2.0  03/02/2020  add uart0-pin code and rf-pin code
// V1.2.1  03/26/2020  fix vmode pin
// V1.2.2  04/14/2020  use pa2 as lmac debug1:rx_req
// V1.2.3  09/12/2020  uart0 fix to A10/A11, uart1 fix to A12/A13

#include "typesdef.h"
#include "errno.h"
#include "list.h"
#include "dev.h"
#include "devid.h"
#include "hal/gpio.h"
#include "lib/mcu/mcu_util.h"

__weak void user_pin_func(int dev_id, int request){};

static int uart_pin_func(int dev_id, int request)
{
    int ret = RET_OK;

    switch (dev_id) {
        case HG_UART0_DEVID:
#ifdef FPGA_SUPPORT
            if (request) {
                gpio_set_mode(PIN_UART0_RX_A2_F4, GPIO_PULL_UP, GPIO_PULL_LEVEL_100K);
                gpio_set_altnt_func(PIN_UART0_RX_A2_F4, 4);
                gpio_set_altnt_func(PIN_UART0_TX_A3_F4, 4);
            } else {
                gpio_set_dir(PIN_UART0_RX_A2_F4, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_UART0_TX_A3_F4, GPIO_DIR_INPUT);
            }
#else
#ifdef DUAL_UART_DBG_PRINT
                if (request) {
                    gpio_set_altnt_func(PA_31, 9);
                } else {
                    gpio_set_dir(PA_31, GPIO_DIR_INPUT);
                }
#else
                if (request) {
                    gpio_set_mode(PIN_UART0_RX_A10_F4, GPIO_PULL_UP, GPIO_PULL_LEVEL_10K);
                    gpio_set_altnt_func(PIN_UART0_RX_A10_F4, 4);
                    gpio_set_altnt_func(PIN_UART0_TX_A11_F4, 4);
                } else {
                    gpio_set_dir(PIN_UART0_RX_A10_F4, GPIO_DIR_INPUT);
                    gpio_set_dir(PIN_UART0_TX_A11_F4, GPIO_DIR_INPUT);
                }
#endif
#endif
            break;
        case HG_UART1_DEVID:
            if (request) {
                gpio_set_mode(PIN_UART1_RX_A12_F3, GPIO_PULL_UP, GPIO_PULL_LEVEL_100K);
                gpio_set_altnt_func(PIN_UART1_RX_A12_F3, 3);
                gpio_set_altnt_func(PIN_UART1_TX_A13_F3, 3);
            } else {
                gpio_set_dir(PIN_UART1_RX_A12_F3, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_UART1_TX_A13_F3, GPIO_DIR_INPUT);
            }
            break;
        default:
            ret = EINVAL;
            break;
    }
    return ret;
}

static int gmac_pin_func(int dev_id, int request)
{
    int ret = RET_OK;

    switch (dev_id) {
        case HG_GMAC_DEVID:
            if (request) {
                gpio_set_altnt_func(PIN_GMAC_RMII_REF_CLKIN, 2);
//                gpio_set_altnt_func(PIN_GMAC_RMII_RX_ER, 2);
                gpio_set_altnt_func(PIN_GMAC_RMII_RXD0, 2);
                gpio_set_altnt_func(PIN_GMAC_RMII_RXD1, 2);
                gpio_set_altnt_func(PIN_GMAC_RMII_TXD0, 2);
                gpio_set_altnt_func(PIN_GMAC_RMII_TXD1, 2);
                gpio_set_altnt_func(PIN_GMAC_RMII_CRS_DV, 2);
                gpio_set_altnt_func(PIN_GMAC_RMII_TX_EN, 2);
#ifndef HG_GMAC_IO_SIMULATION
                gpio_set_altnt_func(PIN_GMAC_RMII_MDIO, 2);
                gpio_set_altnt_func(PIN_GMAC_RMII_MDC, 2);
#endif
                /* Enable the hysteresis function to reduce the effect of
                 * glitches as much as possible.
                 */
                gpio_ioctl(PIN_GMAC_RMII_REF_CLKIN, GPIO_INPUT_DELAY_ON_OFF, 1);
                gpio_ioctl(PIN_GMAC_RMII_RXD0, GPIO_INPUT_DELAY_ON_OFF, 1);
                gpio_ioctl(PIN_GMAC_RMII_RXD1, GPIO_INPUT_DELAY_ON_OFF, 1);
                gpio_ioctl(PIN_GMAC_RMII_TXD0, GPIO_INPUT_DELAY_ON_OFF, 1);
                gpio_ioctl(PIN_GMAC_RMII_TXD1, GPIO_INPUT_DELAY_ON_OFF, 1);
                gpio_ioctl(PIN_GMAC_RMII_CRS_DV, GPIO_INPUT_DELAY_ON_OFF, 1);
                gpio_ioctl(PIN_GMAC_RMII_TX_EN, GPIO_INPUT_DELAY_ON_OFF, 1);
            } else {
                gpio_set_dir(PIN_GMAC_RMII_REF_CLKIN, GPIO_DIR_INPUT);
//                gpio_set_dir(PIN_GMAC_RMII_RX_ER, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_GMAC_RMII_RXD0, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_GMAC_RMII_RXD1, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_GMAC_RMII_TXD0, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_GMAC_RMII_TXD1, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_GMAC_RMII_CRS_DV, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_GMAC_RMII_TX_EN, GPIO_DIR_INPUT);
//                gpio_set_dir(PIN_GMAC_RMII_MDIO, GPIO_DIR_INPUT);
//                gpio_set_dir(PIN_GMAC_RMII_MDC, GPIO_DIR_INPUT);
            }
            break;
        default:
            ret = EINVAL;
            break;
    }
    return ret;
}

//To fix gmac bugs
void gmac_csr_dv_disable(int dev_id)
{
    gpio_set_dir(PIN_GMAC_RMII_CRS_DV, GPIO_DIR_INPUT);
}

//To fix gmac bugs
void gmac_csr_dv_enable(int dev_id)
{
    gpio_set_altnt_func(PIN_GMAC_RMII_CRS_DV, 2);
}

static int dbg_pin_func(int dev_id, int request)
{
    int ret = RET_OK;
    
    switch (dev_id) {
        case HG_DBGPATH_DEVID:
            if (request) {
            #ifndef MACBUS_GMAC
                gpio_set_altnt_func(PIN_DBGPATH_DBG0_B0_F5, 5);
                gpio_set_altnt_func(PIN_DBGPATH_DBG1_B1_F5, 5);
                gpio_set_altnt_func(PIN_DBGPATH_DBG2_B2_F5, 5);
                gpio_set_altnt_func(PIN_DBGPATH_DBG3_B3_F5, 5);
                gpio_set_altnt_func(PIN_DBGPATH_DBG4_B4_F5, 5);
                gpio_set_altnt_func(PIN_DBGPATH_DBG5_B5_F5, 5);
                gpio_set_altnt_func(PIN_DBGPATH_DBG6_B6_F5, 5);
                gpio_set_altnt_func(PIN_DBGPATH_DBG7_B7_F5, 5);
                gpio_set_altnt_func(PIN_DBGPATH_DBG4_A22_F6, 6);
                gpio_set_altnt_func(PIN_DBGPATH_DBG5_A23_F6, 6);
                gpio_set_altnt_func(PIN_DBGPATH_DBG6_A24_F6, 6);
                gpio_set_altnt_func(PIN_DBGPATH_DBG7_A25_F6, 6);
            #endif
            } else {
            #ifndef MACBUS_GMAC
                gpio_set_dir(PIN_DBGPATH_DBG0_B0_F5, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_DBGPATH_DBG1_B1_F5, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_DBGPATH_DBG2_B2_F5, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_DBGPATH_DBG3_B3_F5, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_DBGPATH_DBG4_B4_F5, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_DBGPATH_DBG5_B5_F5, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_DBGPATH_DBG6_B6_F5, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_DBGPATH_DBG7_B7_F5, GPIO_DIR_INPUT);
            #endif
                gpio_set_dir(PIN_DBGPATH_DBG4_A22_F6, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_DBGPATH_DBG5_A23_F6, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_DBGPATH_DBG6_A24_F6, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_DBGPATH_DBG7_A25_F6, GPIO_DIR_INPUT);
            }
            break;
        default:
            ret = EINVAL;
            break;
    }
    return ret;
    
}

static int usb_pin_func(int dev_id, int request)
{
    int ret = RET_OK;

    switch (dev_id) {
        case HG_USB11_DEV_DEVID:
            if (request) {
                gpio_anolog(PIN_USB_DM_ANA, 1);
                gpio_anolog(PIN_USB_DP_ANA, 1);
            } else {
                gpio_set_dir(PIN_USB_DM_ANA, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_USB_DP_ANA, GPIO_DIR_INPUT);
            }
            break;
        default:
            ret = EINVAL;
            break;
    }
    return ret;
}

static int sdio_pin_func(int dev_id, int request)
{
    int ret = RET_OK;

    switch (dev_id) {
        case HG_SDIOSLAVE_DEVID:
            if (request) {
                gpio_set_altnt_func(PIN_SDCLK, 0);
                gpio_set_altnt_func(PIN_SDCMD, 0);
                gpio_set_mode(PIN_SDCMD, GPIO_PULL_UP, GPIO_PULL_LEVEL_100K);
                gpio_set_altnt_func(PIN_SDDAT0, 0);
                gpio_set_mode(PIN_SDDAT0, GPIO_PULL_UP, GPIO_PULL_LEVEL_100K);
                gpio_set_altnt_func(PIN_SDDAT1, 0);
                gpio_set_mode(PIN_SDDAT1, GPIO_PULL_UP, GPIO_PULL_LEVEL_100K);
                gpio_set_altnt_func(PIN_SDDAT2, 0);
                gpio_set_mode(PIN_SDDAT2, GPIO_PULL_UP, GPIO_PULL_LEVEL_100K);
                gpio_set_altnt_func(PIN_SDDAT3, 0);
                gpio_set_mode(PIN_SDDAT3, GPIO_PULL_UP, GPIO_PULL_LEVEL_100K);
//              #ifdef RAISE_SDIO_DS
                gpio_driver_strength(PIN_SDCMD, GPIO_DS_14MA);
                gpio_driver_strength(PIN_SDDAT0, GPIO_DS_14MA);
                gpio_driver_strength(PIN_SDDAT1, GPIO_DS_14MA);
                gpio_driver_strength(PIN_SDDAT2, GPIO_DS_14MA);
                gpio_driver_strength(PIN_SDDAT3, GPIO_DS_14MA);
//              #endif

                gpio_ioctl(PIN_SDCMD, GPIO_INPUT_DELAY_ON_OFF, 1);
                gpio_ioctl(PIN_SDCLK, GPIO_INPUT_DELAY_ON_OFF, 1);
                gpio_ioctl(PIN_SDDAT0, GPIO_INPUT_DELAY_ON_OFF, 1);
                gpio_ioctl(PIN_SDDAT1, GPIO_INPUT_DELAY_ON_OFF, 1);
                gpio_ioctl(PIN_SDDAT2, GPIO_INPUT_DELAY_ON_OFF, 1);
                gpio_ioctl(PIN_SDDAT3, GPIO_INPUT_DELAY_ON_OFF, 1);
            } else {
                gpio_set_dir(PIN_SDCLK, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_SDCMD, GPIO_DIR_INPUT);
                gpio_set_mode(PIN_SDCMD, GPIO_PULL_UP, GPIO_PULL_LEVEL_NONE);
                gpio_set_dir(PIN_SDDAT0, GPIO_DIR_INPUT);
                gpio_set_mode(PIN_SDDAT0, GPIO_PULL_UP, GPIO_PULL_LEVEL_NONE);
                gpio_set_dir(PIN_SDDAT1, GPIO_DIR_INPUT);
                gpio_set_mode(PIN_SDDAT1, GPIO_PULL_UP, GPIO_PULL_LEVEL_NONE);
                gpio_set_dir(PIN_SDDAT2, GPIO_DIR_INPUT);
                gpio_set_mode(PIN_SDDAT2, GPIO_PULL_UP, GPIO_PULL_LEVEL_NONE);
                gpio_set_dir(PIN_SDDAT3, GPIO_DIR_INPUT);
                gpio_set_mode(PIN_SDDAT3, GPIO_PULL_UP, GPIO_PULL_LEVEL_NONE);
            }
            break;
        default:
            ret = EINVAL;
            break;
    }
    return ret;
}

static int spi_pin_func(int dev_id, int request)
{
    int ret = RET_OK;

    switch (dev_id) {
        case HG_SPI0_DEVID:
            if (request) {
                gpio_set_dir(PIN_SPI0_CS, GPIO_DIR_OUTPUT);
                gpio_set_val(PIN_SPI0_CS, 1);
                gpio_set_altnt_func(PIN_SPI0_CLK, 0);
                gpio_set_altnt_func(PIN_SPI0_IO0, 0);
                gpio_set_altnt_func(PIN_SPI0_IO1, 0);
            } else {
                //gpio_set_dir(PIN_SPI0_CS, GPIO_DIR_INPUT);//201218
                gpio_set_dir(PIN_SPI0_CS, GPIO_DIR_OUTPUT);
                gpio_set_val(PIN_SPI0_CS, 1);
                gpio_set_dir(PIN_SPI0_CLK, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_SPI0_IO0, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_SPI0_IO1, GPIO_DIR_INPUT);
                gpio_set_altnt_func(PIN_MAC_DBG1_A2_F8, 8);
                //switch to uart0
                if (PIN_UART0_RX == PIN_UART0_RX_A2_F4) {
                    gpio_set_altnt_func(PIN_UART0_RX_A2_F4, 4);
                }
                if (PIN_UART0_TX == PIN_UART0_TX_A3_F4) {
                    gpio_set_altnt_func(PIN_UART0_TX_A3_F4, 4);
                }
#if defined K_VMODE_CNTL
                gpio_set_dir(PIN_PA_VMODE, GPIO_DIR_OUTPUT);
                gpio_set_val(PIN_PA_VMODE, 0); //PA3 PA_VMODE=0 to select ePA high power output
#endif
#ifdef MCU_PIR_SENSOR_MUX_SPI_IO
                gpio_set_dir(PA_2, GPIO_DIR_OUTPUT);
                gpio_set_val(PA_2, !!(mcu_pir_sensor_get() & BIT(0)));
                gpio_set_dir(PA_3, GPIO_DIR_OUTPUT);
                gpio_set_val(PA_3, !!(mcu_pir_sensor_get() & BIT(1)));
#endif
            }
            break;
        case HG_SPI1_DEVID:
            if (request) {
                gpio_set_dir(PIN_SPI1_CS, GPIO_DIR_OUTPUT);
                gpio_set_val(PIN_SPI1_CS, 1);
                gpio_set_altnt_func(PIN_SPI1_CLK, 3);
                gpio_set_altnt_func(PIN_SPI1_IO0, 3);
                gpio_set_altnt_func(PIN_SPI1_IO1, 3);
            } else {
                //gpio_set_dir(PIN_SPI1_CS, GPIO_DIR_INPUT);//201218
                gpio_set_dir(PIN_SPI1_CS, GPIO_DIR_OUTPUT);
                gpio_set_val(PIN_SPI1_CS, 1);
                gpio_set_dir(PIN_SPI1_CLK, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_SPI1_IO0, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_SPI1_IO1, GPIO_DIR_INPUT);
            }
            break;
        case HG_SPI3_DEVID:
            if (request) {
                gpio_set_altnt_func(PIN_SPI3_CS, 1);
                gpio_set_altnt_func(PIN_SPI3_CLK, 1);
                gpio_set_altnt_func(PIN_SPI3_IO0, 1);
                gpio_set_altnt_func(PIN_SPI3_IO1, 1);
            } else {
                gpio_set_dir(PIN_SPI3_CS, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_SPI3_CLK, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_SPI3_IO0, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_SPI3_IO1, GPIO_DIR_INPUT);
            }
            break;
        default:
            ret = EINVAL;
            break;
    }
    return ret;
}

static int iic_pin_func(int dev_id, int request)
{
    int ret = RET_OK;

    switch (dev_id) {
        case HG_I2C0_DEVID:
//            gpio_set_dir(PIN_IIC0_SCL_MAP0, GPIO_DIR_OUTPUT);
//            gpio_set_dir(PIN_IIC0_SDA_MAP0, GPIO_DIR_OUTPUT);
//            SYSCTRL->IO_MAP |= IO_MAP_IIC0_MAP0_MSK;
//            gpio_release(PIN_IIC0_SCL_MAP0);
//            gpio_release(PIN_IIC0_SDA_MAP0);
            break;
        default:
            ret = EINVAL;
            break;
    }
    return ret;
}

static int lmac_pin_func(int dev_id, int request)
{
    int ret = RET_OK;

    switch (dev_id) {
        case HG_LMAC_DEVID:
            if(request) {
#ifndef MCU_PIR_SENSOR_MUX_SPI_IO
                gpio_set_altnt_func(PIN_MAC_DBG1_A2_F8, 8);
#endif
                gpio_set_altnt_func(PIN_MAC_DBG3_B15_F7, 7);
                gpio_set_altnt_func(PIN_MAC_DBG0_B16_F7, 7);
                gpio_set_altnt_func(PIN_MAC_DBG1_B17_F7, 7);
            } else { //request == 0
                gpio_set_dir(PIN_MAC_DBG3_B15_F7, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_MAC_DBG0_B16_F7, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_MAC_DBG1_B17_F7, GPIO_DIR_INPUT);
            }
            break;
        default:
            ret = RET_ERR;
            break;
    }
    return ret;
}

static int rfspi_pin_func(int dev_id, int request)
{
    int ret = RET_OK;

    switch (dev_id) {
        case HG_RFSPI_DEVID:
            if(request == INT_PHY_EXT_RF_MODE) { //for ext-rf case, config phy part
                SYSCTRL->IO_MAP |= IO_MAP_RF_SPI_MASTER_MAP0_MSK;
                SYSCTRL->IO_MAP &= ~IO_MAP_RF_SPI_SLAVE_MAP0_MSK;
                gpio_set_altnt_func(PIN_RFSPI_MSTR_NSS_F3, 3);
                gpio_set_altnt_func(PIN_RFSPI_MSTR_MOSI_F3, 3);
                gpio_set_altnt_func(PIN_RFSPI_MSTR_MISO_F3, 3);
                gpio_set_altnt_func(PIN_RFSPI_MSTR_CLK_F3, 3);
            } else if (request == PHY_RF_NORMAL_MODE) { //ic normal case + debugout
                SYSCTRL->IO_MAP &= ~IO_MAP_RF_SPI_MASTER_MAP0_MSK;
                SYSCTRL->IO_MAP &= ~IO_MAP_RF_SPI_SLAVE_MAP0_MSK;
                gpio_set_altnt_func(PIN_RFSPI_DBG_NSS_F4, 4);
                gpio_set_altnt_func(PIN_RFSPI_DBG_MOSI_F4, 4);
                gpio_set_altnt_func(PIN_RFSPI_DBG_MISO_F4, 4);
                gpio_set_altnt_func(PIN_RFSPI_DBG_CLK_F4, 4);
            } else if(request == INT_RF_EXT_PHY_MODE) { //transceiver case
                SYSCTRL->IO_MAP &= ~IO_MAP_RF_SPI_MASTER_MAP0_MSK;
                SYSCTRL->IO_MAP |= IO_MAP_RF_SPI_SLAVE_MAP0_MSK;
                gpio_set_altnt_func(PIN_RFSPI_SLV_NSS_F1, 1);
                gpio_set_altnt_func(PIN_RFSPI_SLV_MOSI_F1, 1);
                gpio_set_altnt_func(PIN_RFSPI_SLV_MISO_F1, 1);
                gpio_set_altnt_func(PIN_RFSPI_SLV_CLK_F1, 1);
            } else { //request == 0
                SYSCTRL->IO_MAP &= ~IO_MAP_RF_SPI_MASTER_MAP0_MSK;
                SYSCTRL->IO_MAP &= ~IO_MAP_RF_SPI_SLAVE_MAP0_MSK;
                gpio_set_dir(PIN_RFSPI_MSTR_NSS_F3, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_RFSPI_MSTR_MOSI_F3, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_RFSPI_MSTR_MISO_F3, GPIO_DIR_INPUT);
                gpio_set_dir(PIN_RFSPI_MSTR_CLK_F3, GPIO_DIR_INPUT);
            }
            break;
        default:
            ret = EINVAL;
            break;
    }
    return ret;
}

static int rf_dev_pin_func(int dev_id, int request)
{
    int ret = RET_OK;

    switch (dev_id) {
        case HG_S1GRF_DEVID:
            if(request == INT_PHY_EXT_RF_MODE) { //for ext-rf case
                SYSCTRL->IO_MAP &= ~(IO_MAP_EXT_PHY_DEBUG_MAP0_MSK | IO_MAP_AD9361_MAP_MSK);
//                SYSCTRL->IO_MAP |= (IO_MAP_EXT_RF_DEBUG_MAP0_MSK|IO_MAP_RF_SWITCH_MAP0_MSK);
                SYSCTRL->IO_MAP |= IO_MAP_EXT_RF_DEBUG_MAP0_MSK;  //liuhm for FDD cal change 20190715
                sysctrl_internal_rf_en_cut_off();
                gpio_set_altnt_func(PIN_RXCLK_IN_B7_F0, 0);
                gpio_set_altnt_func(PIN_TXCLK_OUT_B12_F0, 0);
                gpio_set_altnt_func(PIN_CLK_IN_B9_F0, 0);
                gpio_set_altnt_func(PIN_TXNRX_B6_F1, 1);
                gpio_set_altnt_func(PIN_RX_EN_B10_F3, 3);
                #if defined(K_MIPI_IF)
                    gpio_set_altnt_func(PIN_MIPI_CLK_B11_F4, 4);
                    gpio_set_altnt_func(PIN_MIPI_DATA_B10_F4, 4);
                    gpio_set_altnt_func(PIN_MIPI_VIO_B12_F3, 3);
                #else
                    gpio_set_altnt_func(PIN_PA_EN_B16_F3, 3);
//                    gpio_set_altnt_func(PIN_SWITCH_EN1_B10_F0, 0); //liuhm for FDD cal change 20190715
                    gpio_set_altnt_func(PIN_SWITCH_EN2_B11_F0, 0);
                #endif
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D0_A14_F0, 0);
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D1_A15_F0, 0);
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D2_A16_F0, 0);
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D3_A17_F0, 0);
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D4_A18_F0, 0);
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D5_A19_F0, 0);
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D6_A20_F0, 0);
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D7_A21_F0, 0);
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D8_A26_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D9_A27_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D10_A28_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_TRX_D11_A29_F1, 1);

                gpio_set_altnt_func(PIN_EXT_RF_DPD_TX_D0_A4_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_DPD_TX_D1_A5_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_DPD_TX_D2_B0_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_DPD_TX_D3_B1_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_DPD_TX_D4_B2_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_DPD_TX_D5_B3_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_DPD_TX_D6_B4_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_DPD_TX_D7_B8_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_DPD_TX_D8_B14_F1, 1);
                gpio_set_altnt_func(PIN_EXT_RF_DPD_TX_D9_B15_F1, 1);

            } else if (request == PHY_RF_NORMAL_MODE) { //ic normal case + debugout
                SYSCTRL->IO_MAP &= ~IO_MAP_EXT_PHY_DEBUG_MAP0_MSK;
                SYSCTRL->IO_MAP &= ~(IO_MAP_EXT_RF_DEBUG_MAP0_MSK | IO_MAP_AD9361_MAP_MSK);
                SYSCTRL->IO_MAP |= IO_MAP_RF_SWITCH_MAP0_MSK; //switch SWITCH_EN mapping
                sysctrl_internal_rf_en_connected();
                if(PIN_SWITCH_EN1 == PIN_SWITCH_EN1_B10_F0) {
                    pmu_vccmipi_vol_set_sec(VCCMIPI_3P3V);
                    gpio_set_altnt_func(PIN_SWITCH_EN1_B10_F0, 0);
                    #ifdef K_SINGLE_PIN_SWITCH
                        #ifdef K_EXT_PA
                            gpio_set_altnt_func(PIN_PA_EN_B11_F3, 3);
                        #endif
                    #else //dual-pin switch
                        gpio_set_altnt_func(PIN_SWITCH_EN2_B11_F0, 0);
                        #ifdef K_EXT_PA
                            gpio_set_altnt_func(PIN_PA_EN_A2_F7, 7);
                        #endif
                    #endif
                }
                #if defined K_VMODE_CNTL
                    gpio_set_dir(PIN_PA_VMODE, GPIO_DIR_OUTPUT);
                    gpio_set_val(PIN_PA_VMODE, 0); //PA3 PA_VMODE=0 to select ePA high power output
                #endif
            } else if(request == INT_RF_EXT_PHY_MODE) { //transceiver case
                SYSCTRL->IO_MAP &= ~(IO_MAP_EXT_RF_DEBUG_MAP0_MSK | IO_MAP_AD9361_MAP_MSK);
                SYSCTRL->IO_MAP |= IO_MAP_EXT_PHY_DEBUG_MAP0_MSK;
                sysctrl_internal_rf_en_cut_off();
            } else { //request == 0
                SYSCTRL->IO_MAP &= ~IO_MAP_EXT_PHY_DEBUG_MAP0_MSK;
                SYSCTRL->IO_MAP &= ~IO_MAP_EXT_RF_DEBUG_MAP0_MSK;
                SYSCTRL->IO_MAP &= ~IO_MAP_AD9361_MAP_MSK;
            }
            break;
        default:
            ret = EINVAL;
            break;
    }
    return ret;
}

int pin_func(int dev_id, int request)
{
    int ret = RET_OK;

    sysctrl_unlock();
    
    switch (dev_id) {
        case HG_UART0_DEVID:
        case HG_UART1_DEVID:
            ret = uart_pin_func(dev_id, request);
            break;
        case HG_GMAC_DEVID:
            ret = gmac_pin_func(dev_id, request);
            break;
        case HG_USB11_DEV_DEVID:
            ret = usb_pin_func(dev_id, request);
            break;
        case HG_SDIOSLAVE_DEVID:
            ret = sdio_pin_func(dev_id, request);
            break;
        case HG_SPI0_DEVID:
        case HG_SPI1_DEVID:
        case HG_SPI3_DEVID:
            ret = spi_pin_func(dev_id, request);
            break;
        case HG_I2C0_DEVID:
            ret = iic_pin_func(dev_id, request);
            break;
        case HG_LMAC_DEVID:
            ret = lmac_pin_func(dev_id, request);
            break;
        case HG_RFSPI_DEVID:
            ret = rfspi_pin_func(dev_id, request);
            break;
        case HG_S1GRF_DEVID:
            ret = rf_dev_pin_func(dev_id, request);
            break;
        case HG_DBGPATH_DEVID:
            ret = dbg_pin_func(dev_id, request);
            break;
        default:
            break;
    }
    user_pin_func(dev_id, request);    
    sysctrl_lock();    
    return ret;
}

