#ifndef _HGIC_FWINFO_H_
#define _HGIC_FWINFO_H_

#define fwinfo_dbg(fmt, ...) //os_printf("%s:%d::"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define fwinfo_err(fmt, ...) os_printf(fmt, ##__VA_ARGS__)

#define FWINFO_BOOT_HDR    0x5a69
#define FWINFO_SPI_HDR     0x1
#define FWINFO_CODE_HDR    0x2
#define FWINFO_ENCRYPT_INFO_HDR    0x3

struct fwinfo_spiflash_header_boot {
    uint16 boot_flag;              /* 0  :  0x5a69, header boot flag  */
    uint8  version;                /* 2  :  version                  */
    uint8  size;                   /* 3  :  Link to Next Header      */
    uint32 boot_to_sram_addr;       /* 4  :  spi data load to sram addr   */
    uint32 run_sram_addr;           /* 8  :  code execute start addr  */
    uint32 boot_code_offset_addr;     /* 12 :  HeaderLen+ParamLen=4096+512        */
    uint32 boot_from_flash_len;       /* 16 :         */
    uint16 boot_data_crc;           /* 20 :  boot data crc check      */
    uint16 flash_blk_size;       /* 22 :  flash size in 64KB(version > 1),   512B(version== 0) */
    uint16 boot_baud_mhz : 14,   /* 24 :  spi clk freq in mhz(version > 1),  khz(version== 0) */
           driver_strength : 2;      /*       io driver strength */

    struct {
        uint16 pll_src : 8,   /*       pll src in Mhz */
               pll_en : 1,   /*       PLL enable */
               debug : 1,   /*       debug info uart output enable */
               aes_en : 1,   /*       AES enable */
               crc_en : 1,   /*       CRC check enable */
               reserved : 4;
    } mode;                     /* 26 :  boot option */
    uint16 reserved;               /* 28 :  */
    uint16 head_crc16;             /*       (size+4) byte CRC16 check value */
}__packed;

/* format : cmd + dummys_flags + dat_len + dat */
struct fwinfo_spiflash_spec_sequnce {
    uint8  cmd_nums;
    uint8  cmd;
    uint8  dummy;
    uint8  dat_len;
    uint8  dat;
};

struct fwinfo_spiflash_read_cfg {
    uint8  read_cmd;                       /* read_cmd */
    uint8  cmd_dummy_cycles : 4,            /* read dummy cycles */
           clock_mode : 2,            /* clock polarity & phase */
           spec_sequnce_en : 1,            /* spec sequnce to execute, maybe same with quad_wire_en */
           quad_wire_en : 1;                   /* spi D2/D3 enable */

    uint8  wire_mode_cmd : 2,
           wire_mode_addr : 2,
           wire_mode_data : 2,
           quad_wire_select : 2;               /* spi D2/D3 group select */

    uint8  reserved3;

    uint16 sample_delay;                   /* RX sample dalay time: 0 ~ clk_divor */
}__packed;


struct fwinfo_spiflash_header_spi_info {
    uint8 func_code;                       /* 0 : header function(0x1)  */
    uint8 size;                            /* 1:  Link to Next Header   */

    struct fwinfo_spiflash_read_cfg read_cfg;
    uint8  fwinfo_spiflash_spec_sequnce[64];

    uint16 header_crc16;                   /*     (size+2) byte CRC16 check value */
}__packed;

/*  fwinfo_ah_fw_v1.0.1.1_2020.2.20.bin  ？*/


struct fwinfo_spiflash_header_firmware_info {
    uint8 func_code;                       /* 0 : header function(0x2)  */
    uint8 size;                            /* 1:  Link to Next Header   */
    uint32 sdk_version;                         /* version   */
    uint32 svn_version;
    uint32 date;                           /* date   */
    uint16 chip_id;                        /* chip_id   */
    uint8 cpu_id;                         /* cpu id, fix 0  */
    uint32 code_crc32;                    /* code CRC32 */
    uint16 param_crc16;                    /* param CRC16 */
    uint16 crc16;                   /*     (size+2) byte CRC16 check value */
}__packed;

struct spiflash_header_encrypt_info  {
    unsigned char  func_code;                       /* 0 : header function(0x3)  */
    unsigned char  size;                            /* 1:  Link to Next Header   */
	unsigned short customer_id;                         /* customer_id */
    unsigned short crc16;                         /* (size) byte CRC16 check value */
}__packed;

struct fwinfo_hdr {
    struct fwinfo_spiflash_header_boot        boot;
    struct fwinfo_spiflash_header_spi_info        spi_infor;      /* func1*/
    struct fwinfo_spiflash_header_firmware_info   fw_infor ;  /* func2*/
    struct spiflash_header_encrypt_info   spec_encrypt_infor ; 	/* func3*/
}__packed;

uint16 fwinfo_crc16(const uint8 *data, uint32 length);
uint32 fwinfo_crc32(const uint8 *data, uint32 length);
int32 fwinfo_check_fwinfo_hdr(const uint8 *data);
uint16 fwinfo_get_fw_aes_en(const uint8 *data, int32 *err_code);
uint16 fwinfo_get_fw_crc_en(const uint8 *data, int32 *err_code);
uint32 fwinfo_get_fw_dl_addr(const uint8 *data, int32 *err_code);
uint32 fwinfo_get_fw_run_addr(const uint8 *data, int32 *err_code);
uint32 fwinfo_get_fw_code_offset(const uint8 *data, int32 *err_code);
uint32 fwinfo_get_fw_local_crc32(const uint8 *data, int32 *err_code);
uint32 fwinfo_get_fw_sdk_version(const uint8 *data, int32 *err_code);
uint32 fwinfo_get_fw_svn_version(const uint8 *data, int32 *err_code);
uint16 fwinfo_get_fw_chipid(const uint8 *data, int32 *err_code);
uint8  fwinfo_get_fw_cpuid(const uint8 *data, int32 *err_code);
int32 fwinfo_get_fw_code_checksum(const uint8 *data, int32 len);
uint32  fwinfo_get_fw_lenght(const uint8 *data, int32 *err_code);
int32 fwinfo_check_customer_id(const uint8 *data);


#endif
