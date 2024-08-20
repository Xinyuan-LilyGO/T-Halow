#ifndef _HAL_RFSPI_H_
#define _HAL_RFSPI_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
  * @breif : enum of rfspi trig mode
  */
enum rfspi_trig_mode {
    SW_TRIG_MODE     = 0,
    HW_TRIG_MODE     = 1,
};

/**
  * @breif : enum of rfspi timing mode
  */
enum rfspi_tim_mode {
    AD936X_MODE      = 0,
    HUGEIC_MODE      = 1,
};

/**
  * @breif : enum of rfspi Clock
  */
enum rfspi_clk { //in fpga only 16M is valid
    CLK_8M           = 8, //35,
    CLK_16M          = 16,//17,
    CLK_24M          = 24,//11,
    CLK_32M          = 32,//8,
    CLK_36M          = 36,//7,
    CLK_48M          = 48,//5,
};


struct rfspi_device {
    struct dev_obj dev;
    int32(*set_trig_mode)(struct rfspi_device *rfspi, enum rfspi_trig_mode trig_mode);
    int32(*open)(struct rfspi_device *rfspi, enum rfspi_tim_mode tim_mode, enum rfspi_clk clk, int32 pin_mode);
    int32(*close)(struct rfspi_device *rfspi);
    int32(*rst_spi_slave)(struct rfspi_device *rfspi);
    int32(*write)(struct rfspi_device *rfspi, uint16 addr, uint16 data);
    uint16(*read)(struct rfspi_device *rfspi, uint16 addr);
    uint16(*write_and_read)(struct rfspi_device *rfspi, uint16 addr, uint16 data);
};

static inline int32 rfspi_set_trig_mode(struct rfspi_device *rfspi, enum rfspi_trig_mode trig_mode)
{
    if (rfspi && rfspi->set_trig_mode) {
        return rfspi->set_trig_mode(rfspi, trig_mode);
    }
    return RET_ERR;
}

static inline int32 rfspi_open(struct rfspi_device *rfspi, enum rfspi_tim_mode tim_mode, enum rfspi_clk clk, int32 pin_mode)
{
    if (rfspi && rfspi->open) {
        return rfspi->open(rfspi, tim_mode, clk, pin_mode);
    }
    return RET_ERR;
}

static inline int32 rfspi_close(struct rfspi_device *rfspi)
{
    if (rfspi && rfspi->close) {
        return rfspi->close(rfspi);
    }
    return RET_ERR;
}

static inline int32 rfspi_rst_spi_slave(struct rfspi_device *rfspi)
{
    if (rfspi && rfspi->rst_spi_slave) {
        return rfspi->rst_spi_slave(rfspi);
    }
    return RET_ERR;
}

static inline int32 rfspi_write(struct rfspi_device *rfspi, uint16 addr, uint16 data)
{
    if (rfspi && rfspi->write) {
        return rfspi->write(rfspi, addr, data);
    }
    return RET_ERR;
}

static inline uint16 rfspi_read(struct rfspi_device *rfspi, uint16 addr)
{
    if (rfspi && rfspi->read) {
        return rfspi->read(rfspi, addr);
    }
    return 0xffff;
}

static inline uint16 rfspi_write_and_read(struct rfspi_device *rfspi, uint16 addr, uint16 data)
{
    rfspi->write(rfspi, addr, data);
    return rfspi->read(rfspi, addr);
}

#ifdef __cplusplus
}
#endif
#endif

