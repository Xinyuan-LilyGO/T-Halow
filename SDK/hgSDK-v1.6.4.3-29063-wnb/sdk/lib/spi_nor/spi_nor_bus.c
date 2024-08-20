#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "dev.h"
#include "hal/spi.h"
#include "hal/spi_nor.h"
#include "osal/sleep.h"

/**
  * @brief Standard SPI instructions
  */
#define SPI_NOR_STANDARD_WRITE_ENABLE                           0x06
#define SPI_NOR_STANDARD_WRITE_DISABLE                          0x04
#define SPI_NOR_STANDARD_READ_STATUS_REG                        0x05
#define SPI_NOR_STANDARD_WRITE_STATUS_REG                       0x01
#define SPI_NOR_STANDARD_PAGE_PROGRAM                           0x02
#define SPI_NOR_STANDARD_SECTOR_ERASE                           0x20
#define SPI_NOR_STANDARD_BLOCK_ERASE                            0xD8
#define SPI_NOR_STANDARD_CHIP_ERASE                             0xC7//0x60
#define SPI_NOR_STANDARD_ERASE_SUSPEND                          0x75
#define SPI_NOR_STANDARD_ERASE_RESUME                           0x7A
#define SPI_NOR_STANDARD_READ_DATA                              0x03
#define SPI_NOR_STANDARD_FAST_READ                              0x0B
#define SPI_NOR_STANDARD_RELEASE_POWERDOWN_ID                   0xAB
#define SPI_NOR_STANDARD_DEVICE_ID                              0x90
#define SPI_NOR_STANDARD_JEDEC_ID                               0x9F
#define SPI_NOR_STANDARD_ENABLE_QPI                             0x38
#define SPI_NOR_STANDARD_POWER_DOWN                             0xB9
#define SPI_NOR_STANDARD_RELEASE_POWER_DOWN                     0xAB
/**
  * @}
  */

/**
  * @brief Dual SPI instructions
  */
#define SPI_NOR_DUAL_FAST_READ_DUAL_OUTPUT                      0x3B
#define SPI_NOR_DUAL_FAST_READ_DUAL_IO                          0xBB
/**
  * @}
  */

/**
  * @brief Quad SPI instructions
  */
#define SPI_NOR_QUAD_PAGE_PROGRAM                               0x32
#define SPI_NOR_QUAD_FAST_READ_QUAD_OUTPUT                      0x6B
#define SPI_NOR_QUAD_FAST_READ_QUAD_IO                          0xEB
/**
  * @}
  */

/**
  * @brief QPI instructions
  */
#define SPI_NOR_QPI_WRITE_ENABLE                                0x06
#define SPI_NOR_QPI_WRITE_DISABLE                               0x04
#define SPI_NOR_QPI_READ_STATUS_REG                             0x05
#define SPI_NOR_QPI_WRITE_STATUS_REG                            0x01
#define SPI_NOR_QPI_PAGE_PROGRAM                                0x02
#define SPI_NOR_QPI_SECTOR_ERASE                                0x20
#define SPI_NOR_QPI_BLOCK_ERASE                                 0xD8
#define SPI_NOR_QPI_CHIP_ERASE                                  0xC7
#define SPI_NOR_QPI_ERASE_SUSPEND                               0x75
#define SPI_NOR_QPI_ERASE_RESUME                                0x7A
#define SPI_NOR_QPI_FAST_READ                                   0x0B
#define SPI_NOR_QPI_FAST_READ_QUAD_IO                           0xEB
#define SPI_NOR_QPI_JEDEC_ID                                    0x9F
#define SPI_NOR_QPI_DISABLE_QPI                                 0xFF
/**
  * @}
  */

/**
  * @brief SPI NOR STATUS register
  */
#define SPI_NOR_STATUS_BUSY                                     0x01
#define SPI_NOR_STATUS_WEL                                      0x02
#define SPI_NOR_STATUS2_QUAD_ENABLE                             0x200
/**
  * @}
  */

