#include "typesdef.h"
#include "list.h"
#include "dev.h"
#include "devid.h"
#include "osal/string.h"
#include "osal/semaphore.h"
#include "osal/mutex.h"
#include "osal/irq.h"
#include "osal/task.h"
#include "osal/sleep.h"
#include "osal/timer.h"
#include "hal/gpio.h"
#include "hal/watchdog.h"
#include "hal/sysaes.h"
#include "lib/common.h"
#include "lib/syscfg.h"
#include "lib/sysheap.h"
#include "lib/skb/skb.h"
#include "lib/skb/skb_list.h"
#include "lib/mac_bus.h"
#include "lib/lmac/lmac.h"
#include "lib/lmac/lmac_host.h"
#include "lib/wnb/libwnb.h"
#include "lib/xmodem.h"
#include "lib/atcmd/libatcmd.h"


#define WNB_SIGNAL_LED1   PA_9
#ifdef DUAL_UART_DBG_PRINT
#define WNB_SIGNAL_LED2   PA_14 //empty pin
#define WNB_SIGNAL_LED3   PA_15 //empty pin
#else
#define WNB_SIGNAL_LED2   PA_31
#define WNB_SIGNAL_LED3   PA_30
#endif
#ifdef USING_ROLE_LED
#define WNB_CONN_LED_IO   PA_9
#define WNB_PAIR_LED      PA_9
#define WNB_ROLE_LED      PA_6
#else
#define WNB_CONN_LED_IO   PA_6
#ifdef CONN_IO_REVERT
#define WNB_CONN_LED_IO_REVERT   PB_1
#endif
#define WNB_PAIR_LED      PA_6
#endif
#define WNB_PAIR_KEY      PB_1
#define WNB_ROLE_KEY      PA_31
#ifdef USING_RESET_KEY
#define WNB_RESET_KEY     PB_1
#else
#define WNB_RESET_KEY     PA_8
#endif

#ifdef ETH_PHY_RESET
#define ETH_PHY_RESET_IO  PB_1
#endif

#ifndef IGONOR_PAIR_KEY
static struct os_task wnb_pairkey_task;
#endif
#if !defined(IGONOR_ROLE_KEY) && !defined(RESET_REPLACE_ROLE_KEY)
static struct os_task wnb_rolekey_task;
#endif
#if defined(USING_RESET_KEY) || defined(RESET_REPLACE_ROLE_KEY)
static struct os_task wnb_resetkey_task;
#endif

struct wnb_config wnbcfg = {
    .role = WNB_STA_ROLE_SLAVE,
    .chan_list = {9080, 9160, 9240},
    .chan_cnt = 3,
    .bss_bw   = 8,
    .pri_chan = 3,
    .tx_mcs   = 0xff,
    .encrypt  = 1,
    .forward  = 1,
    .max_sta  = WNB_STA_COUNT,
    .acs_enable = 1,
    .bss_max_idle = 300,
    .beacon_int = WNB_BEACON_INT,
    .heartbeat_int = WNB_HEARTBEAT_INT,
    .dtim_period = 2,
    .mcast_filter = WNB_MCAST_FILTER,
    .auto_role = WNB_AUTO_ROLE,
    .supper_pwr_set = WNB_SUPP_PWR_OFF,
    .ap_hide = WNB_AP_HIDE,
    .tx_power = MAX_TX_POWER,
    .dupfilter = 1,
    .ack_tmo= ACK_TO_EXTRA,
};

static uint8 sysdbg_heap = 0;
static uint8 sysdbg_top = 0;
static uint8 sysdbg_irq = 0;
static uint8 sysdbg_wnb = 0;
static uint8 sysdbg_lmac = 1;
static uint8 pair_waitting = 0;

#if ERRLOG_SIZE
static int32 sys_atcmd_errlog_hdl(const char *cmd, uint8 *data, int32 len)
{
    char *arg = atcmd_args(0);
    if(atcmd_args_num() == 1){
        errlog_action(os_atoi(arg));
    }
    return 0;
}
#endif

