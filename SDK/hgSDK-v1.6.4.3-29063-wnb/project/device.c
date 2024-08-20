
#include "typesdef.h"
#include "list.h"
#include "dev.h"
#include "devid.h"
#include "osal/string.h"
#include "osal/semaphore.h"
#include "osal/mutex.h"
#include "osal/timer.h"
#include "osal/task.h"

#include "hal/uart.h"
#include "hal/i2c.h"
#include "hal/wphy.h"
#include "hal/rfspi.h"
#include "hal/dbgpath.h"
#include "hal/tdma.h"
#include "hal/rf_device.h"
#include "hal/rfdigicali.h"
//#include "hal/rfmipi.h"
#include "hal/timer_device.h"
#include "hal/dma.h"
#include "hal/netdev.h"
#include "hal/spi.h"
#include "hal/spi_nor.h"
#include "hal/sysaes.h"
#include "lib/syscfg.h"
#include "lib/ethernet_phy/eth_mdio_bus.h"
#include "lib/ethernet_phy/eth_phy.h"

#ifdef ETHERNET_IP101G
#include "lib/ethernet_phy/phy/ip101g.h"
#endif
#ifdef ETHERNET_RTL8201F
#include "lib/ethernet_phy/phy/rtl8201f.h"
#endif
#ifdef ETHERNET_SZ18201
#include "lib/ethernet_phy/phy/sz18201.h"
#endif
#ifdef AUTO_ETHERNET_PHY
#include "lib/ethernet_phy/phy/auto_phy.h"
#endif

#include "lib/ota/fw.h"

#include "dev/uart/hguart.h"
#include "dev/i2c/hgi2c_dw.h"
#include "dev/sdio/hgsdio20_slave.h"
#include "dev/dma/dw_dmac.h"
#include "dev/gpio/hggpio_v2.h"
#include "dev/tdma/hgtdma.h"
#include "dev/wphy/hgwphy_ah.h"
#include "dev/dbgpath/hgdbgpath.h"
#include "dev/rfspi/hgrfspi_v2.h"
#include "dev/rf_device/hgrf_s1gv3.h"
#include "dev/rfdigicali/hgrfdigicali_ah.h"
//#include "dev/rfmipi/hgrfmipi.h"
#include "dev/timer/hgtimer_v2.h"
#include "dev/dma/hg_m2m_dma.h"
#include "dev/usb/hgusb11_dev_api.h"
#include "dev/emac/hg_gmac_eva.h"
#include "dev/wdt/hg_wdt_v1.h"
#include "dev/spi/hgspi_dw.h"
#include "dev/crc/hg_crc.h"
#include "dev/sysaes/hg_sysaes.h"

#include "drv_usart.h"
#include "device.h"

extern const struct hgwphy_ah_cfg nphyahcfg;
extern union _dpd_ram dpd_ram;
extern const uint32 rx_imb_iq_normal[6];
extern const union hgdbgpath_cfg ndbgpathcfg;
extern const union hgrfmipi_cfg nrfmipicfg;
extern struct dma_device *m2mdma;
struct sys_config sys_cfgs;

struct hgusb11_dev usb_dev = {
    .usb_hw = (struct hgusb11_dev_hw *)HG_USB11_DEVICE_BASE,
    .irq_num = USB_CTL_IRQn,
    .sof_irq_num = USB_SOF_IRQn,
};

struct hgsdio20_slave sdioslave = {
    .hw = (struct hgsdio20_slave_hw *)HG_SDIO20_SLAVE_BASE,
    .irq_num = HGSDIO20_IRQn,
    .rst_irq_num = HGSDIO20_RST_IRQn,
    .block_size = 64,
};

struct hg_crc crc32_module = {
    .hw = (struct hg_crc_hw *)HG_CRC32_BASE,
    .irq_num = CRC_IRQn,
};

struct hguart uart0 = {
    .hw = (struct hguart_hw *) HG_UART0_BASE,
    .irq_num = UART0_IRQn
};
struct hguart uart1 = {
    .hw = (struct hguart_hw *) HG_UART1_BASE,
    .irq_num = UART1_IRQn
};

struct hggpio_v2 gpioa = {
    .hw = (struct hggpio_v2_hw *)HG_GPIOA_BASE,
    .irq_num = GPIOA_IRQn,
    .pin_num = {0, 31},
};

struct hggpio_v2 gpiob = {
    .hw = (struct hggpio_v2_hw *)HG_GPIOB_BASE,
    .irq_num = GPIOB_IRQn,
    .pin_num = {32, 50},
};

struct hgi2c_dw hgi2c0 = {
    .hw = (struct hgi2c_dw_reg *)IIC0_BASE,
    .irq_num = IIC0_IRQn,
};

struct hgdma_dw dmac = {
    .hw = (struct hgdma_dw_hw *)DMAC_BASE,
    .irq_num = DMAC_IRQn,
};

