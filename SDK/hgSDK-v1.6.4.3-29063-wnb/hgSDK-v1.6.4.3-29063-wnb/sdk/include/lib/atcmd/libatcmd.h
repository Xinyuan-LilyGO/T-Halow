#ifndef _HUGEIC_ATCMD_H_
#define _HUGEIC_ATCMD_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*hgic_atcmd_outhdl)(void *priv, uint8 *data, int32 len);

typedef int32(*hgic_atcmd_hdl)(const char *cmd, uint8 *data, int32 len);

#define atcmd_dbg(fmt, ...) //os_printf("%s:%d::"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define atcmd_err(fmt, ...) os_printf(fmt, ##__VA_ARGS__)

#define AT_END(str)   (os_strcmp(str, "+++") == 0)
#define atcmd_resp(fmt, ...) atcmd_printf("%s:"fmt"\r\nOK\r\n", cmd+2, ##__VA_ARGS__)
#define atcmd_ok             atcmd_printf("OK\r\n")
#define atcmd_error          atcmd_printf("ERROR\r\n")

int32 atcmd_init(int32 uart_id);
int32 atcmd_recv(uint8 *data, int32 len);
int32 atcmd_register(const char *cmd, hgic_atcmd_hdl hdl, const char *help);
int32 atcmd_unregister(const char *cmd);
char *atcmd_args(uint32 index);
int32 atcmd_args_num(void);
void atcmd_output(uint8 *data, int32 len);
void atcmd_output_hdl(hgic_atcmd_outhdl output, void *arg);
void atcmd_printf(const char *format, ...);
uint8 atcmd_getchar(int32 *err);
void atcmd_dumphex(char *prestr, uint8 *data, int32 len, uint8 newline);

#ifdef __cplusplus
}
#endif
#endif
