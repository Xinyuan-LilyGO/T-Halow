#ifndef  _HAL_RFDIGICALI_H_
#define  _HAL_RFDIGICALI_H_
#ifdef __cplusplus
extern "C" {
#endif

#define K_TX_PWR_IDX_MODE_INT    0   // used only by internal RF
#define K_TX_PWR_IDX_MODE_EXTSPI 1   // EXTSPI is used for config extern spi based RF front end such as ad9631
#define K_RX_PWR_IDX_MODE_TST    0   // for calibration and some simliar cases
#define K_RX_PWR_IDX_MODE_NORM   1   // for PHY normal running

struct rfdigicali_device {
    struct dev_obj dev;
    void (*stop_tx_cali)(struct rfdigicali_device *pdev);
    int32(*pwr_calc_kick)(struct rfdigicali_device *pdev);
    void (*dcoc_est_en)(struct rfdigicali_device *pdev);
    void (*dcoc_est_kick)(struct rfdigicali_device *pdev, int32 amp_val[2]);
    void (*dcoc_imb_est_kick)(struct rfdigicali_device *pdev);
    void (*cfg_tx_gain_idx_src)(struct rfdigicali_device *pdev, uint8 source);
    void (*set_tx_pwr)(struct rfdigicali_device *pdev, uint8 pwr_idx);  // pwr_idx: 0~5
    void (*cfg_tx_dcoc)(struct rfdigicali_device *pdev, int16 iqval[2], uint8 pwr_idx);  // pwr_idx: 0~5
    void (*cfg_tx_imb)(struct rfdigicali_device *pdev, int16 phase_comp, uint16 gain_comp, uint8 pwr_idx); // pwr_idx: 0~5
    void (*cfg_tx_digi_gain)(struct rfdigicali_device *pdev, uint16 tx_digi_gain, uint8 pwr_idx); // pwr_idx: 0~5
    void (*cfg_rx_gain_idx_src)(struct rfdigicali_device *pdev, uint8 source);
    void (*set_rx_gain)(struct rfdigicali_device *pdev, uint8 pwr_idx, uint8 bw);  // pwr_idx: 0~5  bw: 0:1M   1:2M   2:4M   3:8M   4:full bandfor DPD
    void (*cfg_rx_dcoc)(struct rfdigicali_device *pdev, int16 iqval[2], uint8 pwr_idx, uint8 bw);  // pwr_idx: 0~5  bw: 0:1M   1:2M   2:4M   3:8M   4:full bandfor DPD
    void (*cfg_rx_imb)(struct rfdigicali_device *pdev, int16 phase_comp, uint16 gain_comp, uint8 pwr_idx, uint8 bw); // pwr_idx: 0~5  bw: 0:1M   1:2M   2:4M   3:8M   4:full bandfor DPD
    void (*cfg_rx_dfilt_bw)(struct rfdigicali_device *pdev, uint8 bw);
    void (*cfg_rx_dfilt_bw_auto)(struct rfdigicali_device *pdev);
    void (*get_rx_dcoc)(struct rfdigicali_device *pdev, int16 iqval[2], uint8 pwr_idx, uint8 bw);  // pwr_idx: 0~5  bw: 0:1M   1:2M   2:4M   3:8M   4:full bandfor DPD
    void (*get_rx_imb)(struct rfdigicali_device *pdev, int16 *phase_comp, uint16 *gain_comp, uint8 pwr_idx, uint8 bw); // pwr_idx: 0~5  bw: 0:1M   1:2M   2:4M   3:8M   4:full bandfor DPD
    // only for RFDIGICALI_HW_VER >= 2 // 1: 4001 2: MARS
    uint16(*get_tx_digi_gain)(struct rfdigicali_device *pdev, uint8 pwr_idx);
    void (*cfg_rx_hw_dcoc)(struct rfdigicali_device *pdev, uint8 start_dur, uint8 dcoc_coarse_est_dur, uint16 dcoc_fine_est_dur); // start_dur: 0~255  unit:8us   dcoc_coarse_est_dur: 0~255  unit:8us  dcoc_fine_est_dur: 0~(65535-255)  unit:8us
    void (*dcoc_hw_trig_en)(struct rfdigicali_device *pdev);
    void (*dcoc_hw_trig_dis)(struct rfdigicali_device *pdev);
    void (*cfg_hw_bknoise)(struct rfdigicali_device *pdev, uint16 start_dur, uint8 mag_pwr_avg_sel); // mag_pwr_avg_sel: 0: 256(8us)  1:512(16us) ... 15:262144(8192us)
    void (*bknoise_hw_trig_en)(struct rfdigicali_device *pdev);
    void (*bknoise_hw_trig_dis)(struct rfdigicali_device *pdev);
    void (*bknoise_pwr_calc_en)(struct rfdigicali_device *pdev);
    void (*bknoise_pwr_calc_dis)(struct rfdigicali_device *pdev);
    int32(*bknoise_valid_pd_get)(struct rfdigicali_device *pdev);
    void (*bknoise_valid_pd_clr)(struct rfdigicali_device *pdev);
    void (*cfg_fb_comp)(struct rfdigicali_device *pdev, uint8 en_or_dis);
    int8(*bknoise_get)(struct rfdigicali_device *pdev);
    int16(*dcoci_get)(struct rfdigicali_device *pdev);
    int16(*dcocq_get)(struct rfdigicali_device *pdev);
};

static inline void rfdigicali_device_stop_tx_cali(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->stop_tx_cali) {
        pdev->stop_tx_cali(pdev);
    }
}

