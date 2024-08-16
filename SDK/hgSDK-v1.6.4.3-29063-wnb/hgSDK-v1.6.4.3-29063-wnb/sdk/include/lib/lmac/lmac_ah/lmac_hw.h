#ifndef _LMAC_HW_H_
#define _LMAC_HW_H_

#ifdef __cplusplus
extern "C" {
#endif

#define FSM_TXMOD        0x1
#define FSM_RXMOD        0x2

#define S1G_1M           0
#define S1G_SHORT        1
#define S1G_LONG         2
#define S1G_1M_NDP_CMAC  0
#define S1G_2M_NDP_CMAC  1

#define SF_1             0
#define SF_10            1
#define SF_1000          2
#define SF_10000         3

#define SIFS_INIT0          0       //SIFS init value1, used before Tx in AC pending
#define SIFS_INIT1          130     //SIFS init value1, used before Tx 
#define SIFS_INIT2          0       //SIFS init value2, used before Rx.//modified 20190929 hushifei
#define SIFS_INIT3          10      //SIFS init value3, used during BO. 
#define DLY_AFTER_BO        3       //20 //Delay after Backoff
//#define WAIT_RESP_TO      1500    //WAIT_ACK_TO //1M NDP 601us //tbc global var according bss_bw
//1: 115+ 40*(14-8) add 240
#ifdef TX4001A
#define WAIT_RESP_TO        (aACKTimingAlign + 115 + 50)//=375us: 115 sync irq, 52 margin
//#define WAIT_SIFS_TO        (aSIFSTime + 115 + 50)//=375us: 115 sync irq, 52 margin
#else//MARS
#define WAIT_RESP_TO        (aACKTimingAlign + 265 + 10)//=375us: 265 sync irq, 52 margin
//#define WAIT_SIFS_TO        (aSIFSTime + 265 + 20)//=375us: 265 sync irq, 52 margin
#endif
#define DTIM_PROTECT_TIME     25000 //us
#define DTIM_IDLE_TIME        1000 //us
#define ROM_START_ADDR        0x0000
#define ROM_END_ADDR          0x8000

#define RX_BUFF_GAP_0    0
#define RX_BUFF_GAP_64   1
#define RX_BUFF_GAP_128  2
#define RX_BUFF_GAP_256  3

/*
****************************************************************************************************
* lmac register definition
****************************************************************************************************
*/

struct tx_subframe {
    __IO uint32 TXADDR;
    __IO uint32 TXLEN;
};

struct rx_subframe {
    __I  uint32 RXADDR;
    __I  uint32 RXFCSLEN;
};


#if LMAC_VERSION == 43
#define LMAC_SUBF_CNT 16

struct ah_lmac_hw {
    __IO uint32 MACADDRL;
    __IO uint32 MACADDRH;
    __IO uint32 AID;
    uint32 RESERVED0;
    __IO uint32 TSFL;
    __IO uint32 TSFH;
    __IO uint32 NAV_CNT;
    __IO uint32 SIFS_INIT;
    __IO uint32 BO_CNT0;
    __IO uint32 BO_CNT1;
    uint32 RESERVED1;
    __I  uint32 FSM_TSF;
    __IO uint32 FSM_CFG;
    __I  uint32 FSM_STAT;
    __I  uint32 FSM_TSF1;
    __IO uint32 RAND_GEN;
    __IO uint32 COMN_CTRL;
    __IO uint32 IRQ_EN;
    __IO uint32 IRQ_PD;
    __IO uint32 AC_PD;
    uint32 RESERVED3;
    __I  uint32 FCS_RES;
    __IO uint32 AGGR_CTRL;
    uint32 RESERVED4[2];
    __IO uint32 TXVEC[4];
    __IO uint32 TX_STAT;
    __IO uint32 TX_DLY1;
    __IO uint32 TX_BYTCNT;
    __IO uint32 TX_EOFBYT;
    __IO uint32 TX_DLY2;
    __IO uint32 TX_PRBS_GEN;
    __IO uint32 TX_DLY3;
    uint32 RESERVED5[4];
    __IO uint32 RX_CTRL;
    __I  uint32 RXVEC[4];
    __IO uint32 RX_STAT;
    uint32 RESERVED5a;
    __IO uint32 CCA_STAT;
    __IO uint32 HF_TIMER1;
    __IO uint32 HF_TIMER2;
    __IO uint32 LF_TIMER;
    __IO uint32 TIMER_CTL;
    uint32 RESERVED6[12];
    __IO uint32 TXDMACTL;
    __I  uint32 CURTXDMACNT;
    __I  uint32 TXDMASTAT;
    uint32 RESERVED7[5];
    struct tx_subframe TXSUFRM[LMAC_SUBF_CNT];
    uint32 RESERVED8[24];
    __IO uint32 RXDMACTL;
    __IO uint32 RXFSTADDR;
    __IO uint32 RXFENADDR;
    __I  uint32 CURRXLADDR;
    __I  uint32 CURRXDMACNT;
    __I  uint32 RXDMASTAT;
    uint32 RESERVED9[2];
    struct rx_subframe RXSUFRM[LMAC_SUBF_CNT];
    __IO uint32 TEST_CTRL;
    __IO uint32 DBG_CTRL;
} ;
#endif

#if LMAC_VERSION == 46
#define LMAC_SUBF_CNT 64

struct ah_lmac_hw {
    __IO uint32 MACADDRL;
    __IO uint32 MACADDRH;
    __IO uint32 AID;
    uint32 RESERVED0;
    __IO uint32 TSFL;
    __IO uint32 TSFH;
    __IO uint32 NAV_CNT;
    __IO uint32 SIFS_INIT;
    __IO uint32 BO_CNT0;
    __IO uint32 BO_CNT1;
    uint32 RESERVED1;
    __I  uint32 FSM_TSF;
    __IO uint32 FSM_CFG;
    __I  uint32 FSM_STAT;
    __I  uint32 FSM_TSF1;
    __IO uint32 RAND_GEN;
    __IO uint32 COMN_CTRL;
    __IO uint32 IRQ_EN;
    __IO uint32 IRQ_PD;
    __IO uint32 AC_PD;
    uint32 RESERVED3;
    __I  uint32 FCS_RES;
    __IO uint32 AGGR_CTRL;
    uint32 RESERVED4[2];
    __IO uint32 TXVEC[4];
    __IO uint32 TX_STAT;
    __IO uint32 TX_DLY1;
    __IO uint32 TX_BYTCNT;
    __IO uint32 TX_EOFBYT;
    __IO uint32 TX_DLY2;
    __IO uint32 TX_PRBS_GEN;
    __IO uint32 TX_DLY3;
    uint32 RESERVED5[4];
    __IO uint32 RX_CTRL;
    __I  uint32 RXVEC[4];
    __IO uint32 RX_STAT;
    uint32 RESERVED5a;
    __IO uint32 CCA_STAT;
    __IO uint32 HF_TIMER1;
    __IO uint32 HF_TIMER2;
    __IO uint32 LF_TIMER;
    __IO uint32 TIMER_CTL;
    __IO uint32 HF_TIMER3;
    __IO uint32 HF_TIMER4;
    __IO uint32 HF_TIMER5;
    __IO uint32 HF_TIMER6;
    uint32 RESERVED6[6];
    __IO uint32 TEST_CTRL;
    __IO uint32 DBG_CTRL;
    __IO uint32 TXDMACTL;
    __I  uint32 CURTXDMACNT;
    __I  uint32 TXDMASTAT;
    uint32 RESERVED7[5];
    struct  tx_subframe TXSUFRM[LMAC_SUBF_CNT];
    uint32 RESERVED8[56];
    __IO uint32 RXDMACTL;
    __IO uint32 RXFSTADDR;
    __IO uint32 RXFENADDR;
    uint32 RESERVED9;
    __I  uint32 CURRXDMACNT;
    __I  uint32 RXDMASTAT;
    __I  uint32 RXFCS[2];
    struct   rx_subframe RXSUFRM[LMAC_SUBF_CNT];
} ;
#endif

#if LMAC_VERSION == 59
struct ah_lmac_hw {
    __IO uint32 MACADDRL;
    __IO uint32 MACADDRH;
    __IO uint32 AID;
         uint32 RESERVED0;
    __IO uint32 TSFL;
    __IO uint32 TSFH;
    __IO uint32 NAV_CNT;
    __IO uint32 SIFS_INIT;
    __IO uint32 BO_CNT0;
    __IO uint32 BO_CNT1;
         uint32 RESERVED1;
    __I  uint32 FSM_TSF;
    __IO uint32 FSM_CFG;
    __I  uint32 FSM_STAT;
    __I  uint32 FSM_TSF1;
    __IO uint32 RAND_GEN;
    __IO uint32 COMN_CTRL;
    __IO uint32 IRQ_EN;
    __IO uint32 IRQ_PD;
    __IO uint32 AC_PD;
         uint32 RESERVED3;
    __I  uint32 FCS_RES;
    __IO uint32 AGGR_CTRL;
    __IO uint32 END_TO_LIMIT;
         uint32 RESERVED4;
    __IO uint32 TXVEC[4];
    __IO uint32 TX_STAT;
    __IO uint32 TX_DLY1;
    __IO uint32 TX_BYTCNT;
    __IO uint32 TX_EOFBYT;
    __IO uint32 TX_DLY2;
    __IO uint32 TX_PRBS_GEN;
    __IO uint32 TX_DLY3;
         uint32 RESERVED5[4];
    __IO uint32 RX_CTRL;
    __I  uint32 RXVEC[4];
    __IO uint32 RX_STAT;
         uint32 RESERVED5a;
    __IO uint32 CCA_STAT;
    __IO uint32 HF_TIMER1;
    __IO uint32 HF_TIMER2;
    __IO uint32 LF_TIMER;
    __IO uint32 TIMER_CTL;
    __IO uint32 HF_TIMER3;
    __IO uint32 HF_TIMER4;
    __IO uint32 HF_TIMER5;
    __IO uint32 HF_TIMER6;
         uint32 RESERVED6[6];
    __IO uint32 TEST_CTRL;
    __IO uint32 DBG_CTRL;
    __IO uint32 TXDMACTL;
    __I  uint32 CURTXDMACNT;
    __I  uint32 TXDMASTAT;
         uint32 RESERVED7[5];
    struct tx_subframe TXSUFRM[64];
         uint32 RESERVED8[56];
    __IO uint32 RXDMACTL;
    __IO uint32 RXFSTADDR;
    __IO uint32 RXFENADDR;
         uint32 RESERVED9;
    __I  uint32 CURRXDMACNT;
    __I  uint32 RXDMASTAT;
    __I  uint32 RXFCS[2];
    struct rx_subframe RXSUFRM[64];
    __IO uint32 RXFSTADDR_SEC;
    __IO uint32 RXFENADDR_SEC;
         uint32 RESERVED10[2];
    __IO uint32 CCADBGCTL;
    __I  uint32 CCAINFO[5];
    __IO uint32 DUMMY[2];
} ;
#endif

extern struct ah_lmac_hw *LMAC;

/*
****************************************************************************************************
* lmac register definition
****************************************************************************************************
*/
#define AID_AID_MSK                         0x00001fff
#define AID_AID_SHIFT                       0
#define NAC_CNT_NAV_MSK                     0x0000ffff
#define NAC_CNT_NAV_SHIFT                   0
#define SIFS_INIT_INIT1_MSK                 0x000000ff
#define SIFS_INIT_INIT1_SHIFT               0
#define SIFS_INIT_INIT2_MSK                 0x00ffff00
#define SIFS_INIT_INIT2_SHIFT               8
#define SIFS_INIT_INIT3_MSK                 0xff000000
#define SIFS_INIT_INIT3_SHIFT               24
#define BO_CNT0_BO_BK_MSK                   0x000007ff
#define BO_CNT0_BO_BK_SHIFT                 0
#define BO_CNT0_BK_EN_MSK                   0x00000800
#define BO_CNT0_BK_EN_SHIFT                 11
#define BO_CNT0_BK_AIFS_MSK                 0x0000f000
#define BO_CNT0_BK_AIFS_SHIFT               12
#define BO_CNT0_BO_BE_MSK                   0x07ff0000
#define BO_CNT0_BO_BE_SHIFT                 16
#define BO_CNT0_BE_EN_MSK                   0x08000000
#define BO_CNT0_BE_EN_SHIFT                 27
#define BO_CNT0_BE_AIFS_MSK                 0xf0000000
#define BO_CNT0_BE_AIFS_SHIFT               28
#define BO_CNT1_BO_VI_MSK                   0x000007ff
#define BO_CNT1_BO_VI_SHIFT                 0
#define BO_CNT1_VI_EN_MSK                   0x00000800
#define BO_CNT1_VI_EN_SHIFT                 11
#define BO_CNT1_VI_AIFS_MSK                 0x0000f000
#define BO_CNT1_VI_AIFS_SHIFT               12
#define BO_CNT1_BO_VO_MSK                   0x07ff0000
#define BO_CNT1_BO_VO_SHIFT                 16
#define BO_CNT1_VO_EN_MSK                   0x08000000
#define BO_CNT1_VO_EN_SHIFT                 27
#define BO_CNT1_VO_AIFS_MSK                 0xf0000000
#define BO_CNT1_VO_AIFS_SHIFT               28
#define FSM_CFG_ST_MSK                      0x00000001
#define FSM_CFG_ST_SHIFT                    0
#define FSM_CFG_ABT_MSK                     0x00000002
#define FSM_CFG_ABT_SHIFT                   1
#define FSM_CFG_MOD_MSK                     0x00000030
#define FSM_CFG_MOD_SHIFT                   4
#define FSM_CFG_CCA_BYP_MSK                 0x00000100
#define FSM_CFG_CCA_BYP_SHIFT               8
#define FSM_CFG_AIFS_FEN_MSK                0x00000200
#define FSM_CFG_AIFS_FEN_SHIFT              9
#define FSM_CFG_BO_FEN_MSK                  0x00000400
#define FSM_CFG_BO_FEN_SHIFT                10
#define FSM_CFG_CCA_SIFS_CARE_MSK           0x00000800
#define FSM_CFG_CCA_SIFS_CARE_SHIFT         11
#define FSM_CFG_TXVEC_RDY_MSK               0x00001000
#define FSM_CFG_TXVEC_RDY_SHIFT             12
#define FSM_CFG_CCA_SYNC_CARE_BUSY_MSK      0x00002000
#define FSM_CFG_CCA_SYNC_CARE_BUSY_SHIFT    13
#define FSM_STAT_TXD_STAT_MSK               0x0000000f
#define FSM_STAT_TXD_STAT_SHIFT             0
#define FSM_STAT_TXT_STAT_MSK               0x000000f0
#define FSM_STAT_TXT_STAT_SHIFT             4
#define FSM_STAT_TXP_STAT_MSK               0x00000f00
#define FSM_STAT_TXP_STAT_SHIFT             8
#define RAND_GEN_SEED_MSK                   0x00007fff
#define RAND_GEN_SEED_SHIFT                 0
#define COMN_CTRL_BA_PRO_EN_MSK             0x00000001
#define COMN_CTRL_BA_PRO_EN_SHIFT           0
#define COMN_CTRL_FPGAMOD_MSK               0x00000002
#define COMN_CTRL_FPGAMOD_SHIFT             1
#define COMN_CTRL_BSS_BW_MSK                0x00000030
#define COMN_CTRL_BSS_BW_SHIFT              4
#define COMN_CTRL_DYN_BW_EN_MSK             0x00000040
#define COMN_CTRL_DYN_BW_EN_SHIFT           6
#define COMN_CTRL_DOZ_EN_MSK                0x00000080
#define COMN_CTRL_DOZ_EN_SHIFT              7
#define COMN_CTRL_RF_EN_MSK                 0x00000100
#define COMN_CTRL_RF_EN_SHIFT               8
#define COMN_CTRL_RF_SW_CTRL_MSK            0x00000200
#define COMN_CTRL_RF_SW_CTRL_SHIFT          9
#define COMN_CTRL_RF_TXEN_MSK               0x00000400
#define COMN_CTRL_RF_TXEN_SHIFT             10
#define COMN_CTRL_RF_RXEN_MSK               0x00000800
#define COMN_CTRL_RF_RXEN_SHIFT             11
#if LMAC_VERSION >= 46
#define COMN_CTRL_RXEN_CCA_MSK              0x00001000
#define COMN_CTRL_RXEN_CCA_SHIFT            12
#define COMN_CTRL_CCA_UPDAT_BW_EN_MSK       0x00002000
#define COMN_CTRL_CCA_UPDAT_BW_EN_SHIFT     13
#define COMN_CTRL_RX_UPDAT_BW_EN_MSK        0x00004000
#define COMN_CTRL_RX_UPDAT_BW_EN_SHIFT      14
#define COMN_CTRL_RX_UPDAT_NDP_EN_MSK       0x00008000
#define COMN_CTRL_RX_UPDAT_NDP_EN_SHIFT     15
#define COMN_CTRL_RF_PAEN_MSK               0x00010000
#define COMN_CTRL_RF_PAEN_SHIFT             16
#if LMAC_VERSION >= 59
#define COMN_CTRL_DAC_EN_MSK                BIT(17)
#define COMN_CTRL_FCS_ALIGN_APEP_MSK        BIT(18)
#endif
#endif

#define IRQ_EN_TXVEC2_EN_MSK                0x00000001
#define IRQ_EN_TXVEC2_EN_SHIFT              0
#define IRQ_EN_TX_ERR_EN_MSK                0x00000002
#define IRQ_EN_TX_ERR_EN_SHIFT              1
#define IRQ_EN_TX_END_EN_MSK                0x00000004
#define IRQ_EN_TX_END_EN_SHIFT              2
#define IRQ_EN_BO_ST_EN_MSK                 0x00000010
#define IRQ_EN_BO_ST_EN_SHIFT               4
#define IRQ_EN_BO_FNS_EN_MSK                0x00000020
#define IRQ_EN_BO_FNS_EN_SHIFT              5
#define IRQ_EN_BO_NEAR_END_EN_MSK           0x00000040
#define IRQ_EN_BO_NEAR_END_EN_SHIFT         6
#define IRQ_EN_AC_PD_EN_MSK                 0x00000080
#define IRQ_EN_AC_PD_EN_SHIFT               7
#define IRQ_EN_SYNC_IRQ_EN_MSK              0x00000100
#define IRQ_EN_SYNC_IRQ_EN_SHIFT            8
#define IRQ_EN_RX_HDR_EN_MSK                0x00000200
#define IRQ_EN_RX_HDR_EN_SHIFT              9
#define IRQ_EN_RX_END_EN_MSK                0x00000400
#define IRQ_EN_RX_END_EN_SHIFT              10
#define IRQ_EN_DEAGG_ERR_EN_MSK             0x00000800
#define IRQ_EN_DEAGG_ERR_EN_SHIFT           11
#define IRQ_EN_RXSUBF_EN_MSK                0x00001000
#define IRQ_EN_RXSUBF_EN_SHIFT              12
#define IRQ_EN_HT1_EN_MSK                   0x00002000
#define IRQ_EN_HT1_EN_SHIFT                 13
#define IRQ_EN_HT2_EN_MSK                   0x00004000
#define IRQ_EN_HT2_EN_SHIFT                 14
#define IRQ_EN_LT_EN_MSK                    0x00008000
#define IRQ_EN_LT_EN_SHIFT                  15
#if LMAC_VERSION >= 46
#define IRQ_EN_HT3_EN_MSK                   0x00010000
#define IRQ_EN_HT3_EN_SHIFT                 16
#define IRQ_EN_HT4_EN_MSK                   0x00020000
#define IRQ_EN_HT4_EN_SHIFT                 17
#define IRQ_EN_HT5_EN_MSK                   0x00040000
#define IRQ_EN_HT5_EN_SHIFT                 18
#define IRQ_EN_HT6_EN_MSK                   0x00080000
#define IRQ_EN_HT6_EN_SHIFT                 19
#endif
#if LMAC_VERSION >= 59
#define IRQ_EN_END_TO_EN_MSK                BIT(20)
#define IRQ_EN_PD_NOT_CARE_IEN              BIT(31)
#endif

#define IRQ_PD_TXVEC2_PD_MSK                0x00000001
#define IRQ_PD_TXVEC2_PD_SHIFT              0
#define IRQ_PD_TX_ERR_PD_MSK                0x00000002
#define IRQ_PD_TX_ERR_PD_SHIFT              1
#define IRQ_PD_TX_END_PD_MSK                0x00000004
#define IRQ_PD_TX_END_PD_SHIFT              2
#define IRQ_PD_BO_ST_PD_MSK                 0x00000010
#define IRQ_PD_BO_ST_PD_SHIFT               4
#define IRQ_PD_BO_FNS_PD_MSK                0x00000020
#define IRQ_PD_BO_FNS_PD_SHIFT              5
#define IRQ_PD_BO_NEAR_END_PD_MSK           0x00000040
#define IRQ_PD_BO_NEAR_END_PD_SHIFT         6
#define IRQ_PD_AC_PD_PD_MSK                 0x00000080
#define IRQ_PD_AC_PD_PD_SHIFT               7
#define IRQ_PD_SYNC_IRQ_PD_MSK              0x00000100
#define IRQ_PD_SYNC_IRQ_PD_SHIFT            8
#define IRQ_PD_RX_HDR_PD_MSK                0x00000200
#define IRQ_PD_RX_HDR_PD_SHIFT              9
#define IRQ_PD_RX_END_PD_MSK                0x00000400
#define IRQ_PD_RX_END_PD_SHIFT              10
#define IRQ_PD_DEAGG_ERR_PD_MSK             0x00000800
#define IRQ_PD_DEAGG_ERR_PD_SHIFT           11
#define IRQ_PD_RXSUBF_PD_MSK                0x00001000
#define IRQ_PD_RXSUBF_PD_SHIFT              12
#define IRQ_PD_HT1_PD_MSK                   0x00002000
#define IRQ_PD_HT1_PD_SHIFT                 13
#define IRQ_PD_HT2_PD_MSK                   0x00004000
#define IRQ_PD_HT2_PD_SHIFT                 14
#define IRQ_PD_LT_PD_MSK                    0x00008000
#define IRQ_PD_LT_PD_SHIFT                  15
#if LMAC_VERSION >= 46
#define IRQ_PD_HT3_PD_MSK                   0x00010000
#define IRQ_PD_HT3_PD_SHIFT                 16
#define IRQ_PD_HT4_PD_MSK                   0x00020000
#define IRQ_PD_HT4_PD_SHIFT                 17
#define IRQ_PD_HT5_PD_MSK                   0x00040000
#define IRQ_PD_HT5_PD_SHIFT                 18
#define IRQ_PD_HT6_PD_MSK                   0x00080000
#define IRQ_PD_HT6_PD_SHIFT                 19
#endif
#if LMAC_VERSION >= 59
#define IRQ_PD_END_TO_PD_MSK                BIT(20)
#endif

#define AC_PD_BK_PD_MSK                     0x00000001
#define AC_PD_BK_PD_SHIFT                   0
#define AC_PD_BE_PD_MSK                     0x00000002
#define AC_PD_BE_PD_SHIFT                   1
#define AC_PD_VI_PD_MSK                     0x00000004
#define AC_PD_VI_PD_SHIFT                   2
#define AC_PD_VO_PD_MSK                     0x00000008
#define AC_PD_VO_PD_SHIFT                   3
#define AGGR_CTRL_AGGREG_MSK                0x00000001
#define AGGR_CTRL_AGGREG_SHIFT              0
#define AGGR_CTRL_EOF_MSK                   0x00000002
#define AGGR_CTRL_EOF_SHIFT                 1
#define AGGR_CTRL_LEN0SFC_MSK               0x000000f0
#define AGGR_CTRL_LEN0SFC_SHIFT             4

#if LMAC_VERSION >= 59
#define END_TO_LIMIT_MSK                    0xffff
#define END_TO_LIMIT_SHIFT                  0
#endif
#define TXVEC0_TXPWRLVL_MSK                 0x0000001f
#define TXVEC0_TXPWRLVL_SHIFT               0
#define TXVEC0_NDP_IND_MSK                  0x00000020
#define TXVEC0_NDP_IND_SHIFT                5
#define TXVEC0_SIGBW_MSK                    0x000000c0
#define TXVEC0_SIGBW_SHIFT                  6
#define TXVEC0_TXMDMBW_MSK                  0x00000300
#define TXVEC0_TXMDMBW_SHIFT                8
#define TXVEC0_TXFRMTYP_MSK                 0x00000c00
#define TXVEC0_TXFRMTYP_SHIFT               10
#define TXVEC0_MCS_MSK                      0x0000f000
#define TXVEC0_MCS_SHIFT                    12
#define TXVEC0_SRCM_INIT_MSK                0x007f0000
#define TXVEC0_SRCM_INIT_SHIFT              16
#define TXVEC0_DUPEN_MSK                    0x00800000
#define TXVEC0_DUPEN_SHIFT                  23
#define TXVEC1_NSYM_MSK                     0x000003ff
#define TXVEC1_NSYM_SHIFT                   0
#define TX_STAT_PHY_TXERR_MSK               0x00000001
#define TX_STAT_PHY_TXERR_SHIFT             0
#define TX_STAT_END_EARLY_ERR_MSK           0x00000002
#define TX_STAT_END_EARLY_ERR_SHIFT         1
#define TX_DLY1_DELAY_8M_MSK                0x0000001f
#define TX_DLY1_DELAY_8M_SHIFT              0
#define TX_DLY1_DELAY_4M_MSK                0x000003e0
#define TX_DLY1_DELAY_4M_SHIFT              5
#define TX_DLY1_DELAY_2M_MSK                0x00007c00
#define TX_DLY1_DELAY_2M_SHIFT              10
#define TX_DLY1_DELAY_1M_MSK                0x00007c00
#define TX_DLY1_DELAY_1M_SHIFT              15
#define TX_DLY1_BO_DLY_MSK                  0xff000000
#define TX_DLY1_BO_DLY_SHIFT                24
#define TX_BYTCNT_BYT_CNT_MSK               0x0001ffff
#define TX_BYTCNT_BYT_CNT_SHIFT             0
#define TX_DLY2_DELAY_8M_2_MSK              0x0000003f
#define TX_DLY2_DELAY_8M_2_SHIFT            0
#define TX_DLY2_DELAY_4M_2_MSK              0x00003f00
#define TX_DLY2_DELAY_4M_2_SHIFT            8
#define TX_DLY2_DELAY_2M_2_MSK              0x003f0000
#define TX_DLY2_DELAY_2M_2_SHIFT            16
#define TX_DLY2_DELAY_1M_2_MSK              0x3f000000
#define TX_DLY2_DELAY_1M_2_SHIFT            24
#define TX_PRBS_GEN_PRBS_EN_MSK             0x00000001
#define TX_PRBS_GEN_PRBS_EN_SHIFT           0
#define TX_PRBS_GEN_SEED_MSK                0x0007fff0
#define TX_PRBS_GEN_SEED_SHIFT              4
#define TX_DLY3_RF_TX_DLY_MSK               0x0000000f
#define TX_DLY3_RF_TX_DLY_SHIFT             0
#define TX_DLY3_AD9361EN_DLY_MSK            0x00000030
#define TX_DLY3_AD9361EN_DLY_SHIFT          4
#define TX_DLY3_DAC_DLY_MSK                 0x00000f00
#define TX_DLY3_DAC_DLY_SHIFT               8
#if LMAC_VERSION >= 46
#define TX_DLY3_PA_DLY_MSK                  0x0001f000
#define TX_DLY3_PA_DLY_SHIFT                12
#endif

#define RX_CTRL_CCA_TO_EN_MSK               0x00000001
#define RX_CTRL_CCA_TO_EN_SHIFT             0
#define RX_CTRL_SYNC_TO_EN_MSK              0x00000002
#define RX_CTRL_SYNC_TO_EN_SHIFT            1
#define RX_CTRL_RX_FLT_MSK                  0x00000004
#define RX_CTRL_RX_FLT_SHIFT                2
#define RX_CTRL_HDR_THRD_MSK                0x000001f0
#define RX_CTRL_HDR_THRD_SHIFT              4
#define RX_CTRL_CCA_WINSIZE_MSK             0x0000fe00
#define RX_CTRL_CCA_WINSIZE_SHIFT           9
#define RX_CTRL_SYNC_WINSIZE_MSK            0x01ff0000
#define RX_CTRL_SYNC_WINSIZE_SHIFT          16
#define RX_CTRL_RX_DLY_MSK                  0xf0000000
#define RX_CTRL_RX_DLY_SHIFT                28
#define RXVEC3_RCPI_MSK                     0x0000000f
#define RXVEC3_RCPI_SHIFT                   0
#define RXVEC3_EVM1_MSK                     0x000000f0
#define RXVEC3_EVM1_SHIFT                   8
#define RX_STAT_SYNC_TO_MSK                 0x00000001
#define RX_STAT_SYNC_TO_SHIFT               0
#define RX_STAT_CCA_TO_MSK                  0x00000002
#define RX_STAT_CCA_TO_SHIFT                1
#define RX_STAT_PHY_ERR_MSK                 0x00000004
#define RX_STAT_PHY_ERR_SHIFT               2
#define RX_STAT_RX_FIFO_ERR_MSK             0x00000008
#define RX_STAT_RX_FIFO_ERR_SHIFT           3
#define RX_STAT_ADDR_MISM_MSK               0x00000010
#define RX_STAT_ADDR_MISM_SHIFT             4
#define RX_STAT_RXDMAOF_MSK                 0x00000020
#define RX_STAT_RXDMAOF_SHIFT               5
#define RX_STAT_RXSIGBW_MSK                 0x000000c0
#define RX_STAT_RXSIGBW_SHIFT               6
#define RX_STAT_PRI_BW_MSK                  0x00000100
#define RX_STAT_PRI_BW_SHIFT                8
#define RX_STAT_LONG_MSK                    0x00000200
#define RX_STAT_LONG_SHIFT                  9
#define RX_STAT_BW_ERR_MSK                  0x00000400
#define RX_STAT_BW_ERR_SHIFT                10
#define RX_STAT_ABT_TX_MSK                  0x00000800
#define RX_STAT_ABT_TX_SHIFT                11
#define RX_STAT_ABT_RX_MSK                  0x00001000
#define RX_STAT_ABT_RX_SHIFT                12
#define RX_STAT_RXDUPBW_MSK                 0x00006000
#define RX_STAT_RXDUPBW_SHIFT               13
#define RX_STAT_END_ERR_MSK                 0x00008000
#define RX_STAT_END_ERR_SHIFT               15
#define CCA_STAT_PRI1_MSK                   0x00000001
#define CCA_STAT_PRI1_SHIFT                 0
#define CCA_STAT_PRI2_MSK                   0x00000002
#define CCA_STAT_PRI2_SHIFT                 1
#define CCA_STAT_SEC2_MSK                   0x00000004
#define CCA_STAT_SEC2_SHIFT                 2
#define CCA_STAT_SEC4_MSK                   0x00000008
#define CCA_STAT_SEC4_SHIFT                 3
#define CCA_STAT_BK_NEAREND_PD_MSK          0x00000010
#define CCA_STAT_BK_NEAREND_PD_SHIFT        4
#define CCA_STAT_BE_NEAREND_PD_MSK          0x00000020
#define CCA_STAT_BE_NEAREND_PD_SHIFT        5
#define CCA_STAT_VI_NEAREND_PD_MSK          0x00000040
#define CCA_STAT_VI_NEAREND_PD_SHIFT        6
#define CCA_STAT_VO_NEAREND_PD_MSK          0x00000080
#define CCA_STAT_VO_NEAREND_PD_SHIFT        7
#define CCA_STAT_BK_FNS_PD_MSK              0x00000100
#define CCA_STAT_BK_FNS_PD_SHIFT            8
#define CCA_STAT_BE_FNS_PD_MSK              0x00000200
#define CCA_STAT_BE_FNS_PD_SHIFT            9
#define CCA_STAT_VI_FNS_PD_MSK              0x00000400
#define CCA_STAT_VI_FNS_PD_SHIFT            10
#define CCA_STAT_VO_FNS_PD_MSK              0x00000800
#define CCA_STAT_VO_FNS_PD_SHIFT            11
#define LF_TIMER_IV_MSK                     0x0fffffff
#define LF_TIMER_IV_SHIFT                   0
#define LF_TIMER_SF_MSK                     0xc0000000
#define LF_TIMER_SF_SHIFT                   30
#define TIMER_CTL_HF1_ST_MSK                0x00000001
#define TIMER_CTL_HF1_ST_SHIFT              0
#define TIMER_CTL_HF1_ABT_MSK               0x00000002
#define TIMER_CTL_HF1_ABT_SHIFT             1
#define TIMER_CTL_HF2_ST_MSK                0x00000004
#define TIMER_CTL_HF2_ST_SHIFT              2
#define TIMER_CTL_HF2_ABT_MSK               0x00000008
#define TIMER_CTL_HF2_ABT_SHIFT             3
#define TIMER_CTL_LF_ST_MSK                 0x00000010
#define TIMER_CTL_LF_ST_SHIFT               4
#define TIMER_CTL_LF_ABT_MSK                0x00000020
#define TIMER_CTL_LF_ABT_SHIFT              5
#if LMAC_VERSION >= 46
#define TIMER_CTL_HF3_ST_MSK                0x00000040
#define TIMER_CTL_HF3_ST_SHIFT              6
#define TIMER_CTL_HF3_ABT_MSK               0x00000080
#define TIMER_CTL_HF3_ABT_SHIFT             7
#define TIMER_CTL_HF4_ST_MSK                0x00000100
#define TIMER_CTL_HF4_ST_SHIFT              8
#define TIMER_CTL_HF4_ABT_MSK               0x00000200
#define TIMER_CTL_HF4_ABT_SHIFT             9
#define TIMER_CTL_HF5_ST_MSK                0x00000400
#define TIMER_CTL_HF5_ST_SHIFT              10
#define TIMER_CTL_HF5_ABT_MSK               0x00000800
#define TIMER_CTL_HF5_ABT_SHIFT             11
#define TIMER_CTL_HF6_ST_MSK                0x00001000
#define TIMER_CTL_HF6_ST_SHIFT              12
#define TIMER_CTL_HF6_ABT_MSK               0x00002000
#define TIMER_CTL_HF6_ABT_SHIFT             13
#endif

#if LMAC_VERSION == 43
#define TXDMACTL_LSTCNT_MSK                 0x0000003e
#define TXDMACTL_LSTCNT_SHIFT               1
#endif
#if LMAC_VERSION >= 46
#define TXDMACTL_LSTCNT_MSK                 0x0000007f
#define TXDMACTL_LSTCNT_SHIFT               0
#endif

#define CURTXDMACNT_CURCNT_MSK              0x00003fff
#define CURTXDMACNT_CURCNT_SHIFT            0
#define CURTXDMACNT_CURREM_MSK              0x3fff0000
#define CURTXDMACNT_CURREM_SHIFT            16

#if LMAC_VERSION == 43
#define TXDMASTAT_CURLSTIDX_MSK             0x0000001f
#define TXDMASTAT_CURLSTIDX_SHIFT           0
#endif
#if LMAC_VERSION >= 46
#define TXDMASTAT_CURLSTIDX_MSK             0x0000007f
#define TXDMASTAT_CURLSTIDX_SHIFT           0
#endif

#define TXLEN_LEN_MSK                       0x0001ffff
#define TXLEN_LEN_SHIFT                     0

#if LMAC_VERSION >= 59
#define RXDMACTL_SEC_BUF_VALID_MSK          BIT(1)
#else
#define RXDMACTL_RELOAD_MSK                 0x00000002
#define RXDMACTL_RELOAD_SHIFT               1
#endif
#define RXDMACTL_BGAP_MSK                   0x0000000c
#define RXDMACTL_BGAP_SHIFT                 2

#define CURRXDMACNT_CURCNT_MSK              0x00003fff
#define CURRXDMACNT_CURCNT_SHIFT            0
#define CURRXDMACNT_CURREM_MSK              0x3fff0000
#define CURRXDMACNT_CURREM_SHIFT            16

#if LMAC_VERSION == 43
#define RXDMASTAT_LSTCNT_MSK                0x0000003e
#define RXDMASTAT_LSTCNT_SHIFT              1
#define RXDMASTAT_FCS_RES_MSK               0xffff0000
#define RXDMASTAT_FCS_RES_SHIFT             16
#endif
#if LMAC_VERSION >= 46
#define RXDMASTAT_LSTCNT_MSK                0x0000007f
#define RXDMASTAT_LSTCNT_SHIFT              0
#endif

#define RXFCSLEN_LEN_MSK                    0x00003fff
#define RXFCSLEN_LEN_SHIFT                  0
#define RXFCSLEN_FCS_MSK                    0x00004000
#define RXFCSLEN_FCS_SHIFT                  14
#define TEST_CTRL_TX_TSTEN_MSK              0x00000001
#define TEST_CTRL_TX_TSTEN_SHIFT            0
#define TEST_CTRL_RX_TSTEN_MSK              0x00000002
#define TEST_CTRL_RX_TSTEN_SHIFT            1
#define TEST_CTRL_RX_LEN_MSK                0x0007fffc
#define TEST_CTRL_RX_LEN_SHIFT              2
#define DBG_CTRL_DBG_MOD_MSK                0x00000007
#define DBG_CTRL_DBG_MOD_SHIFT              0

#if LMAC_VERSION >= 59
#define CCADBGCTL_CLR_CCA_RECORD_MSK        BIT(0)
#define CCADBGCTL_CCA_PERIOD_SHIFT          1
#define CCADBGCTL_CCA_PERIOD_MSK           (0x7<<CCADBGCTL_CCA_PERIOD_SHIFT)
#define CCADBGCTL_CCA_OBSERVATION_DONE_MSK  BIT(4)

#define CCAINFO0_PRI1START_SHIFT            0
#define CCAINFO0_PRI1START_MSK             (0xffffUL<<CCAINFO0_PRI1START_SHIFT)
#define CCAINFO0_PRI2START_SHIFT            16
#define CCAINFO0_PRI2START_MSK             (0xffffUL<<CCAINFO0_PRI2START_SHIFT)

#define CCAINFO1_PRI1MID_SHIFT              0
#define CCAINFO1_PRI1MID_MSK               (0xffffUL<<CCAINFO1_PRI1MID_SHIFT)
#define CCAINFO1_PRI2MID_SHIFT              16
#define CCAINFO1_PRI2MID_MSK               (0xffffUL<<CCAINFO1_PRI2MID_SHIFT)

#define CCAINFO2_SEC2MID_SHIFT              0
#define CCAINFO2_SEC2MID_MSK               (0xffffUL<<CCAINFO2_SEC2MID_SHIFT)
#define CCAINFO2_SEC4MID_SHIFT              16
#define CCAINFO2_SEC4MID_MSK               (0xffffUL<<CCAINFO2_SEC4MID_SHIFT)

#define CCAINFO3_PRI1ED_SHIFT               0
#define CCAINFO3_PRI1ED_MSK                (0xffffUL<<CCAINFO3_PRI1ED_SHIFT)
#define CCAINFO3_PRI2ED_SHIFT               16
#define CCAINFO3_PRI2ED_MSK                (0xffffUL<<CCAINFO3_PRI2ED_SHIFT)

#define CCAINFO4_SEC2ED_SHIFT               0
#define CCAINFO4_SEC2ED_MSK                (0xffffUL<<CCAINFO4_SEC2ED_SHIFT)
#define CCAINFO4_SEC4ED_SHIFT               16
#define CCAINFO4_SEC4ED_MSK                (0xffffUL<<CCAINFO4_SEC4ED_SHIFT)
#endif

#define GET_LMAC_TSFL()         (LMAC->TSFL)
#define GET_LMAC_TSFH()         (LMAC->TSFH)
#define CFG_LMAC_TSFLH(val)     do{\
                                    LMAC->TSFL = (val) & 0xffffffff;\
                                    LMAC->TSFH = ((val) >> 32) & 0xffffffff;\
                                }while(0)