static int32 sys_atcmd_sysdbg_hdl(const char *cmd, uint8 *data, int32 len)
{
    char *arg = atcmd_args(0);
    if (atcmd_args_num() == 2) {
        if (os_strcasecmp(arg, "heap") == 0) {
            sysdbg_heap = os_atoi(atcmd_args(1));
        }
        if (os_strcasecmp(arg, "top") == 0) {
            sysdbg_top = os_atoi(atcmd_args(1));
        }
        if (os_strcasecmp(arg, "irq") == 0) {
            sysdbg_irq = os_atoi(atcmd_args(1));
        }
        if (os_strcasecmp(arg, "wnb") == 0) {
            sysdbg_wnb = os_atoi(atcmd_args(1));
        }
        if (os_strcasecmp(arg, "lmac") == 0) {
            sysdbg_lmac = os_atoi(atcmd_args(1));
        }
        atcmd_ok;
    } else {
        atcmd_error;
    }
    return 0;
}

static int32 syscfg_save_def(void)
{
    int ret = RET_ERR;
    if (sys_cfgs.magic_num != SYSCFG_MAGIC) {
        // set syscfg default value
        // save wnbcfg (actully total syscfg) at last
        ret = wnb_save_cfg(&wnbcfg, 1);
        os_printf("save default syscfg %s\r\n", ret ? "Fail" : "OK");
    }
    return ret;
}

static void watchdog_init(void)
{
    struct watchdog_device *wd = (struct watchdog_device *)dev_get(HG_WDTV1_DEVID);
    ASSERT(wd);
    watchdog_device_open(wd, 0);
    watchdog_device_start(wd, 5);
    //watchdog_device_stop(wd);
}

#ifndef IGONOR_PAIR_KEY
static int32 wnb_pair_key_val(void)
{
    int32 i, v;
    int32 v0 = 0, v1 = 0;

    for (i = 0; i < 50; i++) {
        v = gpio_get_val(WNB_PAIR_KEY);
        if (v) { v1++; }
        else  { v0++; }
    }
    return (v1 > v0 ? 1 : 0);
}

static void wnb_pair_key_task(void *args)
{
    int32 new_val, last_val, defval;

    defval  = 1;
    last_val = wnb_pair_key_val();

    os_printf("key default: %d\r\n", defval);
    while (1) {
        os_sleep_ms(100);
        new_val = wnb_pair_key_val();
        if (new_val != last_val) {
            if (new_val == defval) {
                wnb_pairing(0);
            } else {
                wnb_pairing(1);
            }
            last_val = new_val;
        }
    }
}
#endif

#if !defined(IGONOR_ROLE_KEY) && !defined(RESET_REPLACE_ROLE_KEY)
static void wnb_role_key_task(void *args)
{
    int32 new_val, last_val;

    last_val = gpio_get_val(WNB_ROLE_KEY);

    while (1) {
        os_sleep_ms(100);
        new_val = gpio_get_val(WNB_ROLE_KEY);
        if (new_val != last_val) {
            os_printf("role key press:%d\r\n", new_val);
            mcu_reset();
        }
    }
}
#endif

#if defined(USING_RESET_KEY) || defined(RESET_REPLACE_ROLE_KEY)
static void wnb_reset_key_task(void *args)
{
    int32 new_val, last_val, defval;
    int8 reset_start = 0;
    uint32 reset_tick = 0;

    defval  = 1;
    last_val = gpio_get_val(WNB_RESET_KEY);

    while (1) {
        os_sleep_ms(100);
        new_val = gpio_get_val(WNB_RESET_KEY);
        if (new_val != last_val) {
            if (new_val == defval) { // 放手
                reset_start = 0;
            } else { // 按下
                reset_start = 1;
                reset_tick = os_jiffies();
            }
            last_val = new_val;
        }
        if (reset_start && DIFF_JIFFIES(reset_tick, os_jiffies()) > 5000) {
            os_printf("factory data reset\r\n");
            syscfg_loaddef();
            mcu_reset();
        }
    }
}
#endif

