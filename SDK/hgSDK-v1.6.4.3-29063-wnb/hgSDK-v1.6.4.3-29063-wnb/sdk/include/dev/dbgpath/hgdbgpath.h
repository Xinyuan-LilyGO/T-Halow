// hgdbgpath.h
// early version of 802dot11ah debugpath software access register definition
#ifndef _HGDBGPATH_H_
#define _HGDBGPATH_H_

// related register field DBGPATH_CFG.dbg_mode[0:2]
//#define K_DBGPATH_NORMAL_MODE        0  // 0: normal (direction is controlled by MAC)
//#define K_DBGPATH_RAM2DAC_MODE       1  // 1: RAM to DAC mode (TX RF test)
//#define K_DBGPATH_RAM2PHY_MODE       2  // 2: RAM to PHY mode (RX PHY test)
//#define K_DBGPATH_PHY2RAM_MODE       3  // 3: PHY to RAM mode (TX PHY test)
//#define K_DBGPATH_ADC2RAM_MODE       4  // 4: ADC to RAM mode (RX RF test)
//#define K_DBGPATH_ADC2RAM_DPD_MODE   5  // 5: ADC to RAM when tx enabled and tx data valid

// related register field DBGPATH_CFG.Ext_rf_en
#define K_USE_INTERNAL_RF            0  // directly connected to RF TX/RX
#define K_USE_EXTERNAL_RF            1  // IO to external RF(DDR)

// ad9361 or ad9365's reg address
#define K_EXT_RF_RX_ADDR            0x109
#define K_EXT_RF_TX_ADDR            0x73

// debug path dma abort condition
#define K_DBGPATH_DMA_FREERUN       0x0
#define K_DBGPATH_DMA_STOP_PHYRXEND 0x1
#define K_DBGPATH_DMA_STOP_PHYRXERR 0x2
#define K_DBGPATH_DMA_STOP_LTFSYNC  0x3

struct MIPICTLDATA
{
    struct {
        // bit 0:2
        uint32           CSS                                 :  3,
        //----------------------------------------------------
        // bit 3
                         reserved0                           :  1,
        //----------------------------------------------------
        // bit 4:7
                         SlaveAddr                           :  4,
        //----------------------------------------------------
        // bit 8:11
        // Number of bytes to transmit
        // 0: 1 byte
        // 1: 2 bytes
        // 2: 3 bytes
        // 3: 4 bytes
        // Otherwise not allow
        // This field is valid only if serial_en == 1'b1 and serial_type == 1'b1
                         DBN                                 :  4,
        //----------------------------------------------------
        // bit 12:15
                         reserved1                           :  4,
        //----------------------------------------------------
        // bit 16:23
        // The slave device's register address for RF MIPI mode
        // This field is valid only if serial_en == 1'b1 and serial_type == 1'b1
                         SlaveRegAddr                        :  8,
        //----------------------------------------------------
        // bit 24:26
                         reserved2                           :  3,
        //----------------------------------------------------
        // bit 27
        // Sampling edge select: (valid for full speed mode)
        // 0: falling edge
        // 1: rising edge
                         SES                                 :  1,
        //----------------------------------------------------
        // bit 28
        // Data rate
        // 0: full speed
        // 1: half speed
                         DRR                                 :  1,
        //----------------------------------------------------
        // bit 29
        // Determine whether to enable or disable auto trig function
        // 0: disable
        // 1: enable
                         auto_trig_en                        :  1,
        //----------------------------------------------------                
        // bit 30:31
                         reserved3                           :  2;
        //----------------------------------------------------
    } mipictl;
    //----------------------------------------------------
    // MIPIWDATA0~3
    //----------------------------------------------------
    uint8 mipiwdata[4];
};

