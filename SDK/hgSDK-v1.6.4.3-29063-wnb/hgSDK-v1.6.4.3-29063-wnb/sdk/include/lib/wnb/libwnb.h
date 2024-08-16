#ifndef _HGSDK_WNB_H_
#define _HGSDK_WNB_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "lib/rbuffer.h"
#include "lib/lmac/hgic.h"
#include "lib/skb/skb_list.h"
#include "lib/lmac/lmac.h"
#include "lib/lmac/lmac_ah/ieee802_11_defs.h"
#include "lib/lmac/lmac_ah/ieee802_11_ah_defs.h"
#include "lib/wnb/libwnb.h"

#define WNB_SSID_LEN        (32)
#define COUNTRY_REGION_LEN  (4)
#define ETH_P_NETAT         (0x4848)
#define ETH_P_ATDATA        (0x4849)
#define ETH_P_RAWDATA       (0x4850)
#define ETH_P_M2UCAST       (0x4852)
#define ETH_P_WNBROAM       (0x4853)

/* WNB protocol defines */
#define IEEE80211_STYPE_WNB       0x00E0

#define WNB_STYPE_ASSOC           0x01
#define WNB_STYPE_PAIR            0x02
#define WNB_STYPE_DISASSOC        0x03
#define WNB_STYPE_CUSTOMER        0x04
#define WNB_STYPE_CONFIG          0x05
#define WNB_STYPE_OTA             0x06
#define WNB_STYPE_STA_HEARTHBEAT  0x07
#define WNB_STYPE_ROAMING         0x08
#define WNB_STYPE_PROBE_REQUEST   0x09
#define WNB_STYPE_PROBE_RESPONSE  0x0A
#define WNB_STYPE_USER_HEARTBEAT  0x0B
#define WNB_STYPE_USER_HEARTBEAT_RESP  0x0C
#define WNB_STYPE_USER_WAKEUP_DATA     0x0D
#define WNB_STYPE_USER_HEARTBEAT_LOST  0x0E
#define WNB_STYPE_BATTERY_SOC          0x0F
#define WNB_STYPE_MGTM_CONFIG          0x11

#define WNB_FOR_ME(h,wnb)     (os_memcmp((h)->addr1, (wnb)->cfg->addr, 6)==0)
#define RSSI_CHANGED(r1,r2)   ((r1)>(r2)?((r1)-(r2)>8):((r2)-(r1)>8))
#define EVM_CHANGED(r1,r2)    ((r1)>(r2)?((r1)-(r2)>3):((r2)-(r1)>3))
#define IS_BCAST_ADDR(a)      (((a)[0]&(a)[1]&(a)[2]&(a)[3]&(a)[4]&(a)[5]) == 0xff)
#define IS_MCAST_ADDR(a)      ((a)[0]&0x01)
#define IS_ZERO_ADDR(a)       (!((a)[0] | (a)[1] | (a)[2] | (a)[3] | (a)[4] | (a)[5]))
#define WNB_PROTO(fc)         (ieee80211_is_mgmt(fc) && ((fc) & 0x00f0) == IEEE80211_STYPE_WNB)
#define MAC_EQU(a1,a2)        (os_memcmp((a1), (a2), 6)==0)
//#define WNB_TIM_SET(wnb, aid) ((wnb)->ps_data.tim[(aid) / 8] |= (1 << ((aid) % 8)))
//#define WNB_TIM_CLR(wnb, aid) ((wnb)->ps_data.tim[(aid) / 8] &= ~(1 << ((aid) % 8)))
#define FROM_AP(wnb, hdr)      (MAC_EQU((wnb)->stas[0].sta->addr, (hdr)->addr2))
#define IS_MYAP(wnb, sta)     (((wnb)->cfg->role == WNB_STA_ROLE_SLAVE||(wnb)->cfg->role == WNB_STA_ROLE_REPEATER) && (sta) == &(wnb)->stas[0])
#define MY_SSID(wnb)          (((wnb)->cfg->role == WNB_STA_ROLE_REPEATER)?(wnb)->cfg->r_ssid:(wnb)->cfg->ssid)
#define MY_KEY(wnb)           (((wnb)->cfg->role == WNB_STA_ROLE_REPEATER)?(wnb)->cfg->r_key:(wnb)->cfg->key)
#define MY_ENC(wnb)           (((wnb)->cfg->role == WNB_STA_ROLE_REPEATER)?(wnb)->cfg->r_encrypt:(wnb)->cfg->encrypt)
#define IS_UPPER_AP(wnb, sta) (((wnb)->cfg->role == WNB_STA_ROLE_REPEATER) && (sta) == &(wnb)->stas[0])

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define BITS_PER_BYTE     (8)
#define BITS_TO_LONGS(nr) DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))

#define WNB_NETLOG_PORT (64320)

enum wnb_frm_type {
    WNB_FRM_TYPE_ETHER = 0,
    WNB_FRM_TYPE_HGIC,
    WNB_FRM_TYPE_RAW,
};

struct wnb_txq_param {
    uint8   aifsn                       : 4,
            acm                         : 1,
            aci                         : 2,
            reserved                    : 1;
    uint8   ecwmin                      : 4,
            ecwmax                      : 4;
    uint16  txop_limit;
};

struct wnb_mgmt {
    uint8  type: 7, resp: 1;
    uint8  cookie;
    uint16 center_freq; // current center frequence
};

