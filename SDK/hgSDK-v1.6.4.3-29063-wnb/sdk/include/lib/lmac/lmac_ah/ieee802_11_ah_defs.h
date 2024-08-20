#ifndef IEEE802_11_AH_DEFS_H
#define IEEE802_11_AH_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <typesdef.h>
#include "ieee802_11_defs.h"

#define GET_FC(addr)            get_unaligned_le16(addr)
#define GET_PV(addr)            ((*(uint8 *)addr) & 0x03)     
      
static const uint8  broadcast_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

//#define GET_TYPE_SUBTYPE(fc)  (((fc) & 0x00fc) >> 2)

/* control */
#define WLAN_FC_STYPE_CTRL_WRAP     7
#define WLAN_FC_STYPE_BA_REQ        8
#define WLAN_FC_STYPE_BA            9

#define ACK_RXED_FLAG          -1
#define BA_RXED_FLAG           -2

#define WLAN_INVALID_SEQ_NUM   0xFFFF
#define WLAN_EID_EXT_QA_OPERATION                       (128)

#define MAC_ADDR_SIZE                   6
#define COMPRESSED_S1G_SSID_MAX_LEN     4
#define SHORT_ID_MASK                   0x00001fff
#define IEEE80211_QOS_CTL_TID_MASK      0x000f
#define IEEE80211_MORE_DATA_MASK        0x2000

enum _NDP_BW {
	NDP_NONE  = 0,
    NDP_1MHZ  = 1,
    NDP_2MHZ  = 2,
};
    
enum _DUP_EN {
    DUP_DISABLE  = 0,
    DUP_ENABLE   = 1,
};

/*
* same as struct ieee80211_rts, to be delete
*/
struct pv0_ctrl_rts {
    union {
        uint16 val;
        IEEE80211_FRAME_CONTROL fc;
    };
    uint16 duration;
    uint8 ra[MAC_ADDR_SIZE];
    uint8 ta[MAC_ADDR_SIZE];
};

struct short_id {
    uint16 aid     : 13, 
           a3p     : 1,  
           a4p     : 1, 
           amsdu   : 1;  
};

struct sid_mac {
    struct short_id             sid;
    uint8                       mac[MAC_ADDR_SIZE];
};

struct fromds0_addr {
    uint8                       a1[MAC_ADDR_SIZE];
    struct short_id             a2;
};

struct fromds1_addr {
    struct short_id             a1;
    uint8                       a2[MAC_ADDR_SIZE];
};

struct ieee80211_pv1_qos_data1 {
    union {
        uint16                   frame_control;
        IEEE80211_FRAME_CONTROL  frm_ctrl;
    } fc;
    union {
        struct fromds0_addr sta2ap;  
        struct fromds1_addr ap2sta;   
    } addr;
    uint16 seq_ctrl;
};

struct ieee80211_pv1_ctrl_action {
    union {
        uint16                   frame_control;
        IEEE80211_FRAME_CONTROL  frm_ctrl;
    } fc;
    union {
        struct fromds0_addr sta2ap;  
        struct fromds1_addr ap2sta;   
    } addr;
    uint16 seq_ctrl;
};


struct ieee80211_pv1_qos_data2 {
    union {
        uint16 val;
        IEEE80211_FRAME_CONTROL  frm_ctrl;
    };
    uint8 a1[MAC_ADDR_SIZE];
    uint8 a2[MAC_ADDR_SIZE];
    uint16 seq_ctrl;
};


// =====================================================================================
// NDP, D8, p.223, to be handled by PHY
//0 NDP CTS (control frame) 9.9.2.1 (NDP CTS)
//0 NDP CF-End (control frame) 9.9.2.2 (NDP CF-End)
//1 NDP PS-Poll (control frame) 9.9.2.3 (NDP PS-Poll)
//2 NDP Ack (control frame) 9.9.2.4 (NDP Ack)
//3 NDP PS-Poll-Ack (control frame) 9.9.2.5 (NDP PS-Poll-Ack)
//4 NDP BlockAck (control frame) 9.9.2.6 (NDP BlockAck)
//5 NDP Beamforming Report Poll (control frame)9.9.2.7 (NDP Beamforming Report Poll)
//6 NDP Paging (control frame) 9.9.2.8 (NDP Paging)
//7 NDP Probe Request (management frame)9.9.3.1 (NDP Probe Request)
//D8, p.276, p.278
// BSSID[39:47]mod(2^9-1) + 1
//(AID[0:8] + 2^5 * BSSID[44:47] (+) BSSID[40:43])mod 2^9
// D8, p.223
struct ndp_cmac_cts1m {  
    uint32   ndp_type             : 3,  // B0
             cts_cfend_ind        : 1,  // B3, 0 = CTS, 1 = CF-END or RTS
             addr_ind             : 1,  // B4, 0 = CTS resp to RTS, 1 = AP broadcast
             ra_bssid             : 9,  // B5
             duration             : 10, //B14 in units of OFDM symbol duration (40 us)
             early_sec_ind        : 1,  //B24, No BF = 0
             unused               : 7;  // make it 32 bit;
};

