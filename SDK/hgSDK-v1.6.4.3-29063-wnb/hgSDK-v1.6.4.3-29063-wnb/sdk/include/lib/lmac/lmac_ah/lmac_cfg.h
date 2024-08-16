
#ifndef _LMAC_CFG_H_
#define _LMAC_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <typesdef.h>
#include <osal/atomic.h>
#include <osal/msgqueue.h>
#include <osal/task.h>
#include "osal/timer.h"
#include "ieee802_11_ah_defs.h"
#include "lib/rbuffer.h"
#include "lib/lmac/lmac_ah/lmac_cipher.h"
#include "lib/skb/skb.h"
#include "lib/skb/skb_list.h"

#define LMAC_DEBUG_LEVEL 3
#if RFDIGICALI_HW_VER >= 2//mars
#define NEW_STATUS_RET
#endif

#ifdef LMAC_DEBUG_LEVEL 
#define lmac_debug(fmt,...) os_printf(fmt,##__VA_ARGS__)
#define lmac_debugX(level, fmt,...) if(LMAC_DEBUG_LEVEL >= level) os_printf(fmt, ##__VA_ARGS__)
#else
#define lmac_debug(fmt, ...) 
#define lmac_debugX(level, fmt, ...) 
#endif
#define lmac_print(fmt, ...) os_printf(fmt, ##__VA_ARGS__)
#define lmac_error(fmt, ...) do{\
                                os_printf("lmac error!!!"fmt,##__VA_ARGS__);\
                              }while(0) 

#define LMAC_EVENT_QUEUE_SIZE          64
#define LMAC_EVENT_Q_PUT(msg)          do{RB_SET(&ah_lmac.evtq, msg); os_sema_up(&ah_lmac.evt_sema);}while(0)


/**
*MIB: TBD...
**/

#define Tx2SyncDelay                    130
#define aSlotTime                       52
#define aSIFSTime                       160
#define aNDPTime                        240
//#define aMAXACKTime                     560//840@mcs0, 560@mcs1
#define aMAXACKDelay                    13 //13->161
#define aACKTimingAlign                 (aSIFSTime + aMAXACKDelay)
#define aCCATime                        0
#define aPHYRXSTARTDelay                0
#define aRxPHYStartDelay                0
#define aTxPLCPDelay                    0
#define aRxPLCPDelay                    0
#define aRxTxSwitchTime                 0
#define aTxRampOnTime                   0
#define aTxRampOffTime                  0
#define aTxRFDelay                      0
#define aRxRFDelay                      0
#define aAirPropagationTime             6
#define aMACProcessingDelay             0
#define aPreambleLength                 0
#define aRIFSTime                       0
#define aSymbolLength                   40
#define aSymbolLengthShortGI            36
#define aSTFOneLength                   0
#define aSTFTwoLength                   0
#define aLTFOneLength                   0
#define aLTFTwoLength                   0
#define aPLCPHeaderLength               0
#define aPLCPSigTwoLength               0
#define aPLCPServiceLength              0
#define aPLCPConvolutionalTailLength    0
#define aMPDUDurationFactor             0
#define aMPDUMaxLength                  0
#define aPSDUMaxLength                  0
#define aPSDUMaxLengthWithNoAggregation 0
#define aPPDUMaxTime                    0
#define aIUSTime                        0
#define aDTT2UTTTime                    0
#define aCWmin                          15 // for multi stations(4) 31
#define aCWmax                          31 //for multi stations(4) 63 fix CWmin = CWmax = 63 wenjie
#define aMaxCSIMatricesReportDelay      0
#define aMaxTODError                    0
#define aMaxTOAError                    0
#define aTxPmdTxStartRFDelay            0
#define aTxPmdTxStartRMS                0
#define aRxTxTurnaroundTime             0
#define aTxPHYDelay                     0
#define aRxPHYDelay                     0
#define aRxPHYStartDelay                0
#define aSignalExtension                0
#define aPHY1MSyms                      14
#define aPHYLONGSyms                    8
#define aPHYSHORTSyms                   6

#define ACKTimeout                     (aSIFSTime+aSlotTime+aRxPHYStartDelay)
#define FCS_SIZE                        4
#define HG_BOOTDL_FW_RESP               0xA012

enum ah_lmac_mode {
    LMAC_DISCONNECT_MODE = 0,
    LMAC_STATION_MODE,
    LMAC_AP_MODE,
    LMAC_RELAY_MODE,
};

struct edca_para {
    uint8   aifs[IEEE80211_AC_NUM];
    uint8   qsrc[IEEE80211_AC_NUM];
    uint8   qlrc[IEEE80211_AC_NUM];
    uint16  cwmin[IEEE80211_AC_NUM];
    uint16  cw[IEEE80211_AC_NUM];
    uint16  cwmax[IEEE80211_AC_NUM];
    uint32  txop_limit[IEEE80211_AC_NUM];
};