struct wnb_mgmt_heartbeat {
    struct wnb_mgmt hdr;
    uint8  aid;
    uint8  role;
    union{
        struct {
            uint8 addr[6];
            uint32 tick;
        }group;
    }info;
};

struct wnb_mgmt_pair {
    struct wnb_mgmt hdr;
    uint8  role;
    uint8  encrypt;
    uint8  key[32];
    uint8  dev_id[6];
    uint8  ssid[WNB_SSID_LEN];
    uint8  aid;
};

struct wnb_mgmt_assoc {
    struct wnb_mgmt hdr;
    uint8 aid;
    uint8 dev_id[6];
    uint8 auth[WNB_SSID_LEN];
    uint8 ps_mode: 3, roaming:1, newkey:1, p2: 3;
    uint8 ssid_set:1, rev:7;
    uint8 roam_bssid[6];
    uint8 ssid[WNB_SSID_LEN];
};

struct wnb_mgmt_assoc_resp {
    struct wnb_mgmt hdr;
    uint8  aid;
    uint8  dev_id[6];
    uint8  assoc_status;
    uint16 bss_max_idle;
    uint8  wk_reason;
    uint8  repeater:1, newkey:1, rev:6;
    uint16 heartbeat_int;
    uint8  p1, p2/*, p3, p4*/; 
    uint8  key[32];
    uint16 repeater_level;
};

struct wnb_mgmt_config {
    struct wnb_mgmt hdr;
    uint16 type, len;
};

enum wnb_mgmt_configtype{
    WNB_MGMT_CONFIGTYPE_FREQINFO = 1,
    WNB_MGMT_CONFIGTYPE_RESET,
    WNB_MGMT_CONFIGTYPE_PSALIVE_CONFIG,
};

struct wnb_mgmt_probe_req {
    struct wnb_mgmt hdr;
    uint8 ssid[WNB_SSID_LEN];
};

struct wnb_mgmt_probe_resp {
    struct wnb_mgmt hdr;
    uint8 ssid[WNB_SSID_LEN];
    uint8 encrypt: 1, ver: 2;
    uint16 repeter;
    uint8 bss_bw;
    uint8 pri_chan;
    uint8 country_region[COUNTRY_REGION_LEN];
};

struct wnb_mgmt_disassoc {
    struct wnb_mgmt hdr;
    uint16 flags;
};

struct wnb_mgmt_roaming {
    struct wnb_mgmt hdr;
    uint8  request:1, pad:7;
};

struct wnb_bss_info {
    struct list_head list;
    uint8 ssid[WNB_SSID_LEN + 2];
    uint8 bssid[6];
    uint8 encrypt: 1, assoc: 1, disable:1, ann:1;
    int8  signal, rssi_tick;
    int32  rssi_add;
    uint16 freq, repeater;
    uint32 lifetime;
    atomic_t ref;
    uint8 country_region[COUNTRY_REGION_LEN];
    uint8 bss_bw;
};


#define WNB_DISASSOC_FLAGS_UNPAIR BIT(0)

/////////////////////////////////////////////////////////////////
/* WNB module defines */
#define WNB_EVTQ_SIZE (32)
#define WNB_NAT_COUNT (256)
#define WNB_CHAN_COUNT (16)
#define WNB_PAIR_DELAY (50)
#define WNB_HEART_INT  (500)
#define WNB_SCAN_DELAY (20)
#define WNB_BSS_MAX    (32)
#define WNB_PS_BC_SIZE (4)
#define WNB_MAX_IDLE_TU (30*1000) // units: 1.024ms 

#ifndef WNB_SCAN_DELAY
#define WNB_SCAN_DELAY (20)
#endif
#ifndef WNB_CONN_DELAY
#define WNB_CONN_DELAY (20)
#endif
#ifndef WNB_PS_DATA_SIZE
#define WNB_PS_DATA_SIZE (2)
#endif
#ifndef WNB_CON_CHAN_TRY
#define WNB_CON_CHAN_TRY (2)
#endif
#ifndef WNB_PAIR_TRY
#define WNB_PAIR_TRY   (4)
#endif
#ifndef WNB_SCAN_TRY
#define WNB_SCAN_TRY   (2)
#endif

#define RED_FONT    "\e[31m" /* ERROR */
#define YELLOW_FONT "\e[33m" /* WARNING */
#define FONT_END    "\e[0m"

#define wnb_dbg(fmt, ...) //os_printf(fmt, ##__VA_ARGS__)
#define wnb_err(fmt, ...) os_printf(RED_FONT fmt FONT_END, ##__VA_ARGS__)

typedef enum{
    WNB_FORWARD_TYPE_NONE,
    WNB_FORWARD_TYPE_2LOCAL,
    WNB_FORWARD_TYPE_2UPPER,
}wnb_forward_type;

typedef enum {
    WNB_EVENT_SEND_BEACON = 1,
    WNB_EVENT_HEARTBEAT,
    WNB_EVENT_PAIR_START,
    WNB_EVENT_PAIR_SUCCESS,
    WNB_EVENT_PAIR_FAIL,
    WNB_EVENT_PAIR_DONE,
    WNB_EVENT_CONNECT_START,
    WNB_EVENT_CONNECTED,
    WNB_EVENT_DISCONNECTED,
    WNB_EVENT_RX_DATA,
    WNB_EVENT_RSSI,
    WNB_EVENT_SCAN_START,
    WNB_EVENT_SCAN_DONE,
    WNB_EVENT_EVM,
    WNB_EVENT_DHCPC_REQ,
    WNB_EVENT_DHCPC_DONE,
    WNB_EVENT_CONNECT_FAIL,
    WNB_EVENT_MACBUS_IDLE,
} wnb_event;