struct ndp_cmac_cts2m {  
    uint64   ndp_type             : 3,  // B0
             cts_cfend_ind        : 1,  // B3, 0 = CTS, 1 = CF-END or RTS
             addr_ind             : 1,  // B4, 0 = CTS resp to RTS, 1 = AP broadcast
             ra_bssid             : 9,  // B5, partial AID for receiving non-ap sta, partial 
                                        //bssid for receiving ap
             duration             : 15, //B14 microseconds nc ? 15 bits?
             early_sec_ind        : 1,  //B29, No BF = 0
             bw_ind               : 3,  //B30, 0=1MHz, 1=2MHz, 2=4MHz, 3=8MHz, 4=16MHz
             rsvd                 : 4,  //B33
             unused               : 27; // make it 64 bit
};

struct ndp_cmac_ack1m {   // 2
    uint32   ndp_type             : 3,  // B0
             ack_id               : 9,  // B3
             more_data            : 1,  //B12
             idle_ind             : 1,  //B13
             duration             : 10, //B14 //idle_ind = 0: in units of 40us, =1:in milliseconds
             relay_frame          : 1,  //B24
             unused               : 7;  // make it 32 bit;
};

struct ndp_cmac_ack2m {   // 2
    uint64   ndp_type             : 3,  // B0
             ack_id               : 16, // B3
             more_data            : 1,  //B19
             idle_ind             : 1,  //B20
             duration             : 14, //B21
             relay_frame          : 1,  //B35
             reserved             : 1,  //B36
             unused               : 27; // make it 64 bit;
};

//D8, p.232
struct ndp_cmac_ba1m {   // 4
    uint32   ndp_type             : 3,  // B0
             id                   : 2,  // B3
             start_sn             : 12, // B5
             bitmap               : 8,  //B17
             unused               : 7;  // make it 32 bit;
};

struct ndp_cmac_ba2m {   // 4
    uint64   type               : 3,  // B0
             id                 : 6,  // B3
             start_sn           : 12, // B9
             bitmap             : 16, //B21
             unused             : 27; // make it 64 bit;
};

struct ndp_cmac_psp2m {  
    uint64   type               : 3, // B0
             ra                 : 9, // B3
             ta                 : 9, // B12
             preferred_mcs      : 4, // B21
             udi                : 12;// B25, duration in units of 40us
};

struct ndp_cmac_pspack2m {  
    uint64   type               : 3, // B0
             ack_id             : 16,// B3
             more_data          : 1, // B19
             idle_ind           : 1, // B20
             duration           : 16;// B21, duration in units of us
};

//D8, p.232
struct ndp_probe_req_1m {   // 4
    uint32   type                 : 3,  // B0
             cssid_ano_present    : 1,  // B3
             cssid_ano            : 16, // B4
             probe_resp_type      : 1,  // B20
             reserved             : 4,  // B24
             unused               : 7;  // make it 32 bit;
};

struct ndp_probe_req_2m {   // 4
    uint64   type               : 3,  // B0
             cssid_ano_present  : 1,  // B3
             cssid_ano          : 32, // B9
             probe_resp_type    : 1, //B21
             unused             : 27; // make it 64 bit;
};

struct ndp_cmac {
    union {
        struct ndp_cmac_cts1m    cts1m;
        struct ndp_cmac_cts2m    cts2m;
        struct ndp_cmac_ack1m    ack1m;
        struct ndp_cmac_ack2m    ack2m;
        struct ndp_cmac_ba1m     ba1m;
        struct ndp_cmac_ba2m     ba2m;
        struct ndp_cmac_psp2m    psp2m;
        struct ndp_cmac_pspack2m pspack2m;
        //mgmt
        struct ndp_probe_req_1m  prob_req1m;
        struct ndp_probe_req_2m  prob_req2m;
        uint64  frm_body;           // NDP_1M = 25 bits, NDP_2M = 37 bits
    };
};

