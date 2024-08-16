#ifndef _HG_SYSAES_H_
#define _HG_SYSAES_H_
#include "hal/sysaes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLOCK_NUM_NUM_MSK                   0x000fffff
#define BLOCK_NUM_NUM_SHIFT                 0
	 
#define AES_CTRL_START_MSK                  0x00000001
#define AES_CTRL_START_SHIFT                0
#define AES_CTRL_EOD_MSK                    0x00000002
#define AES_CTRL_EOD_SHIFT                  1
#define AES_CTRL_MOD_MSK                    0x00000004
#define AES_CTRL_MOD_SHIFT                  2
#define AES_CTRL_IRQ_EN_MSK                 0x00000008
#define AES_CTRL_IRQ_EN_SHIFT               3

#define AES_STAT_COMP_PD_MSK                0x00000001
#define AES_STAT_COMP_PD_SHIFT              0

enum hg_sysaes_mode {
    ENCRYPT,
    DECRYPT,
};

struct hg_sysaes_hw {
    __IO uint32 KEY[8];
    __IO uint32 SADDR;
    __IO uint32 DADDR;
    __IO uint32 BLOCK_NUM;
         uint32 RESERVED[5];
    __IO uint32 AES_CTRL;
    __IO uint32 AES_STAT;
};

struct hg_sysaes {
    struct sysaes_dev dev;
    struct hg_sysaes_hw *hw;
    struct os_mutex lock;
    struct os_semaphore done;
    uint32 irq_num;
};

int32 hg_sysaes_attach(uint32 dev_id, struct hg_sysaes *sysaes);

#endif /* _HG_SYSAES_H_ */