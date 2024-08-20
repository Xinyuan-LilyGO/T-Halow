#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "dev.h"
#include "devid.h"
#include "osal/irq.h"
#include "osal/semaphore.h"
#include "dev/spi/hgspi_dw.h"
#include "hal/gpio.h"
#include "hal/dma.h"

static void hgspi_dma_tx_irq_hdl(struct dma_device *p_dma, uint32 ch, enum dma_irq_type irq, uint32 data)
{
    struct hgspi_dw *dev = (struct hgspi_dw *)data;
    /* release channel */
    dma_stop(p_dma, ch);
    
    os_sema_up(&dev->tx_dma_sema);
}

static void hgspi_dma_rx_irq_hdl(struct dma_device *p_dma, uint32 ch, enum dma_irq_type irq, uint32 data)
{
    struct hgspi_dw *dev = (struct hgspi_dw *)data;
    /* release channel */
    dma_stop(p_dma, ch);
    
    os_sema_up(&dev->rx_dma_sema);
}

/**
  * @brief  SPI module Disable designware spi device function
  * @param  p_spi       : Select the initialized SPI module pointer
  * @retval None
  */
static inline void hgspi_dw_disable(struct hgspi_dw_hw *p_spi)
{
    /** disable spi operations, then program spi control regs is possible */
    p_spi->SSIENR = HGSPI_DW_SSI_DISABLE;
}

/**
  * @brief  SPI module Enable designware spi device function
  * @param  p_spi       : Select the initialized SPI module pointer
  * @retval None
  */
static inline void hgspi_dw_enable(struct hgspi_dw_hw *p_spi)
{
    p_spi->SSIENR = HGSPI_DW_SSI_ENABLE;
}

/**
  * @brief  SPI module test whether spi is send over function
  * @param  p_spi       : Select the initialized SPI module pointer
  * @retval 1           : over
  *         0           : not over
  */
static inline int32 hgspi_dw_get_tx_fifo_empty(struct hgspi_dw_hw *p_spi)
{
    return ((p_spi->SR & HGSPI_DW_SR_TFE));
}

/**
  * @brief  SPI module test whether spi is busy function
  * @param  p_spi       : Select the initialized SPI module pointer
  * @retval 1           : busy
  *         0           : not busy
  */
static inline int32 hgspi_dw_get_busy(struct hgspi_dw_hw *p_spi)
{
    return ((p_spi->SR & HGSPI_DW_SR_BUSY) != 0);
}

/**
  * @brief  SPI module wait spi send over function
  * @param  p_spi       : Select the initialized SPI module pointer
  * @retval None
  */
static inline void hgspi_dw_wait_tx_done(struct hgspi_dw_hw *p_spi)
{
    while (!hgspi_dw_get_tx_fifo_empty(p_spi));
    while (hgspi_dw_get_busy(p_spi));
}

/**
 * @brief   ll_spi_get_dfs
 * @param   p_spi     : spi register structure pointer
 * @retval  dfs
 */
static inline uint32 hgspi_dw_get_dfs(struct hgspi_dw_hw *p_spi)
{
    return ((p_spi->CTRLR0 & 0xF) + 1);
}

/**
  * @brief  SPI module test whether spi is ready to receive function
  * @param  p_spi       : Select the initialized SPI module pointer
  * @retval 1           : ready
  *         0           : not ready
  */
static inline int32 hgspi_dw_get_rx_ready_sta(struct hgspi_dw_hw *p_spi)
{
    return ((p_spi->SR & HGSPI_DW_SR_RFNE) != 0);
}

/**
  * @brief  SPI module read data from spi receive fifo function
  * @param  p_spi       : Select the initialized SPI module pointer
  * @retval data received
  */
static inline int32 hgspi_dw_getdata(struct hgspi_dw_hw *p_spi)
{
    return (int32_t)p_spi->DATAREG;
}

/**
 * @brief   receive one char from spi in poll method, blocked function
 * @param[in]   p_spi : spi register structure pointer
 * @retval  data received by the spi
 */
static inline int32 hgspi_dw_poll_rcv_dat(struct hgspi_dw_hw *p_spi)
{
    /** wait until spi is ready to receive */
    while (!hgspi_dw_get_rx_ready_sta(p_spi)); /* blocked */
    /** receive data */
    return hgspi_dw_getdata(p_spi);
}