typedef enum {
    WNB_STATE_IDLE,
    WNB_STATE_PAIR_START,     //1
    WNB_STATE_PAIRING,        //2
    WNB_STATE_PAIR_DONE,      //3
    WNB_STATE_CONNECT_START,  //4
    WNB_STATE_CONNECTING,     //5
    WNB_STATE_CONNECTED,      //6
    WNB_STATE_DISCONNECT,     //7
    WNB_STATE_SCAN_START,     //8
    WNB_STATE_SCANNING,       //9
    WNB_STATE_SCAN_DONE,      //10
    WNB_STATE_WAITING_AP,     //11
} wnb_state;

typedef enum {
    WNB_STA_ROLE_SLAVE,
    WNB_STA_ROLE_MASTER,
    WNB_STA_ROLE_GPMEMB,
    WNB_STA_ROLE_REPEATER,

    WNB_STA_ROLE_MAX,
} wnb_sta_role;

typedef enum {
    WNB_ASSOC_SUCCESS = 0,
    WNB_ASSOC_REFUSED = 1,
    WNB_ASSOC_DENIED_NO_MORE_STAS = 17,
    WNB_ASSOC_DENIED_INSUFFICIENT_BANDWIDTH = 33,
    WNB_ASSOC_REFUSED_AP_OUT_OF_MEMORY = 93,
    WNB_ASSOC_NO_AP = 0xff,
} wnb_assoc_status;

typedef void (*wnb_event_cb)(wnb_event evt, uint32 param1, uint32 param2);

/*saved into flash*/
struct wnb_sta_info {
    uint16 paired  : 1,
           encrypt : 1;
    uint8  addr[6];
    uint8  key[32];
};

struct wnb_psalive_config{

    uint16 wkdata_off;
    uint16 wkdata_save:1, rev:15;
    uint8  wkdata_mask[16];
    uint8  hbmask_off, hbmask_len;
    uint8  hbdata_mask[64];
};

struct wnb_sta_psalive {
    uint32 ipaddr;
    uint16 port;
    uint8  hb_period, hb_timeout;
    uint8 *heartbeat;
    uint8 *heartbeat_resp;
    uint8 *wakeup_data;
    int16  expired;
    uint16 heartbeat_len, heartbeat_resp_len, wakeup_data_len;
    uint8  heartbeat_lost, rev;
    struct wnb_psalive_config config;
};

/*needn't save*/
struct wnb_sta {
    void *wnb;
    struct wnb_sta_info *sta;
    uint8  id, aid;
    uint16  connected    : 1,
            ps           : 1,
            ps_poll      : 1,
            ps_mode      : 3,
            m2ucast      : 1,
            roam_out     : 2,
            roam_in      : 1,
            rnd_key      : 1;
    uint32 last_rx;
    uint32 last_tx;
    uint32 roam_jiff;
    int8   rssi, evm, wk_reason, rssi_montior;
    uint32 ipaddr;
    uint16 rxseq_head[4];
    uint64 rxseq_bit[4];
    uint16 tx_seqno[4];
    uint16 rx_seqno;
    struct skb_list psdata;
    struct skb_list ps_etherdata;
    struct wnb_sta_psalive psalive;
    uint8  roaming_bssid[6];
    uint8  roaming_notify;
    uint8  key[32];
    uint8  rx_cust_cookie, rssi_tick, rsv2, rsv3;
    int16  rssi_add;
};

struct wnb_route_entry {
    struct list_head list;
    struct wnb_sta *sta;
    uint32 lifetime;
    uint8  addr[6];
};

struct wnb_route_table {
    struct os_mutex  lock;
    struct list_head list[16];
    uint32           count;
};

#define WNB_WKUPHOST_REASONS (32)
struct wnb_config {
    uint8  role;
    uint8  bss_bw;
    uint8  encrypt: 1,
           forward: 1,
           key_set: 1,
           mkey_set: 1,
           join_group: 1,
           bssid_set: 1,
           mcast_filter: 1,
           reassoc_wkhost: 1;
    uint8  chan_cnt;
    uint16 freq_start, freq_end;
    uint16 chan_list[WNB_CHAN_COUNT];
    uint8  ssid[WNB_SSID_LEN];
    uint8  key[32];
    uint8  addr[6];
    uint8  max_sta;
    uint8  tx_mcs;
    uint8  acs_enable;
    uint8  acs_tmo;
    uint8  tx_bw;
    struct wnb_sta_info stas[WNB_STA_COUNT];
    uint8  mcast_key[32];
    uint8  tx_power: 5, pri_chan: 3;
    uint8  psconnect_period, psconnect_roundup;
    uint8  last_chan;
    uint16 wkio_mode: 1, psmode: 3, auto_chsw: 1, auto_role: 1, roaming: 1,
           dupfilter: 1, pa_pwrctrl_dis: 1, pair_autostop: 1, supper_pwr_set: 1, 
           r_encrypt: 1, not_auto_save: 1, rev4: 1, auto_pair:1, dhcpc_en:1;
    uint16 bss_max_idle;
    uint16 beacon_int, dtim_period;
    uint8  group_aid, agg_cnt, wkup_io, wkio_edge;
    uint16 aplost_time;
    int16  auto_sleep_time;
    uint16 heartbeat_int, ack_tmo;
    int8   roam_rssi_th;
    uint8  roam_int, max_txcnt;
    uint8  dcdc13: 2, wait_psmode: 2;
    uint8  r_ssid[WNB_SSID_LEN];
    uint8  r_key[32];
    uint8  dhcpc_hostname[32];
    uint8  mcast_txmcs, mcast_txbw, mcast_clearch, mcast_dupcnt;
    uint32 dhcpc_update_hbdata:1, wkhost_reasons_set:1, dual_ant:1,ant_auto_dis:1,
           ant_sel:1, mac_filter_en:1, roaming_samefreq:1, ap_hide:1, ap_psmode:1,
           dis_1v1_m2u:1, psconnect_dis:1, kick_assoc:1, quick_wk_appu:1, connect_onlypair:1,
           cust_isolation:1, mac_set:1, cca_for_ce:1, supper_pwr:3;
    uint8  wkhost_reasons[WNB_WKUPHOST_REASONS];
    uint16 repeater_level;
    uint8  macbus_idle;
    uint8  standby_channel;
    uint32 standby_period_ms;
    int32  uartbus_dev_baudrate;
    int8   rxg_offest;
    uint8  scan_dly, scan_retry;
    uint8  roam_rssi_diff;
    uint8  country_region[COUNTRY_REGION_LEN];
};

