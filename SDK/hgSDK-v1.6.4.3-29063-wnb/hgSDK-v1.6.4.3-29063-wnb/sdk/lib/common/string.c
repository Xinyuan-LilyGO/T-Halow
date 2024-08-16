
#include "typesdef.h"
#include "list.h"
#include "dev.h"
#include "devid.h"
#include "osal/mutex.h"
#include "osal/string.h"
#include "hal/uart.h"
#include "hal/spi_nor.h"
#include "lib/atcmd/libatcmd.h"


#if ERRLOG_SIZE
struct sys_errlog {
    char buff[ERRLOG_SIZE];
    uint16 off;
    uint8  wr_idx, enable;
    uint32 wr_num;
};
struct sys_errlog _errlogs;
#endif


struct os_mutex _print_m_;
int    _print_m_init_ = 0;

static int32_t _disable_printf_ = 0;

void print_lock(void)
{
    if (!_print_m_init_) {
        os_mutex_init(&_print_m_);
        _print_m_init_ = 1;
    }
    os_mutex_lock(&_print_m_, osWaitForever);
}

void print_unlock(void)
{
    os_mutex_unlock(&_print_m_);
}

int32 hex2int(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

int32 hex2char(char *hex)
{
    int a, b;
    a = hex2int(*hex++);
    if (a < 0) {
        return -1;
    }
    b = hex2int(*hex++);
    if (b < 0) {
        return -1;
    }
    return (a << 4) | b;
}

int32 hex2bin(char *hex_str, uint8 *bin, uint32 len)
{
    uint32 i = 0;
    uint32 str_len = 0;
    int32  a;
    char *ipos = hex_str;
    uint8 *opos = bin;

    if (!hex_str || !bin) {
        return i;
    }

    str_len = os_strlen(hex_str);
    for (i = 0; i < len && (i * 2) + 2 <= str_len; i++) {
        a = hex2char(ipos);
        if (a < 0) {
            return i;
        }
        *opos++ = (uint8)a;
        ipos += 2;
    }
    return i;
}

void str2mac(char *macstr, uint8 *mac)
{
    mac[0] = hex2char(macstr);
    mac[1] = hex2char(macstr + 3);
    mac[2] = hex2char(macstr + 6);
    mac[3] = hex2char(macstr + 9);
    mac[4] = hex2char(macstr + 12);
    mac[5] = hex2char(macstr + 15);
}

uint32 os_atoh(char *str)
{
    uint32 val = 0;
    uint8  s = 0;

    if (os_strlen(str) > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        str += 2;
    }

    while (*str) {
        if ((*str >= '0') && (*str <= '9')) {
            s = *str - '0';
        } else if ((*str >= 'A') && (*str <= 'F')) {
            s = 0x0A + (*str - 'A');
        } else if ((*str >= 'a') && (*str <= 'f')) {
            s = 0x0A + (*str - 'a');
        } else {
            break;
        }
        val = (val << 4) + s;
        str++;
    }
    return val;
}

#if ERRLOG_SIZE
__weak int32 errlog_flashinfo(struct spi_nor_flash **flash, uint32 *addr, uint32 *size)
{
    return RET_ERR;
}

static uint8 errlog_wridx(uint32 *wr_num)
{
    uint32 errlog_addr = 0;
    uint32 errlog_size = 0;
    uint32 num = 0;
    uint16 num_max = 0;
    uint8  idx = 0;
    uint8  max_idx = 0;
    struct spi_nor_flash *flash = NULL;

    if (errlog_flashinfo(&flash, &errlog_addr, &errlog_size) == RET_OK) {
        spi_nor_open(flash);
        while ((idx * flash->sector_size) < errlog_size) {
            spi_nor_read(flash, errlog_addr + (idx * flash->sector_size), (uint8 *)&num, 4);
            if ((num >> 24) == 0xab) {
                num &= 0xffffff;
                if (num > num_max) {
                    num_max = num;
                    max_idx = idx;
                }
            }
            idx++;
        }
        spi_nor_close(flash);
    }

    *wr_num = num_max;
    return max_idx;
}

__weak void errlog_write(char *log, uint32 size)
{
    uint32 errlog_addr = 0;
    uint32 errlog_size = 0;
    uint32 wr_addr;
    uint32 num = 0;
    struct spi_nor_flash *flash = NULL;
    if (errlog_flashinfo(&flash, &errlog_addr, &errlog_size) == RET_OK) {
        if (_errlogs.wr_num == 0) {
            _errlogs.wr_idx = errlog_wridx(&_errlogs.wr_num);
        }

        _errlogs.wr_num++;
        _errlogs.wr_idx++;
        if (_errlogs.wr_idx * ERRLOG_SIZE >= errlog_size) {
            _errlogs.wr_idx = 0;
        }

        //hgprintf("wr_idx=%d, wr_num=%d\r\n", _errlogs.wr_idx, _errlogs.wr_num);
        num = _errlogs.wr_num | 0xab000000;
        wr_addr = errlog_addr + _errlogs.wr_idx * ERRLOG_SIZE;
        spi_nor_open(flash);
        spi_nor_sector_erase(flash, wr_addr);
        spi_nor_write(flash, wr_addr, (uint8 *)&num, 4);
        spi_nor_write(flash, wr_addr + 4, (uint8 *)log, flash->sector_size - 4);
        spi_nor_close(flash);
    }
}

__weak void errlog_dump(void)
{
    char *buf = NULL;
    uint32 rd_addr;
    uint32 errlog_addr = 0;
    uint32 errlog_size = 0;
    struct spi_nor_flash *flash = NULL;

    if (errlog_flashinfo(&flash, &errlog_addr, &errlog_size) == RET_OK) {
        buf = os_malloc(256);
        if (buf) {
            rd_addr = errlog_addr;
            hgprintf_out("ERRLOG DUMP:\r\n", 0);
            spi_nor_open(flash);
            while (rd_addr < errlog_addr + errlog_size) {
                spi_nor_read(flash, rd_addr, (uint8 *)buf, 256);
                hgprintf_out(buf, 256);
                rd_addr += 256;
            }
            spi_nor_close(flash);
            os_free(buf);
        }
    }
}

__weak void errlog_clear(void)
{
    uint32 addr;
    uint32 errlog_addr = 0;
    uint32 errlog_size = 0;
    struct spi_nor_flash *flash = NULL;
    if (errlog_flashinfo(&flash, &errlog_addr, &errlog_size) == RET_OK) {
        addr = errlog_addr;
        spi_nor_open(flash);
        while (addr < errlog_addr + errlog_size) {
            spi_nor_sector_erase(flash, addr);
            addr += flash->sector_size;
        }
        spi_nor_close(flash);
        hgprintf_out("ERRLOG CLEAN\r\n", 0);
    }
}

static void errlog_do_flush(void)
{
    if (_errlogs.enable) {
        errlog_write(_errlogs.buff, ERRLOG_SIZE);
    }
}

static void errlog_save(char *msg, uint32 len)
{
    uint32 flag;
    uint32 off;

    if (_errlogs.enable) {
        flag = disable_irq();
        off  = _errlogs.off;
        if (off + len > ERRLOG_SIZE) off = 0;
        _errlogs.off = off + len;
        enable_irq(flag);
        os_strncpy(_errlogs.buff + off, msg, ERRLOG_SIZE - off);
    }
}

void errlog_flush(void)
{
    const char *cmd = "at+errlog=2";
    if (_errlogs.enable) {
        atcmd_recv((uint8 *)cmd, os_strlen(cmd));
    }
}

void errlog_action(uint8 action)
{
    switch (action) {
        case 0: //disable
            _errlogs.enable = 0;
            break;
        case 1: //enable
            _errlogs.enable = 1;
            break;
        case 2: //flush
            errlog_do_flush();
            break;
        case 3: //dump
            errlog_dump();
            break;
        case 4: //clear
            errlog_clear();
            break;
        default:
            break;
    }
}

#endif

void (*__print_redirect)(char *msg);
void osprint_redirect(void (*print)(char *msg))
{
    __print_redirect = print;
}
static void hgprintf_uart(char *str, int32 len)
{
    extern void *console_handle;
    int32 off = 0;
    if (len == 0) len = os_strlen(str);
    while (off < len) {
        uart_putc((struct uart_device *)console_handle, str[off++]);
    }
}

void hgprintf_out(char *str, int32 len)
{
    void (*_print)(char *msg) = __print_redirect;
    if (_print) {
        _print(str);
    } else {
        hgprintf_uart(str, len);
    }
}

void disable_print(void)
{
    _disable_printf_ = 1;
}

void enable_print(void)
{
    _disable_printf_ = 0;
}

void hgprintf(const char *fmt, ...)
{
#define HGPRINTF_LEN (1024)
    static char _print_buff_p[HGPRINTF_LEN];
    int32 len = 0;
    va_list ap;
    if (_disable_printf_ && !__print_redirect) { return; }
    va_start(ap, fmt);
    len = vsnprintf(_print_buff_p, (HGPRINTF_LEN - 1), fmt, ap);
    if (len < 0 || len > (HGPRINTF_LEN - 1)) {
        len = HGPRINTF_LEN - 1;
        _print_buff_p[len - 1] = '\n';
        _print_buff_p[len - 2] = '\r';
    }

    va_end(ap);
    if (len > 0) {
        _print_buff_p[len] = 0;
        hgprintf_out(_print_buff_p, len);
#if ERRLOG_SIZE
        errlog_save(_print_buff_p, len);
#endif
    }
}


void dump_hex(char *str, uint8 *data, uint32 len)
{
    int i = 0;
    if (data && len) {
        if (str) { _os_printf("%s", str); }
        for (i = 0; i < len; i++) {
            if (i > 0) {
                if ((i & 0x7) == 0) { _os_printf("   "); }
                if ((i & 0xf) == 0) { _os_printf("\r\n"); }
            }
            _os_printf("%02x ", data[i] & 0xFF);
        }
        _os_printf("\r\n");
    }
}

void dump_key(uint8 *str, uint8 *key, uint32 len)
{
    int32 i = 0;
    if (key && len) {
        if (str) { _os_printf("%s:", str); }
        for (i = 0; i < len; i++) { _os_printf("%02x", key[i]); }
        _os_printf("\r\n");
    }
}

int32 os_random_bytes(uint8 *data, int32 len)
{
    int32 i = 0;
    int32 seed;
#ifdef TXW4002ACK803
    seed = csi_coret_get_value() ^ (csi_coret_get_value() << 8) ^ (csi_coret_get_value() >> 8);
#else
    seed = csi_coret_get_value() ^ sysctrl_get_trng() ^ (sysctrl_get_trng() >> 8);
#endif
    for (i = 0; i < len; i++) {
        seed = seed * 214013L + 2531011L;
        data[i] = (uint8)(((seed >> 16) & 0x7fff) & 0xff);
    }
    return 0;
}

uint32 os_rand(void)
{
    uint32 data = 0;
    os_random_bytes((uint8 *)&data, 4);
    return data;
}