union hgdbgpath_cfg
{
    struct {
        //----------------------------------------------------
        // related register DBGPATH_CFG
        //----------------------------------------------------
        struct {
            // 1st parameter
            // bit 0:2
            uint32           dbg_mode                              :   3,
            //----------------------------------------------------
            // bit 3
                             Ext_rf_en                             :   1,
            //----------------------------------------------------
            // bit 4
                             dma_start                             :   1,
            //----------------------------------------------------
            // bit 5
                             dma_abort_trigger                     :   1,
            //----------------------------------------------------
            // bit 6:10
                             rf_tx_clk_delay                       :   5,
            //----------------------------------------------------
            // bit 11:15
                             rf_rx_clk_delay                       :   5,
            //----------------------------------------------------
            // bit 16
                             m_bIQrev_adc                          :   1,
            //----------------------------------------------------
            // 8th parameter
            // bit 17
                             m_bIQrev_dac                          :   1,
            //----------------------------------------------------
            // bit 18:19
            // 2'db00: no abort condition, free run
            // 2'd01: Packet Decode Done
            // 2'd10: error code
            // 2'd11: LTF synchronization
                             RxDmaAbortCond                        :   2,
            //----------------------------------------------------
            // bit 20
            // 0: the ddr IO[11:0] work as both adc input  and dac out,the IO direction is atuo controlled.
            // 1:one bus of dedicated tx_data_iq[9:0] bus enabled,  the orignal ddr IO[11:0] work as adc input only.
            // (this bit is not included in JX6001 MPW2)
                             AdaptDpdPathEn                        :   1,
            //----------------------------------------------------
            // bit 21
            // 1'b0: latch out TX_DPD_POWER_INDEX via hardware triggered spi bus when rf_tx_en rises
            // 1'b1:if this bit is set, latch out RX_DPD_POWER_INDEX and TX_DPD_POWER_INDEX  when rf_tx_en rises via spi bus
                             DpdPwrIdxEn                           :   1,
            //----------------------------------------------------
            // bit 22
            // Write this bit will start dma2 transfer,dma2 only writes adc_data to ram.
                             dma2_start                            :   1,
            //----------------------------------------------------
            // bit 23
            // The conversion from zero to one of this bit will abort dma2 transfer
                             dma2_abort_trigger                    :   1,
            //----------------------------------------------------
            // bit 24
            // 1'b0: select ddr_data_in (input bus no.1 )to async fifo
            // 1'b1: select ddr_data_in2 (input bus no.2) to async fifo.
            // ddr_data_in[11:0] (bus no.1) :{pa_in[29:26],pa_in[21:14]}
            // ddr_data_in2 bus no.2:{ pb_in[15:14],pb_in[8],pb_in[4:0],pa_in[5:4]}
                             ddr_bus2_sel                          :   1,
            //----------------------------------------------------
            // bit 25
                             Clk_out_aon                           :   1,
            //----------------------------------------------------
            // bit 26
            // 1'b0:rfdigcal_adc in data source is from adc
            // 1'b1: rfdigcal_adc in data source is from tdma
                             rfdigcal_adc_src_sel                  :   1,
            //----------------------------------------------------
            // bit 27
                             hw_freq_kick_en                       :   1,
            //----------------------------------------------------
            // bit 28:31
                             TX_LO_FREQ                            :   4;
            //----------------------------------------------------
        } ndbgpath_cfg;
#if RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
        //----------------------------------------------------
        // TXCALIB_CFG0
        //----------------------------------------------------
        struct {
            // bit 0:9
            // TX I path dc offset compensation value,Q9.0
            uint32           tx_i_dcofs                          :  10,
            //----------------------------------------------------
            // bit 10:19
            // TX Q path dc offset compensation value,Q9.0
                             tx_q_dcofs                          :  10,
            //----------------------------------------------------
            // bit 20:30
            // TX Digital gain,unsigned Q1.10,  default value 0x400
                             tx_dig_gain                         :  11,
            //----------------------------------------------------
            // bit 31
            // Tx calibration enable, 1: enable tx calibraion   0:disable and bypass tx calibration
            // The function is enable if rf tx enable and tx_cal_en bit are enable or RAM to DAC mode is selected.
                             Txcal_en                            :   1;
            //----------------------------------------------------
        } ntxcalib_cfg0;
        //----------------------------------------------------
        // TXCALIB_CFG1
        //----------------------------------------------------
        struct {
            // bit 0:8
            // TX IQ imbalance, phase compensation, Q8.0
            uint32           tx_phase_comp                       :   9,
            //----------------------------------------------------
            // bit 9:20
            // TX IQ imbalance, gain compensation, unsigned Q1.11
                             tx_gain_comp                        :  12,
            //----------------------------------------------------
            // bit 21:31
                             Reserved                            :  11;
            //----------------------------------------------------
        } ntxcalib_cfg1;
        //----------------------------------------------------
        // DBG_COUNTER
        // The low to high transition of dma_start bit will force the value to zero.
        // The counter will increase until DMA transfer end
        // This field is cleared at rising edge of DMA start bit
        // The stop position can be derived from  DMA buffer size, DMA reload mode  and DBG_COUNTER
        // uint32           Sample_pair_counter;
        //----------------------------------------------------
        // TX_POWER_INDEX
        //----------------------------------------------------
        struct {
            // bit 0:5
            uint32           tx_power_index                      :  6,
            //----------------------------------------------------
            // bit 7:6
                             reserved0                           :  2,
            //----------------------------------------------------
            // bit 8:17
                             Address                             :  10,
            //----------------------------------------------------
            // bit 18:22
                             reserved1                           :  5,
            //----------------------------------------------------
            // bit 23
                             RWindicator                         :  1,
            //----------------------------------------------------
            // bit 24:31
                             reserved2                           :  8;
            //----------------------------------------------------
        } ntx_power_index;
        //----------------------------------------------------
        // RX_POWER_INDEX
        //----------------------------------------------------
        struct {
            // bit 0:5
            uint32           rx_power_index                      :  6,
            //----------------------------------------------------
            // bit 7:6
                             reserved0                           :  2,
            //----------------------------------------------------
            // bit 8:17
            // Address of RX register of external RF IC
                             Address                             :  10,
            //----------------------------------------------------
            // bit 18:22
                             reserved1                           :  5,
            //----------------------------------------------------
            // bit 23
                             RWindicator                         :  1,
            //----------------------------------------------------
            // bit 24:31
                             reserved2                           :  8;
            //----------------------------------------------------
        } nrx_power_index;
        //----------------------------------------------------
        // RX_DPD_POWER_INDEX
        //----------------------------------------------------
        struct {
            // bit 0:5
            uint32           rx_power_index                      :  6,
            //----------------------------------------------------
            // bit 7:6
                             reserved0                           :  2,
            //----------------------------------------------------
            // bit 8:17
            // Address of RX register of external RF IC
                             Address                             : 10,
            //----------------------------------------------------
            // bit 18:22
                             reserved1                           :  5,
            //----------------------------------------------------
            // bit 23
                             RWindicator                         :  1,
            //----------------------------------------------------
            // bit 24:31
                             reserved2                           :  8;
            //----------------------------------------------------
        } nrx_dpd_power_index;
#else
        //----------------------------------------------------
        // EXTSPI_TX_PWR_CMD
        //----------------------------------------------------
        struct {
            // bit 0:5
            uint32           tx_power_index                      :  8,
            //----------------------------------------------------
            // bit 8:17
                             Address                             :  10,
            //----------------------------------------------------
            // bit 18:22
                             reserved1                           :  5,
            //----------------------------------------------------
            // bit 23
                             RWindicator                         :  1,
            //----------------------------------------------------
            // bit 24:31
                             reserved2                           :  8;
            //----------------------------------------------------
        } n_extspi_tx_power_cmd;
        //----------------------------------------------------
        // EXTSPI_RX_PWR_CMD
        //----------------------------------------------------
        struct {
            // bit 0:5
            uint32           rx_power_index                      :  8,
            //----------------------------------------------------
            // bit 8:17
                             Address                             :  10,
            //----------------------------------------------------
            // bit 18:22
                             reserved1                           :  5,
            //----------------------------------------------------
            // bit 23
                             RWindicator                         :  1,
            //----------------------------------------------------
            // bit 24:31
                             reserved2                           :  8;
            //----------------------------------------------------
        } n_extspi_rx_power_cmd;
        //----------------------------------------------------
        // EXTSPI_RX_DPD_PWR_CMD
        //----------------------------------------------------
        struct {
            // bit 0:5
            uint32           rx_power_index                      :  8,
            //----------------------------------------------------
            // bit 8:17
                             Address                             :  10,
            //----------------------------------------------------
            // bit 18:22
                             reserved1                           :  5,
            //----------------------------------------------------
            // bit 23
                             RWindicator                         :  1,
            //----------------------------------------------------
            // bit 24:31
                             reserved2                           :  8;
            //----------------------------------------------------
        } n_extspi_rx_dpd_power_cmd;
        //----------------------------------------------------
        // RFENCTL0
        //----------------------------------------------------
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
            // 0: no mipi err received
            // 1:mipi err received, no further command will be issued. To clear this bit write mipi_en bit to 0.
                             mipi_err_pending                    :  1,
            //----------------------------------------------------
            // bit 13
            // 1'b0:select rf spi rf_lo_freq hardware trigger for tx4001 rf
            // 1'b1:select rf spi gain_idx hardware trigger for 9361
                            sel_9361_hwspi                       :  1,
            //----------------------------------------------------
            // bit 14
                            reserved                             :  1,
            //----------------------------------------------------
            // bit 15
            // 1'b1:enable rfif  (debug path generate io-timing)
            // 1'b0:disable and sync reset rfif sub-module to initial state
                            rfif_enable                          :  1,
            //----------------------------------------------------
            // bit 16:19
            // (0:2:30)+1us
            // if mipi_en == false
            //    Ramp up of rf_switch_sel0 is triggered by rising edge of rf_tx_en signal
            // else
            //    mipi_cmd0 (command 0 is to configure rf switch to TX path througth mipi interface) is triggered by rising edge of rf_tx_en signal
            // end
            // for more detail see section Timing of MAC to PHY,RF and calibration module

