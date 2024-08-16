
// @file    hgrf_s1gv3.h
// @author  wangying
// @brief   This file contains all the tx4002 RFIP driver definitions.
// Revision History
// V1.0.0  07-20-2019  First Release
// V1.0.1  07-26-2019  add tdma2_dev
// V1.0.2  09-26-2019  updated rf operate function


#ifndef __HGRF_S1GV3_H__
#define __HGRF_S1GV3_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup RFIP_DRV_Exported_Constants
  * @{
  */

//RFREG
#define RFREG_BASE_ADDR                              0
#define RFREG_GROUP_OFFSET                           0x40
#define RFREG_GROUP_CNT                              4
#define RFREG_REG_CNT                                34
#define RFREG_OVERRIDE_REG_BASE_ADDR                 0x100
#define RFREG_REFLECT_BASE_ADDR                      0x900

#define RFREG0_LO_BIAS_EN_SHIFT                      0
#define RFREG0_LO_BIAS_EN_MSK                        BIT(0)
#define RFREG0_LO_BIAS_SEL_SHIFT                     1
#define RFREG0_LO_BIAS_SEL_MSK                       BIT(1)
#define RFREG0_LO_DIV2_ISEL_SHIFT                    2
#define RFREG0_LO_DIV2_ISEL_MSK                     (3<<RFREG0_LO_DIV2_ISEL_SHIFT)
#define RFREG0_LO_EXT_EN_SHIFT                       4
#define RFREG0_LO_EXT_EN_MSK                         BIT(4)
#define RFREG0_LO_MODE_SHIFT                         5
#define RFREG0_LO_MODE_MSK                           BIT(5)
#define RFREG0_LO1_LO2RX1_EN_SHIFT                   6
#define RFREG0_LO1_LO2RX1_EN_MSK                     BIT(6)
#define RFREG0_LO1_LO2RX2_EN_SHIFT                   7
#define RFREG0_LO1_LO2RX2_EN_MSK                     BIT(7)
#define RFREG0_LO1_LO2TX1_EN_SHIFT                   8
#define RFREG0_LO1_LO2TX1_EN_MSK                     BIT(8)

#define RFREG1_LO1_ACC_LECEL_SHIFT                   0
#define RFREG1_LO1_ACC_LECEL_MSK                    (3<<RFREG1_LO1_ACC_LECEL_SHIFT)
#define RFREG1_LO1_AFC_EN_SHIFT                      2
#define RFREG1_LO1_AFC_EN_MSK                        BIT(2)
#define RFREG1_LO1_ATE_EN_SHIFT                      3
#define RFREG1_LO1_ATE_EN_MSK                        BIT(3)
#define RFREG1_LO1_ATE_SEL_SHIFT                     4
#define RFREG1_LO1_ATE_SEL_MSK                      (7<<RFREG1_LO1_ATE_SEL_SHIFT)
#define RFREG1_LO1_CP_EN_SHIFT                       7
#define RFREG1_LO1_CP_EN_MSK                         BIT(7)
#define RFREG1_LO1_D2S_IBS_SHIFT                     8
#define RFREG1_LO1_D2S_IBS_MSK                      (3<<RFREG1_LO1_D2S_IBS_SHIFT)
#define RFREG1_LO1_D50_CAL_EN_SHIFT                  10
#define RFREG1_LO1_D50_CAL_EN_MSK                    BIT(10)
#define RFREG1_LO1_D50_CLK_IN_SHIFT                  11
#define RFREG1_LO1_D50_CLK_IN_MSK                    BIT(11)
#define RFREG1_LO1_D50_GSW_SHIFT                     12
#define RFREG1_LO1_D50_GSW_MSK                       BIT(12)
#define RFREG1_LO1_DIV2_EN_SHIFT                     13
#define RFREG1_LO1_DIV2_EN_MSK                       BIT(13)

#define RFREG2_LO1_DIV2_VSEL_SHIFT                   0
#define RFREG2_LO1_DIV2_VSEL_MSK                    (7<<RFREG2_LO1_DIV2_VSEL_SHIFT)
#define RFREG2_LO1_DSM_EN_SHIFT                      3
#define RFREG2_LO1_DSM_EN_MSK                        BIT(3)
#define RFREG2_LO1_DTE1_EN_SHIFT                     4
#define RFREG2_LO1_DTE1_EN_MSK                       BIT(4)
#define RFREG2_LO1_DTE2_EN_SHIFT                     5
#define RFREG2_LO1_DTE2_EN_MSK                       BIT(5)
#define RFREG2_LO1_DTES_SHIFT                        6
#define RFREG2_LO1_DTES_MSK                         (3<<RFREG2_LO1_DTES_SHIFT)

#define RFREG3_LO1_ICP_HIGH_SHIFT                    0
#define RFREG3_LO1_ICP_HIGH_MSK                     (0xff<<RFREG3_LO1_ICP_HIGH_SHIFT)
#define RFREG3_LO1_ICP_NORMAL_SHIFT                  8
#define RFREG3_LO1_ICP_NORMAL_MSK                   (0xff<<RFREG3_LO1_ICP_NORMAL_SHIFT)

#define RFREG4_LO1_IOC_EN_SHIFT                      0
#define RFREG4_LO1_IOC_EN_MSK                        BIT(0)
#define RFREG4_LO1_LD_EN_SHIFT                       1
#define RFREG4_LO1_LD_EN_MSK                         BIT(1)
#define RFREG4_LO1_LDO_EN_SHIFT                      2
#define RFREG4_LO1_LDO_EN_MSK                        BIT(2)
#define RFREG4_LO1_LPF_C1_SHIFT                      3
#define RFREG4_LO1_LPF_C1_MSK                       (7<<RFREG4_LO1_LPF_C1_SHIFT)
#define RFREG4_LO1_LPF_C2_SHIFT                      6
#define RFREG4_LO1_LPF_C2_MSK                       (7<<RFREG4_LO1_LPF_C2_SHIFT)
#define RFREG4_LO1_LPF_R1_SHIFT                      9
#define RFREG4_LO1_LPF_R1_MSK                       (7<<RFREG4_LO1_LPF_R1_SHIFT)
#define RFREG4_LO1_MASH_SEL_SHIFT                    12
#define RFREG4_LO1_MASH_SEL_MSK                      BIT(12)
#define RFREG4_LO1_MSB_MORE_CNT_SHIFT                13
#define RFREG4_LO1_MSB_MORE_CNT_MSK                  BIT(13)
#define RFREG4_LO1_NMDSM_EN_SHIFT                    14
#define RFREG4_LO1_NMDSM_EN_MSK                      BIT(14)
#define RFREG4_LO1_NOISE_EN_SHIFT                    15
#define RFREG4_LO1_NOISE_EN_MSK                      BIT(15)

#define RFREG5_LO1_NOISE_WIDTH_SHIFT                 0
#define RFREG5_LO1_NOISE_WIDTH_MSK                  (7<<RFREG5_LO1_NOISE_WIDTH_SHIFT)
#define RFREG5_LO1_PFD_EN_SHIFT                      3
#define RFREG5_LO1_PFD_EN_MSK                        BIT(3)
#define RFREG5_LO1_QUANT_MODE_SHIFT                  4
#define RFREG5_LO1_QUANT_MODE_MSK                    BIT(4)
#define RFREG5_LO1_RECALC_SEL_SHFIT                  5
#define RFREG5_LO1_RECALC_SEL_MSK                   (3<<RFREG5_LO1_RECALC_SEL_SHFIT)
#define RFREG5_LO1_RETIME_EN_SHFIT                   7
#define RFREG5_LO1_RETIME_EN_MSK                     BIT(7)
#define RFREG5_LO1_SDMCKS_SHFIT                      8
#define RFREG5_LO1_SDMCKS_MSK                        BIT(8)
#define RFREG5_LO1_SEL_VDDDIVIB_SHFIT                9
#define RFREG5_LO1_SEL_VDDDIVIB_MSK                 (3<<RFREG5_LO1_SEL_VDDDIVIB_SHFIT)
#define RFREG5_LO1_SEL_VDDDIVRL_SHFIT                11
#define RFREG5_LO1_SEL_VDDDIVRL_MSK                 (3<<RFREG5_LO1_SEL_VDDDIVRL_SHFIT)
#define RFREG5_LO1_SEL64M_SHFIT                      13
#define RFREG5_LO1_SEL64M_MSK                        BIT(13)
#define RFREG5_LO1_SLF_EN_SHFIT                      14
#define RFREG5_LO1_SLF_EN_MSK                        BIT(14)

#define RFREG6_LO1_TIME_HI_SHIFT                     0
#define RFREG6_LO1_TIME_HI_MSK                      (0xf<<RFREG6_LO1_TIME_HI_SHIFT)
#define RFREG6_LO1_TIME_LOCK_SHIFT                   4
#define RFREG6_LO1_TIME_LOCK_MSK                    (0x1ff<<RFREG6_LO1_TIME_LOCK_SHIFT)

#define RFREG7_TRIM_VDDCP_LO1_SHIFT                  0
#define RFREG7_TRIM_VDDCP_LO1_MSK                   (0xf<<RFREG7_TRIM_VDDCP_LO1_SHIFT)
#define RFREG7_LO1_TRIM_VDDDIV_SHIFT                 4
#define RFREG7_LO1_TRIM_VDDDIV_MSK                  (0xf<<RFREG7_LO1_TRIM_VDDDIV_SHIFT)
#define RFREG7_LO1_TRIM_VDDVCO_SHIFT                 8
#define RFREG7_LO1_TRIM_VDDVCO_MSK                  (0xf<<RFREG7_LO1_TRIM_VDDVCO_SHIFT)
#define RFREG7_LO1_VAR_SEL_SHIFT                     12
#define RFREG7_LO1_VAR_SEL_MSK                      (3<<RFREG7_LO1_VAR_SEL_SHIFT)
#define RFREG7_LO1_VCO_EN_SHIFT                      14
#define RFREG7_LO1_VCO_EN_MSK                        BIT(14)

#define RFREG8_LO1_VCO_IBUF_SHIFT                    0
#define RFREG8_LO1_VCO_IBUF_MSK                     (0xf<<RFREG8_LO1_VCO_IBUF_SHIFT)
#define RFREG8_LO1_VCO_ICB_SHIFT                     4
#define RFREG8_LO1_VCO_ICB_MSK                      (0xf<<RFREG8_LO1_VCO_ICB_SHIFT)
#define RFREG8_LO1_IB_VDDVCO_SEL_SHIFT               8
#define RFREG8_LO1_IB_VDDVCO_SEL_MSK                (3<<RFREG8_LO1_IB_VDDVCO_SEL_SHIFT)

#define RFREG9_LO2_ACC_LECEL_SHIFT                   0
#define RFREG9_LO2_ACC_LECEL_MSK                    (3<<RFREG9_LO2_ACC_LECEL_SHIFT)
#define RFREG9_LO2_AFC_EN_SHIFT                      2
#define RFREG9_LO2_AFC_EN_MSK                        BIT(2)
#define RFREG9_LO2_ATE_EN_SHIFT                      3
#define RFREG9_LO2_ATE_EN_MSK                        BIT(3)
#define RFREG9_LO2_ATE_SEL_SHIFT                     4
#define RFREG9_LO2_ATE_SEL_MSK                      (7<<RFREG9_LO2_ATE_SEL_SHIFT)
#define RFREG9_LO2_CP_EN_SHIFT                       7
#define RFREG9_LO2_CP_EN_MSK                         BIT(7)
#define RFREG9_LO2_D2S_IBS_SHIFT                     8
#define RFREG9_LO2_D2S_IBS_MSK                      (3<<RFREG9_LO2_D2S_IBS_SHIFT)
#define RFREG9_LO2_D50_CAL_EN_SHIFT                  10
#define RFREG9_LO2_D50_CAL_EN_MSK                    BIT(10)
#define RFREG9_LO2_D50_CLK_IN_SHIFT                  11
#define RFREG9_LO2_D50_CLK_IN_MSK                    BIT(11)
#define RFREG9_LO2_D50_GSW_SHIFT                     12
#define RFREG9_LO2_D50_GSW_MSK                       BIT(12)

#define RFREG10_LO2_DIV2_VSEL_SHIFT                  0
#define RFREG10_LO2_DIV2_VSEL_MSK                   (7<<RFREG10_LO2_DIV2_VSEL_SHIFT)
#define RFREG10_LO2_DSM_EN_SHIFT                     3
#define RFREG10_LO2_DSM_EN_MSK                       BIT(3)
#define RFREG10_LO2_DTE1_EN_SHIFT                    4
#define RFREG10_LO2_DTE1_EN_MSK                      BIT(4)
#define RFREG10_LO2_DTE2_EN_SHIFT                    5
#define RFREG10_LO2_DTE2_EN_MSK                      BIT(5)
#define RFREG10_LO2_DTES_SHIFT                       6
#define RFREG10_LO2_DTES_MSK                        (3<<RFREG10_LO2_DTES_SHIFT)

#define RFREG11_LO2_ICP_HIGH_SHIFT                   0
#define RFREG11_LO2_ICP_HIGH_MSK                    (0xff<<RFREG11_LO2_ICP_HIGH_SHIFT)
#define RFREG11_LO2_ICP_NORMAL_SHIFT                 8
#define RFREG11_LO2_ICP_NORMAL_MSK                  (0xff<<RFREG11_LO2_ICP_NORMAL_SHIFT)

#define RFREG12_LO2_IOC_EN_SHIFT                     0
#define RFREG12_LO2_IOC_EN_MSK                       BIT(0)
#define RFREG12_LO2_LD_EN_SHIFT                      1
#define RFREG12_LO2_LD_EN_MSK                        BIT(1)
#define RFREG12_LO2_LDO_EN_SHIFT                     2
#define RFREG12_LO2_LDO_EN_MSK                       BIT(2)
#define RFREG12_LO2_LPF_C1_SHIFT                     3
#define RFREG12_LO2_LPF_C1_MSK                      (7<<RFREG12_LO2_LPF_C1_SHIFT)
#define RFREG12_LO2_LPF_C2_SHIFT                     6
#define RFREG12_LO2_LPF_C2_MSK                      (7<<RFREG12_LO2_LPF_C2_SHIFT)
#define RFREG12_LO2_LPF_R1_SHIFT                     9
#define RFREG12_LO2_LPF_R1_MSK                      (7<<RFREG12_LO2_LPF_R1_SHIFT)
#define RFREG12_LO2_MASH_SEL_SHIFT                   12
#define RFREG12_LO2_MASH_SEL_MSK                     BIT(12)
#define RFREG12_LO2_MSB_MORE_CNT_SHIFT               13
#define RFREG12_LO2_MSB_MORE_CNT_MSK                 BIT(13)
#define RFREG12_LO2_NMDSM_EN_SHIFT                   14
#define RFREG12_LO2_NMDSM_EN_MSK                     BIT(14)
#define RFREG12_LO2_NOISE_EN_SHIFT                   15
#define RFREG12_LO2_NOISE_EN_MSK                     BIT(15)

#define RFREG13_LO2_NOISE_WIDTH_SHIFT                0
#define RFREG13_LO2_NOISE_WIDTH_MSK                 (7<<RFREG13_LO2_NOISE_WIDTH_SHIFT)
#define RFREG13_LO2_PFD_EN_SHIFT                     3
#define RFREG13_LO2_PFD_EN_MSK                       BIT(3)
#define RFREG13_LO2_QUANT_MODE_SHIFT                 4
#define RFREG13_LO2_QUANT_MODE_MSK                   BIT(4)
#define RFREG13_LO2_RECALC_SEL_SHIFT                 5
#define RFREG13_LO2_RECALC_SEL_MSK                  (3<<RFREG13_LO2_RECALC_SEL_SHIFT)
#define RFREG13_LO2_RETIME_EN_SHIFT                  7
#define RFREG13_LO2_RETIME_EN_MSK                    BIT(7)
#define RFREG13_LO2_SDMCKS_SHIFT                     8
#define RFREG13_LO2_SDMCKS_MSK                       BIT(8)
#define RFREG13_LO2_SEL_VDDDIVIB_SHIFT               9
#define RFREG13_LO2_SEL_VDDDIVIB_MSK                (3<<RFREG13_LO2_SEL_VDDDIVIB_SHIFT)
#define RFREG13_LO2_SEL_VDDDIVRL_SHIFT               11
#define RFREG13_LO2_SEL_VDDDIVRL_MSK                (3<<RFREG13_LO2_SEL_VDDDIVRL_SHIFT)
#define RFREG13_LO2_SEL64M_SHIFT                     13
#define RFREG13_LO2_SEL64M_MSK                       BIT(13)
#define RFREG13_LO2_SLF_EN_SHIFT                     14
#define RFREG13_LO2_SLF_EN_MSK                       BIT(14)

#define RFREG14_LO2_TIME_HI_SHIFT                    0
#define RFREG14_LO2_TIME_HI_MSK                     (0xf<<RFREG14_LO2_TIME_HI_SHIFT)
#define RFREG14_LO2_TIME_LOCK_SHIFT                  4
#define RFREG14_LO2_TIME_LOCK_MSK                   (0x1ff<<RFREG14_LO2_TIME_LOCK_SHIFT)

#define RFREG15_LO2_TRIM_VDDCP_SHIFT                 0
#define RFREG15_LO2_TRIM_VDDCP_MSK                  (0xf<<RFREG15_LO2_TRIM_VDDCP_SHIFT)
#define RFREG15_LO2_TRIM_VDDDIV_SHIFT                4
#define RFREG15_LO2_TRIM_VDDDIV_MSK                 (0xf<<RFREG15_LO2_TRIM_VDDDIV_SHIFT)
#define RFREG15_LO2_TRIM_VDDVCO_SHIFT                8
#define RFREG15_LO2_TRIM_VDDVCO_MSK                 (0xf<<RFREG15_LO2_TRIM_VDDVCO_SHIFT)
#define RFREG15_LO2_VAR_SEL_SHIFT                    12
#define RFREG15_LO2_VAR_SEL_MSK                     (3<<RFREG15_LO2_VAR_SEL_SHIFT)
#define RFREG15_LO2_VCO_EN_SHIFT                     14
#define RFREG15_LO2_VCO_EN_MSK                       BIT(14)

#define RFREG16_LO2_VCO_IBUF_SHIFT                   0
#define RFREG16_LO2_VCO_IBUF_MSK                    (0xf<<RFREG16_LO2_VCO_IBUF_SHIFT)
#define RFREG16_LO2_VCO_ICB_SHIFT                    4
#define RFREG16_LO2_VCO_ICB_MSK                     (0xf<<RFREG16_LO2_VCO_ICB_SHIFT)
#define RFREG16_LO2_IB_VDDVCO_SEL_SHIFT              8
#define RFREG16_LO2_IB_VDDVCO_SEL_MSK               (3<<RFREG16_LO2_IB_VDDVCO_SEL_SHIFT)

#define RFREG17_RX_EN_BIAS_SHIFT                     0 
#define RFREG17_RX_EN_BIAS_MSK                       BIT(0)
#define RFREG17_RX_EN_IDAC_SHIFT                     1
#define RFREG17_RX_EN_IDAC_MSK                       BIT(1)
#define RFREG17_RX_EN_LDORX_SHIFT                    2
#define RFREG17_RX_EN_LDORX_MSK                      BIT(2)
#define RFREG17_RX_EN_LNA_SHIFT                      3
#define RFREG17_RX_EN_LNA_MSK                        BIT(3)
#define RFREG17_RX_EN_LNABUF_SHIFT                   4
#define RFREG17_RX_EN_LNABUF_MSK                     BIT(4)
#define RFREG17_RX_EN_MIXDIV_SHIFT                   5
#define RFREG17_RX_EN_MIXDIV_MSK                    (3<<RFREG17_RX_EN_MIXDIV_SHIFT)
#define RFREG17_RX_EN_PAMIXDIV_SHIFT                 7    
#define RFREG17_RX_EN_PAMIXDIV_MSK                  (3<<RFREG17_RX_EN_PAMIXDIV_SHIFT)
#define RFREG17_RX_EN_TIA_SHIFT                      9
#define RFREG17_RX_EN_TIA_MSK                        BIT(9)
#define RFREG17_RX_IB_MIXDIV_SHIFT                   10
#define RFREG17_RX_IB_MIXDIV_MSK                    (3<<RFREG17_RX_IB_MIXDIV_SHIFT)
#define RFREG17_RX_IB_MIXVB_SHIFT                    12
#define RFREG17_RX_IB_MIXVB_MSK                     (3<<RFREG17_RX_IB_MIXVB_SHIFT)
#define RFREG17_RX_IB_TIA_SHIFT                      14
#define RFREG17_RX_IB_TIA_MSK                       (3<<RFREG17_RX_IB_TIA_SHIFT)

#define RFREG18_RX_EN_TEST_SHIFT                     0
#define RFREG18_RX_EN_TEST_MSK                      (0xfff<<RFREG18_RX_EN_TEST_SHIFT)
#define RFREG18_RX_LDOLNA_TRIM_SHIFT                 12
#define RFREG18_RX_LDOLNA_TRIM_MSK                  (0xf<<RFREG18_RX_LDOLNA_TRIM_SHIFT)

#define RFREG19_RX_LDORX_IB_SHIFT                    0
#define RFREG19_RX_LDORX_IB_MSK                     (3<<RFREG19_RX_LDORX_IB_SHIFT)
#define RFREG19_RX_LDORX_RL_SHIFT                    2
#define RFREG19_RX_LDORX_RL_MSK                     (3<<RFREG19_RX_LDORX_RL_SHIFT)
#define RFREG19_RX_LDORX_TRIM_SHIFT                  4
#define RFREG19_RX_LDORX_TRIM_MSK                   (0xf<<RFREG19_RX_LDORX_TRIM_SHIFT)
#define RFREG19_RX_MIXVB_SHIFT                       8
#define RFREG19_RX_MIXVB_MSK                        (3<<RFREG19_RX_MIXVB_SHIFT)
#define RFREG19_RX_RSSI_BW_SHIFT                     10
#define RFREG19_RX_RSSI_BW_MSK                      (7<<RFREG19_RX_RSSI_BW_SHIFT)

#define RFREG20_RX_RSSI_GAIN_SHIFT                   0
#define RFREG20_RX_RSSI_GAIN_MSK                    (0xf<<RFREG20_RX_RSSI_GAIN_SHIFT)
#define RFREG20_RX_RSSI_VTH_SHIFT                    4
#define RFREG20_RX_RSSI_VTH_MSK                     (0x1f<<RFREG20_RX_RSSI_VTH_SHIFT)
#define RFREG20_RX_RSSI_VTL_SHIFT                    9
#define RFREG20_RX_RSSI_VTL_MSK                     (0x1f<<RFREG20_RX_RSSI_VTL_SHIFT)
#define RFREG20_RX2_EN_LNA_SHIFT                     14
#define RFREG20_RX2_EN_LNA_MSK                       BIT(14)

#define RFREG21_RX2_EN_MIXDIV_SHIFT                  0       
#define RFREG21_RX2_EN_MIXDIV_MSK                   (3<<RFREG21_RX2_EN_MIXDIV_SHIFT)
#define RFREG21_RX2_EN_MIXDIVPA_SHIFT                2
#define RFREG21_RX2_EN_MIXDIVPA_MSK                 (3<<RFREG21_RX2_EN_MIXDIVPA_SHIFT)
#define RFREG21_RX2_EN_REG_SHIFT                     4
#define RFREG21_RX2_EN_REG_MSK                       BIT(4)
#define RFREG21_RX2_IB_NBS_SHIFT                     5
#define RFREG21_RX2_IB_NBS_MSK                      (3<<RFREG21_RX2_IB_NBS_SHIFT)
#define RFREG21_RX2_IB_PBS_SHIFT                     7
#define RFREG21_RX2_IB_PBS_MSK                      (3<<RFREG21_RX2_IB_PBS_SHIFT)
#define RFREG21_RX2_RSEL_SHIFT                       10
#define RFREG21_RX2_RSEL_MSK                        (7<<RFREG21_RX2_RSEL_SHIFT)
#define RFREG21_RX2_SEL_CS_SHIFT                     12 
#define RFREG21_RX2_SEL_CS_MSK                      (0xf<<RFREG21_RX2_SEL_CS_SHIFT)

#define RFREG22_RX2_SELD_SHIFT                       0
#define RFREG22_RX2_SELD_MSK                        (0xff<<RFREG22_RX2_SELD_SHIFT)
#define RFREG22_RX2_VCM_CAL_SHIFT                    8
#define RFREG22_RX2_VCM_CAL_MSK                     (3<<RFREG22_RX2_VCM_CAL_SHIFT)
#define RFREG22_RXBB_EN_BIAS_SHIFT                   10
#define RFREG22_RXBB_EN_BIAS_MSK                     BIT(10)
#define RFREG22_RXBB_EN_IDAC_SHIFT                   11
#define RFREG22_RXBB_EN_IDAC_MSK                     BIT(11)
#define RFREG22_RXBB_EN_TXPDI_SHIFT                  12
#define RFREG22_RXBB_EN_TXPDI_MSK                    BIT(12)
#define RFREG22_RXBB_EN_TXPDQ_SHIFT                  13
#define RFREG22_RXBB_EN_TXPDQ_MSK                    BIT(13)
#define RFREG22_RXBB_ENI_SHIFT                       14
#define RFREG22_RXBB_ENI_MSK                         BIT(14)
#define RFREG22_RXBB_ENQ_SHIFT                       15
#define RFREG22_RXBB_ENQ_MSK                         BIT(15)

#define RFREG23_RXBB_EN_TEST_SHIFT                   0
#define RFREG23_RXBB_EN_TEST_MSK                    (0xfff<<RFREG23_RXBB_EN_TEST_SHIFT)
#define RFREG23_RXBB_ENRIN_SHIFT                     12
#define RFREG23_RXBB_ENRIN_MSK                      (3<<RFREG23_RXBB_ENRIN_SHIFT)
#define RFREG23_RXBB_HBW_SHIFT                       14
#define RFREG23_RXBB_HBW_MSK                         BIT(14)

#define RFREG24_RXBB_IB_OPA_SHIFT                    0
#define RFREG24_RXBB_IB_OPA_MSK                     (3<<RFREG24_RXBB_IB_OPA_SHIFT)
#define RFREG24_TXBB_ENI_SHIFT                       2
#define RFREG24_TXBB_ENI_MSK                         BIT(2)
#define RFREG24_TXBB_ENQ_SHIFT                       3
#define RFREG24_TXBB_ENQ_MSK                         BIT(3)
#define RFREG24_TXBB_TEN_SHIFT                       4
#define RFREG24_TXBB_TEN_MSK                        (0x1ff<<RFREG24_TXBB_TEN_SHIFT)
#define RFREG24_TXPD_EN_SHIFT                        13
#define RFREG24_TXPD_EN_MSK                          BIT(13)
#define RFREG24_TXPD_HPF_SHIFT                       14
#define RFREG24_TXPD_HPF_MSK                         BIT(14)

#define RFREG25_TXPD_IB_SHIFT                        0
#define RFREG25_TXPD_IB_MSK                         (3<<RFREG25_TXPD_IB_SHIFT)
#define RFREG25_TXPD_SEL_SHIFT                       2
#define RFREG25_TXPD_SEL_MSK                        (0xf<<RFREG25_TXPD_SEL_SHIFT)
#define RFREG25_TXPD_SET_SHIFT                       6
#define RFREG25_TXPD_SET_MSK                        (7<<RFREG25_TXPD_SET_SHIFT)
#define RFREG25_TXPD_TEN_SHIFT                       9
#define RFREG25_TXPD_TEN_MSK                         BIT(9)
#define RFREG25_TXRF_EN_BIAS_SHIFT                   10
#define RFREG25_TXRF_EN_BIAS_MSK                     BIT(10)
#define RFREG25_TXRF_EN_DA_SHIFT                     11
#define RFREG25_TXRF_EN_DA_MSK                       BIT(11)
#define RFREG25_TXRF_EN_DPD_SHIFT                    12
#define RFREG25_TXRF_EN_DPD_MSK                      BIT(12)
#define RFREG25_TXRF_EN_EPA_SHIFT                    13
#define RFREG25_TXRF_EN_EPA_MSK                      BIT(13)
#define RFREG25_TXRF_EN_PA_SHIFT                     14
#define RFREG25_TXRF_EN_PA_MSK                       BIT(14)
#define RFREG25_TXRF_EN2_DPD_SHIFT                   15
#define RFREG25_TXRF_EN2_DPD_MSK                     BIT(15)

#define RFREG26_TXRF_EN2_PA_SHIFT                    0
#define RFREG26_TXRF_EN2_PA_MSK                      BIT(0)
#define RFREG26_TXRF_ENMIXDIV_SHIFT                  1
#define RFREG26_TXRF_ENMIXDIV_MSK                    BIT(1)
#define RFREG26_TXRF_ENMIXLDO_SHIFT                  2
#define RFREG26_TXRF_ENMIXLDO_MSK                    BIT(2)
#define RFREG26_TXRF_ENTXLDO_SHIFT                   3
#define RFREG26_TXRF_ENTXLDO_MSK                     BIT(3)
#define RFREG26_TXRF_IBDA12_SHIFT                    4
#define RFREG26_TXRF_IBDA12_MSK                     (3<<RFREG26_TXRF_IBDA12_SHIFT)
#define RFREG26_TXRF_IBDA33_SHIFT                    6
#define RFREG26_TXRF_IBDA33_MSK                     (3<<RFREG26_TXRF_IBDA33_SHIFT)
#define RFREG26_TXRF_IBDIV_SHIFT                     8
#define RFREG26_TXRF_IBDIV_MSK                      (3<<RFREG26_TXRF_IBDIV_SHIFT)
#define RFREG26_TXRF_IBEPA12_SHIFT                   10
#define RFREG26_TXRF_IBEPA12_MSK                    (3<<RFREG26_TXRF_IBEPA12_SHIFT)
#define RFREG26_TXRF_IBEPA33_SHIFT                   12
#define RFREG26_TXRF_IBEPA33_MSK                    (3<<RFREG26_TXRF_IBEPA33_SHIFT)
#define RFREG26_TXRF_IBMIX_SHIFT                     14
#define RFREG26_TXRF_IBMIX_MSK                      (3<<RFREG26_TXRF_IBMIX_SHIFT)

#define RFREG27_TXRF_IBOPA_SHIFT                     0
#define RFREG27_TXRF_IBOPA_MSK                      (3<<RFREG27_TXRF_IBOPA_SHIFT)
#define RFREG27_TXRF_IBPA12_SHIFT                    2
#define RFREG27_TXRF_IBPA12_MSK                     (3<<RFREG27_TXRF_IBPA12_SHIFT)
#define RFREG27_TXRF_IBPA33_SHIFT                    4
#define RFREG27_TXRF_IBPA33_MSK                     (3<<RFREG27_TXRF_IBPA33_SHIFT)
#define RFREG27_TXRF_IBTXLDO_SHIFT                   6
#define RFREG27_TXRF_IBTXLDO_MSK                    (3<<RFREG27_TXRF_IBTXLDO_SHIFT)
#define RFREG27_TXRF_MIXLDO_SHIFT                    8
#define RFREG27_TXRF_MIXLDO_MSK                     (0xf<<RFREG27_TXRF_MIXLDO_SHIFT)
#define RFREG27_TXRF_MIXVB_SHIFT                     12
#define RFREG27_TXRF_MIXVB_MSK                      (3<<RFREG27_TXRF_MIXVB_SHIFT)
#define RFREG27_TXRF_RLTXLDO_SHIFT                   14
#define RFREG27_TXRF_RLTXLDO_MSK                    (3<<RFREG27_TXRF_RLTXLDO_SHIFT)

#define RFREG28_TXRF_TEN_SHIFT                       0
#define RFREG28_TXRF_TEN_MSK                        (0x3fff<<RFREG28_TXRF_TEN_SHIFT)

#define RFREG29_TXRF_TSEN_SHIFT                      0
#define RFREG29_TXRF_TSEN_MSK                       (0x1f<<RFREG29_TXRF_TSEN_SHIFT)
#define RFREG29_TXRF_TXLDO_SHIFT                     5
#define RFREG29_TXRF_TXLDO_MSK                      (0xf<<RFREG29_TXRF_TXLDO_SHIFT)
#define RFREG29_TXRX_ENIBPT_SHIFT                    9
#define RFREG29_TXRX_ENIBPT_MSK                      BIT(9)
#define RFREG29_TXRX_ENLDOBB_SHIFT                   10
#define RFREG29_TXRX_ENLDOBB_MSK                     BIT(10)
#define RFREG29_TXRX_ENREF_SHIFT                     11
#define RFREG29_TXRX_ENREF_MSK                       BIT(11)
#define RFREG29_TXRX_LDOBB_SHIFT                     12
#define RFREG29_TXRX_LDOBB_MSK                      (0xf<<RFREG29_TXRX_LDOBB_SHIFT)

#define RFREG30_TXRX_RXREF_SHIFT                     0
#define RFREG30_TXRX_RXREF_MSK                      (3<<RFREG30_TXRX_RXREF_SHIFT)
#define RFREG30_TXRX_SELIB_SHIFT                     2
#define RFREG30_TXRX_SELIB_MSK                      (7<<RFREG30_TXRX_SELIB_SHIFT)
#define RFREG30_TXRX_SELIBPT_SHIFT                   5
#define RFREG30_TXRX_SELIBPT_MSK                    (7<<RFREG30_TXRX_SELIBPT_SHIFT)
#define RFREG30_TXRX_TEN_SHIFT                       8
#define RFREG30_TXRX_TEN_MSK                        (0xff<<RFREG30_TXRX_TEN_SHIFT)

#define RFREG31_TXRX_TRIMIB_SHIFT                    0
#define RFREG31_TXRX_TRIMIB_MSK                     (0xf<<RFREG31_TXRX_TRIMIB_SHIFT)
#define RFREG31_TXRX_TRIMIBPT_SHIFT                  4
#define RFREG31_TXRX_TRIMIBPT_MSK                   (0xf<<RFREG31_TXRX_TRIMIBPT_SHIFT)
#define RFREG31_TXRX_TRIMVREF_SHIFT                  8
#define RFREG31_TXRX_TRIMVREF_MSK                   (7<<RFREG31_TXRX_TRIMVREF_SHIFT)
#define RFREG31_TXRX_TXREF_SHIFT                     11
#define RFREG31_TXRX_TXREF_MSK                      (3<<RFREG31_TXRX_TXREF_SHIFT)
#define RFREG31_VREF_EXT_EN_SHIFT                    13
#define RFREG31_VREF_EXT_EN_MSK                      BIT(13)
#define RFREG31_XO_ATE_EN_SHIFT                      14
#define RFREG31_XO_ATE_EN_MSK                        BIT(14)
#define RFREG31_XOPD_TEN_SHIFT                       15
#define RFREG31_XOPD_TEN_MSK                         BIT(15)

#define RFREG32_XO_DL_SEL_SHIFT                      0
#define RFREG32_XO_DL_SEL_MSK                       (0xf<<RFREG32_XO_DL_SEL_SHIFT)
#define RFREG32_XO_ENLDO_SHIFT                       4
#define RFREG32_XO_ENLDO_MSK                         BIT(4)
#define RFREG32_XO_ENREF_SHIFT                       5
#define RFREG32_XO_ENREF_MSK                         BIT(5)
#define RFREG32_XO_FX2_EN_SHIFT                      6
#define RFREG32_XO_FX2_EN_MSK                        BIT(6)
#define RFREG32_XO_GM_EN_SHIFT                       7
#define RFREG32_XO_GM_EN_MSK                         BIT(7)

#define RFREG33_XO_HYS_SHIFT                         0
#define RFREG33_XO_HYS_MSK                          (0x1f<<RFREG33_XO_HYS_SHIFT)
#define RFREG33_XO_LDO_SEL_SHIFT                     5
#define RFREG33_XO_LDO_SEL_MSK                      (0xf<<RFREG33_XO_LDO_SEL_SHIFT)
#define RFREG33_XO_VBG_VSEL_SHIFT                    9
#define RFREG33_XO_VBG_VSEL_MSK                     (7<<RFREG33_XO_VBG_VSEL_SHIFT)
#define RFREG33_XO_ENLDO_SHIFT                       12
#define RFREG33_XO_ENLDO_MSK                         BIT(12)
#define RFREG33_XOPD_SEL_SHIFT                       13
#define RFREG33_XOPD_SEL_MSK                        (7<<RFREG33_XOPD_SEL_SHIFT)

#define RFREG_OVERRIDE_CTRL0_ADDR                    0x140
#define RFREG_OVERRIDE_CTRL1_ADDR                    0x141
#define RFREG_OVERRIDE_CTRL2_ADDR                    0x142

//AGCREG
#define AGCREG_BASE_ADDR                             0x200
#define AGCREG_GROUP_OFFSET                          0x10
#define AGCREG_GROUP_CNT                             16
#define AGCREG_REG_CNT                               9
#define AGCREG_OVERRIDE_REG_BASE_ADDR                0x300
#define AGCREG_REFLECT_BASE_ADDR                     0x922

#define AGCREG0_RX_EN_LNARIN_SHIFT                   0
#define AGCREG0_RX_EN_LNARIN_MSK                    (7<<AGCREG0_RX_EN_LNARIN_SHIFT)
#define AGCREG0_RX_IB_IDAC_SHIFT                     3
#define AGCREG0_RX_IB_IDAC_MSK                      (3<<AGCREG0_RX_IB_IDAC_SHIFT)
#define AGCREG0_RX_IB_LNA_SHIFT                      5
#define AGCREG0_RX_IB_LNA_MSK                       (0xf<<AGCREG0_RX_IB_LNA_SHIFT)
#define AGCREG0_RX_IB_LNABUF_SHIFT                   9
#define AGCREG0_RX_IB_LNABUF_MSK                    (3<<AGCREG0_RX_IB_LNABUF_SHIFT)
#define AGCREG0_RX_IDAC_DIN_SHIFT                    11
#define AGCREG0_RX_IDAC_DIN_MSK                     (0x1f<<AGCREG0_RX_IDAC_DIN_SHIFT)

#define AGCREG1_RX_IDAC_DIP_SHIFT                    0
#define AGCREG1_RX_IDAC_DIP_MSK                     (0x1f<<AGCREG1_RX_IDAC_DIP_SHIFT)
#define AGCREG1_RX_IDAC_DQN_SHIFT                    5
#define AGCREG1_RX_IDAC_DQN_MSK                     (0x1f<<AGCREG1_RX_IDAC_DQN_SHIFT)
#define AGCREG1_RX_IDAC_DQP_SHIFT                    10
#define AGCREG1_RX_IDAC_DQP_MSK                     (0x1f<<AGCREG1_RX_IDAC_DQP_SHIFT)

#define AGCREG2_RX_LNA_GMLOAD_SHIFT                  0
#define AGCREG2_RX_LNA_GMLOAD_MSK                   (7<<AGCREG2_RX_LNA_GMLOAD_SHIFT)
#define AGCREG2_RX_LNABUF_GAIN_SHIFT                 3
#define AGCREG2_RX_LNABUF_GAIN_MSK                  (7<<AGCREG2_RX_LNABUF_GAIN_SHIFT)
#define AGCREG2_RX_LNACL_SHIFT                       6
#define AGCREG2_RX_LNACL_MSK                        (7<<AGCREG2_RX_LNACL_SHIFT)
#define AGCREG2_RX_LNACLS_SHIFT                      9
#define AGCREG2_RX_LNACLS_MSK                       (7<<AGCREG2_RX_LNACLS_SHIFT)
#define AGCREG2_RX_LNACS_SHIFT                       12
#define AGCREG2_RX_LNACS_MSK                        (0xf<<AGCREG2_RX_LNACS_SHIFT)

#define AGCREG3_RX_LNAGM_SHIFT                       0
#define AGCREG3_RX_LNAGM_MSK                        (0xf<<AGCREG3_RX_LNAGM_SHIFT)
#define AGCREG3_RX_LNALG_SHIFT                       4
#define AGCREG3_RX_LNALG_MSK                        (3<<AGCREG3_RX_LNALG_SHIFT)
#define AGCREG3_RX2_GAIN_LNA_SHIFT                   6
#define AGCREG3_RX2_GAIN_LNA_MSK                    (3<<AGCREG3_RX2_GAIN_LNA_SHIFT)
#define AGCREG3_RX2_LNA_LGIN_SHIFT                   8
#define AGCREG3_RX2_LNA_LGIN_MSK                    (3<<AGCREG3_RX2_LNA_LGIN_SHIFT)

#define AGCREG4_TXBB_PRFB_SHIFT                      0
#define AGCREG4_TXBB_PRFB_MSK                       (7<<AGCREG4_TXBB_PRFB_SHIFT)
#define AGCREG4_TXBB_PRIN_SHIFT                      3
#define AGCREG4_TXBB_PRIN_MSK                       (7<<AGCREG4_TXBB_PRIN_SHIFT)
#define AGCREG4_TXBB_RIN_SHIFT                       6
#define AGCREG4_TXBB_RIN_MSK                        (3<<AGCREG4_TXBB_RIN_SHIFT)
#define AGCREG4_TXBB_RQ_SHIFT                        8
#define AGCREG4_TXBB_RQ_MSK                         (3<<AGCREG4_TXBB_RQ_SHIFT)
#define AGCREG4_TXRF_DA_CL_SHIFT                     10
#define AGCREG4_TXRF_DA_CL_MSK                      (7<<AGCREG4_TXRF_DA_CL_SHIFT)
#define AGCREG4_TXRF_DA_CLS_SHIFT                    13
#define AGCREG4_TXRF_DA_CLS_MSK                     (7<<AGCREG4_TXRF_DA_CLS_SHIFT)

#define AGCREG5_TXRF_DAGAIN_SHIFT                    0
#define AGCREG5_TXRF_DAGAIN_MSK                     (0xf<<AGCREG5_TXRF_DAGAIN_SHIFT)
#define AGCREG5_TXRF_DARL_SHIFT                      4
#define AGCREG5_TXRF_DARL_MSK                       (7<<AGCREG5_TXRF_DARL_SHIFT)
#define AGCREG5_TXRF_DAVB33_SHIFT                    7
#define AGCREG5_TXRF_DAVB33_MSK                     (0xf<<AGCREG5_TXRF_DAVB33_SHIFT)
#define AGCREG5_TXRF_DPDAT_SHIFT                     11
#define AGCREG5_TXRF_DPDAT_MSK                      (3<<AGCREG5_TXRF_DPDAT_SHIFT)
#define AGCREG5_TXRF_EPARL_SHIFT                     13
#define AGCREG5_TXRF_EPARL_MSK                      (7<<AGCREG5_TXRF_EPARL_SHIFT)

#define AGCREG6_TXRF_EPACAP_SHIFT                    0
#define AGCREG6_TXRF_EPACAP_MSK                     (0xf<<AGCREG6_TXRF_EPACAP_SHIFT)
#define AGCREG6_TXRF_EPAOCAP_SHIFT                   4
#define AGCREG6_TXRF_EPAOCAP_MSK                    (0xf<<AGCREG6_TXRF_EPAOCAP_SHIFT)
#define AGCREG6_TXRF_EPAVB33_SHIFT                   8
#define AGCREG6_TXRF_EPAVB33_MSK                    (0x1f<<AGCREG6_TXRF_EPAVB33_SHIFT)
#define AGCREG6_TXRF_IBDA_SHIFT                      13
#define AGCREG6_TXRF_IBDA_MSK                       (7<<AGCREG6_TXRF_IBDA_SHIFT)

#define AGCREG7_TXRF_EPAGAIN_SHIFT                   0
#define AGCREG7_TXRF_EPAGAIN_MSK                    (0x3f<<AGCREG7_TXRF_EPAGAIN_SHIFT)
#define AGCREG7_TXRF_IBEPA_SHIFT                     6
#define AGCREG7_TXRF_IBEPA_MSK                      (7<<AGCREG7_TXRF_IBEPA_SHIFT)
#define AGCREG7_TXRF_IBPA_SHIFT                      9
#define AGCREG7_TXRF_IBPA_MSK                       (7<<AGCREG7_TXRF_IBPA_SHIFT)
#define AGCREG7_TXRF_PACAP_SHIFT                     12
#define AGCREG7_TXRF_PACAP_MSK                      (0xf<<AGCREG7_TXRF_PACAP_SHIFT)

#define AGCREG8_TXRF_PAGAIN_SHIFT                    0
#define AGCREG8_TXRF_PAGAIN_MSK                     (0x3f<<AGCREG8_TXRF_PAGAIN_SHIFT)
#define AGCREG8_TXRF_PAOCAP_SHIFT                    6
#define AGCREG8_TXRF_PAOCAP_MSK                     (0xf<<AGCREG8_TXRF_PAOCAP_SHIFT)
#define AGCREG8_TXRF_PAVB33_SHIFT                    10
#define AGCREG8_TXRF_PAVB33_MSK                     (0x1f<<AGCREG8_TXRF_PAVB33_SHIFT)

#define AGCREG_OVERRIDE_CTRL_ADDR                    0x310

#define AGCREG_AGC_IDX_STATUS_ADDR                   0x311

//BWREG
#define BWREG_BASE_ADDR                              0x400
#define BWREG_GROUP_OFFSET                           0x8
#define BWREG_GROUP_CNT                              8
#define BWREG_REG_CNT                                3
#define BWREG_OVERRIDE_REG_BASE_ADDR                 0x440
#define BWREG_REFLECT_BASE_ADDR                      0x92b

#define BWREG0_RXBB_CFB_SHIFT                        0
#define BWREG0_RXBB_CFB_MSK                         (0x3f<<BWREG0_RXBB_CFB_SHIFT)
#define BWREG0_RXBB_CPGA_SHIFT                       6
#define BWREG0_RXBB_CPGA_MSK                        (0x3f<<BWREG0_RXBB_CPGA_SHIFT)

#define BWREG1_RXBB_CTRIM_SHIFT                      0
#define BWREG1_RXBB_CTRIM_MSK                       (0x3f<<BWREG1_RXBB_CTRIM_SHIFT)
#define BWREG1_RXBB_RFB_SHIFT                        6
#define BWREG1_RXBB_RFB_MSK                         (3<<BWREG1_RXBB_RFB_SHIFT)
#define BWREG1_RXBB_RQ_SHIFT                         8
#define BWREG1_RXBB_RQ_MSK                          (0x1f<<BWREG1_RXBB_RQ_SHIFT)

#define BWREG2_TXBB_CFB_SHIFT                        0
#define BWREG2_TXBB_CFB_MSK                         (0x3f<<BWREG2_TXBB_CFB_SHIFT)
#define BWREG2_TXBB_CPGA_SHIFT                       6
#define BWREG2_TXBB_CPGA_MSK                        (0x3f<<BWREG2_TXBB_CPGA_SHIFT)

#define BWREG_OVERRIDE_CTRL_ADDR                     0x448

//FREQREG
#define FREQREG_BASE_ADDR                            0x500
#define FREQREG_GROUP_OFFSET                         0x10
#define FREQREG_GROUP_CNT                            16
#define FREQREG_REG_CNT                              8
#define FREQREG_OVERRIDE_REG_BASE_ADDR               0x600
#define FREQREG_REFLECT_BASE_ADDR                    0x92e

#define FREQREG0_LO1_INT_DIV_SHIFT                   0
#define FREQREG0_LO1_INT_DIV_MSK                    (0xff<<FREQREG0_LO1_INT_DIV_SHIFT)

#define FREQREG1_LO1_FRAC_DIV_LOW_SHIFT              0
#define FREQREG1_LO1_FRAC_DIV_LOW_MSK               (0xffff<<FREQREG1_LO1_FRAC_DIV_LOW_SHIFT)

#define FREQREG2_LO1_FRAC_DIV_HIGH_SHIFT             0
#define FREQREG2_LO1_FRAC_DIV_HIGF_MSK              (0x3f<<FREQREG2_LO1_FRAC_DIV_HIGH_SHIFT)

#define FREQREG3_LO1_SOFT_BAND_SHIFT                 0
#define FREQREG3_LO1_SOFT_BAND_MSK                  (0x1ff<<FREQREG3_LO1_SOFT_BAND_SHIFT)

#define FREQREG4_LO2_INT_DIV_SHIFT                   0
#define FREQREG4_LO2_INT_DIV_MSK                    (0xff<<FREQREG4_LO2_INT_DIV_SHIFT)

#define FREQREG5_LO2_FRAC_DIV_LOW_SHIFT              0
#define FREQREG5_LO2_FRAC_DIV_LOW_MSK               (0xffff<<FREQREG5_LO2_FRAC_DIV_LOW_SHIFT)

#define FREQREG6_LO2_FRAC_DIV_HIGH_SHIFT             0
#define FREQREG6_LO2_FRAC_DIV_HIGF_MSK              (0x3f<<FREQREG6_LO2_FRAC_DIV_HIGH_SHIFT)


#define FREQREG7_LO2_SOFT_BAND_SHIFT                 0
#define FREQREG7_LO2_SOFT_BAND_MSK                  (0x1ff<<FREQREG7_LO2_SOFT_BAND_SHIFT)

#define FREQREG_OVERRIDE_CTRL_ADDR                   0x610

//AGCBWREG
#define AGCBWREG_BASE_ADDR                           0x700
#define AGCBWREG_GROUP_OFFSET                        0x2
#define AGCBWREG_GROUP_CNT                           64
#define AGCBWREG_REG_CNT                             2
#define AGCBWREG_OVERRIDE_REG_BASE_ADDR              0x780
#define AGCBWREG_REFLECT_BASE_ADDR                   0x936

#define AGCBWREG0_RX_TIA_C_SHIFT                     0
#define AGCBWREG0_RX_TIA_C_MSK                      (0x3f<<AGCBWREG0_RX_TIA_C_SHIFT)
#define AGCBWREG0_RX_TIA_G_SHIFT                     6
#define AGCBWREG0_RX_TIA_G_MSK                      (3<<AGCBWREG0_RX_TIA_G_SHIFT)
#define AGCBWREG0_RX_TIA_R_SHIFT                     8
#define AGCBWREG0_RX_TIA_R_MSK                      (7<<AGCBWREG0_RX_TIA_R_SHIFT)
#define AGCBWREG0_RX_TRIM_TIAC_SHIFT                 11
#define AGCBWREG0_RX_TRIM_TIAC_MSK                   BIT(11)

#define AGCBWREG1_RXBB_IB_IDAC_SHIFT                 0
#define AGCBWREG1_RXBB_IB_IDAC_MSK                  (3<<AGCBWREG1_RXBB_IB_IDAC_SHIFT)
#define AGCBWREG1_RXBB_IDACI_SHIFT                   2
#define AGCBWREG1_RXBB_IDACI_MSK                    (0x1f<<AGCBWREG1_RXBB_IDACI_SHIFT)
#define AGCBWREG1_RXBB_IDACQ_SHIFT                   7
#define AGCBWREG1_RXBB_IDACQ_MSK                    (0x1f<<AGCBWREG1_RXBB_IDACQ_SHIFT)
#define AGCBWREG1_RXBB_RIN_SHIFT                     12
#define AGCBWREG1_RXBB_RIN_MSK                      (7<<AGCBWREG1_RXBB_RIN_SHIFT)

#define AGCBWREG_OVERRIDE_CTRL_ADDR                 0x782

//SPECIAL_RFREG
#define REG_RC_CAL_BASE_ADDR                         0x800
#define REG_RC_CAL_REG_CNT                           6

#define RCCALREG0_ADDR                               0x800
#define RCCALREG0_RCCAL_EN_SHIFT                     0
#define RCCALREG0_RCCAL_EN_MSK                       BIT(0)
#define RCCALREG0_RCCAL_MODE_SHIFT                   1
#define RCCALREG0_RCCAL_MODE_MSK                     BIT(1)
#define RCCALREG0_REPEAT_TIME_SHIFT                  2
#define RCCALREG0_REPEAT_TIME_MSK                   (0xf<<RCCALREG0_REPEAT_TIME_MSK)
#define RCCALREG0_SAME_TIME_SHIFT                    6 
#define RCCALREG0_SAME_TIME_MSK                     (0xf<<RCCALREG0_SAME_TIME_SHIFT)
#define RCCALREG0_CPU_RCCAL_DONE_CLR_SHIFT           15
#define RCCALREG0_CPU_RCCAL_DONE_CLR_MSK             BIT(15)

#define RCCALREG1_ADDR                               0x801
#define RCCALREG1_RCRST_LOW_SHIFT                    0
#define RCCALREG1_RCRST_LOW_MSK                     (0x3ff<<RCCALREG1_RCRST_LOW_SHIFT)

#define RCCALREG2_ADDR                               0x802
#define RCCALREG2_RCRST_HIGH_SHIFT                   0
#define RCCALREG2_RCRST_HIGH_MSK                    (0x7ff<<RCCALREG2_RCRST_HIGH_SHIFT)

#define RCCALREG3_ADDR                               0x803
#define RCCALREG3_RCRST_SETUP_SHIFT                  0
#define RCCALREG3_RCRST_SETUP_MSK                   (0x3ff<<RCCALREG3_RCRST_SETUP_SHIFT)

#define RCCALREG4_ADDR                               0x804
#define RCCALREG4_ANALOG_SETUP_SHIFT                 0
#define RCCALREG4_ANALOG_SETUP_MSK                  (0x3ff<<RCCALREG4_ANALOG_SETUP_SHIFT)

#define RCCALREG5_ADDR                               0x805
#define RCCALREG5_RCSEL_IN_SHIFT                     0
#define RCCALREG5_RCSEL_IN_MSK                      (0x3f<<RCCALREG5_RCSEL_IN_SHIFT)
#define RCCALREG5_RC_TRIM_SOFT_SHIFT                 6
#define RCCALREG5_RC_TRIM_SOFT_MSK                   BIT(6)

#define RCCALREG6_ADDR                               0x806  //readonly
#define RCCALREG6_RCSEL_SHIFT                        0
#define RCCALREG6_RCSEL_MSK                         (0x3f<<RCCALREG6_RCSEL_SHIFT)
#define RCCALREG6_RCCAL_DONE_SHIFT                   8
#define RCCALREG6_RCCAL_DONE_MSK                     BIT(8)
#define RCCALREG6_RC_OUT_SHIFT                       9
#define RCCALREG6_RC_OUT_MSK                         BIT(9)
#define RCCALREG6_RC_TRIM_SHIFT                      10
#define RCCALREG6_RC_TRIM_MSK                        BIT(10)
#define RCCALREG6_RCCAL_EN_SHIFT                     11
#define RCCALREG6_RCCAL_EN_MSK                       BIT(11)

#define REG_LO1_ADDR                                 0x810
#define REG_LO1_AFC_KICK_SHIFT                       0
#define REG_LO1_AFC_KICK_MSK                         BIT(0)
#define REG_LO1_SOFTBAND_DEC_SHIFT                   1
#define REG_LO1_SOFTBAND_DEC_MSK                     BIT(1)
#define REG_LO1_SOFTBAND_ADD_SHIFT                   2
#define REG_LO1_SOFTBAND_ADD_MSK                     BIT(2)
#define REG_LO1_SOFT_FORCE_SHIFT                     3
#define REG_LO1_SOFT_FORCE_MSK                       BIT(3)
#define REG_LO1_DIV_LOAD_SHIFT                       4
#define REG_LO1_DIV_LOAD_MSK                         BIT(4)
#define REG_LO1_DIV_EN_SHIFT                         5
#define REG_LO1_DIV_EN_MSK                           BIT(5)
#define REG_LO1_DSM_SELF_TESTEN_SHIFT                6
#define REG_LO1_DSM_SELF_TESTEN_MSK                  BIT(6)

#define REG_LO2_ADDR                                 0x820
#define REG_LO2_AFC_KICK_SHIFT                       0
#define REG_LO2_AFC_KICK_MSK                         BIT(0)
#define REG_LO2_SOFTBAND_DEC_SHIFT                   1
#define REG_LO2_SOFTBAND_DEC_MSK                     BIT(1)
#define REG_LO2_SOFTBAND_ADD_SHIFT                   2
#define REG_LO2_SOFTBAND_ADD_MSK                     BIT(2)
#define REG_LO2_SOFT_FORCE_SHIFT                     3
#define REG_LO2_SOFT_FORCE_MSK                       BIT(3)
#define REG_LO2_DIV_LOAD_SHIFT                       4
#define REG_LO2_DIV_LOAD_MSK                         BIT(4)
#define REG_LO2_DIV_EN_SHIFT                         5
#define REG_LO2_DIV_EN_MSK                           BIT(5)
#define REG_LO2_DSM_SELF_TESTEN_SHIFT                6
#define REG_LO2_DSM_SELF_TESTEN_MSK                  BIT(6)

#define RF_XO_REG_CNT                                2

#define REG_XO_0_ADDR                                0x830
#define REG_XO_0_XO_DR_SHIFT                         0
#define REG_XO_0_XO_DR_MSK                          (0xff<<REG_XO_0_XO_DR_SHIFT)
#define REG_XO_0_XO_CS_SHIFT                         8
#define REG_XO_0_XO_CS_MSK                          (0xf<<REG_XO_0_XO_CS_SHIFT)

#define REG_XO_1_ADDR                                0x831
#define REG_XO_1_XO_CTI_SHIFT                        0
#define REG_XO_1_XO_CTI_MSK                         (0x1f<<REG_XO_1_XO_CTI_SHIFT)
#define REG_XO_1_XO_CTO_SHIFT                        8
#define REG_XO_1_XO_CTO_MSK                         (0x1f<<REG_XO_1_XO_CTO_SHIFT)

#define REG_RSSI_ADDR                                0x840
#define REG_RSSI_CLK_DIV_SHIFT                       0
#define REG_RSSI_CLK_DIV_MSK                        (0xff<<REG_RSSI_CLK_DIV_SHIFT)

#define RF_DCOC_REG_CNT                              2

#define REG_DCOC_0_ADDR                              0x850
#define REG_DCOC_0_RXBB_CMPEN_SHIFT                  0
#define REG_DCOC_0_RXBB_CMPEN_MSK                    BIT(0)

#define REG_DCOC_1_ADDR                              0x851
#define REG_DCOC_1_CLK_DIV_SHIFT                     0
#define REG_DCOC_1_CLK_DIV_MSK                      (0xff<<REG_DCOC_1_CLK_DIV_SHIFT)

#define REG_TXBB_ADDR                                0x860
#define REG_TXBB_TXBB_CTRIM_SHIFT                    0
#define REG_TXBB_TXBB_CTRIM_MSK                     (0x3f<<REG_TXBB_TXBB_CTRIM_SHIFT)

#define REG_ANALOG_CHANGE_ADDR                       0x870
#define REG_ANALOG_CHANGE_ANALOG_CHANGE_SHIFT        0
#define REG_ANALOG_CHANGE_ANALOG_CHANGE_MSK          BIT(0)

#define REG_RF_REG_RST_ADDR                          0xfff
#define RF_REG_RESET_SHIFT                           0
#define RF_REG_RESET_MSK                             BIT(0)

#define RF_WATCH_REG_BASE                            0x900

#define I_PATH 0
#define Q_PATH 1

struct hgrf_s1gv3 {
    struct rf_device dev;
    struct rfspi_device *rfspi_dev;
    struct dbgpath_device *dbgpath_dev;
    struct tdma_device *tdma_dev;
    struct tdma_device *tdma2_dev;
    struct rfdigicali_device *rfdigicali_dev;
    struct rfmipi_device *mipi_dev;
    uint32 opened;
};


/** @defgroup Exported_Functions
  * @{
  */

int32 hgrf_s1gv3_attach(uint32 dev_id, struct hgrf_s1gv3 *rfip);

#ifdef __cplusplus
}
#endif

#endif 