struct wnb_statistic {
    uint32 tot_tx, tot_rx, tot_fw, if_recv, if_write, rx_hook, tx_hook;
    uint32 tx_err, rx_err, if_err, fw_err, rx_drop, no_mem, tx_drop, filter;
};

struct wnb_rx_info {
    struct wnb_sta *sta;
    uint8 *data;
    uint16 len;
    uint16 fromDS: 1, resv: 15;
};

#define WNB_MAX_TIM_LEN (32)

struct wnb_ps_data {
    /* yes, this looks ugly, but guarantees that we can later use bitmap_empty :)
     * NB: don't touch this bitmap, use sta_info_{set,clear}_tim_bit */
    uint8 tim[WNB_MAX_TIM_LEN];
    struct skb_list bc_buf;
    uint8 num_sta_ps; /* number of stations in PS mode */
    int32 dtim_count;
    uint8 dtim_bc_mc;
};

struct wnb_init_param {
    uint8 if_type;
    uint8 frm_type;
    uint8 hook_cnt;
    struct lmac_ops *ops;
    struct wnb_config *cfg;
    wnb_event_cb cb;
};

struct wnb_mgmt_tx {
    uint8 *dest;
    uint16 len;
    uint16 flags;
    struct wnb_mgmt *mgmt;
    struct hgic_tx_info *txinfo;
};

struct wnb_udp_data{
    uint8 *dest;
    uint32 dest_ip, dest_port;
    uint32 src_ip, src_port;
    uint8 *data;
    uint32 len;
};

struct wireless_nb;
typedef int32(*wnb_pkt_tx_hdl)(struct wireless_nb *wnb, struct sk_buff *skb);
typedef int32(*wnb_pkt_rx_hdl)(struct wireless_nb *wnb, struct wnb_rx_info *rxinfo);
struct wnb_pkt_hook {
    const char *name;
    uint16 protocol;
    wnb_pkt_tx_hdl tx;
    wnb_pkt_rx_hdl rx;
};

typedef enum{
    WNB_ROAM_IDLE,
    WNB_ROAM_CHECK_RSSI,
    WNB_ROAM_REQUEST_ROAMING,
    WNB_ROAM_REQUEST_CANCLE,
    WNB_ROAM_DO_ROAMING,
    WNB_ROAM_ROAMING_BACK,
}WNB_ROAM_STATE;

/* WNB sub modules */
struct wnb_module_roam {
    WNB_ROAM_STATE state;
    uint8  request;
    uint8  check;
    int16  rssi_add;
    int8   rssi_avg;
    uint8  bssid[6];
    uint16 cur_freq;
    uint8  ssid[32];
    struct os_timer tmr;
    struct wnb_bss_info *newbss;
    void (*check_rssi)(struct wireless_nb *wnb, struct hgic_rx_info *rxinfo, uint8 *data, int32 len);
    int32(*forward_data)(struct wireless_nb *wnb, struct wnb_sta *sta, struct sk_buff *skb);
    int32(*cache_data)(struct wireless_nb *wnb, struct sk_buff *skb);
    void(*roam_in)(struct wireless_nb *wnb, struct wnb_sta *sta, uint8 notify, uint8 *roam_bssid);
    void(*proc_mgmt)(struct wireless_nb * wnb, uint8 * data, int32 len);
};

struct wnb_module_ota {
    void (*proc_data)(struct wireless_nb *wnb);
};

enum WNB_PSALIVE_ACTION{
    WNB_PSALIVE_ACTION_DO_HEARBEAT,
    WNB_PSALIVE_ACTION_KEEP_HEARTBEAT,
    WNB_PSALIVE_ACTION_SEND_CONFIG,
    WNB_PSALIVE_ACTION_UPDATE_HBDATA,
};
struct wnb_module_psalive {
    struct os_timer timer;
    void (*do_action)(struct wireless_nb *wnb, int32 action);
    void (*proc_mgmt)(struct wireless_nb *wnb, uint8 *data, int32 len);
    void (*start_sta)(struct wireless_nb *wnb, struct wnb_sta *sta, uint8 start);
};

struct wnb_module_netlog {
    uint8  addr[6], cookie[6];
    uint32 ip;
    uint32 time;
    uint16 port;
};

