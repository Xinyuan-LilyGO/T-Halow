#ifndef _HGIC_LMAC_H_
#define _HGIC_LMAC_H_
#include "list.h"
#include "lib/skb/skb.h"
#include "lib/lmac/hgic.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct lmac_ops  ah_ops;
extern struct lmac_priv ah_lmac;

//#define LMAC_DBG_PIN
#define dbg_io0 PA_30
#define dbg_io1 PA_31


#ifndef MAC_ADDR_SIZE
#define MAC_ADDR_SIZE 6
#endif
#ifndef STRUCT_PACKED
#define STRUCT_PACKED __attribute__ ((__packed__))
#endif

#define IEEE80211_AC_NUM                4
#define MAX_CHANS_NUM                   16
#define LMAC_FREQ_MIN                   700000 
#define TX_GAIN_NUM 6

//------------------------ dsleep -----------------------
#define DSLEEP_CFG_ADDR                 0x20000000
#define BKN_RETRY_LIMIT                 7
#define BKN_RETRY_HIGH_DTIM_LIMIT       31
#define BKN_RETRY_1M_MCS10_LIMIT        3
#define NOR_CS                          PA_0
#define NOR_CLK                         PA_1
#define NOR_MOSI                        PA_2
#define NOR_MISO                        PA_3

#define DSLEEP_STATE_IND                PB_0
#define DSLEEP_EXCEP_IND                PB_4

// #define PA_CTL                          PA_30
// #define DCDC_CTL                        PA_31//no use 

#define PA_ON                           0
#define PA_OFF                          1
#define DCDC_ON                         1
#define DCDC_OFF                        0

#define PSALIVE_HEARTBEAT_SIZE          256
#define PSALIVE_HEARTBEAT_RESP_SIZE     128
#define PSALIVE_WAKEUP_DATA_SIZE        128
#define SLEEP_USER_DATA_LEN             512

#define DSLEEP_CFG_MAGIC                (0xDDDDEEEE)
#define GPIOA_REG_LEN                   (0x0064/4 + 1)
#define GPIOB_REG_LEN                   (0x0064/4 + 1)
#define DBGPATH_REG_LEN                 (0x0024/4 + 1)
#define RFDIGCAL_REG_LEN                (0x0160/4 + 1)
#define RFSPI_REG_LEN                   (0x0028/4 + 1)
#define PHY_REG_LEN                     (0x0238/4 + 1)
#define LMAC_REG_LEN                    (0x0100/4 + 1)
#define PMU_REG_LEN                     (0x00bc/4 + 1)

#define DSLEEP_IO_DET                   BIT(0)
#define DSLEEP_UC_TIM_DET               BIT(1)
#define DSLEEP_BC_TIM_DET               BIT(2)
#define DSLEEP_WAKUP_FRAME_DET          BIT(3)
#define DSLEEP_BEACON_LOST              BIT(4)
#define DSLEEP_HEARTBEAT_LOST           BIT(5)

enum DSLEEP_MODE{
    DSLEEP_MODE_NONE,
    DSLEEP_MODE_STA_ALIVE,
    DSLEEP_MODE_AP_ALIVE,
    DSLEEP_MODE_UCASTWK,
    DSLEEP_MODE_APWK,
    DSLEEP_MODE_IOWK_ONLY = 6, //之前用了6，后续如果有新增先添加一个5
    
    DSLEEP_MODE_NUM,
};

enum DSLEEP_WAIT_MODE{
    DSLEEP_WAIT_MODE_PS_CONNECT,
    DSLEEP_WAIT_MODE_STANDBY,
    
    DSLEEP_WAIT_MODE_NUM,
};

enum DSLEEP_WK_REASON{
    DSLEEP_WK_REASON_TIMER = 1,
    DSLEEP_WK_REASON_TIM,           // 2
    DSLEEP_WK_REASON_BC_TIM,        // 3
    DSLEEP_WK_REASON_IO,            // 4
    DSLEEP_WK_REASON_BEACON_LOST,   // 5
    DSLEEP_WK_REASON_AP_ERROR,      // 6
    DSLEEP_WK_REASON_HB_TIMEOUT,    // 7
    DSLEEP_WK_REASON_WK_DATA,       // 8
    DSLEEP_WK_REASON_MCLR,          // 9
    DSLEEP_WK_REASON_LVD,           // 10
    DSLEEP_WK_REASON_PIR,           // 11
    DSLEEP_WK_REASON_APWK,          // 12
    DSLEEP_WK_REASON_PS_DISCONNECT, // 13
    DSLEEP_WK_REASON_STANDBY,       // 14
    
