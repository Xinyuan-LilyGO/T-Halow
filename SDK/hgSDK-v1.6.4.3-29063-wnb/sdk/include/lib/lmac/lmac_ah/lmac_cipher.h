#ifndef _AH_CIPHER_ENGINE_H_
#define _AH_CIPHER_ENGINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define IV0_PRIO_MSK                        0x0000000f
#define IV0_PRIO_SHIFT                      0
#define IV0_MGM_MSK                         0x00000010
#define IV0_MGM_SHIFT                       4
#define IV0_PV_MSK                          0x00000020
#define IV0_PV_SHIFT                        5
#define IV0_ZEROS_MSK                       0x000000c0
#define IV0_ZEROS_SHIFT                     6
#define IV0_A2_23_0_MSK                     0xffffff00
#define IV0_A2_23_0_SHIFT                   8

#define IV1_A2_47_24_MSK                    0x00ffffff
#define IV1_A2_47_24_SHIFT                  0

#define PN0_PN_B5_MSK                       0x000000ff
#define PN0_PN_B5_SHIFT                     0
#define PN0_PN_B4_MSK                       0x0000ff00
#define PN0_PN_B4_SHIFT                     8
#define PN0_PN_B3_MSK                       0x00ff0000
#define PN0_PN_B3_SHIFT                     16
#define PN0_PN_B2_MSK                       0xff000000
#define PN0_PN_B2_SHIFT                     24

#define PN1_PN_B1_MSK                       0x000000ff
#define PN1_PN_B1_SHIFT                     0
#define PN1_PN_B0_MSK                       0x0000ff00
#define PN1_PN_B0_SHIFT                     8

#define AAD0_AAD_LEN_MSK                    0x0000ff00
#define AAD0_PN_B0_SHIFT                    8

#define ENC_DATA_LEN_DLEN_MSK               0x00003fff
#define ENC_DATA_LEN_DLEN_SHIFT             0

#define CIPHER_CTRL0_START_MSK              0x00000001
#define CIPHER_CTRL0_START_SHIFT            0
#define CIPHER_CTRL0_INTR_EN_MSK            0x00000002
#define CIPHER_CTRL0_INTR_EN_SHIFT          1

#define CIPHER_CTRL1_EOD_MSK                0x00000001
#define CIPHER_CTRL1_EOD_SHIFT              0
#define CIPHER_CTRL1_KEY_LEN_MSK            0x00003000
#define CIPHER_CTRL1_KEY_LEN_SHIFT          12

#define CIPHER_STATUS_COMP_PD_MSK           0x00000001
#define CIPHER_STATUS_COMP_PD_SHIFT         0
#define CIPHER_STATUS_MIC_ERR_MSK           0x00000002
#define CIPHER_STATUS_MIC_ERR_SHIFT         1
#define CIPHER_STATUS_FSM_STAT_MSK          0x0000003c
#define CIPHER_STATUS_FSM_STAT_SHIFT        2

/*
#define KEY_128BIT                          16
#define KEY_256BIT                          32
#define ENCRYPTION                          0
#define DECRYPTION                          1
*/

/**
  * @breif : enum of cipher-engine key size
  */
enum ah_ce_key_size {
    KEY_128BIT     = 0,
    KEY_256BIT     = 2,
};

/**
  * @breif : enum of cipher-engine mode
  */
enum ah_ce_mode {
    CE_ENCRYPTION     = 0,
    CE_DECRYPTION     = 1,
};


/**
  * @breif huge-ic cipher_engine register definition
  */
struct ah_ce_hw {
    __IO uint32 KEY[8];
    __IO uint32 IV[2];
    __IO uint32 PN[2];
    __IO uint32 AAD[8];
    __IO uint32 ENC_DATA_LEN;
    __IO uint32 ENC_SADDR;
    __IO uint32 ENC_DADDR;
    uint32 RESERVED0;
    __IO uint32 CIPHER_CTRL[2];
    __IO uint32 CIPHER_STATUS;
    uint32 RESERVED1;
    __I  uint32 MIC[4];
};

struct ah_ce {
    struct ah_ce_hw *hw;
    //ce_irq_hdl irq_hdl;
    struct os_mutex ce_lock;
    struct os_semaphore ce_done;
    uint32 irq_num;
};

struct ah_ce_para {
    uint8 *key;
    uint8 key_size;
    uint8 prio;
    uint8 mgm;
    uint8 pv;
    uint8 *a2;
    uint8 *pn;
    uint8 *aad;
    uint8 aad_size;
    uint8 mode;
    uint16 data_len;
    uint32 src_addr;
    uint32 dst_addr;
};

int32 ah_ce_init(uint32 dev_id, struct ah_ce *ce);
int32 ah_ce_start(struct ah_ce *ce, struct ah_ce_para *ce_para);

#ifdef __cplusplus
}
#endif


#endif



