// hgrfmipi.h
#ifndef _HGRFMIPI_H_
#define _HGRFMIPI_H_

union hgrfmipi_cfg
{
    struct {
        //----------------------------------------------------
        // related register RFFE_CTL
        //----------------------------------------------------
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
            // Clock devision select
            // 0: PHY_CLK/1
            // 1: PHY_CLK/2
            // 2: PHY_CLK/4
            // ...
            // 7: PHY_CLK/128reserved
                             CDS                                 :  3,
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
                             SS                                  :  1,
            //----------------------------------------------------
            // bit 30
                             RBV                                 :  1, 
            //----------------------------------------------------                   	    
            // bit 31
                             VIO                                 :  1;
            //----------------------------------------------------
        } n_rffe_ctl;
        //----------------------------------------------------
        // related register RFFE_INTE
        //----------------------------------------------------
        struct {
            // bit 0
            // Interrupt enable bit of transmission complete
            uint32           TDIE                                :  1,
            //----------------------------------------------------  
            // bit 1
            // Interrupt enable bit of reception complete
                             RDIE                                :  1,
            //----------------------------------------------------  
            // bit 2
            // Interrupt enable bit of read back verify error 
                             RBVIE                               :  1,
            //----------------------------------------------------  
            // bit 3:31
                             reserved                            :  3;         
        } n_rffe_inte;
        //----------------------------------------------------
        // related register RFFE_DCTL
        //----------------------------------------------------
        struct {
            // bit 0:4
            // Clock delay 0~31
            uint32           CDK                                 :  5,
            //----------------------------------------------------  
            // bit 5:7
                             reserved0                           :  3,
            //----------------------------------------------------  
            // bit 8:12
            // input data delay 0~31
                             DID                                 :  1,
            //---------------------------------------------------- 
            // bit 13:15
                             reserved1                           :  3,
            //----------------------------------------------------  
            // bit 16:20
            // Interrupt enable bit of read back verify error 
                             DOD                                 :  5,
            //----------------------------------------------------  
            // bit 3:31
                             reserved                            : 11;         
        } n_rffe_dctl;
    };
    uint32           word_buf[3];
};

struct hgrfmipi_reg
{
    __IO uint32 RFFE_CTL;
    __IO uint32 RFFE_DATA[4];
    __IO uint32 RFFE_INTE;
    __IO uint32 RFFE_STA;
    __IO uint32 RFFE_DCTL;
    __IO uint32 RFFE_TEST;
};

struct hgrfmipi {
    struct rfmipi_device         dev;
    struct hgrfmipi_reg          *prfmipireg;
    const union hgrfmipi_cfg     *prfmipicfg;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
// Register Address: 'h00
#define RFFE_CTL_VIO_MSK               0x80000000
#define RFFE_CTL_VIO_SHIFT             31
#define RFFE_CTL_RBV_MSK               0x40000000
#define RFFE_CTL_RBV_SHIFT             30
#define RFFE_CTL_SS_MSK                0x20000000
#define RFFE_CTL_SS_SHIFT              29
#define RFFE_CTL_DRR_MSK               0x10000000
#define RFFE_CTL_DRR_SHIFT             28
#define RFFE_CTL_SES_MSK               0x08000000
#define RFFE_CTL_SES_SHIFT             27
#define RFFE_CTL_CDS_MSK               0x07000000
#define RFFE_CTL_CDS_SHIFT             24
#define RFFE_CTL_SLAVEREGADDR_MSK      0x00FF0000
#define RFFE_CTL_SLAVEREGADDR_SHIFT    16
#define RFFE_CTL_DBN_MSK               0x00000F00
#define RFFE_CTL_DBN_SHIFT             8
#define RFFE_CTL_SLAVEADDR_MSK         0x000000F0
#define RFFE_CTL_SLAVEADDR_SHIFT       4
#define RFFE_CTL_CSS_MSK               0x00000007
#define RFFE_CTL_CSS_SHIFT             0

// Register Address: 'h04
#define RFFE_WDATA0_WRITE_DATA_MSK      0xFFFFFFFF
#define RFFE_WDATA0_WRITE_DATA_SHIFT    0

// Register Address: 'h08
#define RFFE_WDATA1_WRITE_DATA_MSK      0xFFFFFFFF
#define RFFE_WDATA1_WRITE_DATA_SHIFT    0

// Register Address: 'h10
#define RFFE_WDATA3_WRITE_DATA_MSK      0xFFFFFFFF
#define RFFE_WDATA3_WRITE_DATA_SHIFT    0

// Register Address: 'h14
#define RFFE_INTE_RBVIE_MSK      0x00000004
#define RFFE_INTE_RBVIE_SHIFT    2
#define RFFE_INTE_RDIE_MSK       0x00000002
#define RFFE_INTE_RDIE_SHIFT     1
#define RFFE_INTE_TDIE_MSK       0x00000001
#define RFFE_INTE_TDIE_SHIFT     0

// Register Address: 'h18
#define RFFE_STA_PEF_MSK       0xFFFF0000
#define RFFE_STA_PEF_SHIFT     16
#define RFFE_STA_RBVP_MSK      0x00000004
#define RFFE_STA_RBVP_SHIFT    2
#define RFFE_STA_RDP_MSK       0x00000002
#define RFFE_STA_RDP_SHIFT     1
#define RFFE_STA_TDP_MSK       0x00000001
#define RFFE_STA_TDP_SHIFT     0

// Register Address: 'h1c
#define RFFE_DCTL_DOD_MSK      0x001F0000
#define RFFE_DCTL_DOD_SHIFT    16
#define RFFE_DCTL_DID_MSK      0x00001F00
#define RFFE_DCTL_DID_SHIFT    8
#define RFFE_DCTL_CDK_MSK      0x0000001F
#define RFFE_DCTL_CDK_SHIFT    0

// Register Address: 'h20
#define RFFE_TEST_EBS_MSK      0xFFFF0000
#define RFFE_TEST_EBS_SHIFT    16
#define RFFE_TEST_SPE_MSK      0x00000003
#define RFFE_TEST_SPE_SHIFT    0

int32 hgrfmipi_attach(uint32 dev_id, struct hgrfmipi *prfmipi);
#endif