enum _ndp_type {
    NDP_CTS_CFEND       = 0,
    NDP_PS_POLL         = 1,
    NDP_ACK             = 2,
    NDP_PS_POLL_ACK     = 3,
    NDP_BA              = 4,
    NDP_BRP             = 5,
    NDP_PAGING          = 6,
    NDP_PROBE_REQ       = 7,
};

struct key_iv {
    uint8    rsvd : 5,  // b0-4
             ext_iv: 1,  // b5 always 1 for ccmp
             key_id: 2;  // b6-8, key index, default = 0;
};


struct pv0_ccmp_hdr {
    uint8               pn0;
    uint8               pn1;
    uint8               rsvd;
    struct key_iv       key_iv;
    uint8               pn2;
    uint8               pn3;
    uint8               pn4;
    uint8               pn5;
};

struct ccmp_aad_pv0 {
    IEEE80211_FRAME_CONTROL fc;
    uint8  a1[MAC_ADDR_SIZE];
    uint8  a2[MAC_ADDR_SIZE];
    uint8  a3[MAC_ADDR_SIZE];
    uint16 seq_ctrl;
    uint8  options[8]; // a4 qos Optional
};

struct ccmp_aad_pv1 {
    IEEE80211_FRAME_CONTROL fc;
    uint8  a1[MAC_ADDR_SIZE];
    uint8  a2[MAC_ADDR_SIZE];
    uint16 seq_ctrl;
    uint8  options[12]; // a3 a4 Optional
};

struct nonce_flags {
    uint8    priority : 4,
             mgmt     : 1,
             pv1      : 1,  //pv1 flag
             zeros    : 2;
};

struct ccmp_nonce {
    struct nonce_flags      flags;              // b0-b3, b4-b7=0;
    uint8                   a2[MAC_ADDR_SIZE];
    uint8                   pn[6];              //pn0..5
};

static inline uint8 ieee80211_is_pv0(uint16 fc)
{
    return ((fc & WLAN_FC_PVER) == 0x00);
}

/**
* 9.2.4.6.2 HT variant
**/
struct ht_control{
    uint32  vht             :   1,//b0
            trq             :   1,//b1  transmit a sounding PPDU
            mai             :   4,//b2~b5
            mfsi            :   3,//b6~b8
            mfb_aselc       :   7,//b9~b15
            cali_pos        :   2,//b16~b17
            cali_seq        :   2,//b18~b19
            reserved1       :   2,//b20~b21
            csi_steering    :   2,//b22~b23
            ndp_announce    :   1,//b24
            reserved2       :   4,//b25~b28
            dei             :   1,//b29
            ac_constrain    :   1,//b30
            rdg             :   1;//b31
};

/**
* reference 2016 9.2.4.6.3 VHT variant
* Figure 9-14aâ€”MFB subfield in the VHT variant HT Control field when carried in S1G PPDU
* bw: Set to 0 for 1 MHz,  1 for 2 MHz,  2 for 4 MHz,  3 for 8 MHz
**/
struct vht_control{
        uint32  vht         :   1,//b0 VHT
            reserved        :   1,//b1 fix 0 
            mrq             :   1,//b2 mcs req
            msi_stbc        :   3,//b3~b5
            mfsi_gidl       :   3,//b6~b8
            num_sts         :   2,//b9~b10
            vht_mcs         :   4,//b11~b14
            bw              :   3,//b15~b17
            snr             :   6,//b18~b23
            gid_h           :   3,//b24~b26
            coding_type     :   1,//b27
            fb_tx_type      :   1,//b28
            unsolicited_mfb :   1,//b29
            ac_constraint   :   1,//b30
            rdg_more_ppdu   :   1;//b31
};

struct vs_qa_resp{
    int8    rssi;
    int8    evm;    
    int8    freq_dev;//KHz
    uint8   agc;     //last two
    int8    bgrssi;
    uint16  svn_version;
    uint8   uni_test : 1,
            sdk_bver : 4,
            sdk_pver : 3;
}STRUCT_PACKED;

struct vs_qa_resp2{
    int8    temperature;
    uint8   vcc_meas    : 6,
            resv        : 2;
};
    
