#ifndef  _HAL_DBGPATH_H_
#define  _HAL_DBGPATH_H_
#ifdef __cplusplus
extern "C" {
#endif

#define K_DBGPATH_NORMAL_MODE        0  // 0: normal (direction is controlled by MAC)
#define K_DBGPATH_RAM2DAC_MODE       1  // 1: RAM to DAC mode (TX RF test)
#define K_DBGPATH_RAM2PHY_MODE       2  // 2: RAM to PHY mode (RX PHY test)
#define K_DBGPATH_PHY2RAM_MODE       3  // 3: PHY to RAM mode (TX PHY test)
#define K_DBGPATH_ADC2RAM_MODE       4  // 4: ADC to RAM mode (RX RF test)
#define K_DBGPATH_ADC2RAM_DPD_MODE   5  // 5: ADC to RAM when tx enabled and tx data valid

// external io path mode
#define K_EXTPATH_TDD                0
#define K_EXTPATH_FDD                1

// debug pin name
#define K_DBG_SEL0                   0
#define K_DBG_SEL1                   1
#define K_DBG_SEL2                   2
#define K_DBG_SEL3                   3
#define K_DBG_SEL4                   4
#define K_DBG_SEL5                   5
#define K_DBG_SEL6                   6
#define K_DBG_SEL7                   7

// signal name for debug
#define K_DBGOUT_TX_REQ                            0   // lmac_dbgo[0 ]
#define K_DBGOUT_RX_REQ                            1   // lmac_dbgo[1 ]
#define K_DBGOUT_MACDATA_VALID                     2   // lmac_dbgo[2 ]
#define K_DBGOUT_PHY_RDY                           3   // lmac_dbgo[3 ]
#define K_DBGOUT_TXEND                             4   // lmac_dbgo[4 ]
#define K_DBGOUT_TXERR                             5   // lmac_dbgo[5 ]
#define K_DBGOUT_RXERR_P                           6   // lmac_dbgo[6 ]
#define K_DBGOUT_RX_LAST_BYTE                      7   // lmac_dbgo[7 ]
#define K_DBGOUT_RX_SYNC                           8   // lmac_dbgo[8 ]
#define K_DBGOUT_RX_CCA_PRI_1M                     9   // lmac_dbgo[9 ]
#define K_DBGOUT_RX_CCA_PRI_2M                     10  // lmac_dbgo[10]
#define K_DBGOUT_RX_CCA_SEC_2M                     11  // lmac_dbgo[11]
#define K_DBGOUT_RX_CCA_SEC_4M                     12  // lmac_dbgo[12]
#define K_DBGOUT_RX_BW_IDC0                        13  // lmac_dbgo[13]
#define K_DBGOUT_RX_BW_IDC1                        14  // lmac_dbgo[14]
#define K_DBGOUT_RX_BAS2M_IDC                      15  // lmac_dbgo[15]
#define K_DBGOUT_RX_LONG_IDC                       16  // lmac_dbgo[16]
#define K_DBGOUT_RX_DUP8M_DET                      17  // lmac_dbgo[17]
#define K_DBGOUT_RX_DUP4M_DET                      18  // lmac_dbgo[18]
#define K_DBGOUT_CCAPRIMARY1START                  19  // lmac_dbgo[19]
#define K_DBGOUT_CCAPRIMARY2START                  20  // lmac_dbgo[20]
#define K_DBGOUT_CCAPRIMARY1MID                    21  // lmac_dbgo[21]
#define K_DBGOUT_CCAPRIMARY2MID                    22  // lmac_dbgo[22]
#define K_DBGOUT_CCASECONDARY2MID                  23  // lmac_dbgo[23]
#define K_DBGOUT_CCASECONDARY4MID                  24  // lmac_dbgo[24]
#define K_DBGOUT_CCAPRIMARY1ED                     25  // lmac_dbgo[25]
#define K_DBGOUT_CCAPRIMARY2ED                     26  // lmac_dbgo[26]
#define K_DBGOUT_CCASECONDARY2ED                   27  // lmac_dbgo[27]
#define K_DBGOUT_CCASECONDARY4ED                   28  // lmac_dbgo[28]
#define K_DBGOUT_RX_END_TIMING_D2                  29  // lmac_dbgo[29]
#define K_DBGOUT_RXEND_P_MD                        30  // lmac_dbgo[30]
#define K_DBGOUT_RF_EN                             31  // lmac_dbgo[31]
#define K_DBGOUT_MAC_PA_EN                         32  // lmac_dbgo[32]
#define K_DBGOUT_MAC_DAC_EN                        33  // lmac_dbgo[33]
#define K_DBGOUT_RF_TX_EN                          34  // lmac_dbgo[34]
#define K_DBGOUT_MAC_RF_RX_EN                      35  // lmac_dbgo[35]
#define K_DBGOUT_TX_DUP_EN_NEW                     36  // lmac_dbgo[36]
#define K_DBGOUT_RX_SYNC_WIN                       37  // lmac_dbgo[37]
#define K_DBGOUT_TX_SIG_BW_NEW0                    38  // lmac_dbgo[38]
#define K_DBGOUT_TX_SIG_BW_NEW1                    39  // lmac_dbgo[39]
#define K_DBGOUT_SWITCH_RX_EN_O                    41  // rfif_dbgo[01]
#define K_DBGOUT_ADC_ENABLE                        42  // rfif_dbgo[02]
#define K_DBGOUT_PA_EN                             43  // rfif_dbgo[03]
#define K_DBGOUT_RFIP_RX_ENABLE                    44  // rfif_dbgo[04]
#define K_DBGOUT_HW_DAC_EN                         45  // rfif_dbgo[05]
#define K_DBGOUT_RFIP_IDX_LATCH                    46  // rfif_dbgo[06]
#define K_DBGOUT_RFIP_GAIN_INDEX0                  47  // rfif_dbgo[07]
#define K_DBGOUT_RFIP_GAIN_INDEX1                  48  // rfif_dbgo[08]
#define K_DBGOUT_RFIP_GAIN_INDEX2                  49  // rfif_dbgo[09]
#define K_DBGOUT_DAC_MODE_CTL0                     50  // rfif_dbgo[10]
#define K_DBGOUT_DAC_MODE_CTL1                     51  // rfif_dbgo[11]
#define K_DBGOUT_ADC0_SAREN_VDD                    52  // rfif_dbgo[12]
#define K_DBGOUT_RFIP_TX_EN                        53  // rfif_dbgo[13]
#define K_DBGOUT_PHY_RXINFO1_APPROVED_BW10         56  // modem_dbgo[0 ]
#define K_DBGOUT_PHY_RXINFO1_APPROVED_BW11         57  // modem_dbgo[1 ]
#define K_DBGOUT_PHY_INFO_IND_M_BLTF1MPPDU         58  // modem_dbgo[2 ]
#define K_DBGOUT_DPD_DISTORT_EN                    59  // modem_dbgo[3 ]
#define K_DBGOUT_RX_PHY_RDY                        60  // modem_dbgo[4 ]
#define K_DBGOUT_TX_PHY_RDY                        61  // modem_dbgo[5 ]
#define K_DBGOUT_PHY_INFO_IND_TXCRC4_31            62  // modem_dbgo[6 ]
#define K_DBGOUT_PHY_INFO_IND_TXCRC4_30            63  // modem_dbgo[7 ]
#define K_DBGOUT_PHY_INFO_IND_TXCRC4_29            64  // modem_dbgo[8 ]
#define K_DBGOUT_PHY_INFO_IND_TXCRC4_28            65  // modem_dbgo[9 ]
#define K_DBGOUT_LTF_DETECT_ERROR1AND2             66  // modem_dbgo[10]
#define K_DBGOUT_11                                67  // modem_dbgo[11]
#define K_DBGOUT_12                                68  // modem_dbgo[12]
#define K_DBGOUT_13                                69  // modem_dbgo[13]
#define K_DBGOUT_14                                70  // modem_dbgo[14]
#define K_DBGOUT_15                                71  // modem_dbgo[15]
#define K_DBGOUT_16                                72  // modem_dbgo[16]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE4         73  // modem_dbgo[17]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE5         74  // modem_dbgo[18]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE6         75  // modem_dbgo[19]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE7         76  // modem_dbgo[20]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE8         77  // modem_dbgo[21]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE9         78  // modem_dbgo[22]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE10        79  // modem_dbgo[23]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE11        80  // modem_dbgo[24]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE12        81  // modem_dbgo[25]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE13        82  // modem_dbgo[26]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE14        83  // modem_dbgo[27]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE15        84  // modem_dbgo[28]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE16        85  // modem_dbgo[29]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE17        86  // modem_dbgo[30]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE18        87  // modem_dbgo[31]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE19        88  // modem_dbgo[32]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE20        89  // modem_dbgo[33]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE21        90  // modem_dbgo[34]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE22        91  // modem_dbgo[35]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE23        92  // modem_dbgo[36]
#define K_DBGOUT_PHY_STATE_INFO0_RX_STATE24        93  // modem_dbgo[37]
#define K_DBGOUT_PHY_STATE_INFO0_MACIF_STATE0      94  // modem_dbgo[38]
#define K_DBGOUT_PHY_STATE_INFO0_MACIF_STATE1      95  // modem_dbgo[39]
#define K_DBGOUT_PHY_STATE_INFO0_MACIF_STATE2      96  // modem_dbgo[40]
#define K_DBGOUT_PHY_STATE_INFO0_MACIF_STATE3      97  // modem_dbgo[41]
#define K_DBGOUT_PHY_STATE_INFO1_TX_STATE0         98  // modem_dbgo[42]
#define K_DBGOUT_PHY_STATE_INFO1_TX_STATE1         99  // modem_dbgo[43]
#define K_DBGOUT_PHY_STATE_INFO1_TX_STATE2         100 // modem_dbgo[44]
#define K_DBGOUT_PHY_STATE_INFO1_TX_STATE3         101 // modem_dbgo[45]
#define K_DBGOUT_PHY_STATE_INFO1_TX_STATE4         102 // modem_dbgo[46]
#define K_DBGOUT_PHY_STATE_INFO1_TX_STATE5         103 // modem_dbgo[47]
#define K_DBGOUT_PHY_STATE_INFO1_TX_STATE6         104 // modem_dbgo[48]
#define K_DBGOUT_PHY_STATE_INFO1_TX_STATE7         105 // modem_dbgo[49]
#define K_DBGOUT_PHY_STATE_INFO1_TX_STATE8         106 // modem_dbgo[50]
#define K_DBGOUT_PHY_STATE_INFO1_TX_STATE9         107 // modem_dbgo[51]
#define K_DBGOUT_VITERBI_STATE0                    108 // modem_dbgo[52]
#define K_DBGOUT_VITERBI_STATE1                    109 // modem_dbgo[53]
#define K_DBGOUT_VITERBI_STATE2                    110 // modem_dbgo[54]
#define K_DBGOUT_VITERBI_STATE3                    111 // modem_dbgo[55]
#define K_DBGOUT_FILLBUF_END                       112 // modem_dbgo[56]
#define K_DBGOUT_FILLBUF_END_48M                   113 // modem_dbgo[57]

// for configure all enable bits of debug path module
union _DBGPATH_EN_BITS {
    struct {
        // bit 0
        // 1'b1:overide lmac pa_en (debug path generate)    1'b0:no overide (default)
        uint32           en_pa_ovrd                          :  1,
                         //----------------------------------------------------
                         // bit 1
                         en_dac_ovrd                         :  1,
                         //----------------------------------------------------
                         // bit 2
                         en_adc_ovrd                         :  1,
                         //----------------------------------------------------
                         // bit 3
                         en_extra_rf_rx                      :  1,
                         //----------------------------------------------------
                         // bit 4
                         en_rx_switch_ovrd                   :  1,
                         //----------------------------------------------------
                         // bit 5
                         en_tx_switch_ovrd                   :  1,
                         //----------------------------------------------------
                         // bit 6
                         en_bk_noise                         :  1,
                         //----------------------------------------------------
                         // bit 7
                         en_rx_dc_est                        :  1,
                         //----------------------------------------------------
                         // bit 8
                         dpd_fb_adc_en                       :  1,
                         //----------------------------------------------------
                         // bit 9
                         dpd_fbadcen_sel                     :  1,
                         //----------------------------------------------------
                         // bit 10
                         // 1'b1: fb_adc_en enabled by modem hardware adapt dpd enable
                         // 1'b0: fb_adc_en enabled by dpd_fb_adc_en
                         mipi_en                             :  1,
                         //----------------------------------------------------
                         // bit 11
                         // Determine whether to clear control interface once MIPI error has been detected
                         // 0: disable
                         // 1: enable
                         mipi_err_clr_io                     :  1,
                         //----------------------------------------------------
                         // bit 12 (read only)
                         reserved0                           :  1,
                         //----------------------------------------------------
                         // bit 13
                         // 1'b0:select rf spi rf_lo_freq hardware trigger for tx4001 rf
                         // 1'b1:select rf spi gain_idx hardware trigger for 9361
                         sel_9361_hwspi                      :  1,
                         //----------------------------------------------------
                         // bit 14
                         reserved1                           :  1,
                         //----------------------------------------------------
                         // bit 15
                         // 1'b1:enable rfif  (debug path generate io-timing)
                         // 1'b0:disable and sync reset rfif sub-module to initial state
                         rfif_enable                         :  1,
                         //----------------------------------------------------
                         // bit 16
                         Ext_rf_en                           :  1,
                         //----------------------------------------------------
                         // bit 17
                         mipictl0_auto_trig_en               :  1,
                         //----------------------------------------------------
                         // bit 18
                         mipictl1_auto_trig_en               :  1,
                         //----------------------------------------------------
                         // bit 19
                         mipictl2_auto_trig_en               :  1,
                         //----------------------------------------------------
                         // bit 20
                         mipictl3_auto_trig_en               :  1,
                         //----------------------------------------------------
                         // bit 21
                         mipictl4_auto_trig_en               :  1,
                         //----------------------------------------------------
                         // bit 22
                         mipictl5_auto_trig_en               :  1,
                         //----------------------------------------------------
                         // bit 23:31
                         reserved                            :  9;
        //----------------------------------------------------
    } para;
    uint16 half_word_buf[2];
    uint32 word_var;
};

struct dbgpath_device {
    struct dev_obj dev;
    void(*init)(struct dbgpath_device *pdev);
    void(*set_tx_dly)(struct dbgpath_device *pdev, uint8 ndly);
    void(*set_rx_dly)(struct dbgpath_device *pdev, uint8 ndly);
    void(*set_extspi_tx_pwr)(struct dbgpath_device *pdev, uint16 naddr, uint8 nval);
    void(*set_extspi_rx_gain)(struct dbgpath_device *pdev, uint16 naddr, uint8 nval);
    void(*set_extspi_dpd_gain)(struct dbgpath_device *pdev, uint16 naddr, uint8 nval);
    void(*en_ext_dpd_gain)(struct dbgpath_device *pdev);
    void(*dis_ext_dpd_gain)(struct dbgpath_device *pdev);
    uint32(*get_stop_pos)(struct dbgpath_device *pdev, uint32 dma_buflen);
    void(*trig_dma)(struct dbgpath_device *pdev);
    void(*trig_dma2)(struct dbgpath_device *pdev);
    void(*abort_dma)(struct dbgpath_device *pdev);
    void(*abort_dma2)(struct dbgpath_device *pdev);
    void(*cfg_dmaend_cond)(struct dbgpath_device *pdev, uint8 ncond);
    void(*set_path_mode)(struct dbgpath_device *pdev, uint8 nmode);
    void(*cfg_tdma2_en_bit)(struct dbgpath_device *pdev, uint8 on_off);
    void(*cfg_ext_path)(struct dbgpath_device *pdev, uint8 tdd_or_fdd);
    void(*cfg_dbg_out)(struct dbgpath_device *pdev, uint8 dbg_pin_sel, uint8 dbg_src_sel); // dbg_pin_sel: 0~7   dbg_src_sel: 0~127
    void(*cfg_dbg_en_bits)(struct dbgpath_device *pdev, union _DBGPATH_EN_BITS en_bits); // config all enable bits of debug path module
    uint8(*get_mipi_err_info)(struct dbgpath_device *pdev);  // get rf mipi error information
    void (*clr_mipi_err_info)(struct dbgpath_device *pdev); // clear rf mipi error information
    // only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    void(*set_tx_pwr)(struct dbgpath_device *pdev, uint8 npwr_idx);  // npwr_idx: 0~9
    // only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    void(*tune_tx_dcoc)(struct dbgpath_device *pdev);
    // only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    void(*tune_tx_imb)(struct dbgpath_device *pdev);
    // only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    void(*cfg_tx_dcoc)(struct dbgpath_device *pdev, int16 i_val, int16 q_val);
    // only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    void(*cfg_tx_imb)(struct dbgpath_device *pdev, int16 phase_comp, uint16 gain_comp);
    // only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    void(*mod_tx_pwr_tab)(struct dbgpath_device *pdev, int16 iq_val[2], int16 phase_comp, uint16 gain_comp, uint8 npwr_idx);
    // only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    void(*cfg_tx_digi_gain)(struct dbgpath_device *pdev, uint16 tx_digi_gain);
    // only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    uint16(*get_tx_digi_gain)(struct dbgpath_device *pdev);
};

static inline void init_dbgpath_device(struct dbgpath_device *pdev)
{
    if (pdev && pdev->init) {
        pdev->init(pdev);
    }
}

static inline void set_dbgpath_device_tx_dly(struct dbgpath_device *pdev, uint8 ndly)
{
    if (pdev && pdev->set_tx_dly) {
        pdev->set_tx_dly(pdev, ndly);
    }
}

static inline void set_dbgpath_device_rx_dly(struct dbgpath_device *pdev, uint8 ndly)
{
    if (pdev && pdev->set_rx_dly) {
        pdev->set_rx_dly(pdev, ndly);
    }
}

static inline void set_dbgpath_device_extspi_tx_pwr(struct dbgpath_device *pdev, uint16 naddr, uint8 nval)
{
    if (pdev && pdev->set_extspi_tx_pwr) {
        pdev->set_extspi_tx_pwr(pdev, naddr, nval);
    }
}

static inline void set_dbgpath_device_extspi_rx_gain(struct dbgpath_device *pdev, uint16 naddr, uint8 nval)
{
    if (pdev && pdev->set_extspi_rx_gain) {
        pdev->set_extspi_rx_gain(pdev, naddr, nval);
    }
}

static inline void set_dbgpath_device_extspi_dpd_gain(struct dbgpath_device *pdev, uint16 naddr, uint8 nval)
{
    if (pdev && pdev->set_extspi_dpd_gain) {
        pdev->set_extspi_dpd_gain(pdev, naddr, nval);
    }
}

static inline void enable_dbgpath_device_ext_dpd_gain(struct dbgpath_device *pdev)
{
    if (pdev && pdev->en_ext_dpd_gain) {
        pdev->en_ext_dpd_gain(pdev);
    }
}

static inline void disable_dbgpath_device_ext_dpd_gain(struct dbgpath_device *pdev)
{
    if (pdev && pdev->dis_ext_dpd_gain) {
        pdev->dis_ext_dpd_gain(pdev);
    }
}

static inline uint32 get_dbgpath_device_stop_pos(struct dbgpath_device *pdev, uint32 dma_buflen)
{
    if (pdev && pdev->get_stop_pos) {
        return pdev->get_stop_pos(pdev, dma_buflen);
    } else {
        return 0;
    }
}

static inline void trig_dbgpath_device_dma(struct dbgpath_device *pdev)
{
    if (pdev && pdev->trig_dma) {
        pdev->trig_dma(pdev);
    }
}

static inline void trig_dbgpath_device_dma2(struct dbgpath_device *pdev)
{
    if (pdev && pdev->trig_dma2) {
        pdev->trig_dma2(pdev);
    }
}

static inline void abort_dbgpath_device_dma(struct dbgpath_device *pdev)
{
    if (pdev && pdev->abort_dma) {
        pdev->abort_dma(pdev);
    }
}

static inline void abort_dbgpath_device_dma2(struct dbgpath_device *pdev)
{
    if (pdev && pdev->abort_dma2) {
        pdev->abort_dma2(pdev);
    }
}

// only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
static inline void set_dbgpath_device_tx_pwr(struct dbgpath_device *pdev, uint8 npwr_idx)
{
    if (pdev && pdev->set_tx_pwr) {
        pdev->set_tx_pwr(pdev, npwr_idx);
    }
}

// only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
static inline void tune_dbgpath_device_tx_dcoc(struct dbgpath_device *pdev)
{
    if (pdev && pdev->tune_tx_dcoc) {
        pdev->tune_tx_dcoc(pdev);
    }
}

// only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
static inline void tune_dbgpath_device_tx_imb(struct dbgpath_device *pdev)
{
    if (pdev && pdev->tune_tx_imb) {
        pdev->tune_tx_imb(pdev);
    }
}

// only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
static inline void config_dbgpath_device_tx_dcoc(struct dbgpath_device *pdev, int16 i_val, int16 q_val)
{
    if (pdev && pdev->cfg_tx_dcoc) {
        pdev->cfg_tx_dcoc(pdev, i_val, q_val);
    }
}

// only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
static inline void config_dbgpath_device_tx_imb(struct dbgpath_device *pdev, int16 phase_comp, uint16 gain_comp)
{
    if (pdev && pdev->cfg_tx_imb) {
        pdev->cfg_tx_imb(pdev, phase_comp, gain_comp);
    }
}

// only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
static inline void modify_dbgpath_device_tx_pwr_tab(struct dbgpath_device *pdev, int16 iq_val[2], int16 phase_comp, uint16 gain_comp, uint8 npwr_idx)
{
    if (pdev && pdev->mod_tx_pwr_tab) {
        pdev->mod_tx_pwr_tab(pdev, iq_val, phase_comp, gain_comp, npwr_idx);
    }
}

// only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
static inline void config_dbgpath_device_tx_digi_gain(struct dbgpath_device *pdev, uint16 tx_digi_gain)
{
    if (pdev && pdev->cfg_tx_digi_gain) {
        pdev->cfg_tx_digi_gain(pdev, tx_digi_gain);
    }
}

// only for RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
static inline uint16 get_dbgpath_device_tx_digi_gain(struct dbgpath_device *pdev)
{
    if (pdev && pdev->get_tx_digi_gain) {
        return  pdev->get_tx_digi_gain(pdev);
    } else{
        return 0;
    }
}

static inline void config_dbgpath_device_dmaend_cond(struct dbgpath_device *pdev, uint8 ncond)
{
    if (pdev && pdev->cfg_dmaend_cond) {
        pdev->cfg_dmaend_cond(pdev, ncond);
    }
}

static inline void set_dbgpath_device_path_mode(struct dbgpath_device *pdev, uint8 nmode)
{
    if (pdev && pdev->set_path_mode) {
        pdev->set_path_mode(pdev, nmode);
    }
}

static inline void set_dbgpath_device_tdma2_en_bit(struct dbgpath_device *pdev, uint8 on_off)
{
    if (pdev && pdev->cfg_tdma2_en_bit) {
        pdev->cfg_tdma2_en_bit(pdev, on_off);
    }
}

static inline void config_dbgpath_device_ext_path(struct dbgpath_device *pdev, uint8 tdd_or_fdd)
{
    if (pdev && pdev->cfg_ext_path) {
        pdev->cfg_ext_path(pdev, tdd_or_fdd);
    }
}

static inline void config_dbgpath_device_dbg_out(struct dbgpath_device *pdev, uint8 dbg_pin_sel, uint8 dbg_src_sel)
{
    if (pdev && pdev->cfg_dbg_out) {
        pdev->cfg_dbg_out(pdev, dbg_pin_sel, dbg_src_sel);
    }
}

// config all enable bits of debug path module
static inline void config_dbgpath_device_enable_bits(struct dbgpath_device *pdev, union _DBGPATH_EN_BITS en_bits)
{
    if (pdev && pdev->cfg_dbg_en_bits) {
        pdev->cfg_dbg_en_bits(pdev, en_bits);
    }
}

// get rf mipi information
static inline uint8 get_dbgpath_device_rfmipi_err_info(struct dbgpath_device *pdev)
{
    if (pdev && pdev->get_mipi_err_info) {
        return  pdev->get_mipi_err_info(pdev);
    } else{
        return 0;
    }
}

// clear rf mipi error information
static inline void clear_dbgpath_device_rfmipi_err_info(struct dbgpath_device *pdev)
{
    if (pdev && pdev->clr_mipi_err_info) {
        pdev->clr_mipi_err_info(pdev);
    }
}

#ifdef __cplusplus
}
#endif
#endif