#define LHW_INIT_REG_AC()       (LMAC->AC_PD = 0)
#define LHW_CLR_REG_AC(ac)      (LMAC->AC_PD &= ~(0x01 << (ac)))
#define LHW_CLR_CCA_STAT()      (LMAC->CCA_STAT = 0x0ff0)
#define LHW_CLR_CCA_CFG()       (LMAC->BO_CNT0 = 0x00)
#define LHW_GET_NDP_TYPE()      ((LMAC->RXVEC[0]) & 0x07)
#define LHW_GET_RX_VEC(n)       (LMAC->RXVEC[n])
//#define LHW_GET_RX_SA()         (LMAC->RXFSTADDR)
#define LHW_GET_SUB_FRM_NUM()   ((LMAC->RXDMASTAT & RXDMASTAT_LSTCNT_MSK) >> RXDMASTAT_LSTCNT_SHIFT)
#define LHW_GET_SUB_FRM_ADDR(n) (LMAC->RXSUFRM[n].RXADDR)
#define LHW_GET_SUB_FRM_LEN(n)  (LMAC->RXSUFRM[n].RXFCSLEN&RXFCSLEN_LEN_MSK) 
#define LHW_GET_SUB_FRM_FCS(n)  (LMAC->RXSUFRM[n].RXFCSLEN&RXFCSLEN_FCS_MSK)
#define LHW_GET_NDP_1M()        (LMAC->RXVEC[0])
#define LHW_GET_RX_STAT()       (LMAC->RX_STAT)
#define LHW_CFG_TX_VEC(n,val)   (LMAC->TXVEC[n] = (val))
#define LHW_GET_TX_VEC(n)       (LMAC->TXVEC[n])
#define LHW_GET_FCS()           (LMAC->FCS_RES)
#define LHW_GET_TX_PWR()        ((LMAC->TXVEC[0] & TXVEC0_TXPWRLVL_MSK) >> TXVEC0_TXPWRLVL_SHIFT)
#define LHW_GET_TX_SRCM_INIT()  ((LMAC->TXVEC[0] & TXVEC0_SRCM_INIT_MSK) >> TXVEC0_SRCM_INIT_SHIFT)
#define LHW_GET_TX_MCS()        ((LMAC->TXVEC[0] & TXVEC0_MCS_MSK) >> TXVEC0_MCS_SHIFT)
#define LHW_GET_TX_SIGBW()      ((LMAC->TXVEC[0] & TXVEC0_SIGBW_MSK) >> TXVEC0_SIGBW_SHIFT)
#define LHW_GET_TX_FRMTYP()     ((LMAC->TXVEC[0] & TXVEC0_TXFRMTYP_MSK) >> TXVEC0_TXFRMTYP_SHIFT)
#define LHW_GET_TX_TS()         (LMAC->FSM_TSF)
#define LHW_GET_RX_SYNC_TS()    (LMAC->FSM_TSF)
#define LHW_START_FSM()         (LMAC->FSM_CFG |= FSM_CFG_ST_MSK)
#define LHW_ABORT_FSM()         (LMAC->FSM_CFG |= FSM_CFG_ABT_MSK)
#define LHW_GET_RX_START_ADDR()     (LMAC->RXFSTADDR)
#define LHW_GET_RX_STOP_ADDR()      (LMAC->RXFENADDR)
#define LHW_CFG_RX_START_ADDR(val)  (LMAC->RXFSTADDR = (val))
#define LHW_CFG_RX_STOP_ADDR(val)   (LMAC->RXFENADDR = (val))
#define LHW_CLR_IRQ_AC()        (LMAC->IRQ_EN &= ~IRQ_EN_AC_PD_EN_MSK)
#define LHW_CFG_RAND_SEED()     (LMAC->RAND_GEN = LMAC->TSFL)
#define LHW_GET_RAND_NUM(max)   (LMAC->RAND_GEN % (max))
#define LHW_GET_REG_AC()        (LMAC->AC_PD & 0x0f)
#define LHW_GET_REG_AC_BIT(ac)  (LMAC->AC_PD & (1<<(ac)))
#define LHW_CFG_REG_AC(val)     (LMAC->AC_PD = (val))
#define LHW_GET_BIT_AC_BK()     ((LMAC->AC_PD & AC_PD_BK_PD_MSK) >> AC_PD_BK_PD_SHIFT)
#define LHW_GET_BIT_AC_BE()     ((LMAC->AC_PD & AC_PD_BE_PD_MSK) >> AC_PD_BE_PD_SHIFT)
#define LHW_GET_BIT_AC_VI()     ((LMAC->AC_PD & AC_PD_VI_PD_MSK) >> AC_PD_VI_PD_SHIFT)
#define LHW_GET_BIT_AC_VO()     ((LMAC->AC_PD & AC_PD_VO_PD_MSK) >> AC_PD_VO_PD_SHIFT)
#define LHW_GET_RXP_STAT()      ((LMAC->FSM_STAT & 0x07000000) >> 24)
#define LHW_GET_TXP_STAT()      ((LMAC->FSM_STAT & 0x00000700) >> 8)
#define LHW_GET_FSM_STAT()      (LMAC->FSM_STAT)
#define RXP_STAT_SYNCDET        (0x01)
#define LHW_CFG_HF_TIMER1(val)  (LMAC->HF_TIMER1 = (val))
#define LHW_GET_HF_TIMER1()     (LMAC->HF_TIMER1)
#define LHW_START_HF_TIMER1()   (LMAC->TIMER_CTL |= TIMER_CTL_HF1_ST_MSK)
#define LHW_ABORT_HF_TIMER1()   (LMAC->TIMER_CTL |= TIMER_CTL_HF1_ABT_MSK)
#define LHW_CFG_HF_TIMER2(val)  (LMAC->HF_TIMER2 = (val))
#define LHW_GET_HF_TIMER2()     (LMAC->HF_TIMER2)
#define LHW_START_HF_TIMER2()   (LMAC->TIMER_CTL |= TIMER_CTL_HF2_ST_MSK)
#define LHW_ABORT_HF_TIMER2()   (LMAC->TIMER_CTL |= TIMER_CTL_HF2_ABT_MSK)
#define LHW_CFG_HF_TIMER3(val)  (LMAC->HF_TIMER3 = (val))
#define LHW_GET_HF_TIMER3()     (LMAC->HF_TIMER3)
#define LHW_START_HF_TIMER3()   (LMAC->TIMER_CTL |= TIMER_CTL_HF3_ST_MSK)
#define LHW_ABORT_HF_TIMER3()   (LMAC->TIMER_CTL |= TIMER_CTL_HF3_ABT_MSK)
#define LHW_CFG_HF_TIMER4(val)  (LMAC->HF_TIMER4 = (val))
#define LHW_GET_HF_TIMER4()     (LMAC->HF_TIMER4)
#define LHW_START_HF_TIMER4()   (LMAC->TIMER_CTL |= TIMER_CTL_HF4_ST_MSK)
#define LHW_ABORT_HF_TIMER4()   (LMAC->TIMER_CTL |= TIMER_CTL_HF4_ABT_MSK)
#define LHW_CFG_HF_TIMER5(val)  (LMAC->HF_TIMER5 = (val))
#define LHW_GET_HF_TIMER5()     (LMAC->HF_TIMER5)
#define LHW_START_HF_TIMER5()   (LMAC->TIMER_CTL |= TIMER_CTL_HF5_ST_MSK)
#define LHW_ABORT_HF_TIMER5()   (LMAC->TIMER_CTL |= TIMER_CTL_HF5_ABT_MSK)
#define LHW_CFG_HF_TIMER6(val)  (LMAC->HF_TIMER6 = (val))
#define LHW_GET_HF_TIMER6()     (LMAC->HF_TIMER6)
#define LHW_START_HF_TIMER6()   (LMAC->TIMER_CTL |= TIMER_CTL_HF6_ST_MSK)
#define LHW_ABORT_HF_TIMER6()   (LMAC->TIMER_CTL |= TIMER_CTL_HF6_ABT_MSK)
#define LHW_CFG_LF_TIMER(val)   (LMAC->LF_TIMER |= ((val) & LF_TIMER_IV_MSK))
#define LHW_CFG_LF_SCALE(val)   (LMAC->LF_TIMER |= ((val) << LF_TIMER_SF_SHIFT))
#define LHW_GET_LF_TIMER()      (LMAC->LF_TIMER & LF_TIMER_IV_MSK)
#define LHW_START_LF_TIMER()    (LMAC->TIMER_CTL |= TIMER_CTL_LF_ST_MSK)
#define LHW_ABORT_LF_TIMER()    (LMAC->TIMER_CTL |= TIMER_CTL_LF_ABT_MSK)
#define LHW_SET_AIFS_FISRT()    (LMAC->FSM_CFG |= FSM_CFG_AIFS_FEN_MSK)
#define LHW_CLR_AIFS_FISRT()    (LMAC->FSM_CFG &= ~FSM_CFG_AIFS_FEN_MSK)
#define LHW_SET_BO_FISRT()      (LMAC->FSM_CFG |= FSM_CFG_BO_FEN_MSK)
#define LHW_CLR_BO_FISRT()      (LMAC->FSM_CFG &= ~FSM_CFG_BO_FEN_MSK)
#define LHW_SET_BITMAP_P()      (LMAC->COMN_CTRL |= COMN_CTRL_BA_PRO_EN_MSK)
#define LHW_CLR_BITMAP_P()      (LMAC->COMN_CTRL &= ~COMN_CTRL_BA_PRO_EN_MSK)
#define LHW_SET_DYN_BW()        (LMAC->COMN_CTRL |= COMN_CTRL_DYN_BW_EN_MSK)
#define LHW_CLR_DYN_BW()        (LMAC->COMN_CTRL &= ~COMN_CTRL_DYN_BW_EN_MSK)
#define LHW_SET_DOZ_MODE()      (LMAC->COMN_CTRL |= COMN_CTRL_DOZ_EN_MSK)
#define LHW_CLR_DOZ_MODE()      (LMAC->COMN_CTRL &= ~COMN_CTRL_DOZ_EN_MSK)
#define LHW_CFG_BSS_BW(bw)      do{\
        LMAC->COMN_CTRL &= ~COMN_CTRL_BSS_BW_MSK;\
        LMAC->COMN_CTRL |= (((bw) << COMN_CTRL_BSS_BW_SHIFT) & COMN_CTRL_BSS_BW_MSK);\
    }while(0)
