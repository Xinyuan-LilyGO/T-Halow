#ifndef _LMAC_RC_H_
#define _LMAC_RC_H_

#ifdef __cplusplus
extern "C" {
#endif

//TODO: 1M BSS only try MCS
#define MAX_MCS_NUM             8
#define MAX_BW_NUM              4
#define MAX_ANT_NUM             2
#define PROB_PERIOD             20//10
#define RATE_GROUPS             (MAX_ANT_NUM * MAX_BW_NUM * MAX_MCS_NUM)
#define SAMPLE_SIZE             18
//#define RETRY_CHAIN             4

#define RC_FLAGS_IDX_MASK       (RATE_GROUPS - 1)
#define RC_FLAGS_MCS_SHIFT      0 
#define RC_FLAGS_MCS_MASK       (0x07 << RC_FLAGS_MCS_SHIFT)
#define RC_FLAGS_BW_SHIFT       3 
#define RC_FLAGS_BW_MASK        (0x03 << RC_FLAGS_BW_SHIFT)
#define RC_FLAGS_ANT_SHIFT      5 
#define RC_FLAGS_ANT_MASK       (0x01 << RC_FLAGS_ANT_SHIFT)
#define RC_FLAGS_MCS_10_SHIFT   6 
#define RC_FLAGS_MCS_10_MASK    (0x01 << RC_FLAGS_MCS_10_SHIFT)
#define RC_IDX_GET(grp)         (grp & (RC_FLAGS_BW_MASK | RC_FLAGS_MCS_MASK))
#define RC_MCS_GET(grp)         ((((grp) & RC_FLAGS_MCS_10_MASK) >> (RC_FLAGS_MCS_10_SHIFT - RC_FLAGS_BW_SHIFT)) + \
                                 (((grp) & RC_FLAGS_MCS_MASK) >> RC_FLAGS_MCS_SHIFT))
#define RC_BW_GET(grp)          (((grp) & RC_FLAGS_BW_MASK) >> RC_FLAGS_BW_SHIFT)
#define RC_SIGBW_GET(grp)       ((RC_BW_GET(grp) + 3) % 4)
#define RC_ANT_GET(grp)         (((grp) & RC_FLAGS_ANT_MASK) >> RC_FLAGS_ANT_SHIFT)
#define RC_IDX_CALC(bw, mcs) 	((((bw) << RC_FLAGS_BW_SHIFT) & RC_FLAGS_BW_MASK) + \
                                  (((mcs) << RC_FLAGS_MCS_SHIFT) & RC_FLAGS_MCS_MASK))
#define RC_GRP_CALC(ant, bw, mcs) ((((ant) << RC_FLAGS_ANT_SHIFT) & RC_FLAGS_ANT_MASK) + \
                                   (((bw) << RC_FLAGS_BW_SHIFT) & RC_FLAGS_BW_MASK) + \
                                   (((mcs >> RC_FLAGS_BW_SHIFT) << RC_FLAGS_MCS_10_SHIFT) & RC_FLAGS_MCS_10_MASK) + \
                                   (((mcs) << RC_FLAGS_MCS_SHIFT) & RC_FLAGS_MCS_MASK))

#define RG_SELECT_DFT           (0x01 << 0)
//#define RG_SELECT_TP1           (0x01 << 1)
//#define RG_SELECT_TP2           (0x01 << 2)
#define RG_SELECT_PROB          (0x01 << 3)
#define RG_SELECT_BASIC         (0x01 << 4)
#define RG_SELECT_SAMPLE        (0x01 << 5)

extern uint16 rate_tbl[32];

struct rate_group {
    uint16 rate;//actual rate => phy rate
    uint8 grp;
    uint8 cnt;//since stich last update
};

struct rate_ctrl_info {
    uint8  use_dft_grp  : 1;//RESV
    uint32 sample_cnt   : 8,
           rg_sel       : 8,
           prob_tick    : 8,
           prob_idx     : 8;

    //uint32 prob_rate[RATE_GROUPS];//
    uint16 prob_prr[RATE_GROUPS];//packet right rate 
    uint8  prob_cnt[RATE_GROUPS];
    
    struct rate_group   rg_dft;
    struct rate_group   rg_tp1;
    struct rate_group   rg_tp2;
    struct rate_group   rg_prob;//rate去掉？有什么用
    //struct rate_group   rg_basic;//not used
};
int32 lmac_rc_init(void); 

/**
* infos
* MCS rate information for an MCS group 
* flags = IEEE80211_TX_RC_SHORT_GI;    TODO
*/

#ifdef __cplusplus
}
#endif

#endif




