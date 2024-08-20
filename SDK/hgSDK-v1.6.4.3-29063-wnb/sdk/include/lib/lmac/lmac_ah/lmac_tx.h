#ifndef _LMAC_TX_H_
#define _LMAC_TX_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
*lmac_tx_info:all necessary info for each individual frame
*less than 48 bytes, contain in skb.cb
**/
struct lmac_beacon_info{
    //uint32  ind            : 1;//bkn.ind no change                   ok
            //channel_switch : 1;//bkn.channel_switch                  ok
    struct pv0_mgmt_s1g_beacon              *hdr;//bkn.hdr no change ok
    struct ieee80211_s1g_compatibility_ie   *compat;//bkn.compat     ok
    struct ieee80211_tim_ie                 *tim;//bkn.tim           ok
    struct ieee80211_s1g_capabilities       *cap;//bkn.cap
    struct ieee80211_s1g_operation          *op;
    struct ieee80211_cf_parameter_set_ie    *cfps;//bkn.cfps         ok
    struct bkn_priv_info_element            *priv;
    uint8                                   *next_tbtt;//tbtt        ok
    //tbc 
};

/*
struct hgic_tx_info {
    uint8  band;
    uint8  tx_bw;
    uint8  tx_mcs;
    uint8  antenna;
    uint32 tx_flags;
    uint16 tx_flags2;
    uint8  priority:4, freq_idx : 4;
    uint8  tx_power;
};
*/

enum lmac_tx_info_flags3{
   LMAC_TX_FLAGS3_NO_AGG            = BIT(0),
   LMAC_TX_FLAGS3_MEASURE_RPT       = BIT(1),
   LMAC_TX_FLAGS3_BSS_ANN           = BIT(2),
   LMAC_TX_FLAGS3_SCAN_PROBE        = BIT(3),
   LMAC_TX_FLAGS3_ANT_PROBE         = BIT(4),
};
//#define TX_MCS_LIMIT() (ah_lmac.cfg.bss_1m_ind ? 10 : 7)
//#define TX_BW_LIMIT()  (ah_lmac.cfg.bss_1m_ind ? SIG_BW : 7)
//#define TX_PRIORITY_LIMIT()     7
//#define TX_FREQ_IDX_LIMIT()     15
//#define TX_ANT_SEL_LIMIT()      1

struct lmac_tx_info {
    uint32 flags1;//copy of skb txinfo flags1
    uint32 flags2;//copy of skb txinfo flags2
    uint32 flags3;//lmac local tx ctrl flags3                     
    //struct lmac_beacon_info      bkn;//tbc: in bo irq
    struct lmac_sta_info        *sta;
    //IEEE80211_FRAME_CONTROL *fc;
    uint8                       *buff;
    int32                        frm_len    :16,
                                 apep_len   :16;
    uint16                       seq_num;//TODO   
    uint8                        rx_addr[MAC_ADDR_SIZE];//TODO:del? NULL or ??
    uint32                       tx_bpn;
    uint32                       proto_ver  : 2,//0
                                 type       : 3,//2
                                 stype      : 4,//5
                                 ack_policy : 1,//9
                                 ndp_ind    : 1,//10
                                 ndp_bw     : 2,//11
                                 dup_ind    : 1,//13
                                 from_ds    : 1,//14
                                 to_ds      : 1,//15
                                 tid        : 4,//19
                                 protected_frm  : 1,//20
                                 hdr_compress   : 1,//21
                                 uplink_ind     : 1,   //22
                                 mcast          : 1,//23
                                 control_frm    : 1,  //24
                                 data_frm       : 1,//25
                                 action_frm     : 1,//26
                                 aft_beacon     : 1,   //27 
                                 heart_beat     : 1,    //28
                                 frag_frm       : 1,    //29
                                 bkn_ind        : 1;    //30
                                 