/**
 * @brief   Set spi mode
 * @param   p_spi     : spi register structure pointer
 * @param   mode      : TYPE_ENUM_LL_SPI_MODE
 * @retval  None
 */
static inline void hgspi_dw_set_mode(struct hgspi_dw_hw *p_spi, uint32 mode)
{
    hgspi_dw_wait_tx_done(p_spi);

    hgspi_dw_disable(p_spi);
    p_spi->CTRLR0 = (p_spi->CTRLR0 & ~(HGSPI_DW_CTRLR0_TMOD_MASK)) |
                    (mode);
    hgspi_dw_enable(p_spi);
}

/**
  * @brief  SPI module test whether spi is ready to send function
  * @param  p_spi       : Select the initialized SPI module pointer
  * @retval 1           : ready
  *         0           : not ready
  */
static inline uint32 hgspi_dw_get_tx_ready_sta(struct hgspi_dw_hw *p_spi)
{
    return ((p_spi->SR & HGSPI_DW_SR_TFNF) != 0);
}

/**
 * @brief   send char by spi in poll method, blocked function
 * @param[in]   p_spi : spi register structure pointer
 * @param[in]   data        data to be sent
 */
static inline void hgspi_dw_poll_send_dat(struct hgspi_dw_hw *p_spi, uint32 data)
{
    /** wait until spi is ready to send */
    while (!hgspi_dw_get_tx_ready_sta(p_spi)); /* blocked */
    /** send char */
    p_spi->DATAREG = data;
}

/**
 * @brief   spi Enable bit interrupt with mask
 * @param   p_spi : spi register structure pointer
 * @param   mask  : TYPE_ENUM_LL_SPI_INT_MSK
 * @retval  None
 */
static inline void hgspi_dw_unmask_interrupt(struct hgspi_dw_hw *p_spi, uint32 mask)
{
    p_spi->IMR |= mask;
}



/**
  * @brief  Low layer SPI sets wire mode
  * @param  p_spi    : The structure pointer of the SPI group (SPI0, SPI1) is selected
  * @param  wire_mode: The wire mode to be set
  * @retval None
  */
static void hgspi_dw_set_wire_mode(struct hgspi_dw_hw *p_spi, uint32 wire_mode)
{
    hgspi_dw_wait_tx_done(p_spi);

    hgspi_dw_disable(p_spi);
    
    p_spi->CTRLR0 = (p_spi->CTRLR0 & (~(0x3<<21))) | (wire_mode<<21);

    hgspi_dw_enable(p_spi);
}

/**
  * @brief  Low layer SPI gets wire mode
  * @param  p_spi    : The structure pointer of the SPI group (SPI0, SPI1) is selected
  * @retval Return the spi wire mode
  */
static uint32 hgspi_dw_get_wire_mode(struct hgspi_dw_hw *p_spi)
{
    return ((p_spi->CTRLR0 >> 21) & (0x3));
}

/* interrupt handler */
static void hgspi_dw_irq_handler(void *data)
{
    struct hgspi_dw *dev = (struct hgspi_dw *)data;
    uint32 isr_status = dev->hw->ISR;
    
    //clear all interrupt pending
    (void)dev->hw->ICR;
    
    dev->irq_hdl(isr_status, dev->irq_data);
}