/**
  * @brief Standard SPI instructions
  */
//JECEC ID
void spi_nor_standard_read_jedec_id(struct spi_nor_flash *flash, uint8 *buf)
{
    uint8 instruction = SPI_NOR_STANDARD_JEDEC_ID;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_read(flash->spidev, buf, 3);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

//write disable
static void spi_nor_standard_write_disable(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_STANDARD_WRITE_DISABLE;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

//write enable
static void spi_nor_standard_write_enable(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_STANDARD_WRITE_ENABLE;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

//read status register
static uint8 spi_nor_standard_read_status_register(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_STANDARD_READ_STATUS_REG;
    uint8 result;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_read(flash->spidev, &result, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    return result;
}

//write status register
static void spi_nor_standard_write_status_register(struct spi_nor_flash *flash, uint16 data)
{
    uint8 write_buf[3];

    spi_nor_standard_write_enable(flash);

    write_buf[0] = SPI_NOR_STANDARD_WRITE_STATUS_REG;
    write_buf[1] = data;
    write_buf[2] = data >> 8;
    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 3);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_nor_standard_write_disable(flash);
}

//read data
static void spi_nor_standard_read_data(struct spi_nor_flash *flash, uint32 addr, uint8 *buf, uint32 buf_size)
{
    uint8 write_buf[4];

    write_buf[0] = SPI_NOR_STANDARD_READ_DATA;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 4);
    spi_read(flash->spidev, buf, buf_size);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

//fast read
static void spi_nor_standard_fast_read(struct spi_nor_flash *flash, uint32 addr, uint8 *buf, uint32 buf_size)
{
    uint8 write_buf[5];

    write_buf[0] = SPI_NOR_STANDARD_FAST_READ;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;
    write_buf[4] = 0x00;    //dummy clock

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 5);
    spi_read(flash->spidev, buf, buf_size);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

//page program
static void spi_nor_standard_page_program(struct spi_nor_flash *flash, uint32 addr, uint8 *buf, uint32 buf_size)
{
    uint8 write_buf[4];

    spi_nor_standard_write_enable(flash);

    write_buf[0] = SPI_NOR_STANDARD_PAGE_PROGRAM;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 4);
    spi_write(flash->spidev, buf, buf_size);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    //wait page program done
    while (spi_nor_standard_read_status_register(flash) & SPI_NOR_STATUS_BUSY);

    spi_nor_standard_write_disable(flash);
}

//sector erase
static void spi_nor_standard_sector_erase(struct spi_nor_flash *flash, uint32 addr)
{
    uint8 write_buf[4];

    spi_nor_standard_write_enable(flash);

    write_buf[0] = SPI_NOR_STANDARD_SECTOR_ERASE;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 4);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    //wait sector erase done
    while (spi_nor_standard_read_status_register(flash) & SPI_NOR_STATUS_BUSY);

    spi_nor_standard_write_disable(flash);
}

//block erase
static void spi_nor_standard_block_erase(struct spi_nor_flash *flash, uint32 addr)
{
    uint8 write_buf[4];

    spi_nor_standard_write_enable(flash);

    write_buf[0] = SPI_NOR_STANDARD_BLOCK_ERASE;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 4);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    //wait block erase done
    while (spi_nor_standard_read_status_register(flash) & SPI_NOR_STATUS_BUSY);

    spi_nor_standard_write_disable(flash);
}

//chip erase
static void spi_nor_standard_chip_erase(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_STANDARD_CHIP_ERASE;

    spi_nor_standard_write_enable(flash);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    //wait block erase done
    while (spi_nor_standard_read_status_register(flash) & SPI_NOR_STATUS_BUSY);

    spi_nor_standard_write_disable(flash);
}