    uint32                       tx_success     : 1,
                                 frm_retry_cnt  : 8,
                                 rts_retry_cnt  : 8,
                                 hdr_len        : 8,
                                 short_gi       : 1,
                                 frm_type       : 2,
                                 modem_bw       : 2,
                                 ping_data      : 1;//22
    uint8                        dup_cnt;
    uint16                       aid;
    uint16                       partial_aid;
    uint32                       jiffies_cca;//TODO
    //uint32                       jiffies_deq;  
    //params assigned by umac
    uint8                        sig_bw;//0x0f auto
    uint8                        sig_mcs;//0x0f auto
    uint8                        priority;//0x0f auto
    uint8                        freq_idx:5, antenna:3;
    uint8                        tx_pwr_idx;
    uint8                        tx_dig_att;
    uint16                       rate_idx;
    //int32                        icmp_sn;
	//int32                        rate_idx;//to be used: size overflow
};

struct tx_vec_part2_1m_ndp {
    uint64     ndp_cmac_frm_body: 25,
               ndp_indication: 1,
               crc: 4,
               trail: 6;
};
struct tx_vec_part2_2m_ndp {
    uint64     ndp_cmac_frm_body: 37,
               ndp_indication: 1,
               crc: 4,
               trail: 6;
};
/////////////////////////////////////////////////////////////////
struct tx_vec_part2_1m_frm {
    uint64               space_time_streams: 2, // bit 1:0, must be 0
                         short_guard_interval: 1, // bit2
                         coding: 1, // bit 3, must be 0: BCC
                         low_density_parity_check: 1, // bit 4, must be 1
                         space_time_block_coding: 1, // bit 5, must be 0
                         reserved_bit: 1, // must be 1
                         mcs: 4, // bit 10:7
                         aggregation_indication: 1, // bit 11
                         length: 9, // bit 20:12
                         response_indication: 2, // bit 22:21
                         smoothing: 1, // bit 23
                         traveling_pilot: 1, // bit 24
                         ndp_indication: 1, // bit 25
                         crc: 4, // bit 29:26
                         trail: 6; // bit 35:30
};
/////////////////////////////////////////////////////////////////
struct tx_vec_part2_2m_short {
    uint64             reserved_bit: 1, // bit 0, must be 1
                       space_time_block_coding: 1, // bit 1, must be 0
                       uplink_indication: 1, // bit 2
                       signal_bandwidth: 2, // bit 4:3
                       space_time_streams: 2, // bit 6:5, must be 0
                       identification: 9, // bit 15:7
                       short_guard_interval: 1, // bit 16
                       coding: 1, // bit 17, must be 0
                       low_density_parity_check: 1, // bit 18
                       mcs: 4, // bit 22:19
                       smoothing: 1, // bit 23
                       aggregation_indication: 1, // bit 24
                       length: 9, // bit 33:25
                       response_indication: 2, // bit 35:34
                       traveling_pilot: 1, // bit 36
                       ndp_indication: 1, // bit 37
                       crc: 4, // bit 41:38
                       trail: 6; // bit 47:42
};
/////////////////////////////////////////////////////////////////
struct tx_vec_part2_2m_long {
    uint64       multi_user_support: 1, // bit 0, must be 0
                 space_time_block_coding: 1, // bit 1, must be 1
                 uplink_indication: 1, // bit 2
                 signal_bandwidth: 2, // bit 4:3
                 space_time_streams: 2, // bit 6:5, must be 0
                 identification: 9, // bit 15:7
                 short_guard_interval: 1, // bit 16
                 coding: 1, // bit 17, must be 0
                 low_density_parity_check: 1, // bit 18, must be 1
                 mcs: 4, // bit 22:19
                 beam_changer_smoothing: 1, // bit 23
                 aggregation_indication: 1, // bit 24
                 length: 9, // bit 33:25
                 response_indication: 2, // bit 35:34
                 reserved_bit: 1, // bit 36, must be 1
                 traveling_pilot: 1, // bit 37
                 crc: 4, // bit 41:38
                 trail: 6; // bit 47:42
};

struct s1g_tx_vec_part1 {
    uint32              tx_power: 5,
                        ndp_indication: 1,
                        signal_bandwidth: 2,
                        modem_bandwidth: 2,
                        frm_type: 2,
                        mcs: 4,
                        scrambler_init: 7,
                        dup_en: 1,
                        reserved: 8;
};

