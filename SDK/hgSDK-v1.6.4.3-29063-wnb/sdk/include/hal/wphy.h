#ifndef  _HAL_WPHY_H
#define  _HAL_WPHY_H

#ifdef __cplusplus
extern "C" {
#endif

#define K_PHYAH_BW_1M   0    // primary channel number is only 0
#define K_PHYAH_BW_2M   1    // primary channel number is 0~1
#define K_PHYAH_BW_4M   2    // primary channel number is 0~3
#define K_PHYAH_BW_8M   3    // primary channel number is 0~7

#define K_AGCSRC_AGCBW  0    // AGC is controlled by AGC BW
#define K_AGCSRC_SIGBW  1    // AGC is controlled by nTxRxModemBW or RXPWRIDX.Rf_rx_bw

#define K_DPD_INFO_DLY_MSK        ((uint32)0xf<<18)
#define K_DPD_INFO_AN_SAT_MSK     ((uint32)1<<17)
#define K_DPD_INFO_KN_SAT_MSK     ((uint32)1<<16)
#define K_DPD_INFO_PN_SAT_MSK     ((uint32)1<<15)
#define K_DPD_INFO_YN_SAT_MSK     ((uint32)1<<14)
#define K_DPD_INFO_YN_ZERO_MSK    ((uint32)1<<13)
#define K_DPD_INFO_YN_LARGE_MSK   ((uint32)1<<12)
#define K_DPD_INFO_YN_SMALL_MSK   ((uint32)1<<11)
#define K_DPD_INFO_INV_GAIN_MSK   0x7ff

union _dpd_ram {
    struct {
        // 1st parameter for initiate DPD RAM
        // initial value of 1M PPDU pre-distortion IQ channel coefficients, signed Q5.15
        int32 DPD_1M_coef_vec[9][2];    // int21
        // 2nd parameter for initiate DPD RAM
        // initial value of 2M PPDU pre-distortion IQ channel coefficients, signed Q5.15
        int32 DPD_2M_coef_vec[9][2];    // int21
        // 3rd parameter for initiate DPD RAM
        // initial value of 4M PPDU pre-distortion IQ channel coefficients, signed Q5.15
        int32 DPD_4M_coef_vec[9][2];    // int21
        // 4th parameter for initiate DPD RAM
        // initial value of 8M PPDU pre-distortion IQ channel coefficients, signed Q5.15
        int32 DPD_8M_coef_vec[9][2];    // int21
        // 5th parameter for initiate DPD RAM
        // initial value of 1M PPDU Pn coefficients, signed Q6.13, upper triangular matrix
        int32 Pn_1m[45][2];             // int20
        // 6th parameter for initiate DPD RAM
        // initial value of 2M PPDU Pn coefficients, signed Q6.13, upper triangular matrix
        int32 Pn_2m[45][2];             // int20
        // 7th parameter for initiate DPD RAM
        // initial value of 4M PPDU Pn coefficients, signed Q6.13, upper triangular matrix
        int32 Pn_4m[45][2];             // int20
        // 8th parameter for initiate DPD RAM
        // initial value of 4M PPDU Pn coefficients, signed Q6.13, upper triangular matrix
        int32 Pn_8m[45][2];             // int20
    } n_dpd_ram;
    int32 word_buf[216][2];
};

struct hgwphy_ah_cfg;
struct wphy_device {
    struct dev_obj dev;
    void(*open)(struct wphy_device *pdev);
    void(*change_para)(struct wphy_device *pdev, const struct hgwphy_ah_cfg *pwhy_cfg);
    void(*close)(struct wphy_device *pdev);
    void(*rd_dpd_ram)(struct wphy_device *pdev);
    void(*cfg_dpd_ram)(struct wphy_device *pdev);
    int32(*ver_dpd_ram)(struct wphy_device *pdev);
    void(*disp)(struct wphy_device *pdev);
    void(*direct_rx_iq)(struct wphy_device *pdev, uint32 *pimbtab);
    void(*swap_rx_iq)(struct wphy_device *pdev, uint32 *pimbtab);
    void(*get_info)(struct wphy_device *pdev);
    void(*cfg_bw)(struct wphy_device *pdev, uint8 phy_bw);
    void(*cfg_pri_ch)(struct wphy_device *pdev, uint8 n_pri_ch);
    void(*en_rx_testmode)(struct wphy_device *pdev); // will obsolete in the future version
    void(*dis_rx_testmode)(struct wphy_device *pdev); // will obsolete in the future version
    void(*en_wphy)(struct wphy_device *pdev);
    void(*dis_wphy)(struct wphy_device *pdev);
    uint8(*get_scrambinit)(struct wphy_device *pdev);
    int8(*get_avg_power)(struct wphy_device *pdev);
    int8(*get_avg_evm)(struct wphy_device *pdev);
    void(*en_cont_tx)(struct wphy_device *pdev);
    void(*dis_cont_tx)(struct wphy_device *pdev);
    uint32(*get_tx_crc)(struct wphy_device *pdev);
    void(*cali_rx_imb_en)(struct wphy_device *pdev);
    void(*cali_rx_imb_dis)(struct wphy_device *pdev, int16 *phase_comp, uint16 *gain_comp);
    void(*wr_special_reg)(struct wphy_device *pdev, uint32 nVal32);
    uint32(*get_err_code)(struct wphy_device *pdev);
    uint16(*get_agc_info)(struct wphy_device *pdev);
    void (*cfg_rx_imb_tab)(struct wphy_device *pdev, uint32 *pimbtab);
    void (*cfg_rx_dc_tab)(struct wphy_device *pdev, int8 dc_offset_tab[2][6]);
    void (*dis_rx_agc)(struct wphy_device *pdev);
    void (*en_rx_agc)(struct wphy_device *pdev);
    void (*cfg_rx_gain_tab)(struct wphy_device *pdev, uint8 mcs, int8 RxGainVector[6]);
    void (*cfg_rx_gain_idx)(struct wphy_device *pdev, uint8 mcs, uint8 gain_idx);
    void (*cfg_cca_th)(struct wphy_device *pdev, int8 cca_th_tab[11]);
    uint8(*get_best_bw)(struct wphy_device *pdev);
    void (*cfg_phy_tx_sine)(struct wphy_device *pdev, uint8 mode, uint16 nSineStepSize);
    void (*cfg_phy_tx_tri)(struct wphy_device *pdev, uint8 mode, uint16 nSineStepSize);
    void (*cfg_phy_tx_norm)(struct wphy_device *pdev);
    void (*sw_rst_phy)(struct wphy_device *pdev);
    void (*sw_derst_phy)(struct wphy_device *pdev);
    uint16(*get_rx_psdu_crc)(struct wphy_device *pdev);
    uint16(*get_tx_psdu_crc)(struct wphy_device *pdev);
    uint32(*get_dpd_info)(struct wphy_device *pdev);
    uint8(*get_rx_sat_info)(struct wphy_device *pdev);
    uint8(*get_dpd_rx_sat_info)(struct wphy_device *pdev);
    void (*en_obss_sd_det)(struct wphy_device *pdev);
    void (*dis_obss_sd_det)(struct wphy_device *pdev);
    void (*cfg_obss_para)(struct wphy_device *pdev, uint8 BssColor, uint16 PartialBSSID, uint8 drop_downlink, int8 obss_sd);
    uint8(*get_tx_crc4)(struct wphy_device *pdev);  // output value 0~15
    uint8(*get_rx_crc4)(struct wphy_device *pdev);  // output value 0~15
    void (*cfg_agc_bw_src)(struct wphy_device *pdev, uint8 agc_bw_source); // 0: PHY_CTL.agc_bw  1:  nTxRxModemBW(dynamic_rx_bw_en == 1'b0)  RXPWRIDX.Rf_rx_bw(dynamic_rx_bw_en == 1'b1)
    void (*cfg_agc_bw)(struct wphy_device *pdev, uint8 agc_bw); // 2'd0 1M   2'd1 2M   2'd2 4M   2'd3 8M
    void (*cfg_phy_rx_bw_src)(struct wphy_device *pdev, uint8 rx_bw_src); // 0: nTxRxModemBW   1: RXPWRIDX.Rf_rx_bw
    void (*cfg_low_pwr_th)(struct wphy_device *pdev, uint8 nLowPowerTh); // nLowPowerTh : 5~15
    void (*en_auto_sig_err_rst)(struct wphy_device *pdev);
    void (*dis_auto_sig_err_rst)(struct wphy_device *pdev);
    void (*cfg_dpd)(struct wphy_device *pdev, uint8 m_bDPDen, uint8 m_bDynamicDPDen); // m_bDPDen 0: disable  1: enable     m_bDynamicDPDen   0: disable  1: enable
    int8(*adj_gain_val)(struct wphy_device *pdev, int8 ref_pwr, uint8 gain_idx);  // ref_pwr: [-128, 127] dBm   gain_idx: 0~5
    void (*cfg_rx_fix_gain_idx)(struct wphy_device *pdev, uint8 gain_idx); //  gain_idx: 0~5
    int32(*get_rx_freq_offset)(struct wphy_device *pdev);
    void (*get_rx_gain_para)(struct wphy_device *pdev, int8 rx_gain_tab[6], int8 *p_conversion_gain); // penghong 191120
    void (*cfg_rx_gain_stage)(struct wphy_device *pdev, uint8 stage_num);
};

static inline void wphy_device_open(struct wphy_device *pdev)
{
    if (pdev && pdev->open) {
        pdev->open(pdev);
    }
}

static inline void wphy_device_change_para(struct wphy_device *pdev, const struct hgwphy_ah_cfg *pwhy_cfg)
{
    if (pdev && pdev->change_para) {
        pdev->change_para(pdev, pwhy_cfg);
    }
}

static inline void wphy_device_close(struct wphy_device *pdev)
{
    if (pdev && pdev->close) {
        pdev->close(pdev);
    }
}

static inline void wphy_device_read_dpd_ram(struct wphy_device *pdev)
{
    if (pdev && pdev->rd_dpd_ram) {
        pdev->rd_dpd_ram(pdev);
    }
}

static inline void wphy_device_config_dpd_ram(struct wphy_device *pdev)
{
    if (pdev && pdev->cfg_dpd_ram) {
        pdev->cfg_dpd_ram(pdev);
    }
}

static inline int32 wphy_device_verify_dpd_ram(struct wphy_device *pdev)
{
    if (pdev && pdev->ver_dpd_ram) {
        return pdev->ver_dpd_ram(pdev);
    } else {
        return RET_ERR;
    }
}

static inline void wphy_device_disp(struct wphy_device *pdev)
{
    if (pdev && pdev->disp) {
        pdev->disp(pdev);
    }
}

static inline void wphy_device_direct_rx_iq(struct wphy_device *pdev, uint32 *pimbtab)
{
    if (pdev && pdev->direct_rx_iq) {
        pdev->direct_rx_iq(pdev, pimbtab);
    }
}

static inline void wphy_device_swap_rx_iq(struct wphy_device *pdev, uint32 *pimbtab)
{
    if (pdev && pdev->swap_rx_iq) {
        pdev->swap_rx_iq(pdev, pimbtab);
    }
}

static inline void wphy_device_get_info(struct wphy_device *pdev)
{
    if (pdev && pdev->get_info) {
        pdev->get_info(pdev);
    }
}

static inline void wphy_device_config_bw(struct wphy_device *pdev, uint8 phy_bw)
{
    if (pdev && pdev->cfg_bw) {
        pdev->cfg_bw(pdev, phy_bw);
    }
}

static inline void wphy_device_config_ch(struct wphy_device *pdev, uint8 n_pri_ch)
{
    if (pdev && pdev->cfg_pri_ch) {
        pdev->cfg_pri_ch(pdev, n_pri_ch);
    }
}

static inline void wphy_device_enable_rx_testmode(struct wphy_device *pdev)
{
    if (pdev && pdev->en_rx_testmode) {
        pdev->en_rx_testmode(pdev);
    }
}

static inline void wphy_device_disable_rx_testmode(struct wphy_device *pdev)
{
    if (pdev && pdev->dis_rx_testmode) {
        pdev->dis_rx_testmode(pdev);
    }
}

static inline void wphy_device_enable(struct wphy_device *pdev)
{
    if (pdev && pdev->en_wphy) {
        pdev->en_wphy(pdev);
    }
}

static inline void wphy_device_disable(struct wphy_device *pdev)
{
    if (pdev && pdev->dis_wphy) {
        pdev->dis_wphy(pdev);
    }
}

static inline uint8 wphy_device_get_scrambler_init(struct wphy_device *pdev)
{
    if (pdev && pdev->get_scrambinit) {
        return pdev->get_scrambinit(pdev);
    } else {
        return 0;
    }
}

static inline int8 wphy_device_get_avg_power(struct wphy_device *pdev)
{
    if (pdev && pdev->get_avg_power) {
        return pdev->get_avg_power(pdev);
    } else {
        return 0;
    }
}

static inline int8 wphy_device_get_avg_evm(struct wphy_device *pdev)
{
    if (pdev && pdev->get_avg_evm) {
        return pdev->get_avg_evm(pdev);
    } else {
        return 0;
    }
}

static inline void wphy_device_enable_cont_tx(struct wphy_device *pdev)
{
    if (pdev && pdev->en_cont_tx) {
        pdev->en_cont_tx(pdev);
    }
}

static inline void wphy_device_disable_cont_tx(struct wphy_device *pdev)
{
    if (pdev && pdev->dis_cont_tx) {
        pdev->dis_cont_tx(pdev);
    }
}

static inline uint32 wphy_device_get_tx_crc(struct wphy_device *pdev)
{
    if (pdev && pdev->get_tx_crc) {
        return pdev->get_tx_crc(pdev);
    } else {
        return 0;
    }
}

// approved input power while performing calibration are listed below:
// gain_idx 5:   -65dBm
// gain_idx 4:   -48dBm
// gain_idx 3:   -31dBm
// gain_idx 2:   -21dBm
// gain_idx 1:   -11dBm
// gain_idx 0:   -11dBm
static inline void wphy_device_cali_rx_imb_en(struct wphy_device *pdev)
{
    if (pdev && pdev->cali_rx_imb_en) {
        pdev->cali_rx_imb_en(pdev);
    }
}

static inline void wphy_device_cali_rx_imb_dis(struct wphy_device *pdev, int16 *phase_comp, uint16 *gain_comp)
{
    if (pdev && pdev->cali_rx_imb_dis) {
        pdev->cali_rx_imb_dis(pdev, phase_comp, gain_comp);
    }
}

static inline void wphy_device_write_special_reg(struct wphy_device *pdev, uint32 nVal32)
{
    if (pdev && pdev->wr_special_reg) {
        pdev->wr_special_reg(pdev, nVal32);
    }
}

static inline uint32 wphy_device_get_err_code(struct wphy_device *pdev)
{
    if (pdev && pdev->get_err_code) {
        return pdev->get_err_code(pdev);
    } else {
        return 0;
    }
}

static inline uint16 wphy_device_get_agc_info(struct wphy_device *pdev)
{
    if (pdev && pdev->get_agc_info) {
        return pdev->get_agc_info(pdev);
    } else {
        return 0;
    }
}

static inline void wphy_device_config_imb_tab(struct wphy_device *pdev, uint32 *pimbtab)
{
    if (pdev && pdev->cfg_rx_imb_tab) {
        pdev->cfg_rx_imb_tab(pdev, pimbtab);
    }
}

static inline void wphy_device_config_rx_dc_tab(struct wphy_device *pdev, int8 dc_offset_tab[2][6])
{
    if (pdev && pdev->cfg_rx_dc_tab) {
        pdev->cfg_rx_dc_tab(pdev, dc_offset_tab);
    }
}

static inline void wphy_device_disable_rx_agc(struct wphy_device *pdev)
{
    if (pdev && pdev->dis_rx_agc) {
        pdev->dis_rx_agc(pdev);
    }
}
static inline void wphy_device_enable_rx_agc(struct wphy_device *pdev)
{
    if (pdev && pdev->en_rx_agc) {
        pdev->en_rx_agc(pdev);
    }
}

static inline void wphy_device_config_rx_gain_tab(struct wphy_device *pdev, uint8 mcs, int8 RxGainVector[6])
{
    if (pdev && pdev->cfg_rx_gain_tab) {
        pdev->cfg_rx_gain_tab(pdev, mcs, RxGainVector);
    }
}

static inline void wphy_device_config_rx_idx(struct wphy_device *pdev, uint8 mcs, uint8 gain_idx)
{
    if (pdev && pdev->cfg_rx_gain_idx) {
        pdev->cfg_rx_gain_idx(pdev, mcs, gain_idx);
    }
}

static inline void wphy_device_config_cca_th(struct wphy_device *pdev, int8 cca_th_tab[11])
{
    if (pdev && pdev->cfg_cca_th) {
        pdev->cfg_cca_th(pdev, cca_th_tab);
    }
}

static inline uint8 wphy_device_get_approved_bw(struct wphy_device *pdev)
{
    if (pdev && pdev->get_best_bw) {
        return pdev->get_best_bw(pdev);
    } else {
        return 0;
    }
}

static inline void wphy_device_config_tx_sine_mode(struct wphy_device *pdev, uint8 mode, uint16 nSineStepSize)
{
    if (pdev && pdev->cfg_phy_tx_sine) {
        pdev->cfg_phy_tx_sine(pdev, mode, nSineStepSize);
    }
}

static inline void config_wphy_device_tx_tri_mode(struct wphy_device *pdev, uint8 mode, uint16 nSineStepSize)
{
    if (pdev && pdev->cfg_phy_tx_tri) {
        pdev->cfg_phy_tx_tri(pdev, mode, nSineStepSize);
    }
}

static inline void wphy_device_config_tx_norm_mode(struct wphy_device *pdev)
{
    if (pdev && pdev->cfg_phy_tx_norm) {
        pdev->cfg_phy_tx_norm(pdev);
    }
}

static inline void wphy_device_soft_reset(struct wphy_device *pdev)
{
    if (pdev && pdev->sw_rst_phy) {
        pdev->sw_rst_phy(pdev);
    }
}

static inline void wphy_device_soft_dereset(struct wphy_device *pdev)
{
    if (pdev && pdev->sw_derst_phy) {
        pdev->sw_derst_phy(pdev);
    }
}

static inline uint16 wphy_device_get_rx_psdu_crc(struct wphy_device *pdev)
{
    if (pdev && pdev->get_rx_psdu_crc) {
        return pdev->get_rx_psdu_crc(pdev);
    } else {
        return 0;
    }
}

static inline uint16 wphy_device_get_tx_psdu_crc(struct wphy_device *pdev)
{
    if (pdev && pdev->get_tx_psdu_crc) {
        return pdev->get_tx_psdu_crc(pdev);
    } else {
        return 0;
    }
}

static inline uint8 wphy_device_get_rx_sat_info(struct wphy_device *pdev)
{
    if (pdev && pdev->get_rx_sat_info) {
        return pdev->get_rx_sat_info(pdev);
    } else {
        return 0;
    }
}

static inline uint32 wphy_device_get_dpd_info(struct wphy_device *pdev)
{
    if (pdev && pdev->get_dpd_info) {
        return pdev->get_dpd_info(pdev);
    } else {
        return 0;
    }
}

static inline uint8 wphy_device_get_dpd_rx_sat_info(struct wphy_device *pdev)
{
    if (pdev && pdev->get_dpd_rx_sat_info) {
        return pdev->get_dpd_rx_sat_info(pdev);
    } else {
        return 0;
    }
}

static inline void wphy_device_enable_obss_sd_det(struct wphy_device *pdev)
{
    if (pdev && pdev->en_obss_sd_det) {
        pdev->en_obss_sd_det(pdev);
    }
}

static inline void wphy_device_disable_obss_sd_det(struct wphy_device *pdev)
{
    if (pdev && pdev->dis_obss_sd_det) {
        pdev->dis_obss_sd_det(pdev);
    }
}

// this function is to config obss signal detection parameter
// BssColor      : 0~7
// PartialBSSID  : 0~511
// drop_downlink : 0~1
// obss_sd       : -128~127 dBm
static inline void wphy_device_config_obss_para(struct wphy_device *pdev,  uint8 BssColor, uint16 PartialBSSID, uint8 drop_downlink, int8 obss_sd)
{
    if (pdev && pdev->cfg_obss_para) {
        pdev->cfg_obss_para(pdev, BssColor, PartialBSSID, drop_downlink, obss_sd);
    }
}

// output value 0~15
static inline uint8 wphy_device_get_tx_crc4(struct wphy_device *pdev)
{
    if (pdev && pdev->get_tx_crc4) {
        return pdev->get_tx_crc4(pdev);
    } else {
        return 0;
    }
}

// output value 0~15
static inline uint8 wphy_device_get_rx_crc4(struct wphy_device *pdev)
{
    if (pdev && pdev->get_rx_crc4) {
        return pdev->get_rx_crc4(pdev);
    } else {
        return 0;
    }
}

// 0: PHY_CTL.agc_bw  1:  nTxRxModemBW(dynamic_rx_bw_en == 1'b0)  RXPWRIDX.Rf_rx_bw(dynamic_rx_bw_en == 1'b1)
static inline void wphy_device_config_agc_bw_src(struct wphy_device *pdev, uint8 agc_bw_source)
{
    if (pdev && pdev->cfg_agc_bw_src) {
        pdev->cfg_agc_bw_src(pdev, agc_bw_source);
    }
}

// 2'd0 1M   2'd1 2M   2'd2 4M   2'd3 8M
static inline void wphy_device_config_agc_bw(struct wphy_device *pdev, uint8 agc_bw)
{
    if (pdev && pdev->cfg_agc_bw) {
        pdev->cfg_agc_bw(pdev, agc_bw);
    }
}

// 0: nTxRxModemBW   1: RXPWRIDX.Rf_rx_bw
static inline void wphy_device_config_rx_bw_src(struct wphy_device *pdev, uint8 rx_bw_src)
{
    if (pdev && pdev->cfg_phy_rx_bw_src) {
        pdev->cfg_phy_rx_bw_src(pdev, rx_bw_src);
    }
}

// adjust low power detect threshold according to energy of background noise
// nLowPowerTh : 5~15
static inline void wphy_device_config_low_pwr_th(struct wphy_device *pdev, uint8 nLowPowerTh)
{
    if (pdev && pdev->cfg_low_pwr_th) {
        pdev->cfg_low_pwr_th(pdev, nLowPowerTh);
    }
}


static inline void wphy_device_enable_auto_sig_err_rst(struct wphy_device *pdev)
{
    if (pdev && pdev->en_auto_sig_err_rst) {
        pdev->en_auto_sig_err_rst(pdev);
    }
}

static inline void wphy_device_disable_auto_sig_err_rst(struct wphy_device *pdev)
{
    if (pdev && pdev->dis_auto_sig_err_rst) {
        pdev->dis_auto_sig_err_rst(pdev);
    }
}

// m_bDPDen          0: disable  1: enable
// m_bDynamicDPDen   0: disable  1: enable
static inline void wphy_device_config_dpd(struct wphy_device *pdev, uint8 m_bDPDen, uint8 m_bDynamicDPDen)
{
    if (pdev && pdev->cfg_dpd) {
        pdev->cfg_dpd(pdev, m_bDPDen, m_bDynamicDPDen);
    }
}

// ref_pwr: [-128, 127] dBm   gain_idx: 0~5
// this function should be called during FT or module test
static inline int8 wphy_device_adjust_value(struct wphy_device *pdev, int8 ref_pwr, uint8 gain_idx)
{
    if (pdev && pdev->adj_gain_val) {
        return pdev->adj_gain_val(pdev, ref_pwr, gain_idx);
    } else {
        return 0;
    }
}

static inline void wphy_device_config_rx_fix_gain_idx(struct wphy_device *pdev, uint8 fix_gain_idx)
{
    if (pdev && pdev->cfg_rx_fix_gain_idx) {
        pdev->cfg_rx_fix_gain_idx(pdev, fix_gain_idx);
    }
}

static inline int32 wphy_device_get_rx_freq_offset(struct wphy_device *pdev)
{
    if (pdev && pdev->get_rx_freq_offset) {
        return pdev->get_rx_freq_offset(pdev);
    } else {
        return 0;
    }
}

static inline void wphy_device_get_rx_gain_para(struct wphy_device *pdev, int8 rx_gain_tab[6], int8 *p_conversion_gain)
{
    if (pdev && pdev->get_rx_gain_para) {
        pdev->get_rx_gain_para(pdev, rx_gain_tab, p_conversion_gain);
    }
}

static inline void wphy_device_config_rx_gain_stage(struct wphy_device *pdev, uint8 stage_num)
{
    if (pdev && pdev->cfg_rx_gain_stage) {
        pdev->cfg_rx_gain_stage(pdev, stage_num);
    }
}

#ifdef __cplusplus
}
#endif
#endif