#define LHW_SET_TX_IRQ_EN()     (LMAC->IRQ_EN |= IRQ_EN_TX_END_EN_MSK)
#define LHW_CLR_TX_IRQ_EN()     (LMAC->IRQ_EN &= ~IRQ_EN_TX_END_EN_MSK)
#define LHW_SET_RXSYNC_IRQ_EN() (LMAC->IRQ_EN |= IRQ_EN_SYNC_IRQ_EN_MSK)
#define LHW_CLR_RXSYNC_IRQ_EN() (LMAC->IRQ_EN &= ~IRQ_EN_SYNC_IRQ_EN_MSK)
#define LHW_SET_RXHDR_IRQ_EN()  (LMAC->IRQ_EN |= IRQ_EN_RX_HDR_EN_MSK)
#define LHW_CLR_RXHDR_IRQ_EN()  (LMAC->IRQ_EN &= ~IRQ_EN_RX_HDR_EN_MSK)
#define LHW_SET_RX_IRQ_EN()     (LMAC->IRQ_EN |= IRQ_EN_RX_END_EN_MSK)
#define LHW_CLR_RX_IRQ_EN()     (LMAC->IRQ_EN &= ~IRQ_EN_RX_END_EN_MSK)
#define LHW_SET_DEAGG_ERR_EN()  (LMAC->IRQ_EN |= IRQ_EN_DEAGG_ERR_EN_MSK)
#define LHW_CLR_DEAGG_ERR_EN()  (LMAC->IRQ_EN &= ~IRQ_EN_DEAGG_ERR_EN_MSK)
#define LHW_CLR_LT_IRQ_EN()     (LMAC->IRQ_EN &= ~IRQ_EN_LT_EN_MSK)
#define LHW_CLR_HT1_IRQ_EN()    (LMAC->IRQ_EN &= ~IRQ_EN_HT1_EN_MSK)
#define LHW_CLR_HT2_IRQ_EN()    (LMAC->IRQ_EN &= ~IRQ_EN_HT2_EN_MSK)
#define LHW_CLR_HT3_IRQ_EN()    (LMAC->IRQ_EN &= ~IRQ_EN_HT3_EN_MSK)
#define LHW_CLR_HT4_IRQ_EN()    (LMAC->IRQ_EN &= ~IRQ_EN_HT4_EN_MSK)
#define LHW_CLR_HT5_IRQ_EN()    (LMAC->IRQ_EN &= ~IRQ_EN_HT5_EN_MSK)
#define LHW_CLR_HT6_IRQ_EN()    (LMAC->IRQ_EN &= ~IRQ_EN_HT6_EN_MSK)
#define LHW_SET_LT_IRQ_EN()     (LMAC->IRQ_EN |= IRQ_EN_LT_EN_MSK)
#define LHW_SET_HT1_IRQ_EN()    (LMAC->IRQ_EN |= IRQ_EN_HT1_EN_MSK)
#define LHW_SET_HT2_IRQ_EN()    (LMAC->IRQ_EN |= IRQ_EN_HT2_EN_MSK)
#define LHW_SET_HT3_IRQ_EN()    (LMAC->IRQ_EN |= IRQ_EN_HT3_EN_MSK)
#define LHW_SET_HT4_IRQ_EN()    (LMAC->IRQ_EN |= IRQ_EN_HT4_EN_MSK)
#define LHW_SET_HT5_IRQ_EN()    (LMAC->IRQ_EN |= IRQ_EN_HT5_EN_MSK)
#define LHW_SET_HT6_IRQ_EN()    (LMAC->IRQ_EN |= IRQ_EN_HT6_EN_MSK)
#define LHW_GET_IRQ_PD_LT()     (LMAC->IRQ_PD & IRQ_PD_LT_PD_MSK)
#define LHW_CLR_IRQ_PD_LT()     (LMAC->IRQ_PD = IRQ_PD_LT_PD_MSK)
#define LHW_GET_IRQ_PD_HT1()    (LMAC->IRQ_PD & IRQ_PD_HT1_PD_MSK)
#define LHW_CLR_IRQ_PD_HT1()    (LMAC->IRQ_PD = IRQ_PD_HT1_PD_MSK)
#define LHW_GET_IRQ_PD_HT2()    (LMAC->IRQ_PD & IRQ_PD_HT2_PD_MSK)
#define LHW_CLR_IRQ_PD_HT2()    (LMAC->IRQ_PD = IRQ_PD_HT2_PD_MSK)
#define LHW_GET_IRQ_PD_HT3()    (LMAC->IRQ_PD & IRQ_PD_HT3_PD_MSK)
#define LHW_CLR_IRQ_PD_HT3()    (LMAC->IRQ_PD = IRQ_PD_HT3_PD_MSK)
#define LHW_GET_IRQ_PD_HT4()    (LMAC->IRQ_PD & IRQ_PD_HT4_PD_MSK)
#define LHW_CLR_IRQ_PD_HT4()    (LMAC->IRQ_PD = IRQ_PD_HT4_PD_MSK)
#define LHW_GET_IRQ_PD_HT5()    (LMAC->IRQ_PD & IRQ_PD_HT5_PD_MSK)
#define LHW_CLR_IRQ_PD_HT5()    (LMAC->IRQ_PD = IRQ_PD_HT5_PD_MSK)
#define LHW_GET_IRQ_PD_HT6()    (LMAC->IRQ_PD & IRQ_PD_HT6_PD_MSK)
#define LHW_CLR_IRQ_PD_HT6()    (LMAC->IRQ_PD = IRQ_PD_HT6_PD_MSK)
#define LHW_GET_IRQ_PD_AC()     (LMAC->IRQ_PD & IRQ_PD_AC_PD_PD_MSK)
#define LHW_CLR_IRQ_PD_AC()     (LMAC->IRQ_PD = IRQ_PD_AC_PD_PD_MSK)
#define LHW_GET_IRQ_PD_BO()     (LMAC->IRQ_PD & IRQ_PD_BO_FNS_PD_MSK)
#define LHW_CLR_IRQ_PD_BO()     (LMAC->IRQ_PD = IRQ_PD_BO_FNS_PD_MSK)
#define LHW_GET_IRQ_PD_TX()     (LMAC->IRQ_PD & IRQ_PD_TX_END_PD_MSK)
#define LHW_CLR_IRQ_PD_TX()     (LMAC->IRQ_PD = IRQ_PD_TX_END_PD_MSK)
#define LHW_GET_IRQ_PD_RXSYNC() (LMAC->IRQ_PD & IRQ_PD_SYNC_IRQ_PD_MSK)
#define LHW_CLR_IRQ_PD_RXSYNC() (LMAC->IRQ_PD = IRQ_PD_SYNC_IRQ_PD_MSK)
#define LHW_GET_IRQ_PD_RX()     (LMAC->IRQ_PD & IRQ_PD_RX_END_PD_MSK)
#define LHW_CLR_IRQ_PD_RX()     (LMAC->IRQ_PD = IRQ_PD_RX_END_PD_MSK)
#define LHW_GET_IRQ_PD_DEAGG_ERR()     (LMAC->IRQ_PD & IRQ_PD_DEAGG_ERR_PD_MSK)
#define LHW_CLR_IRQ_PD_DEAGG_ERR()     (LMAC->IRQ_PD = IRQ_PD_DEAGG_ERR_PD_MSK)
#define LHW_CLR_IRQ_PD()        (LMAC->IRQ_PD = 0xffffffff)