static int32 hgspi_dw_open(struct spi_device *p_spi, uint32 clk_freq, uint32 work_mode,
                           uint32 wire_mode, uint32 clk_mode)
{
    struct hgspi_dw *dev = (struct hgspi_dw *)p_spi;
    uint32 clk_div_cnt;
    int32 ret;
    
    if (dev->opened) {
        return -EBUSY;
    }
    
    if (p_spi == (struct spi_device *)dev_get(HG_SPI0_DEVID)) {
        SYSCTRL_REG_OPT(
            sysctrl_spi0_clk_open();
            sysctrl_spi0_reset();
        );
    } else if (p_spi == (struct spi_device *)dev_get(HG_SPI1_DEVID)) {
        SYSCTRL_REG_OPT(
            sysctrl_spi1_clk_open();
            sysctrl_spi1_reset();
        );
    } else if (p_spi == (struct spi_device *)dev_get(HG_SPI3_DEVID)) {
        SYSCTRL_REG_OPT(
            sysctrl_spi3_clk_open();
            sysctrl_spi3_reset();
        );
    }
    
    if(pin_func(p_spi->dev.dev_id, 1) != RET_OK) {
        return RET_ERR;
    }
    
    if(request_irq(dev->irq_num, hgspi_dw_irq_handler, dev) != RET_OK) {
        return RET_ERR;
    }
    
    hgspi_dw_disable(dev->hw);
    
    /* Clear interrupts */
    uint32 ctrl0_reg = dev->hw->ICR;
    /* Mask all interrupts */
    dev->hw->IMR = 0;
    
    ctrl0_reg = HGSPI_DW_CTRLR0_FRF_MOTOROLA        | 
                HGSPI_DW_TMOD_TRANSMIT_RECEIVE      | 
                (clk_mode << 6)                     | 
                (8 - 1)                             | //frame size
                HGSPI_DW_CTRLR0_SLV_OE_ENABLE;
    
    switch(wire_mode) {
        case SPI_WIRE_NORMAL_MODE:
            ctrl0_reg |= HGSPI_DW_NORMAL_MODE << 21;
            break;
//        case SPI_WIRE_DUAL_MODE:
//            ctrl0_reg |= HGSPI_DW_DUAL_MODE << 21;
//            break;
//        case SPI_WIRE_QUAD_MODE:
//            ctrl0_reg |= HGSPI_DW_QUAD_MODE << 21;
//            break;
        default:
            return RET_ERR;
    };
    
    dev->hw->CTRLR0  = ctrl0_reg;
    dev->hw->CTRLR1  = 0;
    dev->hw->DMATDLR = 0;
    dev->hw->DMARDLR = 0;
    dev->hw->DMACR   = 0;

    /* set spi clk */
    clk_div_cnt = sys_get_apbclk() / clk_freq;
    ASSERT((clk_div_cnt >= 2) && (clk_div_cnt <= 65534));
    dev->hw->BAUDR         = clk_div_cnt;
    dev->hw->SPICTRLR0     = (0<<11) | (2<<8) | (0<<2);
    dev->hw->RX_SAMPLE_DLY = 0;
    
    /* Set threshold values for both tx and rx */
    dev->hw->TXFTLR = 0;
    dev->hw->RXFTLR = 0;
    
    if(work_mode == SPI_MASTER_MODE) {
        dev->hw->SER = 1;
    } else {
        dev->hw->SER = 0;
    }

    hgspi_dw_enable(dev->hw);
    
    ret = os_sema_init(&dev->tx_dma_sema, 0);
    if(ret != RET_OK) {
        return ret;
    }
    ret = os_sema_init(&dev->rx_dma_sema, 0);
    if(ret != RET_OK) {
        os_sema_del(&dev->tx_dma_sema);
        return ret;
    }
    
    dev->opened = 1;
    return RET_OK;
}

static int32 hgspi_dw_close(struct spi_device *p_spi)
{
    struct hgspi_dw *dev = (struct hgspi_dw *)p_spi;

    if (!dev->opened) {
        return RET_OK;
    }
    
    irq_disable(dev->irq_num);
    pin_func(p_spi->dev.dev_id, 0);
    hgspi_dw_disable(dev->hw);
    
    os_sema_del(&dev->tx_dma_sema);
    os_sema_del(&dev->rx_dma_sema);
    
    dev->opened = 0;
    return RET_OK;
}

static int32 hgspi_dw_ioctl(struct spi_device *p_spi, uint32 cmd, uint32 param)
{
    struct hgspi_dw *dev = (struct hgspi_dw *)p_spi;
    uint32 temp;
    
    switch(cmd) {
        case SPI_WIRE_MODE_SET:
            {
                switch(param) {
                    case SPI_WIRE_NORMAL_MODE:
                        temp = HGSPI_DW_NORMAL_MODE;
                        break;
//                    case SPI_WIRE_DUAL_MODE:
//                        temp = HGSPI_DW_DUAL_MODE;
//                        break;
//                    case SPI_WIRE_QUAD_MODE:
//                        temp = HGSPI_DW_QUAD_MODE;
//                        break;
                    default:
                        return RET_ERR;
                };
                hgspi_dw_set_wire_mode(dev->hw, temp);
            }
            break;
        case SPI_WIRE_MODE_GET:
            {
                switch(hgspi_dw_get_wire_mode(dev->hw)) {
                    case HGSPI_DW_NORMAL_MODE:
                        temp = SPI_WIRE_NORMAL_MODE;
                        break;
//                    case HGSPI_DW_DUAL_MODE:
//                        temp = SPI_WIRE_DUAL_MODE;
//                        break;
//                    case HGSPI_DW_QUAD_MODE:
//                        temp = SPI_WIRE_QUAD_MODE;
//                        break;
                    default:
                        return RET_ERR;
                }
                return temp;
            }
        case SPI_DW_INTR_SET:
            hgspi_dw_unmask_interrupt(dev->hw, param);
            break;
        case SPI_DMAC_USE:
            dev->dma = (struct dma_device *)param;
            if(dev->dma) {
                dev->hw->DMATDLR = 0;
                dev->hw->DMARDLR = 0;
                dev->hw->DMACR   = HGSPI_DW_DMACR_TDMAE_EN;
            } else {
                dev->hw->DMACR   = 0;
            }
            break;
        default:
            return RET_ERR;
    }
    
    return RET_OK;
}