struct hgtdma tdma = {
    .hw = (struct hgtdma_hw *)TDMA_BASE,
};
struct hgtdma tdma2 = {
    .hw = (struct hgtdma_hw *)TDMA2_BASE,
};

struct hgrfspi_v2 rfspi_v2 = {
    .hw = (struct hgrfspi_v2_hw *)ZH_RFSPI_BASE,
};

struct hgwphy_ah wphy = {
    .pwphyreg = (struct hgwphy_ah_reg *)HG_WPHY_AH_BASE,
    .prximbtab = (uint32 *)rx_imb_iq_normal,
};

struct hgdbgpath dbgpath = {
    .pdbgpathreg = (struct hgdbgpath_reg *)DBGPATH_BASE,
    .pdbgpathcfg = &ndbgpathcfg,
};

struct hgrfdigicali rfdigicali = {
    .prfdigicalireg = (struct hgrfdigicali_reg *)RFDIGCAL_BASE,
};

//struct hgrfmipi rfmipi = {
//    .prfmipireg = (struct hgrfmipi_reg *)MIPI_BASE,
//    .prfmipicfg = &nrfmipicfg, 
//};
#ifndef SYS_IRQ_STAT
struct hgtimer_v2 timer0 = {
    .hw      = (struct hgtimer_v2_hw *)HG_TIMER0_BASE,
    .irq_num = TIM0_IRQn,
};
#endif
struct hgtimer_v2 timer2 = {
    .hw      = (struct hgtimer_v2_hw *)HG_TIMER2_BASE,
    .irq_num = TIM2_IRQn,
};

struct mem_dma_dev mem_dma = {
    .hw      = (struct mem_dma_hw *)M2M_DMA0_BASE,
};

struct hg_gmac_eva gmac = {
    .hw      = (struct hg_gmac_eva_hw *)HG_GMAC_BASE,
    .irq_num = GMAC_IRQn,
    .tx_buf_size = 8*1024,
    .rx_buf_size = 8*1024,
    .modbus_devid = HG_ETH_MDIOBUS0_DEVID,
    .phy_devid    = HG_ETHPHY0_DEVID,    
#ifdef HG_GMAC_IO_SIMULATION
    .mdio_pin = HG_GMAC_MDIO_PIN,
    .mdc_pin  = HG_GMAC_MDC_PIN,
#endif
};

struct hg_wdt_v1 watchdog = {
    .hw = (struct hg_wdt_v1_hw *)WDT_BASE,
    .irq_num = WDT_IRQn,
};

struct hg_sysaes sysaes = {
    .hw = (struct hg_sysaes_hw *)SYS_AES_BASE,
    .irq_num = SYS_AES_IRQn,
};

struct hgspi_dw spi0 = {
    .hw      = (struct hgspi_dw_hw *)SPI0_BASE,
    .irq_num = SPI0_IRQn,
    .cs_pin  = {1, PIN_SPI0_CS},
};

struct hgspi_dw spi1 = {
    .hw      = (struct hgspi_dw_hw *)SPI1_BASE,
    .irq_num = SPI1_IRQn,
    .cs_pin  = {1, PIN_SPI1_CS},
};

struct spi_nor_flash flash0 = {
    .spidev      = (struct spi_device *)&spi0,
    .spi_config  = {12000000, SPI_CLK_MODE_3, SPI_WIRE_NORMAL_MODE, 0},
    .vendor_id   = 0,
    .product_id  = 0,
    .size        = 0x100000,
    .sector_size = 0x1000,
    .page_size   = 256,
    .mode        = SPI_NOR_NORMAL_SPI_MODE,
};

struct ethernet_mdio_bus mdio_bus0;

#ifdef ETHERNET_IP101G
struct ethernet_phy_device ethernet_phy0 = {
    .addr = ETHERNET_PHY_ADDR,
    .drv  = &ip101g_driver,
};
#endif
#ifdef ETHERNET_RTL8201F
struct ethernet_phy_device ethernet_phy0 = {
    .addr = ETHERNET_PHY_ADDR,
    .drv  = &rtl8201f_driver,
};
#endif
#ifdef ETHERNET_SZ18201
struct ethernet_phy_device ethernet_phy0 = {
    .addr = ETHERNET_PHY_ADDR,
    .drv  = &sz18201_driver,
};
#endif
#ifdef AUTO_ETHERNET_PHY
struct ethernet_phy_device ethernet_phy0 = {
    .addr = ETHERNET_PHY_ADDR,
    .drv  = &auto_phy_driver,
};
#endif

struct ota_info_type ota_info = {
    .flash0      = &flash0,
    /* If flash1 is not NULL, it means dual firmware function is used. */
    .flash1      = &flash0,
    /* The following content is determined by the boot loader and cannot
     * be modified.
     */
    .addr0       = 0x00000000,
    .addr1       = 0x00080000,
};

