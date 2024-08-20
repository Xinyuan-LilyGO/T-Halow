#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "dev.h"
#include "osal/irq.h"
#include "osal/string.h"
#include "hal/i2c.h"
#include "dev/i2c/hgi2c_dw.h"

static int32 hgi2c_dw_set_baudrate(struct i2c_device *i2c, uint32 baudrate)
{
    struct hgi2c_dw *dev = (struct hgi2c_dw *)i2c;
    uint32 baudrate_cnt =  sys_get_apbclk()/baudrate/2;
    
//    if(baudrate <= 100000UL) {
//        iic_con |= DW_IIC_CON_SPEED(IIC_SPEED_STANDARD_MODE);
//    } else if((baudrate > 100000UL) && (baudrate <= 400000UL)) {
//        iic_con |= DW_IIC_CON_SPEED(IIC_SPEED_MODE);
//    } else if((baudrate > 400000UL) && (baudrate <= 3400000UL)) {
//        iic_con |= DW_IIC_CON_SPEED(IIC_SPEED_HIGH_MODE);
//    }
    
    dev->hw->SS_SCL_HCNT = DW_IIC_IC_SS_SCL_HCNT(baudrate_cnt);
    dev->hw->SS_SCL_LCNT = DW_IIC_IC_SS_SCL_LCNT(baudrate_cnt);
    
    return RET_OK;
}

static void hgi2c_dw_hw_init(struct i2c_device       *i2c, 
                             enum i2c_mode mode_sel, 
                             enum i2c_addr_mode addr_bit_sel,
                             uint32              addr)
{
    uint32 con_val = 0;
    struct hgi2c_dw *dev = (struct hgi2c_dw *)i2c;
    
    if(mode_sel == IIC_MODE_MASTER) {
        con_val            |= DW_IIC_CON_MASTER_MODE;
        con_val            |= DW_IIC_CON_IC_SLAVE_DISABLE;
        //The IIC uses a 7-bit address by default.
        con_val            &= ~DW_IIC_CON_IC10BITADDR_MASTER;
        dev->hw->TAR = DW_IIC_TAR_IC_TAR(addr);
        dev->hw->SAR = DW_IIC_SAR_IC_SAR(0);
    } else if(mode_sel == IIC_MODE_SLAVE) {
        con_val            &= ~DW_IIC_CON_MASTER_MODE;
        con_val            &= ~DW_IIC_CON_IC_SLAVE_DISABLE;
        //The IIC uses a 7-bit address by default.
        con_val            &= ~DW_IIC_CON_IC10BITADDR_SLAVE;
        dev->hw->TAR = DW_IIC_TAR_IC_TAR(0);
        dev->hw->SAR = DW_IIC_SAR_IC_SAR(addr);
    }
    
    if(addr_bit_sel == IIC_ADDR_10BIT) {
        con_val            |= DW_IIC_CON_IC10BITADDR_MASTER;
    }
    
    con_val |= DW_IIC_CON_SPEED(IIC_SPEED_STANDARD_MODE);
    con_val |= DW_IIC_CON_IC_RESTART_EN;
    
    dev->hw->CON      = con_val;
    dev->hw->RX_TL    = DW_IIC_RX_TL(6);
    dev->hw->TX_TL    = DW_IIC_TX_TL(6);
    dev->hw->DMA_TDLR = DW_IIC_DMA_TDLR(6);
    dev->hw->DMA_RDLR = DW_IIC_DMA_RDLR(6);
    dev->hw->ENABLE   = DW_IIC_ENABLE;
}