#ifdef USING_STA_LED
static void wnb_sta_led(uint8 sta_num)
{
    gpio_set_val(WNB_CONN_LED_IO, sta_num >= 1 ? 0 : 1);
    gpio_set_val(WNB_SIGNAL_LED1, sta_num >= 2 ? 0 : 1);
    //gpio_set_val(WNB_SIGNAL_LED2, sta_num >= 3 ? 0 : 1);
    gpio_set_val(WNB_SIGNAL_LED3, sta_num >= 4 ? 0 : 1);
}
#endif

#ifdef USING_ROLE_LED
static void wnb_role_led()
{
    if (wnbcfg.role == WNB_STA_ROLE_MASTER) {
        gpio_set_val(WNB_ROLE_LED, 0);
    } else if (wnbcfg.role == WNB_STA_ROLE_SLAVE) {
        gpio_set_val(WNB_ROLE_LED, 1);
    } else {
        gpio_set_val(WNB_ROLE_LED, !gpio_get_val(WNB_ROLE_LED));
    }
}
#endif

static void wnb_event_hdl(wnb_event evt, uint32 param1, uint32 param2)
{
    static int __pair_led_on = 0;
    switch (evt) {
        case WNB_EVENT_PAIR_START:
            os_printf("wnb: start pairing ...\r\n");
            pair_waitting = 1;
#ifndef IOA6_1_ON
            gpio_set_val(WNB_PAIR_LED, 1);
#else
            gpio_set_val(WNB_PAIR_LED, 0);
#endif
            break;
        case WNB_EVENT_PAIR_SUCCESS:
            pair_waitting = 0;
#ifndef IOA6_1_ON
            gpio_set_val(WNB_PAIR_LED, __pair_led_on ? 0 : 1);
#else
            gpio_set_val(WNB_PAIR_LED, __pair_led_on ? 1 : 0);
#endif
            __pair_led_on = !__pair_led_on;
            os_printf("wnb: pairing success!\r\n");
            break;
        case WNB_EVENT_PAIR_DONE:
            pair_waitting = 0;
#ifndef USING_STA_LED
#ifndef IOA6_1_ON
            gpio_set_val(WNB_PAIR_LED, 1);          //disable WNB_PAIR_LED
            
            if (param2 > 0) {
                gpio_set_val(WNB_CONN_LED_IO, 0);   //enable WNB_CONN_LED_IO
#ifdef  CONN_IO_REVERT
                gpio_set_val(WNB_CONN_LED_IO_REVERT, 1);  
#endif 
            } else {
                gpio_set_val(WNB_CONN_LED_IO, 1);   //disable WNB_CONN_LED_IO
#ifdef  CONN_IO_REVERT
                gpio_set_val(WNB_CONN_LED_IO_REVERT, 0);
#endif
            }
#else
            gpio_set_val(WNB_PAIR_LED, 0);          //disable WNB_PAIR_LED
            
            if (param2 > 0) {
                gpio_set_val(WNB_CONN_LED_IO, 1);   //enable WNB_CONN_LED_IO
            } else {
                gpio_set_val(WNB_CONN_LED_IO, 0);   //disable WNB_CONN_LED_IO
            }
#endif
#else
            wnb_sta_led(param2);
#endif
            os_printf("wnb: pairing done, save wnb config!\r\n");
            if(wnb_save_cfg((struct wnb_config *)param1, 0)){
                os_printf("save wnb config fail, try again!\r\n");
                wnb_save_cfg((struct wnb_config *)param1, 0);
            }
            break;
        case WNB_EVENT_RX_DATA:
            os_printf("wnb: rx customer data 0x%x, len:%d\r\n", param1, param2);
#ifdef UART_P2P_DEV
void uart_p2p_recv(uint8 *data, uint32 len);
            uart_p2p_recv((uint8 *)param1, param2);
#endif
            break;
        case WNB_EVENT_CONNECT_START:
            //os_printf("wnb: start connecting ...\r\n");
            break;
        case WNB_EVENT_CONNECTED:
#ifndef USING_STA_LED
            os_printf("wnb: ["MACSTR"] connect success!\r\n", MAC2STR((uint8 *)param1));
#ifndef IOA6_1_ON
            gpio_set_val(WNB_CONN_LED_IO, 0);
#ifdef  CONN_IO_REVERT
            gpio_set_val(WNB_CONN_LED_IO_REVERT, 1);
#endif
#else
            gpio_set_val(WNB_CONN_LED_IO, 1);
#endif
#else
            wnb_sta_led(param2);
#endif
            break;
        case WNB_EVENT_DISCONNECTED:
#ifndef USING_STA_LED
            os_printf("wnb: connection lost!\r\n");
            if (param2 == 0) {
#ifndef IOA6_1_ON
                gpio_set_val(WNB_CONN_LED_IO, 1);
#ifdef  CONN_IO_REVERT
                gpio_set_val(WNB_CONN_LED_IO_REVERT, 0);
#endif
#else
                gpio_set_val(WNB_CONN_LED_IO, 0);
#endif
                gpio_set_val(WNB_SIGNAL_LED3, 1);
               // gpio_set_val(WNB_SIGNAL_LED2, 1);
                gpio_set_val(WNB_SIGNAL_LED1, 1);
            }
#else
            wnb_sta_led(param2);
#endif
            break;
        case WNB_EVENT_RSSI:
            // os_printf("wnb: rssi:%d, %d\r\n", (int8)param1, param2);
#ifndef USING_STA_LED
            if (param2 == 0) {
                gpio_set_val(WNB_SIGNAL_LED3, 1);
               // gpio_set_val(WNB_SIGNAL_LED2, 1);
#ifndef USING_ROLE_LED
                gpio_set_val(WNB_SIGNAL_LED1, 1);
#endif
            } else if (param2 == 1 || wnbcfg.role == WNB_STA_ROLE_REPEATER) {
                gpio_set_val(WNB_SIGNAL_LED3, ((int8)param1 >= -48) ? 0 : 1);
               // gpio_set_val(WNB_SIGNAL_LED2, ((int8)param1 >= -60) ? 0 : 1);
#ifndef USING_ROLE_LED
                gpio_set_val(WNB_SIGNAL_LED1, ((int8)param1 >= -72) ? 0 : 1);
#endif
            } else {
                gpio_set_val(WNB_SIGNAL_LED3, 0);
                //gpio_set_val(WNB_SIGNAL_LED2, 0);
#ifndef USING_ROLE_LED
                gpio_set_val(WNB_SIGNAL_LED1, 0);
#endif
            }
#endif
            break;
        case WNB_EVENT_EVM:
            // os_printf("wnb: evm:%d, %d\r\n", (int8)param1, param2);
#ifndef USING_STA_LED
            if (param2 == 1 || wnbcfg.role == WNB_STA_ROLE_REPEATER) {
                if (((int8)param1) >= -20) {
                    gpio_set_val(WNB_SIGNAL_LED3, 1);
                }
                if (((int8)param1) >= -15) {
                    gpio_set_val(WNB_SIGNAL_LED2, 1);
                }
            }
#endif
            break;
        default:
            break;
    }
}