//enter QPI
static void spi_nor_standard_enter_qpi(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_STANDARD_ENABLE_QPI;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

//enter power down
static void spi_nor_standard_power_down(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_STANDARD_POWER_DOWN;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

//release power down
static void spi_nor_standard_release_power_down(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_STANDARD_RELEASE_POWER_DOWN;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

static void spi_nor_standard_open(struct spi_nor_flash *flash)
{
    //release power down
    //spi_nor_standard_release_power_down(flash);
    //wait done
    //os_sleep_us(100);
}

/**
  * @}
  */

/**
  * @brief Dual SPI instructions
  */
//fast read dual output
//If flash supports DUAL, this function is also generally supported
static void spi_nor_dual_fast_read_dual_output(struct spi_nor_flash *flash, uint32 addr, uint8 *buf, uint32 buf_size)
{
    uint8 write_buf[5];

    write_buf[0] = SPI_NOR_DUAL_FAST_READ_DUAL_OUTPUT;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;
    write_buf[4] = 0x00;    //dummy clock

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);

    //instruction & address & dummy clock should tx in Standard SPI mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);
    spi_write(flash->spidev, write_buf, 5);

    //data rx in DUAL SPI mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_DUAL_MODE);
    spi_read(flash->spidev, buf, buf_size);

    //Return to normal mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

//fast read dual IO
//warning! You need to confirm that nor flash supports this function.
static void spi_nor_dual_fast_read_dual_io(struct spi_nor_flash *flash, uint32 addr, uint8 *buf, uint32 buf_size)
{
    uint8 write_buf[5];

    write_buf[0] = SPI_NOR_DUAL_FAST_READ_DUAL_IO;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;
    write_buf[4] = 0x00;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);

    //instruction should tx in Standard SPI mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);
    spi_write(flash->spidev, write_buf, 1);

    //address & dummy clock should tx in DUAL SPI mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_DUAL_MODE);
    spi_write(flash->spidev, &write_buf[1], 4);

    //data rx in DUAL SPI mode
    spi_read(flash->spidev, buf, buf_size);

    //Return to normal mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

static void spi_nor_quad_open(struct spi_nor_flash *flash)
{
    uint16 status;
    
    //release power down
    spi_nor_standard_release_power_down(flash);
    //wait done
    os_sleep_us(50);
    
    status = spi_nor_standard_read_status_register(flash);
    status |= SPI_NOR_STATUS2_QUAD_ENABLE;
    spi_nor_standard_write_status_register(flash, status);
}

/**
  * @}
  */

/**
  * @brief Quad SPI instructions
  * @note  warning! You need to confirm that nor flash supports this function.
  */
//fast read quad output
static void spi_nor_quad_fast_read_quad_output(struct spi_nor_flash *flash, uint32 addr, uint8 *buf, uint32 buf_size)
{
    uint8 write_buf[5];

    write_buf[0] = SPI_NOR_QUAD_FAST_READ_QUAD_OUTPUT;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;
    write_buf[4] = 0x00;    //dummy clock

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);

    //instruction & address & dummy clock should tx in Standard SPI mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);
    spi_write(flash->spidev, write_buf, 5);

    //data rx in QUAD SPI mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);
    spi_read(flash->spidev, buf, buf_size);

    //Return to normal mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

//fast read quad IO
static void spi_nor_quad_fast_read_quad_io(struct spi_nor_flash *flash, uint32 addr, uint8 *buf, uint32 buf_size)
{
    uint8 write_buf[7];

    write_buf[0] = SPI_NOR_QUAD_FAST_READ_QUAD_IO;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;
    write_buf[4] = 0x00;
    write_buf[5] = 0x00;    //dummy clock
    write_buf[6] = 0x00;    //dummy clock

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);

    //instruction should tx in Standard SPI mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);
    spi_write(flash->spidev, write_buf, 1);

    //address & dummy clock should tx in QUAD SPI mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);
    spi_write(flash->spidev, &write_buf[1], 6);

    //data rx in DUAL SPI mode
    spi_read(flash->spidev, buf, buf_size);

    //Return to normal mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

//quad input page program
static void spi_nor_quad_page_program(struct spi_nor_flash *flash, uint32 addr, uint8 *buf, uint32 buf_size)
{
    uint8 write_buf[4];

    write_buf[0] = SPI_NOR_QUAD_PAGE_PROGRAM;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);

    spi_nor_standard_write_enable(flash);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 4);
    //data tx in QUAD SPI mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);
    spi_write(flash->spidev, buf, buf_size);
    //Return to normal mode
    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    //wait tx done
    while (spi_nor_standard_read_status_register(flash) & SPI_NOR_STATUS_BUSY);
    spi_nor_standard_write_disable(flash);
}


/**
  * @}
  */

/**
  * @brief QPI instructions
  * @note  warning! You need to confirm that nor flash supports this function.
  */
//JECEC ID
static void spi_nor_qpi_read_jedec_id(struct spi_nor_flash *flash, uint8 *buf)
{
    uint8 instruction = SPI_NOR_QPI_JEDEC_ID;

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_read(flash->spidev, buf, 3);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);
}