static int32 hgi2c_dw_open(struct i2c_device       *i2c, 
                           enum i2c_mode mode_sel, 
                           enum i2c_addr_mode addr_bit_sel,
                           uint32              addr)
{
    int32 ret = 0;
    struct hgi2c_dw *dev = (struct hgi2c_dw *)i2c;

    if (dev->opened) {
        return RET_OK;
    }

    ret = pin_func(i2c->dev.dev_id, 1);
    if (ret) {
        ASSERT(ret == RET_OK);
//        os_printf("hgi2c_dw request io failed!\r\n");
        return ret;
    }
//    ret = os_mutex_init(&dev->tx_lock);
//    if (ret) {
//        pin_func(i2c->dev.dev_id, 0);
//        os_printf("hgi2c_dw mutex init failed!\r\n");
//        return ret;
//    }
//    ret = os_sema_init(&dev->tx_done, 0);
//    if (ret) {
//        pin_func(i2c->dev.dev_id, 0);
//        os_mutex_del(&dev->tx_lock);
//        os_printf("hgi2c_dw semaphore init failed!\r\n");
//        return ret;
//    }
    
    dev->hw->INTR_MASK &= ~(DW_IIC_INTR_MASK(0x7FFF));
    hgi2c_dw_hw_init(i2c, mode_sel, addr_bit_sel, addr);

    dev->opened = 1;
    return RET_OK;
}

static int32 hgi2c_dw_close(struct i2c_device *i2c)
{
    struct hgi2c_dw *dev = (struct hgi2c_dw *)i2c;
    
    if (!dev->opened) {
        return RET_OK;
    }
    irq_disable(dev->irq_num);

    dev->hw->ENABLE &= ~(DW_IIC_ENABLE);
    dev->hw->INTR_MASK &= ~(DW_IIC_INTR_MASK(0x7FFF));
    
    pin_func(i2c->dev.dev_id, 0);
//    os_mutex_del(&dev->tx_lock);
//    os_sema_del(&dev->tx_done);
    dev->irq_hdl = NULL;
    dev->irq_data = 0;
    dev->opened = 0;
    
    return RET_OK;
}

static int32 hgi2c_dw_read(struct i2c_device *i2c, 
                           int8         *addr_buf, 
                           uint32        addr_len, 
                           int8         *buf, 
                           uint32        len)
{
    struct hgi2c_dw *dev = (struct hgi2c_dw *)i2c;
    uint32 write_cnt = 0;
    uint32 read_cnt  = 0;
    int8  *p_buf = addr_buf;
    
    if(!dev->opened) {
        return RET_ERR;
    }
    
    if((len == 0) || (addr_len == 0)) {
        return RET_OK;
    }
    
    dev->hw->DATA_CMD = DW_IIC_DATA_CMD_RESTART | DW_IIC_DATA_CMD_DAT(*p_buf);
    p_buf++;
    addr_len--;
    
    while(addr_len > 0) {
        dev->hw->DATA_CMD = DW_IIC_DATA_CMD_DAT(*p_buf);
        p_buf++;
        addr_len--;
    }
    
    if(len == 1) {
        while(DW_IIC_GET_STATUS_TX_FIFO_NO_FULL(dev->hw) == 0);
        /* start+TAR, read, stop */
        DW_IIC_TIMING_RESTART_READ_STOP(dev->hw);
    } else {
        while(DW_IIC_GET_STATUS_TX_FIFO_NO_FULL(dev->hw) == 0);
        /* start+TAR, read */
        DW_IIC_TIMING_RESTART_READ(dev->hw); 
        
        for(write_cnt=1; write_cnt<(len - 1); write_cnt++) {
            while(DW_IIC_GET_STATUS_TX_FIFO_NO_FULL(dev->hw) == 0);
            /* Sending the read signal actually acts as ii_clk. */
            DW_IIC_TIMING_READ(dev->hw);
            
            /* The data is taken out of the RX FIFO to prevent 
             * the RX FIFO data from being overwritten. 
             */
            if(DW_IIC_GET_STATUS_RX_FIFO_NO_EMPTY(dev->hw)) {
                DW_IIC_TIMING_GET_READ_DATA(dev->hw, *buf);
                buf++;
                read_cnt++;
            }
        }
        
        while(DW_IIC_GET_STATUS_TX_FIFO_NO_FULL(dev->hw) == 0);
        /* read last byte, stop */
        DW_IIC_TIMING_READ_STOP(dev->hw);
    }
    
    /* Take the data out of the RX FIFO. */
    for(; read_cnt<len; read_cnt++) {
        while(!DW_IIC_GET_STATUS_RX_FIFO_NO_EMPTY(dev->hw));
        DW_IIC_TIMING_GET_READ_DATA(dev->hw, *buf);
        buf++;
    }
    
    /* Check if the STOP signal of the module is completed. 
     * Or whether the communication is terminated. 
     */
    while(1) {
        if(DW_IIC_GET_RAW_TX_ABRT_PENDING(dev->hw)) {
            return RET_ERR;
        }
        if(DW_IIC_GET_RAW_STOP_DET_PENDING(dev->hw)) {
            return RET_OK;
        }
    }
}