#if LMAC_VERSION >= 59
#define LHW_SET_END_TO_IRQ_EN() (LMAC->IRQ_EN |= IRQ_EN_END_TO_EN_MSK)
#define LHW_CLR_END_TO_IRQ_EN() (LMAC->IRQ_EN &= ~IRQ_EN_END_TO_EN_MSK)
#define LHW_GET_IRQ_PD_END_TO() (LMAC->IRQ_PD & IRQ_PD_END_TO_PD_MSK)
#define LHW_CLR_IRQ_PD_END_TO() (LMAC->IRQ_PD = IRQ_PD_END_TO_PD_MSK)
#define LMAC_CCA_BUSY_CARE_SYNC()           (LMAC->FSM_CFG &= ~FSM_CFG_CCA_SYNC_CARE_BUSY_MSK)
#define LMAC_TXVEC_RDY()                    (LMAC->FSM_CFG |= FSM_CFG_TXVEC_RDY_MSK)
#define LMAC_ABORT_RX_NOT_CARE_TX_SIFS()    (LMAC->FSM_CFG &= ~FSM_CFG_CCA_SIFS_CARE_MSK)
#define LHW_SET_RXSUBF_IRQ_EN() (LMAC->IRQ_EN |= IRQ_EN_RXSUBF_EN_MSK)
#define LHW_CLR_RXSUBF_IRQ_EN() (LMAC->IRQ_EN &= ~IRQ_EN_RXSUBF_EN_MSK)
#define LHW_GET_IRQ_PD_RXSUBF() (LMAC->IRQ_PD & IRQ_PD_RXSUBF_PD_MSK)
#define LHW_CLR_IRQ_PD_RXSUBF() (LMAC->IRQ_PD = IRQ_PD_RXSUBF_PD_MSK)
#endif