                            rf_switch_sel0_en_dly                :  4,
            //----------------------------------------------------
            // bit 20:23
            // (0:8:120)+1 us
            // if mipi_en == false
            //    Ramp down of rf_switch_sel0 is triggered by tx_end_p signal from PHY
            // else
            //    mipi_cmd1 (command 1 is to configure rf switch to RX path througth mipi interface) is triggered by tx_end_p signal from PHY
            // end
                            rf_switch_sel0_dis_dly               :  4,
            //----------------------------------------------------
            // bit 24:27
            // (0:2:30)+1us
            // if mipi_en == false
            //     Ramp up of rf_switch_sel1 is triggered by rx_end_for_timing_p signal from PHY
            //     rf_switch_sel1 is used to drive the rf switch to tx path which is used for calculating RX DCOC
            // else
            //     mipi_cmd0  (command 0 is to configure rf switch to TX path througth mipi interface) is triggered by rx_end_for_timing_p signal from PHY
            // end
                            rf_switch_sel1_en_dly               :  4,
            //----------------------------------------------------
            // bit 28:31
            // rf_switch_sel1_dis_dly   (0:8:120)+1 us
            // if mipi_en == false
            //     Ramp down of rf_switch_sel1 is triggered by rx_end_for_timing_p signal from PHY
            // else
            //     mipi_cmd1  (command 1 is to configure rf switch to RX path througth mipi interface) is triggered by rx_end_for_timing_p signal from PHY
            // end
                            rf_switch_sel1_dis_dly               :  4;
            //----------------------------------------------------
        } n_rf_en_ctl0;
        //----------------------------------------------------
        // RFENCTL1
        //----------------------------------------------------
        struct {
            // bit 0:3
            // (0:8:120)+1 us
            // Ramp up of rx_dc_est is triggered by rx_end_for_timing_p signal from PHY
            uint32           rx_dc_est_en_dly                    :  4,
            //----------------------------------------------------
            // bit 4:7
            // (0:8:120)+1 us
            // Ramp down of rx_dc_est is strickly followed by ramp up of bk_noise
                             rx_dc_est_dis_dly                   :  4,
            //----------------------------------------------------
            // bit 8:11
            // (0:8:120)+1 us
            // Ramp up of bk_noise is triggered by rx_end_for_timing_p signal from PHY
                             bk_noise_en_dly                     :  4,
            //----------------------------------------------------
            // bit 12:15
            // (0:8:120)+1 us
            // Ramp down of bk_noise is strickly followed by ramp up of bk_noise
                             bk_noise_dis_dly                    :  4,
            //----------------------------------------------------
            // bit 16:19
            // (0:2:30)+1us
            // Ramp up of dac_en is triggered by rising edge of rf_tx_en signal
                             dpd_fb_en_dly                       :  4,
            //----------------------------------------------------
            // bit 20:23
            // (0:8:120)+1 us
            // Ramp down of dpd_fb is triggered by tx_end_p signal from PHY
                             dpd_fb_dis_dly                      :  4,
            //----------------------------------------------------
            // bit 24:27
            // (0:2:30)+1us
            // Ramp up of dac_en is triggered by rising edge of rf_tx_en signal
                             dac_en_dly                          :  4,
            //----------------------------------------------------
            // bit 28:31
            // (0:8:120)+1 us
            // Ramp down of dac_en is triggered by tx_end_p signal from PHY
                             dac_dis_dly                         :  4;
            //----------------------------------------------------
        } n_rf_en_ctl1;
        //----------------------------------------------------
        // RFENCTL2
        //----------------------------------------------------
        struct {
            // bit 0:3
            // (0:2:30)+1 us
            // Ramp up of rx_dc_est is triggered by rx_end_for_timing_p signal from PHY
            uint32           adc_en_dly                          :  4,
            //----------------------------------------------------
            // bit 4:7
            // (0:8:120)+1 us
            // Ramp down of rx_dc_est is strickly followed by ramp up of bk_noise
                             adc_dis_dly                         :  4,
            //----------------------------------------------------
            // bit 8:11
            // (0:8:120)+1 us
            // Ramp up of bk_noise is triggered by rx_end_for_timing_p signal from PHY
                             pa_ctl_en_dly                       :  4,
            //----------------------------------------------------
            // bit 12:15
            // (0:8:120)+1 us
            // Ramp down of bk_noise is strickly followed by ramp up of bk_noise
                             pa_ctl_dis_dly                      :  4,
            //----------------------------------------------------
            // bit 16:19
            // (0:2:30)+1us
            // Ramp up of dac_en is triggered by rising edge of rf_tx_en signal
                             kick_rx_lo_dly                      :  4,
            //----------------------------------------------------
            // bit 20:23
            // (0:8:120)+1 us
            // Ramp down of dpd_fb is triggered by tx_end_p signal from PHY
                             kick_tx_lo_dly                      :  4,
            //----------------------------------------------------
            // bit 24:27
            // (0:2:30)+1us
            // Ramp up of dac_en is triggered by rising edge of rf_tx_en signal
                             Extra_rf_rx_en_dis_dly              :  4,
            //----------------------------------------------------
            // bit 28:29
                             reserved                            :  2,
            //----------------------------------------------------
            // bit 30
            // rximb calibrated data to tdma2_wdata selected.
                             rximb_data_dma2_sel                 :  1,
            //----------------------------------------------------
            // bit 31
            // overrid  sync_fifo enable
                             Sync_fifo_soft_en                   :  1;
        } n_rf_en_ctl2;
        //----------------------------------------------------
        // DBGOUT_CTL0
        //----------------------------------------------------
        struct {
            // bit 0:7
            uint32           dbg_sel0                            :  8,
            //----------------------------------------------------
            // bit 8:15
                             dbg_sel1                            :  8,
            //----------------------------------------------------
            // bit 16:23
                             dbg_sel2                            :  8,
            //----------------------------------------------------
            // bit 24:31
                             dbg_sel3                            :  8;
        } n_dbgout_ctl0;
        //----------------------------------------------------
        // DBGOUT_CTL1
        //----------------------------------------------------
        struct {
            // bit 0:7
            uint32           dbg_sel4                            :  8,
            //----------------------------------------------------
            // bit 8:15
                             dbg_sel5                            :  8,
            //----------------------------------------------------
            // bit 16:23
                             dbg_sel6                            :  8,
            //----------------------------------------------------
            // bit 24:31
                             dbg_sel7                            :  8;
            //----------------------------------------------------
        } n_dbgout_ctl1;
        //----------------------------------------------------
        // MIPICTL&DATA0~3
        //----------------------------------------------------
        struct MIPICTLDATA   n_mipi_ctl_data[6];
        //----------------------------------------------------
        // RFSPIWDATA  
        //----------------------------------------------------
        uint32               n_rfspiwdata;
        //----------------------------------------------------        
#endif // RFDIGICALI_HW_VER >= 2 // 1: 4001 2: MARS
    };
