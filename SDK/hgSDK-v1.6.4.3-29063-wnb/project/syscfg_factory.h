#ifndef __SYSCFG_FACTORY_H__
#define __SYSCFG_FACTORY_H__

#ifdef SYS_FACTORY_PARAM_SIZE
extern const uint16_t sys_factory_param[SYS_FACTORY_PARAM_SIZE / 2];
#endif

struct syscfg_fact {
    uint16_t wnb_chan_list[16];
    uint8_t  wnb_bss_bw, wnb_tx_mcs, wnb_encrypt, wnb_forward;
    uint16_t wnb_freq_start, wnb_freq_end;
    uint32_t wnb_customer_id;
    uint16_t wnb_ether_type;
    uint8_t  wnb_tx_power;
};

static inline struct syscfg_fact *syscfg_fact_params(void)
{
#ifdef SYS_FACTORY_PARAM_SIZE
    ASSERT(sizeof(struct syscfg_fact) <= (SYS_FACTORY_PARAM_SIZE - 4));
    if (sys_factory_param[1] == 0x1a2b) {
        return (struct syscfg_fact *)(&sys_factory_param[2]);
    }
#endif
    return NULL;
}

#endif