#define LHW_CFG_AGG_TX(val)    do{\
        LMAC->AGGR_CTRL &= ~AGGR_CTRL_AGGREG_MSK;\
        LMAC->AGGR_CTRL |= (((val) << AGGR_CTRL_AGGREG_SHIFT) & AGGR_CTRL_AGGREG_MSK);\
    }while(0)
#define LHW_CFG_EOF_BYTE(val)   (LMAC->TX_EOFBYT = (val))
#define LHW_CFG_EOF_BIT(val)   do{\
        LMAC->AGGR_CTRL &= ~AGGR_CTRL_EOF_MSK;\
        LMAC->AGGR_CTRL |= (((val) << AGGR_CTRL_EOF_SHIFT) & AGGR_CTRL_EOF_MSK);\
    }while(0)
#define LHW_CFG_DUMMY_SUB_FRM_NUM(val)  do{\
        LMAC->AGGR_CTRL &= ~AGGR_CTRL_LEN0SFC_MSK;\
        LMAC->AGGR_CTRL |= (((val) << AGGR_CTRL_LEN0SFC_SHIFT) & AGGR_CTRL_LEN0SFC_MSK);\
    }while(0)
#define LHW_CFG_DELAY_AFTER_BO(val)     do{\
        LMAC->TX_DLY1 &= ~TX_DLY1_BO_DLY_MSK;\
        LMAC->TX_DLY1 |= (((val) << TX_DLY1_BO_DLY_SHIFT) & TX_DLY1_BO_DLY_MSK);\
    }while(0)