struct lmac_chan_info { 
    uint32  freq;//KHz
    uint8   pri_chan;
    int8    bgrssi_min;
    int8    bgrssi_max;
    int8    bgrssi_avg;
    int32   bgrssi_acc;
    int32   cnt;
    int32   rxsync_cnt;
    int32   noise_factor;
};
struct lmac_obss_info{
    int32 bss_freq;
    int8  pri_chan;
    int8  bss_bw;
    int8  bg_rssi;
    int8  rssi;
    int8  sta_num;
    int8  rsvd[3];
};

#ifdef NEW_STATUS_RET
struct lmac_fwstat_testmode_info {
    uint32 test_tx_start : 1, bss_freq : 24;
    int32 freq_dev;
    int32 chip_temp;
    int32 tx_frms;
    int32 tx_fail;
    int32 tx_mcs;
    int32 tx_sig_bw;
    int32 rx_pkts;
    int32 rx_firm;
    int32 rx_err;
    int32 rx_rssi;
    int32 agc;
    int32 rx_evm;
    uint8 chip_vcc[8];
};

struct lmac_fwstat_qainfo {
    uint8 dut_mac[MAC_ADDR_SIZE];
    uint16 svn_version;
    int8 result_per;
    int8 cfg_per;
    int8 rssi;
    int8 tssi;
    int8 rx_evm;
    int8 tx_evm;
    int8 rx_freq_dev;
    int8 tx_freq_dev;
    int8 rx_rssi_th;
    int8 tx_tssi_th;
    int8 rx_evm_th;
    int8 tx_evm_th;
    int8 rx_freq_dev_th;
    int8 tx_freq_dev_th;
};

struct lmac_fwstat_stainfo {
    uint8 addr[MAC_ADDR_SIZE];
    int32 tx_frms;
    int32 tx_frms_success;
    int32 tx_cnt;
    int32 tx_apep;
    int32 tx_cca;
    int32 tx_apep_success;
    int32 tx_apep_droped;
    int32 tx_frms_droped;
    int32 tx_symbols;
    int32 freq_offset;
    uint32 rx_cnt;
    uint32 rx_pkts;
    uint32 rx_bytes;
    uint32 rx_fcs_err;
    uint32 rx_symbols;

    uint8 tx_bw : 3, tx_mcs : 4;
    uint8 rx_bw : 4, rx_mcs : 4;
    int8 evm_avg, evm_std, rssi, tx_snr;
    uint16 aid, agc;
    uint16 bw_adv[4];
    uint64 tx_jiffies;
};

struct lmac_fwstat {
    uint8 mode;
    uint8 mac_address[MAC_ADDR_SIZE];
    uint16 aid;
    uint32 bss_freq_idx : 8, bss_freq : 24;
    uint32 pri1m_start : 16, pri2m_start : 16;
    uint32 pri1m_mid : 16, pri2m_mid : 16;
    uint32 sec2m_mid : 16, sec4m_mid : 16;
    uint32 pri1m_ed : 16, pri2m_ed : 16;
    uint32 sec2m_ed : 16, sec4m_ed : 16;
    uint8  tx_power_auto_adjust_en : 1, tx_pwr_adj : 5;
    uint8  chan_cnt;
    uint8  rx_duty_cycle;
    uint8  tx_pwr;
    int8  bg_rssi;
    int32 bgrssi_iqacc;
    int32 demod_dly_max;
    int32 sifs_dly_max;
    int32 resp_dly_max;
    int32 resp_sifs_to;
    int32 resp_ack_to;
    int32 frms_ack_to;
    int32 rx_ovf_cnt;
    int32 rx_nobuf_cnt;
    int32 rx_bus_max;
    int16 bgrssi_spur_thd;
    int16 bgrssi_spur_det;
    int16 bgrssi_spurs;
    int16 bgrssi_iqmax;
    int16 rx_dc_i;
    int16 rx_dc_q;
    uint32 lo_kick_cnt : 16, chan_switch_cnt : 16;
    int32 soft_rest;
#ifdef USING_TX_SQ
    uint32 lmac_txsq_count;
#else
    uint32 lmac_txbcq_count;
#endif
    uint32 lmac_txq_count;
    uint32 lmac_acq_count[IEEE80211_AC_NUM];
    uint32 lmac_txagg_count[IEEE80211_AC_NUM];
    uint32 lmac_statq_count;
    int32 lmac_rx_data_queue_count;
    int32 ac_irq_cnt;
    //int32 ac_dly_max;
    int32 tx_irq_rts;
    int32 bo_irq_cnt[IEEE80211_AC_NUM];
    int32 cts_tmo_cnt;
    int32 resp_tmo_cnt;
    int32 rx_irq_cnt;
    int32 tx_cnt;
    int32 tx_cts_bw_acc;
    int32 tx_cts_cnt;
    int32 tx_cts_evm_acc;
    int32 tx_frms;
    int32 tx_sq_empty;
    int32 agg_no_data;
    int32 agg_check_fail;
    int32 tx_apep;
    int32 tx_symbols;
    int32 tx_cca;
    int32 tx_fail;
    int32 tx_drop;
    int32 rx_cnt;
    int32 rx_cts_bw_acc;
    int32 rx_cts_cnt;
    int32 rx_cts_mcs_acc;
    int32 rx_pkts;
    int32 rx_bytes;
    int32 rx_symbols;
    int32 rx_phy_err;
    int32 rx_fcs_err;
    int32 phy_err_code;
    int32 tx_irq_bkn;