    DSLEEP_WK_REASON_STA_ERROR = 20,
    DSLEEP_WK_REASON_SLEEPED_STA_ERROR, // 21
    DSLEEP_WK_REASON_STA_DATA,          // 22
    DSLEEP_WK_REASON_AP_PAIR,           // 23
};

// use for wnb/lmac
struct dsleep_psdata{
    uint32              ip;
    uint16              port, period, hb_tmo, aplost_time, wkdata_off;
    uint8               hbdata_len, hbresp_len, wkdata_len, hbmask_off, hbmask_len;
    uint8               psmode:3, ap_err:1, wkio_mode:1, paired:1;
    uint8               conn_try;
    uint8               hb_data[PSALIVE_HEARTBEAT_SIZE];
    uint8               hb_resp[PSALIVE_HEARTBEAT_RESP_SIZE];
    uint8               wk_data[PSALIVE_WAKEUP_DATA_SIZE];
    uint8               arp_reply[64];
    uint8               wk_reason, channel;
    uint8               wk_io:7, wkio_edge:1;
    uint8               detect_io:7, detect_level:1;
    uint8               pa_ctrl:1, pa_ctrl_io:7;//todo
    uint8               vdd13_ctrl:2, ssid_set:1, gpiob_en:1, wkdata_save:1, io_level_wk:1, wait_psmode:2;
    uint8               ssid[32], psk[32], bssid[6];
    uint8               wkdata_mask[16];
    uint8               hbdata_mask[64];

    //system_sleep_config parameter
    uint32              user_gpioa_resv;
    uint32              user_gpiob_resv;
    uint32              sleep_us;
    uint32              boot_mode : 4, dsleep_en : 1;
    
    uint32              dhcpc_ip;
    uint64              rtc_local;
    uint64              last_timestamp_local;
    uint64              rtc_remote;
    uint64              last_timestamp_remote;
};

// use for lmac
struct dsleep_cfg{
    uint32                      magic;

    struct dsleep_psdata        psdata;

    //params
    uint32                      gpioa_regs[GPIOA_REG_LEN];
    uint32                      gpiob_regs[GPIOB_REG_LEN];
    uint32                      dbgpath_regs[DBGPATH_REG_LEN];
    uint32                      rfdigcal_regs[RFDIGCAL_REG_LEN];
    uint32                      rfspi_regs[RFSPI_REG_LEN];
    uint32                      phy_regs[PHY_REG_LEN];
    uint32                      lmac_regs[LMAC_REG_LEN];
    uint16                      wk_lo_tbl[4];
    uint16                      bss_lo_tbl[4];
        
    uint8                       rx_buff[256];
    
    uint8                       aifs;
    uint8                       cw_min;
    uint8                       cw_max;
    uint8                       pri_chan;
    
    uint16                      aid;
    uint8                       dtim_period;
    uint8                       bss_bw;

    uint32                      compressed_ssid;
    uint8                       mac_addr[MAC_ADDR_SIZE];
    uint32                      beacon_interval_us;
    uint32                      wk_freq;
    uint32                      bss_freq;
    uint32                      bss_max_idle_tu;
    uint32                      freq_list[MAX_CHANS_NUM];
    uint8                       freq_cnt;
    uint8                       freq_idx;
    uint8                       wk_lo_tbl_valid         : 1,
                                bss_lo_tbl_valid        : 1,
                                ant_dual                : 1,
                                ant_dft                 : 1,
                                uart0_sel               : 1,
                                bss_1m_ind              : 1;
    uint8                       ant_ctrl_pin1           : 7,
                                ant_ctrl_pin1_valid     : 1;
    uint8                       ant_ctrl_pin2           : 7,
                                ant_ctrl_pin2_valid     : 1;
    uint8                       tx_pwr_sel  : 3;
    int8                        bgrssi_bak;
    
    uint32                      sta_dsleep_us;
    uint32                      ap_probe_timeout;

    //above size = 2380, below is user defined funcs & datas
    void                       *enter_sleep_post_cb;
    void                       *keep_alive_post_cb;
    void                       *wake_up_post_cb;
    uint8                      usr_data[SLEEP_USER_DATA_LEN];
    int32                      sleep_us_max;
};

extern struct dsleep_cfg *dsleep_cfg_get(void);
extern int32 dsleep_cfg_init(struct dsleep_cfg *cfg);
extern int32 dsleep_enter(uint32 sleep_us, uint32 bootmode);
//------------------------ dsleep -----------------------