struct pv0_ctrl_ba {
    union {
        uint16 val;
        IEEE80211_FRAME_CONTROL fc;
    };
    uint16   duration;               //in microseconds(us)
    uint8   ra[MAC_ADDR_SIZE];
    uint8   ta[MAC_ADDR_SIZE];
    uint16  ba_ack_policy       :1,
            multi_tid:1,
            compressed_bitmap   : 1,
            gcr                 : 1,
            reserved            : 8, 
            tid_info            : 4;
    int16  start_seq;
    union{
        uint64  bitmap;
        struct vs_qa_resp       qa_resp;
    };
}STRUCT_PACKED;

struct pv0_wrapper_ctrl {
    union {
        uint16                  val;
        IEEE80211_FRAME_CONTROL fc;
    };
    uint16   duration;               
    uint8   ra[MAC_ADDR_SIZE];
    union {
        uint16                  cfc_val;
        IEEE80211_FRAME_CONTROL carried_fc;
    };

    struct vht_control          vht_ctrl;
}STRUCT_PACKED;

struct pv0_wrapper_ba {
    struct  pv0_wrapper_ctrl     wp;
    uint8   ta[MAC_ADDR_SIZE];
    uint16  ba_ack_policy       :1,
            multi_tid:1,
            compressed_bitmap   : 1,
            gcr                 : 1,
            reserved            : 8,
            tid_info            : 4;
    uint16  start_seq;          //TODO:SN:4:15 FN:0:3  
    union{
        uint64  bitmap;
        struct vs_qa_resp       qa_resp;
    };
}STRUCT_PACKED;

struct pv0_ctrl_wrapper_ba {
    union {
        uint16                  val;
        IEEE80211_FRAME_CONTROL fc;
    };
    uint16   duration;               
    uint8   ra[MAC_ADDR_SIZE];
    union {
        uint16                  cfc_val;
        IEEE80211_FRAME_CONTROL carried_fc;
    };
    struct vht_control          vht_ctrl;
    uint8   ta[MAC_ADDR_SIZE];
    uint16  ba_ack_policy       :1,
            multi_tid:1,
            compressed_bitmap   : 1,
            gcr                 : 1,
            reserved            : 8,
            tid_info            : 4;
    int16  start_seq;
    uint64  bitmap;
}STRUCT_PACKED;


//WLAN_FC_STYPE_QOS_DATA_CFPOLL
struct pv0_data_cf_poll{
    union {
        uint16 val;
        IEEE80211_FRAME_CONTROL fc;
    };
    uint16  duration; //in microseconds(us)
    uint8   ra[MAC_ADDR_SIZE];
    uint8   ta[MAC_ADDR_SIZE];
    uint8   a3[MAC_ADDR_SIZE];
    uint16  seq_ctrl;
    uint16  tid:4,  //qos control
            eosp:1,
            ack_policy:2,
            reserved:1,
            txop_limit:8;
    struct vht_control vht_ctrl;        
};

struct pv0_ctrl_cf_end{
    union {
        uint16 val;
        IEEE80211_FRAME_CONTROL fc;
    };
    uint16  duration; //in microseconds(us)
    uint8   ra[MAC_ADDR_SIZE];//broad-cast
    uint8   ta[MAC_ADDR_SIZE];//bssid  
};

//qos null
struct pv0_data_qos_null{
    union {
        uint16 val;
        IEEE80211_FRAME_CONTROL fc;
    };
    uint16  duration; //in microseconds(us)
    uint8   ra[MAC_ADDR_SIZE];//broad-cast
    uint8   ta[MAC_ADDR_SIZE];//bssid
    uint8   bssid[MAC_ADDR_SIZE];//bssid
    uint16  seq_ctrl;
    uint16  tid:4,  //qos control
            eosp:1,
            ack_policy:2,
            reserved:1,
            txop_limit:8;
}STRUCT_PACKED;

//ps-poll
struct pv0_ctrl_pspoll{
  union {
        uint16 val;
        IEEE80211_FRAME_CONTROL fc;
    };
    uint16  id; //associate ID
    uint8   ra[MAC_ADDR_SIZE];//broad-cast
    uint8   ta[MAC_ADDR_SIZE];//bssid
}STRUCT_PACKED;

/**
 * struct ieee80211_channel_sw_ie
 * This structure refers to "Channel Switch Announcement information element"
 */
struct ieee80211_channel_sw_ie {
    uint8 eid;
    uint8 len;
    uint8 mode;
    uint8 new_ch_num;
    uint8 count;
} STRUCT_PACKED;

/**
 * This structure refers to 9.4.2.5 CF Parameter Set element
 */