static inline int32 rfdigicali_device_power_calc_kick_start(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->pwr_calc_kick) {
        return pdev->pwr_calc_kick(pdev);
    }
    return 0;
}

static inline void rfdigicali_device_dcoc_est_en(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->dcoc_est_en) {
        pdev->dcoc_est_en(pdev);
    }
}

static inline void rfdigicali_device_dcoc_est_kick_start(struct rfdigicali_device *pdev, int32 amp_val[2])
{
    if (pdev && pdev->dcoc_est_kick) {
        pdev->dcoc_est_kick(pdev, amp_val);
    }
}

static inline void rfdigicali_device_dcoc_imb_est_kick_start(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->dcoc_imb_est_kick) {
        pdev->dcoc_imb_est_kick(pdev);
    }
}

static inline void rfdigicali_device_config_tx_gain_idx_src(struct rfdigicali_device *pdev, uint8 source)
{
    if (pdev && pdev->cfg_tx_gain_idx_src) {
        pdev->cfg_tx_gain_idx_src(pdev, source);
    }
}

static inline void rfdigicali_device_config_tx_pwr(struct rfdigicali_device *pdev, uint8 pwr_idx)
{
    if (pdev && pdev->set_tx_pwr) {
        pdev->set_tx_pwr(pdev, pwr_idx);
    }
}

static inline void rfdigicali_device_config_tx_dcoc(struct rfdigicali_device *pdev, int16 iqval[2], uint8 pwr_idx)
{
    if (pdev && pdev->cfg_tx_dcoc) {
        pdev->cfg_tx_dcoc(pdev, iqval, pwr_idx);
    }
}

static inline void rfdigicali_device_config_tx_imb(struct rfdigicali_device *pdev, int16 phase_comp, uint16 gain_comp, uint8 pwr_idx)
{
    if (pdev && pdev->cfg_tx_imb) {
        pdev->cfg_tx_imb(pdev, phase_comp, gain_comp, pwr_idx);
    }
}

static inline void rfdigicali_device_config_tx_digi_gain(struct rfdigicali_device *pdev, uint16 tx_digi_gain, uint8 pwr_idx)
{
    if (pdev && pdev->cfg_tx_digi_gain) {
        pdev->cfg_tx_digi_gain(pdev, tx_digi_gain, pwr_idx);
    }
}

static inline void rfdigicali_device_config_rx_gain_idx_src(struct rfdigicali_device *pdev, uint8 source)
{
    if (pdev && pdev->cfg_rx_gain_idx_src) {
        pdev->cfg_rx_gain_idx_src(pdev, source);
    }
}

// pwr_idx: 0~5  bw: 0:1M   1:2M   2:4M   3:8M   4:full bandfor DPD
static inline void rfdigicali_device_config_rx_gain(struct rfdigicali_device *pdev, uint8 gain_idx, uint8 bw)
{
    if (pdev && pdev->set_rx_gain) {
        pdev->set_rx_gain(pdev, gain_idx, bw);
    }
}

static inline void rfdigicali_device_config_rx_dcoc(struct rfdigicali_device *pdev, int16 iqval[2], uint8 pwr_idx, uint8 bw)
{
    if (pdev && pdev->cfg_rx_dcoc) {
        pdev->cfg_rx_dcoc(pdev, iqval, pwr_idx, bw);
    }
}

static inline void rfdigicali_device_config_rx_imb(struct rfdigicali_device *pdev, int16 phase_comp, uint16 gain_comp, uint8 pwr_idx, uint8 bw)
{
    if (pdev && pdev->cfg_rx_imb) {
        pdev->cfg_rx_imb(pdev, phase_comp, gain_comp, pwr_idx, bw);
    }
}

static inline void rfdigicali_device_config_rx_filter(struct rfdigicali_device *pdev, uint8 bw)
{
    if (pdev && pdev->cfg_rx_dfilt_bw) {
        pdev->cfg_rx_dfilt_bw(pdev, bw);
    }
}