#define LMAC_ERR_FLAG_BO_FNS_STAT   (1u << 0)
#define LMAC_ERR_FLAG_TX_END_STAT   (1u << 1)
#define LMAC_ERR_FLAG_EDCA_PARAM    (1u << 2)
#define LMAC_ERR_FLAG_CHAN_SWITCH   (1u << 3)
#define LMAC_ERR_FLAG_RX_FRM_TYPE   (1u << 4)
#define LMAC_ERR_FLAG_RX_DATA_Q     (1u << 5)
#define LMAC_ERR_FLAG_DUP_DET_BW    (1u << 6)
#define LMAC_ERR_FLAG_RTS_TYPE      (1u << 7)
#define LMAC_ERR_FLAG_CTS_STA_NULL  (1u << 8)
#define LMAC_ERR_FLAG_RX_END_ERR    (1u << 9)
#define LMAC_ERR_FLAG_RX_FIFO_ERR   (1u << 10)
#define LMAC_ERR_FLAG_RX_FRM_ADDR   (1u << 11)
#define LMAC_ERR_FLAG_RX_END_TXSTAT  (1u << 12)
#define LMAC_ERR_FLAG_TX_PWR_CFG     (1u << 13)
#define LMAC_ERR_FLAG_TX_SUBFRM_ZERO (1u << 14)
#define LMAC_ERR_FLAG_RX_INFO_CLEAR  (1u << 15)
#define LMAC_ERR_FLAG_RX_PV_ERR      (1u << 16)
#define LMAC_ERR_FLAG_RX_LEN_ERR     (1u << 17)

#define NO_RESPONSE                     0
#define NDP_RESPONSE                    1
#define NORMAL_RESPONSE                 2
#define LONG_RESPONSE                   3

enum {
        AC_BE = 0,
        AC_BK = 1,
        AC_VI = 2,
        AC_VO = 3,
};
        
#define INVALID_MCS 0xff
#define INVALID_BW  0xff
#define INVALID_ANT 0xff
enum {
        MCS0 = 0,
        MCS1,
        MCS2,
        MCS3,
        MCS4,
        MCS5,
        MCS6,
        MCS7,
        MCS8,
        MCS9,
        MCS10
};

#define BSS_BW_1M           0
#define BSS_BW_2M           1
#define BSS_BW_4M           2
#define BSS_BW_8M           3

#define SIG_BW_1M           3
#define SIG_BW_2M           0
#define SIG_BW_4M           1
#define SIG_BW_8M           2

struct frame_format_80211{
    /*uint16 fc;
    uint16 duration;
    uint8 a1[MAC_ADDR_SIZE];
    uint8 a2[MAC_ADDR_SIZE];
    uint8 a3[MAC_ADDR_SIZE];
    uint16 seq_ctrl; //24B
    */
    //uint16 qos
    //uint16 htc
    //eth 
    uint8 src_mac[MAC_ADDR_SIZE];
    uint16 type;//0x0800  //32B
    //IP
    uint8  version_hdr_len;//0x45:ver4 20B
    uint8  service_filed;
    uint16 total_len;
    uint16 id;
    uint16 flags;
    uint8  ttl;
    uint8  protocol;//UDP=0x11 TCP=0x06 //42B
    uint16 hdr_check_sum;//44B
    uint32  src_ip;
    uint32  dst_ip; //52B
    //udp/tcp
    uint16 src_port;
    uint16 dst_port;//56B
}STRUCT_PACKED;

//ping
//lmac 34B len = 94; 64B len = 124
//fmac 64B len = 116
#define PING_PKT_LEN 116000 
struct lmac_txq_param {
    uint16 txop;
    uint16 cw_min;
    uint16 cw_max;
    uint8  aifs;
    uint8  acm;
};

struct vendor_specific_wakeup_element{
    uint16 sta_num;
    uint8 ra[MAC_ADDR_SIZE];
};

#define HGIC_ORG_ID_B0 0x00
#define HGIC_ORG_ID_B1 0x40
#define HGIC_ORG_ID_B2 0x01
enum vendor_specific_element_type {
    VS_STYPE_CHAN_LIST = 0,
    VS_STYPE_RATE_CTRL = 1,
    VS_STYPE_BSS_ANN = 2,
    VS_STYPE_OBSS_INFO = 3,
    VS_STYPE_BKN_INFO = 4,
};

//9.4.1.32 Organization Identifier field
//Organization Identifier: 3 Bytes(OUI and CID) or 5 bytes(OUI-36.)
struct vendor_specific_element{
    uint8   eid;
    uint8   len;
    uint8   org_id[3];
    uint16  aid;
    uint8   type;
}STRUCT_PACKED;

