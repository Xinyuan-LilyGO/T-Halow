#ifndef __FW_H__
#define __FW_H__

#ifdef __cplusplus
extern "C" {
#endif

#define fw_ota_dbg(fmt, ...)                //os_printf(fmt, ##__VA_ARGS__)

/* The OTA marker and marker size are only applicable to huge-ic chips. */
#define OTA_FLASH_MARKER                    0x5A69
#define OTA_FLASH_MARKER_SIZE               2
#define OTA_VERIFY_READ_BUF_SIZE            256

/* OTA inof */
struct ota_info_type {
    struct spi_nor_flash   *flash0;
    uint32                  addr0;
    /* If flash1 is not NULL, it means dual firmware function is used. */
    struct spi_nor_flash   *flash1;
    uint32                  addr1;
};

/* OTA control */
struct ota_ctrl {
    struct spi_nor_flash *p_flash;
    uint32 base_addr;
    uint32 local_off;
    uint32 marker;
    uint16 erase_start, erase_end;
    uint8  verify_read_buf[OTA_VERIFY_READ_BUF_SIZE];
};

extern struct ota_info_type ota_info;

int32 libota_write_fw(uint32 tot_len, uint32 off, uint8 *data, uint16 len);

#ifdef __cplusplus
}
#endif

#endif