static void led_blink(void)
{
#if LED_INIT_BLINK
    int32 i = 4;
    while(i-- > 0){
#ifdef USING_ROLE_LED
        gpio_set_val(WNB_ROLE_LED, (i&0x1));
#else
#ifndef IOA6_1_ON
        gpio_set_val(WNB_PAIR_LED, (i&0x1));
#else
        gpio_set_val(WNB_PAIR_LED, ((i+1)&0x1));
#endif
#endif
        gpio_set_val(WNB_SIGNAL_LED1, (i&0x1));
        //gpio_set_val(WNB_SIGNAL_LED2, (i&0x1));
        gpio_set_val(WNB_SIGNAL_LED3, (i&0x1));
        os_sleep_ms(500);
    }
#ifdef USING_ROLE_LED
    gpio_set_val(WNB_ROLE_LED, 1);
#else
#ifndef IOA6_1_ON
    gpio_set_val(WNB_PAIR_LED, 1);
#else
    gpio_set_val(WNB_PAIR_LED, 0);
#endif
#endif
    gpio_set_val(WNB_SIGNAL_LED1, 1);
   // gpio_set_val(WNB_SIGNAL_LED2, 1);
    gpio_set_val(WNB_SIGNAL_LED3, 1);
#endif
}

static void wnb_pair_waiting(void)
{
    static uint8 waiting_led = 0;
    if(pair_waitting){
#ifndef IOA6_1_ON
        gpio_set_val(WNB_PAIR_LED, waiting_led ? 0 : 1);
#else
        gpio_set_val(WNB_PAIR_LED, waiting_led ? 1 : 0);
#endif
        waiting_led = !waiting_led;
    }
}