struct wnb_module_netat {
    uint8 dest[6];
};

struct wnb_module_dhcpc {
    uint32 transID, leasetime;
    uint8  svraddr[6], state;
    struct os_timer timer;
    struct {
        uint32 ipaddr, netmask, svrip, router, dns1, dns2;
    } result;
    void (*reset)(struct wireless_nb *wnb);
    void (*request_ip)(struct wireless_nb *wnb);
};

struct wnb_module_atcmd {
    struct{
        int32 count;
        struct hgic_tx_info txinfo;
    }txdata_arg;
};

struct wnb_module_drivercmd {
    void (*proc_cmd)(struct wireless_nb *wnb);
};

struct wnb_module_arp {
    void (*send_reply)(struct wireless_nb *wnb);
};

struct wnb_unpair_info {
    struct list_head list;
    uint8 addr[6];
};

struct wireless_nb {
    wnb_state           state;
    struct wnb_config  *cfg;
    struct wnb_sta     *stas;
    struct os_mutex     lock;
    struct os_semaphore sema;
    struct os_semaphore sm_sema;
    struct os_semaphore cfgsema;
    struct os_task      task;
    struct os_task      sm_task;
    struct os_timer     dly_run;
    struct os_timer     heart_tm;
    struct os_timer     beacon_tm;
    struct skb_list     datalist;
    struct skb_list     cstlist;
    struct skb_list     f2upper;
    struct skb_list     f2local;
    struct skb_list     cmd_list;
    struct skb_list     otalist;
    struct skb_list     up2host;
    struct skb_list     wkdata_list;
    struct skb_list     rxcache_list;

    struct list_head    bss_list;
    struct os_mutex     bss_lock;
    uint8               bss_cnt;
    uint8               waiting_ap;
    struct list_head    unpair_list;
    struct os_mutex     unpair_lock;
    uint32              unpair_cnt;

    RBUFFER_IDEF(evtq, uint8, WNB_EVTQ_SIZE);
    struct mac_bus        *bus;
    struct lmac_ops       *ops;
    struct wnb_route_table rt_table;
    struct wnb_route_table lp_table;
    struct wnb_pkt_hook  **hooks;
    wnb_event_cb           cb;

    struct wnb_ps_data    ps_data;
    struct dsleep_psdata *psalive_data;

    uint16              chan_list[WNB_CHAN_COUNT];
    uint8               chan_cnt, start_chan, chan_idx; 
    int8                chan_try;
    uint8               connect_bssid[6];

    uint8               assoc_result;
    uint8               hooks_cnt;
    uint8               sta_num;
    uint8               new_sta_idx;
    uint16              repeater_level;

    uint8               mgmt_cookie, last_cookie;
    uint16              bus_txcookie;
    uint16              bus_rxcookie;

    uint16              curr_freq;
    uint16              tx_seqno;
    uint16              ap_freq;

    uint8               frm_type;
    uint8               my_aid;
    uint8               heartbeat_lost;
    int8                rssi, evm, rsv;
    uint8               change_sequence, edca_update_cnt;

    uint8               conn_fail;
    uint16              conn_delay, pair_delay, scan_delay;

    uint16              ether_type;
    uint8               ps_hb_set: 1, ps_hbresp_set: 1, ps_wkdata_set: 1, ps_config_set:1, sleep_try: 3, detect_ap: 1;
    uint8               host_alive, wk_reason;

    /*flags*/
    uint32              need_save: 1,
                        ps: 1,
                        fix_freq: 1,
                        closed: 1,
                        testmode: 1,
                        mcast_copy: 1,
                        mcu_func: 1,
                        bg_scan: 1,
                        repeater_en:1,
                        bus_stop: 1,
                        acs_scanning: 1,
                        scan_done:1,
                        init_report:1,
                        manual_scan:1,
                        first_assoc:1;

    struct {
        uint8           role_changed:1, keygen:1, resp_rx:1, resp_tx:1;
        uint8           key[32];
        uint32          start_jif;
        struct          wnb_sta *sta;
    } pairing;
    struct {
        uint8  assoc_status;
        uint8  req_param: 1, req_param_dis: 1, req_param_cnt: 6;
    } report;

    uint32                 last_rx, last_tx, last_ps;
    uint32                 macbus_tick;
    struct wnb_statistic   statistic;
    
    struct wnb_module_roam      roaming;
    struct wnb_module_ota       ota;
    struct wnb_module_netlog    netlog;
    struct wnb_module_netat     netat;
    struct wnb_module_dhcpc     dhcpc;
    struct wnb_module_atcmd     atcmd;
    struct wnb_module_drivercmd drivercmd;
    struct wnb_module_arp       arp;
    struct wnb_module_psalive   psalive;

    atomic_t if_txwnd, txwnd_rp;
};

