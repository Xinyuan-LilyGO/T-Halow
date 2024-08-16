#ifndef _HAL_I2C_H_
#define _HAL_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

enum i2c_mode {
    IIC_MODE_MASTER = 0,
    IIC_MODE_SLAVE,
};

enum i2c_addr_mode {
    IIC_ADDR_7BIT = 0,
    IIC_ADDR_10BIT,
};

enum i2c_irq_type {
    I2C_IRQ_SCL_STUCK_AT_LOW = 0,
    I2C_IRQ_MST_ON_HOLD,
    I2C_IRQ_RESTART_DET,
    I2C_IRQ_GEN_CALL,
    I2C_IRQ_START_DET,
    I2C_IRQ_STOP_DET,
    I2C_IRQ_ACTIVITY,
    I2C_IRQ_RX_DONE,
    I2C_IRQ_TX_ABRT,
    I2C_IRQ_RD_REQ,
    I2C_IRQ_TX_EMPTY,
    I2C_IRQ_TX_OVER,
    I2C_IRQ_RX_FULL,
    I2C_IRQ_RX_OVER,
    I2C_IRQ_RX_UNDER,
};

typedef void (*i2c_irq_hdl)(uint32 irq, uint32 irq_data, uint32 param);

struct i2c_device {
    struct dev_obj dev;
    int32(*open)(struct i2c_device *i2c, enum i2c_mode mode, enum i2c_addr_mode addr_mode, uint32 addr);
    int32(*close)(struct i2c_device *i2c);
    int32(*ioctl)(struct i2c_device *i2c, int32 cmd, uint32 param);
    int32(*baudrate)(struct i2c_device *i2c, uint32 baudrate);
    int32(*read)(struct i2c_device *i2c, int8 *addr, uint32 addr_len, int8 *buf, uint32 len);
    int32(*write)(struct i2c_device *i2c, int8 *addr, uint32 addr_len, int8 *buf, uint32 len);
    int32(*request_irq)(struct i2c_device *i2c, i2c_irq_hdl irqhdl, uint32 irq_data);
};

static inline int32 i2c_open(struct i2c_device *i2c, enum i2c_mode mode, enum i2c_addr_mode addr_mode, uint32 addr)
{
    if (i2c && i2c->open) {
        return i2c->open(i2c, mode, addr_mode, addr);
    }
    return RET_ERR;
}

static inline int32 i2c_close(struct i2c_device *i2c)
{
    if (i2c && i2c->close) {
        return i2c->close(i2c);
    }
    return RET_ERR;
}

static inline int32 i2c_set_baudrate(struct i2c_device *i2c, uint32 baudrate)
{
    if(i2c && i2c->baudrate) {
        return i2c->baudrate(i2c, baudrate);
    }
    
    return RET_ERR;
}

static inline int32 i2c_ioctl(struct i2c_device *i2c, uint32 cmd, uint32 param)
{
    if (i2c && i2c->ioctl) {
        return i2c->ioctl(i2c, cmd, param);
    }
    return RET_ERR;
}

static inline int32 i2c_read(struct i2c_device *i2c, int8 *addr, uint32 addr_len, int8 *buf, uint32 buf_len)
{
    if (i2c && i2c->read) {
        return i2c->read(i2c, addr, addr_len, buf, buf_len);
    }
    return RET_ERR;
}

static inline int32 i2c_write(struct i2c_device *i2c, int8 *addr, uint32 addr_len, int8 *buf, uint32 buf_len)
{
    if (i2c && i2c->write) {
        return i2c->write(i2c, addr, addr_len, buf, buf_len);
    }
    return RET_ERR;
}

static inline int32 i2c_request_irq(struct i2c_device *i2c, i2c_irq_hdl handle, uint32 irq_data)
{
    if (i2c && i2c->request_irq) {
        return i2c->request_irq(i2c, handle, irq_data);
    }
    return RET_ERR;
}

#ifdef __cplusplus
}
#endif
#endif