static int32 hgspi_dw_read(struct spi_device *p_spi, void *buf, uint32 size)
{
    struct hgspi_dw *dev = (struct hgspi_dw *)p_spi;
    uint8 *p_data = buf;
    struct dma_xfer_data xfer_data;
    
    if(size) {
        hgspi_dw_wait_tx_done(dev->hw);
        hgspi_dw_disable(dev->hw);
        dev->hw->CTRLR0 = (dev->hw->CTRLR0 & ~(HGSPI_DW_CTRLR0_TMOD_MASK)) |
                          (HGSPI_DW_TMOD_RECEIVE_ONLY);
        hgspi_dw_enable(dev->hw);
        
        if(dev->dma && size > 4) {
            dev->hw->DMACR  |= HGSPI_DW_DMACR_RDMAE_EN;
            /* In SPI master mode, rx needs 2 DMA channels */
            xfer_data.dest              = (uint32)buf;
            xfer_data.src               = (uint32)&dev->hw->DATAREG;
            xfer_data.element_per_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
            xfer_data.element_num       = size;
            xfer_data.irq_hdl           = hgspi_dma_rx_irq_hdl;
            xfer_data.irq_data          = (uint32)p_spi;
            
            dma_xfer(dev->dma, &xfer_data);
            if (dev->hw->SER) { // only master need tx channel
                /* SPI tx DMA generates clock */
                xfer_data.dest              = (uint32)&dev->hw->DATAREG;
                xfer_data.src               = (uint32)buf;
                xfer_data.element_per_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
                xfer_data.element_num       = size;
                xfer_data.irq_hdl           = hgspi_dma_tx_irq_hdl;
                xfer_data.irq_data          = (uint32)p_spi;
                
                dma_xfer(dev->dma, &xfer_data);
                
                /* wait done */
                os_sema_down(&dev->tx_dma_sema, osWaitForever);
            }
            os_sema_down(&dev->rx_dma_sema, osWaitForever);
            
            dev->hw->DMACR  &= ~HGSPI_DW_DMACR_RDMAE_EN;
        } else {
            while(size--) {
                if (dev->hw->SER) { // only master need write
                    dev->hw->DATAREG = 0xFF;
                }
                *p_data++ = hgspi_dw_poll_rcv_dat(dev->hw);
            }
        }
        hgspi_dw_set_mode(dev->hw, HGSPI_DW_TMOD_TRANSMIT_ONLY);
    }
    return RET_OK;
}

static int32 hgspi_dw_write(struct spi_device *p_spi, const void *buf, uint32 size)
{
    struct hgspi_dw *dev = (struct hgspi_dw *)p_spi;
    const uint8 *p_data = buf;
    struct dma_xfer_data xfer_data;
    
    if(dev->dma && size > 4) {
        /* SPI tx only needs 1 dma channel */
        xfer_data.dest              = (uint32)&dev->hw->DATAREG;
        xfer_data.src               = (uint32)buf;
        xfer_data.element_per_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
        xfer_data.element_num       = size;
        xfer_data.irq_hdl           = hgspi_dma_tx_irq_hdl;
        xfer_data.irq_data          = (uint32)p_spi;
        
        dma_xfer(dev->dma, &xfer_data);
        /* wait done */
        os_sema_down(&dev->tx_dma_sema, osWaitForever);
    } else {
        while(size--) {
            hgspi_dw_poll_send_dat(dev->hw, *p_data++);
        }
    }
    hgspi_dw_wait_tx_done(dev->hw);
    
    return RET_OK;
}