#if RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    uint32           word_buf[6];  
#else
    uint32           word_buf[22];
#endif // RFDIGICALI_HW_VER >= 2 // 1: 4001 2: MARS
};
#if RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
union tx_para
{
    struct {
        // TX I path dc offset compensation value,Q9.0
        uint32           tx_i_dcofs                          :  10;
        //----------------------------------------------------
        // bit 10:19
        // TX Q path dc offset compensation value,Q9.0
        uint32           tx_q_dcofs                          :  10;
        //----------------------------------------------------
        // bit 20:30
        // TX Digital gain,unsigned Q1.10,  default value 0x400
        uint32           tx_dig_gain                         :  11;
        //----------------------------------------------------
        // bit 31
        uint32           reserved0                           :   1;
        //----------------------------------------------------
        // bit 0:8
        // TX IQ imbalance, phase compensation, Q8.0
        uint32           tx_phase_comp                       :   9;
        //----------------------------------------------------
        // bit 9:20
        // TX IQ imbalance, gain compensation, unsigned Q1.11
        uint32           tx_gain_comp                        :  12;
        //----------------------------------------------------
        // bit 21:26
        uint32           tx_power_index                      :   6;
        //----------------------------------------------------
        // bit 27:31
        uint32           reserved1                           :   5;
        //----------------------------------------------------
    } para;
    uint32    word_buf[2];
};
#endif // RFDIGICALI_HW_VER >= 2 // 1: 4001 2: MARS
struct hgdbgpath_reg
{
    __IO uint32 DBGPATH_CFG;
#if RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    __IO uint32 TXCALIB_CFG0;
    __IO uint32 TXCALIB_CFG1;
#else
    __IO uint32 UNUSED0;
    __IO uint32 UNUSED1;
#endif // RFDIGICALI_HW_VER >= 2 // 1: 4001 2: MARS
    __IO uint32 DBG_COUNTER;
#if RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    __IO uint32 TX_POWER_INDEX;
    __IO uint32 RX_POWER_INDEX;
    __IO uint32 RX_DPD_POWER_INDEX;
#else
    __IO uint32 EXTSPI_TX_PWR_CMD;
    __IO uint32 EXTSPI_RX_PWR_CMD;
    __IO uint32 EXTSPI_RX_DPD_PWR_CMD;
    __IO uint32 RFENCTL0;
    __IO uint32 RFENCTL1;
    __IO uint32 RFENCTL2;  
    __IO uint32 DBGOUT_CTL0;
    __IO uint32 DBGOUT_CTL1;
    __IO uint32 MIPICTL0;
    __IO uint32 MIPIWDATA0;
    __IO uint32 MIPICTL1;
    __IO uint32 MIPIWDATA1;
    __IO uint32 MIPICTL2;
    __IO uint32 MIPIWDATA2;
    __IO uint32 MIPICTL3;
    __IO uint32 MIPIWDATA3;
    __IO uint32 MIPICTL4;
    __IO uint32 MIPIWDATA4;
    __IO uint32 MIPICTL5;
    __IO uint32 MIPIWDATA5;
    __IO uint32 MIPI_RES[4];//husf 20200304
    __IO uint32 RFSPIWDATA;
#endif // RFDIGICALI_HW_VER >= 2 // 1: 4001 2: MARS
};