//write disable
static void spi_nor_qpi_write_disable(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_QPI_WRITE_DISABLE;

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);
}

//write enable
static void spi_nor_qpi_write_enable(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_QPI_WRITE_ENABLE;

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);
}

//read status register
static uint8 spi_nor_qpi_read_status_register(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_QPI_READ_STATUS_REG;
    uint8 result;

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_read(flash->spidev, &result, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);

    return result;
}

//write status register
static void spi_nor_qpi_write_status_register(struct spi_nor_flash *flash, uint16 data)
{
    uint8 write_buf[3];

    spi_nor_qpi_write_enable(flash);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);

    write_buf[0] = SPI_NOR_QPI_WRITE_STATUS_REG;
    write_buf[1] = data;
    write_buf[2] = data >> 8;
    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 3);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);

    spi_nor_qpi_write_disable(flash);
}

//fast read quad io
static void spi_nor_qpi_fast_read_quad_io(struct spi_nor_flash *flash, uint32 addr, uint8 *buf, uint32 buf_size)
{
    uint8 write_buf[5];

    write_buf[0] = SPI_NOR_QPI_FAST_READ_QUAD_IO;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;
    write_buf[4] = 0x00;

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 5);
    spi_read(flash->spidev, buf, buf_size);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);
}

//page program
static void spi_nor_qpi_page_program(struct spi_nor_flash *flash, uint32 addr, uint8 *buf, uint32 buf_size)
{
    uint8 write_buf[4];

    spi_nor_qpi_write_enable(flash);

    write_buf[0] = SPI_NOR_QPI_PAGE_PROGRAM;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 4);
    spi_write(flash->spidev, buf, buf_size);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);

    //wait page program done
    while (spi_nor_qpi_read_status_register(flash) & SPI_NOR_STATUS_BUSY);

    spi_nor_qpi_write_disable(flash);
}

//sector erase
static void spi_nor_qpi_sector_erase(struct spi_nor_flash *flash, uint32 addr)
{
    uint8 write_buf[4];

    spi_nor_qpi_write_enable(flash);

    write_buf[0] = SPI_NOR_QPI_SECTOR_ERASE;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 4);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);

    //wait sector erase done
    while (spi_nor_qpi_read_status_register(flash) & SPI_NOR_STATUS_BUSY);

    spi_nor_qpi_write_disable(flash);
}

//block erase
static void spi_nor_qpi_block_erase(struct spi_nor_flash *flash, uint32 addr)
{
    uint8 write_buf[4];

    spi_nor_qpi_write_enable(flash);

    write_buf[0] = SPI_NOR_QPI_BLOCK_ERASE;
    write_buf[1] = addr >> 16;
    write_buf[2] = addr >> 8;
    write_buf[3] = addr;

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, write_buf, 4);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);

    //wait block erase done
    while (spi_nor_qpi_read_status_register(flash) & SPI_NOR_STATUS_BUSY);

    spi_nor_qpi_write_disable(flash);
}