    uint8 lmac_doze : 1, cca_obsv_dur : 3;

    int32 sta_tx_syms;
    int32 sta_rx_syms;
    uint32 est_tx_bitrate;
    uint32 sta_num;
    uint8 fixed_tx_mcs;
    int skb_free_count;

    struct lmac_chan_info chan_list[MAX_CHANS_NUM];
    struct lmac_fwstat_testmode_info test_mode;
    struct lmac_fwstat_qainfo qa_stat;
    struct lmac_fwstat_stainfo sta_info[0];
};
#endif

#define LMAC_DBG_SEL_OBSS      BIT(0)
#define LMAC_DBG_SEL_RC_NEW    BIT(1)
#define LMAC_DBG_SEL_RC_OLD    BIT(2)
#define LMAC_DBG_SEL_HW_SCAN   BIT(3)
#define LMAC_DBG_SEL_TX_ERR    BIT(4)
#define LMAC_DBG_SEL_REORDER   BIT(5)
#define LMAC_DBG_SEL_BSS_LOAD  BIT(6)
#define LMAC_DBG_SEL_AP_SLEEP  BIT(7)
#define LMAC_DBG_SEL_DUAL_ANT  BIT(8)

struct lmac_cfg {//to be reorder...
    struct  edca_para  edca;//12*4 bytes
    struct  edca_para  bss_edca;
    struct  edca_para  obss_edca;
    struct  short_id   sid;//2 bytes
    enum    ah_lmac_mode lmac_mode;
    struct  lmac_chan_info chan_list[MAX_CHANS_NUM];
    struct  lmac_obss_info obss_info[MAX_CHANS_NUM];
    int8              obss_th;
    int8              obss_det; 
    uint8             mac_address[MAC_ADDR_SIZE];//TODO: dual mac mode
    uint8             bss_bandwidth;
    uint8             pri_chn, pri_chn_orig;
    uint8             crypto;
    uint8             bk_percent;
    uint8             be_percent;
    uint8             vi_percent;
    uint8             vo_percent;
    uint8             short_gi          : 1,
                      obss_switch_en    : 1,
                      obss_edca_en      : 1,
                      strictly_ordered  : 1,
                      tx_agg_auto       : 1,
                      rx_reorder        : 1,
                      dual_ant_opt      : 1,
                      dual_ant_sel      : 1;
    uint8             rc_new_version;
    uint8             rts_retry_max;
    uint8             frm_retry_max;
    uint8             mcast_dup_cnt:5,
                      mcast_rts_en :1,
                      mcast_reorder:2;
    uint8             tx_max_agg;
    uint8             lmac_dbg_mode;
    uint8             ewma_window;
    uint8             send_null_pkt;
    uint8             send_pspoll_pkt   : 1,
                      power_save_mode   : 1,
                      wake_all_stas     : 4,
                      ap_sleep_mode     : 1,
                      ap_wkio_det       : 1;
    uint8             ap_psmode_en      : 1;
    uint8             ap_sleep_wkio_sel : 7,
                      ap_sleep_wkio_edge: 1;
    int8              golden_txsnr_max;
    int8              golden_txsnr_min;
    int8              bg_rssi;
    int8              agc_adj_threshold_4;
    int8              agc_adj_threshold_5;
    int8              rx_gain_tab[6];
    int8              rx_conversion_gain;
    int8              bgrssi_margin;
    int8              bgrssi_max;
    int8              new_cs_cnt;  
    int16             bgrssi_spur_thd;
    uint16            rts_threshold;
    uint16            aid;
    uint32            adc_dump          : 8,
                      adc_dump_ready    : 1,
                      short_frm_th      : 16;
    uint32            ccmp_support      : 1,
                      partial_aid       : 6,
                      partial_aid_ndp   : 9,
                      tx_power_auto_adjust_en :1,
                      rts_dup_en        : 1,
                      cts_dup_en        : 1,
                      rc_new            : 1;
    uint32            bss_freq          : 24,
                      bss_freq_idx      : 8;
    uint32            cur_freq          : 24,
                      cur_freq_idx      : 8;
    uint32            lock_freq         : 24;//used for connect with sleep ap
    uint32            new_cs_freq;
    uint32            new_cs_num        : 8,
                      bss_op_class      : 8, 
                      bss_1m_ind        : 1,
                      bss_1m_lo_offset  : 15;//for 1m bss bug fix
    uint32            tx_bpn;
    uint32            rx_bpn;
    uint32            freq_start;//KHz
    uint32            freq_stop;//KHz
    uint32            scan_time_per_chn;//ms
    uint32            pcf_enable        : 1,//to be config by fw
                      tx_max_syms       : 9,
                      cca_adj_en        : 1,
                      agc_adj_en        : 1,
                      bgrssi_avg_pks    : 8,
                      gain_idx          : 8;
    uint32            cfp_period        : 8,
                      cfp_percent       : 8;//0~100
    uint32            cfp_time_remain;
    uint32            tx_pwr_adj        : 5,
                      tx_pwr_idx        : 5,
                      tx_pwr_super_en   : 2,
                      tx_pwr_super_th   : 8,
                      tx_rate_fixed     : 1;
    uint32            est_tx_bitrate;
    uint32            status_skb_len;
    uint32            chan_cnt          : 8,
                      chan_survey       : 8,
                      chan_update_pkts  : 16;
    uint32            chan_list_bgrssi_scan : 1,
                      auto_chan_switch  : 1,
                      auto_chan_switch_th : 8,
                      auto_noise_report : 1,
                      chan_tbl_update   : 1;
                      //soft_reset        : 1;
    uint32            dual_nav_en       : 1,
                      dual_nav_diff     : 6,
                      obss_sd_en        : 1,
                      obss_sd_diff      : 6,
                      tx_bw_dynamic     : 1;
    uint32            txop_enable       : 1,
                      txop_ac           : 3,
                      txop_bw           : 2,
                      txop_mcs          : 4;//tbc:fixed
    uint32            txop_us;
    uint32            lmac_wd_period;//ms
    uint32            lmac_cm_period;
    uint32            lmac_nh_period;
    uint32            lmac_tk_period;
    uint32            lmac_print_period;
    uint32            bss_ann_period;
    uint32            obss_eval_period;
    uint32            hw_scan_probe_period;
    uint32            hw_scan_probe_timeout;
    uint32            chan_tbl_update_period;
    uint32            qa_timeout_check_period;
    uint32            ant_probe_interval;
    uint32            dbg_sel;
    uint16            bw_probe;
    uint16            bw_window;
    uint32            ap_active_tick;
    uint32            ap_active_tmo :16;
    uint32            sta_active_tick;
    uint16            ack_timeout_extra;
    uint8             psconnect_period;
    uint8             vdd13_ctrl : 2, dgain_fixed:1, cca_for_ce : 1;
    int8              rxg_offset;
    uint8             obss_per;
} ;
struct lmac_param {
    uint64  next_dtim_timestamp;//for sta
    uint32  change_sequence     : 8,
            bkn_ies_len         : 16;
    uint8  bkn_ies[256];
    struct ieee80211_s1g_capabilities cap;//15
    struct ieee80211_edca_param_set_ie edca_set;//18
    struct ieee80211_edca_param_set_ie obss_edca_set;//18

