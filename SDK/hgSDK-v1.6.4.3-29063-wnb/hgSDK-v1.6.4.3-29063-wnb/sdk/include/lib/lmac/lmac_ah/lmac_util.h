#ifndef _LMAC_UTIL_H_
#define _LMAC_UTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define LMAC_EWMA_SCALE  16

#define MAX_SID_COUNT     32 // 8191 for 8K entries
#define MAX_AID_LEVELS    16 //  128 for 8K entries
#define MAX_LEN_MCS10    383//byte, 383Bytes(511 symbol) for agg, 
//#define MAX_SUBFRM_LEN_MCS10 511 //511bytes() for sub
#define IS_ZERO_ADDR(a)       (!((a)[0] | (a)[1] | (a)[2] | (a)[3] | (a)[4] | (a)[5]))
#define IS_MCAST_ADDR(a) (a[0]&0x1)
#define MAC_ADDR_EQU(a1,a2) ((a1[0]==a2[0])&&(a1[1]==a2[1])&&(a1[2]==a2[2])&&\
                             (a1[3]==a2[3])&&(a1[4]==a2[4])&&(a1[5]==a2[5]))                           
#define LMAC_SAFE_DIV(a, b) (((b) == 0) ? 0 : ((a) / (b)))
#define LMAC_DUP_BSSBW_CHECK()    ((ah_lmac.cfg.bss_bandwidth >= BSS_BW_4M) ? 1 : 0)
#define lmac_basic_nav_get()        LHW_GET_HF_TIMER3()
#define lmac_obss_nav_get()         LHW_GET_HF_TIMER4()
#define lmac_chan_switch_start(cs_us) do{\
                                      if(cs_us){\
                                          LHW_ABORT_HF_TIMER5();\
                                          LHW_CFG_HF_TIMER5(cs_us);\
                                          LHW_START_HF_TIMER5();\
                                        }\
                                        }while(0)
#define lmac_txop_start(txop_us)    do{\
                                    if(txop_us > 0){\
                                        LHW_ABORT_HF_TIMER6();\
                                        LHW_CLR_IRQ_PD_HT6();\
                                        /*gpio_set_val(dbg_io1, 1);*/\
                                        LHW_CFG_HF_TIMER6(txop_us);\
                                        LHW_START_HF_TIMER6();\
                                    }\
                                    }while(0)
#define lmac_txop_abort()         do{\
                                    LHW_ABORT_HF_TIMER6();\
                                    LHW_CLR_IRQ_PD_HT6();\
                                    }while(0)                                    
#define lmac_txop_remaining()     LHW_GET_HF_TIMER6()

//extern struct sid_mac sid_mac_map[MAX_SID_COUNT];
extern const uint8 bw_map_bss2sig[4];
extern const uint8 bw_map_sig2bss[4];
extern const int8 tx_pwr_tbl[TX_GAIN_NUM];
extern uint32 max_byte_table[11][4];

void lmac_delay_us(uint32 us);
uint16 lmac_get_seq_num(uint8 *buff);
uint32 calc_max_agg_bytes(uint8 bandwidth, uint8 mcs);
uint16 calc_symbol_len(uint32 apep_length, uint8 sig_bandwidth, uint8 mcs);

//commom functions used by tx & rx both


int32 lmac_hw_init(uint8 bss_bandwidth, uint8 lmac_dbg_mode);
void lmac_dsleep_init(void);

int32 lmac_wait_sync(uint32 init_us);
void lmac_wait_bgscan(uint32 init_us);
void lmac_cancle_tx_tmo(void);

uint8 ieee80211_is_data(uint16 frame_control);
uint8 ieee80211_is_data_qos(uint16 frame_control);
uint16 ieee80211_get_qos_ctl(uint8 *buff);
uint8 lmac_get_tid(uint8 *data);
uint8 lmac_get_hdr_len_pv0(uint8 *data);
void lmac_get_rx_addr(uint8 *a1, uint8 *frame);
void lmac_get_tx_addr(uint8 *a2, uint8 *frame);

uint8 lmac_get_hdr_len_pv1(uint8 *data);
uint8 *lmac_convert_sid2mac(struct short_id sidKey);
void sid_mac_map_init(struct sid_mac *base);
void lmac_quick_sort_sid(struct sid_mac *arr, int16 elements);

void lmac_set_basic_nav(uint32 nav_us);
void lmac_clr_basic_nav(void);
void lmac_set_obss_nav(uint32 nav_us);
void lmac_clr_obss_nav(void);

int8 lmac_std_calc(int8 *buff, int32 samples);
void *lmac_auto_rate_ctrl(struct list_head *head);

void hgics_print_hex(uint8 *buf, int32 len);
void hgics_print_char(uint8 *buf, int32 len);

int32 lmac_bss_bw(void);
uint64 hexstr2dec(uint8 *spos);
struct lmac_sta_info *lmac_alloc_sta(void);
void lmac_sta_put(struct lmac_sta_info *sta);
int32 lmac_sta_del(uint16 aid, uint8 *mac_addr);
struct lmac_sta_info *lmac_sta_get(uint16 aid, uint8 *mac_addr);
struct lmac_sta_info *lmac_sta_search(uint16 aid, uint8 *mac_addr);
#define lmac_sta_get_by_aid(aid)   lmac_sta_get(aid, 0) //todo:do not use aid
#define lmac_sta_get_by_addr(addr) lmac_sta_get(0xffff, addr)
#define lmac_sta_search_by_aid(aid)   lmac_sta_search(aid, 0)
#define lmac_sta_search_by_addr(addr) lmac_sta_search(0xffff, addr)
#define lmac_sta_del_by_aid(aid) lmac_sta_del(aid, 0)
#define lmac_sta_del_by_addr(addr) lmac_sta_del(0xffff, addr)

int32 get_icmp_seq_num(uint8 *buff);
uint16 partial_bssid_calc(uint8 *bssid);
uint16 partial_aid_ndp_calc(uint16 aid, uint8 *bssid);
uint16 partial_aid_calc(uint16 aid, uint8 *bssid);
void element_short_beacon_interval_hdl(uint8 *pos);
int16 calc_bitmap_offset(int16 seq_num, int16 start_sn);
void lmac_update_pv0_cfend_addr(void);
uint16 lmac_amp_atten_calc(uint16 val, double db);
int32 lmac_qa_results_valid_check(void);
uint32 lmac_next_beacon_calc(void);
uint32 lmac_next_dtim_calc(void);
int32 lmac_bkn_dly_calc(void);
void lmac_beacon_timer_start(uint32 tmo_us);
void lmac_beacon_timer_abort(void);
void lf_timer_start(uint32 x_us);
extern const int8  k_channel_rejection_thd[8][2];
int32 lmac_adc_dump(uint8 flag, uint8 *data, uint32 size);
int32 lmac_rx_dbg_info(void);
void lmac_tdma_start(void);
int32 lmac_is_icmp_ping(uint8 *data);
uint32 dsleep_dur_calc(uint64 tbtt);
void lmac_rx_gain_cfg(uint8 gain_idx);
void lmac_spec_cca_cfg(uint8 ch_type);
int8 lmac_get_avg_power(void);
int8 lmac_get_beacon_retry_limit(void);
int32 lmac_report_sleep_exit(uint8 wk_reason);

#ifdef __cplusplus
}
#endif

#endif