struct bkn_priv_info_element{
    uint8 t_dly[4];
    uint8 tbtt0;
    uint8 sta_map[4];
}STRUCT_PACKED;

struct lmac_init_param{
    uint32 rxbuf, rxbuf_size;    
    uint32 tdma_buff, tdma_buff_size;
    uint32 uart0_sel : 1;
};

struct lmac_ops {
    void *priv;
    uint16 headroom, tailroom;
    uint32 radio_on    :   1;//flags
    int32(*open)(struct lmac_ops *ops);
    int32(*close)(struct lmac_ops *ops);
    int32(*tx)(struct lmac_ops *ops, struct sk_buff *skb);
    int32(*test_tx)(struct lmac_ops *ops, struct sk_buff *skb);
    int32(*rx)(void *priv, struct hgic_rx_info *info, uint8 *data, int32 len);
    int32(*tx_status)(void *priv, struct sk_buff *skb);
    int32(*notify)(void *priv, uint8 event_id, uint8 *data, int32 len);
    int32(*set_freq_range)(struct lmac_ops *ops, uint16 freq_start, uint16 freq_end, uint8 chan_bw);
    int32(*set_freq)(struct lmac_ops *ops, uint32 center_freq);
    int32(*start_acs)(struct lmac_ops *ops, int32 enable, uint32 scan_ms);
    int32(*set_mac)(struct lmac_ops *ops, uint8 *mac_addr);
    int32(*add_sta)(struct lmac_ops *ops, uint16 aid, uint8 *addr);
    int32(*del_sta)(struct lmac_ops *ops, uint16 aid);
    int32(*set_key)(struct lmac_ops *ops, uint8 cmd, uint16 aid, uint8 *key, uint8 key_len);
    int32(*set_mcast_key)(struct lmac_ops *ops, uint8 cmd, uint8 *key, uint8 key_len);
    struct sk_buff *(*get_status)(struct lmac_ops *ops);
    int32(*set_primary_chan)(struct lmac_ops *ops, uint8 primary_chan);
    int32(*set_bgrssi)(struct lmac_ops *ops, int8 bgrssi);
    struct sk_buff *(*test_cmd)(struct lmac_ops *ops, struct sk_buff *skb);
    int32(*set_aid)(struct lmac_ops *ops, uint32 aid);
    int32(*set_txq_param)(struct lmac_ops *ops, uint32 txq, struct lmac_txq_param *param);
    int32(*set_chan_list)(struct lmac_ops *ops, uint16 *chan_list, uint16 count);
    int32(*sleep)(struct lmac_ops *ops, uint32 enable, uint32 sleep_us, uint32 bootmode);
    int32(*qa_status)(void *priv, uint8 pass);
    int32(*eth_scan_report)(struct lmac_ops *ops, uint8 pass);
    int32(*setcfg)(struct lmac_ops *ops, uint32 cmd, uint32 param1, uint32 param2);
    int32(*getcfg)(struct lmac_ops *ops, uint32 cmd, uint32 *param1, uint32 *param2);
    int32(*radio_onoff)(struct lmac_ops *ops, uint32 onoff);
};

struct lmac_ops *lmac_ah_init(struct lmac_init_param *param);
void lmac_tx_queue_state(void);
void lmac_sta_info_statics_print(void *p);
void lmac_transceive_statics(uint8 en);
void lmac_notify_channel_switch(uint32 freq);
void lmac_notify_testmode_state(uint8 start);
void lmac_doze_enter(void);
void lmac_doze_exit(void);
int32 ap_sleep_enter(void);
int32 lmac_psm_enter(struct lmac_ops *ops, uint32 enable, uint32 sleep_us, uint32 bootmode);
struct dsleep_psdata *lmac_dsleep_psdata(void);
void lmac_rf_reset(void);
void lmac_phy_reset(void);
void lmac_phy_soft_reset(void);
uint32 lmac_bitrate_est(void);

enum lmac_event {
    LMAC_EVENT_AUTO_CHANNEL_SELECT = 1,
    LMAC_EVENT_AUTO_RATE_CTRL,
    LMAC_EVENT_TX_BITRATE,
    LMAC_EVENT_BGRSSI_REPORT,
    LMAC_EVENT_CHAN_LIST_EVAL,
    LMAC_EVENT_CHIP_MONITOR,
    LMAC_EVENT_LMAC_STATICS,
    LMAC_EVENT_RESET,
    LMAC_EVENT_BSS_ANN,
    LMAC_EVENT_OBSS_EVAL,
    LMAC_EVENT_SCAN_PROBE,
    LMAC_EVENT_ANT_PROBE,
};