#define WNB_SMRUN(wnb)            do { if(os_sema_count(&wnb->sm_sema)==0) os_sema_up(&wnb->sm_sema); } while(0)
#define WNB_SMRUN_DELAY(wnb, tmo) do { os_timer_stop(&wnb->dly_run); os_timer_start(&wnb->dly_run, tmo); } while(0)
#define WNB_RUN(wnb) os_sema_up(&wnb->sema)
#define WNB_EVENT(wnb, evt) do{RB_SET(&wnb->evtq, (uint8)evt); WNB_RUN(wnb);}while(0)
#define WNB_CB(evt,p1,p2) if(wnb->cb){ wnb->cb(evt, (uint32)(p1), (uint32)(p2));}
#define WNB_IS_REQ(hdr)  (!((hdr)->resp)) /*wnb request packet*/
#define WNB_IS_RESP(hdr) ((hdr)->resp)     /*wnb response packet*/
#define WNB_NEXT_CH(wnb, ch)  (((ch)+1>=(wnb)->chan_cnt)?(0):((ch)+1))
#define WNB_VALID_BW(bw)  ((bw)==1||(bw)==2||(bw)==4||(bw)==8)
#define WNB_VALID_FREQ(f) ((f)>=7300&&(f)<=9300)
#define WNB_VALID_MCS(m)  (((m)>=0 && (m)<=7)||((m)==10))
#define WNB_PSDATA_SET2AP(wnb) (wnb->ps_hb_set && wnb->ps_hbresp_set && wnb->ps_wkdata_set && wnb->ps_config_set)

extern const uint8 wnb_bcast_addr[6];
extern const struct wnb_txq_param wnb_edca_params[5][4];
extern uint8 ieee80211_is_data_qos(uint16 frame_control);

int32 wnb_init(struct wnb_init_param *param);
void wnb_open(void);
void wnb_close(void);
void wnb_clear(void);

void wnb_role(struct wireless_nb *wnb, wnb_sta_role role);
int32 wnb_join_group(struct wireless_nb *wnb, uint8 *group_addr, uint8 aid);
int32 wnb_send_customer_data(struct hgic_tx_info *txinfo, uint8 *dest, uint8 *data, int32 len);
int32 wnb_send_ether_data(struct hgic_tx_info *txinfo, uint8 *data, int32 len);
void wnb_tx_data(struct wireless_nb *wnb, struct sk_buff *skb, wnb_forward_type forward);
int32 wnb_load_cfg(struct wnb_config *cfg);
int32 wnb_save_cfg(struct wnb_config *cfg, uint8 force);
void wnb_setup_chan_list(struct wireless_nb *wnb);
int32 wnb_freq_to_ch(struct wireless_nb *wnb, uint32 freq);
uint32 wnb_customer_id(void);
int32 wnb_dev_identify(struct  wireless_nb *wnb, uint8 *id);
int32 wnb_is_loopback_data(struct wireless_nb *wnb, struct wnb_rx_info *rxinfo);
int32 wnb_ether_filter(struct wireless_nb *wnb, uint8 *data, int32 len);
void wnb_set_edca_param(struct wireless_nb *wnb, struct wnb_txq_param *param);
int32 wnb_macbus_send_data(struct wireless_nb *wnb, uint8 *data, int32 len);
int32 wnb_rx_data(struct wireless_nb *wnb, uint8 *data, int32 len);
int32 wnb_active_sta_count(struct wireless_nb *wnb);


int32 wnb_send_mgmt(struct wireless_nb *wnb, struct wnb_mgmt_tx *tx);
uint8 wnb_cookie(struct wireless_nb *wnb);
uint16 wnb_seqno(struct wireless_nb *wnb, struct wnb_sta *sta, uint8 ac);
int32 wnb_host_notify(void *priv, uint8 event_id, uint8 *args, int32 len);
void wnb_role_changed(struct wireless_nb *wnb);
struct wnb_sta *wnb_get_sta(struct wireless_nb *wnb, uint8 *addr);
struct wnb_sta *wnb_new_sta(struct wireless_nb *wnb);
void wnb_del_sta(struct wireless_nb *wnb, struct wnb_sta *sta);
int32 wnb_get_qos_flags(struct sk_buff *skb, uint8 qos[2]);
void wnb_new_state(struct wireless_nb *wnb, uint8 new_state);
void wnb_statistic_print(void);
void wnb_load_factparam(struct wnb_config *wnbcfg);
void wnb_sta_init(struct wireless_nb *wnb);

void wnb_connect(int32 start);
void wnb_send_assoc_req(struct wireless_nb *wnb);
void wnb_send_disassoc(struct wireless_nb *wnb, uint8 *dest, uint16 flags);
void wnb_rx_assoc(struct wireless_nb *wnb, uint8 *data, int32 len);
void wnb_rx_disassoc(struct wireless_nb *wnb, uint8 *data, int32 len);
void wnb_send_beacon(struct wireless_nb *wnb);
void wnb_send_heartbeat(struct wireless_nb *wnb, uint8 *dest);
void wnb_rx_heartbeat(struct wireless_nb *wnb, uint8 *data, int32 len);
int32 wnb_rx_beacon(struct wireless_nb *wnb, struct hgic_rx_info *rxinfo, uint8 *data, int32 len);
void wnb_delay_next_conn(struct wireless_nb *wnb);
struct wnb_bss_info *wnb_find_suitable_ap(struct wireless_nb *wnb);

void wnb_pairing(int32 start);
void wnb_rx_pair(struct wireless_nb *wnb, uint8 *data, int len);
void wnb_pairing_hello(struct wireless_nb *wnb);
void wnb_rx_config(struct wireless_nb *wnb, uint8 *data, int32 len);
void wnb_pair_role_changed(struct wireless_nb *wnb);
void wnb_host_event_pair_done(struct wireless_nb *wnb);
void wnb_pairing_prepare(struct wireless_nb *wnb);