    uint8   bssid[MAC_ADDR_SIZE];//6
    uint8   ssid[32 + 4];
    uint32  compressed_ssid;
    uint8   tim_len;
    uint8   dtim_count;
    uint8   dtim_period;
    uint8   aid0;
    
    
    uint8   tim_bitmap[252];//Bitmap Control & Partial Virtual Bitmap
    uint16  compat_info;
    uint16  short_beacon_interval_tu;
    uint32  short_beacon_interval_us;// 1TU = 1024us
    uint32  beacon_cnt;
    uint32  timestamp_lo;
    uint32  timestamp_hi;
    uint32  bss_color:3,
            partial_bssid : 9;//reservd bits
    uint32  ndp_us : 16,
            pv0_wpcts_us : 16;
    uint32  pv0_wpack_us : 16,
            pv0_wpba_us  : 16;
    uint32  pv0_cfend_us : 16,
            pv0_s1gbkn_us: 16;
    uint32  bss_max_idle_tu;
    
    //chip monitor params
    int32   chip_temp;
    float   chip_vcc;
    uint32  lmac_doze   : 1,
            vref_dft    : 3,
            vref_val    : 3;
    uint16  tx_dgain_dft[TX_GAIN_NUM];
    int8    tx_pwr_dft;
    uint8   xo_cs_dft;
    uint8   rx_duty_cycle;
    uint8   tx_duty_cycle;
    uint8   mkey_len;
    uint8   mkey[32];
    float   chip_vdd13b;
    float   chip_vdd13c;
};