struct hgdbgpath {
    struct dbgpath_device        dev;
    struct hgdbgpath_reg         *pdbgpathreg;
    const union hgdbgpath_cfg    *pdbgpathcfg;
#if RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
    union tx_para                *ptxpara;
#endif // RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
// Register Address: 'h00
#define DBGPATH_CFG_TX_LO_FREQ_MSK                0xF0000000
#define DBGPATH_CFG_TX_LO_FREQ_SHIFT              28
#define DBGPATH_CFG_HW_FREQ_KICK_EN_MSK           0x08000000
#define DBGPATH_CFG_HW_FREQ_KICK_EN_SHIFT         27
#define DBGPATH_CFG_RFDIGCAL_ADC_SRC_SEL_MSK      0x04000000
#define DBGPATH_CFG_RFDIGCAL_ADC_SRC_SEL_SHIFT    26
#define DBGPATH_CFG_CLK_OUT_AON_MSK               0x02000000
#define DBGPATH_CFG_CLK_OUT_AON_SHIFT             25
#define DBGPATH_CFG_DDR_BUS2_SEL_MSK              0x01000000
#define DBGPATH_CFG_DDR_BUS2_SEL_SHIFT            24
#define DBGPATH_CFG_DMA2_ABORT_TRIGGER_MSK        0x00800000
#define DBGPATH_CFG_DMA2_ABORT_TRIGGER_SHIFT      23
#define DBGPATH_CFG_DBG_EN2_MSK                   0x00400000
#define DBGPATH_CFG_DBG_EN2_SHIFT                 22
#define DBGPATH_CFG_DPDPWRIDXEN_MSK               0x00200000
#define DBGPATH_CFG_DPDPWRIDXEN_SHIFT             21
#define DBGPATH_CFG_ADAPTDPDPATHEN_MSK            0x00100000
#define DBGPATH_CFG_ADAPTDPDPATHEN_SHIFT          20
#define DBGPATH_CFG_RXDMAABORTCOND_MSK            0x000C0000
#define DBGPATH_CFG_RXDMAABORTCOND_SHIFT          18
#define DBGPATH_CFG_M_BIQREV_DAC_MSK              0x00020000
#define DBGPATH_CFG_M_BIQREV_DAC_SHIFT            17
#define DBGPATH_CFG_M_BIQREV_ADC_MSK              0x00010000
#define DBGPATH_CFG_M_BIQREV_ADC_SHIFT            16
#define DBGPATH_CFG_RF_RX_CLK_DELAY_MSK           0x0000F800
#define DBGPATH_CFG_RF_RX_CLK_DELAY_SHIFT         11
#define DBGPATH_CFG_RF_TX_CLK_DELAY_MSK           0x000007C0
#define DBGPATH_CFG_RF_TX_CLK_DELAY_SHIFT         6
#define DBGPATH_CFG_DMA_ABORT_TRIGGER_MSK         0x00000020
#define DBGPATH_CFG_DMA_ABORT_TRIGGER_SHIFT       5
#define DBGPATH_CFG_DBG_EN_MSK                    0x00000010
#define DBGPATH_CFG_DBG_EN_SHIFT                  4
#define DBGPATH_CFG_EXT_RF_EN_MSK                 0x00000008
#define DBGPATH_CFG_EXT_RF_EN_SHIFT               3
#define DBGPATH_CFG_DBG_MODE_MSK                  0x00000007
#define DBGPATH_CFG_DBG_MODE_SHIFT                0

#if RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
// Register Address: 'h04
#define TXCALIBRATIONCONFIGREGISTER0_TXCAL_EN_MSK         0x80000000
#define TXCALIBRATIONCONFIGREGISTER0_TXCAL_EN_SHIFT       31
#define TXCALIBRATIONCONFIGREGISTER0_TX_DIG_GAIN_MSK      0x7FF00000
#define TXCALIBRATIONCONFIGREGISTER0_TX_DIG_GAIN_SHIFT    20
#define TXCALIBRATIONCONFIGREGISTER0_TX_Q_DCOFS_MSK       0x000FFC00
#define TXCALIBRATIONCONFIGREGISTER0_TX_Q_DCOFS_SHIFT     10
#define TXCALIBRATIONCONFIGREGISTER0_TX_I_DCOFS_MSK       0x000003FF
#define TXCALIBRATIONCONFIGREGISTER0_TX_I_DCOFS_SHIFT     0

// Register Address: 'h08
#define TXCALIBRATIONCONFIGREGISTER1_TX_GAIN_COMP_MSK       0x001FFE00
#define TXCALIBRATIONCONFIGREGISTER1_TX_GAIN_COMP_SHIFT     9
#define TXCALIBRATIONCONFIGREGISTER1_TX_PHASE_COMP_MSK      0x000001FF
#define TXCALIBRATIONCONFIGREGISTER1_TX_PHASE_COMP_SHIFT    0
#endif // RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS

// Register Address: 'h0c
#define DEBUGCOUNTERREGISTER_SAMPLE_PAIR_COUNTER_MSK      0xFFFFFFFF
#define DEBUGCOUNTERREGISTER_SAMPLE_PAIR_COUNTER_SHIFT    0

#if RFDIGICALI_HW_VER < 2
// Register Address: 'h10
#define TXPOWERINDEXREGISTER_RWINDICATOR_MSK         0x00800000
#define TXPOWERINDEXREGISTER_RWINDICATOR_SHIFT       23
#define TXPOWERINDEXREGISTER_ADDRESS_MSK             0x0003FF00
#define TXPOWERINDEXREGISTER_ADDRESS_SHIFT           8
#define TXPOWERINDEXREGISTER_TX_POWER_INDEX_MSK      0x0000003F
#define TXPOWERINDEXREGISTER_TX_POWER_INDEX_SHIFT    0

// Register Address: 'h14
#define RXPOWERINDEXREGISTER_RWINDICATOR_MSK         0x00800000
#define RXPOWERINDEXREGISTER_RWINDICATOR_SHIFT       23
#define RXPOWERINDEXREGISTER_ADDRESS_MSK             0x0003FF00
#define RXPOWERINDEXREGISTER_ADDRESS_SHIFT           8
#define RXPOWERINDEXREGISTER_RX_POWER_INDEX_MSK      0x0000003F
#define RXPOWERINDEXREGISTER_RX_POWER_INDEX_SHIFT    0

// Register Address: 'h18
#define DPDRXPOWERINDEXREGISTER_RWINDICATOR_MSK         0x00800000
#define DPDRXPOWERINDEXREGISTER_RWINDICATOR_SHIFT       23
#define DPDRXPOWERINDEXREGISTER_ADDRESS_MSK             0x0003FF00
#define DPDRXPOWERINDEXREGISTER_ADDRESS_SHIFT           8
#define DPDRXPOWERINDEXREGISTER_RX_POWER_INDEX_MSK      0x0000003F
#define DPDRXPOWERINDEXREGISTER_RX_POWER_INDEX_SHIFT    0
#else
// Register Address: 'h10
#define EXTSPI_TX_PWR_CMD_RWINDICATOR_MSK         0x00800000
#define EXTSPI_TX_PWR_CMD_RWINDICATOR_SHIFT       23
#define EXTSPI_TX_PWR_CMD_ADDRESS_MSK             0x0003FF00
#define EXTSPI_TX_PWR_CMD_ADDRESS_SHIFT           8
#define EXTSPI_TX_PWR_CMD_TX_POWER_INDEX_MSK      0x000000FF
#define EXTSPI_TX_PWR_CMD_TX_POWER_INDEX_SHIFT    0

// Register Address: 'h14
#define EXTSPI_RX_PWR_CMD_RWINDICATOR_MSK         0x00800000
#define EXTSPI_RX_PWR_CMD_RWINDICATOR_SHIFT       23
#define EXTSPI_RX_PWR_CMD_ADDRESS_MSK             0x0003FF00
#define EXTSPI_RX_PWR_CMD_ADDRESS_SHIFT           8
#define EXTSPI_RX_PWR_CMD_RX_POWER_INDEX_MSK      0x000000FF
#define EXTSPI_RX_PWR_CMD_RX_POWER_INDEX_SHIFT    0

// Register Address: 'h18
#define EXTSPI_RX_DPD_PWR_CMD_RWINDICATOR_MSK         0x00800000
#define EXTSPI_RX_DPD_PWR_CMD_RWINDICATOR_SHIFT       23
#define EXTSPI_RX_DPD_PWR_CMD_ADDRESS_MSK             0x0003FF00
#define EXTSPI_RX_DPD_PWR_CMD_ADDRESS_SHIFT           8
#define EXTSPI_RX_DPD_PWR_CMD_RX_POWER_INDEX_MSK      0x000000FF
#define EXTSPI_RX_DPD_PWR_CMD_RX_POWER_INDEX_SHIFT    0

// Register Address: 'h01c
#define RFENCTL0_RF_SWITCH_SEL1_DIS_DLY_MSK      0xF0000000
#define RFENCTL0_RF_SWITCH_SEL1_DIS_DLY_SHIFT    28
#define RFENCTL0_RF_SWITCH_SEL1_EN_DLY_MSK       0x0F000000
#define RFENCTL0_RF_SWITCH_SEL1_EN_DLY_SHIFT     24
#define RFENCTL0_RF_SWITCH_SEL0_DIS_DLY_MSK      0x00F00000
#define RFENCTL0_RF_SWITCH_SEL0_DIS_DLY_SHIFT    20
#define RFENCTL0_RF_SWITCH_SEL0_EN_DLY_MSK       0x000F0000
#define RFENCTL0_RF_SWITCH_SEL0_EN_DLY_SHIFT     16
#define RFENCTL0_RFIF_ENABLE_MSK                 0x00008000
#define RFENCTL0_RFIF_ENABLE_SHIFT               15
#define RFENCTL0_SEL_9361_HWSPI_MSK              0x00002000
#define RFENCTL0_SEL_9361_HWSPI_SHIFT            13
#define RFENCTL0_MIPI_ERR_PENDING_MSK            0x00001000
#define RFENCTL0_MIPI_ERR_PENDING_SHIFT          12
#define RFENCTL0_MIPI_ERR_CLR_IO_MSK             0x00000800
#define RFENCTL0_MIPI_ERR_CLR_IO_SHIFT           11
#define RFENCTL0_MIPI_EN_MSK                     0x00000400
#define RFENCTL0_MIPI_EN_SHIFT                   10
#define RFENCTL0_DPD_FBADCEN_SEL_MSK             0x00000200
#define RFENCTL0_DPD_FBADCEN_SEL_SHIFT           9
#define RFENCTL0_DPD_FB_ADC_EN_MSK               0x00000100
#define RFENCTL0_DPD_FB_ADC_EN_SHIFT             8
#define RFENCTL0_EN_RX_DC_EST_MSK                0x00000080
#define RFENCTL0_EN_RX_DC_EST_SHIFT              7
#define RFENCTL0_EN_BK_NOISE_MSK                 0x00000040
#define RFENCTL0_EN_BK_NOISE_SHIFT               6
#define RFENCTL0_EN_TX_SWITCH_OVRD_MSK           0x00000020
#define RFENCTL0_EN_TX_SWITCH_OVRD_SHIFT         5
#define RFENCTL0_EN_RX_SWITCH_OVRD_MSK           0x00000010
#define RFENCTL0_EN_RX_SWITCH_OVRD_SHIFT         4
#define RFENCTL0_EN_EXTRA_RF_RX_MSK              0x00000008
#define RFENCTL0_EN_EXTRA_RF_RX_SHIFT            3
#define RFENCTL0_EN_ADC_OVRD_MSK                 0x00000004
#define RFENCTL0_EN_ADC_OVRD_SHIFT               2
#define RFENCTL0_EN_DAC_OVRD_MSK                 0x00000002
#define RFENCTL0_EN_DAC_OVRD_SHIFT               1
#define RFENCTL0_EN_PA_OVRD_MSK                  0x00000001
#define RFENCTL0_EN_PA_OVRD_SHIFT                0

// Register Address: 'h020
#define RFENCTL1_DAC_DIS_DLY_MSK            0xF0000000
#define RFENCTL1_DAC_DIS_DLY_SHIFT          28
#define RFENCTL1_DAC_EN_DLY_MSK             0x0F000000
#define RFENCTL1_DAC_EN_DLY_SHIFT           24
#define RFENCTL1_DPD_FB_DIS_DLY_MSK         0x00F00000
#define RFENCTL1_DPD_FB_DIS_DLY_SHIFT       20
#define RFENCTL1_DPD_FB_EN_DLY_MSK          0x000F0000
#define RFENCTL1_DPD_FB_EN_DLY_SHIFT        16
#define RFENCTL1_BK_NOISE_DIS_DLY_MSK       0x0000F000
#define RFENCTL1_BK_NOISE_DIS_DLY_SHIFT     12
#define RFENCTL1_BK_NOISE_EN_DLY_MSK        0x00000F00
#define RFENCTL1_BK_NOISE_EN_DLY_SHIFT      8
#define RFENCTL1_RX_DC_EST_DIS_DLY_MSK      0x000000F0
#define RFENCTL1_RX_DC_EST_DIS_DLY_SHIFT    4
#define RFENCTL1_RX_DC_EST_EN_DLY_MSK       0x0000000F
#define RFENCTL1_RX_DC_EST_EN_DLY_SHIFT     0

// Register Address: 'h024
#define RFENCTL2_SYNC_FIFO_SOFT_EN_MSK           0x80000000
#define RFENCTL2_SYNC_FIFO_SOFT_EN_SHIFT         31
#define RFENCTL2_EXTRA_RF_RX_EN_DIS_DLY_MSK      0x0F000000
#define RFENCTL2_EXTRA_RF_RX_EN_DIS_DLY_SHIFT    24
#define RFENCTL2_KICK_TX_LO_DLY_MSK              0x00F00000
#define RFENCTL2_KICK_TX_LO_DLY_SHIFT            20
#define RFENCTL2_KICK_RX_LO_DLY_MSK              0x000F0000
#define RFENCTL2_KICK_RX_LO_DLY_SHIFT            16
#define RFENCTL2_PA_CTL_DIS_DLY_MSK              0x0000F000
#define RFENCTL2_PA_CTL_DIS_DLY_SHIFT            12
#define RFENCTL2_PA_CTL_EN_DLY_MSK               0x00000F00
#define RFENCTL2_PA_CTL_EN_DLY_SHIFT             8
#define RFENCTL2_ADC_DIS_DLY_MSK                 0x000000F0
#define RFENCTL2_ADC_DIS_DLY_SHIFT               4
#define RFENCTL2_ADC_EN_DLY_MSK                  0x0000000F
#define RFENCTL2_ADC_EN_DLY_SHIFT                0

// Register Address: 'h028
#define DBGOUT_CTL0_DBG_SEL3_MSK      0xFF000000
#define DBGOUT_CTL0_DBG_SEL3_SHIFT    24
#define DBGOUT_CTL0_DBG_SEL2_MSK      0x00FF0000
#define DBGOUT_CTL0_DBG_SEL2_SHIFT    16
#define DBGOUT_CTL0_DBG_SEL1_MSK      0x0000FF00
#define DBGOUT_CTL0_DBG_SEL1_SHIFT    8
#define DBGOUT_CTL0_DBG_SEL0_MSK      0x000000FF
#define DBGOUT_CTL0_DBG_SEL0_SHIFT    0

// Register Address: 'h02c
#define DBGOUT_CTL1_DBG_SEL7_MSK      0xFF000000
#define DBGOUT_CTL1_DBG_SEL7_SHIFT    24
#define DBGOUT_CTL1_DBG_SEL6_MSK      0x00FF0000
#define DBGOUT_CTL1_DBG_SEL6_SHIFT    16
#define DBGOUT_CTL1_DBG_SEL5_MSK      0x0000FF00
#define DBGOUT_CTL1_DBG_SEL5_SHIFT    8
#define DBGOUT_CTL1_DBG_SEL4_MSK      0x000000FF
#define DBGOUT_CTL1_DBG_SEL4_SHIFT    0

// Register Address: 'h030
#define MIPICTL0_AUTO_TRIG_EN_MSK      0x20000000
#define MIPICTL0_AUTO_TRIG_EN_SHIFT    29
#define MIPICTL0_DRR_MSK               0x10000000
#define MIPICTL0_DRR_SHIFT             28
#define MIPICTL0_SES_MSK               0x08000000
#define MIPICTL0_SES_SHIFT             27
#define MIPICTL0_SLAVEREGADDR_MSK      0x00FF0000
#define MIPICTL0_SLAVEREGADDR_SHIFT    16
#define MIPICTL0_DBN_MSK               0x00000F00
#define MIPICTL0_DBN_SHIFT             8
#define MIPICTL0_SLAVEADDR_MSK         0x000000F0
#define MIPICTL0_SLAVEADDR_SHIFT       4
#define MIPICTL0_CSS_MSK               0x00000007
#define MIPICTL0_CSS_SHIFT             0

// Register Address: 'h034
#define MIPIWDATA0_WRITE_DATA_MSK      0xFFFFFFFF
#define MIPIWDATA0_WRITE_DATA_SHIFT    0

// Register Address: 'h038
#define MIPICTL1_AUTO_TRIG_EN_MSK      0x20000000
#define MIPICTL1_AUTO_TRIG_EN_SHIFT    29
#define MIPICTL1_DRR_MSK               0x10000000
#define MIPICTL1_DRR_SHIFT             28
#define MIPICTL1_SES_MSK               0x08000000
#define MIPICTL1_SES_SHIFT             27
#define MIPICTL1_SLAVEREGADDR_MSK      0x00FF0000
#define MIPICTL1_SLAVEREGADDR_SHIFT    16
#define MIPICTL1_DBN_MSK               0x00000F00
#define MIPICTL1_DBN_SHIFT             8
#define MIPICTL1_SLAVEADDR_MSK         0x000000F0
#define MIPICTL1_SLAVEADDR_SHIFT       4
#define MIPICTL1_CSS_MSK               0x00000007
#define MIPICTL1_CSS_SHIFT             0

// Register Address: 'h03c
#define MIPIWDATA1_WRITE_DATA_MSK      0xFFFFFFFF
#define MIPIWDATA1_WRITE_DATA_SHIFT    0

// Register Address: 'h40
#define MIPICTL2_AUTO_TRIG_EN_MSK      0x20000000
#define MIPICTL2_AUTO_TRIG_EN_SHIFT    29
#define MIPICTL2_DRR_MSK               0x10000000
#define MIPICTL2_DRR_SHIFT             28
#define MIPICTL2_SES_MSK               0x08000000
#define MIPICTL2_SES_SHIFT             27
#define MIPICTL2_SLAVEREGADDR_MSK      0x00FF0000
#define MIPICTL2_SLAVEREGADDR_SHIFT    16
#define MIPICTL2_DBN_MSK               0x00000F00
#define MIPICTL2_DBN_SHIFT             8
#define MIPICTL2_SLAVEADDR_MSK         0x000000F0
#define MIPICTL2_SLAVEADDR_SHIFT       4
#define MIPICTL2_CSS_MSK               0x00000007
#define MIPICTL2_CSS_SHIFT             0

// Register Address: 'h44
#define MIPIWDATA2_WRITE_DATA_MSK      0xFFFFFFFF
#define MIPIWDATA2_WRITE_DATA_SHIFT    0

// Register Address: 'h48
#define MIPICTL3_AUTO_TRIG_EN_MSK      0x20000000
#define MIPICTL3_AUTO_TRIG_EN_SHIFT    29
#define MIPICTL3_DRR_MSK               0x10000000
#define MIPICTL3_DRR_SHIFT             28
#define MIPICTL3_SES_MSK               0x08000000
#define MIPICTL3_SES_SHIFT             27
#define MIPICTL3_SLAVEREGADDR_MSK      0x00FF0000
#define MIPICTL3_SLAVEREGADDR_SHIFT    16
#define MIPICTL3_DBN_MSK               0x00000F00
#define MIPICTL3_DBN_SHIFT             8
#define MIPICTL3_SLAVEADDR_MSK         0x000000F0
#define MIPICTL3_SLAVEADDR_SHIFT       4
#define MIPICTL3_CSS_MSK               0x00000007
#define MIPICTL3_CSS_SHIFT             0

// Register Address: 'h04c
#define MIPIWDATA3_WRITE_DATA_MSK      0xFFFFFFFF
#define MIPIWDATA3_WRITE_DATA_SHIFT    0

// Register Address: 'h50
#define MIPICTL4_AUTO_TRIG_EN_MSK      0x20000000
#define MIPICTL4_AUTO_TRIG_EN_SHIFT    29
#define MIPICTL4_DRR_MSK               0x10000000
#define MIPICTL4_DRR_SHIFT             28
#define MIPICTL4_SES_MSK               0x08000000
#define MIPICTL4_SES_SHIFT             27
#define MIPICTL4_SLAVEREGADDR_MSK      0x00FF0000
#define MIPICTL4_SLAVEREGADDR_SHIFT    16
#define MIPICTL4_DBN_MSK               0x00000F00
#define MIPICTL4_DBN_SHIFT             8
#define MIPICTL4_SLAVEADDR_MSK         0x000000F0
#define MIPICTL4_SLAVEADDR_SHIFT       4
#define MIPICTL4_CSS_MSK               0x00000007
#define MIPICTL4_CSS_SHIFT             0

// Register Address: 'h054
#define MIPIWDATA4_WRITE_DATA_MSK      0xFFFFFFFF
#define MIPIWDATA4_WRITE_DATA_SHIFT    0

// Register Address: 'h58
#define MIPICTL5_AUTO_TRIG_EN_MSK      0x20000000
#define MIPICTL5_AUTO_TRIG_EN_SHIFT    29
#define MIPICTL5_DRR_MSK               0x10000000
#define MIPICTL5_DRR_SHIFT             28
#define MIPICTL5_SES_MSK               0x08000000
#define MIPICTL5_SES_SHIFT             27
#define MIPICTL5_SLAVEREGADDR_MSK      0x00FF0000
#define MIPICTL5_SLAVEREGADDR_SHIFT    16
#define MIPICTL5_DBN_MSK               0x00000F00
#define MIPICTL5_DBN_SHIFT             8
#define MIPICTL5_SLAVEADDR_MSK         0x000000F0
#define MIPICTL5_SLAVEADDR_SHIFT       4
#define MIPICTL5_CSS_MSK               0x00000007
#define MIPICTL5_CSS_SHIFT             0

// Register Address: 'h05c
#define MIPIWDATA5_WRITE_DATA_MSK      0xFFFFFFFF
#define MIPIWDATA5_WRITE_DATA_SHIFT    0

// Register Address: 'h070
#define RFSPIWDATA_WRITE_DATA_MSK      0xFFFFFFFF
#define RFSPIWDATA_WRITE_DATA_SHIFT    0
#endif // RFDIGICALI_HW_VER < 2 // 1: 4001 2: MARS
// tx DCOC calibration and tx imb caliration
#define TX_DCOC_START      -50
#define TX_DCOC_STOP        50
#define TX_DCOC_STEP        5
#define TX_GAIN_START    0x780
#define TX_GAIN_STOP     0x880
#define TX_GAIN_STEP       0x8
#define TX_PHASE_START   -0xa0
#define TX_PHASE_STOP     0xa0
#define TX_PHASE_STEP      0x8

// layer conversion
//static void dbgpath_init(struct dbgpath_device *pdev);
//static void set_dbgpath_tx_dly(struct dbgpath_device *pdev, uint8 ndly);
//static void set_dbgpath_rx_dly(struct dbgpath_device *pdev, uint8 ndly);
//static void set_dbgpath_ext_tx_pwr(struct dbgpath_device *pdev, uint16 naddr, uint8 nval);
//static void set_dbgpath_extspi_rx_gain(struct dbgpath_device *pdev, uint16 naddr, uint8 nval);
//static void set_dbgpath_ext_dpd_gain(struct dbgpath_device *pdev, uint16 naddr, uint8 nval);
//static void set_dbgpath_tx_pwr(struct dbgpath_device *pdev, uint8 pwr_idx);
//static void enable_dbgpath_ext_dpd_gain(struct dbgpath_device *pdev);
//static void disable_dbgpath_ext_dpd_gain(struct dbgpath_device *pdev);
//static void set_dbgpath_mode(struct dbgpath_device *pdev, uint8 nmode);
//static uint32 get_dbgpath_dma_stop_pos(struct dbgpath_device *pdev, uint32 dma_buflen);
//static void set_dbgpath_mode(struct dbgpath_device *pdev, uint8 nmode);
//static void trig_dbgpath_dma(struct dbgpath_device *pdev);
//static void trig_dbgpath_dma2(struct dbgpath_device *pdev);
//static void abort_dbgpath_dma(struct dbgpath_device *pdev);
//static void abort_dbgpath_dma2(struct dbgpath_device *pdev);
//static void tune_dbgpath_tx_dcoc(struct dbgpath_device *pdev);
//static void tune_dbgpath_tx_imb(struct dbgpath_device *pdev);
//static void config_tx_digital_dcoc(struct dbgpath_device *pdev, int16 i_val, int16 q_val);
//static void config_tx_imb(struct dbgpath_device *pdev, int16 phase_comp, uint16 gain_comp);
//static void config_dmaend_cond(struct dbgpath_device *pdev, uint8 ncond);
int32 hgdbgpath_attach(uint32 dev_id, struct hgdbgpath *pdbgpath);
#endif

