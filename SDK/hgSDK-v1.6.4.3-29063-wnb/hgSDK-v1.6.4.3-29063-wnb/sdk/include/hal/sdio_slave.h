#ifndef _HAL_SDIO_SLAVE_H_
#define _HAL_SDIO_SLAVE_H_
#ifdef __cplusplus
extern "C" {
#endif

enum sdio_slave_flags {
    SDIO_SLAVE_FLAG_4BIT      = BIT(0),
};

enum sdio_slave_speed {
    SDIO_SLAVE_SPEED_1M,
    SDIO_SLAVE_SPEED_2M,
    SDIO_SLAVE_SPEED_4M,
    SDIO_SLAVE_SPEED_8M,
    SDIO_SLAVE_SPEED_12M,
    SDIO_SLAVE_SPEED_24M,
    SDIO_SLAVE_SPEED_48M,

    SDIO_SLAVE_SPEED_NUM,
};

enum sdio_slave_irqs {
    SDIO_SLAVE_IRQ_RX,
    SDIO_SLAVE_IRQ_RX_OVERFLOW,
    SDIO_SLAVE_IRQ_RX_CRC_ERR,
    SDIO_SLAVE_IRQ_TX_DONE,
    SDIO_SLAVE_IRQ_TX_ERR,
    SDIO_SLAVE_IRQ_RESET,
};

enum sdio_slave_ioctl_cmd {
    SDIO_SLAVE_IO_CMD_SET_USER_REG0,
    SDIO_SLAVE_IO_CMD_SET_USER_REG1,
    SDIO_SLAVE_IO_CMD_SET_USER_REG2,
    SDIO_SLAVE_IO_CMD_RESET,
    SDIO_SLAVE_IO_CMD_SET_RST_TIMER,
};

typedef void (*sdio_slave_irq_hdl)(uint32 irq, uint32 param1, uint32 param2, uint32 param3);

struct sdio_slave {
    struct dev_obj dev;
    int32(*open)(struct sdio_slave *slave, enum sdio_slave_speed speed, uint32 flags);
    int32(*close)(struct sdio_slave *slave);
    int32(*ioctl)(struct sdio_slave *slave, int32 cmd, uint32 param);
    int32(*read)(struct sdio_slave *slave, uint8 *buff, uint32 len, int8 sync);
    int32(*write)(struct sdio_slave *slave, uint8 *buff, uint32 len, int8 sync);
    int32(*request_irq)(struct sdio_slave *slave, sdio_slave_irq_hdl irqhdl, uint32 data);
    int32(*set_id)(struct sdio_slave *slave, uint16 manufacturer_id, uint16 device_id);
};

static inline int32 sdio_slave_open(struct sdio_slave *slave, enum sdio_slave_speed speed, uint32 flags)
{
    if (slave && slave->open) {
        return slave->open(slave, speed, flags);
    }
    return RET_ERR;
}

static inline int32 sdio_slave_close(struct sdio_slave *slave)
{
    if (slave && slave->close) {
        return slave->close(slave);
    }
    return RET_ERR;
}

static inline int32 sdio_slave_write(struct sdio_slave *slave, uint8 *buff, uint32 len, int8 sync)
{
    if (slave && slave->write) {
        return slave->write(slave, buff, len, sync);
    }
    return RET_ERR;
}

static inline int32 sdio_slave_read(struct sdio_slave *slave, uint8 *buff, uint32 len, int8 sync)
{
    if (slave && slave->read) {
        return slave->read(slave, buff, len, sync);
    }
    return RET_ERR;
}

static inline int32 sdio_slave_ioctl(struct sdio_slave *slave, uint32 cmd, uint32 param)
{
    if (slave && slave->ioctl) {
        return slave->ioctl(slave, cmd, param);
    }
    return RET_ERR;
}

static inline int32 sdio_slave_set_id(struct sdio_slave *slave, uint16 manufacturer_id, uint16 device_id)
{
    if (slave && slave->set_id) {
        return slave->set_id(slave, manufacturer_id, device_id);
    }
    return RET_ERR;
}

static inline int32 sdio_slave_request_irq(struct sdio_slave *slave, sdio_slave_irq_hdl handle, uint32 data)
{
    if (slave && slave->request_irq) {
        return slave->request_irq(slave, handle, data);
    }
    return RET_ERR;
}

#define sdio_slave_reset(slave) sdio_slave_ioctl((struct sdio_slave *)slave, SDIO_SLAVE_IO_CMD_RESET, 0)

#ifdef __cplusplus
}
#endif
#endif

