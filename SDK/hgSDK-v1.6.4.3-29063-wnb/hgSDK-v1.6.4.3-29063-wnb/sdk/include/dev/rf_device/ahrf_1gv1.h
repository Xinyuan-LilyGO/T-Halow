
// @file    ahrf_1gv1.h
// @author  wangying
// @version V1.0.0
// @date    2019-01-12
// @brief   This file contains all the jx6001 US-RFIP driver definitions.

// Revision History
// (1) V1.0.0  2019-01-12 First Release

#ifndef __AHRF_1GV1_H__
#define __AHRF_1GV1_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @defgroup RFIP_DRV_Exported_Constants
  * @{
  */

//reg400
#define REG_RXBB0_PGA_INPUT_RES_LOW                  0x400
#define RXBB0_PGA_INPUT_RES_0_15_SHIFT               0
#define RXBB0_PGA_INPUT_RES_0_15_MSK                (0xffff<<RXBB0_PGA_INPUT_RES_0_15_SHIFT)

//reg401
#define RXBB0_PGA_FB_RES_MSK                         BIT(0)
#define RXBB0_TIA_RES_OUTPUT_SHIFT                   1
#define RXBB0_TIA_RES_OUTPUT_MSK                    (7<<RXBB0_TIA_RES_OUTPUT_SHIFT)
#define RXBB0_DCOC_DAC_I_0_4_SHIFT                   4
#define RXBB0_DCOC_DAC_I_0_4_MSK                    (0x1f<<RXBB0_DCOC_DAC_I_0_4_SHIFT)
#define RXBB0_DCOC_DAC_Q_0_4_SHIFT                   9
#define RXBB0_DCOC_DAC_Q_0_4_MSK                    (0x1f<<RXBB0_DCOC_DAC_Q_0_4_SHIFT)
#define RXBB0_TIA_R2_0_1_SHIFT                       14
#define RXBB0_TIA_R2_0_1_MSK                        (3<<RXBB0_TIA_R2_0_1_SHIFT)

//reg402
#define RXBB0_TIA_R2_2_5_SHIFT                       0
#define RXBB0_TIA_R2_2_5_MSK                        (0xf<<RXBB0_TIA_R2_2_5_SHIFT)
#define RXBB0_PGA_INPUT_RES_17_22_SHIFT              4
#define RXBB0_PGA_INPUT_RES_17_22_MSK               (0x3f<<RXBB0_PGA_INPUT_RES_17_22_SHIFT)
#define RXFE0_LNA_MAIN_GAIN_SHIFT                    10
#define RXFE0_LNA_MAIN_GAIN_MSK                     (0xf<<RXFE0_LNA_MAIN_GAIN_SHIFT)
#define RXFE0_LNA_AUX_GAIN_0_1_SHIFT                 14
#define RXFE0_LNA_AUX_GAIN_0_1_MSK                  (3<<RXFE0_LNA_AUX_GAIN_0_1_SHIFT)

//reg403
#define RXFE0_LNA_AUX_GAIN_2_3_SHIFT                 0
#define RXFE0_LNA_AUX_GAIN_2_3_MSK                  (3<<RXFE0_LNA_AUX_GAIN_2_3_SHIFT)
#define RXFE0_GM_GAIN_CTRL_PREBUF_SHIFT              2
#define RXFE0_GM_GAIN_CTRL_PREBUF_MSK               (0x3f<<RXFE0_GM_GAIN_CTRL_PREBUF_SHIFT)
#define RXFE0_LNA_BIAS_RES_SHIFT                     8
#define RXFE0_LNA_BIAS_RES_MSK                      (0xf<<RXFE0_LNA_BIAS_RES_SHIFT)
#define RXFE0_GM_BIAS_RES_SHIFT                      12
#define RXFE0_GM_BIAS_RES_MSK                       (0xf<<RXFE0_LNA_BIAS_RES_SHIFT)

//reg404
#define TXBB0_ADCD_SHIFT                             0
#define TXBB0_ADCD_MSK                              (0xf<<TXBB0_ADCD_SHIFT)
#define TXBB0_DCOC_RANGE_SHIFT                       4
#define TXBB0_DCOC_RANGE_MSK                        (3<<TXBB0_DCOC_RANGE_SHIFT)
#define TXBB0_IDCOC_DAC_SHIFT                        6
#define TXBB0_IDCOC_DAC_MSK                         (0x1ff<<TXBB0_IDCOC_DAC_SHIFT)
#define TXBB0_PGAI_0_MSK                             BIT(15)

//reg405
#define TXBB0_PGAI_1_2_SHIFT                         0
#define TXBB0_PGAI_1_2_MSK                          (3<<TXBB0_PGAI_1_2_SHIFT)
#define TXBB0_PGAO_SHIFT                             2
#define TXBB0_PGAO_MSK                              (0xff<<TXBB0_PGAO_SHIFT)
#define TXBB0_QDCOC_DAC_0_5_SHIFT                    10
#define TXBB0_QDCOC_DAC_0_5_MSK                     (0x3f<<TXBB0_QDCOC_DAC_0_5_SHIFT)

//reg406
#define REG_TXBB0_QDCOC_DAC_HIGH                     0x406
#define TXBB0_QDCOC_DAC_6_8_SHIFT                    0
#define TXBB0_QDCOC_DAC_6_8_MSK                     (7<<TXBB0_QDCOC_DAC_6_8_SHIFT)

//reg408
#define REG_OVERRIDE_GAIN                            0x408
#define OVERRIDE_RX_GAIN_0_15_MSK                    BIT(0)
#define OVERRIDE_RX_GAIN_16_31_MSK                   BIT(1)
#define OVERRIDE_RX_GAIN_32_47_MSK                   BIT(2)
#define OVERRIDE_RX_GAIN_48_63_MSK                   BIT(3)
#define OVERRIDE_TX_GAIN_0_15_MSK                    BIT(4)
#define OVERRIDE_TX_GAIN_16_31_MSK                   BIT(5)
#define OVERRIDE_TX_GAIN_32_47_MSK                   BIT(6)
#define OVERRIDE_TX_GAIN_48_63_MSK                   BIT(7)

//reg800
#define CLKBUF0_BANDSEL_SHIFT                        0
#define CLKBUF0_BANDSEL_MSK                         (7<<CLKBUF0_BANDSEL_SHIFT)
#define CLKBUF0_LOGEN_BUF_EN_MSK                     BIT(3)
#define CLKBUF0_NOTAIL_MSK                           BIT(4)
#define ILDO0_BYPASS_MSK                             BIT(5)
#define ILDO0_EN_LDO_MSK                             BIT(6)
#define ILDO0_TEST_11_MSK                            BIT(7)
#define ILDO0_VREF_LDO_SHIFT                         8
#define ILDO0_VREF_LDO_MSK                          (0xf<<ILDO0_VREF_LDO_SHIFT)
#define IREF0_BYPASS_MSK                             BIT(12)
#define IREF0_EN_LDO_MSK                             BIT(13)
#define IREF0_IREF_SEL_25UA_0_1_SHIFT                14
#define IREF0_IREF_SEL_25UA_0_1_MSK                 (3<<IREF0_IREF_SEL_25UA_0_1_SHIFT)

//reg801
#define IREF0_IREF_SEL_25UA_2_7_SHIFT                0
#define IREF0_IREF_SEL_25UA_2_7_MSK                 (0x3f<<IREF0_IREF_SEL_25UA_2_7_SHIFT)
#define IREF0_IREF_SEL_5UA_SHIFT                     6
#define IREF0_IREF_SEL_5UA_MSK                      (0x3f<<IREF0_IREF_SEL_5UA_SHIFT)
#define IREF0_TEST_11_MSK                            BIT(12)
#define PLL0_CP_LDO_BYPASS_DIG_MSK                   BIT(13)
#define PLL0_CP_LDO_EN_DIG_MSK                       BIT(14)
#define PLL0_CP_LDO_TEST_DIG_MSK                     BIT(15)

//reg802
#define PLL0_CP_LDO_VREF_PROG_DIG_SHIFT              0
#define PLL0_CP_LDO_VREF_PROG_DIG_MSK               (0xf<<PLL0_CP_LDO_VREF_PROG_DIG_SHIFT)
#define PLL0_CP_LPMODE_SEL_DIG_MSK                   BIT(4)
#define PLL0_CPLK_PROG_DIG_SHIFT                     5
#define PLL0_CPLK_PROG_DIG_MSK                      (0xf<<PLL0_CPLK_PROG_DIG_SHIFT)
#define PLL0_CPUMP_BIAS_EN_DIG_MSK                   BIT(9)
#define PLL0_CPUMP_PROG_DIG_SHIFT                    10
#define PLL0_CPUMP_PROG_DIG_MSK                     (0x1f<<PLL0_CPUMP_PROG_DIG_SHIFT)
#define PLL0_FASTCH_SEL_MSK                          BIT(15)

//reg803
#define PLL0_FSW_DIG_SHIFT                           0
#define PLL0_FSW_DIG_MSK                            (0x3ff<<PLL0_FSW_DIG_SHIFT)
#define PLL0_KVCO_DIG_SHIFT                          10
#define PLL0_KVCO_DIG_MSK                           (7<<PLL0_KVCO_DIG_SHIFT)
#define PLL0_LO_LDO_BYPASS_MSK                       BIT(13)
#define PLL0_LO_LDO_EN_DIG_MSK                       BIT(14)
#define PLL0_LO_LDO_TEST_DIG_MSK                     BIT(15)

//reg804
#define PLL0_LO_LDO_VREF_PROG_SHIFT                  0
#define PLL0_LO_LDO_VREF_PROG_MSK                   (0xf<<PLL0_LO_LDO_VREF_PROG_SHIFT)
#define PLL0_LPF_C1_PROG_DIG_SHIFT                   4
#define PLL0_LPF_C1_PROG_DIG_MSK                    (0xf<<PLL0_LPF_C1_PROG_DIG_SHIFT)
#define PLL0_LPF_R1_PROG_DIG_SHIFT                   8
#define PLL0_LPF_R1_PROG_DIG_MSK                    (0xf<<PLL0_LPF_R1_PROG_DIG_SHIFT)
#define PLL0_NDIV_LDO_BYPASS_DIG_MSK                 BIT(12)
#define PLL0_NDIV_LDO_EN_DIG_MSK                     BIT(13)
#define PLL0_NDIV_LDO_TEST_DIG_MSK                   BIT(14)
#define PLL0_NDIV_LDO_VREF_PROG_DIG_0_MSK            BIT(15)

//reg805
#define PLL0_NDIV_LDO_VREF_PROG_DIG_1_3_SHIFT        0
#define PLL0_NDIV_LDO_VREF_PROG_DIG_1_3_MSK         (7<<PLL0_NDIV_LDO_VREF_PROG_DIG_1_3_SHIFT)
#define PLL0_NDIV_RESETB_DIG_MSK                     BIT(3)
#define PLL0_PFD_EN_DIG_MSK                          BIT(4)
#define PLL0_PLL_DDC_MODE_MSK                        BIT(5)
#define PLL0_PLL_FRAC_LOW_SHIFT                      6
#define PLL0_PLL_FRAC_LOW_MSK                       (0x3ff<<PLL0_PLL_FRAC_LOW_SHIFT)

//reg806
#define PLL0_PLL_FRAC_HIGH_SHIFT                     0
#define PLL0_PLL_FRAC_HIGH_MSK                      (0x7fff<<PLL0_PLL_FRAC_HIGH_SHIFT)
#define PLL0_PLL_K_INT_0_MSK                         BIT(15)

//reg807
#define PLL0_PLL_K_INT_1_7_SHIFT                     0
#define PLL0_PLL_K_INT_1_7_MSK                      (0x7f<<PLL0_PLL_K_INT_1_7_SHIFT)
#define PLL0_PLL_NDIV_PRES45_EN_MSK                  BIT(7)
#define PLL0_PLL_NDIV_PWE_DIG_MSK                    BIT(8)
#define PLL0_PLL_R2_SHORT_DIG_MSK                    BIT(9)
#define PLL0_PLL_RFTST_CLK_EN_DIG_MSK                BIT(10)
#define PLL0_PLL_SDM_NOISE_EN_MSK                    BIT(11)
#define PLL0_PLL_SDM_NOISE_LEVEL_SHIFT               12
#define PLL0_PLL_SDM_NOISE_LEVEL_MSK                (3<<PLL0_PLL_SDM_NOISE_LEVEL_SHIFT)
#define PLL0_PLL_SPARE_0_1_SHIFT                     14
#define PLL0_PLL_SPARE_0_1_MSK                      (3<<PLL0_PLL_SPARE_0_1_SHIFT)

//reg808
#define PLL0_PLL_SPARE_2_7_SHIFT                     0
#define PLL0_PLL_SPARE_2_7_MSK                      (0x3f<<PLL0_PLL_SPARE_2_7_SHIFT)
#define PLL0_SEL_DNDLY_DIG_SHIFT                     6
#define PLL0_SEL_DNDLY_DIG_MSK                      (0xf<<PLL0_SEL_DNDLY_DIG_SHIFT)
#define PLL0_SEL_UPDLY_DIG_SHIFT                     10
#define PLL0_SEL_UPDLY_DIG_MSK                      (0xf<<PLL0_SEL_UPDLY_DIG_SHIFT)
#define PLL0_VCO_DIV2_EN_DIG_MSK                     BIT(14)
#define PLL0_VCO_LDO_BYPASS_MSK                      BIT(15)

//reg809
#define PLL0_VCO_LDO_SEL_DIG_MSK                     BIT(0)
#define PLL0_VCO_LDO_TST_MSK                         BIT(1)
#define PLL0_VCO_LO_EN_MSK                           BIT(2)
#define PLL0_VCO_SEL_HB_LBB_MSK                      BIT(3)
#define PLL0_VCOLDO_VREF_LDO_SHIFT                   4
#define PLL0_VCOLDO_VREF_LDO_MSK                    (0xf<<PLL0_VCOLDO_VREF_LDO_SHIFT)
#define PLL0_VMID_TST_MSK                            BIT(8)
#define RXBB_BIAS_EN_MSK                             BIT(10)
#define TXFE0_datest_EN_MSK                          BIT(11)
#define RXBB_TIA_FBCTRL_SHIFT                        12
#define RXBB_TIA_FBCTRL_MSK                         (0xf<<RXBB_TIA_FBCTRL_SHIFT)

//reg80a
#define TXFE0_UPCTEST_EN_MSK                         BIT(0)
#define ATB_CHIPOUT_SEL2_MSK                         BIT(1)
#define RXBB_EN_SIGBUF_SHIFT                         5
#define RXBB_EN_SIGBUF_MSK                          (0xf<<RXBB_EN_SIGBUF_SHIFT)
#define PLL_SELNDIV_MSK                              BIT(9)
#define PLL_EN_CAL_MSK                               BIT(10)
#define ATB_CHIPOUT_SEL1_MSK                         BIT(11)
#define ATB_TOP_CTRL_SHIFT                           12
#define ATB_TOP_CTRL_MSK                            (0xf<<ATB_TOP_CTRL_SHIFT)

//reg80b
#define EXTLO_EN_MSK                                 BIT(0)
#define CAL_MSK_CTRL_3_MSK                           BIT(1)
#define CAL_MSK_CTRL_2_MSK                           BIT(2)
#define CAL_MSK_CTRL_1_MSK                           BIT(3)
#define CAL_MSK_CTRL_0_MSK                           BIT(4)

//reg80c
#define POS13_L_MSK                                  BIT(9)
#define RXBB0_BYPASS_ICHANNEL_0_5_SHIFT              10
#define RXBB0_BYPASS_ICHANNEL_0_5_MSK               (0x3f<<RXBB0_BYPASS_ICHANNEL_0_5_SHIFT)

//reg80d
#define RXBB0_BYPASS_ICHANNEL_6_15_SHIFT             0
#define RXBB0_BYPASS_ICHANNEL_6_15_MSK              (0x3ff<<RXBB0_BYPASS_ICHANNEL_6_15_SHIFT)
#define RXBB0_BYPASS_QCHANNEL_0_5_SHIFT              10
#define RXBB0_BYPASS_QCHANNEL_0_5_MSK               (0x3f<<RXBB0_BYPASS_QCHANNEL_0_5_SHIFT)

//reg80e
#define RXBB0_BYPASS_QCHANNEL_6_15_SHIFT             0
#define RXBB0_BYPASS_QCHANNEL_6_15_MSK              (0x3ff<<RXBB0_BYPASS_QCHANNEL_6_15_SHIFT)
#define RXBB0_EN_1V1SHIFTER_3P3V_MSK                 BIT(10)
#define RXBB0_FILT_C1_0_4_SHIFT                      11
#define RXBB0_FILT_C1_0_4_MSK                       (0x1f<<RXBB0_FILT_C1_0_4_SHIFT)

//reg80f
#define RXBB0_FILT_C1_5_MSK                          BIT(0)
#define RXBB0_FILT_R1_SHIFT                          1
#define RXBB0_FILT_R1_MSK                           (0x3f<<RXBB0_FILT_R1_SHIFT)
#define RXBB0_FILT_R2_SHIFT                          7
#define RXBB0_FILT_R2_MSK                           (0x3f<<RXBB0_FILT_R2_SHIFT)
#define RXBB0_PGA_BIAS_ENABLE_MSK                    BIT(13)
#define RXBB0_PGA_BIAS_RES_INPUT_0_1_SHIFT           14
#define RXBB0_PGA_BIAS_RES_INPUT_0_1_MSK            (3<<RXBB0_PGA_BIAS_RES_INPUT_0_1_SHIFT)

//reg810
#define RXBB0_PGA_BIAS_RES_INPUT_2_3_SHIFT           0
#define RXBB0_PGA_BIAS_RES_INPUT_2_3_MSK            (3<<RXBB0_PGA_BIAS_RES_INPUT_2_3_SHIFT)
#define RXBB0_PGA_BIAS_RES_OUTPUT_SHIFT              0
#define RXBB0_PGA_BIAS_RES_OUTPUT_MSK               (0xf<<RXBB0_PGA_BIAS_RES_OUTPUT_SHIFT)
#define RXBB0_PGA_BIASR_BYPASS_MSK                   BIT(6)
#define RXBB0_PGA_INPUT_BIAS_NMOS_MULT_SHIFT         7
#define RXBB0_PGA_INPUT_BIAS_NMOS_MULT_MSK          (3<<RXBB0_PGA_INPUT_BIAS_NMOS_MULT_SHIFT)
#define RXBB0_PGA_INPUT_BIAS_PMOS_MULT_SHIFT         7
#define RXBB0_PGA_INPUT_BIAS_PMOS_MULT_MSK          (3<<RXBB0_PGA_INPUT_BIAS_PMOS_MULT_SHIFT)
#define RXBB0_PGA_MILLER_COMP_SHIFT                  11
#define RXBB0_PGA_MILLER_COMP_MSK                   (0xf<<RXBB0_PGA_MILLER_COMP_SHIFT)
#define RXBB0_PGA_OUTPUT_BIAS_NMOS_MULT_0_MSK        BIT(15)

//reg811
#define RXBB0_PGA_OUTPUT_BIAS_NMOS_MULT_1_MSK        BIT(0)
#define RXBB0_PGA_OUTPUT_BIAS_PMOS_MULT_SHIFT        1
#define RXBB0_PGA_OUTPUT_BIAS_PMOS_MULT_MSK         (3<<RXBB0_PGA_OUTPUT_BIAS_PMOS_MULT_SHIFT)
#define RXBB0_PGA_SPARE_PREBUF_MSK                   BIT(3)
#define RXBB0_RXBB_LDO_BYPASS_1P3_MSK                BIT(4)
#define RXBB0_RXBB_LDO_ENABLE_1P3_MSK                BIT(5)
#define RXBB0_RXBB_LDO_TEST_MSK                      BIT(6)
#define RXBB0_STAGE1_BIAS_ENABLE_MSK                 BIT(7)
#define RXBB0_STAGE1_BIAS_RES_INPUT_SHIFT            8
#define RXBB0_STAGE1_BIAS_RES_INPUT_MSK             (0xf<<RXBB0_STAGE1_BIAS_RES_INPUT_SHIFT)
#define RXBB0_STAGE1_BIAS_RES_OUTPUT_SHIFT           12
#define RXBB0_STAGE1_BIAS_RES_OUTPUT_MSK            (0xf<<RXBB0_STAGE1_BIAS_RES_OUTPUT_SHIFT)

//reg812
#define RXBB0_STAGE1_BIASR_BYPASS_MSK                BIT(0)
#define RXBB0_STAGE1_INPUT_BIAS_NMOS_MULT_SHIFT      1
#define RXBB0_STAGE1_INPUT_BIAS_NMOS_MULT_MSK       (3<<RXBB0_STAGE1_INPUT_BIAS_NMOS_MULT_SHIFT)
#define RXBB0_STAGE1_INPUT_BIAS_PMOS_MULT_SHIFT      3
#define RXBB0_STAGE1_INPUT_BIAS_PMOS_MULT_MSK       (3<<RXBB0_STAGE1_INPUT_BIAS_PMOS_MULT_SHIFT)
#define RXBB0_STAGE1_MILLER_COMP_SHIFT               5
#define RXBB0_STAGE1_MILLER_COMP_MSK                (0xf<<RXBB0_STAGE1_MILLER_COMP_SHIFT)
#define RXBB0_STAGE1_OUTPUT_BIAS_NMOS_MULT_SHIFT     9
#define RXBB0_STAGE1_OUTPUT_BIAS_NMOS_MULT_MSK      (3<<RXBB0_STAGE1_OUTPUT_BIAS_NMOS_MULT_SHIFT)
#define RXBB0_STAGE1_OUTPUT_BIAS_PMOS_MULT_SHIFT     11
#define RXBB0_STAGE1_OUTPUT_BIAS_PMOS_MULT_MSK      (3<<RXBB0_STAGE1_OUTPUT_BIAS_PMOS_MULT_SHIFT)
#define RXBB0_STAGE1_SPARE_PREBUF_SHIFT              13
#define RXBB0_STAGE1_SPARE_PREBUF_MSK               (3<<RXBB0_STAGE1_SPARE_PREBUF_SHIFT)
#define RXBB0_STAGE2_BIAS_ENABLE_MSK                 BIT(15)

//reg813
#define RXBB0_STAGE2_BIAS_RES_INPUT_SHIFT            0
#define RXBB0_STAGE2_BIAS_RES_INPUT_MSK             (0xf<<RXBB0_STAGE2_BIAS_RES_INPUT_SHIFT)
#define RXBB0_STAGE2_BIAS_RES_OUTPUT_SHIFT           0
#define RXBB0_STAGE2_BIAS_RES_OUTPUT_MSK            (0xf<<RXBB0_STAGE2_BIAS_RES_OUTPUT_SHIFT)
#define RXBB0_STAGE2_BIASR_BYPASS_MSK                BIT(8)
#define RXBB0_STAGE2_INPUT_BIAS_NMOS_MULT_SHIFT      9
#define RXBB0_STAGE2_INPUT_BIAS_NMOS_MULT_MSK       (3<<RXBB0_STAGE2_INPUT_BIAS_NMOS_MULT_SHIFT)
#define RXBB0_STAGE2_INPUT_BIAS_PMOS_MULT_SHIFT      11
#define RXBB0_STAGE2_INPUT_BIAS_PMOS_MULT_MSK       (3<<RXBB0_STAGE2_INPUT_BIAS_PMOS_MULT_SHIFT)
#define RXBB0_STAGE2_MILLER_COMP_0_2_SHIFT           13
#define RXBB0_STAGE2_MILLER_COMP_0_2_MSK            (7<<RXBB0_STAGE2_MILLER_COMP_0_2_SHIFT)

//reg814
#define RXBB0_STAGE2_MILLER_COMP_3_MSK               BIT(0)
#define RXBB0_STAGE2_OUTPUT_BIAS_NMOS_MULT_SHIFT     1
#define RXBB0_STAGE2_OUTPUT_BIAS_NMOS_MULT_MSK      (3<<RXBB0_STAGE2_OUTPUT_BIAS_NMOS_MULT_SHIFT)
#define RXBB0_STAGE2_OUTPUT_BIAS_PMOS_MULT_SHIFT     1
#define RXBB0_STAGE2_OUTPUT_BIAS_PMOS_MULT_MSK      (3<<RXBB0_STAGE2_OUTPUT_BIAS_PMOS_MULT_SHIFT)
#define RXBB0_STAGE2_SPARE_PREBUF_SHIFT              5
#define RXBB0_STAGE2_SPARE_PREBUF_MSK               (3<<RXBB0_STAGE2_SPARE_PREBUF_SHIFT)
#define RXBB0_TIA_BIAS_ENABLE_MSK                    BIT(7)
#define RXBB0_TIA_BIAS_RES_INPUT_SHIFT               8
#define RXBB0_TIA_BIAS_RES_INPUT_MSK                (0xf<<RXBB0_TIA_BIAS_RES_INPUT_SHIFT)
#define RXBB0_TIA_BIAS_RES_OUTPUT_SHIFT              12
#define RXBB0_TIA_BIAS_RES_OUTPUT_MSK               (0xf<<RXBB0_TIA_BIAS_RES_OUTPUT_SHIFT)

//reg815
#define RXBB0_TIA_BIASR_BYPASS_MSK                   BIT(0)
#define RXBB0_TIA_C1_SHIFT                           1
#define RXBB0_TIA_C1_MSK                            (0x3f<<RXBB0_TIA_C1_SHIFT)
#define RXBB0_TIA_CMFB_RES_LOW_MSK                   BIT(7)
#define RXBB0_TIA_INPUT_BIAS_NMOS_MULT_SHIFT         8
#define RXBB0_TIA_INPUT_BIAS_NMOS_MULT_MSK          (3<<RXBB0_TIA_INPUT_BIAS_NMOS_MULT_SHIFT)
#define RXBB0_TIA_INPUT_BIAS_PMOS_MULT_SHIFT         10
#define RXBB0_TIA_INPUT_BIAS_PMOS_MULT_MSK          (3<<RXBB0_TIA_INPUT_BIAS_NMOS_MULT_SHIFT)
#define RXBB0_TIA_MILLER_COMP_SHIFT                  12
#define RXBB0_TIA_MILLER_COMP_MSK                   (0xf<<RXBB0_TIA_MILLER_COMP_SHIFT)

//reg816
#define RXBB0_TIA_OUTPUT_BIAS_NMOS_MULT_SHIFT        0
#define RXBB0_TIA_OUTPUT_BIAS_NMOS_MULT_MSK         (3<<RXBB0_TIA_OUTPUT_BIAS_NMOS_MULT_SHIFT)
#define RXBB0_TIA_OUTPUT_BIAS_PMOS_MULT_SHIFT        2
#define RXBB0_TIA_OUTPUT_BIAS_PMOS_MULT_MSK         (3<<RXBB0_TIA_OUTPUT_BIAS_PMOS_MULT_SHIFT)
#define RXBB0_TIA_SPARE_PREBUF_MSK                   BIT(7)
#define RXBB0_VREF_RXBB_LDO_1P3_SHIFT                8
#define RXBB0_VREF_RXBB_LDO_1P3_MSK                 (0xf<<RXBB0_VREF_RXBB_LDO_1P3_SHIFT)
#define RXBB1_EN_LVLSHIFTER_3P3V_MSK                 BIT(12)
#define SEL_TX_EXT_IN_PM_Q_MSK                       BIT(15)

//reg817
#define TXBB_DCOC_ICTRL_SHIFT                        0
#define TXBB_DCOC_ICTRL_MSK                         (3<<TXBB_DCOC_ICTRL_SHIFT)
#define RXFE_ATB_EN_MSK                              BIT(3)
#define HOSC_EN_OVERRIDE_MSK                         BIT(6)
#define ATB_EN_2_MSK                                 BIT(7)
#define RXFE0_GM_BIAS_NMOS_MULT_SHIFT                12
#define RXFE0_GM_BIAS_NMOS_MULT_MSK                 (3<<RXFE0_GM_BIAS_NMOS_MULT_SHIFT)
#define RXFE0_GM_BIAS_PMOS_MULT_SHIFT                14
#define RXFE0_GM_BIAS_PMOS_MULT_MSK                 (3<<RXFE0_GM_BIAS_PMOS_MULT_SHIFT)

//reg818
#define RXFE0_GM_BIASR_BYPASS_MSK                    BIT(0)
#define RXFE0_GM_LDO_BYPASS_1P3_MSK                  BIT(1)
#define RXFE0_GM_LDO_ENABLE_1P3_MSK                  BIT(2) //???
#define ATB_TX_DCOC_CTRL_MSK                         BIT(2)
#define EN_TXBB_DCOC_GAIN_MSK                        BIT(3)
#define RXFE0_GM_LDO_TEST_MSK                        BIT(3)
#define RXFE0_GM_SPARE_SHIFT                         4
#define RXFE0_GM_SPARE_MSK                          (7<<RXFE0_GM_SPARE_SHIFT)
#define RXFE0_LNA_AUX_INPUT_RES_SHIFT                7
#define RXFE0_LNA_AUX_INPUT_RES_MSK                 (7<<RXFE0_LNA_AUX_INPUT_RES_SHIFT)
#define RXFE0_LNA_AUX_PATH_EN                        BIT(10)
#define RXFE0_LNA_BIAS_NMOS_MULT_SHIFT               11
#define RXFE0_LNA_BIAS_NMOS_MULT_MSK                (0xf<<RXFE0_LNA_BIAS_NMOS_MULT_SHIFT)
#define RXFE0_LNA_BIASR_BYPASS_MSK                   BIT(15)

//reg819
#define RXFE0_LNA_CAP_ATTEN_2P5V_SHIFT               0
#define RXFE0_LNA_CAP_ATTEN_2P5V_MSK                (3<<RXFE0_LNA_CAP_ATTEN_2P5V_SHIFT)
#define RXFE0_LNA_CAPBIT_SHIFT                       2
#define RXFE0_LNA_CAPBIT_MSK                        (0xf<<RXFE0_LNA_CAPBIT_SHIFT)
#define RXFE0_LNA_LDO_BYPASS_1P3_MSK                 BIT(6)
#define RXFE0_LNA_LDO_ENABLE_1P3_MSK                 BIT(7)
#define RXFE0_LNA_LDO_TEST_MSK                       BIT(8)
#define RXFE0_LNA_LOAD_RES_SHIFT                     9
#define RXFE0_LNA_LOAD_RES_MSK                      (0xf<<RXFE0_LNA_LOAD_RES_SHIFT)
#define RXFE0_MIXER_CONTROL_0_2_SHIFT                13
#define RXFE0_MIXER_CONTROL_0_2_MSK                 (7<<RXFE0_MIXER_CONTROL_0_2_SHIFT)

//reg81a
#define RXFE0_MIXER_CONTROL_3_10_SHIFT               0
#define RXFE0_MIXER_CONTROL_3_10_MSK                (0xff<<RXFE0_MIXER_CONTROL_3_10_SHIFT)
#define RXFE0_VREF_GM_LDO_1P3_SHIFT                  8
#define RXFE0_VREF_GM_LDO_1P3_MSK                   (0xf<<RXFE0_VREF_GM_LDO_1P3_SHIFT)
#define RXFE0_VREF_LNA_LDO_1P3_SHIFT                 12
#define RXFE0_VREF_LNA_LDO_1P3_MSK                  (0xf<<RXFE0_VREF_LNA_LDO_1P3_SHIFT)

//reg81b
#define TXBB_CTRL_IIN_0_MSK                          BIT(10)
#define XTAL_PPM_LEFT_0_1_SHIFT                      11
#define XTAL_PPM_LEFT_0_1_MSK                       (3<<XTAL_PPM_LEFT_0_1_SHIFT)
#define TXBB_CTRL_IIN_1_3_SHIFT                      13
#define TXBB_CTRL_IIN_1_3_MSK                       (7<<TXBB_CTRL_IIN_1_3_SHIFT)

//reg81c
#define TXBB_CTRL_IIN_4_6_SHIFT                      0
#define TXBB_CTRL_IIN_4_6_MSK                       (7<<TXBB_CTRL_IIN_4_6_SHIFT)
#define SEL_TX_EXT_IN_PM_I_MSK                       BIT(3)
#define TXBB_CTRL_IIN_7_MSK                          BIT(4)
#define XTAL_PPM_LEFT_2_4_SHIFT                      5
#define XTAL_PPM_LEFT_2_4_MSK                       (7<<XTAL_PPM_LEFT_2_4_SHIFT)
#define XTAL_PPM_LEFT_9_MSK                          BIT(8)
#define XTAL_PPM_RIGHT_0_6_SHIFT                     9
#define XTAL_PPM_RIGHT_0_6_MSK                      (0x7f<<XTAL_PPM_RIGHT_0_6_SHIFT)

//reg81d
#define XTAL_PPM_RIGHT_7_9_SHIFT                     0
#define XTAL_PPM_RIGHT_7_9_MSK                      (7<<XTAL_PPM_RIGHT_7_9_SHIFT)
#define XTAL_PPM_LEFT_5_8_SHIFT                      3
#define XTAL_PPM_LEFT_5_8_MSK                       (0xf<<XTAL_PPM_LEFT_5_8_SHIFT)
#define RXLOLB_BUF_EN_MSK                            BIT(9)
#define RXLOLB_IFLO_DIV32EN_MSK                      BIT(10)
#define TXBB0_DAC_EN_MSK                             BIT(11)
#define TXBB0_MODE_MSK                               BIT(12)
#define TXBB0_PD_MSK                                 BIT(13)
#define TXBB0_REALP_CCTR_0_1_SHIFT                   14
#define TXBB0_REALP_CCTR_0_1_MSK                    (3<<TXBB0_REALP_CCTR_0_1_SHIFT)

//reg81e
#define TXBB0_REALP_CCTR_2_3_SHIFT                   0
#define TXBB0_REALP_CCTR_2_3_MSK                    (3<<TXBB0_REALP_CCTR_2_3_SHIFT)
#define TXBB0_TSTFILT_SEL_MSK                        BIT(2)
#define TXBB0_VRBWSEL_SHIFT                          3
#define TXBB0_VRBWSEL_MSK                           (0xf<<TXBB0_VRBWSEL_SHIFT)
#define TXFE0_EN_LVLSHIFTER_3P3V_MSK                 BIT(7)
#define TXFE0_PA_AUX_PATH_EN_MSK                     BIT(8)
#define TXFE0_PA_BIAS_NMOS_MULT_SHIFT                9
#define TXFE0_PA_BIAS_NMOS_MULT_MSK                 (3<<TXFE0_PA_BIAS_NMOS_MULT_SHIFT)
#define TXFE0_PA_BIAS_PMOS_MULT_SHIFT                11
#define TXFE0_PA_BIAS_PMOS_MULT_MSK                 (3<<TXFE0_PA_BIAS_PMOS_MULT_SHIFT)
#define TXFE0_PA_BIAS_RES_0_2_SHIFT                  13
#define TXFE0_PA_BIAS_RES_0_2_MSK                   (7<<TXFE0_PA_BIAS_RES_0_2_SHIFT)

//reg81f
#define TXFE0_PA_BIAS_RES_3_MSK                      BIT(0)
#define TXFE0_PA_BIASR_BYPASS_MSK                    BIT(1)
#define TXFE0_PA_CASC_BIAS_SHIFT                     2
#define TXFE0_PA_CASC_BIAS_MSK                      (0xfff<<TXFE0_PA_CASC_BIAS_SHIFT)
#define TXFE0_PA_SPARE_0_1_SHIFT                     14
#define TXFE0_PA_SPARE_0_1_MSK                      (3<<TXFE0_PA_SPARE_0_1_SHIFT)

//reg820
#define TXFE0_PA_SPARE_2_MSK                         BIT(0)
#define TXFE0_PABIAS_LDO_BYPASS_LP3_MSK              BIT(1)
#define TXFE0_PABIAS_LDO_ENABLE_LP3_MSK              BIT(2)
#define TXFE0_PABIAS_LDO_TEST_MSK                    BIT(3)
#define TXFE0_UPC_CAPBIT_SHIFT                       4
#define TXFE0_UPC_CAPBIT_MSK                        (0xf<<TXFE0_UPC_CAPBIT_SHIFT)
#define TXFE0_UPC_CASC_BIAS_SHIFT                    8
#define TXFE0_UPC_CASC_BIAS_MSK                     (0x3f<<TXFE0_UPC_CASC_BIAS_SHIFT)
#define TXFE0_UPC_LDO_BYPASS_LP3_MSK                 BIT(14)
#define TXFE0_UPC_LDO_ENABLE_LP3_MSK                 BIT(15)

//reg821
#define TXFE0_UPC_LDO_TEST_MSK                       BIT(0)
#define TXFE0_VREF_PABIAS_LDO_LP3_SHIFT              1
#define TXFE0_VREF_PABIAS_LDO_LP3_MSK               (0xf<<TXFE0_VREF_PABIAS_LDO_LP3_SHIFT)
#define TXFE0_VREF_UPC_LDO_LP3_SHIFT                 5
#define TXFE0_VREF_UPC_LDO_LP3_MSK                  (0xf<<TXFE0_VREF_UPC_LDO_LP3_SHIFT)
#define TXFE1_EN_LVLSHIFTER_3P3V_MSK                 BIT(9)

//reg823
#define TXLOLB_BUF_EN_MSK                            BIT(2)
#define XTAL0_REFCLK2X_EN_MSK                        BIT(3)
#define XTAL0_XTAL_EN_MSK                            BIT(4)
#define XTAL0_XTAL_LDO_BYPASS_MSK                    BIT(5)
#define XTAL0_XTAL_LDO_EN_MSK                        BIT(6)
#define XTAL0_XTAL_LDO_TEST                          BIT(7)
#define XTAL0_XTAL_LDO_VREF_LDO_SHIFT                8
#define XTAL0_XTAL_LDO_VREF_LDO_MSK                 (0xf<<XTAL0_XTAL_LDO_VREF_LDO_SHIFT)
#define XTAL0_XTALBUF_EN_MSK                         BIT(12)

//reg824
#define RXFE0_LNA_MAIN_PATH_EN_MSK                   BIT(0)
#define PLL0_PLL_EN_LOBUFDIG_SHIFT                   2
#define PLL0_PLL_EN_LOBUFDIG_MSK                    (3<<PLL0_PLL_EN_LOBUFDIG_SHIFT)
#define RXIF0_EN_1V1SHIFTER_3P3V_MSK                 BIT(9)
#define LPF_VMID_EN_MSK                              BIT(11)
#define TXFE0_UPC_CM_ADJUST_SHIFT                    12
#define TXFE0_UPC_CM_ADJUST_MSK                     (3<<TXFE0_UPC_CM_ADJUST_SHIFT)
#define TXFE0_ATB_CTRL_0_1_SHIFT                     14
#define TXFE0_ATB_CTRL_0_1_MSK                      (3<<TXFE0_ATB_CTRL_0_1_SHIFT)

//reg825
#define TXFE0_ATB_CTRL_2_3_SHIFT                     0
#define TXFE0_ATB_CTRL_2_3_MSK                      (3<<TXFE0_ATB_CTRL_2_3_SHIFT)
#define TXFE0_DA_BIAS_RES_SHIFT                      2
#define TXFE0_DA_BIAS_RES_MSK                       (0xf<<TXFE0_DA_BIAS_RES_SHIFT)
#define TXFE0_DA_BIASR_BYPASS_MSK                    BIT(6)
#define RXFE_ATB_CTRL_SHIFT                          7
#define RXFE_ATB_CTRL_MSK                           (0xf<<RXFE_ATB_CTRL_SHIFT)
#define LPF_VMID_SEL_SHIFT                           11
#define LPF_VMID_SEL_MSK                            (0xf<<LPF_VMID_SEL_SHIFT)
#define RXBB0_PGA_INPUT_RES_16_MSK                   BIT(15)

//reg826
#define TXFE0_DA_LDO_BYPASS_1P3_MSK                  BIT(0)
#define SEL_EXT_IN_PM_Q_MSK                          BIT(3)
#define SEL_EXT_IN_PM_I_MSK                          BIT(4)
#define TXBB_GAIN_DOUBLER_MSK                        BIT(5)
#define TXFE0_DA_LDO_ENABLE_LP3_MSK                  BIT(6)
#define TXFE0_DA_LDO_TEST_MSK                        BIT(7)
#define TXFE0_DA_CAPBIT_SHIFT                        8
#define TXFE0_DA_CAPBIT_MSK                         (0xf<<TXFE0_DA_CAPBIT_SHIFT)
#define TXFE0_DA_BIAS_NMOS_MULT_SHIFT                12
#define TXFE0_DA_BIAS_NMOS_MULT_MSK                 (0xf<<TXFE0_DA_BIAS_NMOS_MULT_SHIFT)

//reg827
#define RXBB0_FILT_C2_SHIFT                          0
#define RXBB0_FILT_C2_MSK                           (0x3f<<RXBB0_FILT_C2_SHIFT)
#define RXBB_DCOC_ICTRL_SHIFT                        6
#define RXBB_DCOC_ICTRL_MSK                         (7<<RXBB_DCOC_ICTRL_SHIFT)
#define TXFE0_ATB_EN_MSK                             BIT(9)
#define TXFE0_VREF_DA_LDO_1P3_SHIFT                  10
#define TXFE0_VREF_DA_LDO_1P3_MSK                   (0xf<<TXFE0_VREF_DA_LDO_1P3_SHIFT)

//reg828
#define RXIF1_EN_LVLSHIFTER_3P3V_MSK                 BIT(1)
#define XTAL0_BBCLK_SEL2X_MSK                        BIT(15)

//reg829
#define IREF0_IREF_SEL_25UA_8_MSK                    BIT(0)
#define PLL0_PLL1_SDM_RSTN_MSK                       BIT(1)
#define PLL0_SDMCLK_EDGE_SEL_MSK                     BIT(2)
#define RXBB0_DCOC_RANGE_I_SHIFT                     5
#define RXBB0_DCOC_RANGE_I_MSK                      (3<<RXBB0_DCOC_RANGE_I_SHIFT)
#define RXBB0_DCOC_RANGE_Q_SHIFT                     7
#define RXBB0_DCOC_RANGE_Q_MSK                      (3<<RXBB0_DCOC_RANGE_Q_SHIFT)
#define RXBB0_DCOC_RANGE0P5X_I_MSK                   BIT(9)
#define RXBB0_DCOC_RANGE0P5X_Q_MSK                   BIT(10)

//reg82a
#define BG_TEST_EN_MSK                               BIT(6)
#define RXLOLB_EN_RXLO_I_IF_MSK                      BIT(15)

//reg82b
#define RXLOLB_EN_RXLO_I_RF_MSK                      BIT(0)
#define RXLOLB_EN_RXLO_Q_IF_MSK                      BIT(1)
#define RXLOLB_EN_RXLO_Q_RF_MSK                      BIT(2
#define TXBB0_BYPASS_11_MSK                          BIT(3)
#define TXBB0_EN_LDO_MSK                             BIT(4)
#define TXBB0_TEST_11_MSK                            BIT(6)
#define TXBB0_VREF_LDO_11_SHIFT                      7
#define TXBB0_VREF_LDO_11_MSK                       (0xf<<TXBB0_VREF_LDO_11_SHIFT)

//reg82c
#define TXLOHB_LO_LDO_TEST_MSK                       BIT(3)
#define TXLOHB_LO_LDO_VREF_SHIFT                     4
#define TXLOHB_LO_LDO_VREF_MSK                      (0xf<<TXLOHB_LO_LDO_VREF_SHIFT)
#define RXBB0_FILT_R3_0_4_SHIFT                      11
#define RXBB0_FILT_R3_0_4_MSK                       (0x1f<<RXBB0_FILT_R3_0_4_SHIFT)

//reg82d
#define RXBB0_FILT_R3_5_MSK                          BIT(0)
#define RXBB0_FILT_R4_SHIFT                          1
#define RXBB0_FILT_R4_MSK                           (0x3f<<RXBB0_FILT_R4_SHIFT)


//reg82e
#define REG_RXBB0_DCOC_DAC_HIGH                      0x82E
#define RXBB0_DCOC_DAC_I_5_9_SHIFT                   3
#define RXBB0_DCOC_DAC_I_5_9_MSK                    (0x1f<<RXBB0_DCOC_DAC_I_5_9_SHIFT)
#define RXBB0_DCOC_DAC_Q_5_9_SHIFT                   8
#define RXBB0_DCOC_DAC_Q_5_9_MSK                    (0x1f<<RXBB0_DCOC_DAC_Q_5_9_SHIFT)

//reg82f
#define REF_PLL_K_INT_RX_MODE                        0x82F
#define PLL_K_INT_RX_MODE_0_8_SHIFT                  7
#define PLL_K_INT_RX_MODE_0_8_MSK                   (0x1ff<<PLL_K_INT_RX_MODE_0_8_SHIFT)

//reg830
#define REF_PLL_K_FRAC_RX_MODE_HIGH                  0x830
#define PLL_K_FRAC_RX_MODE_9_24_SHIFT                0
#define PLL_K_FRAC_RX_MODE_9_24_MSK                 (0xffff<<PLL_K_FRAC_RX_MODE_9_24_SHIFT)

//reg831
#define PLL_K_FRAC_RX_MODE_0_8_SHIFT                 0
#define PLL_K_FRAC_RX_MODE_0_8_MSK                  (0x1ff<<PLL_K_FRAC_RX_MODE_0_8_SHIFT)
#define PLL0_PLL_INT_MODE_MSK                        BIT(9)
#define PLL0_PLL_K_INT_8_MSK                         BIT(11)
#define TRNG_ENB_MSK                                 BIT(13)
#define TXLOLB_TXLO_PDET_EN_MSK                      BIT(14)
#define TXLOLB_NOTAIL_MSK                            BIT(15)

//reg834
#define REG_ATB_SEL_LOW                              0x834
#define ATB_SEL_0_15_SHIFT                           0
#define ATB_SEL_0_15_MSK                            (0xffff<<ATB_SEL_0_15_SHIFT)

//reg835
#define ATB_SEL_16_23_SHIFT                          0
#define ATB_SEL_16_23_MSK                           (0xff<<ATB_SEL_16_23_SHIFT)
#define TXLOLB_ATB_SEL_SHIFT                         8
#define TXLOLB_ATB_SEL_MSK                          (3<<TXLOLB_ATB_SEL_SHIFT)
#define TXLOLB_LO_BANDSEL_SHIFT                      10
#define TXLOLB_LO_BANDSEL_MSK                       (0xf<<TXLOLB_LO_BANDSEL_SHIFT)
#define TXLOLB_LO_LDO_BYPASS_MSK                     BIT(14)
#define TXLOLB_LO_LDO_EN_MSK                         BIT(15)

//reg836
#define REG_BIAS_LOW                                 0x836
#define BIAS_LOW_SHIFT                               0
#define BIAS_LOW_MSK                                (0xffff<<BIAS_LOW_SHIFT)

//reg837
#define EXTLOMUX_SHIFT                               6
#define EXTLOMUX_MSK                                (7<<EXTLOMUX_SHIFT)
#define ITE_IM2_EN_SHIFT                             9
#define ITE_IM2_EN_MSK                              (3<<ITE_IM2_EN_SHIFT)

//reg838
#define REG_IM2_I_REGVAL                             0x838

//reg839
#define REG_IM2_Q_REGVAL                             0x839

//reg840
#define RXBB0_PGA_ENABLE_AUX_I_MSK                   BIT(0)
#define RXBB0_PGA_ENABLE_AUX_Q_MSK                   BIT(1)
#define RXBB0_PGA_ENABLE_I_MSK                       BIT(2)
#define RXBB0_PGA_ENABLE_Q_MSK                       BIT(3)
#define RXBB0_STAGE1_ENABLE_I_MSK                    BIT(4)
#define RXBB0_STAGE1_ENABLE_Q_MSK                    BIT(5)
#define RXBB0_STAGE2_ENABLE_I_MSK                    BIT(6)
#define RXBB0_STAGE2_ENABLE_Q_MSK                    BIT(7)
#define RXBB0_TIA_ENABLE_I_MSK                       BIT(8)
#define RXBB0_TIA_ENABLE_Q_MSK                       BIT(9)
#define RXBB1_PGA_ENABLE_AUX_I_MSK                   BIT(10)
#define RXBB1_PGA_ENABLE_AUX_Q_MSK                   BIT(11)
#define RXBB1_PGA_ENABLE_I_MSK                       BIT(12)
#define RXBB1_PGA_ENABLE_Q_MSK                       BIT(13)
#define RXBB1_STAGE1_ENABLE_I_MSK                    BIT(14)
#define RXBB1_STAGE1_ENABLE_Q_MSK                    BIT(15)

//reg841
#define RXBB1_STAGE2_ENABLE_I_MSK                    BIT(0)
#define RXBB1_STAGE2_ENABLE_Q_MSK                    BIT(1)
#define RXBB1_TIA_ENABLE_I_MSK                       BIT(2)
#define RXBB1_TIA_ENABLE_Q_MSK                       BIT(3)
#define RXFE0_GM_ENABLE_MSK                          BIT(4)
#define RXFE0_LNA_ENABLE_MSK                         BIT(5)
#define RXFE0_MIXER_ENABLE_I_MSK                     BIT(6)
#define RXFE0_MIXER_ENABLE_Q_MSK                     BIT(7)
#define RXFE1_GM_ENABLE_MSK                          BIT(8)
#define RXFE1_LNA_ENABLE_MSK                         BIT(9)
#define RXFE1_MIXER_ENABLE_I_MSK                     BIT(10)
#define RXFE1_MIXER_ENABLE_Q_MSK                     BIT(11)
#define RXFE2_GM_ENABLE_MSK                          BIT(12)
#define RXFE2_LNA_ENABLE_MSK                         BIT(13)
#define RXIF0_MIXER_ENABLE_I_MSK                     BIT(14)
#define RXIF0_MIXER_ENABLE_Q_MSK                     BIT(15)

//reg844

#define TXFE0_PA_ENABLE_MSK                          BIT(0)
#define TXFE0_PA_MAIN_PATH_EN_MSK                    BIT(1)
#define TXFE0_UPC_ENABLE_MSK                         BIT(2)
#define TXFE0_DA_PATH_EN_MSK                         BIT(6)


#define I_PATH 0
#define Q_PATH 1

#define AHRF_1GV1_UNUSE_FUNC

struct ahrf_1gv1 {
    struct rf_device dev;
    struct rfspi_device *rfspi_dev;
    struct dbgpath_device *dbgpath_dev;
    struct tdma_device *tdma_dev;
    uint32 opened;
};


/** @defgroup Exported_Functions
  * @{
  */

//uint16 abs_amp(int16 val);
//void lo_debug_control(uint8 onoff);
//void lo_freq_config(uint16 lo_fsw_value, uint16 pll_k_value);
//void lo_onoff_control(uint8 onoff);
//void lo_power_control(uint8 onoff);
//void pll_vtune_output_enable(void);
//void pll_vtune_output_disable(void);
//
//void tx_dcoc_config(uint16 i_target_value, uint16 q_target_value, uint8 iq_ref_current);
//void tx_dcoc_search(uint8 iq_ref_current);
//void tx_lo_buf_control(uint8 onoff);
//void tx_iq_switch_reset(void);
//
//void rx_dcoc_calc(void);
//void rx_dcoc_config_en(void);
//void rx_dcoc_i_coarse_config(uint16 reg_val);
//void rx_dcoc_i_fine_config(uint16 reg_val);
//void rx_dcoc_q_coarse_config(uint16 reg_val);
//void rx_dcoc_q_fine_config(uint16 reg_val);
//void rx_dcoc_i_cur_ref_config(uint16 reg_val);
//void rx_dcoc_q_cur_ref_config(uint16 reg_val);
//void rx_dcoc_config(uint16 i_target_value, uint16 q_target_value);
//uint16 rx_dcoc_search(void);
//int16 rx_dcoc_search_cur_ref_fixed(void);
//int16 rx_dcoc_fine_tune(void);
//void rx_dcoc_tune_copy(uint8 entry_src, uint8 entry_dst);
//void rx_dcoc_fine_tune_copy(uint8 entry_dst);
//void rx_max_bw_config(void);
//void rx_bw_config(uint8 rx_filter_c1, uint8 rx_filter_c2, uint8 rx_filter_r1, uint8 rx_filter_r2, uint8 rx_filter_r3, uint8 rx_filter_r4);
//void rx_bw_flatness_config(uint8 rx_filter_r1, uint8 rx_filter_r2);
//void rx_lna_main_config(uint8 lna_gain_value);
//void rx_lna_aux_config(uint8 lna_gain_value);
//void rx_lna_bias_config(uint8 lna_bias);
//void rx_gm_gain_config(uint8 gm_gain);
//void rx_gm_bias_config(uint8 gm_bias);
//void rx_tia_gain_config(uint8 tia_gain_value);
//void rx_tia_out_config(uint8 tia_out_value);
//void rx_pga_gain_config(uint32 pga_gain);
//void rx_pga_fb_config(uint8 pga_fb_value);
//void rx_gain_table0_config(uint8 gain_entry);
//void rx_gain_table_config(uint8 table_idx, uint16 *gain_table);
//void rf_gain_table_config2(void);
//void rx_low_gain_config(void);
//void rx_middle_gain_config(void);
//void rx_gain_override(uint8 idx);
//void rx_lo_buf_control(uint8 onoff);
//void rx_iq_switch_reset(void);
//
//int32 rfip_1gv1_init(void);
//void agc_config(void);
//void agc_config2(void);

int32 ahrf_1gv1_attach(uint32 dev_id, struct ahrf_1gv1 *rfip);

#ifdef __cplusplus
}
#endif

#endif //__RFIP_DRV_H__