struct ieee80211_cf_parameter_set_ie {
    uint8 eid;
    uint8 len;
    uint8 cfp_count;
    uint8 cfp_period;
    uint8 cfp_maxdur[2];//TU
    uint8 cfp_durremain[2];
} STRUCT_PACKED;

/**
 * This structure refers to 9.4.2.6 TIM element
 */
struct ieee80211_tim_ie {
    uint8 dtim_count;
    uint8 dtim_period;
    uint8 bitmap_control;
    uint8 partial_virtual_bitmap[1];
} STRUCT_PACKED;


struct noise_hist_req{
    union{
    uint16  freq; //hgic private 
    uint16   operating_class : 8,
             channel_number : 8;
    };
    uint16  rand_interval;
    uint16  meas_duration;
}STRUCT_PACKED;

/**
* reference: Figure 9-147¡ªMeasurement Request element format
**/
struct ieee80211_measure_req_ie {
    uint8 eid;
    uint8 len;
    uint8 token;
    uint8 parallel : 1,
          enable : 1,
          request : 1,
          report : 1,
          dur_mandatory : 1,
          reserved : 3;
    uint8 type;
} STRUCT_PACKED;

struct bgrssi_report_info { 
    uint8   freq[4];
    int8    bgrssi_avg;
};

struct noise_hist_report{
    union{
        uint16  freq; //hgic private 
        uint8   operating_class : 8,
                channel_number  : 8;
    };
    uint8   actual_meas_start_time[8];
    uint16  meas_dur;
    uint8   antenna_id;
    uint8   anpi;
    uint8   ipi_density[11];
}STRUCT_PACKED;

/**
* reference: Figure 9-191¡ªMeasurement Report element format
**/
struct ieee80211_measure_report_ie {
    uint8 eid;
    uint8 len;
    uint8 token;
    uint8 late : 1,
          incapable : 1,
          refused : 1,
          reserved : 3;
    uint8 type;
    //uint8 report[0];//variable
} STRUCT_PACKED;

/**
 * struct ieee80211_ext_chansw_ie
 *
 * This structure represents the "Extended Channel Switch Announcement element"
 */
struct ieee80211_ext_chansw_ie {
    uint8 eid;
    uint8 len;
    uint8 mode;
    uint8 new_operating_class;
    uint8 new_ch_num;
    uint8 count;
} STRUCT_PACKED;

/**
 * struct ieee80211_wide_bw_chansw_ie - wide bandwidth channel switch IE
 */
struct ieee80211_wide_bw_chansw_ie {
    uint8 new_channel_width;
    uint8 new_center_freq_seg0;
    uint8 new_center_freq_seg1;
} STRUCT_PACKED;

struct pv0_mgmt_s1g_beacon{
    struct {
    uint16   protol_version  :      2,
             type       :           2,
             subtype    :           4,
             next_tbtt  :           1,
             comp_ssid  :           1,
             ano        :           1,
             bss_bw     :           3,
             security   :           1,
             ap_pm      :           1;
    };//oct 0~1
    uint16 duration;//oct 2~3
    uint8 sa[MAC_ADDR_SIZE];////oct 4~9
    uint8 timestamp[4];//oct 10~13
    uint8 change_sequence; //oct 14
    uint8 next_target_beacon_trans_time[3]; //0ct 15~17
    uint8 compressed_ssid[4];//0ct 18~21
    uint8 access_network_opt;//0ct 22
}STRUCT_PACKED;

struct s1g_beacon_compatibility{
    union {  
        uint16  compat_info;
        uint16  ess         : 1,
                ibss        : 1,
                cf_pollable : 1,
                cf_poll_req : 1,
                privacy     : 1,
                short_preamble:1,
                rsvd1       : 1,
                rsvd2       : 1,
                spectrum_mgmt:1,
                qos         : 1,
                short_slot_time:1,
                apsd        : 1,
                radio_measure:1,
                rsvd3       : 1,
                delay_ba    : 1,
                immediate_ba: 1;
        };
    uint16  interval;   //TU= 1024us
    uint32  tsf_completion;
}STRUCT_PACKED;

struct vs_bss_announcement_ie{
    int32 bss_freq;
    int8  pri_chan;
    int8  bss_bw;
    int8  bg_rssi;//reserved: TODO: add bgrssi
    int8  sta_num;
    uint8  ssid[32 + 4];
}STRUCT_PACKED;

#ifdef __cplusplus
}
#endif

#endif

