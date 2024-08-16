// hgwphy_ah.h
// 802dot11ah phy software access register definition
#ifndef _HGWPHY_AH_H_
#define _HGWPHY_AH_H_

#define K_AGC_STEP_NUM        6
#define K_MCS_NUM            11           // MCS0~10
#define K_RX_GAIN_INDEX_NUM   6

//#define K_RX_FIX_GAIN_EN
#define K_RX_INIT_GAIN_INDEX  0x5

//#define K_PRINT_WPHY_AH_PARAMETER
#define K_NSERVICE        8
#define K_NES             1
#define K_NTAIL           6
#define K_MSTBC           1

#define K_USE_DPD_RAM     1 // penghong 190925

struct REG48BIT {
    __IO uint32 REGL;
    __IO uint32 REGH;
};

struct hgwphy_gain_cfg {
    // dBm MCS0/MCS10    [gain_stage]
    int8              IncreaseGainTH[K_AGC_STEP_NUM - 1];
    //----------------------------------------------------
    // dBm MCS0/MCS10    [gain_stage]
    int8              ReduceGainTH[K_AGC_STEP_NUM - 1];
    //----------------------------------------------------
    // dBm               [mcs][gain_stage]
    int8              GainThVector[7][K_AGC_STEP_NUM - 1];
    //----------------------------------------------------
    // dB                [mcs][gain_stage]
    int8              RxGainVector[8][K_AGC_STEP_NUM];
    //----------------------------------------------------
    // 37th parameter
    // rf_rx_gain_index  [mcs][gain_stage] uint5
    uint8             RxIndexVector[8][K_AGC_STEP_NUM];
    //----------------------------------------------------
};

struct hgwphy_ah_cfg {
    //----------------------------------------------------
    // 1st parameter
    // 0: Tx mode   1: Rx modes
    // not used for register initialization, discard it
    // bit 0
    // uint32           m_bTxRxMode                        :   1;
    //----------------------------------------------------
    // 2nd parameter
    // Primary Channel Number
    // Bit field 3:0 is valid if supported bandwidth is 16M and S1G_1M PPDU.
    // Bit field 2:0 is valid if supported bandwidth is 8M and S1G_1M PPDU.
    // Bit field 1:0 is valid if supported bandwidth is 4M and S1G_1M PPDU.
    // Bit field 0 is valid if supported bandwidth is 2M and S1G_1M PPDU.
    // Bit field 2:0 is valid if supported bandwidth is 8M and S1G_2 PPDU.
    // Bit field 1:0 is valid if supported bandwidth is 4M and S1G_2 PPDU.
    // Bit field 0 is valid if supported bandwidth is 2M and S1G_2M PPDU.
    // bit 0:2
    uint32           Primary_CH                            :   3,
    //----------------------------------------------------
    // 3rd parameter
    // approved value is 0 (disable zero if mode)
    // bit 3
                      m_bZeroIF                            :   1,
    //----------------------------------------------------
    // 4th parameter
    // Enable continuous transmit mode.  (for debug use)
    // bit 4
                      continuousTx                         :   1,
    //----------------------------------------------------
    // 5th parameter
    // STF boost control of 1M NDP packet
    // bit 5
                      m_bNDP1m_boost_en                    :   1,
    //----------------------------------------------------
    // 6th parameter
    // maximum rx modem decoding bandwidth
    // 2'b00: 1MHz  if PPDU (SIG_SHORT/LONG.BW+1) > 1MHz Error Code = K_RX_INSUFFICIENT_BW/K_TX_INSUFFICIENT_BW
    // 2'b01: 2MHz  if PPDU (SIG_SHORT/LONG.BW+1) > 2MHz Error Code = K_RX_INSUFFICIENT_BW/K_TX_INSUFFICIENT_BW
    // 2'b10: 4MHz  if PPDU (SIG_SHORT/LONG.BW+1) > 4MHz Error Code = K_RX_INSUFFICIENT_BW/K_TX_INSUFFICIENT_BW
    // 2'b11: 8MHz  if PPDU (SIG_SHORT/LONG.BW+1) > 8MHz Error Code = K_RX_INSUFFICIENT_BW/K_TX_INSUFFICIENT_BW
    // bit 6:7
                      nTxRxModemBW                         :   2,
    //----------------------------------------------------
    // 7th parameter
    // packet_detect_threshold, unsigned Q0.8
    // bit 8:15
                      packet_detect_threshold              :   8,
    //----------------------------------------------------
    // 8th parameter
    // nPrimary1SyncConfirmTimeTh  [0 255]
    // bit 16:23
                      nPrimary1SyncConfirmTimeTh           :   8,
    //----------------------------------------------------
    // 9th parameter
    // nPrimary1SyncConfirmTimeTh  [0 255]
    // bit 24:31
                      nPrimary2SyncConfirmTimeTh           :   8;
    //----------------------------------------------------
    // 10th parameter
    // nSecondary2SyncConfirmTimeTh  [0 255]
    // bit 0:7
    uint32            nSecondary2SyncConfirmTimeTh         :   8,
    //----------------------------------------------------
    // 11th parameter
    // nSecondary4SyncConfirmTimeTh  [0 255]
    // bit 8:15
                      nSecondary4SyncConfirmTimeTh         :   8,
    //----------------------------------------------------
    // 12th parameter
    // nLowPowerTh [0 15]
    // bit 16:19
                      nLowPowerTh                          :   4,
    //----------------------------------------------------
    // 13th parameter
    // nLowPower2mDiv1mTh
    // threshold of power ratio of secondary2 to primary1
    // 0: Secondary2_POWER/Primary1_POWER<2^(-1)
    // 1: Secondary2_POWER/Primary1_POWER<2^(-2)
    // 2: Secondary2_POWER/Primary1_POWER<2^(-3)
    // 3: Secondary2_POWER/Primary1_POWER<2^(-4)
    // bit 20:21
                      nLowPower2mDiv1mTh                   :   2,
    //----------------------------------------------------
    // 14th parameter
    // nLowPower4mDiv1mTh
    // threshold of power ratio of secondary2 to primary1
    // 0: Secondary4_POWER/Primary1_POWER<2^0
    // 1: Secondary4_POWER/Primary1_POWER<2^(-1)
    // 2: Secondary4_POWER/Primary1_POWER<2^(-2)
    // 3: Secondary4_POWER/Primary1_POWER<2^(-3)
    // bit 22:23
                      nLowPower4mDiv1mTh                   :   2,
    //----------------------------------------------------
    // 15th parameter
    // the threshold of STS counter to detect 1M or 2/4/8M packet is received
    // if K_RX_PRIMARY1_STS_DETECT_TAP_LEN == K_LSTS_1M_LEN, approved value is 8
    // if K_RX_PRIMARY1_STS_DETECT_TAP_LEN == K_LSTS_1M_LEN*2, approved value is 7
    // bit 24:28
                      nLtfDetector1M2MTh                   :   5,
    //----------------------------------------------------
    // 16th parameter
    // if m_bModifyFreqOffsetAtStsSync == false, approved value is 0;
    // if m_bModifyFreqOffsetAtStsSync == true, approved value is 1;(discard 1st STS symobl after frequency has been changed)
    // bit 29:30
                      nPrimary1LtfDetectorCorrStartCounter :   2,
    // bit 31
                      reserved0                            :   1;
    //----------------------------------------------------
    // 17th parameter
    // if m_bModifyFreqOffsetAtStsSync == false, approved value is 0;
    // if m_bModifyFreqOffsetAtStsSync == true, approved value is 1;(discard 1st STS symobl after frequency has been changed)
    // bit 0:1
    uint32            nPrimary2LtfDetectorCorrStartCounter :   2,
    //----------------------------------------------------
    // 18th parameter
    // Scale factor for LTF synchronization, approved yb_scaler is 1, 2 or 3
    // bit 2:3
                      yb_scaler                            :   2,
    //----------------------------------------------------
    // 19th parameter
    // determine whether to estimate channel response in DLTF symbol
    // bit 4
                      m_bEstimateDltfChannel               :   1,
    //----------------------------------------------------
    // 20th parameter
    // determine whether to estimate channel response in SIGB symbol
    // bit 5
                      m_bEstimateSigbChannel               :   1,
    //----------------------------------------------------
    // 21th parameter
    // determine whether to enable channel smoothing for channel estimation
    // bit 6
                      m_bChannelSmoothing                  :   1,
    //----------------------------------------------------
    // 22th parameter
    // coarse timing increase or decrease or keep stable threshold [0 127]
    // bit 7:13
                      coarse_timing_th                     :   7,
    //----------------------------------------------------
    // 23th parameter
    // nSymbolTimingAverageTimes  // [0 10]
    // bit 14:17
                      nSymbolTimingAverageTimes            :   4,
    //----------------------------------------------------
    // 24th parameter
    // 1M PPDU Average times of delta_phase [0 7]
    // bit 18:20
                      delta_phase_avg_times_1m             :   3,
    //----------------------------------------------------
    // 25th parameter
    // 2/4/8M PPDU Average times of delta_phase [0 7]
    // bit 21:23
                      delta_phase_avg_times_248m           :   3,
    //----------------------------------------------------
    // 26th parameter
    // wait cycle for Mn valid, [0 255] @32MSPS
    // bit 24:31
                      PowerCorrWaitDuration                :   8;
    //----------------------------------------------------
    // 27th parameter
    // wait cycle for non-zero signal filling the delay tap, [0 255] @32MSPS
    // bit 0:7
    uint32            DcEstimateWaitDuration               :   8,
    // bit 8:31
                      reserved1                            :  24;
    //----------------------------------------------------
    // 28th parameter
    // estimated dc offset for DC component compensation
    int8              default_estimated_dc_offset_vec[2][K_RX_GAIN_INDEX_NUM];
    //----------------------------------------------------
    // 29th parameter
    // Wait times before 1st AGC power calculation, 0~4095  (@32MSPS)
    // bit 0:11
    uint32            nAgcStartSample                      :  12,
    //----------------------------------------------------
    // 30th parameter
    // 0~255 (@32MSPS) 8us STS
    // bit 12:19
                      nAgcStableDuration                   :   8,
    //----------------------------------------------------
    // 31th parameter
    // -128~127 dB
    // bit 20:27
                      conversion_gain_dB                   :   8,
    //----------------------------------------------------
    // 32th parameter
    // 0: false  1: lock
    // bit 28
                      m_bAgcFreezeEn                       :   1,
    // bit 29:31
                      reserved2                            :   3;
    //----------------------------------------------------
    // 33th parameter
    // dBm MCS0/MCS10    [gain_stage]
    int8              IncreaseGainTH[K_AGC_STEP_NUM - 1];
    //----------------------------------------------------
    // 34th parameter
    // dBm MCS0/MCS10    [gain_stage]
    int8              ReduceGainTH[K_AGC_STEP_NUM - 1];
    //----------------------------------------------------
    // 35th parameter
    // dBm               [mcs][gain_stage]
    int8              GainThVector[7][K_AGC_STEP_NUM - 1];
    //----------------------------------------------------
    // 36th parameter
    // dB                [mcs][gain_stage]
    int8              RxGainVector[8][K_AGC_STEP_NUM];
    //----------------------------------------------------
    // 37th parameter
    // rf_rx_gain_index  [mcs][gain_stage] uint5
    uint8             RxIndexVector[8][K_AGC_STEP_NUM];
    //----------------------------------------------------
    // 39th parameter (note: 38th parameter is in debug.h)
    // 1st time frequency offset compensation
    // bit 0
    uint8             m_bModifyFreqOffsetAtStsSync         :   1,
    //----------------------------------------------------
    // 40th parameter
    // 2nd time frequency offset compensation
    // bit 1
                      m_bmodifyFreqOffsetAtLtfSync         :   1,
    //----------------------------------------------------
    // 41th parameter
    // 3rd time frequency offset compensation
    // bit 2
                      m_bmodifyFreqOffsetAtLtfEnd          :   1,
    //----------------------------------------------------
    // 42th parameter
    // dc removal control
    // 0: Dc removal off   1: 31/32   2: 63/64  3: 127/128
    // bit 3:4
                      nDcRemovalType                       :   2,
    //----------------------------------------------------
    // 43th parameter
    // rx noise add control
    // bit 5
                      m_bAddNoiseBeforeStsSync             :   1,
    // bit 6:7
                      reserved3                            :   2;
    //----------------------------------------------------
    // 44th parameter
    // CCA primary1 OFDM STS detection energy threshold [-128,127] dBm
    int8              nPrimary1StartTh;
    //----------------------------------------------------
    // 45th parameter
    // CCA primary2 OFDM STS detection energy threshold [-128,127] dBm
    int8              nPrimary2StartTh;
    //----------------------------------------------------
    // 46th parameter
    // CCA primary1 OFDM symbol detection energy threshold [-128,127] dBm
    int8              nPrimary1MidTh;
    //----------------------------------------------------
    // 47th parameter
    // CCA primary2 OFDM symbol detection energy threshold [-128,127] dBm
    int8              nPrimary2MidTh;
    //----------------------------------------------------
    // 48th parameter
    // CCA secondary2 OFDM symbol detection energy threshold [-128,127] dBm
    int8              nSecondary2MidTh;
    //----------------------------------------------------
    // 49th parameter
    // CCA secondary4 OFDM symbol detection energy threshold [-128,127] dBm
    int8              nSecondary4MidTh;
    //----------------------------------------------------
    // 50th parameter
    // CCA primary1 energy detection energy threshold [-128,127] dBm
    int8              nPrimary1EdTh;
    //----------------------------------------------------
    // 51th parameter
    // CCA primary2 energy detection energy threshold [-128,127] dBm
    int8              nPrimary2EdTh;
    //----------------------------------------------------
    // 52th parameter
    // CCA secondary2 energy detection energy threshold [-128,127] dBm
    int8              nSecondary2EdTh;
    //----------------------------------------------------
    // 53th parameter
    // CCA secondary4 energy detection energy threshold [-128,127] dBm
    int8              nSecondary4EdTh;
    //----------------------------------------------------
    // 54th parameter
    // Cn/Pn threshold for cca_mid_detect [0,255] approved value is 150
    uint8             cca_mid_detect_shortGI_threshold;
    //----------------------------------------------------
    // 55th parameter
    // Cn/Pn threshold for cca_mid_detect [0,255] approved value is 180
    uint8             cca_mid_detect_longGI_threshold;
    //----------------------------------------------------
    // 56th parameter
    // remove LOW-SNR pilot threshold [0,31]
    // discard delta_phase result of adjacent pilot if amplitude_normalization_factor < 2^phy_vars.nBadPilotTh
    // bit 0:4
    uint8             nBadPilotTh                          :   5,
    //----------------------------------------------------
    // 57th parameter
    // adjust agc gain at DSTF
    // bit 5
                      m_bAdjGainAtDstf                     :   1,
    //----------------------------------------------------
    // 58th parameter
    // TX DSTF boost enable bit
    // bit 6
                      m_bDSTFboostEn                       :   1,
    // bit 7
                      reserved4                            :   1;
    //----------------------------------------------------
    // 59th parameter
    // rx gain mismatch compensate coefficients
    // unsigned Q1.11 default value is 2048
    uint16            gm_compen_vec[K_RX_GAIN_INDEX_NUM];
    //----------------------------------------------------
    // 60th parameter
    // rx phase mismatch compensate coefficients
    // signed Q0.9 default value is 0
    int16             pm_compen_vec[K_RX_GAIN_INDEX_NUM];
    //----------------------------------------------------
    // 61th parameter
    // the minimum requiared EVM for decoding
    int8              evm_th_vec[4];
    //----------------------------------------------------
    // 62th parameter
    // 1m PPDU angle limiter
    uint8             angle_limiter_1m; // max value is ceil(pi*2^6) = 202, approved value is ceil(pi*2^6*2/26) = 16
    //----------------------------------------------------
    // 63th parameter
    // 2m PPDU angle limiter
    uint8             angle_limiter_2m; // max value is ceil(pi*2^6) = 202, approved value is ceil(pi*2^6*4/26) = 31
    //----------------------------------------------------
    // 64th parameter
    // 4m PPDU angle limiter
    uint8             angle_limiter_4m; // max value is ceil(pi*2^6) = 202, approved value is ceil(pi*2^6*8/26) = 62
    //----------------------------------------------------
    // 65th parameter
    // 8m PPDU angle limiter
    uint8             angle_limiter_8m; // max value is ceil(pi*2^6) = 202, approved value is ceil(pi*2^6*16/26) = 124
    //----------------------------------------------------
    // 66th parameter
    // average times for phase_error estimation in frequency_domain_preprocessor()
    // 0~3
    uint8             phase_error_avg_times                :   2,
                      reserved5                            :   6;
    //----------------------------------------------------
    // 67th parameter
    // the threshold of difference of adjacent 2 symbol's delta_phase
    // approved value is from 36 to 100, which is 4 times greater than the difference of adjacent delta_phase generated by 400ppm timing error
    int16             diff_delta_phase_th;
    //----------------------------------------------------
    // 68th parameter
    // auto reset RX PHY state machine if LTF miss is detected
    // bit 0
    uint16            m_bAutoLtfMissResetEn                :   1,
    //----------------------------------------------------
    // 69th parameter
    // CCA always on
    // bit 1
                      m_bCCAalwaysOn                       :   1,
    //----------------------------------------------------
    // 70th parameter
    // load floating or fix point IQ curve
    // no use
    //----------------------------------------------------
    // 71th parameter
    // bit 2:13
    // IQ saturate detect high threshold, int12
                      iq_sat_high_th                       :  12,
    // bit 14:15
                      reserved6                            :   2;
    //----------------------------------------------------
    // 72th parameter
    // IQ saturate detect low threshold, int12
    // bit 0:11
    uint32            iq_sat_low_th                        :  12,
    //----------------------------------------------------
    // 73th parameter
    // energy protect threshold
    // bit 12:14
                      protect_th                           :   3,
    //----------------------------------------------------
    // 74th parameter
    // digital pre-distortion enable bit
    // bit 15
                      m_bDPDen                             :   1,
    //----------------------------------------------------
    // 75th parameter
    // dynamic dpd enable bit
    // bit 16
                      m_bDynamicDPDen                      :   1,
    //----------------------------------------------------
    // 76th parameter
    // DPD loop back delay search window selection
    // 3'd0: search window is from 0~15
    // 3'd1: search window is from 8~23
    // 3'd2: search window is from 16~31
    // 3'd3: search window is from 24~39
    // 3'd4: search window is from 32~37
    // 3'd5: search window is from 40~55
    // 3'd6: search window is from 48~63
    // 3'd7: search window is from 56~71
    // bit 17:19
                      nLoopbackSearchWin                   :   3,
    //----------------------------------------------------
    // 77th parameter
    // Dynamic DPD stateration threshold of yn [0, 2047]
    // bit 20:30
                      nDPDynSatTH                          :  11,
    // bit 31
                      reserved7                            :   1;
    //----------------------------------------------------
    // 78th parameter
    // Dynamic DPD stateration threshold of Pn [0 : 1 : 63]
    // bit 0:5
    uint32            nDPDPnSatTH                          :   6,
    //----------------------------------------------------
    // 79th parameter
    // Dynamic DPD saturate threshold of kn [0 : 1/8 : 7/8]
    // bit 6:8
                      nDPDknSatTH                          :   3,
    //----------------------------------------------------
    // 80th parameter
    // Dynamic DPD saturate threshold of An [0 : 1 : 31]
    // bit 9:13
                      nDPDAnSatTH                          :   5,
    //----------------------------------------------------
    // 81th parameter
    // additional delay to DPD coefficient calculation [0 : 2]
    // bit 14:15
                      dpd_ext_dly                          :   2,
    //----------------------------------------------------
    // 82th parameter
    // the power threshold of enable DPD, 0~31 dBm
    // bit 16:20
                      dpd_en_pow_th                        :   5,
    //----------------------------------------------------
    // 83th parameter
    // the duration for DPD PA stable
    // 20~63, smaller is better for this field
    // bit 21:26
                      dpd_stable_duration                  :   6,
    //----------------------------------------------------
    // 84th parameter
    // determine whether or not to generate sine waveform and how to generate the waveform
    // 2'b00: do not replace TX waveform
    // 2'b01: replace TX waveform by in phase sine wave and the amplitude equal to half of full range
    // 2'b10: replace TX waveform by orthogonal phase sine wave and the amplitude equal to full range
    // 2'b11: replace TX waveform by orthogonal phase sine wave and the amplitude equal to half of full range
    // bit 27:28
                      TxSineWaveMode                       :   2,
    // bit 29:31
                      reserved8                            :   3;
    //----------------------------------------------------
    // 85th parameter
    // determine the step size to look up sine table
    // bit 0:8
    uint32            nSineStepSize                        :   9,
    //----------------------------------------------------
    // 86th parameter
    // frequency selective fading detect threshold of 2m PPDU
    // bit 9:12
                      FreqFadeTh2M                         :   4,
    //----------------------------------------------------
    // 87th parameter
    // frequency selective fading detect threshold of 4m PPDU
    // bit 13:16
                      FreqFadeTh4M                         :   4,
    //----------------------------------------------------
    // 88th parameter
    // frequency selective fading detect threshold of 8m PPDU
    // bit 17:20
                      FreqFadeTh8M                         :   4,
    //----------------------------------------------------
    // 89th parameter
    // determine whether to generate sine waveform or triangular waveform if TxSineWaveMode == 2'd0
    // bit 21
                      triangular_sine_sel                  :   1,
    //----------------------------------------------------
    // 90th parameter
    // Determine whether the TIA saturation detection is enable and when to disable the circuits
    // bit 22:23
                      TIASatDetSel                         :   2,
    //----------------------------------------------------
    // 91th parameter penghong 190703
    // Whether or not to enable OBSS signal detection
    // bit 24
                      OBSS_SDen                            :   1,
    //----------------------------------------------------
    // bit 25:31
                      reserved9                            :   7;
    //----------------------------------------------------
    // 92th parameter penghong 190703
    // The CCA OBSS signal detect energy threshold of primary2 channel
    // bit 0:7
    uint32            OBSS_SD                              :   8,
    //----------------------------------------------------
    // 93th parameter penghong 190703
    // Partial BSSID is used for dynamic OBSS_SD adjustment
    // bit 8:16
                      PartialBSSID                         :   9,
    //----------------------------------------------------
    // 94th parameter penghong 190703
    // BSS color is used for dynamic OBSS_SD adjustment
    // bit 17:19
                      BssColor                             :   3,
    //----------------------------------------------------
    // 95th parameter penghong 190705
    // Determine whether to multiply the TX waveform by 2
    // bit 20
                      tx_boost_en                          :   1,
    //----------------------------------------------------
    // 96th parameter penghong 190727
    // bit 21
    // Determine whether to generate a false-match signal when receive a frame
    // which uplink indication bit of SIG part is cleared. This is used when the recipient is in AP mode:
    // 0: disable (STA mode or AP+STA mode)
    // 1: enable (AP only mode)
                      dropdownlink                         :   1,
    //----------------------------------------------------
    // 97th parameter penghong 190731
    // bit 22
    // Determine the AGC bandwidth source:
    // 0: adjust gain index according to the in band STS energy selected by PHY_CTL.agc_bw field
    // 1: adjust gain index according to the in band STS energy selected by nTxRxModemBW
    //    if dynamic_rx_bw_en == 1'b0 or RXPWRIDX.Rf_rx_bw if dynamic_rx_bw_en == 1'b1
                      agc_bw_sel                           :   1,
    //----------------------------------------------------
    // 98th parameter penghong 190731
    // bit 23:24
    // Adjust AGC according a prior bandwidth information
    // 2'd0 1M   2'd1 2M   2'd2 4M   2'd3 8M
                      agc_bw                               :   2,
    //----------------------------------------------------
    // 99th parameter penghong 190807
	// Whether to reset PHY automatically when SIG error is detected. 
    // 0: disable
    // If this bit is clear LTF Sync will send to LMAC. A signal called sig_ok_pluse
	// will never send to LMAC. The SIG bit will send to LMAC after LTFSync is set.
    // 1: enable
    // If this bit is set LTF Sync will never send to LMAC. A signal called sig_ok_pluse will 
	// send to LMAC if no error is detected for SIG deparser. The SIG bit will send to LMAC after sig_ok is set.
                      m_bAutoSigErrResetEn                 :   1,
    // bit 25:30
                      reserved10                           :   5,
    //----------------------------------------------------
    // 97th parameter
    // note the parameter m_bLoadCapturedData is in debug.h
    //----------------------------------------------------
    // bit 31
                      m_bAllDataPayload                    :   1; // for TX4001 and TX6001 lmac normal mode only
    //----------------------------------------------------
    struct hgwphy_gain_cfg agc_4_stage_para;
    struct hgwphy_gain_cfg agc_5_stage_para;
};