enum lmac_setcfg_cmd {
    LMAC_SETCFG_AGGCNT,
    LMAC_SETCFG_BSS_BW,
    LMAC_SETCFG_TX_BW,
    LMAC_SETCFG_TX_MCS,
    LMAC_SETCFG_RTS_TH,
    LMAC_SETCFG_TXPOWER,
    LMAC_SETCFG_BSS_MAX_IDLE,
    LMAC_SETCFG_TX_ORDERED,
    LMAC_SETCFG_AUTO_CHAN_SWITCH,//bss auto channel switch
    LMAC_SETCFG_PRI_CHAN,
    LMAC_SETCFG_RADIO_ONOFF,
    LMAC_SETCFG_PS_HEARBEAT,
    LMAC_SETCFG_PS_HEARBEAT_RESP,
    LMAC_SETCFG_PS_WAKEUP_DATA,
    LMAC_SETCFG_PS_HEARBEAT_PERIOD,
    LMAC_SETCFG_SSID,
    LMAC_SETCFG_WAKEUPIO_MODE,
    LMAC_SETCFG_PS_MODE,
    LMAC_SETCFG_SLEEP_APLOST_TIME,
    LMAC_SETCFG_SLEEP_WAKEIUP_IO,
    LMAC_SETCFG_SUPPER_PWR,
    LMAC_SETCFG_PA_PWR_CTRL,
    LMAC_SETCFG_STA_ROAMING,
    LMAC_SETCFG_HW_SCAN,
    LMAC_SETCFG_VDD13,
    LMAC_SETCFG_ACK_TIMEOUT_EXTRA,
    LMAC_SETCFG_TX_CNT_MAX,
    LMAC_SETCFG_SLEEP_GPIOA_RESV,
    LMAC_SETCFG_SLEEP_GPIOB_RESV,
    LMAC_SETCFG_SLEEP_GPIOC_RESV,
    LMAC_SETCFG_ENTER_SLEEP_CB,
    LMAC_SETCFG_KEEP_ALIVE_CB,
    LMAC_SETCFG_WAKE_UP_CB,
    LMAC_SETCFG_PSCONNECT_PERIOD,
    LMAC_SETCFG_MCAST_TXMCS,
    LMAC_SETCFG_MCAST_TXBW,
    LMAC_SETCFG_MCAST_TXPOWER,
    LMAC_SETCFG_MCAST_DUP_TXCNT,
    LMAC_SETCFG_MCAST_CLEAR_CHN,
    LMAC_SETCFG_ANT_DUAL_EN,
    LMAC_SETCFG_ANT_CTRL_PIN,
    LMAC_SETCFG_ANT_AUTO_EN,
    LMAC_SETCFG_ANT_SEL,
    LMAC_SETCFG_REASSOCIATION,
    LMAC_SETCFG_APSLEEP_RC,
    LMAC_SETCFG_MAX_TXCNT,
    LMAC_SETCFG_BSSID,
    LMAC_SETCFG_AP_PSMODE_EN,
    LMAC_SETCFG_WKSRC_DETECT,
    LMAC_SETCFG_RTC,
    LMAC_SETCFG_STANDBY,
    LMAC_SETCFG_WAIT_PSMODE,
    LMAC_SETCFG_CCA_FOR_CE,
    LMAC_SETCFG_RXG_OFFEST,
    LMAC_SETCFG_OBSS_EN,
    LMAC_SETCFG_OBSS_TH,
    LMAC_SETCFG_OBSS_PER,
    LMAC_SETCFG_OBSS_ANNONCE_INT,
    LMAC_SETCFG_SET_BEACON,
};
enum lmac_getcfg_cmd {
    LMAC_GETCFG_AGGCNT,
    LMAC_GETCFG_BSS_BW,
    LMAC_GETCFG_TX_BW,
    LMAC_GETCFG_TX_MCS,
    LMAC_GETCFG_RTS_TH,
    LMAC_GETCFG_TXPOWER,
    LMAC_GETCFG_BSS_MAX_IDLE,
    LMAC_GETCFG_TX_ORDERED,
    LMAC_GETCFG_LO_FREQ,
    LMAC_GETCFG_QA_BW,
    LMAC_GETCFG_QA_MCS,
    LMAC_GETCFG_QA_PER,
    //add for deepsleep
    LMAC_GETCFG_AID,
    LMAC_GETCFG_PRI_CHAN,
    LMAC_GETCFG_MAC_ADDR,
    LMAC_GETCFG_BSS_ID,
    LMAC_GETCFG_BKN_INTERVAL,
    LMAC_GETCFG_DTIM_PERIOD,
    LMAC_GETCFG_SLEEP_USER_DATA_ADDR,
    LMAC_GETCFG_SLEEP_USER_DATA_LEN,
    LMAC_GETCFG_ANT_SEL,
    LMAC_GETCFG_BSS_LOAD,
    LMAC_GETCFG_RTC,
    LMAC_GETCFG_SNR,
    LMAC_GETCFG_BGR,
    LMAC_GETCFG_ACS_RESULT,
};

