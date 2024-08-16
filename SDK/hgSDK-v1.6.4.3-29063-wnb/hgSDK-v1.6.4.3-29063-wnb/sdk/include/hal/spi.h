#ifndef _HAL_SPI_H_
#define _HAL_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief spi working mode type
  */
enum spi_work_mode {
    SPI_MASTER_MODE,
    SPI_SLAVE_MODE,
};

/**
  * @brief spi wire mode
  */
enum spi_wire_mode {
    SPI_WIRE_SINGLE_MODE,
    SPI_WIRE_NORMAL_MODE,
    SPI_WIRE_DUAL_MODE,
    SPI_WIRE_QUAD_MODE,
};

/**
  * @brief spi clock mode
  */
enum spi_clk_mode {
    SPI_CPOL_0_CPHA_0 = 0,  /*!< Inactive state of serial clock is low, serial clock toggles in middle of first data bit */
    SPI_CPOL_0_CPHA_1 = 1,  /*!< Inactive state of serial clock is low, serial clock toggles at start of first data bit  */
    SPI_CPOL_1_CPHA_0 = 2,  /*!< Inactive state of serial clock is high, serial clock toggles in middle of first data bit */
    SPI_CPOL_1_CPHA_1 = 3,  /*!< Inactive state of serial clock is high, serial clock toggles at start of first data bit */

    SPI_CLK_MODE_0    = SPI_CPOL_0_CPHA_0,  /*!< Equal to \ref SPI_CPOL_0_CPHA_0 */
    SPI_CLK_MODE_1    = SPI_CPOL_0_CPHA_1,  /*!< Equal to \ref SPI_CPOL_0_CPHA_1 */
    SPI_CLK_MODE_2    = SPI_CPOL_1_CPHA_0,  /*!< Equal to \ref SPI_CPOL_1_CPHA_0 */
    SPI_CLK_MODE_3    = SPI_CPOL_1_CPHA_1   /*!< Equal to \ref SPI_CPOL_1_CPHA_1 */
};

/**
  * @brief spi ioctl cmd
  *        The user-defined command should be greater than 0x100.
  */
enum spi_ioctl_cmd {
    SPI_WIRE_MODE_SET       = 0,
    SPI_WIRE_MODE_GET       = 1,
    SPI_DW_INTR_SET         = 2,
    SPI_DMAC_USE            = 3,
};

typedef void (*spi_irq_hdl)(uint32 irq, uint32 irq_data);

struct spi_device {
    struct dev_obj dev;
    int32(*open)(struct spi_device *p_spi, uint32 clk_freq, uint32 work_mode,
                 uint32 wire_mode, uint32 clk_mode);
    int32(*close)(struct spi_device *p_spi);
    int32(*ioctl)(struct spi_device *p_spi, uint32 cmd, uint32 param);
    int32(*read)(struct spi_device *p_spi, void *buf, uint32 size);
    int32(*write)(struct spi_device *p_spi, const void *buf, uint32 size);
    int32(*write_read)(struct spi_device *p_spi, const void *out, void *in, uint32 size);
    int32(*set_cs)(struct spi_device *p_spi, uint32 cs, uint32 value);
    int32(*request_irq)(struct spi_device *p_spi, spi_irq_hdl irqhdl, uint32 irq_data);
};

static inline int32 spi_open(struct spi_device *spi, uint32 clk_freq, uint32 work_mode,
                             uint32 wire_mode, uint32 clk_mode)
{
    if(spi && spi->open) {
        return spi->open(spi, clk_freq, work_mode, wire_mode, clk_mode);
    }
    return RET_ERR;
}

static inline int32 spi_close(struct spi_device *spi)
{
    if(spi && spi->close) {
        return spi->close(spi);
    }
    return RET_ERR;
}

static inline int32 spi_ioctl(struct spi_device *spi, uint32 cmd, uint32 param)
{
    if(spi && spi->ioctl) {
        return spi->ioctl(spi, cmd, param);
    }
    return RET_ERR;
}

static inline int32 spi_read(struct spi_device *spi, void *buf, uint32 size)
{
    if(spi && spi->read) {
        return spi->read(spi, buf, size);
    }
    return RET_ERR;
}

static inline int32 spi_write(struct spi_device *spi, const void *buf, uint32 size)
{
    if(spi && spi->write) {
        return spi->write(spi, buf, size);
    }
    return RET_ERR;
}

static inline int32 spi_write_read(struct spi_device *spi, const void *out, void *in, uint32 size)
{
    if(spi && spi->write_read) {
        return spi->write_read(spi, out, in, size);
    }
    return RET_ERR;
}

static inline int32 spi_set_cs(struct spi_device *spi, uint32 cs, uint32 value)
{
    if(spi && spi->set_cs) {
        return spi->set_cs(spi, cs, value);
    }
    return RET_ERR;
}

static inline int32 spi_request_irq(struct spi_device *spi, spi_irq_hdl irqhdl, uint32 irq_data)
{
    if(spi && spi->request_irq) {
        return spi->request_irq(spi, irqhdl, irq_data);
    }
    return RET_ERR;
}

#ifdef __cplusplus
}
#endif
#endif