struct hgwphy_ah_info {
    union { // related register: ERR_CODE
        struct {
            uint32 TX_INSUFFICIENT_BW                          :    1,  // bit 0
                   TX_UNSUPPORTED_MCS                          :    1,  // bit 1
                   TX_UNSUPPORTED_BW                           :    1,  // bit 2
                   Tx_DUP_BW_ERR                               :    1,  // bit 3
                   TX_NSYM_ERR                                 :    1,  // bit 4
                   TX_INVALID_SIG                              :    1,  // bit 5
                   TX_BUF_UNDER_RUN                            :    1,  // bit 6
                   TX_VECTOR2_UNDER_RUN                        :    1,  // bit 7
                   reserved                                    :    8,  // bit 8~15
                   RX_INSUFFICIENT_BW                          :    1,  // bit 16
                   RX_UNSUPPORTED_MCS                          :    1,  // bit 17
                   RX_UNSUPPORTED_BW                           :    1,  // bit 18
                   reserved0                                   :    1,  // bit 19
                   RX_NSYM_ERR                                 :    1,  // bit 20
                   RX_INVALID_SIG                              :    1,  // bit 21
                   K_RX_LTF_MISS_ERR                           :    1,  // bit 22
                   K_RX_LTF_FALSE_2M_PPDU                      :    1,  // bit 23
                   K_RX_1MPPDU_SIG_ROT_ERR                     :    1,  // bit 24
                   K_RX_NON_1MPPDU_SIG_ROT_ERR                 :    1,  // bit 25
                   K_RX_CRC4_ERR                               :    1,  // bit 26
                   K_RX_SIGBW_GT_STSBW_ERR                     :    1,  // bit 27
                   K_RX_DUP_BW_ERR                             :    1,  // bit 28
                   K_RX_CARRIER_LOST                           :    1,  // bit 29
                   K_RX_LTF_MISS_ERR2                          :    1,  // bit 30
                   reserved1                                   :    1;  // bit 31
        };
        uint32 word_buf;
    } nErrCode;
    union { // related register: PHY_INFO_IND
        struct {
            uint32 m_bPrimary1CoarseSync                       :    1,  // bit 0
                   m_bPrimary2CoarseSync                       :    1,  // bit 1
                   m_bSecondary2CoarseSync                     :    1,  // bit 2
                   m_bSecondary4CoarseSync                     :    1,  // bit 3
                   m_bLtf1mPPDU                                :    1,  // bit 4
                   m_bPrimary1LtfSync                          :    1,  // bit 5
                   m_bLtf248mPPDU                              :    1,  // bit 6
                   m_bPrimary2LtfSync                          :    1,  // bit 7
                   m_bRxShortOrLong                            :    1,  // bit 8
                   m_bSig0Rot                                  :    1,  // bit 9
                   m_bSig1Rot                                  :    1,  // bit 10
                   CCAPrimary1                                 :    1,  // bit 11
                   CCAPrimary2                                 :    1,  // bit 12
                   CCASecondary2                               :    1,  // bit 13
                   CCASecondary4                               :    1,  // bit 14
                   m_bCCAPrimary1Start                         :    1,  // bit 15
                   m_bCCAPrimary2Start                         :    1,  // bit 16
                   m_bCCAPrimary1Mid                           :    1,  // bit 17
                   m_bCCAPrimary2Mid                           :    1,  // bit 18
                   m_bCCASecondary2Mid                         :    1,  // bit 19
                   m_bCCASecondary4Mid                         :    1,  // bit 20
                   m_bCCAPrimary1ED                            :    1,  // bit 21
                   m_bCCAPrimary2ED                            :    1,  // bit 22
                   m_bCCASecondary2ED                          :    1,  // bit 23
                   m_bCCASecondary4ED                          :    1,  // bit 24
                   m_bDup4mDet                                 :    1,  // bit 25
                   m_bDup8mDet                                 :    1,  // bit 26
                   reserved                                    :    1;  // bit 27:31
        };
        uint32 word_buf;
    } nPhyInfoInd;
    // dc component, related register: PHY_EST_INIT_DC
    int16   init_dc_estimate_q;
    int16   init_dc_estimate_i;
    // Estimated coarse frequency offset if 1st STS had been detected, related register PHY_CFO0_ESTIMATE
    int32   cfoEstimate;      // bit 0:17
    // Estimated coarse frequency offset at the edge of STF and LTF, relate4d register PHY_CFO1_ESTIMATE
    int32   nAvgCfoEstimate;  // bit 0:17
    // Synchronization sample counter @1st STS had been detected, related register PHY_STS_SYNC_POS
    uint32  sync_pos0;
    union { // related register PHY_RXInfo0
        struct {
            uint32 Reserved0                                   :    1,  // bit 0
                   nRxSTBC                                     :    1,  // bit 1
                   UplinkIndication                            :    1,  // bit 2
                   nRxSigBW                                    :    2,  // bit 3:4
                   nRxNsts                                     :    2,  // bit 5:6
                   nRxID                                       :    9,  // bit 7:15
                   m_bRxShortGI                                :    1,  // bit 16
                   m_bRxCoding                                 :    1,  // bit 17
                   m_bRxLDPC_extra                             :    1,  // bit 18
                   nRxDataFieldMcs                             :    4,  // bit 19:22
                   m_bRxRecommendSmoothing                     :    1,  // bit 23
                   m_bRxAggregation                            :    1,  // bit 24
                   m_bRxNdpIndication                          :    1,  // bit 25
                   nRxResponseIndication                       :    2,  // bit 26:27
                   nRxTravelingPilots                          :    1,  // bit 28
                   Reserved1                                   :    3;  // bit 29:31
        };
        uint32 word_buf;
    } nPhyRxInfo0;
    union { // related register PHY_RXInfo1
        struct {
            uint32  nRxDataSymbolNum                           :   10,  // bit 0:9
                    approved_bw                                :    2,  // bit 10:11
                    nRxCrc4                                    :    4,  // bit 12:15
                    nRxDataByteNum                             :    9,  // bit 16:24
                    nRxScramInitVec                            :    7;  // bit 25:31
        };
        uint32  word_buf;
    } nPhyRxInfo1;
    union { // related register PHY_RXPowerInfo0
        struct {
            int8    nAvgSecondary4Power;
            int8    nAvgSecondary2Power;
            int8    nAvgPrimary2Power;
            int8    nAvgPrimary1Power;
        } nChPower;
        uint32  word_buf;
    } nPhyRxPowerInfo0;
    union { // related register PHY_RXPowerInfo1
        struct {
            int8    nAvgPower;
            uint8   Reserved0;
            uint8   Reserved1;
            uint8   m_bGain0TIAsat                         :    1,  // bit 24
                    m_bGain1TIAsat                         :    1,  // bit 25
                    m_bGain2TIAsat                         :    1,  // bit 26
                    m_bGain3TIAsat                         :    1,  // bit 27
                    m_bGain4TIAsat                         :    1,  // bit 28
                    m_bGain5TIAsat                         :    1,  // bit 29
                    Reserved2                              :    2;  // bit 30:31
        } nAvgPow_Saturate;
        uint32  word_buf;
    } nPhyRxPowerInfo1;
    union { // AGC gain state, related register PHY_RXInfo2
        struct {
            int8    avg_evm;
            int8    worst_evm;
            uint8   GainStateInfo0                         :    3,  // bit16:18
                    Reserved0                              :    1,  // bit19
                    GainStateInfo1                         :    3,  // bit20:22
                    Reserved1                              :    1;  // bit23
            uint8   GainStateInfo2                         :    3,  // bit24:26
                    Reserved2                              :    1,  // bit27
                    GainStateInfo3                         :    3,  // bit28:30
                    Reserved3                              :    1;  // bit31
        } nEvm_GainState;
        uint32  word_buf;
    } nPhyRxInfo2;
    union { // related register RXIQCALIB1
        struct {
            uint32  gm_compen                              :   12,  // bit0:11, unsigned Q1.11
                    Reserved0                              :    4,  // bit12:15
                    pm_compen                              :   10,  // bit16:25, signed Q0.9
                    Reserved1                              :    6;  // bit26:31
        } nRxIqCaliInfo;
        uint32  word_buf;
    } nRxIqCalib1;
    // Synchronization sample counter at the edge of STF and LTF, related register PHY_LTF_SYNC_POS
    uint32  sync_pos1;
    // related register PHY_CFO2_ESTMATE
    int32   nFineFreqOffsetEstimate;  // bit 0:17
    union { // related register PHY_DPD_Info
        struct {
            uint32  inv_dpd_gain_est                       :   11,  // bit0:10, unsigned Q2.9
                    m_bDPD_yn_small                        :    1,  // bit11
                    m_bDPD_yn_large                        :    1,  // bit12
                    m_bDPD_yn_zero                         :    1,  // bit13
                    m_bDPDynSat                            :    1,  // bit14
                    m_bDPDPnSat                            :    1,  // bit15
                    m_bDPDknSat                            :    1,  // bit16
                    m_bDPDAnSat                            :    1,  // bit17
                    dpd_loop_dly_est                       :    4,  // bit18:21
                    reserved                               :   10;  // bit22:31
        } nDpdInfo0;
        uint32  word_buf;
    } nPhyDpdInfo;
    union { // related register PHY_DPD_Info2
        struct {
            int16   DpdInitPhase                                 ;  // bit0:15
            uint16  m_bynSat                               :    1,
                    m_bynSat2                              :    1,
                    reserved                               :   14;
        } nDpdInfo1;
        uint32  word_buf;
    } nPhyDpdInfo2;
    uint32 rx_psdu_len;
    uint32 tx_psdu_len;
    uint16 n_crc_rx_payload_dly_tap;
};