//chip erase
static void spi_nor_qpi_chip_erase(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_QPI_CHIP_ERASE;

    spi_nor_qpi_write_enable(flash);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);

    //wait block erase done
    while (spi_nor_qpi_read_status_register(flash) & SPI_NOR_STATUS_BUSY);

    spi_nor_qpi_write_disable(flash);
}

//disable QPI
static void spi_nor_standard_disable_qpi(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_QPI_DISABLE_QPI;

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_QUAD_MODE);

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);

    spi_ioctl(flash->spidev, SPI_WIRE_MODE_SET, SPI_WIRE_NORMAL_MODE);
}

//enter power down
static void spi_nor_qpi_power_down(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_STANDARD_POWER_DOWN;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

//release power down
static void spi_nor_qpi_release_power_down(struct spi_nor_flash *flash)
{
    uint8 instruction = SPI_NOR_STANDARD_RELEASE_POWER_DOWN;

    spi_set_cs(flash->spidev, flash->spi_config.cs, 0);
    spi_write(flash->spidev, &instruction, 1);
    spi_set_cs(flash->spidev, flash->spi_config.cs, 1);
}

static void spi_nor_qpi_open(struct spi_nor_flash *flash)
{
    uint16 status;
    
    //release power down
    spi_nor_qpi_release_power_down(flash);
    //wait done
    os_sleep_us(50);
    
    status = spi_nor_standard_read_status_register(flash);
    status |= SPI_NOR_STATUS2_QUAD_ENABLE;
    spi_nor_standard_write_status_register(flash, status);
    spi_nor_standard_enter_qpi(flash);
}

static void spi_nor_qpi_close(struct spi_nor_flash *flash)
{
    spi_nor_standard_disable_qpi(flash);
}

/**
  * @}
  */

//SPI NOR function
static const struct spi_nor_bus spinor_bus_list[] = {
    //NORMAL SPI
    {
        spi_nor_standard_open,
        NULL,
        spi_nor_standard_read_data,
        spi_nor_standard_page_program,
        spi_nor_standard_sector_erase,
        spi_nor_standard_block_erase,
        spi_nor_standard_chip_erase,
        spi_nor_standard_power_down,
        spi_nor_standard_release_power_down,
    },
    //DUAL SPI
    {
        spi_nor_standard_open,
        NULL,
        spi_nor_dual_fast_read_dual_output,
        spi_nor_standard_page_program,
        spi_nor_standard_sector_erase,
        spi_nor_standard_block_erase,
        spi_nor_standard_chip_erase,
        spi_nor_standard_power_down,
        spi_nor_standard_release_power_down,
    },
    //QUAD SPI
    {
        spi_nor_quad_open,
        NULL,
        spi_nor_quad_fast_read_quad_output,
        spi_nor_quad_page_program,
        spi_nor_standard_sector_erase,
        spi_nor_standard_block_erase,
        spi_nor_standard_chip_erase,
        spi_nor_standard_power_down,
        spi_nor_standard_release_power_down,
    },
    //QPI
    {
        spi_nor_qpi_open,
        spi_nor_qpi_close,
        spi_nor_qpi_fast_read_quad_io,
        spi_nor_qpi_page_program,
        spi_nor_qpi_sector_erase,
        spi_nor_qpi_block_erase,
        spi_nor_qpi_chip_erase,
        spi_nor_qpi_power_down,
        spi_nor_qpi_release_power_down,
    },
};

const struct spi_nor_bus *spi_nor_bus_get(enum spi_nor_mode mode)
{
    ASSERT(mode <= SPI_NOR_QPI_MODE);
    return &spinor_bus_list[mode];
}

