#ifndef __SYS_CONFIG_H__
#define __SYS_CONFIG_H__
#include <stdint.h>
#include "project_config.h"
/*
#define CONFIG_PATH(x) CONFIG_PATH1(x)
#define CONFIG_PATH1(x) #x
#define CONFIG_FILE(x) CONFIG_PATH(customer/x.h)
#define CUSTOMER meari
#include CONFIG_FILE(CUSTOMER)
*/
#define RTOS_ENABLE
#define OS_TASK_COUNT 20

#define SYSCFG_ENABLE
#define PROJECT_TYPE PRO_TYPE_WNB
#define WNB_RSSID_34LED
#define MACBUS_GMAC

/* SYS_KEY protect enable */
#define SYS_KEY_OPT_EN                  0

#define USING_TX_SQ
#define TDMA_DEBUG
#define RXSUBFRAME_EN       1
#define RXSUBFRAME_PERIOD   (5)
//#define DEEP_SLEEP

#ifndef TDMA_BUFF_SIZE
#define TDMA_BUFF_SIZE    (32*4*100)
#endif
#ifndef SYS_HEAP_SIZE
#define  SYS_HEAP_SIZE (50*1024+1024*WNB_STA_COUNT)
#endif
#ifndef WIFI_RX_BUFF_SIZE
#if  (128*1024) >= (1024*WNB_STA_COUNT)
#define  WIFI_RX_BUFF_SIZE (128*1024-1024*WNB_STA_COUNT)
#else
#define  WIFI_RX_BUFF_SIZE (0)
#endif
#endif
#if WIFI_RX_BUFF_SIZE < (64*1024)
#undef WIFI_RX_BUFF_SIZE
#define WIFI_RX_BUFF_SIZE (64*1024)
#endif

extern uint32_t userpool_start;
extern uint32_t userpool_end;
#define USER_POOL_START   (userpool_start)
#define USER_POOL_SIZE    ((userpool_end) - (userpool_start))
#define TDMA_BUFF_ADDR    (USER_POOL_START)
#define SYS_HEAP_START    (TDMA_BUFF_ADDR+TDMA_BUFF_SIZE)
#define WIFI_RX_BUFF_ADDR (SYS_HEAP_START+SYS_HEAP_SIZE)
#define SKB_POOL_ADDR     (WIFI_RX_BUFF_ADDR+WIFI_RX_BUFF_SIZE)
#define SKB_POOL_SIZE     (USER_POOL_START+USER_POOL_SIZE-SKB_POOL_ADDR)

#define K_EXT_PA
//#define K_iPA
#ifdef K_EXT_PA
#define K_VMODE_CNTL
#endif
#define K_SINGLE_PIN_SWITCH
//#define K_MIPI_IF

#define RF_PARA_FROM_NOR   //if open it to read parameter from nor in case efuse is not ready
                            //when efuse data is ready, close it

/*! Use GPIO to simulate the MII management interface                           */
#define HG_GMAC_IO_SIMULATION
#ifndef HG_GMAC_MDIO_PIN
#define HG_GMAC_MDIO_PIN PA_7
#endif
#ifndef HG_GMAC_MDC_PIN
#define HG_GMAC_MDC_PIN  PA_8
#endif

#define HGGPIO_DEFAULT_LEVEL 2

#define US_TICKER_TIMER HG_TIMER0_DEVID
#define UART_P2P_TIMER  HG_TIMER2_DEVID

#define MEM_DMA_ENABLE

#ifndef LED_INIT_BLINK
#define LED_INIT_BLINK 1
#endif
#ifndef WNB_AUTO_ROLE
#define WNB_AUTO_ROLE 0
#endif
#ifndef WNB_SUPP_PWR_OFF
#define WNB_SUPP_PWR_OFF 0
#endif
#ifndef MCU_FUNCTION
#define MCU_FUNCTION 0
#else
#define MCU_PIR_SENSOR_MUX_SPI_IO
#endif
#ifndef MAX_TX_POWER
#define MAX_TX_POWER 20
#endif

#ifndef WNB_BEACON_INT
#define WNB_BEACON_INT 500
#endif

#ifndef WNB_HEARTBEAT_INT
#define WNB_HEARTBEAT_INT 500
#endif

#ifndef WNB_MCAST_FILTER
#define WNB_MCAST_FILTER 0
#endif

#ifndef WNB_AP_HIDE
#define WNB_AP_HIDE 0
#endif

#ifndef WNB_NEW_KEY
#define WNB_NEW_KEY 0
#endif

#ifndef ACK_TO_EXTRA
#define ACK_TO_EXTRA 0
#endif

#ifndef ERRLOG_SIZE
#define ERRLOG_SIZE (4096)
#endif

//when using sleep，choose mcs0，else choose mcs10
#ifndef BW1M_MGMT_MCS
#define BW1M_MGMT_MCS MCS0
#endif

#ifndef TRV_PILOT
#define TRV_PILOT 1
#endif

struct sys_config {
    uint16_t magic_num, crc;
    uint16_t size, rev1, rev2, rev3;
    uint8_t  wnbcfg[512+40*WNB_STA_COUNT];
};
extern struct sys_config sys_cfgs;

#endif