struct hgwphy_ah_reg {
    __IO uint32 PHY_CTL;
    __IO uint32 PHY_TXCTL;
    __I  uint32 PHY_TXCRC;
    __IO uint32 PHY_RXCTL0;
    __I  uint32 ERR_CODE;
    __I  uint32 PHY_INFO_IND;
    __I  uint32 PHY_EST_INIT_DC;
    __I  uint32 PHY_CFO0_ESTIMATE;
    __I  uint32 PHY_STS_SYNC_POS;
    __I  uint32 PHY_CFO1_ESTIMATE;
    __IO uint32 PHY_SYNC_TIME_TH;
    __IO uint32 PHY_RXCTL1;
    __IO uint32 PHY_RXCTL2;
    __IO uint32 DC_I[8];
    __IO uint32 DC_Q[8];
    __IO uint32 INCREASEGAINTH_3_0;
    __IO uint32 INCREASEGAINTH_4;
    struct REG48BIT MCSGAINTH[8];
    struct REG48BIT MCSRXGAIN[8];
    struct REG48BIT MCSRXGAININDEX[8];
    __I  uint32 PHY_RXINFO0;
    __I  uint32 PHY_RXINFO1;
    __IO uint32 PHY_RXCTL3;
    __IO uint32 CCA_START_DET_TH;
    __IO uint32 CCA_MID_DET_TH;
    __IO uint32 CCA_ED_TH;
    __I  uint32 PHY_RXPOWERINFO0;
    __I  uint32 PHY_RXPOWERINFO1;
    __IO uint32 PHY_RXIQCOMP[32];
    __IO uint32 RXIQCALIB0;
    __IO uint32 RXIQCALIB1;
    __IO uint32 RXIQCALIB2;
    __I  uint32 PHY_RXINFO2;
    __IO uint32 PHY_RXCTL4;
    __IO uint32 PHY_RXCTL5;
    __IO uint32 PHY_RXCTL6;
    __I  uint32 PHY_LTF_SYNC_POS;
    __IO uint32 RETREG;
    __I  uint32 PHY_CFO2_ESTIMATE;
    __IO uint32 PHY_UNUSED;
    __IO uint32 PHY_RXCTL7;
    __I  uint32 PHY_DPD_INFO;
    __IO uint32 PHY_DPD_CTL;
    __IO uint32 DPD_RAM_WR_CTL;
    __IO uint32 DPD_RAM_RD_CTL;
    __IO uint32 PHY_DMA_ABORT_CFG;
    __I  uint32 PHY_DPD_INFO2;
    __IO uint32 PHY_RXCTL8;
    __IO uint32 PHY_STATE_INFO0;
    __IO uint32 PHY_STATE_INFO1;
    __IO uint32 PHYPSDUCRC;
    __IO uint32 PHY_RXInfo3;
    __IO uint32 PHY_TXInfo0;
};

union _BITGRP16
{
    struct _BIT16 {
        uint16 b0  :   1,
               b1  :   1,
               b2  :   1,
               b3  :   1,
               b4  :   1,
               b5  :   1,
               b6  :   1,
               b7  :   1,
               b8  :   1,
               b9  :   1,
               b10 :   1,
               b11 :   1,
               b12 :   1,
               b13 :   1,
               b14 :   1,
               b15 :   1;
    } bit;
    uint16   halfword_var;
};

union _BITGRP8
{
    struct _BIT8 {
        uint8 b0  :   1,
              b1  :   1,
              b2  :   1,
              b3  :   1,
              b4  :   1,
              b5  :   1,
              b6  :   1,
              b7  :   1;
    } bit;
    uint8   byte_var;
};