#define LHW_CLR_CCA_SYNC_TO()       (LMAC->RX_CTRL &= ~(RX_CTRL_CCA_TO_EN_MSK | RX_CTRL_SYNC_TO_EN_MSK))
#define LHW_CFG_TX_BYTE_CNT(val)    (LMAC->TX_BYTCNT = (val))
#define LHW_GET_TX_STAT_ERR()       (LMAC->TX_STAT & (TX_STAT_PHY_TXERR_MSK | TX_STAT_END_EARLY_ERR_MSK))
#define LHW_CLR_TX_STAT_ERR()       (LMAC->TX_STAT |= ((TX_STAT_PHY_TXERR_MSK | TX_STAT_END_EARLY_ERR_MSK)))
#define LHW_GET_RX_PHY_ERROR()      (LMAC->RX_STAT & RX_STAT_PHY_ERR_MSK)
#define LHW_GET_RX_END_ERROR()      (LMAC->RX_STAT & RX_STAT_END_ERR_MSK)
#define LHW_GET_RX_FIFO_ERROR()     (LMAC->RX_STAT & RX_STAT_RX_FIFO_ERR_MSK)
#define LHW_GET_RX_DMAOF_ERROR()    (LMAC->RX_STAT & RX_STAT_RXDMAOF_MSK)
#define LHW_CLR_RX_PHY_ERROR()      (LMAC->RX_STAT = RX_STAT_PHY_ERR_MSK)
#define LHW_CLR_RX_END_ERROR()      (LMAC->RX_STAT = RX_STAT_END_ERR_MSK)
#define LHW_CLR_RX_FIFO_ERROR()     (LMAC->RX_STAT = RX_STAT_RX_FIFO_ERR_MSK)
#define LHW_CLR_RX_DMAOF_ERROR()    (LMAC->RX_STAT = RX_STAT_RXDMAOF_MSK)
#define LHW_CLR_RX_STAT()           (LMAC->RX_STAT = 0xffffffff)
#define LHW_GET_RX_SIG_BW()         ((LMAC->RX_STAT & RX_STAT_RXSIGBW_MSK) >> RX_STAT_RXSIGBW_SHIFT)
#define LHW_GET_RX_PRI_BW()         ((LMAC->RX_STAT & RX_STAT_PRI_BW_MSK) >> RX_STAT_PRI_BW_SHIFT)
#define LHW_GET_RX_DUP_BW()         (((LMAC->RX_STAT) & RX_STAT_RXDUPBW_MSK) >> RX_STAT_RXDUPBW_SHIFT)
#define LHW_GET_RX_LONG_IND()       ((LMAC->RX_STAT & RX_STAT_LONG_MSK) >> RX_STAT_LONG_SHIFT)
#define LHW_CFG_DBG_MODE(val)       do{\
        LMAC->DBG_CTRL &= ~DBG_CTRL_DBG_MOD_MSK;\
        LMAC->DBG_CTRL |= ((val << DBG_CTRL_DBG_MOD_SHIFT) & DBG_CTRL_DBG_MOD_MSK);\
    }while(0)