struct hgrf_s1gv3 rf_s1g;

void device_init(void)
{
    extern usart_handle_t console_handle;

    hggpio_v2_attach(HG_GPIOA_DEVID, &gpioa);
    hggpio_v2_attach(HG_GPIOB_DEVID, &gpiob);
    
    hguart_attach(HG_UART0_DEVID, &uart0);
    hguart_attach(HG_UART1_DEVID, &uart1);
    
    hgsdio20_slave_attach(HG_SDIOSLAVE_DEVID, &sdioslave);

    hgtdma_attach(HG_TDMA_DEVID, &tdma);
    hgtdma_attach(HG_TDMA2_DEVID, &tdma2);

    hgwphy_ah_attach(HG_AHPHY_DEVID, &wphy, &nphyahcfg, &dpd_ram);
    
    hgdbgpath_attach(HG_DBGPATH_DEVID, &dbgpath);

    hgrfdigicali_attach(HG_RFDIGICALI_DEVID, &rfdigicali);
    
//    hgrfmipi_attach(HG_MIPI_DEVID, &rfmipi);
    hgrfspi_v2_attach(HG_RFSPI_DEVID, &rfspi_v2);

    hgrf_s1gv3_attach(HG_S1GRF_DEVID, &rf_s1g);
#ifndef SYS_IRQ_STAT
    hgtimer_v2_attach(HG_TIMER0_DEVID, &timer0);
#endif
    hgtimer_v2_attach(HG_TIMER2_DEVID, &timer2);
    
    mem_dma_dev_attach(HG_M2MDMA_DEVID, &mem_dma);
    m2mdma = (struct dma_device *)&mem_dma;

    dw_dmac_attach(HG_DMAC_DEVID, &dmac);

    hgusb11_dev_attach(HG_USB11_DEV_DEVID, &usb_dev);
    
    hg_gmac_attach(HG_GMAC_DEVID, &gmac);

    hg_wdt_v1_attach(HG_WDTV1_DEVID, &watchdog);

    hg_sysaes_attach(HG_HWAES_DEVID, &sysaes);
    
    //spi_nor_master
    hgspi_dw_attach(HG_SPI0_DEVID, &spi0);
    spi_nor_attach(&flash0, HG_SPI_FLASH0_DEVID);
    hg_crc_attach(HG_CRC_DEVID, &crc32_module);
    
    eth_mdio_bus_attach(HG_ETH_MDIOBUS0_DEVID, &mdio_bus0);
    eth_phy_attach(HG_ETHPHY0_DEVID, &ethernet_phy0);

    hgspi_dw_attach(HG_SPI1_DEVID, &spi1);

//cfg print
#if defined(MACBUS_USB) || defined(DUAL_UART_DBG_PRINT)
    uart_open((struct uart_device *)&uart0);
    console_handle = (usart_handle_t)&uart0;
#else
    uart_open((struct uart_device *)&uart1);
    console_handle = (usart_handle_t)&uart1;
#endif
}

struct gpio_device *gpio_get(uint32 pin)
{
    if (pin >= gpioa.pin_num[0] && pin <= gpioa.pin_num[1]) {
        return (struct gpio_device *)&gpioa;
    }
    if (pin >= gpiob.pin_num[0] && pin <= gpiob.pin_num[1]) {
        return (struct gpio_device *)&gpiob;
    }
    return NULL;
}

int32 syscfg_info_get(struct syscfg_info *pinfo)
{
#ifdef SYSCFG_ENABLE
    pinfo->flash1 = &flash0;
    pinfo->flash2 = &flash0;
    pinfo->size   = ALIGN(sizeof(struct sys_config), pinfo->flash1->sector_size);
    pinfo->addr1  = pinfo->flash1->size - (2 * pinfo->size);
    pinfo->addr2  = pinfo->flash1->size - pinfo->size;
    ASSERT((pinfo->addr1 & ~(pinfo->flash1->sector_size - 1)) == pinfo->addr1);
    ASSERT((pinfo->addr2 & ~(pinfo->flash2->sector_size - 1)) == pinfo->addr2);
    ASSERT((pinfo->size >= sizeof(struct sys_config)) && 
           (pinfo->size == (pinfo->size & ~(pinfo->flash1->sector_size - 1))));
    return 0;
#else
    return -1;
#endif
}

void syscfg_save(void)
{
    syscfg_write(&sys_cfgs, sizeof(sys_cfgs));
}

#if ERRLOG_SIZE
int32 errlog_flashinfo(struct spi_nor_flash **flash, uint32 *addr, uint32 *size)
{
   *flash = &flash0;
    /* need keep syscfg region: the last 3 sector. */
    *addr = flash0.size - (10+3)*flash0.sector_size;
    *size = 10*flash0.sector_size; //10 sectors.
    return RET_OK;
}
#endif