static int32 hgi2c_dw_write(struct i2c_device *i2c, 
                            int8         *addr_buf, 
                            uint32        addr_len, 
                            int8         *buf, 
                            uint32        len)
{
    struct hgi2c_dw *dev = (struct hgi2c_dw *)i2c;
    uint32 write_cnt = 0;
    int8  *p_buf = addr_buf;
    
    if(!dev->opened) {
        return RET_ERR;
    }
    
    if((len == 0) || (addr_len == 0)) {
        return RET_OK;
    }
    
    dev->hw->DATA_CMD = DW_IIC_DATA_CMD_RESTART | DW_IIC_DATA_CMD_DAT(*p_buf);
    p_buf++;
    addr_len--;
    
    while(addr_len > 0) {
        dev->hw->DATA_CMD = DW_IIC_DATA_CMD_DAT(*p_buf);
        p_buf++;
        addr_len--;
    }
    
    for(write_cnt=0; write_cnt<(len - 1); write_cnt++) {
        while(DW_IIC_GET_STATUS_TX_FIFO_NO_FULL(dev->hw) == 0);
        /* write */
        DW_IIC_TIMING_WRITE(dev->hw, *buf++);
    }
        
    while(DW_IIC_GET_STATUS_TX_FIFO_NO_FULL(dev->hw) == 0);
    /* write last byte, +stop. */
    DW_IIC_TIMING_WRITE_STOP(dev->hw, *buf);

    /* Check if the TX FIFO has been sent to the empty state. */
    while(!DW_IIC_GET_STATUS_TX_FIFO_EMPTY(dev->hw));

    /* Check if the STOP signal of the module is completed. 
     * Or whether the communication is terminated. 
     */
    while(1) {
        if(DW_IIC_GET_RAW_TX_ABRT_PENDING(dev->hw)) {
            return RET_ERR;
        }
        if(DW_IIC_GET_RAW_STOP_DET_PENDING(dev->hw)) {
            return RET_OK;
        }
    }
}

static int32 hgi2c_dw_ioctl(struct i2c_device *i2c, int32 cmd, uint32 param)
{

    return RET_OK;
}

/** 
  * @brief  IIC0 Interrupt handler
  * @param  None.
  * @retval None.
  */