static int32 hgspi_dw_write_read(struct spi_device *p_spi, const void *out, void *in, uint32 size)
{
    struct hgspi_dw *dev = (struct hgspi_dw *)p_spi;
    uint8 *p_out = (uint8 *)out;
    uint8 *p_in = in;
    struct dma_xfer_data xfer_data;
    
    if(size) {
        hgspi_dw_wait_tx_done(dev->hw);
        hgspi_dw_disable(dev->hw);
        dev->hw->CTRLR0 = (dev->hw->CTRLR0 & ~(HGSPI_DW_CTRLR0_TMOD_MASK)) |
                          (HGSPI_DW_TMOD_TRANSMIT_RECEIVE);
        hgspi_dw_enable(dev->hw);
        
        if(dev->dma && size > 4) {
            dev->hw->DMACR  |= HGSPI_DW_DMACR_RDMAE_EN;
            /* In SPI master mode, rx needs 2 DMA channels */
            xfer_data.dest              = (uint32)in;
            xfer_data.src               = (uint32)&dev->hw->DATAREG;
            xfer_data.element_per_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
            xfer_data.element_num       = size;
            xfer_data.irq_hdl           = hgspi_dma_rx_irq_hdl;
            xfer_data.irq_data          = (uint32)p_spi;
            
            dma_xfer(dev->dma, &xfer_data);
            if (dev->hw->SER) { // only master need tx channel
                /* SPI tx DMA generates clock */
                xfer_data.dest              = (uint32)&dev->hw->DATAREG;
                xfer_data.src               = (uint32)out;
                xfer_data.element_per_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
                xfer_data.element_num       = size;
                xfer_data.irq_hdl           = hgspi_dma_tx_irq_hdl;
                xfer_data.irq_data          = (uint32)p_spi;
                
                dma_xfer(dev->dma, &xfer_data);
                
                /* wait done */
                os_sema_down(&dev->tx_dma_sema, osWaitForever);
            }
            os_sema_down(&dev->rx_dma_sema, osWaitForever);
            
            dev->hw->DMACR  &= ~HGSPI_DW_DMACR_RDMAE_EN;
        } else {
            while(size--) {
                if (dev->hw->SER) { // only master need write
                    hgspi_dw_poll_send_dat(dev->hw, *p_out++);
                }
                *p_in++ = hgspi_dw_poll_rcv_dat(dev->hw);
            }
        }
        hgspi_dw_set_mode(dev->hw, HGSPI_DW_TMOD_TRANSMIT_ONLY);
    }
    return RET_OK;
}

static int32 hgspi_dw_set_cs(struct spi_device *p_spi, uint32 cs, uint32 value)
{
    struct hgspi_dw *dev = (struct hgspi_dw *)p_spi;
    ASSERT(cs < dev->cs_pin[0] && cs < 4);
    gpio_set_dir(dev->cs_pin[cs+1], GPIO_DIR_OUTPUT);
    return gpio_set_val(dev->cs_pin[cs+1], value);
}

static int32 hgspi_dw_request_irq(struct spi_device *p_spi, spi_irq_hdl irqhdl, uint32 irq_data)
{
    struct hgspi_dw *dev = (struct hgspi_dw *)p_spi;
    
    dev->irq_hdl = irqhdl;
    dev->irq_data = irq_data;
    
    irq_enable(dev->irq_num);
    
    return RET_OK;
}

__init int32 hgspi_dw_attach(uint32 dev_id, struct hgspi_dw *p_spi)
{
    ASSERT(p_spi->cs_pin[0] <= 4);
    hgspi_dw_disable(p_spi->hw);
    p_spi->opened           = 0;
    p_spi->dma              = NULL;
    p_spi->irq_hdl          = NULL;
    p_spi->irq_data         = 0;
    p_spi->dev.open         = hgspi_dw_open;
    p_spi->dev.close        = hgspi_dw_close;
    p_spi->dev.ioctl        = hgspi_dw_ioctl;
    p_spi->dev.read         = hgspi_dw_read;
    p_spi->dev.write        = hgspi_dw_write;
    p_spi->dev.write_read   = hgspi_dw_write_read;
    p_spi->dev.set_cs       = hgspi_dw_set_cs;
    p_spi->dev.request_irq  = hgspi_dw_request_irq;
    irq_disable(p_spi->irq_num);
    dev_register(dev_id, (struct dev_obj *)p_spi);
    return RET_OK;
}