#define lmac_set_aggcnt(ops, aggcnt)                ops->setcfg(ops, LMAC_SETCFG_AGGCNT, aggcnt, 0)
#define lmac_get_aggcnt(ops)                        ops->getcfg(ops, LMAC_GETCFG_AGGCNT, 0, 0)
#define lmac_set_bss_bw(ops, bss_bw)                ops->setcfg(ops, LMAC_SETCFG_BSS_BW, bss_bw, 0)
#define lmac_get_bss_bw(ops)                        ops->getcfg(ops, LMAC_GETCFG_BSS_BW, 0, 0)
#define lmac_set_tx_bw(ops, tx_bw)                  ops->setcfg(ops, LMAC_SETCFG_TX_BW, tx_bw, 0)
#define lmac_get_tx_bw(ops)                         ops->getcfg(ops, LMAC_GETCFG_TX_BW, 0, 0)
#define lmac_set_tx_mcs(ops, tx_mcs)                ops->setcfg(ops, LMAC_SETCFG_TX_MCS, tx_mcs, 0)
#define lmac_get_tx_mcs(ops)                        ops->getcfg(ops, LMAC_GETCFG_TX_MCS, 0, 0)
#define lmac_set_rts(ops, rts_th)                   ops->setcfg(ops, LMAC_SETCFG_RTS_TH, rts_th, 0)
#define lmac_get_rts(ops)                           ops->getcfg(ops, LMAC_GETCFG_RTS_TH, 0, 0)
#define lmac_set_txpower(ops, txpower)              ops->setcfg(ops, LMAC_SETCFG_TXPOWER, txpower, 0)
#define lmac_get_txpower(ops)                       ops->getcfg(ops, LMAC_GETCFG_TXPOWER, 0, 0)
#define lmac_set_bss_max_idle(ops, max_idle_tu)     ops->setcfg(ops, LMAC_SETCFG_BSS_MAX_IDLE, max_idle_tu, 0)
#define lmac_get_bss_max_idle(ops)                  ops->getcfg(ops, LMAC_GETCFG_BSS_MAX_IDLE, 0, 0)
#define lmac_set_strictly_ordered(ops, enable)      ops->setcfg(ops, LMAC_SETCFG_TX_ORDERED, enable, 0)
#define lmac_get_strictly_ordered(ops)              ops->getcfg(ops, LMAC_GETCFG_TX_ORDERED, 0, 0)
#define lmac_get_lo_freq(ops)                       ops->getcfg(ops, LMAC_GETCFG_LO_FREQ, 0, 0)
#define lmac_set_pri_chan(ops, prichan)             ops->setcfg(ops, LMAC_SETCFG_PRI_CHAN, prichan, 0)
#define lmac_get_pri_chan(ops)                      ops->getcfg(ops, LMAC_GETCFG_PRI_CHAN, 0, 0)
#define lmac_set_ssid(ops, ssid)                    ops->setcfg(ops, LMAC_SETCFG_SSID, (uint32)ssid, 32)
#define lmac_set_wkio_mode(ops, mode)               ops->setcfg(ops, LMAC_SETCFG_WAKEUPIO_MODE, mode, 0)
#define lmac_set_ps_mode(ops, mode)                 ops->setcfg(ops, LMAC_SETCFG_PS_MODE, mode, 0)
#define lmac_set_sleep_aplost_time(ops, time)       ops->setcfg(ops, LMAC_SETCFG_SLEEP_APLOST_TIME, time, 0)
#define lmac_set_auto_chan_switch(ops, disable)     ops->setcfg(ops, LMAC_SETCFG_AUTO_CHAN_SWITCH, disable, 0)
#define lmac_set_wakeup_io(ops, io, edge)           ops->setcfg(ops, LMAC_SETCFG_SLEEP_WAKEIUP_IO, io, edge)
#define lmac_set_supper_pwr(ops, off)               ops->setcfg(ops, LMAC_SETCFG_SUPPER_PWR, off, 0)
#define lmac_set_pa_pwr_ctrl(ops, en)               ops->setcfg(ops, LMAC_SETCFG_PA_PWR_CTRL, en, 0)
#define lmac_set_sta_roaming(ops, addr, en)         ops->setcfg(ops, LMAC_SETCFG_STA_ROAMING, (uint32)addr, en)
#define lmac_set_hw_scan(ops, probe, interval)      ops->setcfg(ops, LMAC_SETCFG_HW_SCAN, (uint32)probe, interval)
#define lmac_set_vdd13(ops, mode)                   ops->setcfg(ops, LMAC_SETCFG_VDD13, mode, 0)
#define lmac_set_ack_timeout_extra(ops, val)        ops->setcfg(ops, LMAC_SETCFG_ACK_TIMEOUT_EXTRA, val, 0)
#define lmac_set_retry_cnt(ops, frm_max, rts_max)   ops->setcfg(ops, LMAC_SETCFG_TX_CNT_MAX, frm_max, rts_max)
#define lmac_set_psconnect_period(ops, period)      ops->setcfg(ops, LMAC_SETCFG_PSCONNECT_PERIOD, period, 0)
#define lmac_set_mcast_txmcs(ops, txmcs)            ops->setcfg(ops, LMAC_SETCFG_MCAST_TXMCS, txmcs, 0)
#define lmac_set_mcast_txbw(ops, txbw)              ops->setcfg(ops, LMAC_SETCFG_MCAST_TXBW, txbw, 0)
#define lmac_set_mcast_txpower(ops, txpwr)          ops->setcfg(ops, LMAC_SETCFG_MCAST_TXPOWER, txpwr, 0)
#define lmac_set_mcast_dup_txcnt(ops, dupcnt)       ops->setcfg(ops, LMAC_SETCFG_MCAST_DUP_TXCNT, dupcnt, 0)
#define lmac_set_mcast_clear_chn(ops, en)           ops->setcfg(ops, LMAC_SETCFG_MCAST_CLEAR_CHN, en, 0)
#define lmac_set_ant_dual_en(ops, en)               ops->setcfg(ops, LMAC_SETCFG_ANT_DUAL_EN, en, 0)
#define lmac_set_ant_ctrl_pin(ops, pin)             ops->setcfg(ops, LMAC_SETCFG_ANT_CTRL_PIN, pin,0)
#define lmac_set_ant_auto_en(ops, en)               ops->setcfg(ops, LMAC_SETCFG_ANT_AUTO_EN, en, 0)
#define lmac_set_ant_sel(ops, sel)                  ops->setcfg(ops, LMAC_SETCFG_ANT_SEL, sel, 0)
#define lmac_get_ant_sel(ops)                       ops->getcfg(ops, LMAC_GETCFG_ANT_SEL, 0, 0)
#define lmac_set_max_txcnt(ops, txcnt)              ops->setcfg(ops, LMAC_SETCFG_MAX_TXCNT, txcnt, 0)
#define lmac_set_bssid(ops, bssid)                  ops->setcfg(ops, LMAC_SETCFG_BSSID, (uint32)bssid, 0)
#define lmac_set_ap_psmode_en(ops, en)              ops->setcfg(ops, LMAC_SETCFG_AP_PSMODE_EN, en, 0)
#define lmac_set_wksrc_detect(ops, io, level)       ops->setcfg(ops, LMAC_SETCFG_WKSRC_DETECT, io, level)
#define lmac_set_rtc(ops, rtc)                      ops->setcfg(ops, LMAC_SETCFG_RTC, rtc, 0)
#define lmac_get_rtc(ops)                           ops->getcfg(ops, LMAC_GETCFG_RTC, 0, 0)
#define lmac_get_sta_snr(ops, aid, snr)             ops->getcfg(ops, LMAC_GETCFG_SNR, (uint32 *)((uint32)aid), (uint32 *)snr)
#define lmac_set_standby(ops, chn, time)            ops->setcfg(ops, LMAC_SETCFG_STANDBY, chn, time)
#define lmac_set_wait_psmode(ops, mode)             ops->setcfg(ops, LMAC_SETCFG_WAIT_PSMODE, mode, 0)
#define lmac_set_cca_for_ce(ops, en)                ops->setcfg(ops, LMAC_SETCFG_CCA_FOR_CE, en, 0)
#define lmac_get_chan_bgr(ops, chan, bgr)           ops->getcfg(ops, LMAC_GETCFG_BGR, (uint32 *)((uint32)chan), (uint32 *)bgr)
#define lmac_set_rxg_offest(ops, offset)            ops->setcfg(ops, LMAC_SETCFG_RXG_OFFEST, offset, 0)