void wnb_route_init(struct wireless_nb *wnb);
void wnb_route_update(struct wireless_nb *wnb, uint8 *dest, struct wnb_sta *sta);
struct wnb_sta *wnb_route(struct wireless_nb *wnb, uint8 *dest);
int32 wnb_srcrt_check(struct wireless_nb *wnb, uint8 *src);
void wnb_lptable_update(struct wireless_nb *wnb, uint8 *dest, uint8 *src);
void wnb_route_del(struct wnb_route_table *rt, uint8 *addr);
void wnb_route_print(struct wnb_route_table *rt);

void wnb_scan(struct wireless_nb *wnb, int32 start);
int32 wnb_get_scan_result(struct wireless_nb *wnb, struct sk_buff *skb);
int32 wnb_rx_probe_reponse(struct wireless_nb *wnb, struct hgic_rx_info *rxinfo, uint8 *data, int32 len);
int32 wnb_rx_probe_request(struct wireless_nb *wnb, struct hgic_rx_info *rxinfo, uint8 *data, int32 len);
int32 wnb_tx_probe_request(struct wireless_nb *wnb, uint8 *ssid);
void wnb_bss_flush(struct wireless_nb *wnb);
int32 wnb_bss_info_update(struct wireless_nb *wnb, struct hgic_rx_info *rxinfo, uint8 *data, int32 len);
void wnb_bss_info_update_from_beacon(struct wireless_nb *wnb, struct hgic_rx_info *rxinfo, uint8 *data, int32 len);
int32 wnb_bss_info_update_from_bss_ann(struct wireless_nb *wnb, struct hgic_rx_info *rx_info, uint8 *bssid, struct vs_bss_announcement_ie *bss_ann);
struct wnb_bss_info *wnb_roam(struct wireless_nb *wnb, uint8 flags);
uint8 *wnb_get_element(uint8 *ie, int32 ie_len, uint8 id);
void wnb_bss_disable(struct wireless_nb *wnb, uint8 *bssid, uint8 disable);
void wnb_bss_expired(struct wireless_nb *wnb);
void wnb_bss_put(struct wireless_nb *wnb, struct wnb_bss_info *bss);

int32 wnb_rx(void *priv, struct hgic_rx_info *rxinfo, uint8 *data, int32 len);
int32 wnb_proc_data_rx_hooks(struct wireless_nb *wnb, struct wnb_rx_info *rxinfo);
int32 wnb_proc_data_tx_hooks(struct wireless_nb *wnb, struct sk_buff *skb);
uint8 wnb_check_sta_less_rssi(struct wireless_nb *wnb);

void wnb_sta_ps_end(struct wireless_nb *wnb, struct wnb_sta *sta);
void wnb_sta_ps_start(struct wireless_nb *wnb, struct wnb_sta *sta);
void wnb_free_psdata(struct wireless_nb *wnb, struct wnb_sta *sta);
void wnb_ps_init(struct wireless_nb *wnb);
void wnb_ps_mode(struct wireless_nb *wnb, uint32 start, uint32 time);
int32 wnb_get_sta_list(struct wireless_nb *wnb, struct sk_buff *skb);

int32 wnb_lptable_check(struct wireless_nb *wnb, uint8 *src);
void wnb_reset_beatheart(struct wireless_nb *wnb, int32 interval);

void wnb_disassoc_all(struct wireless_nb *wnb);
void wnb_request_parameter(struct wireless_nb *wnb);
int32 wnb_wakeup_sta(struct wireless_nb *wnb, uint8 *addr);
int8 wnb_get_sta_signal(struct wireless_nb *wnb, int32 index, uint8 *addr);
void wnb_send_nullfunc(struct wireless_nb *wnb, struct wnb_sta *sta, int32 ps);
void wnb_send_pspoll_response(struct wireless_nb *wnb);

struct wnb_sta *wnb_get_sta_ip(struct wireless_nb *wnb, uint32 ipaddr);

void wnb_ps_check_autosleep(struct wireless_nb *wnb);
void wnb_ps_ap_alive(struct wireless_nb *wnb);
void wnb_ps_wakeup_host(struct wireless_nb *wnb);
void wnb_ps_exit(struct wireless_nb *wnb, uint8 wk_reason);
void wnb_ps_check_wkreason(struct wireless_nb *wnb, uint8 wk_reason);

void wnb_opendev(struct wireless_nb *wnb);
void wnb_closedev(struct wireless_nb *wnb);
void wnb_init_lmac(struct wireless_nb *wnb);
int8 wnb_freq_type_match(uint8 ah_module_type, uint32 freq);
int32 wnb_rx_battery_soc(struct wireless_nb *wnb, uint8 *data, int32 len);
int32 mcu_battery_soc_request(struct wireless_nb *wnb);

uint16 wnb_checksum(uint16 initcksum, uint8 *ptr, int32 len);
void wnb_connect_start(struct wireless_nb *wnb);
void wnb_send_data_upper_ap(struct wireless_nb *wnb, uint8 *data, int32 len);
void wnb_check_ps_connect(struct wireless_nb *wnb);
void wnb_start_bgscan(struct wireless_nb *wnb);
void wnb_scan_channel(struct wireless_nb *wnb);
void wnb_ps_set_ssid(struct wireless_nb *wnb);
void wnb_ps_get_ssid(struct wireless_nb *wnb);
void wnb_random(uint8 *key, int32 len);
void wnb_auto_pair_check(struct wireless_nb *wnb, int start);
void wnb_scan_dump(struct wireless_nb *wnb);
int32 customer_driver_data_send(uint8 *data, uint32 len);
int32 wnb_config_send_data(struct wireless_nb *wnb, uint8 *dest, uint16 type, uint8 *data, int32 len);
void wnb_config_send(struct wireless_nb *wnb);
void wnb_rx_mgmt_config(struct wireless_nb *wnb, uint8 *data, int32 len);
int32 wnb_set_key(struct wireless_nb *wnb, uint8 cmd, uint8 aid, uint8 *key, uint8 swap);
struct wnb_unpair_info *wnb_unpair_sta_find(struct wireless_nb *wnb, uint8 *addr);
int32 wnb_unpair_sta(struct wireless_nb *wnb, uint8 *addr);
int32 wnb_register_hook(struct wnb_pkt_hook *hook);
int32 wnb_ssid_match(struct wireless_nb * wnb, uint8 *ssid, uint8 ssid_len);