static inline void rfdigicali_device_config_rx_filter_auto(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->cfg_rx_dfilt_bw_auto) {
        pdev->cfg_rx_dfilt_bw_auto(pdev);
    }
}

static inline void rfdigicali_device_get_rx_dcoc(struct rfdigicali_device *pdev, int16 iqval[2], uint8 pwr_idx, uint8 bw)
{
    if (pdev && pdev->get_rx_dcoc) {
        pdev->get_rx_dcoc(pdev, iqval, pwr_idx, bw);
    }
}

static inline void rfdigicali_device_get_rx_imb(struct rfdigicali_device *pdev, int16 *phase_comp, uint16 *gain_comp, uint8 pwr_idx, uint8 bw)
{
    if (pdev && pdev->get_rx_imb) {
        pdev->get_rx_imb(pdev, phase_comp, gain_comp, pwr_idx, bw);
    }
}

static inline uint16 rfdigicali_device_get_tx_digi_gain(struct rfdigicali_device *pdev, uint8 pwr_idx)
{
    if (pdev && pdev->get_tx_digi_gain) {
        return pdev->get_tx_digi_gain(pdev, pwr_idx);
    } else {
        return 0;
    }
}

// start_dur: 0~255  unit:8us
// dcoc_coarse_est_dur: 0~255  unit:8us
// dcoc_fine_est_dur: 0~(65535-255)  unit:8us
static inline void rfdigicali_device_config_hw_rx_dcoc(struct rfdigicali_device *pdev, uint8 start_dur, uint8 dcoc_coarse_est_dur, uint16 dcoc_fine_est_dur)
{
    if (pdev && pdev->cfg_rx_hw_dcoc) {
        pdev->cfg_rx_hw_dcoc(pdev, start_dur, dcoc_coarse_est_dur, dcoc_fine_est_dur);
    }
}

static inline void rfdigicali_device_rx_dcoc_hw_trig_en(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->dcoc_hw_trig_en) {
        pdev->dcoc_hw_trig_en(pdev);
    }
}

static inline void rfdigicali_device_rx_dcoc_hw_trig_dis(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->dcoc_hw_trig_dis) {
        pdev->dcoc_hw_trig_dis(pdev);
    }
}

// mag_pwr_avg_sel: 0: 256(8us)  1:512(16us) ... 15:262144(8192us)
static inline void rfdigicali_device_config_hw_bknoise(struct rfdigicali_device *pdev, uint16 start_dur, uint8 mag_pwr_avg_sel)
{
    if (pdev && pdev->cfg_hw_bknoise) {
        pdev->cfg_hw_bknoise(pdev, start_dur, mag_pwr_avg_sel);
    }
}

static inline void rfdigicali_device_bknoise_hw_trig_en(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->bknoise_hw_trig_en) {
        pdev->bknoise_hw_trig_en(pdev);
    }
}

static inline void rfdigicali_device_bknoise_hw_trig_dis(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->bknoise_hw_trig_dis) {
        pdev->bknoise_hw_trig_dis(pdev);
    }
}

static inline void rfdigicali_device_cfg_fb_comp(struct rfdigicali_device *pdev, uint8 en_or_dis)
{
    if (pdev && pdev->cfg_fb_comp) {
        pdev->cfg_fb_comp(pdev, en_or_dis);
    }
}

static inline void rfdigicali_device_bknoise_calc_en(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->bknoise_pwr_calc_en) {
        pdev->bknoise_pwr_calc_en(pdev);
    }
}

static inline void rfdigicali_device_bknoise_calc_dis(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->bknoise_pwr_calc_dis) {
        pdev->bknoise_pwr_calc_dis(pdev);
    }
}

static inline int32 rfdigicali_device_bknoise_valid_pd_get(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->bknoise_valid_pd_get) {
        return pdev->bknoise_valid_pd_get(pdev);
    } else {
        return 0;
    }
}

static inline void rfdigicali_device_bknoise_valid_pd_clr(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->bknoise_valid_pd_clr) {
        pdev->bknoise_valid_pd_clr(pdev);
    }
}

static inline int8 rfdigicali_device_bknoise_get(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->bknoise_get) {
        return pdev->bknoise_get(pdev);
    } else {
        return 0;
    }
}

static inline int16 rfdigicali_device_dcoci_get(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->dcoci_get) {
        return pdev->dcoci_get(pdev);
    } else {
        return 0x7fff;
    }
}

static inline int16 rfdigicali_device_dcocq_get(struct rfdigicali_device *pdev)
{
    if (pdev && pdev->dcocq_get) {
        return pdev->dcocq_get(pdev);
    } else {
        return 0x7fff;
    }
}

#ifdef __cplusplus
}
#endif
#endif

