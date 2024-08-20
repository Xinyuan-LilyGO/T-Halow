#ifndef __SYS_PROJECT_CONFIG_H__
#define __SYS_PROJECT_CONFIG_H__
#define WNB_STA_COUNT (8)
//#define WNB_HEARTBEAT_INT 2000

#define AUTO_ETHERNET_PHY
//#define ETHERNET_IP101G
#define ETHERNET_PHY_ADDR               -1

#define DEFAULT_SYS_CLK    96000000UL //options: 32M/48M/72M/144M, and 16*N from 64M to 128M
#define ATCMD_UARTDEV      HG_UART1_DEVID

#define MEM_TRACE
#define MEM_OFCHK

//#define IGONOR_ROLE_KEY


#endif
