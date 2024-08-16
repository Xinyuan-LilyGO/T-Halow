#ifndef __LMAC_TEST_H
#define __LMAC_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "typesdef.h"

#define DUMP_LMAC_NORMAL        1
#define DUMP_LMAC_FCS_ERR       2
#define DUMP_LMAC_PV_ERR        3
#define DUMP_LMAC_RXINFO_ERR    4
#define DUMP_LMAC_TYPE_MGMT     5
#define DUMP_LMAC_TYPE_CTRL     6
#define DUMP_LMAC_TYPE_DATA     7
#define DUMP_LMAC_TYPE_EXT      8
#define DUMP_LMAC_PHY_ERR       9
#define DUMP_LMAC_RXEND_ERR     10
#define DUMP_LMAC_FIFO_ERR      11
#define DUMP_LMAC_LEN_ERR       12
#define DUMP_LMAC_BW_ADV_1M     13
#define DUMP_LMAC_BW_ADV_2M     14
#define DUMP_LMAC_BW_ADV_4M     15
#define DUMP_LMAC_BW_ADV_8M     16


extern struct lmac_test lmactest;

int32 lmac_test_init(void);

struct sk_buff *lmac_test_cmd_hdl(struct lmac_ops *ops, struct sk_buff *skb);
int32 eft_tx_start_hdl(void);
    
struct cmd_reg_rd_def {
    uint32 reg_addr;
};
struct cmd_reg_wt_def {
    uint32 reg_addr;
    uint32 reg_val;
};
struct cmd_lmac_tx_def {
    uint16 fc;
    uint16 duration;
    uint8  da[MAC_ADDR_SIZE];
    uint8  sa[MAC_ADDR_SIZE];
    uint8  bssid[MAC_ADDR_SIZE];
    uint16 seq_num;
    uint16 payload_len;
};
struct cmd_set_tx_rate_def {
    uint8 bw;
    uint8 mcs;
};
struct cmd_set_freq_def {
    uint32 freq;
};
struct cmd_set_tx_pwr_def {
    uint16 pwr;
};
struct cmd_set_payload_def {
    uint8  mode;
    uint16 step;
} __packed;
struct cmd_set_xo_drcs_def {
    uint16 drcs;
};

/**
* for matlab interface
**/
struct test_cmd_hdr {
    uint8  magic;
    uint8  seq_num;
    uint16 len;
    uint8  cmd;
    union {
        struct cmd_reg_rd_def       cmd_reg_rd;
        struct cmd_reg_wt_def       cmd_reg_wt;
        struct cmd_lmac_tx_def      cmd_lmac_tx;
        struct cmd_set_tx_rate_def  cmd_set_tx_rate;
        struct cmd_set_freq_def     cmd_set_freq;
        struct cmd_set_tx_pwr_def   cmd_set_tx_pwr;
        struct cmd_set_payload_def  cmd_set_payload;
        struct cmd_set_xo_drcs_def  cmd_set_xo_drcs;
    };

} __packed;

/*
struct str_idn_def{
        uint8 *format = "?";
        uint16 cmp_len = 2;
};

struct str_reg_rd_def{
        uint8 *format = "REG_RD:";
        uint16 cmp_len = 8;
        uint16 reg_addr_idx = 10;
};

struct str_reg_wt_def{
        uint8 *format = "REG_WT:";
        uint16 cmp_len = 8;
        uint16 reg_addr_idx = 10;
        uint16 reg_val_idx = 13;
};
*/


#ifdef __cplusplus
}
#endif

#endif /* __LMAC_TEST_H */