void wnb_config_send_psaliveconfig(struct wireless_nb *wnb);
void wnb_check_request_params(struct wireless_nb *wnb);
void wnb_request_params_en(struct wireless_nb *wnb, int32 en);
void wnb_encrypt(uint8 *key, uint8 *in, uint8 *out, uint32 len, uint8 en);
int8 wnb_need_wakeup_host(struct wireless_nb *wnb, uint8 wk_reason);

void wnb_module_drivercmd_init(void);
void wnb_module_psalive_init(void);
void wnb_module_ota_init(void);
void wnb_module_dhcpc_init(void);
void wnb_module_netlog_init(void);
void wnb_module_arp_init(void);
void wnb_module_roam_init(void);
void wnb_module_netat_init(void);
void wnb_module_atcmd_init(void);
int ah_set_country_region(char *country_code, uint8 bss_bw, uint8 type);

static inline void wnb_roaming_check_rssi(struct wireless_nb *wnb, struct hgic_rx_info *rxinfo, uint8 *data, int32 len)
{
    if(wnb->cfg->roaming && wnb->roaming.check_rssi) wnb->roaming.check_rssi(wnb, rxinfo, data, len);
}
static inline void wnb_notify_sta_roam_in(struct wireless_nb *wnb, struct wnb_sta *sta, uint8 notify, uint8 *roam_bssid)
{
    if(wnb->roaming.roam_in) wnb->roaming.roam_in(wnb, sta, notify, roam_bssid);
}
static inline int32 wnb_roaming_forward(struct wireless_nb *wnb, struct wnb_sta *sta, struct sk_buff *skb)
{
    if(wnb->roaming.forward_data) 
        return wnb->roaming.forward_data(wnb, sta, skb);
    return 0;
}
static inline void wnb_rx_roaming_frame(struct wireless_nb * wnb, uint8 * data, int32 len)
{
    if(wnb->roaming.proc_mgmt) wnb->roaming.proc_mgmt(wnb, data, len);
}
static inline int32 wnb_roaming_cache_data(struct wireless_nb *wnb, struct sk_buff *skb)
{
    if(wnb->roaming.cache_data) 
        return wnb->roaming.cache_data(wnb, skb);
    return 0;
}
static inline void wnb_psalive_action(struct wireless_nb *wnb, int32 action)
{
    if(wnb->psalive.do_action) wnb->psalive.do_action(wnb, action);
}
static inline void wnb_psalive_start(struct wireless_nb *wnb, struct wnb_sta *sta, uint8 start)
{
    if(wnb->psalive.start_sta) wnb->psalive.start_sta(wnb, sta, start);
}
static inline void wnb_rx_psalive_frame(struct wireless_nb *wnb, uint8 *data, int32 len)
{
    if(wnb->psalive.proc_mgmt) wnb->psalive.proc_mgmt(wnb, data, len);
}
static inline void wnb_dhcpc_reset(struct wireless_nb *wnb)
{
    if(wnb->dhcpc.reset) wnb->dhcpc.reset(wnb);
}
static inline void wnb_dhcpc_request_ip(struct wireless_nb *wnb)
{
    if(wnb->dhcpc.request_ip) wnb->dhcpc.request_ip(wnb);
}
static inline void wnb_proc_driver_cmd(struct wireless_nb *wnb)
{
    if(wnb->drivercmd.proc_cmd) wnb->drivercmd.proc_cmd(wnb);
}
static inline void wnb_send_arp_reply(struct wireless_nb *wnb)
{
    if(wnb->arp.send_reply) wnb->arp.send_reply(wnb);
}
static inline void wnb_proc_ota_data(struct wireless_nb *wnb)
{
    if(wnb->ota.proc_data) wnb->ota.proc_data(wnb);
}

static inline char *WNB_ROLE_STR(int8 role)
{
    switch (role) {
        case WNB_STA_ROLE_MASTER: return "ap";
        case WNB_STA_ROLE_SLAVE:  return "sta";
        case WNB_STA_ROLE_GPMEMB: return "group";
        case WNB_STA_ROLE_REPEATER: return "apsta";
        default: return "none";
    }
}   

static inline void wnb_tim_set(struct wireless_nb *wnb, struct wnb_sta *sta)
{
    uint32 mask = 0;
    mask = disable_irq();
    if(sta && sta->ps) wnb->ps_data.tim[(sta->aid) / 8] |= 1 << ((sta->aid) % 8);
    enable_irq(mask);
}

static inline void wnb_tim_clr(struct wireless_nb *wnb, struct wnb_sta *sta)
{
    uint32 mask = 0;
    mask = disable_irq();
    if(sta) wnb->ps_data.tim[(sta->aid) / 8] &= ~1 << ((sta->aid) % 8);
    enable_irq(mask);
}

#ifdef __cplusplus
}
#endif

#endif