//golden broadcast info to notify dut
struct lmac_qa_operation{//max 8bytes
    uint8 channel_width;
    uint8 operating_class;
    uint8 pri_channel_number;
    uint8 channel_center_freq;
    uint8 uni_test : 1,
          freq_frag : 4;
    uint8 reserved[3];
};
struct lmac_qa_info {
    int8        cnt;
    int8        pass_cnt;
    uint8       start       : 1,
                qa_fh       : 1,
                uni_test    : 1,
                dut_to_cnt  : 5;
    uint8       rsvd;
    //golden cfg
     struct{
         int8   freq[4];
         int8   bw;
         int8   mcs;
         int8   per;
         int8   scan_att;
     }golden_cfg;
    //rx thd
    struct{
        int8    rssi_th;
        int8    evm_th;
        int8    freq_dev_th;
        int8    rsvd_th[5];
    }rx_thd;
    //tx thd
    struct{
        int8    tssi_th;
        int8    evm_th;
        int8    freq_dev_th;
        int8    rsvd_th[5];
    }tx_thd;
    //rx values
    struct{
        int8    rssi;
        int8    evm;
        int8    freq_dev;
        int8    agc;
        int8    bgrssi;
        uint16  svn_version;//rsvd
        int8    rsvd;
    }rx_info;
    //tx values
    struct{
        int8    tssi;
        int8    evm;
        int8    freq_dev;
        int8    agc;
        int8    rsvd[4];
    }tx_info;
    //results
    struct{
        int8    per;
        uint8   dut_pass : 1,
                eht_pass : 1;
        uint8   rx_flags;//1: pass 0:fail
        uint8   tx_flags;//1: pass 0:fail
        uint8   dut_mac[MAC_ADDR_SIZE];
        uint8   vcc_meas    : 6;
        int8    temperature;
    }results;
};

struct lmac_qc_info {
    uint8 fail;
    struct {
        uint8  done;
        uint8  qc_fake_mcs[3];
        uint8  idx;
        uint8  connected;
        int8   cnt_down;
        uint32 pkt_cnt;
    } golden_cfg;
    struct {
        uint8 retry;
        uint8 connected;
    } dut_cfg;
    struct {
        int8 evm_thd;
        int8 rssi_low_thd;
        int8 rssi_high_thd;
        int8 retry_thd;
        int16 freq_thd;
        int16 pkt_thd;
    } test_thd;
    struct {
        uint16 rx_dc_i;
        uint16 rx_dc_q;
        int32  chip_temp;
        float  chip_vcc;
		float  chip_vdd13b;
        float  chip_vdd13c;
        int8   evm_avg;
        int8   evm_std;
        int16  rssi;
        int32  freq_offset;
        uint32 mcs;
    } test_result;
};

enum lmac_tx_state {
    TX_STATE_IDLE   = 0,
    TX_STATE_FRM,   //1
    TX_STATE_ACK,   //2
    TX_STATE_BA,    //3
    TX_STATE_RTS,   //4
    TX_STATE_CTS,   //5
    TX_STATE_CFPOLL,//6
    TX_STATE_CFEND, //7
    TX_STATE_BEACON, //8
    TX_STATE_NULL, //9
    TX_STATE_PSPOLL, //10
};

enum lmac_rx_state {
    RX_STATE_IDLE     = 0,
    RX_STATE_WAIT_RESP,
    RX_STATE_WAIT_CTS,
    RX_STATE_WAIT_CFACK,
    RX_STATE_WAIT_BGSCAN,
    RX_STATE_WAIT_NULLACK,
    RX_STATE_WAIT_PSPOLLACK,
};

enum lmac_ps_state {
    PS_STATE_IDLE   = 0,
    PS_STATE_WAIT_BEACON,
    PS_STATE_WAIT_SLEEP,
    PS_STATE_SLEEPED,
};

struct lmac_at_data{
    int32  tx_frms;
    int32  tx_fail;
    int32  tx_mcs;
    int32  tx_sig_bw;
    
    int32  rx_pkts;
    int32  rx_err;
    int32  rx_rssi;
    int32  rx_evm;
    int32  freq_dev;
    int32  agc;
    uint32 ft_att : 6;
};

struct lmac_monitor {
    //background info
    int8   bg_rssi_min;
    int8   bg_rssi_avg;
    int8   bg_rssi_max;
    uint8  mcast_bw :4,
           mcast_mcs:4;
    uint8  tx_pwr;
    int16  rx_dc_i;
    int16  rx_dc_q;
    //irq info
    int32  ac_irq_cnt;
    int32  bo_irq_cnt[IEEE80211_AC_NUM];
    int32  tx_irq_rts;
    int32  tx_irq_bkn;
    int32  resp_tmo_cnt;
    int32  cts_tmo_cnt;
    int32  rx_irq_cnt;
    //tx info
    int32  tx_cnt;
    int32  tx_frms;
    int32  tx_apep;
    int32  tx_symbols;
    int32  tx_cca;
    int32  tx_success;
    int32  tx_fail;
    int32  tx_drop;
    int32  tx_delay_max;
    int32  tx_delay_acc;
    //rx info
    int32  freq_dev;
    int32  rx_cnt;
    int32  rx_pkts;
    int32  rx_bytes;
    int32  rx_symbols;
    int32  rx_rssi;
    int32  rx_evm;
    int32  agc_info;
    int32  rx_phy_err;
    int32  phy_err_code;
    int32  rx_fcs_err;
    int32  rx_ovf_cnt;
    int32  rx_nobuf_cnt;
    int32  rx_bus_max;
    int32 demod_dly_max;
    int32 sifs_dly_max;
    int32 resp_dly_max;