struct s1g_tx_vec_part2 {
    union {
        struct tx_vec_part2_1m_ndp            ndp_1m;
        struct tx_vec_part2_2m_ndp            ndp_2m;
        struct tx_vec_part2_1m_frm            frm_1m;
        struct tx_vec_part2_2m_short        short_2m;
        struct tx_vec_part2_2m_long          long_2m;
        uint32 val[2];
        uint64 val_u64;
    };
};

struct s1g_tx_vector {
    union {
        struct s1g_tx_vec_part1      part1;
        uint32                       vec0;
    };
    uint32                       num_of_symbols;
    struct s1g_tx_vec_part2      part2;
};

struct lmac_agglist {
    struct sk_buff             *skbs[64];
    uint32                      apep;
    uint32                      symbols;
    uint32                      start_sn:16,
                                end_sn:16;
    uint32                      sub_frms:8,
                                count: 8,
                                bw   : 2,
                                mcs  : 4,
                                phdr : 4,
                                valid: 1;
    struct s1g_tx_vector        txvec;//flag
};

void lmac_tx_init(void);
void lmac_kick_tx_task(void);
int32 lmac_tx(struct lmac_ops *ops, struct sk_buff *skb);
int32 lmac_test_tx(struct lmac_ops *ops, struct sk_buff *skb);
void lmac_irq_ac_pd(void);
void lmac_irq_bo_fns(void);
void lmac_irq_tx_end(void);
void lmac_irq_tx_tmo(void);
void lmac_update_ndp_cts_tx_vec(uint64 ndp_body);
void lmac_update_ndp_ack_tx_vec(uint64 ndp_body);
void lmac_update_ndp2m_ba_tx_vec(uint64 ndp_body);
void lmac_update_pv0_wpcts_tx_vec(void);
void lmac_update_pv0_wpack_tx_vec(void);
void lmac_update_pv0_wpba_tx_vec(void);
void lmac_update_pv0_cfend_tx_vec(void);
void lmac_update_frm_tx_vec(void);
void lmac_update_tx_state_ack(uint8 ack);
int32 lmac_update_tx_state_ba(int16 start_sn, uint64 bitmap);
void lmac_vht_info_get(uint32 vht);
void lmac_adjust_cca_threshold(int8 bg_rssi_avg);
void lmac_adjust_agc_threshold(int8 bg_rssi_avg);

void lmac_tx_vec_init(void);
int32 lmac_auto_channel_select(void);
void lmac_tx_queue_agglist_init(void);

void lmac_gen_pspack_ndp2m(uint16 ack_id, uint16 dur_limit);
int32 ndp_pspoll_ack_rx_hdl(uint64 ndp_body, uint8 pribw);
int32 ndp_ack_rx_hdl(uint64 ndp_body, uint8 pribw);
int32 ndp_ba_rx_hdl(uint64 ndp_body, uint8 pribw);
uint32 lmac_txq_count(void);
#ifdef USING_TX_SQ
uint32 lmac_txsq_count(void);
#else
uint32 lmac_txbcq_count(void);
#endif
uint32 lmac_statq_count(void);
uint32 lmac_acq_count(uint8 ac);
uint8 lmac_txagg_count(uint8 ac);
int32 lmac_send_mgmt_meas_req(uint8 *da);
int32 lmac_send_mgmt_meas_report(void);
int32 lmac_send_bss_announcement(void);
int32 lmac_send_scan_probe(void);
int32 lmac_send_ant_pkt(void);
int32 lmac_send_probe_resp(void);
void lmac_update_ndp_ba_tx_vec(uint64 ndp_body);
int32 lmac_tx_date_prepared(void);
int32 lmac_tx_frame_regen(uint8 ac, uint8 bw, uint8 mcs, uint16 syms);
int32 tx_skbs_cached(void);
int32 lmac_beacon_prepare(void);
extern int32 ah_get_rate(struct lmac_tx_info *tx_info);
void lmac_spec_cca_cfg(uint8 ch_type);
void lmac_update_tx_state_cts(int8 rssi);


#ifdef __cplusplus
}
#endif

#endif