static void hgi2c_dw_irq_handler(void *data)
{
    struct hgi2c_dw *dev = (struct hgi2c_dw *)data;
    uint16 intr = DW_IIC_GET_INTERRPT_PENDING(dev->hw);
    
    if(DW_IIC_CHECK_RX_UNDER_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_RX_UNDER)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_RX_UNDER_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_RX_UNDER, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_RX_OVER_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_RX_OVER)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_RX_OVER_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_RX_OVER, dev->irq_data, 0);
        }
    }   
    if(DW_IIC_CHECK_RX_FULL_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_RX_FULL)) {
        /* Note: RX_FULL does not have a separate CLR register. It can only be 
         * masked or read from the data in the RX buffer. Only the RX FIFO buffer  
         * does not reach full, and the pending will not rise again.
         */
        /* Mask interrupts. */
        //dev->hw->DW_IIC_INTR_MASK &= ~DW_IIC_INTR_MASK_M_RX_FULL;
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_RX_FULL, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_TX_OVER_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_TX_OVER)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_TX_OVER_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_TX_OVER, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_TX_EMPTY_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_TX_EMPTY)) {
        /* Note: TX empty does not have a separate CLR register. It can only be 
         * masked or read from the TX buffer. Only the TX FIFO Buffer is not empty. 
         * This pending will not be up again.
         */
        /* Mask interrupts. */
        //dev->hw->DW_IIC_INTR_MASK &= ~DW_IIC_INTR_MASK_M_TX_EMPTY;
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_TX_EMPTY, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_READ_REQ_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_RD_REQ)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_READ_REQ_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_RD_REQ, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_TX_ABRT_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_TX_ABRT)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_TX_ABRT_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_TX_ABRT, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_RX_DONE_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_RX_DONE)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_RX_DONE_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_RX_DONE, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_ACTIVITY_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_ACTIVITY)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_ACTIVITY_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_ACTIVITY, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_STOP_DET_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_STOP_DET)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_STOP_DET_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_STOP_DET, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_START_DET_INTERRUPT_ENABLE(dev->hw) && 
       (intr & DW_IIC_INTR_STAT_R_START_DET)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_START_DET_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_START_DET, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_GEN_CALL_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_GEN_CALL)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_GEN_CALL_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_GEN_CALL, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_RESTART_DET_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_RESTART_DET)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_RESTART_DET_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_RESTART_DET, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_MST_ON_HOLD_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_MST_ON_HOLD)) {
        /* Note: MASTER_ON_HOLD does not have a separate CLR register. It can 
         * only be masked or read from the TX buffer. Only the TX FIFO Buffer 
         * is not empty. This pending will not be up again. 
         */
        /* Mask interrupts. */
        //dev->hw->DW_IIC_INTR_MASK &= ~DW_IIC_INTR_MASK_M_MST_ON_HOLD;
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_MST_ON_HOLD, dev->irq_data, 0);
        }
    }
    if(DW_IIC_CHECK_SCL_STUCK_AT_LOW_INTERRUPT_ENABLE(dev->hw) &&
       (intr & DW_IIC_INTR_STAT_R_SCL_STUCK_AT_LOW)) {
        /* Clear interrupt pending */
        DW_IIC_CLEAR_STUCK_AT_LOW_PENDING(dev->hw);
        
        /* Handling something */
        if(dev->irq_hdl) {
            dev->irq_hdl(I2C_IRQ_SCL_STUCK_AT_LOW, dev->irq_data, 0);
        }
    }
}

static int32 hgi2c_dw_request_irq(struct i2c_device *i2c, i2c_irq_hdl irqhdl, uint32 irq_data)
{
    int ret;
    struct hgi2c_dw *dev = (struct hgi2c_dw *)i2c;
    
    if(!dev->opened) {
        return RET_ERR;
    }
    
    dev->irq_hdl = irqhdl;
    dev->irq_data = irq_data;
    ret = request_irq(dev->irq_num, hgi2c_dw_irq_handler, dev);
    ASSERT(ret == RET_OK);
    
    irq_enable(dev->irq_num);
    
    dev->hw->INTR_MASK = DW_IIC_INTR_MASK(0);
    
    return RET_OK;
}

int32 hgi2c_dw_attach(uint32 dev_id, struct hgi2c_dw *i2c)
{
    i2c->dev.open  = hgi2c_dw_open;
    i2c->dev.close = hgi2c_dw_close;
    i2c->dev.ioctl = hgi2c_dw_ioctl;
    i2c->dev.baudrate = hgi2c_dw_set_baudrate;
    i2c->dev.request_irq = hgi2c_dw_request_irq;
    i2c->dev.read = hgi2c_dw_read;
    i2c->dev.write = hgi2c_dw_write;
    
    i2c->irq_hdl = NULL;
    i2c->irq_data = 0;
    i2c->opened = 0;
    
    dev_register(dev_id, (struct dev_obj *)i2c);
    return RET_OK;
}