    int32  tx_sq_empty;
    int32  agg_no_data;
    int32  agg_check_fail;

    int32 resp_sifs_to;
    int32 resp_ack_to;
    int32 frms_ack_to;
    int32 soft_rest;

    int32 tx_cts_evm_acc;
    int32 tx_cts_bw_acc;
    int32 tx_cts_cnt;
    
    int32 rx_cts_mcs_acc;
    int32 rx_cts_bw_acc;
    int32 rx_cts_cnt;

    int32 bgrssi_iqacc;
    int16 bgrssi_iqmax;
    int16 bgrssi_spurs;
    int16 bgrssi_spur_det;
    int16 no_print_buff;//allign
    int32 dtim_dly[3];
    uint32 rx_len_err;
    uint32 rx_pm_cnt;
    uint32 rx_drop_cnt;
    uint16 rssi0_cnt;
    uint16 rssin128_cnt;

    uint16 rts_cnt;
    uint16 rts_no_sta;
    uint16 rts_dur_0;
    uint16 rts_no_resp;
    uint16 cts_cnt;

    int64  tx_bkf_acc;
    int64  tx_rate_acc;
     
    // Below this variable is the long-term storage area
    int32 non_clear_area;
    uint32 stat_tick;
    int32 rx_mic_err;
    int32 rx_key_err;
    uint32 rx_buff_free1;
    uint32 rx_buff_free2;
    uint32 rx_buff_free3;
    int16  cali_dc_i;
    int16  cali_dc_q;
    int8  dut_bios_id;
    int8  tx_per;
    uint8 tx_mcs;
    uint8 tx_bw;
    uint8 uni_tx_pwr;
	int8  uni_tsnr;
	uint32 uni_idx;
	uint32  uni_aid;
};

/*
*first consider one AP & one STA,and then more STAs
*tx_mcs & tx_bw should be different according STAs
*/
struct lmac_rate_ctrl {
    uint8 tx_mcs_max;
    uint8 tx_mcs_min;
    uint8 fixed_tx_mcs;//unicast
    uint8 fixed_tx_bw;//unicast
    uint8 mcast_mcs;//multicast
    uint8 mcast_bw;//multicast

    uint8 auto_tx_mcs;
    uint8 auto_tx_bw;

    int8  rssi_pre;
    int8  rssi;
    int8  evm_pre;
    int8  evm;

    int8  margin;

    uint8 mcs_sel;
    uint8 bw_sel;

    uint8 tx_mcs;
    uint8 tx_bw;

    uint8   rcn_mcs_fixed : 1,
            rcn_bw_fixed  : 1,
            ant_dual      : 1,
            ant_dft       : 1,
            ant_fixed     : 1,
            ant_sel       : 1;
    //dual ant ctrl pin
    uint8   ant_ctrl_pin1           : 7,
            ant_ctrl_pin1_valid     : 1;
    uint8   ant_ctrl_pin2           : 7,
            ant_ctrl_pin2_valid     : 1;
};

struct lmac_pcf{
    uint32 cfp_start : 1,
           cfp_count :8,
           poll_idx : 8;
    uint32 cfp_durmax:16,//tbc； del cfp_timestamp
           cfp_dur_remain:16;
    uint32 cfp_timestamp_init;
    uint32 cfp_timestamp_expires;
};

struct lmac_cca_info{
    uint32  pri2m_start : 16,
            pri1m_start : 16;
    uint32  pri2m_mid : 16,
            pri1m_mid : 16;
    uint32  sec4m_mid : 16,
            sec2m_mid : 16;
    uint32  pri2m_ed : 16,
            pri1m_ed : 16;
    uint32  sec4m_ed : 16,
            sec2m_ed : 16;
    uint32  cca_obsv_dur:3;
};

struct window_record{
       uint64   bitmap;
       uint32   start       :   12,
                end         :   12,
                size        :   7,
                init        :   1;
       uint16   timeout     :   8;
       uint16   seq_num_s2;
};

struct lmac_bss_load{
    uint8 station_count[2];
    uint8 channel_utilization;
    uint8 available_admission_capacity[2];
    //may add other vendor specfic infos
    //no explicit admission control now
};

struct ap_sleep_info{
    uint32 mode:1;
    uint64 wk_timstamp;
};

struct lmac_priv {
    struct lmac_ops        *ops;
    struct ah_ce            ce;
    struct lmac_cfg         cfg;
    struct lmac_param       param;
    struct lmac_at_data     atd;
    struct lmac_monitor     monitor;
    struct lmac_cca_info    cca_info;
    struct lmac_rate_ctrl   rate;
    struct lmac_pcf         pcf;
    struct lmac_qa_info     qa_info;
#ifdef QC_TEST
    struct lmac_qc_info     qc_info;
#endif
    struct dsleep_cfg      *dcfg;
    struct lmac_init_param lparam;