#define LHW_CFG_RX_BUFF_GAP(val)    do{\
        LMAC->RXDMACTL &= ~RXDMACTL_BGAP_MSK;\
        LMAC->RXDMACTL |= (((val) << RXDMACTL_BGAP_SHIFT)  & RXDMACTL_BGAP_MSK); \
    }while(0)
#define LHW_SET_TX_TEST_MODE()      (LMAC->TEST_CTRL |= TEST_CTRL_TX_TSTEN_MSK)
#define LHW_CLR_TX_TEST_MODE()      (LMAC->TEST_CTRL &= ~TEST_CTRL_TX_TSTEN_MSK)
#define LHW_SET_RX_TEST_MODE()      (LMAC->TEST_CTRL |= TEST_CTRL_RX_TSTEN_MSK)
#define LHW_CLR_RX_TEST_MODE()      (LMAC->TEST_CTRL &= ~TEST_CTRL_RX_TSTEN_MSK)
#define LHW_CLR_RX_DMA_RELOAD()     (LMAC->RXDMACTL &= ~RXDMACTL_RELOAD_MSK)
#define LHW_SET_PRBS_GEN_EN()       (LMAC->TX_PRBS_GEN |= TX_PRBS_GEN_PRBS_EN_MSK)
#define LHW_CLR_PRBS_GEN_EN()       (LMAC->TX_PRBS_GEN &= ~TX_PRBS_GEN_PRBS_EN_MSK)
#define LHW_SET_PRBS_SEED(val)      do{\
        LMAC->TX_PRBS_GEN &= ~TX_PRBS_GEN_SEED_MSK;\
        LMAC->TX_PRBS_GEN |= ((val)<<TX_PRBS_GEN_SEED_SHIFT)&TX_PRBS_GEN_SEED_MSK;\
    }while(0)