#define lmac_set_obss_en(ops, en)                   ops->setcfg(ops, LMAC_SETCFG_OBSS_EN, en, 0)
#define lmac_set_obss_th(ops, th)                   ops->setcfg(ops, LMAC_SETCFG_OBSS_TH, th, 0)
#define lmac_set_obss_per(ops, per)                 ops->setcfg(ops, LMAC_SETCFG_OBSS_PER, per, 0)
#define lmac_get_acs_result(ops, result)            ops->getcfg(ops, LMAC_GETCFG_ACS_RESULT, (uint32 *)result, 0)
#define lmac_set_beacon_start(ops, start)           ops->setcfg(ops, LMAC_SETCFG_SET_BEACON, (uint32)start, 0)

//reassociation notify lmac
#define lmac_set_reassociation(ops, aid, addr)      ops->setcfg(ops, LMAC_SETCFG_REASSOCIATION, aid, addr)
//get the bss load used for roaming
#define lmac_get_bss_load(ops, bss_load)            ops->getcfg(ops, LMAC_GETCFG_BSS_LOAD, bss_load, 0)

// * 用于配置用户保留的GPIO，在休眠过程中不会改变IO的状态，
// * @param[in]    resv    用户保留的GPIO，每个bit表示一个GPIO，范围GPIOA0~GPIOA31, GPIOB0~GPIOB18 
#define lmac_set_sleep_gpioa_resv(ops, resv)        ops->setcfg(ops, LMAC_SETCFG_SLEEP_GPIOA_RESV, resv, 0)
#define lmac_set_sleep_gpiob_resv(ops, resv)        ops->setcfg(ops, LMAC_SETCFG_SLEEP_GPIOB_RESV, resv, 0)
#define lmac_set_sleep_gpioc_resv(ops, resv)        ops->setcfg(ops, LMAC_SETCFG_SLEEP_GPIOC_RESV, resv, 0)