    struct pv0_ctrl_rts     pv0_rts;
    struct pv0_wrapper_ctrl pv0_wpcts;
    struct pv0_wrapper_ctrl pv0_wpack;
    struct pv0_wrapper_ba   pv0_wpba;
    struct pv0_data_cf_poll pv0_cfpoll;
    struct pv0_ctrl_cf_end  pv0_cfend;
    struct pv0_ctrl_pspoll  pv0_pspoll;
    struct pv0_data_qos_null  pv0_qosnull;
    enum   lmac_tx_state    tx_state;
    enum   lmac_rx_state    rx_state;
    enum   lmac_ps_state    ps_state;
    
    //struct os_msgqueue      lmac_msgq;
    struct os_task          lmac_main_task;

    uint32                  error_flags;
    uint8                  *lmac_print_buff;
    struct os_semaphore     lmac_print_sem;
    struct os_task          lmac_print_task;
    uint16                  lo_kick_cnt;
    uint16                  chan_switch_cnt;
    uint32  ac              : 4,
            ndp_cts         : 1,
            ndp_ba          : 1,
            ndp_ack         : 1,
            sync_timeout    : 1,
            beacon_suspend  : 4,
            cts2self        : 1,
            bkn_retry       : 8,
            bkn_timer_start : 1,
            bkn_tx_notify   : 3,
            bkn_freq_idx    : 4,
            bkn_tsf_init    : 1,
            beacon_rxed     : 1;
            //beacon_lock:1;
    uint32  stop            : 1,
            acs_start       : 1,
            acs_rxsync_cnt  : 16,
            test_mode_enable: 1,
            matcmd          : 1,
            test_tx_start   : 1,
            tx_cont         : 1,
            test_tx_trig    : 1,
            tx_dly_ms       : 8;
    //uint32  tx_data_buffered: 1;//not used todo: del

    uint8 *tdma_buff;
    int32  tdma_buff_len;
    struct tdma_device     *tdma_dev;
    struct dbgpath_device  *dbgpath_dev;
    struct wphy_device     *wphy_ah_dev;
    struct rf_device       *rf_ah_dev;
    struct rfspi_device    *rf_spi;
    struct watchdog_device *sys_wd;
#if RFDIGICALI_HW_VER >= 2  //Mars or later
    struct  rfdigicali_device *rf_digcalib_dev;
#endif
    
    struct list_head       sta_list;
    struct os_mutex        sta_list_lock;
    uint16                 sta_cnt;
    uint16                 sta_psm_cnt;
    uint16                 sta_know_cnt;
    struct os_timer        lmac_tk_tm;
    struct os_timer        scan_probe_tm;
    uint32                 vht_ctrl;
    int8                   rsvd;
    int8                   rssi;
    int8                   tsnr;
    uint8                  lmac_wd_txto     : 1,
                           lmac_wd_rxto     : 1,
                           vht_ctrl_valid   : 1,
                           hw_scan_listen   : 1,
                           hw_scan_start    : 1;
    struct lmac_sta_info  *tx_dst_sta;
    struct sk_buff        *skb_hw_scan_probe;
    struct lmac_bss_load   bss_load;
    uint32 sta_map;
    uint32 sleep_map;
    int16 skb_status_cnt; //just for debug
    int16 skb_user_cnt; //just for debug
    uint16 rx_cache_cnt;
    uint16 rxq_list_cnt;
    RBUFFER_IDEF(evtq, uint32, LMAC_EVENT_QUEUE_SIZE);
    struct os_semaphore evt_sema;
    struct ap_sleep_info apsleep;
    uint32 tx_skb_cnt;
    uint32 wpos_err;
    uint32 rpos_err;
    uint32 tx_skb_max;
    uint8  fcs_err_ind:1;
    struct os_mutex         rf_mutex;
};

struct sta_tx_stat{
    uint32      tx_cnt :16,
                tx_frms : 16;
    int32       tx_apep;
    int32       tx_symbols;
    int32       tx_cca;
    //int32     tx_frms_retry;//DEL
    uint32      tx_frms_success : 16,
                tx_frms_droped  : 16 ;
    int32       tx_apep_success;
    int32       tx_apep_droped;
};
struct sta_rx_stat{
    uint32    rx_cnt:   16,
              rx_pkts:  16;  
    uint32    rx_bytes;
    uint32   rx_symbols;
    int32    freq_offset;
    //uint32   freq_center;
    uint32   rx_fcs_err;
    //int8     evm_bw[4];//del,just instance
};

//580
struct lmac_sta_info {
    struct   list_head list;
    struct   skb_list tx_q;
    atomic_t ref;
    uint32   freq[MAX_CHANS_NUM];
    int8     bgrssi_avg[MAX_CHANS_NUM];
    uint16   aid;
    uint16   partial_aid    : 9,//9
             pwr_mgmt       : 1,//10
             more_data      : 1,//11
             ap_sleep       : 1,//12
             roaming_out    : 1,//13
             deleted        : 1,//14
             chan_info_valid: 1,//15
             ps_polled      : 1;//16
    