static void wnb_gen_ssidpsk()
{
#ifdef WNB_MAC_SSID
    int32 i,g,l;
    os_sprintf(wnbcfg.ssid, "%02x%02x%02x%02x%02x%02x", MAC2STR(wnbcfg.addr));
    for(i=0;i<32;i++){
        g = i/6; l = i%6;
        wnbcfg.key[i] = (g&0x1) ? (wnbcfg.addr[l]) : (wnbcfg.addr[5-l]);
    }
    wnbcfg.key_set = 1;
    wnbcfg.encrypt = 1;
#endif
}

int main(void)
{
    struct lmac_init_param lparam;
    struct wnb_init_param param;
    int8   print_interval = 0;

    watchdog_init();
    syscfg_init(&sys_cfgs, sizeof(sys_cfgs));
    atcmd_init(ATCMD_UARTDEV);
    atcmd_register("AT+FWUPG", xmodem_fwupgrade_hdl, NULL);
    atcmd_register("AT+SKBDUMP", atcmd_skbdump_hdl, NULL);    
#ifdef SKB_POOL_ENABLE
    skb_txpool_init((uint8 *)SKB_POOL_ADDR, (uint32)SKB_POOL_SIZE);
#endif

#ifdef WNB_RSSID_34LED
    jtag_map_set(0);
#endif
#ifdef USING_ROLE_LED
    gpio_set_dir(WNB_ROLE_LED, GPIO_DIR_OUTPUT);
#else
    gpio_set_dir(WNB_PAIR_LED, GPIO_DIR_OUTPUT);
#endif
#ifdef CONN_IO_REVERT
    gpio_set_dir(WNB_CONN_LED_IO_REVERT, GPIO_DIR_OUTPUT);
#endif
    gpio_set_dir(WNB_SIGNAL_LED1, GPIO_DIR_OUTPUT);
    gpio_set_dir(WNB_SIGNAL_LED2, GPIO_DIR_INPUT);
    gpio_set_dir(WNB_SIGNAL_LED3, GPIO_DIR_OUTPUT);
    
#ifdef ETH_PHY_RESET
    gpio_set_dir(ETH_PHY_RESET_IO, GPIO_DIR_OUTPUT);
    gpio_set_val(ETH_PHY_RESET_IO, 1);
    os_sleep_ms(100);
    gpio_set_val(ETH_PHY_RESET_IO, 0);
    os_sleep_ms(100);
    gpio_set_val(ETH_PHY_RESET_IO, 1);
#endif
    
    led_blink();
    
#if !defined(IGONOR_ROLE_KEY) && !defined(RESET_REPLACE_ROLE_KEY)
    gpio_set_dir(WNB_ROLE_KEY, GPIO_DIR_INPUT);
    gpio_set_mode(WNB_ROLE_KEY, GPIO_PULL_DOWN, GPIO_PULL_LEVEL_100K);
#endif

#ifndef IGONOR_PAIR_KEY
    gpio_set_dir(WNB_PAIR_KEY, GPIO_DIR_INPUT);
    gpio_set_mode(WNB_PAIR_KEY, GPIO_PULL_UP, GPIO_PULL_LEVEL_100K);
    OS_TASK_INIT("pair_key", &wnb_pairkey_task, wnb_pair_key_task, 0, OS_TASK_PRIORITY_NORMAL, 512);
#endif

#if defined(USING_RESET_KEY) || defined(RESET_REPLACE_ROLE_KEY)
    gpio_set_dir(WNB_RESET_KEY, GPIO_DIR_INPUT);
    gpio_set_mode(WNB_RESET_KEY, GPIO_PULL_UP, GPIO_PULL_LEVEL_100K);
    OS_TASK_INIT("reset_key", &wnb_resetkey_task, wnb_reset_key_task, 0, OS_TASK_PRIORITY_NORMAL, 512);
#endif

    os_memset(&param, 0, sizeof(param));
    os_memset(&lparam, 0, sizeof(lparam));
    #ifdef MACBUS_USB
        lparam.uart0_sel = 1;
    #else
        lparam.uart0_sel = 0;
    #endif 
    lparam.rxbuf = WIFI_RX_BUFF_ADDR;
    lparam.rxbuf_size = WIFI_RX_BUFF_SIZE;
    lparam.tdma_buff = TDMA_BUFF_ADDR;
    lparam.tdma_buff_size = TDMA_BUFF_SIZE;
    param.ops = lmac_ah_init(&lparam);

    if (module_efuse_info.module_type == MODULE_TYPE_750M) {
        wnbcfg.chan_list[0] = 7640;
        wnbcfg.chan_list[1] = 7720;
        wnbcfg.chan_list[2] = 7800;
    } else if (module_efuse_info.module_type == MODULE_TYPE_810M) {
        wnbcfg.chan_list[0] = 8060;
        wnbcfg.chan_list[1] = 8140;
        wnbcfg.chan_cnt = 2;
    } else if (module_efuse_info.module_type == MODULE_TYPE_850M) {
        wnbcfg.chan_list[0] = 8450;
        wnbcfg.chan_list[1] = 8550;
        wnbcfg.chan_cnt = 2;
    } else if (module_efuse_info.module_type == MODULE_TYPE_860M) {
        wnbcfg.chan_list[0] = 8660;
        wnbcfg.chan_cnt = 1;
        wnbcfg.bss_bw   = 2;
    } else { // 915M case
#ifdef USE_915M_UPPER
        wnbcfg.chan_list[0] = 9180;
        wnbcfg.chan_list[1] = 9220;
        wnbcfg.chan_list[2] = 9260;
        wnbcfg.bss_bw   = 4;
#endif
    }

    wnb_gen_ssidpsk();
    wnb_load_cfg(&wnbcfg);
    ASSERT(wnbcfg.max_sta == WNB_STA_COUNT);
    wnb_load_factparam(&wnbcfg);
    sysctrl_efuse_mac_addr_calc(wnbcfg.addr);

#if !defined(IGONOR_ROLE_KEY) && !defined(RESET_REPLACE_ROLE_KEY)
    if((wnbcfg.role != WNB_STA_ROLE_REPEATER) && (wnbcfg.role != WNB_STA_ROLE_GPMEMB)){
        wnbcfg.role = gpio_get_val(WNB_ROLE_KEY) ? WNB_STA_ROLE_MASTER : WNB_STA_ROLE_SLAVE;
        OS_TASK_INIT("role_key", &wnb_rolekey_task, wnb_role_key_task, 0, OS_TASK_PRIORITY_NORMAL, 512);
    }
#endif

    param.cb  = wnb_event_hdl;
    param.cfg = &wnbcfg;
    param.frm_type = 0;
    param.if_type  = MAC_BUS_TYPE_EMAC;
    param.hook_cnt = 10;
    wnb_init(&param);
    syscfg_save_def();
    wnb_connect(1);

#ifdef UART_P2P_DEV
void uart_p2p_init(void);
    uart_p2p_init();
#ifndef  DUAL_UART_DBG_PRINT
    disable_print();
#endif
#endif

    atcmd_register("AT+SYSDBG", sys_atcmd_sysdbg_hdl, NULL);
#if ERRLOG_SIZE
    atcmd_register("AT+ERRLOG", sys_atcmd_errlog_hdl, NULL);
#endif
    
    sysheap_collect_init();
    while (1) {
        os_sleep(1);
        wnb_pair_waiting();
#ifdef USING_ROLE_LED
        wnb_role_led();
#endif
        if(print_interval++ >= 5){
            if (sysdbg_top) cpu_loading_print(0);
            if (sysdbg_heap) sysheap_status();
            if (sysdbg_irq) irq_status();
            if (sysdbg_wnb) wnb_statistic_print();
            lmac_transceive_statics(sysdbg_lmac);
            print_interval = 0;
        }
    }
}