//获取用户区数据起始地址和长度
#define lmac_get_sleep_user_data_addr(ops)          ops->setcfg(ops, LMAC_GETCFG_SLEEP_USER_DATA_ADDR, 0, 0) 
#define lmac_get_sleep_user_data_len(ops)           ops->setcfg(ops, LMAC_GETCFG_SLEEP_USER_DATA_LEN, 0, 0)

//设置进入休眠和保活时用户函数callback func
#define lmac_set_enter_sleep_cb(ops, func)          ops->setcfg(ops, LMAC_SETCFG_ENTER_SLEEP_CB, func, 0)
#define lmac_set_keep_alive_cb(ops, func)           ops->setcfg(ops, LMAC_SETCFG_KEEP_ALIVE_CB, func, 0)
#define lmac_set_wake_up_cb(ops, func)              ops->setcfg(ops, LMAC_SETCFG_WAKE_UP_CB, func, 0)

#define lmac_radio_onoff(ops, onoff)                ({\
        int32 __v_ret_ = 0;\
        if(ops->radio_onoff) \
            __v_ret_ = ops->radio_onoff(ops, onoff);\
        __v_ret_;\
    })

// for qa
#define lmac_get_qa_bw(ops)                         ops->getcfg(ops, LMAC_GETCFG_QA_BW, 0, 0)
#define lmac_get_qa_mcs(ops)                        ops->getcfg(ops, LMAC_GETCFG_QA_MCS, 0, 0)
#define lmac_get_qa_per(ops)                        ops->getcfg(ops, LMAC_GETCFG_QA_PER, 0, 0)

#define lmac_set_ps_heartbeat(ops, ip, port)        ops->setcfg(ops, LMAC_SETCFG_PS_HEARBEAT, ip, port)
#define lmac_set_ps_heartbeat_resp(ops, data, size) ops->setcfg(ops, LMAC_SETCFG_PS_HEARBEAT_RESP, (uint32)data, size)
#define lmac_set_ps_wakeup_data(ops, data, size)    ops->setcfg(ops, LMAC_SETCFG_PS_WAKEUP_DATA, (uint32)data, size)
#define lmac_set_ps_heartbeat_period(ops, period)   ops->setcfg(ops, LMAC_SETCFG_PS_HEARBEAT_PERIOD, period, 0)

#define lmac_set_obss_annonce_interval(ops, period) ops->setcfg(ops, LMAC_SETCFG_OBSS_ANNONCE_INT, period, 0)
#ifdef __cplusplus
}
#endif

#endif