    uint16   agc;//rx agc info 
    uint8    pspoll_to_cnt;
    uint8    addr[MAC_ADDR_SIZE];
    uint8    key_len;
    uint8    key[32];
    uint8    sta_txop_init;
    uint8    sta_txop;

    //for evm //to be modified with new rate control
    int8    *evm_buff;
    uint8    evm_idx;
    int8     evm;//instant evm value
    int8     evm_avg;
    int8     evm_std;
    uint8    bw_cnt;
    uint8    bw_adv[4];
    uint8    bw_adv_pre[4];
    
    //control info 
    uint8    recommended_mcs: 4,
             tx_mcs         : 4;
    uint8    tx_mcs_instant : 4,
             recommended_bw : 4;//feed back to peer sta
    uint8    tx_bw          : 4,//use for tx
             tx_bw_instant  : 4;
    uint8    tx_bw_cnt;
                  
    //statics info
    uint8     tx_duty_cycle;
    uint8     rx_duty_cycle;
    int8      tx_snr;
    int8      rssi;
    int8      rx_evm;
    uint8     rx_mcs         : 4,
              rx_bw          : 4;
    int8      rssi_max;      //mgmt/ctrl rssi

    struct rate_ctrl_info rc_info;
    struct window_record  r_win; // baseline
    struct window_record  c_win[8];//tid[0,7]
    struct sta_tx_stat    tx_stat;//
    struct sta_rx_stat    rx_stat;//
};

struct lmac_sta_status {
    uint16 aid;
    uint8  addr[6];
    int8   rssi;
    int8   evm;
    int8   evm_std;
    uint8  tx_mcs;
    uint8  tx_bw;
};

struct lmac_status {
    uint16 rxq;
    uint16 txq;
    uint16 acq[4];
    uint16 sta_count;
    struct lmac_sta_status sta[0];
};

int32 lmac_qc_init(void);
int32 lmac_cfg_init(void);
int32 lmac_set(int32 cmd, uint32 data);

int32 lmac_cfg_set_mac(struct lmac_ops *ops, uint8 *mac_addr);
int32 lmac_add_sta(struct lmac_ops *ops, uint16 aid, uint8 *addr);
int32 lmac_del_sta(struct lmac_ops *ops, uint16 aid);
int32 lmac_cfg_set_freq_range(struct lmac_ops *ops, uint16 freq_start, uint16 freq_end, uint8 bw);
int32 lmac_cfg_set_freq(struct lmac_ops *ops, uint32 center_freq);

int32 lmac_open(struct lmac_ops *ops);
int32 lmac_close(struct lmac_ops *ops);
int32 lmac_set_key(struct lmac_ops *ops, uint8 cmd, uint16 aid, uint8 *key, uint8 key_len);
int32 lmac_set_mcast_key(struct lmac_ops *ops, uint8 cmd, uint8 *key, uint8 key_len);
int32 lmac_set_primary_chan(struct lmac_ops *ops, uint8 primary_chan);
int32 lmac_set_bgrssi(struct lmac_ops *ops, int8 bgrssi);
void lmac_cfg_cw_param(uint8 ac, uint32 cw_min, uint32 cw_max);
void lmac_cfg_aifs_param(uint8 ac, uint32 aifs);
void lmac_cfg_txop_param(uint8 ac, uint16 txop_ms);
int32 lmac_set_aid(struct lmac_ops *ops, uint32 aid);
int32 lmac_set_txq_param(struct lmac_ops *ops, uint32 txq, struct lmac_txq_param *param);
int32 lmac_start_acs(struct lmac_ops *ops, int32 enable, uint32 scan_ms);
int32 lmac_lo_table_kick(uint16 chan_idx);
void lmac_lo_table_read(struct rfspi_device *rfspi);
int32 lmac_set_chan_list(struct lmac_ops *ops, uint16 *freq_list, uint16 count);
int32 lmac_lo_freq_set(uint32 center_freq);
int32 lmac_eth_scan_report(struct lmac_ops *ops, uint8 pass);
int32 lmac_set_cfg(struct lmac_ops * ops, uint32 cmd, uint32 param1, uint32 param2);
int32 lmac_get_cfg(struct lmac_ops *ops, uint32 cmd, uint32 *param1, uint32 *param2);
int32 lmac_set_radio_onoff(struct lmac_ops *ops, uint32 on_off);
int32 lmac_setcfg_bss_bw(struct lmac_ops *ops, uint8 bss_bw);
extern  void sta_rc_init(struct lmac_sta_info *sta);
extern  void ah_tx_status(struct lmac_sta_info *sta,
uint32 ampdu_len, uint32 ack_len, uint8 ant, uint8 sigbw, uint8 mcs);
void ah_ant_status(uint8 ant, int8 rssi);

#ifdef __cplusplus
}
#endif

#endif