#if LMAC_VERSION >= 46
#define LHW_SET_RXEN_IN_CCA_SIFS()  (LMAC->COMN_CTRL |= COMN_CTRL_RXEN_CCA_MSK)
#define LHW_CLR_RXEN_IN_CCA_SIFS()  (LMAC->COMN_CTRL &= ~COMN_CTRL_RXEN_CCA_MSK)
#define LHW_CLR_CCA_UPDATE_TX_BW()  (LMAC->COMN_CTRL &= ~COMN_CTRL_CCA_UPDAT_BW_EN_MSK)
#define LHW_CLR_RX_UPDATE_TX_BW()   (LMAC->COMN_CTRL &= ~COMN_CTRL_RX_UPDAT_BW_EN_MSK)
#define LHW_CLR_RX_UPDATE_TX_NDP()  (LMAC->COMN_CTRL &= ~COMN_CTRL_RX_UPDAT_NDP_EN_MSK)
#define LHW_FIX_RX_FCS_BUG()        (LMAC->COMN_CTRL |= COMN_CTRL_FCS_ALIGN_APEP_MSK)
#define LHW_GET_RXEND_TIME()        (LMAC->FSM_TSF1)
#define LHW_SIGBW_MAP2_BW(sigbw)    (((sigbw) + 1) % 4)              
#define LHW_BW_MAP2_SIGBW(bw)       (((bw) + 3) % 4)

void lhw_cfg_tx_delay_pa(uint8 pa_delay);
#endif

uint16 lhw_get_cca_remain(void);
void lhw_start_cca(uint8 aifs, uint16 bo_val);
void lhw_start_rx(int32 delay);
void lhw_start_tx(uint8 sifs_init1);
void lhw_abort_fsm(void);
void lhw_enable_irq_ac(void);
void lhw_cfg_sifs(uint8 sifs_tx, uint16 sifs_rx, uint8 sifs_bo);
void lhw_cfg_tx_delay_before(uint8 dly_1m, uint8 dly_2m, uint8 dly_4m, uint8 dly_8m);
void lhw_cfg_tx_delay_after(uint8 dly_1m, uint8 dly_2m, uint8 dly_4m, uint8 dly_8m);
void lhw_cfg_tx_dalay_dac_rf(uint8 dac_delay, uint8 rf_tx_delay, uint8 ad9361en_delay);
void lhw_cfg_phy_rx_delay(uint8 val);
void lhw_cfg_dma_list_cnt(uint8 list_cnt);
void lhw_cfg_tx_sub_frm(uint8 sub_idx, uint8 *addr, uint32 len);
uint8 lhw_get_rx_frm_type(void);
uint8 lhw_get_rx_ndp_ind(void);
uint64 lhw_get_ndp2m(void);
void lhw_irq_init(void);
void lhw_set_bo_bypass(uint8 val);
void lhw_set_tsf(uint64 value);
void lmac_cfg_rf_en(uint8 val);
void lmac_rf_sw_ctrl(void);
void lmac_rf_hw_ctrl(void);
void lmac_cfg_tx_en(uint8 val);
void lmac_cfg_rx_en(uint8 val);
void lmac_cfg_pa_en(uint8 val);
#if LMAC_VERSION >= 59
void lmac_cfg_dac_en(uint8 val);
void lmac_cfg_end_to_limit(uint16 x_us);
#endif
//void lmac_cont_tx_en(void);
//void lmac_cont_tx_dis(void);
void lhw_start_cca_observ(uint8 observ_sec_shift);
int32 lhw_get_cca_observ(uint32 *buf);

#ifdef __cplusplus
}
#endif

#endif