struct hgwphy_ah {
    struct wphy_device           dev;
    struct hgwphy_ah_info        nwphyahinfo;
    struct hgwphy_ah_cfg         nwphyahcfg;
    union  _dpd_ram              *p_dpd_ram;
    struct hgwphy_ah_reg         *pwphyreg;
    uint32                       *prximbtab;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
// Register Address: 'h0000
#define PHY_CTL_SOFT_RESET_N_MSK                    0x80000000
#define PHY_CTL_SOFT_RESET_N_SHIFT                  31
#define PHY_CTL_M_BIQREV_DAC_MSK                    0x40000000
#define PHY_CTL_M_BIQREV_DAC_SHIFT                  30
#define PHY_CTL_M_BIQREV_ADC_MSK                    0x20000000
#define PHY_CTL_M_BIQREV_ADC_SHIFT                  29
#define PHY_CTL_M_BTXQINV_MSK                       0x10000000
#define PHY_CTL_M_BTXQINV_SHIFT                     28
#define PHY_CTL_M_BRXQINV_MSK                       0x08000000
#define PHY_CTL_M_BRXQINV_SHIFT                     27
#define PHY_CTL_RX_HARD_RESET_N_MSK                 0x04000000
#define PHY_CTL_RX_HARD_RESET_N_SHIFT               26
#define PHY_CTL_TX_HARD_RESET_N_MSK                 0x02000000
#define PHY_CTL_TX_HARD_RESET_N_SHIFT               25
#define PHY_CTL_FFT_HARD_RESET_N_MSK                0x01000000
#define PHY_CTL_FFT_HARD_RESET_N_SHIFT              24
#define PHY_CTL_LTF_TIMEOUT_ENA_MSK                 0x00800000
#define PHY_CTL_LTF_TIMEOUT_ENA_SHIFT               23
#define PHY_CTL_AGC_BW_MSK                          0x00300000
#define PHY_CTL_AGC_BW_SHIFT                        20
#define PHY_CTL_TIASATDETSEL_MSK                    0x000C0000
#define PHY_CTL_TIASATDETSEL_SHIFT                  18
#define PHY_CTL_NTXRXMODEMBW_MSK                    0x00030000
#define PHY_CTL_NTXRXMODEMBW_SHIFT                  16
#define PHY_CTL_AGC_BW_SEL_MSK                      0x00008000
#define PHY_CTL_AGC_BW_SEL_SHIFT                    15
#define PHY_CTL_REFRESH_CCA_TH_EN_MSK               0x00004000
#define PHY_CTL_REFRESH_CCA_TH_EN_SHIFT             14
#define PHY_CTL_DYNAMIC_RX_BW_EN_MSK                0x00002000
#define PHY_CTL_DYNAMIC_RX_BW_EN_SHIFT              13
#define PHY_CTL_TX_CLK_AUTO_TURN_OFF_MSK            0x00001000
#define PHY_CTL_TX_CLK_AUTO_TURN_OFF_SHIFT          12
#define PHY_CTL_RX_48M_AUTO_TURN_OFF_MSK            0x00000800
#define PHY_CTL_RX_48M_AUTO_TURN_OFF_SHIFT          11
#define PHY_CTL_RX_32M_AUTO_TURN_OFF_MSK            0x00000400
#define PHY_CTL_RX_32M_AUTO_TURN_OFF_SHIFT          10
#define PHY_CTL_FFT_CLK_AUTO_TURN_OFF_MSK           0x00000200
#define PHY_CTL_FFT_CLK_AUTO_TURN_OFF_SHIFT         9
#define PHY_CTL_CCA_CLK_AUTO_TURN_OFF_MSK           0x00000100
#define PHY_CTL_CCA_CLK_AUTO_TURN_OFF_SHIFT         8
#define PHY_CTL_LTF_CLK_AUTO_TURN_OFF_MSK           0x00000080
#define PHY_CTL_LTF_CLK_AUTO_TURN_OFF_SHIFT         7
#define PHY_CTL_STF_CLK_AUTO_TURN_OFF_MSK           0x00000040
#define PHY_CTL_STF_CLK_AUTO_TURN_OFF_SHIFT         6
#define PHY_CTL_CLK_PRIM2_AUTO_TURN_OFF_MSK         0x00000020
#define PHY_CTL_CLK_PRIM2_AUTO_TURN_OFF_SHIFT       5
#define PHY_CTL_CLK_PRIM4_AUTO_TURN_OFF_MSK         0x00000010
#define PHY_CTL_CLK_PRIM4_AUTO_TURN_OFF_SHIFT       4
#define PHY_CTL_CLK_PRIM8_AUTO_TURN_OFF_MSK         0x00000008
#define PHY_CTL_CLK_PRIM8_AUTO_TURN_OFF_SHIFT       3
#define PHY_CTL_FINE_EST_CLK_AUTO_TURN_OFF_MSK      0x00000004
#define PHY_CTL_FINE_EST_CLK_AUTO_TURN_OFF_SHIFT    2
#define PHY_CTL_PREPROC_CLK_AUTO_TURN_OFF_MSK       0x00000002
#define PHY_CTL_PREPROC_CLK_AUTO_TURN_OFF_SHIFT     1
#define PHY_CTL_M_BPHYEN_MSK                        0x00000001
#define PHY_CTL_M_BPHYEN_SHIFT                      0

// Register Address: 'h0004
#define PHY_TXCTL_TRIANGULAR_SINE_SEL_MSK      0x80000000
#define PHY_TXCTL_TRIANGULAR_SINE_SEL_SHIFT    31
#define PHY_TXCTL_TX_BOOST_EN_MSK              0x40000000
#define PHY_TXCTL_TX_BOOST_EN_SHIFT            30
#define PHY_TXCTL_NLOOPBACKSEARCHWIN_MSK       0x3C000000
#define PHY_TXCTL_NLOOPBACKSEARCHWIN_SHIFT     26
#define PHY_TXCTL_NSINESTEPSIZE_MSK            0x03FE0000
#define PHY_TXCTL_NSINESTEPSIZE_SHIFT          17
#define PHY_TXCTL_DPD_STABLE_DURATION_MSK      0x0001F800
#define PHY_TXCTL_DPD_STABLE_DURATION_SHIFT    11
#define PHY_TXCTL_M_BDYNAMICDPDEN_MSK          0x00000400
#define PHY_TXCTL_M_BDYNAMICDPDEN_SHIFT        10
#define PHY_TXCTL_M_BDPD_COMP_EN_MSK           0x00000200
#define PHY_TXCTL_M_BDPD_COMP_EN_SHIFT         9
#define PHY_TXCTL_M_BDSTFBOOSTEN_MSK           0x00000100
#define PHY_TXCTL_M_BDSTFBOOSTEN_SHIFT         8
#define PHY_TXCTL_CONTINUOUSTX_MSK             0x00000080
#define PHY_TXCTL_CONTINUOUSTX_SHIFT           7
#define PHY_TXCTL_ZERO_IF_MSK                  0x00000040
#define PHY_TXCTL_ZERO_IF_SHIFT                6
#define PHY_TXCTL_NDP1M_BOOST_EN_MSK           0x00000020
#define PHY_TXCTL_NDP1M_BOOST_EN_SHIFT         5
#define PHY_TXCTL_PRIME_CH_MSK                 0x0000001C
#define PHY_TXCTL_PRIME_CH_SHIFT               2
#define PHY_TXCTL_TXSINEWAVEMODE_MSK           0x00000003
#define PHY_TXCTL_TXSINEWAVEMODE_SHIFT         0

// Register Address: 'h0008
#define PHY_TXCRC_QCH_CRC_MSK      0xFFFF0000
#define PHY_TXCRC_QCH_CRC_SHIFT    16
#define PHY_TXCRC_ICH_CRC_MSK      0x0000FFFF
#define PHY_TXCRC_ICH_CRC_SHIFT    0

// Register Address: 'h000c
#define PHY_RXCTL0_NAGCSTARTSAMPLE_MSK                           0xFFF00000
#define PHY_RXCTL0_NAGCSTARTSAMPLE_SHIFT                         20
#define PHY_RXCTL0_NPRIMARY2LTFDETECTORCORRSTARTCOUNTER_MSK      0x000C0000
#define PHY_RXCTL0_NPRIMARY2LTFDETECTORCORRSTARTCOUNTER_SHIFT    18
#define PHY_RXCTL0_NPRIMARY1LTFDETECTORCORRSTARTCOUNTER_MSK      0x00030000
#define PHY_RXCTL0_NPRIMARY1LTFDETECTORCORRSTARTCOUNTER_SHIFT    16
#define PHY_RXCTL0_M_BMODIFYFREQOFFSETATLTFEND_MSK               0x00008000
#define PHY_RXCTL0_M_BMODIFYFREQOFFSETATLTFEND_SHIFT             15
#define PHY_RXCTL0_M_BMODIFYFREQOFFSETATLTFSYNC_MSK              0x00004000
#define PHY_RXCTL0_M_BMODIFYFREQOFFSETATLTFSYNC_SHIFT            14
#define PHY_RXCTL0_M_BMODIFYFREQOFFSETATSTFSYNC_MSK              0x00002000
#define PHY_RXCTL0_M_BMODIFYFREQOFFSETATSTFSYNC_SHIFT            13
#define PHY_RXCTL0_NLTFDETECTOR1M2MTH_MSK                        0x00001F00
#define PHY_RXCTL0_NLTFDETECTOR1M2MTH_SHIFT                      8
#define PHY_RXCTL0_NLOWPOWER4MDIV1MTH_MSK                        0x000000C0
#define PHY_RXCTL0_NLOWPOWER4MDIV1MTH_SHIFT                      6
#define PHY_RXCTL0_NLOWPOWER2MDIV1MTH_MSK                        0x00000030
#define PHY_RXCTL0_NLOWPOWER2MDIV1MTH_SHIFT                      4
#define PHY_RXCTL0_NLOWPOWERTH_MSK                               0x0000000F
#define PHY_RXCTL0_NLOWPOWERTH_SHIFT                             0

// Register Address: 'h0010
#define ERR_CODE_K_RX_OBSS_MSK                        0x80000000
#define ERR_CODE_K_RX_OBSS_SHIFT                      31
#define ERR_CODE_K_RX_LTF_MISS_ERR2_MSK               0x40000000
#define ERR_CODE_K_RX_LTF_MISS_ERR2_SHIFT             30
#define ERR_CODE_K_RX_CARRIER_LOST_MSK                0x20000000
#define ERR_CODE_K_RX_CARRIER_LOST_SHIFT              29
#define ERR_CODE_K_RX_DUP_BW_ERR_MSK                  0x10000000
#define ERR_CODE_K_RX_DUP_BW_ERR_SHIFT                28
#define ERR_CODE_K_RX_SIGBW_GT_STSBW_ERR_MSK          0x08000000
#define ERR_CODE_K_RX_SIGBW_GT_STSBW_ERR_SHIFT        27
#define ERR_CODE_K_RX_CRC4_ERR_MSK                    0x04000000
#define ERR_CODE_K_RX_CRC4_ERR_SHIFT                  26
#define ERR_CODE_K_RX_NON_1MPPDU_SIG_ROT_ERR_MSK      0x02000000
#define ERR_CODE_K_RX_NON_1MPPDU_SIG_ROT_ERR_SHIFT    25
#define ERR_CODE_K_RX_1MPPDU_SIG_ROT_ERR_MSK          0x01000000
#define ERR_CODE_K_RX_1MPPDU_SIG_ROT_ERR_SHIFT        24
#define ERR_CODE_K_RX_LTF_FALSE_2M_PPDU_MSK           0x00800000
#define ERR_CODE_K_RX_LTF_FALSE_2M_PPDU_SHIFT         23
#define ERR_CODE_K_RX_LTF_MISS_ERR_MSK                0x00400000
#define ERR_CODE_K_RX_LTF_MISS_ERR_SHIFT              22
#define ERR_CODE_RX_INVALID_SIG_MSK                   0x00200000
#define ERR_CODE_RX_INVALID_SIG_SHIFT                 21
#define ERR_CODE_RX_NSYM_ERR_MSK                      0x00100000
#define ERR_CODE_RX_NSYM_ERR_SHIFT                    20
#define ERR_CODE_RX_SIG_TO_ERR_MSK                    0x00080000
#define ERR_CODE_RX_SIG_TO_ERR_SHIFT                  19
#define ERR_CODE_RX_UNSUPPORTED_BW_MSK                0x00040000
#define ERR_CODE_RX_UNSUPPORTED_BW_SHIFT              18
#define ERR_CODE_RX_UNSUPPORTED_MCS_MSK               0x00020000
#define ERR_CODE_RX_UNSUPPORTED_MCS_SHIFT             17
#define ERR_CODE_RX_INSUFFICIENT_BW_MSK               0x00010000
#define ERR_CODE_RX_INSUFFICIENT_BW_SHIFT             16
#define ERR_CODE_TX_VECTOR2_UNDER_RUN_MSK             0x00000080
#define ERR_CODE_TX_VECTOR2_UNDER_RUN_SHIFT           7
#define ERR_CODE_TX_BUF_UNDER_RUN_MSK                 0x00000040
#define ERR_CODE_TX_BUF_UNDER_RUN_SHIFT               6
#define ERR_CODE_TX_INVALID_SIG_MSK                   0x00000020
#define ERR_CODE_TX_INVALID_SIG_SHIFT                 5
#define ERR_CODE_TX_NSYM_ERR_MSK                      0x00000010
#define ERR_CODE_TX_NSYM_ERR_SHIFT                    4
#define ERR_CODE_TX_DUP_BW_ERR_MSK                    0x00000008
#define ERR_CODE_TX_DUP_BW_ERR_SHIFT                  3
#define ERR_CODE_TX_UNSUPPORTED_BW_MSK                0x00000004
#define ERR_CODE_TX_UNSUPPORTED_BW_SHIFT              2
#define ERR_CODE_TX_UNSUPPORTED_MCS_MSK               0x00000002
#define ERR_CODE_TX_UNSUPPORTED_MCS_SHIFT             1
#define ERR_CODE_TX_INSUFFICIENT_BW_MSK               0x00000001
#define ERR_CODE_TX_INSUFFICIENT_BW_SHIFT             0

// Register Address: 'h0014
#define PHY_INFO_IND_TXCRC4_MSK                       0xF0000000
#define PHY_INFO_IND_TXCRC4_SHIFT                     28
#define PHY_INFO_IND_M_BDUP8MDET_MSK                  0x04000000
#define PHY_INFO_IND_M_BDUP8MDET_SHIFT                26
#define PHY_INFO_IND_M_BDUP4MDET_MSK                  0x02000000
#define PHY_INFO_IND_M_BDUP4MDET_SHIFT                25
#define PHY_INFO_IND_M_BCCASECONDARY4ED_MSK           0x01000000
#define PHY_INFO_IND_M_BCCASECONDARY4ED_SHIFT         24
#define PHY_INFO_IND_M_BCCASECONDARY2ED_MSK           0x00800000
#define PHY_INFO_IND_M_BCCASECONDARY2ED_SHIFT         23
#define PHY_INFO_IND_M_BCCAPRIMARY2ED_MSK             0x00400000
#define PHY_INFO_IND_M_BCCAPRIMARY2ED_SHIFT           22
#define PHY_INFO_IND_M_BCCAPRIMARY1ED_MSK             0x00200000
#define PHY_INFO_IND_M_BCCAPRIMARY1ED_SHIFT           21
#define PHY_INFO_IND_M_BCCASECONDARY4MID_MSK          0x00100000
#define PHY_INFO_IND_M_BCCASECONDARY4MID_SHIFT        20
#define PHY_INFO_IND_M_BCCASECONDARY2MID_MSK          0x00080000
#define PHY_INFO_IND_M_BCCASECONDARY2MID_SHIFT        19
#define PHY_INFO_IND_M_BCCAPRIMARY2MID_MSK            0x00040000
#define PHY_INFO_IND_M_BCCAPRIMARY2MID_SHIFT          18
#define PHY_INFO_IND_M_BCCAPRIMARY1MID_MSK            0x00020000
#define PHY_INFO_IND_M_BCCAPRIMARY1MID_SHIFT          17
#define PHY_INFO_IND_M_BCCAPRIMARY2START_MSK          0x00010000
#define PHY_INFO_IND_M_BCCAPRIMARY2START_SHIFT        16
#define PHY_INFO_IND_M_BCCAPRIMARY1START_MSK          0x00008000
#define PHY_INFO_IND_M_BCCAPRIMARY1START_SHIFT        15
#define PHY_INFO_IND_CCASECONDARY4_MSK                0x00004000
#define PHY_INFO_IND_CCASECONDARY4_SHIFT              14
#define PHY_INFO_IND_CCASECONDARY2_MSK                0x00002000
#define PHY_INFO_IND_CCASECONDARY2_SHIFT              13
#define PHY_INFO_IND_CCAPRIMARY2_MSK                  0x00001000
#define PHY_INFO_IND_CCAPRIMARY2_SHIFT                12
#define PHY_INFO_IND_CCAPRIMARY1_MSK                  0x00000800
#define PHY_INFO_IND_CCAPRIMARY1_SHIFT                11
#define PHY_INFO_IND_M_BSIG1ROT_MSK                   0x00000400
#define PHY_INFO_IND_M_BSIG1ROT_SHIFT                 10
#define PHY_INFO_IND_M_BSIG0ROT_MSK                   0x00000200
#define PHY_INFO_IND_M_BSIG0ROT_SHIFT                 9
#define PHY_INFO_IND_M_BRXSHORTORLONG_MSK             0x00000100
#define PHY_INFO_IND_M_BRXSHORTORLONG_SHIFT           8
#define PHY_INFO_IND_M_BPRIMARY2LTFSYNC_MSK           0x00000080
#define PHY_INFO_IND_M_BPRIMARY2LTFSYNC_SHIFT         7
#define PHY_INFO_IND_M_BLTF248MPPDU_MSK               0x00000040
#define PHY_INFO_IND_M_BLTF248MPPDU_SHIFT             6
#define PHY_INFO_IND_M_BPRIMARY1LTFSYNC_MSK           0x00000020
#define PHY_INFO_IND_M_BPRIMARY1LTFSYNC_SHIFT         5
#define PHY_INFO_IND_M_BLTF1MPPDU_MSK                 0x00000010
#define PHY_INFO_IND_M_BLTF1MPPDU_SHIFT               4
#define PHY_INFO_IND_M_BSECONDARY4COARSESYNC_MSK      0x00000008
#define PHY_INFO_IND_M_BSECONDARY4COARSESYNC_SHIFT    3
#define PHY_INFO_IND_M_BSECONDARY2COARSESYNC_MSK      0x00000004
#define PHY_INFO_IND_M_BSECONDARY2COARSESYNC_SHIFT    2
#define PHY_INFO_IND_M_BPRIMARY2COARSESYNC_MSK        0x00000002
#define PHY_INFO_IND_M_BPRIMARY2COARSESYNC_SHIFT      1
#define PHY_INFO_IND_M_BPRIMARY1COARSESYNC_MSK        0x00000001
#define PHY_INFO_IND_M_BPRIMARY1COARSESYNC_SHIFT      0

// Register Address: 'h0018
#define PHY_EST_INIT_DC_INIT_DC_ESTIMATE_Q_MSK      0xFFFF0000
#define PHY_EST_INIT_DC_INIT_DC_ESTIMATE_Q_SHIFT    16
#define PHY_EST_INIT_DC_INIT_DC_ESTIMATE_I_MSK      0x0000FFFF
#define PHY_EST_INIT_DC_INIT_DC_ESTIMATE_I_SHIFT    0

// Register Address: 'h001c
#define PHY_CFO0_ESTIMATE_CFO_EST0_MSK      0x0003FFFF
#define PHY_CFO0_ESTIMATE_CFO_EST0_SHIFT    0

// Register Address: 'h0020
#define PHY_STS_SYNC_POS_SYNC_POS0_MSK      0xFFFFFFFF
#define PHY_STS_SYNC_POS_SYNC_POS0_SHIFT    0

// Register Address: 'h0024
#define PHY_CFO1_ESTIMATE_CFO_EST1_MSK      0x0003FFFF
#define PHY_CFO1_ESTIMATE_CFO_EST1_SHIFT    0

// Register Address: 'h0028
#define PHY_SYNC_TIME_TH_NSECONDARY4SYNCCONFIRMTIMETH_MSK      0xFF000000
#define PHY_SYNC_TIME_TH_NSECONDARY4SYNCCONFIRMTIMETH_SHIFT    24
#define PHY_SYNC_TIME_TH_NSECONDARY2SYNCCONFIRMTIMETH_MSK      0x00FF0000
#define PHY_SYNC_TIME_TH_NSECONDARY2SYNCCONFIRMTIMETH_SHIFT    16
#define PHY_SYNC_TIME_TH_NPRIMARY2SYNCCONFIRMTIMETH_MSK        0x0000FF00
#define PHY_SYNC_TIME_TH_NPRIMARY2SYNCCONFIRMTIMETH_SHIFT      8
#define PHY_SYNC_TIME_TH_NPRIMARY1SYNCCONFIRMTIMETH_MSK        0x000000FF
#define PHY_SYNC_TIME_TH_NPRIMARY1SYNCCONFIRMTIMETH_SHIFT      0

// Register Address: 'h002c
#define PHY_RXCTL1_COARSE_TIMING_TH_MSK             0x7F000000
#define PHY_RXCTL1_COARSE_TIMING_TH_SHIFT           24
#define PHY_RXCTL1_PACKET_DETECT_THRESHOLD_MSK      0x00FF0000
#define PHY_RXCTL1_PACKET_DETECT_THRESHOLD_SHIFT    16
#define PHY_RXCTL1_POWERCORRWAITDURATION_MSK        0x0000FF00
#define PHY_RXCTL1_POWERCORRWAITDURATION_SHIFT      8
#define PHY_RXCTL1_DCESTIMATEWAITDURATION_MSK       0x000000FF
#define PHY_RXCTL1_DCESTIMATEWAITDURATION_SHIFT     0

// Register Address: 'h0030
#define PHY_RXCTL2_CONVERSION_GAIN_DB_MSK             0xFF000000
#define PHY_RXCTL2_CONVERSION_GAIN_DB_SHIFT           24
#define PHY_RXCTL2_NAGCSTABLEDURATION_MSK             0x00FF0000
#define PHY_RXCTL2_NAGCSTABLEDURATION_SHIFT           16
#define PHY_RXCTL2_GAININDEXLATCH_MSK                 0x00008000
#define PHY_RXCTL2_GAININDEXLATCH_SHIFT               15
#define PHY_RXCTL2_M_BCHANNELSMOOTHING_MSK            0x00004000
#define PHY_RXCTL2_M_BCHANNELSMOOTHING_SHIFT          14
#define PHY_RXCTL2_NDCREMOVALTYPE_MSK                 0x00003000
#define PHY_RXCTL2_NDCREMOVALTYPE_SHIFT               12
#define PHY_RXCTL2_NSYMBOLTIMINGAVERAGETIMES_MSK      0x00000F00
#define PHY_RXCTL2_NSYMBOLTIMINGAVERAGETIMES_SHIFT    8
#define PHY_RXCTL2_M_BADDNOISEBEFORESTSSYNC_MSK       0x00000080
#define PHY_RXCTL2_M_BADDNOISEBEFORESTSSYNC_SHIFT     7
#define PHY_RXCTL2_M_BAGCFREEZEEN_MSK                 0x00000040
#define PHY_RXCTL2_M_BAGCFREEZEEN_SHIFT               6
#define PHY_RXCTL2_M_BAUTOSIGERRRESETEN_MSK           0x00000020
#define PHY_RXCTL2_M_BAUTOSIGERRRESETEN_SHIFT         5
#define PHY_RXCTL2_M_BALLDATAPAYLOAD_MSK              0x00000010
#define PHY_RXCTL2_M_BALLDATAPAYLOAD_SHIFT            4
#define PHY_RXCTL2_M_BESTIMATESIGBCHANNEL_MSK         0x00000008
#define PHY_RXCTL2_M_BESTIMATESIGBCHANNEL_SHIFT       3
#define PHY_RXCTL2_M_BESTIMATEDLTFCHANNEL_MSK         0x00000004
#define PHY_RXCTL2_M_BESTIMATEDLTFCHANNEL_SHIFT       2
#define PHY_RXCTL2_YB_SCALER_MSK                      0x00000003
#define PHY_RXCTL2_YB_SCALER_SHIFT                    0

// Register Address: 'h0034
#define DC_I_3_0_DC_I_3_MSK      0xFF000000
#define DC_I_3_0_DC_I_3_SHIFT    24
#define DC_I_3_0_DC_I_2_MSK      0x00FF0000
#define DC_I_3_0_DC_I_2_SHIFT    16
#define DC_I_3_0_DC_I_1_MSK      0x0000FF00
#define DC_I_3_0_DC_I_1_SHIFT    8
#define DC_I_3_0_DC_I_0_MSK      0x000000FF
#define DC_I_3_0_DC_I_0_SHIFT    0

// Register Address: 'h0038
#define DC_I_5_4_DC_I_5_MSK      0x0000FF00
#define DC_I_5_4_DC_I_5_SHIFT    8
#define DC_I_5_4_DC_I_4_MSK      0x000000FF
#define DC_I_5_4_DC_I_4_SHIFT    0

// Register Address: 'h0054
#define DC_Q_3_0_DC_Q_3_MSK      0xFF000000
#define DC_Q_3_0_DC_Q_3_SHIFT    24
#define DC_Q_3_0_DC_Q_2_MSK      0x00FF0000
#define DC_Q_3_0_DC_Q_2_SHIFT    16
#define DC_Q_3_0_DC_Q_1_MSK      0x0000FF00
#define DC_Q_3_0_DC_Q_1_SHIFT    8
#define DC_Q_3_0_DC_Q_0_MSK      0x000000FF
#define DC_Q_3_0_DC_Q_0_SHIFT    0

// Register Address: 'h0058
#define DC_Q_5_4_DC_Q_5_MSK      0x0000FF00
#define DC_Q_5_4_DC_Q_5_SHIFT    8
#define DC_Q_5_4_DC_Q_4_MSK      0x000000FF
#define DC_Q_5_4_DC_Q_4_SHIFT    0

// Register Address: 'h0074
#define INCREASEGAINTH_3_0_INCREASEGAINTH3_MSK      0xFF000000
#define INCREASEGAINTH_3_0_INCREASEGAINTH3_SHIFT    24
#define INCREASEGAINTH_3_0_INCREASEGAINTH2_MSK      0x00FF0000
#define INCREASEGAINTH_3_0_INCREASEGAINTH2_SHIFT    16
#define INCREASEGAINTH_3_0_INCREASEGAINTH1_MSK      0x0000FF00
#define INCREASEGAINTH_3_0_INCREASEGAINTH1_SHIFT    8
#define INCREASEGAINTH_3_0_INCREASEGAINTH0_MSK      0x000000FF
#define INCREASEGAINTH_3_0_INCREASEGAINTH0_SHIFT    0

// Register Address: 'h0078
#define INCREASEGAINTH_4_INCREASEGAINTH4_MSK      0x000000FF
#define INCREASEGAINTH_4_INCREASEGAINTH4_SHIFT    0

// Register Address: 'h007c
#define REDUCEGAINTH_3_0_REDUCEGAINTH3_MSK      0xFF000000
#define REDUCEGAINTH_3_0_REDUCEGAINTH3_SHIFT    24
#define REDUCEGAINTH_3_0_REDUCEGAINTH2_MSK      0x00FF0000
#define REDUCEGAINTH_3_0_REDUCEGAINTH2_SHIFT    16
#define REDUCEGAINTH_3_0_REDUCEGAINTH1_MSK      0x0000FF00
#define REDUCEGAINTH_3_0_REDUCEGAINTH1_SHIFT    8
#define REDUCEGAINTH_3_0_REDUCEGAINTH0_MSK      0x000000FF
#define REDUCEGAINTH_3_0_REDUCEGAINTH0_SHIFT    0

// Register Address: 'h0080
#define REDUCEGAINTH_4_REDUCEGAINTH4_MSK      0x000000FF
#define REDUCEGAINTH_4_REDUCEGAINTH4_SHIFT    0

// Register Address: 'h0084
#define MCS1GAINTH_3_0_MCS1GAINTH3_MSK      0xFF000000
#define MCS1GAINTH_3_0_MCS1GAINTH3_SHIFT    24
#define MCS1GAINTH_3_0_MCS1GAINTH2_MSK      0x00FF0000
#define MCS1GAINTH_3_0_MCS1GAINTH2_SHIFT    16
#define MCS1GAINTH_3_0_MCS1GAINTH1_MSK      0x0000FF00
#define MCS1GAINTH_3_0_MCS1GAINTH1_SHIFT    8
#define MCS1GAINTH_3_0_MCS1GAINTH0_MSK      0x000000FF
#define MCS1GAINTH_3_0_MCS1GAINTH0_SHIFT    0

// Register Address: 'h0088
#define MCS1GAINTH_4_MCS1GAINTH4_MSK      0x000000FF
#define MCS1GAINTH_4_MCS1GAINTH4_SHIFT    0

// Register Address: 'h008c
#define MCS2GAINTH_3_0_MCS2GAINTH3_MSK      0xFF000000
#define MCS2GAINTH_3_0_MCS2GAINTH3_SHIFT    24
#define MCS2GAINTH_3_0_MCS2GAINTH2_MSK      0x00FF0000
#define MCS2GAINTH_3_0_MCS2GAINTH2_SHIFT    16
#define MCS2GAINTH_3_0_MCS2GAINTH1_MSK      0x0000FF00
#define MCS2GAINTH_3_0_MCS2GAINTH1_SHIFT    8
#define MCS2GAINTH_3_0_MCS2GAINTH0_MSK      0x000000FF
#define MCS2GAINTH_3_0_MCS2GAINTH0_SHIFT    0

// Register Address: 'h0090
#define MCS2GAINTH_4_MCS2GAINTH4_MSK      0x000000FF
#define MCS2GAINTH_4_MCS2GAINTH4_SHIFT    0

// Register Address: 'h0094
#define MCS3GAINTH_3_0_MCS3GAINTH3_MSK      0xFF000000
#define MCS3GAINTH_3_0_MCS3GAINTH3_SHIFT    24
#define MCS3GAINTH_3_0_MCS3GAINTH2_MSK      0x00FF0000
#define MCS3GAINTH_3_0_MCS3GAINTH2_SHIFT    16
#define MCS3GAINTH_3_0_MCS3GAINTH1_MSK      0x0000FF00
#define MCS3GAINTH_3_0_MCS3GAINTH1_SHIFT    8
#define MCS3GAINTH_3_0_MCS3GAINTH0_MSK      0x000000FF
#define MCS3GAINTH_3_0_MCS3GAINTH0_SHIFT    0

// Register Address: 'h0098
#define MCS3GAINTH_4_MCS3GAINTH4_MSK      0x000000FF
#define MCS3GAINTH_4_MCS3GAINTH4_SHIFT    0

// Register Address: 'h009c
#define MCS4GAINTH_3_0_MCS4GAINTH3_MSK      0xFF000000
#define MCS4GAINTH_3_0_MCS4GAINTH3_SHIFT    24
#define MCS4GAINTH_3_0_MCS4GAINTH2_MSK      0x00FF0000
#define MCS4GAINTH_3_0_MCS4GAINTH2_SHIFT    16
#define MCS4GAINTH_3_0_MCS4GAINTH1_MSK      0x0000FF00
#define MCS4GAINTH_3_0_MCS4GAINTH1_SHIFT    8
#define MCS4GAINTH_3_0_MCS4GAINTH0_MSK      0x000000FF
#define MCS4GAINTH_3_0_MCS4GAINTH0_SHIFT    0

// Register Address: 'h0a0
#define MCS4GAINTH_4_MCS4GAINTH4_MSK      0x000000FF
#define MCS4GAINTH_4_MCS4GAINTH4_SHIFT    0

// Register Address: 'h00a4
#define MCS5GAINTH_3_0_MCS5GAINTH3_MSK      0xFF000000
#define MCS5GAINTH_3_0_MCS5GAINTH3_SHIFT    24
#define MCS5GAINTH_3_0_MCS5GAINTH2_MSK      0x00FF0000
#define MCS5GAINTH_3_0_MCS5GAINTH2_SHIFT    16
#define MCS5GAINTH_3_0_MCS5GAINTH1_MSK      0x0000FF00
#define MCS5GAINTH_3_0_MCS5GAINTH1_SHIFT    8
#define MCS5GAINTH_3_0_MCS5GAINTH0_MSK      0x000000FF
#define MCS5GAINTH_3_0_MCS5GAINTH0_SHIFT    0

// Register Address: 'h0a8
#define MCS5GAINTH_4_MCS5GAINTH4_MSK      0x000000FF
#define MCS5GAINTH_4_MCS5GAINTH4_SHIFT    0

// Register Address: 'h00ac
#define MCS6GAINTH_3_0_MCS6GAINTH3_MSK      0xFF000000
#define MCS6GAINTH_3_0_MCS6GAINTH3_SHIFT    24
#define MCS6GAINTH_3_0_MCS6GAINTH2_MSK      0x00FF0000
#define MCS6GAINTH_3_0_MCS6GAINTH2_SHIFT    16
#define MCS6GAINTH_3_0_MCS6GAINTH1_MSK      0x0000FF00
#define MCS6GAINTH_3_0_MCS6GAINTH1_SHIFT    8
#define MCS6GAINTH_3_0_MCS6GAINTH0_MSK      0x000000FF
#define MCS6GAINTH_3_0_MCS6GAINTH0_SHIFT    0

// Register Address: 'h0b0
#define MCS6GAINTH_4_MCS6GAINTH4_MSK      0x000000FF
#define MCS6GAINTH_4_MCS6GAINTH4_SHIFT    0

// Register Address: 'h00b4
#define MCS7GAINTH_3_0_MCS7GAINTH3_MSK      0xFF000000
#define MCS7GAINTH_3_0_MCS7GAINTH3_SHIFT    24
#define MCS7GAINTH_3_0_MCS7GAINTH2_MSK      0x00FF0000
#define MCS7GAINTH_3_0_MCS7GAINTH2_SHIFT    16
#define MCS7GAINTH_3_0_MCS7GAINTH1_MSK      0x0000FF00
#define MCS7GAINTH_3_0_MCS7GAINTH1_SHIFT    8
#define MCS7GAINTH_3_0_MCS7GAINTH0_MSK      0x000000FF
#define MCS7GAINTH_3_0_MCS7GAINTH0_SHIFT    0

// Register Address: 'h0b8
#define MCS7GAINTH_4_MCS7GAINTH4_MSK      0x000000FF
#define MCS7GAINTH_4_MCS7GAINTH4_SHIFT    0

// Register Address: 'h00bc
#define MCS0RXGAIN_3_0_MCS0RXGAIN3_MSK      0xFF000000
#define MCS0RXGAIN_3_0_MCS0RXGAIN3_SHIFT    24
#define MCS0RXGAIN_3_0_MCS0RXGAIN2_MSK      0x00FF0000
#define MCS0RXGAIN_3_0_MCS0RXGAIN2_SHIFT    16
#define MCS0RXGAIN_3_0_MCS0RXGAIN1_MSK      0x0000FF00
#define MCS0RXGAIN_3_0_MCS0RXGAIN1_SHIFT    8
#define MCS0RXGAIN_3_0_MCS0RXGAIN0_MSK      0x000000FF
#define MCS0RXGAIN_3_0_MCS0RXGAIN0_SHIFT    0

// Register Address: 'h0c0
#define MCS0RXGAIN_5_4_MCS0RXGAIN5_MSK      0x0000FF00
#define MCS0RXGAIN_5_4_MCS0RXGAIN5_SHIFT    8
#define MCS0RXGAIN_5_4_MCS0RXGAIN4_MSK      0x000000FF
#define MCS0RXGAIN_5_4_MCS0RXGAIN4_SHIFT    0

// Register Address: 'h00c4
#define MCS1RXGAIN_3_0_MCS1RXGAIN3_MSK      0xFF000000
#define MCS1RXGAIN_3_0_MCS1RXGAIN3_SHIFT    24
#define MCS1RXGAIN_3_0_MCS1RXGAIN2_MSK      0x00FF0000
#define MCS1RXGAIN_3_0_MCS1RXGAIN2_SHIFT    16
#define MCS1RXGAIN_3_0_MCS1RXGAIN1_MSK      0x0000FF00
#define MCS1RXGAIN_3_0_MCS1RXGAIN1_SHIFT    8
#define MCS1RXGAIN_3_0_MCS1RXGAIN0_MSK      0x000000FF
#define MCS1RXGAIN_3_0_MCS1RXGAIN0_SHIFT    0

// Register Address: 'h0c8
#define MCS1RXGAIN_5_4_MCS1RXGAIN5_MSK      0x0000FF00
#define MCS1RXGAIN_5_4_MCS1RXGAIN5_SHIFT    8
#define MCS1RXGAIN_5_4_MCS1RXGAIN4_MSK      0x000000FF
#define MCS1RXGAIN_5_4_MCS1RXGAIN4_SHIFT    0

// Register Address: 'h00cc
#define MCS2RXGAIN_3_0_MCS2RXGAIN3_MSK      0xFF000000
#define MCS2RXGAIN_3_0_MCS2RXGAIN3_SHIFT    24
#define MCS2RXGAIN_3_0_MCS2RXGAIN2_MSK      0x00FF0000
#define MCS2RXGAIN_3_0_MCS2RXGAIN2_SHIFT    16
#define MCS2RXGAIN_3_0_MCS2RXGAIN1_MSK      0x0000FF00
#define MCS2RXGAIN_3_0_MCS2RXGAIN1_SHIFT    8
#define MCS2RXGAIN_3_0_MCS2RXGAIN0_MSK      0x000000FF
#define MCS2RXGAIN_3_0_MCS2RXGAIN0_SHIFT    0

// Register Address: 'h0d0
#define MCS2RXGAIN_5_4_MCS2RXGAIN5_MSK      0x0000FF00
#define MCS2RXGAIN_5_4_MCS2RXGAIN5_SHIFT    8
#define MCS2RXGAIN_5_4_MCS2RXGAIN4_MSK      0x000000FF
#define MCS2RXGAIN_5_4_MCS2RXGAIN4_SHIFT    0

// Register Address: 'h00d4
#define MCS3RXGAIN_3_0_MCS3RXGAIN3_MSK      0xFF000000
#define MCS3RXGAIN_3_0_MCS3RXGAIN3_SHIFT    24
#define MCS3RXGAIN_3_0_MCS3RXGAIN2_MSK      0x00FF0000
#define MCS3RXGAIN_3_0_MCS3RXGAIN2_SHIFT    16
#define MCS3RXGAIN_3_0_MCS3RXGAIN1_MSK      0x0000FF00
#define MCS3RXGAIN_3_0_MCS3RXGAIN1_SHIFT    8
#define MCS3RXGAIN_3_0_MCS3RXGAIN0_MSK      0x000000FF
#define MCS3RXGAIN_3_0_MCS3RXGAIN0_SHIFT    0

// Register Address: 'h0d8
#define MCS3RXGAIN_5_4_MCS3RXGAIN5_MSK      0x0000FF00
#define MCS3RXGAIN_5_4_MCS3RXGAIN5_SHIFT    8
#define MCS3RXGAIN_5_4_MCS3RXGAIN4_MSK      0x000000FF
#define MCS3RXGAIN_5_4_MCS3RXGAIN4_SHIFT    0

// Register Address: 'h00dc
#define MCS4RXGAIN_3_0_MCS4RXGAIN3_MSK      0xFF000000
#define MCS4RXGAIN_3_0_MCS4RXGAIN3_SHIFT    24
#define MCS4RXGAIN_3_0_MCS4RXGAIN2_MSK      0x00FF0000
#define MCS4RXGAIN_3_0_MCS4RXGAIN2_SHIFT    16
#define MCS4RXGAIN_3_0_MCS4RXGAIN1_MSK      0x0000FF00
#define MCS4RXGAIN_3_0_MCS4RXGAIN1_SHIFT    8
#define MCS4RXGAIN_3_0_MCS4RXGAIN0_MSK      0x000000FF
#define MCS4RXGAIN_3_0_MCS4RXGAIN0_SHIFT    0

// Register Address: 'h0e0
#define MCS4RXGAIN_5_4_MCS4RXGAIN5_MSK      0x0000FF00
#define MCS4RXGAIN_5_4_MCS4RXGAIN5_SHIFT    8
#define MCS4RXGAIN_5_4_MCS4RXGAIN4_MSK      0x000000FF
#define MCS4RXGAIN_5_4_MCS4RXGAIN4_SHIFT    0

// Register Address: 'h00e4
#define MCS5RXGAIN_3_0_MCS5RXGAIN3_MSK      0xFF000000
#define MCS5RXGAIN_3_0_MCS5RXGAIN3_SHIFT    24
#define MCS5RXGAIN_3_0_MCS5RXGAIN2_MSK      0x00FF0000
#define MCS5RXGAIN_3_0_MCS5RXGAIN2_SHIFT    16
#define MCS5RXGAIN_3_0_MCS5RXGAIN1_MSK      0x0000FF00
#define MCS5RXGAIN_3_0_MCS5RXGAIN1_SHIFT    8
#define MCS5RXGAIN_3_0_MCS5RXGAIN0_MSK      0x000000FF
#define MCS5RXGAIN_3_0_MCS5RXGAIN0_SHIFT    0

// Register Address: 'h0e8
#define MCS5RXGAIN_5_4_MCS5RXGAIN5_MSK      0x0000FF00
#define MCS5RXGAIN_5_4_MCS5RXGAIN5_SHIFT    8
#define MCS5RXGAIN_5_4_MCS5RXGAIN4_MSK      0x000000FF
#define MCS5RXGAIN_5_4_MCS5RXGAIN4_SHIFT    0

// Register Address: 'h00ec
#define MCS6RXGAIN_3_0_MCS6RXGAIN3_MSK      0xFF000000
#define MCS6RXGAIN_3_0_MCS6RXGAIN3_SHIFT    24
#define MCS6RXGAIN_3_0_MCS6RXGAIN2_MSK      0x00FF0000
#define MCS6RXGAIN_3_0_MCS6RXGAIN2_SHIFT    16
#define MCS6RXGAIN_3_0_MCS6RXGAIN1_MSK      0x0000FF00
#define MCS6RXGAIN_3_0_MCS6RXGAIN1_SHIFT    8
#define MCS6RXGAIN_3_0_MCS6RXGAIN0_MSK      0x000000FF
#define MCS6RXGAIN_3_0_MCS6RXGAIN0_SHIFT    0

// Register Address: 'h0f0
#define MCS6RXGAIN_5_4_MCS6RXGAIN5_MSK      0x0000FF00
#define MCS6RXGAIN_5_4_MCS6RXGAIN5_SHIFT    8
#define MCS6RXGAIN_5_4_MCS6RXGAIN4_MSK      0x000000FF
#define MCS6RXGAIN_5_4_MCS6RXGAIN4_SHIFT    0

// Register Address: 'h00f4
#define MCS7RXGAIN_3_0_MCS7RXGAIN3_MSK      0xFF000000
#define MCS7RXGAIN_3_0_MCS7RXGAIN3_SHIFT    24
#define MCS7RXGAIN_3_0_MCS7RXGAIN2_MSK      0x00FF0000
#define MCS7RXGAIN_3_0_MCS7RXGAIN2_SHIFT    16
#define MCS7RXGAIN_3_0_MCS7RXGAIN1_MSK      0x0000FF00
#define MCS7RXGAIN_3_0_MCS7RXGAIN1_SHIFT    8
#define MCS7RXGAIN_3_0_MCS7RXGAIN0_MSK      0x000000FF
#define MCS7RXGAIN_3_0_MCS7RXGAIN0_SHIFT    0

// Register Address: 'h0f8
#define MCS7RXGAIN_5_4_MCS7RXGAIN5_MSK      0x0000FF00
#define MCS7RXGAIN_5_4_MCS7RXGAIN5_SHIFT    8
#define MCS7RXGAIN_5_4_MCS7RXGAIN4_MSK      0x000000FF
#define MCS7RXGAIN_5_4_MCS7RXGAIN4_SHIFT    0

// Register Address: 'h00fc
#define MCS0RXGAININDEX_3_0_MCS0RXINDEXGAIN3_MSK      0x1F000000
#define MCS0RXGAININDEX_3_0_MCS0RXINDEXGAIN3_SHIFT    24
#define MCS0RXGAININDEX_3_0_MCS0RXINDEXGAIN2_MSK      0x001F0000
#define MCS0RXGAININDEX_3_0_MCS0RXINDEXGAIN2_SHIFT    16
#define MCS0RXGAININDEX_3_0_MCS0RXINDEXGAIN1_MSK      0x00001F00
#define MCS0RXGAININDEX_3_0_MCS0RXINDEXGAIN1_SHIFT    8
#define MCS0RXGAININDEX_3_0_MCS0RXINDEXGAIN0_MSK      0x0000001F
#define MCS0RXGAININDEX_3_0_MCS0RXINDEXGAIN0_SHIFT    0

// Register Address: 'h0100
#define MCS0RXGAININDEX_5_4_MCS0RXINDEXGAIN5_MSK      0x00001F00
#define MCS0RXGAININDEX_5_4_MCS0RXINDEXGAIN5_SHIFT    8
#define MCS0RXGAININDEX_5_4_MCS0RXINDEXGAIN4_MSK      0x0000001F
#define MCS0RXGAININDEX_5_4_MCS0RXINDEXGAIN4_SHIFT    0

// Register Address: 'h0104
#define MCS1RXGAININDEX_3_0_MCS1RXINDEXGAIN3_MSK      0x1F000000
#define MCS1RXGAININDEX_3_0_MCS1RXINDEXGAIN3_SHIFT    24
#define MCS1RXGAININDEX_3_0_MCS1RXINDEXGAIN2_MSK      0x001F0000
#define MCS1RXGAININDEX_3_0_MCS1RXINDEXGAIN2_SHIFT    16
#define MCS1RXGAININDEX_3_0_MCS1RXINDEXGAIN1_MSK      0x00001F00
#define MCS1RXGAININDEX_3_0_MCS1RXINDEXGAIN1_SHIFT    8
#define MCS1RXGAININDEX_3_0_MCS1RXINDEXGAIN0_MSK      0x0000001F
#define MCS1RXGAININDEX_3_0_MCS1RXINDEXGAIN0_SHIFT    0

// Register Address: 'h0108
#define MCS1RXGAININDEX_5_4_MCS1RXINDEXGAIN5_MSK      0x00001F00
#define MCS1RXGAININDEX_5_4_MCS1RXINDEXGAIN5_SHIFT    8
#define MCS1RXGAININDEX_5_4_MCS1RXINDEXGAIN4_MSK      0x0000001F
#define MCS1RXGAININDEX_5_4_MCS1RXINDEXGAIN4_SHIFT    0

// Register Address: 'h010c
#define MCS2RXGAININDEX_3_0_MCS2RXINDEXGAIN3_MSK      0x1F000000
#define MCS2RXGAININDEX_3_0_MCS2RXINDEXGAIN3_SHIFT    24
#define MCS2RXGAININDEX_3_0_MCS2RXINDEXGAIN2_MSK      0x001F0000
#define MCS2RXGAININDEX_3_0_MCS2RXINDEXGAIN2_SHIFT    16
#define MCS2RXGAININDEX_3_0_MCS2RXINDEXGAIN1_MSK      0x00001F00
#define MCS2RXGAININDEX_3_0_MCS2RXINDEXGAIN1_SHIFT    8
#define MCS2RXGAININDEX_3_0_MCS2RXINDEXGAIN0_MSK      0x0000001F
#define MCS2RXGAININDEX_3_0_MCS2RXINDEXGAIN0_SHIFT    0

// Register Address: 'h0110
#define MCS2RXGAININDEX_5_4_MCS2RXINDEXGAIN5_MSK      0x00001F00
#define MCS2RXGAININDEX_5_4_MCS2RXINDEXGAIN5_SHIFT    8
#define MCS2RXGAININDEX_5_4_MCS2RXINDEXGAIN4_MSK      0x0000001F
#define MCS2RXGAININDEX_5_4_MCS2RXINDEXGAIN4_SHIFT    0

// Register Address: 'h0114
#define MCS3RXGAININDEX_3_0_MCS3RXINDEXGAIN3_MSK      0x1F000000
#define MCS3RXGAININDEX_3_0_MCS3RXINDEXGAIN3_SHIFT    24
#define MCS3RXGAININDEX_3_0_MCS3RXINDEXGAIN2_MSK      0x001F0000
#define MCS3RXGAININDEX_3_0_MCS3RXINDEXGAIN2_SHIFT    16
#define MCS3RXGAININDEX_3_0_MCS3RXINDEXGAIN1_MSK      0x00001F00
#define MCS3RXGAININDEX_3_0_MCS3RXINDEXGAIN1_SHIFT    8
#define MCS3RXGAININDEX_3_0_MCS3RXINDEXGAIN0_MSK      0x0000001F
#define MCS3RXGAININDEX_3_0_MCS3RXINDEXGAIN0_SHIFT    0

// Register Address: 'h0118
#define MCS3RXGAININDEX_5_4_MCS3RXINDEXGAIN5_MSK      0x00001F00
#define MCS3RXGAININDEX_5_4_MCS3RXINDEXGAIN5_SHIFT    8
#define MCS3RXGAININDEX_5_4_MCS3RXINDEXGAIN4_MSK      0x0000001F
#define MCS3RXGAININDEX_5_4_MCS3RXINDEXGAIN4_SHIFT    0

// Register Address: 'h011c
#define MCS4RXGAININDEX_3_0_MCS4RXINDEXGAIN3_MSK      0x1F000000
#define MCS4RXGAININDEX_3_0_MCS4RXINDEXGAIN3_SHIFT    24
#define MCS4RXGAININDEX_3_0_MCS4RXINDEXGAIN2_MSK      0x001F0000
#define MCS4RXGAININDEX_3_0_MCS4RXINDEXGAIN2_SHIFT    16
#define MCS4RXGAININDEX_3_0_MCS4RXINDEXGAIN1_MSK      0x00001F00
#define MCS4RXGAININDEX_3_0_MCS4RXINDEXGAIN1_SHIFT    8
#define MCS4RXGAININDEX_3_0_MCS4RXINDEXGAIN0_MSK      0x0000001F
#define MCS4RXGAININDEX_3_0_MCS4RXINDEXGAIN0_SHIFT    0

// Register Address: 'h0120
#define MCS4RXGAININDEX_5_4_MCS4RXINDEXGAIN5_MSK      0x00001F00
#define MCS4RXGAININDEX_5_4_MCS4RXINDEXGAIN5_SHIFT    8
#define MCS4RXGAININDEX_5_4_MCS4RXINDEXGAIN4_MSK      0x0000001F
#define MCS4RXGAININDEX_5_4_MCS4RXINDEXGAIN4_SHIFT    0

// Register Address: 'h0124
#define MCS5RXGAININDEX_3_0_MCS5RXINDEXGAIN3_MSK      0x1F000000
#define MCS5RXGAININDEX_3_0_MCS5RXINDEXGAIN3_SHIFT    24
#define MCS5RXGAININDEX_3_0_MCS5RXINDEXGAIN2_MSK      0x001F0000
#define MCS5RXGAININDEX_3_0_MCS5RXINDEXGAIN2_SHIFT    16
#define MCS5RXGAININDEX_3_0_MCS5RXINDEXGAIN1_MSK      0x00001F00
#define MCS5RXGAININDEX_3_0_MCS5RXINDEXGAIN1_SHIFT    8
#define MCS5RXGAININDEX_3_0_MCS5RXINDEXGAIN0_MSK      0x0000001F
#define MCS5RXGAININDEX_3_0_MCS5RXINDEXGAIN0_SHIFT    0

// Register Address: 'h0128
#define MCS5RXGAININDEX_5_4_MCS5RXINDEXGAIN5_MSK      0x00001F00
#define MCS5RXGAININDEX_5_4_MCS5RXINDEXGAIN5_SHIFT    8
#define MCS5RXGAININDEX_5_4_MCS5RXINDEXGAIN4_MSK      0x0000001F
#define MCS5RXGAININDEX_5_4_MCS5RXINDEXGAIN4_SHIFT    0

// Register Address: 'h012c
#define MCS6RXGAININDEX_3_0_MCS6RXINDEXGAIN3_MSK      0x1F000000
#define MCS6RXGAININDEX_3_0_MCS6RXINDEXGAIN3_SHIFT    24
#define MCS6RXGAININDEX_3_0_MCS6RXINDEXGAIN2_MSK      0x001F0000
#define MCS6RXGAININDEX_3_0_MCS6RXINDEXGAIN2_SHIFT    16
#define MCS6RXGAININDEX_3_0_MCS6RXINDEXGAIN1_MSK      0x00001F00
#define MCS6RXGAININDEX_3_0_MCS6RXINDEXGAIN1_SHIFT    8
#define MCS6RXGAININDEX_3_0_MCS6RXINDEXGAIN0_MSK      0x0000001F
#define MCS6RXGAININDEX_3_0_MCS6RXINDEXGAIN0_SHIFT    0

// Register Address: 'h0130
#define MCS6RXGAININDEX_5_4_MCS6RXINDEXGAIN5_MSK      0x00001F00
#define MCS6RXGAININDEX_5_4_MCS6RXINDEXGAIN5_SHIFT    8
#define MCS6RXGAININDEX_5_4_MCS6RXINDEXGAIN4_MSK      0x0000001F
#define MCS6RXGAININDEX_5_4_MCS6RXINDEXGAIN4_SHIFT    0

// Register Address: 'h0134
#define MCS7RXGAININDEX_3_0_MCS7RXINDEXGAIN3_MSK      0x1F000000
#define MCS7RXGAININDEX_3_0_MCS7RXINDEXGAIN3_SHIFT    24
#define MCS7RXGAININDEX_3_0_MCS7RXINDEXGAIN2_MSK      0x001F0000
#define MCS7RXGAININDEX_3_0_MCS7RXINDEXGAIN2_SHIFT    16
#define MCS7RXGAININDEX_3_0_MCS7RXINDEXGAIN1_MSK      0x00001F00
#define MCS7RXGAININDEX_3_0_MCS7RXINDEXGAIN1_SHIFT    8
#define MCS7RXGAININDEX_3_0_MCS7RXINDEXGAIN0_MSK      0x0000001F
#define MCS7RXGAININDEX_3_0_MCS7RXINDEXGAIN0_SHIFT    0

// Register Address: 'h0138
#define MCS7RXGAININDEX_5_4_MCS7RXINDEXGAIN5_MSK      0x00001F00
#define MCS7RXGAININDEX_5_4_MCS7RXINDEXGAIN5_SHIFT    8
#define MCS7RXGAININDEX_5_4_MCS7RXINDEXGAIN4_MSK      0x0000001F
#define MCS7RXGAININDEX_5_4_MCS7RXINDEXGAIN4_SHIFT    0

// Register Address: 'h013c
#define PHY_RXINFO0_NRXTRAVELINGPILOTS_MSK           0x10000000
#define PHY_RXINFO0_NRXTRAVELINGPILOTS_SHIFT         28
#define PHY_RXINFO0_NRXRESPONSEINDICATION_MSK        0x0C000000
#define PHY_RXINFO0_NRXRESPONSEINDICATION_SHIFT      26
#define PHY_RXINFO0_M_BRXNDPINDICATION_MSK           0x02000000
#define PHY_RXINFO0_M_BRXNDPINDICATION_SHIFT         25
#define PHY_RXINFO0_M_BRXAGGREGATION_MSK             0x01000000
#define PHY_RXINFO0_M_BRXAGGREGATION_SHIFT           24
#define PHY_RXINFO0_M_BRXRECOMMENDSMOOTHING_MSK      0x00800000
#define PHY_RXINFO0_M_BRXRECOMMENDSMOOTHING_SHIFT    23
#define PHY_RXINFO0_NRXDATAFIELDMCS_MSK              0x00780000
#define PHY_RXINFO0_NRXDATAFIELDMCS_SHIFT            19
#define PHY_RXINFO0_M_BRXLDPC_EXTRA_MSK              0x00040000
#define PHY_RXINFO0_M_BRXLDPC_EXTRA_SHIFT            18
#define PHY_RXINFO0_M_BRXCODING_MSK                  0x00020000
#define PHY_RXINFO0_M_BRXCODING_SHIFT                17
#define PHY_RXINFO0_M_BRXSHORTGI_MSK                 0x00010000
#define PHY_RXINFO0_M_BRXSHORTGI_SHIFT               16
#define PHY_RXINFO0_NRXID_MSK                        0x0000FF80
#define PHY_RXINFO0_NRXID_SHIFT                      7
#define PHY_RXINFO0_NRXNSTS_MSK                      0x00000060
#define PHY_RXINFO0_NRXNSTS_SHIFT                    5
#define PHY_RXINFO0_NRXSIGBW_MSK                     0x00000018
#define PHY_RXINFO0_NRXSIGBW_SHIFT                   3
#define PHY_RXINFO0_UPLINKINDICATION_MSK             0x00000004
#define PHY_RXINFO0_UPLINKINDICATION_SHIFT           2
#define PHY_RXINFO0_NRXSTBC_MSK                      0x00000002
#define PHY_RXINFO0_NRXSTBC_SHIFT                    1

// Register Address: 'h0140
#define PHY_RXINFO1_NRXSCRAMINITVEC_MSK       0xFE000000
#define PHY_RXINFO1_NRXSCRAMINITVEC_SHIFT     25
#define PHY_RXINFO1_NRXDATABYTENUM_MSK        0x01FF0000
#define PHY_RXINFO1_NRXDATABYTENUM_SHIFT      16
#define PHY_RXINFO1_NRXCRC4_MSK               0x0000F000
#define PHY_RXINFO1_NRXCRC4_SHIFT             12
#define PHY_RXINFO1_APPROVED_BW_MSK           0x00000C00
#define PHY_RXINFO1_APPROVED_BW_SHIFT         10
#define PHY_RXINFO1_NRXDATASYMBOLNUM_MSK      0x000003FF
#define PHY_RXINFO1_NRXDATASYMBOLNUM_SHIFT    0

// Register Address: 'h0144
#define PHY_RXCTL3_CCA_MID_DETECT_LONGGI_THRESHOLD_MSK       0xFF000000
#define PHY_RXCTL3_CCA_MID_DETECT_LONGGI_THRESHOLD_SHIFT     24
#define PHY_RXCTL3_CCA_MID_DETECT_SHORTGI_THRESHOLD_MSK      0x00FF0000
#define PHY_RXCTL3_CCA_MID_DETECT_SHORTGI_THRESHOLD_SHIFT    16
#define PHY_RXCTL3_NBADPILOTTH_MSK                           0x0000F800
#define PHY_RXCTL3_NBADPILOTTH_SHIFT                         11
#define PHY_RXCTL3_M_BAUTOLTFMISSRESETEN_MSK                 0x00000400
#define PHY_RXCTL3_M_BAUTOLTFMISSRESETEN_SHIFT               10
#define PHY_RXCTL3_M_BCCAALWAYSON_MSK                        0x00000200
#define PHY_RXCTL3_M_BCCAALWAYSON_SHIFT                      9
#define PHY_RXCTL3_PHASE_ERROR_AVG_TIMES_MSK                 0x00000180
#define PHY_RXCTL3_PHASE_ERROR_AVG_TIMES_SHIFT               7
#define PHY_RXCTL3_M_BADJGAINATDSTF_MSK                      0x00000040
#define PHY_RXCTL3_M_BADJGAINATDSTF_SHIFT                    6
#define PHY_RXCTL3_DELTA_PHASE_AVG_TIMES_248M_MSK            0x00000038
#define PHY_RXCTL3_DELTA_PHASE_AVG_TIMES_248M_SHIFT          3
#define PHY_RXCTL3_DELTA_PHASE_AVG_TIMES_1M_MSK              0x00000007
#define PHY_RXCTL3_DELTA_PHASE_AVG_TIMES_1M_SHIFT            0

// Register Address: 'h0148
#define CCA_START_DET_TH_OBSS_SD_MSK               0x00FF0000
#define CCA_START_DET_TH_OBSS_SD_SHIFT             16
#define CCA_START_DET_TH_NPRIMARY2STARTTH_MSK      0x0000FF00
#define CCA_START_DET_TH_NPRIMARY2STARTTH_SHIFT    8
#define CCA_START_DET_TH_NPRIMARY1STARTTH_MSK      0x000000FF
#define CCA_START_DET_TH_NPRIMARY1STARTTH_SHIFT    0

// Register Address: 'h014c
#define CCA_MID_DET_TH_NSECONDARY4MIDTH_MSK      0xFF000000
#define CCA_MID_DET_TH_NSECONDARY4MIDTH_SHIFT    24
#define CCA_MID_DET_TH_NSECONDARY2MIDTH_MSK      0x00FF0000
#define CCA_MID_DET_TH_NSECONDARY2MIDTH_SHIFT    16
#define CCA_MID_DET_TH_NPRIMARY2MIDTH_MSK        0x0000FF00
#define CCA_MID_DET_TH_NPRIMARY2MIDTH_SHIFT      8
#define CCA_MID_DET_TH_NPRIMARY1MIDTH_MSK        0x000000FF
#define CCA_MID_DET_TH_NPRIMARY1MIDTH_SHIFT      0

// Register Address: 'h0150
#define CCA_ED_TH_NSECONDARY4EDTH_MSK      0xFF000000
#define CCA_ED_TH_NSECONDARY4EDTH_SHIFT    24
#define CCA_ED_TH_NSECONDARY2EDTH_MSK      0x00FF0000
#define CCA_ED_TH_NSECONDARY2EDTH_SHIFT    16
#define CCA_ED_TH_NPRIMARY2EDTH_MSK        0x0000FF00
#define CCA_ED_TH_NPRIMARY2EDTH_SHIFT      8
#define CCA_ED_TH_NPRIMARY1EDTH_MSK        0x000000FF
#define CCA_ED_TH_NPRIMARY1EDTH_SHIFT      0

// Register Address: 'h0154
#define PHY_RXPOWERINFO0_NAVGSECONDARY4POWER_MSK      0xFF000000
#define PHY_RXPOWERINFO0_NAVGSECONDARY4POWER_SHIFT    24
#define PHY_RXPOWERINFO0_NAVGSECONDARY2POWER_MSK      0x00FF0000
#define PHY_RXPOWERINFO0_NAVGSECONDARY2POWER_SHIFT    16
#define PHY_RXPOWERINFO0_NAVGPRIMARY2POWER_MSK        0x0000FF00
#define PHY_RXPOWERINFO0_NAVGPRIMARY2POWER_SHIFT      8
#define PHY_RXPOWERINFO0_NAVGPRIMARY1POWER_MSK        0x000000FF
#define PHY_RXPOWERINFO0_NAVGPRIMARY1POWER_SHIFT      0

// Register Address: 'h0158
#define PHY_RXPOWERINFO1_NAVGPRIMARY8POWER_MSK   0xFF000000
#define PHY_RXPOWERINFO1_NAVGPRIMARY8POWER_SHIFT 24
#define PHY_RXPOWERINFO1_NAVGPRIMARY4POWER_MSK   0x00FF0000
#define PHY_RXPOWERINFO1_NAVGPRIMARY4POWER_SHIFT 16
#define PHY_RXPOWERINFO1_NOBSSPOWER_MSK          0x0000FF00
#define PHY_RXPOWERINFO1_NOBSSPOWER_SHIFT        8
#define PHY_RXPOWERINFO1_NAVGPOWER_MSK           0x000000FF
#define PHY_RXPOWERINFO1_NAVGPOWER_SHIFT         0

// Register Address: 'h015c
#define PHY_RXIQCOMP0_FC_PHASE_MSK      0x03FF0000
#define PHY_RXIQCOMP0_FC_PHASE_SHIFT    16
#define PHY_RXIQCOMP0_FC_GAIN_MSK       0x00000FFF
#define PHY_RXIQCOMP0_FC_GAIN_SHIFT     0

// Register Address: 'h0160
#define PHY_RXIQCOMP1_FC_PHASE_MSK      0x03FF0000
#define PHY_RXIQCOMP1_FC_PHASE_SHIFT    16
#define PHY_RXIQCOMP1_FC_GAIN_MSK       0x00000FFF
#define PHY_RXIQCOMP1_FC_GAIN_SHIFT     0

// Register Address: 'h0164
#define PHY_RXIQCOMP2_FC_PHASE_MSK      0x03FF0000
#define PHY_RXIQCOMP2_FC_PHASE_SHIFT    16
#define PHY_RXIQCOMP2_FC_GAIN_MSK       0x00000FFF
#define PHY_RXIQCOMP2_FC_GAIN_SHIFT     0

// Register Address: 'h0168
#define PHY_RXIQCOMP3_FC_PHASE_MSK      0x03FF0000
#define PHY_RXIQCOMP3_FC_PHASE_SHIFT    16
#define PHY_RXIQCOMP3_FC_GAIN_MSK       0x00000FFF
#define PHY_RXIQCOMP3_FC_GAIN_SHIFT     0

// Register Address: 'h016c
#define PHY_RXIQCOMP4_FC_PHASE_MSK      0x03FF0000
#define PHY_RXIQCOMP4_FC_PHASE_SHIFT    16
#define PHY_RXIQCOMP4_FC_GAIN_MSK       0x00000FFF
#define PHY_RXIQCOMP4_FC_GAIN_SHIFT     0

// Register Address: 'h0170
#define PHY_RXIQCOMP5_FC_PHASE_MSK      0x03FF0000
#define PHY_RXIQCOMP5_FC_PHASE_SHIFT    16
#define PHY_RXIQCOMP5_FC_GAIN_MSK       0x00000FFF
#define PHY_RXIQCOMP5_FC_GAIN_SHIFT     0

// Register Address: 'h01dc
#define RXIQCALIB0_AVG_CTRL_MSK          0x0001FF80
#define RXIQCALIB0_AVG_CTRL_SHIFT        7
#define RXIQCALIB0_FRZ_PHASE_MSK         0x00000040
#define RXIQCALIB0_FRZ_PHASE_SHIFT       6
#define RXIQCALIB0_FRZ_GAIN_MSK          0x00000020
#define RXIQCALIB0_FRZ_GAIN_SHIFT        5
#define RXIQCALIB0_PHASE_EST_EN_MSK      0x00000010
#define RXIQCALIB0_PHASE_EST_EN_SHIFT    4
#define RXIQCALIB0_GAIN_EST_EN_MSK       0x00000008
#define RXIQCALIB0_GAIN_EST_EN_SHIFT     3
#define RXIQCALIB0_FC_PHASE_EN_MSK       0x00000004
#define RXIQCALIB0_FC_PHASE_EN_SHIFT     2
#define RXIQCALIB0_FC_GAIN_EN_MSK        0x00000002
#define RXIQCALIB0_FC_GAIN_EN_SHIFT      1
#define RXIQCALIB0_CALIB_MEN_MSK         0x00000001
#define RXIQCALIB0_CALIB_MEN_SHIFT       0

// Register Address: 'h01e0
#define RXIQCALIB1_PM_COMPEN_MSK      0x03FF0000
#define RXIQCALIB1_PM_COMPEN_SHIFT    16
#define RXIQCALIB1_GM_COMPEN_MSK      0x00000FFF
#define RXIQCALIB1_GM_COMPEN_SHIFT    0

// Register Address: 'h01e4
#define RXIQCALIB2_PHASE_STEP_MSK      0x7FFF0000
#define RXIQCALIB2_PHASE_STEP_SHIFT    16
#define RXIQCALIB2_GAIN_STEP_MSK       0x0000FFFF
#define RXIQCALIB2_GAIN_STEP_SHIFT     0

// Register Address: 'h01e8
#define PHY_RXINFO2_GAINSTATEINFO3_MSK      0x70000000
#define PHY_RXINFO2_GAINSTATEINFO3_SHIFT    28
#define PHY_RXINFO2_GAINSTATEINFO2_MSK      0x07000000
#define PHY_RXINFO2_GAINSTATEINFO2_SHIFT    24
#define PHY_RXINFO2_GAINSTATEINFO1_MSK      0x00700000
#define PHY_RXINFO2_GAINSTATEINFO1_SHIFT    20
#define PHY_RXINFO2_GAINSTATEINFO0_MSK      0x00070000
#define PHY_RXINFO2_GAINSTATEINFO0_SHIFT    16
#define PHY_RXINFO2_WORST_EVM_MSK           0x0000FF00
#define PHY_RXINFO2_WORST_EVM_SHIFT         8
#define PHY_RXINFO2_AVG_EVM_MSK             0x000000FF
#define PHY_RXINFO2_AVG_EVM_SHIFT           0

// Register Address: 'h01ec
#define PHY_RXCTL4_MIN_EVM3_MSK      0xFF000000
#define PHY_RXCTL4_MIN_EVM3_SHIFT    24
#define PHY_RXCTL4_MIN_EVM2_MSK      0x00FF0000
#define PHY_RXCTL4_MIN_EVM2_SHIFT    16
#define PHY_RXCTL4_MIN_EVM1_MSK      0x0000FF00
#define PHY_RXCTL4_MIN_EVM1_SHIFT    8
#define PHY_RXCTL4_MIN_EVM0_MSK      0x000000FF
#define PHY_RXCTL4_MIN_EVM0_SHIFT    0

// Register Address: 'h01f0
#define PHY_RXCTL5_ANGLE_LIMITER_8M_MSK      0xFF000000
#define PHY_RXCTL5_ANGLE_LIMITER_8M_SHIFT    24
#define PHY_RXCTL5_ANGLE_LIMITER_4M_MSK      0x00FF0000
#define PHY_RXCTL5_ANGLE_LIMITER_4M_SHIFT    16
#define PHY_RXCTL5_ANGLE_LIMITER_2M_MSK      0x0000FF00
#define PHY_RXCTL5_ANGLE_LIMITER_2M_SHIFT    8
#define PHY_RXCTL5_ANGLE_LIMITER_1M_MSK      0x000000FF
#define PHY_RXCTL5_ANGLE_LIMITER_1M_SHIFT    0

// Register Address: 'h01f4
#define PHY_RXCTL6_FREQFADETH2M_MSK             0xF0000000
#define PHY_RXCTL6_FREQFADETH2M_SHIFT           28
#define PHY_RXCTL6_PROTECT_TH_MSK               0x07000000
#define PHY_RXCTL6_PROTECT_TH_SHIFT             24
#define PHY_RXCTL6_RX_MAC_END_DLY_MSK           0x007F0000
#define PHY_RXCTL6_RX_MAC_END_DLY_SHIFT         16
#define PHY_RXCTL6_DIFF_DELTA_PHASE_TH_MSK      0x0000FFFF
#define PHY_RXCTL6_DIFF_DELTA_PHASE_TH_SHIFT    0

// Register Address: 'h01f8
#define PHY_LTF_SYNC_POS_SYNC_POS1_MSK      0xFFFFFFFF
#define PHY_LTF_SYNC_POS_SYNC_POS1_SHIFT    0

// Register Address: 'h01fc
#define RETREG_DATA_RETENTION_MSK      0xFFFFFFFF
#define RETREG_DATA_RETENTION_SHIFT    0

// Register Address: 'h0200
#define PHY_CFO2_ESTIMATE_CFO_EST2_MSK      0x0003FFFF
#define PHY_CFO2_ESTIMATE_CFO_EST2_SHIFT    0

// Register Address: 'h0204
#define PHY_UNUSED_REG1_MSK            0xFF000000
#define PHY_UNUSED_REG1_SHIFT          24
#define PHY_UNUSED_RFRSSIOUT_MSK       0x00C00000
#define PHY_UNUSED_RFRSSIOUT_SHIFT     22
#define PHY_UNUSED_REG0_MSK            0x003FFFFE
#define PHY_UNUSED_REG0_SHIFT          1
#define PHY_UNUSED_RFTIASATEN_MSK      0x00000001
#define PHY_UNUSED_RFTIASATEN_SHIFT    0

// Register Address: 'h0208
#define PHY_RXCTL7_FREQFADETH8M_MSK        0xF0000000
#define PHY_RXCTL7_FREQFADETH8M_SHIFT      28
#define PHY_RXCTL7_IQ_SAT_HIGH_TH_MSK      0x0FFF0000
#define PHY_RXCTL7_IQ_SAT_HIGH_TH_SHIFT    16
#define PHY_RXCTL7_FREQFADETH4M_MSK        0x0000F000
#define PHY_RXCTL7_FREQFADETH4M_SHIFT      12
#define PHY_RXCTL7_IQ_SAT_LOW_TH_MSK       0x00000FFF
#define PHY_RXCTL7_IQ_SAT_LOW_TH_SHIFT     0

// Register Address: 'h020c
#define PHY_DPD_INFO_DPD_LOOP_DLY_EST_MSK      0x003C0000
#define PHY_DPD_INFO_DPD_LOOP_DLY_EST_SHIFT    18
#define PHY_DPD_INFO_M_BDPDANSAT_MSK           0x00020000
#define PHY_DPD_INFO_M_BDPDANSAT_SHIFT         17
#define PHY_DPD_INFO_M_BDPDKNSAT_MSK           0x00010000
#define PHY_DPD_INFO_M_BDPDKNSAT_SHIFT         16
#define PHY_DPD_INFO_M_BDPDPNSAT_MSK           0x00008000
#define PHY_DPD_INFO_M_BDPDPNSAT_SHIFT         15
#define PHY_DPD_INFO_M_BDPDYNSAT_MSK           0x00004000
#define PHY_DPD_INFO_M_BDPDYNSAT_SHIFT         14
#define PHY_DPD_INFO_M_BDPD_YN_ZERO_MSK        0x00002000
#define PHY_DPD_INFO_M_BDPD_YN_ZERO_SHIFT      13
#define PHY_DPD_INFO_M_BDPD_YN_LARGE_MSK       0x00001000
#define PHY_DPD_INFO_M_BDPD_YN_LARGE_SHIFT     12
#define PHY_DPD_INFO_M_BDPD_YN_SMALL_MSK       0x00000800
#define PHY_DPD_INFO_M_BDPD_YN_SMALL_SHIFT     11
#define PHY_DPD_INFO_INV_DPD_GAIN_EST_MSK      0x000007FF
#define PHY_DPD_INFO_INV_DPD_GAIN_EST_SHIFT    0

// Register Address: 'h0210
#define PHY_DPD_CTL_NDPDANSATTH_MSK        0xF8000000
#define PHY_DPD_CTL_NDPDANSATTH_SHIFT      27
#define PHY_DPD_CTL_NDPDKNSATTH_MSK        0x07000000
#define PHY_DPD_CTL_NDPDKNSATTH_SHIFT      24
#define PHY_DPD_CTL_NDPDPNSATTH_MSK        0x00FC0000
#define PHY_DPD_CTL_NDPDPNSATTH_SHIFT      18
#define PHY_DPD_CTL_NDPDYNSATTH_MSK        0x0003FF80
#define PHY_DPD_CTL_NDPDYNSATTH_SHIFT      7
#define PHY_DPD_CTL_DPD_EN_POW_TH_MSK      0x0000007C
#define PHY_DPD_CTL_DPD_EN_POW_TH_SHIFT    2
#define PHY_DPD_CTL_DPD_EXT_DLY_MSK        0x00000003
#define PHY_DPD_CTL_DPD_EXT_DLY_SHIFT      0

// Register Address: 'h0214
#define DPD_RAM_WR_CTL_ADDR_MSK           0xFF000000
#define DPD_RAM_WR_CTL_ADDR_SHIFT         24
#define DPD_RAM_WR_CTL_IQSEL_MSK          0x00800000
#define DPD_RAM_WR_CTL_IQSEL_SHIFT        23
#define DPD_RAM_WR_CTL_WRCTL_MSK          0x00400000
#define DPD_RAM_WR_CTL_WRCTL_SHIFT        22
#define DPD_RAM_WR_CTL_WRITEDATA_MSK      0x001FFFFF
#define DPD_RAM_WR_CTL_WRITEDATA_SHIFT    0

// Register Address: 'h0218
#define DPD_RAM_RD_CTL_ADDR_MSK          0xFF000000
#define DPD_RAM_RD_CTL_ADDR_SHIFT        24
#define DPD_RAM_RD_CTL_IQSEL_MSK         0x00800000
#define DPD_RAM_RD_CTL_IQSEL_SHIFT       23
#define DPD_RAM_RD_CTL_RDCTL_MSK         0x00400000
#define DPD_RAM_RD_CTL_RDCTL_SHIFT       22
#define DPD_RAM_RD_CTL_READDATA_MSK      0x001FFFFF
#define DPD_RAM_RD_CTL_READDATA_SHIFT    0

// Register Address: 'h021c
#define PHY_DMA_ABORT_CFG_K_RX_OBSS_EN_MSK                             0x80000000
#define PHY_DMA_ABORT_CFG_K_RX_OBSS_EN_SHIFT                           31
#define PHY_DMA_ABORT_CFG_K_RX_LTF_MISS_ERR2_TRIG_EN_MSK               0x40000000
#define PHY_DMA_ABORT_CFG_K_RX_LTF_MISS_ERR2_TRIG_EN_SHIFT             30
#define PHY_DMA_ABORT_CFG_K_RX_CARRIER_LOST_TRIG_EN_MSK                0x20000000
#define PHY_DMA_ABORT_CFG_K_RX_CARRIER_LOST_TRIG_EN_SHIFT              29
#define PHY_DMA_ABORT_CFG_K_RX_DUP_BW_ERR_TRIG_EN_MSK                  0x10000000
#define PHY_DMA_ABORT_CFG_K_RX_DUP_BW_ERR_TRIG_EN_SHIFT                28
#define PHY_DMA_ABORT_CFG_K_RX_SIGBW_GT_STSBW_ERR_TRIG_EN_MSK          0x08000000
#define PHY_DMA_ABORT_CFG_K_RX_SIGBW_GT_STSBW_ERR_TRIG_EN_SHIFT        27
#define PHY_DMA_ABORT_CFG_K_RX_CRC4_ERR_TRIG_EN_MSK                    0x04000000
#define PHY_DMA_ABORT_CFG_K_RX_CRC4_ERR_TRIG_EN_SHIFT                  26
#define PHY_DMA_ABORT_CFG_K_RX_NON_1MPPDU_SIG_ROT_ERR_TRIG_EN_MSK      0x02000000
#define PHY_DMA_ABORT_CFG_K_RX_NON_1MPPDU_SIG_ROT_ERR_TRIG_EN_SHIFT    25
#define PHY_DMA_ABORT_CFG_K_RX_1MPPDU_SIG_ROT_ERR_TRIG_EN_MSK          0x01000000
#define PHY_DMA_ABORT_CFG_K_RX_1MPPDU_SIG_ROT_ERR_TRIG_EN_SHIFT        24
#define PHY_DMA_ABORT_CFG_K_RX_LTF_FALSE_2M_PPDU_TRIG_EN_MSK           0x00800000
#define PHY_DMA_ABORT_CFG_K_RX_LTF_FALSE_2M_PPDU_TRIG_EN_SHIFT         23
#define PHY_DMA_ABORT_CFG_K_RX_LTF_MISS_ERR_TRIG_EN_MSK                0x00400000
#define PHY_DMA_ABORT_CFG_K_RX_LTF_MISS_ERR_TRIG_EN_SHIFT              22
#define PHY_DMA_ABORT_CFG_RX_INVALID_SIG_TRIG_EN_MSK                   0x00200000
#define PHY_DMA_ABORT_CFG_RX_INVALID_SIG_TRIG_EN_SHIFT                 21
#define PHY_DMA_ABORT_CFG_RX_NSYM_ERR_TRIG_EN_MSK                      0x00100000
#define PHY_DMA_ABORT_CFG_RX_NSYM_ERR_TRIG_EN_SHIFT                    20
#define PHY_DMA_ABORT_CFG_RX_UNSUPPORTED_BW_TRIG_EN_MSK                0x00040000
#define PHY_DMA_ABORT_CFG_RX_UNSUPPORTED_BW_TRIG_EN_SHIFT              18
#define PHY_DMA_ABORT_CFG_RX_UNSUPPORTED_MCS_TRIG_EN_MSK               0x00020000
#define PHY_DMA_ABORT_CFG_RX_UNSUPPORTED_MCS_TRIG_EN_SHIFT             17
#define PHY_DMA_ABORT_CFG_RX_INSUFFICIENT_BW_TRIG_EN_MSK               0x00010000
#define PHY_DMA_ABORT_CFG_RX_INSUFFICIENT_BW_TRIG_EN_SHIFT             16
#define PHY_DMA_ABORT_CFG_TX_VECTOR2_UNDER_RUN_TRIG_EN_MSK             0x00000080
#define PHY_DMA_ABORT_CFG_TX_VECTOR2_UNDER_RUN_TRIG_EN_SHIFT           7
#define PHY_DMA_ABORT_CFG_TX_BUF_UNDER_RUN_TRIG_EN_MSK                 0x00000040
#define PHY_DMA_ABORT_CFG_TX_BUF_UNDER_RUN_TRIG_EN_SHIFT               6
#define PHY_DMA_ABORT_CFG_TX_INVALID_SIG_TRIG_EN_MSK                   0x00000020
#define PHY_DMA_ABORT_CFG_TX_INVALID_SIG_TRIG_EN_SHIFT                 5
#define PHY_DMA_ABORT_CFG_TX_NSYM_ERR_TRIG_EN_MSK                      0x00000010
#define PHY_DMA_ABORT_CFG_TX_NSYM_ERR_TRIG_EN_SHIFT                    4
#define PHY_DMA_ABORT_CFG_TX_DUP_BW_ERR_TRIG_EN_MSK                    0x00000008
#define PHY_DMA_ABORT_CFG_TX_DUP_BW_ERR_TRIG_EN_SHIFT                  3
#define PHY_DMA_ABORT_CFG_TX_UNSUPPORTED_BW_TRIG_EN_MSK                0x00000004
#define PHY_DMA_ABORT_CFG_TX_UNSUPPORTED_BW_TRIG_EN_SHIFT              2
#define PHY_DMA_ABORT_CFG_TX_UNSUPPORTED_M_TRIG_EN_MSK                 0x00000002
#define PHY_DMA_ABORT_CFG_TX_UNSUPPORTED_M_TRIG_EN_SHIFT               1
#define PHY_DMA_ABORT_CFG_TX_INSUFFICIENT_BW_TRIG_EN_MSK               0x00000001
#define PHY_DMA_ABORT_CFG_TX_INSUFFICIENT_BW_TRIG_EN_SHIFT             0

// Register Address: 'h0220
#define PHY_DPD_INFO2_M_BYNSAT2_MSK         0x00020000
#define PHY_DPD_INFO2_M_BYNSAT2_SHIFT       17
#define PHY_DPD_INFO2_M_BYNSAT_MSK          0x00010000
#define PHY_DPD_INFO2_M_BYNSAT_SHIFT        16
#define PHY_DPD_INFO2_DPDINITPHASE_MSK      0x0000FFFF
#define PHY_DPD_INFO2_DPDINITPHASE_SHIFT    0

// Register Address: 'h0224
#define PHY_RXCTL8_DROPDOWNLINK_MSK      0x00002000
#define PHY_RXCTL8_DROPDOWNLINK_SHIFT    13
#define PHY_RXCTL8_OBSS_SDEN_MSK         0x00001000
#define PHY_RXCTL8_OBSS_SDEN_SHIFT       12
#define PHY_RXCTL8_PARTIALBSSID_MSK      0x00000FF8
#define PHY_RXCTL8_PARTIALBSSID_SHIFT    3
#define PHY_RXCTL8_BSSCOLOR_MSK          0x00000007
#define PHY_RXCTL8_BSSCOLOR_SHIFT        0

// Register Address: 'h0228
#define PHY_STATE_INFO0_RX_STATE_MSK         0x01FFFFF0
#define PHY_STATE_INFO0_RX_STATE_SHIFT       4
#define PHY_STATE_INFO0_MACIF_STATE_MSK      0x0000000F
#define PHY_STATE_INFO0_MACIF_STATE_SHIFT    0

// Register Address: 'h022c
#define PHY_STATE_INFO1_TX_STATE_MSK      0x000003FF
#define PHY_STATE_INFO1_TX_STATE_SHIFT    0

// Register Address: 'h0230
#define PHYPSDUCRC_RXPSDUCRC_MSK      0xFFFF0000
#define PHYPSDUCRC_RXPSDUCRC_SHIFT    16
#define PHYPSDUCRC_TXPSDUCRC_MSK      0x0000FFFF
#define PHYPSDUCRC_TXPSDUCRC_SHIFT    0

// Register Address: 'h0234
#define PHY_RXINFO3_RX_PSDU_LEN_MSK      0x0001FFFF
#define PHY_RXINFO3_RX_PSDU_LEN_SHIFT    0

// Register Address: 'h0238
#define PHY_TXINFO0_TX_PSDU_LEN_MSK      0x0001FFFF
#define PHY_TXINFO0_TX_PSDU_LEN_SHIFT    0

#define TRX_MODEMBW_1M     0
#define TRX_MODEMBW_2M     1
#define TRX_MODEMBW_4M     2
#define TRX_MODEMBW_8M     3

//static void config_wphy_ah_bw(struct hgwphy_ah_reg *pwphyreg, uint8 phy_bw);
//static void enable_wphy_ah(struct hgwphy_ah_reg *pwphyreg);
//static void disable_wphy_ah(struct hgwphy_ah_reg *pwphyreg);
//static void enable_wphy_ah_cont_tx(struct hgwphy_ah_reg *pwphyreg);
//static void disable_wphy_ah_cont_tx(struct hgwphy_ah_reg *pwphyreg);
//static void config_wphy_ah_pri_ch(struct hgwphy_ah_reg *pwphyreg, uint8 pri_ch);
//static uint32 get_wphy_ah_tx_crc(struct hgwphy_ah_reg *pwphyreg);
//static void config_wphy_ah_default_reg(struct hgwphy_ah_reg *pwphyreg);
//#ifdef K_PRINT_WPHY_AH_PARAMETER
//static void disp_wphy_ah_para(struct hgwphy_ah *pwphy);
//#endif
//static void config_wphy_ah(struct hgwphy_ah *pwphy);
//#if WPHY_AH_HW_VER > 1
//static void config_dpd_ram(struct hgwphy_ah *pwphy);
//static void config_dpd_ram_sel(struct hgwphy_ah *pwphy, uint8 iq_sel);
//static int32 verify_dpd_ram(struct hgwphy_ah *pwphy);
//static int32 verify_dpd_ram_sel(struct hgwphy_ah *pwphy, uint8 iq_sel);
//static void read_dpd_ram(struct hgwphy_ah *pwphy);
//static void read_dpd_ram_sel(struct hgwphy_ah *pwphy, uint8 iq_sel);
//#endif
//static uint8 get_wphy_ah_scrambler_init(struct hgwphy_ah_reg *pwphyreg);
//static int8 get_wphy_ah_avg_power(struct hgwphy_ah_reg *pwphyreg);
//static int8 get_wphy_ah_avg_evm(struct hgwphy_ah_reg *pwphyreg);
//static uint32 get_wphy_ah_err_code(struct hgwphy_ah *pwphy);
//static uint16 get_wphy_ah_agc_info(struct hgwphy_ah_reg *pwphyreg);
//static void get_wphy_ah_info(struct hgwphy_ah *pwphy);
//static void delayxus_wphy(uint32 nXus);
//static void cali_wphy_ah_rx_imb(struct hgwphy_ah *pwphy);
//static void config_phy_ah_rx_imb(struct hgwphy_ah_reg *pwphyreg, const uint32 *prximb);
//static void enable_wphy_ah_rx_testmode(struct hgwphy_ah_reg *pwphyreg);  // might be obsoleted in the future version's LMAC
//static void disable_wphy_ah_rx_testmode(struct hgwphy_ah_reg *pwphyreg); // might be obsoleted in the future version's LMAC
//static void reset_wphy_ah(struct hgwphy_ah_reg *pwphyreg);
//static void dereset_wphy_ah(struct hgwphy_ah_reg *pwphyreg);
//static void write_wphy_ah_special_reg(struct hgwphy_ah_reg *pwphyreg, uint32 nVal32);
//static void direct_connect_wphy_ah_rx_iq(struct hgwphy_ah *pwphy, uint32 *pimbtab);
//static void swap_connect_wphy_ah_rx_iq(struct hgwphy_ah *pwphy, uint32 *pimbtab);

// layer conversion
//static void open_wphy(struct wphy_device *pdev);
//static void change_phy_para(struct wphy_device *pdev, const struct hgwphy_ah_cfg *pwhy_cfg);
//static void close_wphy(struct wphy_device *pdev);
//static void direct_wphy_rx_iq(struct wphy_device *pdev, uint32 *pimbtab);
//static void swap_wphy_rx_iq(struct wphy_device *pdev, uint32 *pimbtab);
//static void disp_wphy_para(struct wphy_device *pdev);
//static void get_wphy_info(struct wphy_device *pdev);
//static void config_wphy_bw(struct wphy_device *pdev, uint8 phy_bw);
//static void config_wphy_pri_ch(struct wphy_device *pdev, uint8 pri_ch);
//static void enable_wphy_rx_testmode(struct wphy_device *pdev);
//static void disable_wphy_rx_testmode(struct wphy_device *pdev);
//static void enable_wphy(struct wphy_device *pdev);
//static void disable_wphy(struct wphy_device *pdev);
//static uint8 get_wphy_scrambler_init(struct wphy_device *pdev);
//static int8 get_wphy_avg_power(struct wphy_device *pdev);
//static int8 get_wphy_avg_evm(struct wphy_device *pdev);
//static void enable_wphy_cont_tx(struct wphy_device *pdev);
//static void disable_wphy_cont_tx(struct wphy_device *pdev);
//static uint32 get_wphy_tx_crc(struct wphy_device *pdev);
//static void cali_wphy_rx_imb(struct wphy_device *pdev);
//static void write_wphy_special_reg(struct wphy_device *pdev, uint32 nVal32);
//static uint32 get_wphy_err_code(struct wphy_device *pdev);
//static uint16 get_wphy_agc_info(struct wphy_device *pdev);
int32 hgwphy_ah_attach(uint32 dev_id, struct hgwphy_ah *pwphy, const struct hgwphy_ah_cfg *pwhy_cfg, union _dpd_ram *pdpd_ram);
#endif

