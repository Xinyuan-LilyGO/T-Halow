/**
  ******************************************************************************
  * @file    sdk/driver/hgi2c_dw.h
  * @author  HUGE-IC Application Team
  * @version V1.0.0
  * @date    01-08-2018
  * @brief   This file contains all the IIC LL firmware functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 HUGE-IC</center></h2>
  *
  *
  *
  ******************************************************************************
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HGI2C_DW_H
#define __HGI2C_DW_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
     
/** @addtogroup TX6001_StdPeriph_Driver TX6001 Driver
  * @{
  */
     
/** @addtogroup iic_interface_gr IIC Driver
  * @ingroup  TX6001_StdPeriph_Driver
  * @{
  */ 

/** @addtogroup IIC_LL_Driver IIC LL Driver
  * @ingroup  iic_interface_gr
  * @brief Mainly the driver part of the IIC module, which includes \b IIC \b Register 
  * \b Constants, \b IIC \b Exported \b Constants, \b IIC \b Exported \b Struct, \b IIC
  * \b Data \b transfers \b functions, \b IIC \b Initialization \b and \b IIC \b Configuration 
  * \b And \b Interrupt \b Handle \b function.
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
 
/** @defgroup IIC_LL_Register_Constants IIC LL Register Constants
  * @ingroup  IIC_LL_Driver
  * @brief    IIC LL register constant table definition
  *
  *
@verbatim   
  ===============================================================================
                                Register Constants
  ===============================================================================  
  
    Register Constants mainly encapsulates each bit in each group in the IIC 
    register. In the process of configuration, the macro definition can be directly 
    called to configure the IIC register, mainly for convenience. Understand the 
    configuration of the IIC.
    
@endverbatim
  *
  * @{
  */

/***** IC_CON(IIC Control Register) *****/
/*! In slave, controls to enable DW_apb_i2c slave as persistentor non-persistent slave
 */
#define DW_IIC_CON_SMBUS_PERSISTANT_SLV_ADDR_EN             (1UL << 19)
/*! In slave, controls whether DW_apb_i2c should enable Address Resolution Logic in 
 *  SMBus Mode 
 */
#define DW_IIC_CON_SMBUS_ARP_EN                             (1UL << 18)
/*! In slave, controls DW_apb_i2c slave only receives Quick commands in SMBus Mode
 */
#define DW_IIC_CON_SMBUS_SLAVE_QUICK_CMD_EN                 (1UL << 17)
/*! In slave, Enables the usage of IC_OPTIONAL_SAR register
 */
#define DW_IIC_CON_OPTION_SAR_CTRL                          (1UL << 16)
/*! In master, bus clear feature enable/disable
 */
#define DW_IIC_CON_BUS_CLEAR_FEATURE_CTRL                   (1UL << 11)
/*! in master, stop dectect signal if only/whether the master is active
 */
#define DW_IIC_CON_STOP_DEC_IF_MASTER_ACTINE                (1UL << 10)
/*! This bit controls whether DW_apb_i2c should hold the bus when the Rx FIFO is 
 *  physically full to its RX_BUFFER_DEPTH 
 */
#define DW_IIC_CON_RX_FIFO_FULL_HLD_CTRL                    (1UL << 9)
/*! This bit controls the generation of the TX_EMPTY interrupt, as described in the 
 *  DW_IIC_IC_RAW_INTR_STAT register
 */
#define DW_IIC_CON_TX_EMPTY_CTRL                            (1UL << 8)
/*! In slave, stop dectect signal if only/whether the master is active
 */
#define DW_IIC_CON_STOP_DET_IFADDRESSED                     (1UL << 7)
/*! Enable/Disable IIC slave
 */
#define DW_IIC_CON_IC_SLAVE_DISABLE                         (1UL << 6)
/*! Determines whether RESTART conditions may be sent when acting as a master
 */
#define DW_IIC_CON_IC_RESTART_EN                            (1UL << 5)
/*! In master, support 7bit/10bit address
 */
#define DW_IIC_CON_IC10BITADDR_MASTER                       (1UL << 4)
/*! In slave, support 7bit/10bit address
 */
#define DW_IIC_CON_IC10BITADDR_SLAVE                        (1UL << 3)
/*! These bits control at which speed the DW_apb_i2c operates
 */
#define DW_IIC_CON_SPEED(n)                                 (((n)&0x3) << 1)
/*! This bit controls whether the DW_apb_i2c master is enabled
 */
#define DW_IIC_CON_MASTER_MODE                              (1UL << 0)


/***** IC_TAR(IIC Target Address Register) *****/
/*! If bit 11 (SPECIAL) is set to 1, then this bit indicates whether a Quick command 
 *  is to be performed by the DW_apb_i2c 
 */
#define DW_IIC_TAR_SMBUS_QUICK_CMD                          (1UL << 16)
/*! If bit 11 (SPECIAL) is set to 1, then this bit indicates whether a Device-ID of
 *  a particular slave mentioned in IC_TAR[6:0] is to be performed by the DW_apb_i2c 
 *  Master
 */
#define DW_IIC_TAR_DEVICE_ID                                (1UL << 13)
/*! This bit controls whether the DW_apb_i2c starts its transfers in 7-or 10-bit 
 *  addressing mode when acting as a master 
 */
#define DW_IIC_TAR_IC_10BITADDR_MASTER                      (1UL << 12)
/*! indicates whether software performs a Device-ID, General Call or START BYTE command
 */
#define DW_IIC_TAR_SPECIAL                                  (1UL << 11)
/*! If bit 11 (SPECIAL) is set to 1 and bit 13 (Device-ID) is set to 0, then this bit 
 *  indicates whether a General Call or START byte command is to be performed by the 
 *  DW_apb_i2c
 */
#define DW_IIC_TAR_GC_OR_START                              (1UL << 10)
/*! This is the target address for any master transaction
 */
#define DW_IIC_TAR_IC_TAR(n)                                (((n)&0x3FF) << 0)


/***** IC_SAR(IIC Slave Address Register) *****/
/*! The IC_SAR holds the slave address when the I2C is operating as a slave
 */
#define DW_IIC_SAR_IC_SAR(n)                                (((n)&0x3FF) << 0)


/***** IC_HS_MADDR(IIC High Speed Master Mode Code Address Register) *****/
/*! This bit field holds the value of the I2C HS mode master code
 */
#define DW_IIC_HS_MADDR_IC_HS_MAR(n)                        (((n)&0x7) << 0)


/***** IC_DATA_CMD(IIC Rx/Tx Data Buffer and Command Register) *****/
/*! Indicates the first data byte received after the address phase for receive transfer
 *  in Master receiver or Slave receiver mode 
 */
#define DW_IIC_DATA_CMD_FIRST_DATA_BYTE                     (1UL << 11)
/*! This bit controls whether a RESTART is issued before the byte is sent or received
 */
#define DW_IIC_DATA_CMD_RESTART                             (1UL << 10)
/*! This bit controls whether a STOP is issued after the byte is sent or received
 */
#define DW_IIC_DATA_CMD_STOP                                (1UL << 9)
/*! This bit controls whether a read or a write is performed
 */
#define DW_IIC_DATA_CMD_CMD                                 (1UL << 8)
/*! This register contains the data to be transmitted or received on the I2C bus
 */
#define DW_IIC_DATA_CMD_DAT(n)                              (((n)&0xFF) << 0)


/***** IC_SS_SCL_HCNT(Standard Speed I2C Clock SCL High Count Register) *****/
/*! This register must be set before any I2C bus transaction can take place to ensure 
 *  proper I/O timing, This register sets the SCL clock high-period count for standard 
 *  speed
 */
#define DW_IIC_IC_SS_SCL_HCNT(n)                            (((n)&0xFFFF) << 0)


/***** IC_SS_SCL_LCNT(Standard Speed I2C Clock SCL Low Count Register) *****/
/*! This register must be set before any I2C bus transaction can take place to ensure 
 *  proper I/O timing. This register sets the SCL clock low period count for standard 
 *  speed
 */
#define DW_IIC_IC_SS_SCL_LCNT(n)                            (((n)&0xFFFF) << 0)


/***** IC_FS_SCL_HCNT(Fast Mode or Fast Mode Plus I2C Clock SCL High Count Register) *****/
/*! This register must be set before any I2C bus transaction can take place to ensure 
 *  proper I/O timing. This reg sets the SCL clock high-period count for fast mode or 
 *  fast mode plus
 */
#define DW_IIC_IC_FS_SCL_HCNT(n)                            (((n)&0xFFFF) << 0)


/***** IC_FS_SCL_LCNT(Fast Mode or Fast Mode Plus I2C Clock SCL Low Count Register) *****/
/*! This register must be set before any I2C bus transaction can take place to ensure 
 *  proper I/O timing. This reg sets the SCL clock low period count for fast mode or 
 *  fast mode plus
 */
#define DW_IIC_IC_FS_SCL_LCNT(n)                            (((n)&0xFFFF) << 0)


/***** IC_HS_SCL_HCNT(High Speed I2C Clock SCL High Count Register) *****/
/*! This register must be set before any I2C bus transaction can take place to ensure 
 *  proper I/O timing. This register sets the SCL clock high period count for high speed
 */ 
#define DW_IIC_IC_HS_SCL_HCNT(n)                            (((n)&0xFFFF) << 0)


/***** IC_HS_SCL_LCNT(High Speed I2C Clock SCL Low Count Register) *****/
/*! This register must be set before any I2C bus transaction can take place toensure 
 *  proper I/O timing. This register sets the SCL clock low period count for high speed
 */
#define DW_IIC_IC_HS_SCL_LCNT(n)                            (((n)&0xFFFF) << 0)


/***** IC_INTR_STAT(IIC Interrupt Status Register) *****/
/*! See IC_RAW_INTR_STAT for a detailed description of this bit.
 */
#define DW_IIC_INTR_STAT_R_SCL_STUCK_AT_LOW                 (1UL << 14)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_MST_ON_HOLD                      (1UL << 13)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_RESTART_DET                      (1UL << 12)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_GEN_CALL                         (1UL << 11)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_START_DET                        (1UL << 10)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_STOP_DET                         (1UL << 9)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_ACTIVITY                         (1UL << 8)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_RX_DONE                          (1UL << 7)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_TX_ABRT                          (1UL << 6)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_RD_REQ                           (1UL << 5)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_TX_EMPTY                         (1UL << 4)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_TX_OVER                          (1UL << 3)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_RX_FULL                          (1UL << 2)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_RX_OVER                          (1UL << 1)
/*! See IC_RAW_INTR_STAT on page 186 for a detailed description of this bit
 */
#define DW_IIC_INTR_STAT_R_RX_UNDER                         (1UL << 0)


/***** IC_INTR_MASK (IIC Interrupt Mask Register) *****/
/*! This bit masks the R_SCL_STUCK_AT_LOW interrupt bit in the IC_INTR_STAT register 
 *  This bit is enabled only when IC_BUS_CLEAR_FEATURE = 1.
 */
#define DW_IIC_INTR_MASK_M_SCL_STUCK_AT_LOW                 (1UL << 14)
/*! This bit masks the R_MST_ON_HOLD interrupt bit in the IC_INTR_STAT register.
 */
#define DW_IIC_INTR_MASK_M_MST_ON_HOLD                      (1UL << 13)
/*! This bit masks the R_RESTART_DET interrupt status bit in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_RESTART_DET                      (1UL << 12)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_GEN_CALL                         (1UL << 11)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_START_DET                        (1UL << 10)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_STOP_DET                         (1UL << 9)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_ACTIVITY                         (1UL << 8)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_RX_DONE                          (1UL << 7)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_TX_ABRT                          (1UL << 6)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_RD_REQ                           (1UL << 5)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_TX_EMPTY                         (1UL << 4)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_TX_OVER                          (1UL << 3)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_RX_FULL                          (1UL << 2)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_RX_OVER                          (1UL << 1)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK_M_RX_UNDER                         (1UL << 0)
/*! These bits mask their corresponding interrupt status bits in the IC_INTR_STAT register
 */
#define DW_IIC_INTR_MASK(n)                                 (((n)&0x7FFF) << 0)


/***** IC_RAW_INTR_STAT(IIC Raw Interrupt Status Register) *****/
/*! Indicates whether the SCL Line is stuck at low for the IC_SCL_STUCK_LOW_TIMOUT number 
 *  of ic_clk periods. Enabled only when IC_BUS_CLEAR_FEATURE = 1
 */
#define DW_IIC_RAW_INTR_STAT_SCL_STUCK_AT_LOW               (1UL << 14)
/*! Indicates whether a master is holding the bus and the Tx FIFO is empty. Enabled only 
 *  when I2C_DYNAMIC_TAR_UPDATE = 1 and IC_EMPTYFIFO_HOLD_MASTER_EN = 1
 */
#define DW_IIC_RAW_INTR_STAT_MST_ON_HOLD                    (1UL << 13)
/*! Indicates whether a RESTART condition has occurred on the I2C interface when DW_apb_i2c 
 *  is operating in slave mode and the slave is the addressed slave.Enabled only when 
 *  IC_SLV_RESTART_DET_EN = 1
 */
#define DW_IIC_RAW_INTR_STAT_RESTART_DET                    (1UL << 12)
/*! Set only when a General Call address is received and it is acknowledged. It stays set 
 *  until it is cleared either by disabling DW_apb_i2c or when the CPU reads bit 0 of the 
 *  IC_CLR_GEN_CALL register. DW_apb_i2c stores the received data in the Rx buffer.
 */
#define DW_IIC_RAW_INTR_STAT_GEN_CALL                       (1UL << 11)
/*! Indicates whether a START or RESTART condition has occurred on the I2C interface regardless 
 *  of whether DW_apb_i2c is operating in slave or master mode
 */
#define DW_IIC_RAW_INTR_STAT_START_DET                      (1UL << 10)
/*! Indicates whether a STOP condition has occurred on the I2C interface regardless of whether 
 *  DW_apb_i2c is operating in slave or master mode
 */
#define DW_IIC_RAW_INTR_STAT_STOP_DET                       (1UL << 9)
/*! This bit captures DW_apb_i2c activity and stays set until it is cleared
 */
#define DW_IIC_RAW_INTR_STAT_ACTIVITY                       (1UL << 8)
/*! When the DW_apb_i2c is acting as a slave-transmitter, this bit is set to 1 if the master 
 *  does not acknowledge a transmitted byte. This occurs on the last byte of the transmission, 
 *  indicating that the transmission is done
 */
#define DW_IIC_RAW_INTR_STAT_RX_DONE                        (1UL << 7)
/*! This bit indicates if DW_apb_i2c, as an I2C transmitter, is unable to complete the intended 
 *  actions on the contents of the transmit FIFO. This situation can occur both as an I2C master 
 *  or an I2C slave, and is referred to as a "Transmit abort"
 */
#define DW_IIC_RAW_INTR_STAT_TX_ABRT                        (1UL << 6)
/*! This bit is set to 1 when DW_apb_i2c is acting as a slave and another I2C master is attempting 
 *  to read data from DW_apb_i2c. The DW_apb_i2c holds the I2C bus in a wait state (SCL=0) until 
 *  this interrupt is serviced, which means that the slave has been addressed by a remote master 
 *  that is asking for data to be transferred. The processor must respond to this interrupt and then 
 *  write the requested data to the IC_DATA_CMD register. This bit is set to 0 just after the processor 
 *  reads the IC_CLR_RD_REQ register.
 */
#define DW_IIC_RAW_INTR_STAT_RD_REQ                         (1UL << 5)
/*! The behavior of the TX_EMPTY interrupt status differs based on the TX_EMPTY_CTRL selection in the 
 *  IC_CON register.
 */
#define DW_IIC_RAW_INTR_STAT_TX_EMPTY                       (1UL << 4)
/*! Set during transmit if the transmit buffer is filled to IC_TX_BUFFER_DEPTH and the processor attempts 
 *  to issue another I2C command by writing to the IC_DATA_CMD register. When the module is disabled, this 
 *  bit keeps its level until the master or slave state machines go into idle, and when ic_en goes to 0, 
 *  this interrupt is cleared
 */
#define DW_IIC_RAW_INTR_STAT_TX_OVER                        (1UL << 3)
/*! Set when the receive buffer reaches or goes above the RX_TL threshold in the IC_RX_TL register. It is 
 *  automatically cleared by hardware when buffer level goes below the threshold. If the module is disabled 
 *  (IC_ENABLE[0]=0), the RX FIFO is flushed and held in reset; therefore the RX FIFO is not full. So this 
 *  bit is cleared once IC_ENABLE[0] is set to 0, regardless of the activity that continues.
 */
#define DW_IIC_RAW_INTR_STAT_RX_FULL                        (1UL << 2)
/*! Set if the receive buffer is completely filled to IC_RX_BUFFER_DEPTH and an additional byte is received 
 *  from an external I2C device. The DW_apb_i2c acknowledges this, but any data bytes received after the FIFO
 *  is full are lost. If the module is disabled (IC_ENABLE[0]=0), this bit keeps its level until the master 
 *  or slave state machines go into idle, and when ic_en goes to 0, this interrupt is cleared.
 */
#define DW_IIC_RAW_INTR_STAT_RX_OVER                        (1UL << 1)
/*! Set if the processor attempts to read the receive buffer when it is empty by reading from the IC_DATA_CMD 
 *  register. If the module is disabled (IC_ENABLE[0]=0), this bit keeps its level until the master or slave 
 *  state machines go into idle, and when ic_en goes to 0, this interrupt is cleared.
 */
#define DW_IIC_RAW_INTR_STAT_RX_UNDER                       (1UL << 0)


/***** IC_RX_TL(IIC Receive FIFO Threshold Register) *****/
/*! Receive FIFO Threshold Level Controls the level of entries (or above) that triggers 
 *  the DW_IIC_RX_FULL interrupt(bit 2 in DW_IIC_IC_RAW_INTR_STAT register)
 */
#define DW_IIC_RX_TL(n)                                     (((n)&0xFF ) << 0)


/***** IC_TX_TL(IIC Transmit FIFO Threshold Register) *****/
/*! Transmit FIFO Threshold Level Controls the level of entries (or below) that trigger 
 *  the DW_IIC_TX_EMPTY interrupt(bit 4 in DW_IIC_IC_RAW_INTR_STAT register)
 */
#define DW_IIC_TX_TL(n)                                     (((n)&0xFF) << 0)


/***** IC_CLR_INTR(Clear Combined and Individual Interrupt Register) *****/
/*! Read this register to clear the combined interrupt, all individual interrupts, and 
 *  the DW_IIC_IC_TX_ABRT_SOURCE register
 */
#define DW_IIC_IC_CLR_INTR                                  (1UL << 0)


/***** IC_CLR_RX_UNDER(Clear RX_UNDER Interrupt Register) *****/
/*! Read this register to clear the RX_UNDER interrupt (bit 0) of the DW_IIC_IC_RAW_INTR_STAT 
 *  register
 */
#define DW_IIC_IC_CLR_RX_UNDER                              (1UL << 0)


/***** IC_CLR_RX_OVER(Clear RX_OVER Interrupt Register) *****/
/*! Read this register to clear the RX_OVER interrupt (bit 1) of the DW_IIC_IC_RAW_INTR_STAT 
 *  register 
 */
#define DW_IIC_IC_CLR_RX_OVER                               (1UL << 0)


/***** IC_CLR_TX_OVER(Clear TX_OVER Interrupt Register) *****/
/*! Read this register to clear the TX_OVER interrupt (bit 3) of the IC_RAW_INTR_STAT register 
 */
#define DW_IIC_IC_CLR_TX_OVER                               (1UL << 0)


/***** IC_CLR_RD_REQ(Clear RD_REQ Interrupt Register) *****/
/*! Read this register to clear the RD_REQ interrupt (bit 5) of the IC_RAW_INTR_STAT register. 
 */
#define DW_IIC_IC_CLR_RD_REQ                                (1UL << 0)


/***** IC_CLR_TX_ABRT(Clear TX_ABRT Interrupt Register) *****/
/*! Read this register to clear the TX_ABRT interrupt (bit 6) of the DW_IIC_IC_RAW_INTR_STAT 
 *  register, and the IC_TX_ABRT_SOURCE register.
  */
#define DW_IIC_IC_CLR_TX_ABRT                               (1UL << 0)


/***** IC_CLR_RX_DONE(Clear RX_DONE Interrupt Register) *****/
/*! Read this register to clear the RX_DONE interrupt (bit 7) of the DW_IIC_IC_RAW_INTR_STAT 
 *  register 
 */
#define DW_IIC_IC_CLR_RX_DONE                               (1UL << 0)


/***** IC_CLR_ACTIVITY(Clear ACTIVITY Interrupt Register) *****/
/*! Read this register clears the ACTIVITY interrupt if the I2C is not active anymore
 */
#define DW_IIC_IC_CLR_ACTIVITY                              (1UL << 0)


/***** IC_CLR_STOP_DET(Clear STOP_DET Interrupt Register) *****/
/*! Read this register to clear the STOP_DET interrupt (bit 9) of the DW_IIC_IC_RAW_INTR_STAT 
 *  register
 */
#define DW_IIC_IC_CLR_STOP_DET                              (1UL << 0)


/***** IC_CLR_START_DET(Clear START_DET Interrupt Register) *****/
/*! Read this register to clear the START_DET interrupt (bit 10) of the DW_IIC_IC_RAW_INTR_STAT 
 *  register
 */
#define DW_IIC_IC_CLR_START_DET                             (1UL << 0)


/***** IC_CLR_GEN_CALL(Clear GEN_CALL Interrupt Register) *****/
/*! Read this register to clear the GEN_CALL interrupt (bit 11) of DW_IIC_IC_RAW_INTR_STAT 
 *  register
 */
#define DW_IIC_IC_CLR_GEN_CALL                              (1UL << 0)


/***** IC_ENABLE(IIC Enable Register) *****/
/*! The SMBUS_ALERT_CTRL register bit is used to control assertion of SMBALERT signal
 */
#define DW_IIC_ENABLE_SMBUS_ALERT_EN                        (1UL << 18)
/*! The DW_IIC_SMBUS_SUSPEND_EN register bit is used to control assertion and deassertion of 
 *  SMBSUS signal
 */
#define DW_IIC_ENABLE_SMBUS_SUSPEND_EN                      (1UL << 17)
/*! This bit is used in SMBus Host mode to initiate the SMBus Master Clock Reset
 */
#define DW_IIC_ENABLE_SMBUS_CLK_RESET                       (1UL << 16)
/*! If SDA is stuck at low indicated through the TX_ABORT interrupt (IC_TX_ABRT_SOURCE[17]), 
 *  this bit is used as a control knob to initiate the SDA Recovery Mechanism (that is, send 
 *  at most 9 SCL clocks and STOP to release the SDA line) and then this bit gets auto clear
 */
#define DW_IIC_ENABLE_SDA_STUCK_RECOVERY_ENABLE             (1UL << 3)
/*! In Master mode: 1: Blocks the transmission of data on I2C bus even if Tx FIFO has data to 
 *  transmit; 0: The transmission of data starts on I2C bus automatically, as soon as the 
 *  first data is available in the Tx FIFO
 */
#define DW_IIC_ENABLE_TX_CMD_BLOCK                          (1UL << 2)
/*! When set, the controller initiates the transfer abort
 */
#define DW_IIC_ENABLE_ABORT                                 (1UL << 1)
/*! Controls whether the DW_apb_i2c is enabled
 */
#define DW_IIC_ENABLE                                       (1UL << 0)


/***** IC_STATUS(IIC Status Register, RO) *****/
/*! This bit indicates whether the status of the input signal is ic_smbus_alert_in_n. 
 *  This signal is asserted when the SMBus Alert signal is asserted by the SMBus Device
 */
#define DW_IIC_STATUS_SMBUS_ALERT_STATUS                    (1UL << 20)
/*! This bit indicates whether the status of the input signal is ic_smbus_sus_in_n. 
 *  This signal is asserted when the SMBus Suspend signal is asserted by the SMBus Host
 */
#define DW_IIC_STATUS_SMBUS_SUSPEND_STATUS                  (1UL << 19)
/*! This bit indicates whether the SMBus Slave address (ic_sar[6:0]) is Resolved by ARP Master
 */
#define DW_IIC_STATUS_SMBUS_SLAVE_ADDR_RESOLVED             (1UL << 18)
/*! This bit indicates whether the SMBus Slave address (ic_sar[6:0]) is valid or not
 */ 
#define DW_IIC_STATUS_SMBUS_SLAVE_ADDR_VALID                (1UL << 17)
/*! This bit indicates the R/W bit of the Quick command received. This bit will be cleared 
 *  after the user has read this bit
 */
#define DW_IIC_STATUS_SMBUS_QUICK_CMD_BIT                   (1UL << 16)
/*! This bit indicates that an SDA stuck at low is not recovered after the recovery mechanism.
 *  This bit is enabled only when DW_IIC_IC_BUS_CLEAR_FEATURE = 1
 */
#define DW_IIC_STATUS_SDA_STUCK_NOT_RECOVERED               (1UL << 11)
/*! This bit indicates the BUS Hold in Slave mode due to the Rx FIFO being Full and an 
 *  additional byte being received (this kind of Bus hold is applicable if 
 *  DW_IIC_IC_RX_FULL_HLD_BUS_EN is set to 1)
 */
#define DW_IIC_STATUS_SLV_HOLD_RX_FIFO_FULL                 (1UL << 10)
/*! This bit indicates the BUS Hold in Slave mode for the Read request when the Tx FIFO is 
 *  empty. The Bus is in hold until the Tx FIFO has data to Transmit for the read request.
 */
#define DW_IIC_STATUS_SLV_HOLD_TX_FIFO_EMPTY                (1UL << 9)
/*! This bit indicates the BUS Hold in Master mode due to Rx FIFO is Full and additional byte 
 *  has been received(This kind of Bus hold is applicable if DW_IIC_IC_RX_FULL_HLD_BUS_EN is 
 *  set to 1)
 */
#define DW_IIC_STATUS_MST_HOLD_RX_FIFO_FULL                 (1UL << 8)
/*! This bit indicates the BUS hold when the master holds the bus because of the Tx FIFO being 
 *  empty, and the the previous transferred command does not have the Stop bit set. 
 *  (This kind of Bus hold is applicable if DW_IIC_IC_EMPTYFIFO_HOLD_MASTER_EN is set to 1)
 */
#define DW_IIC_STATUS_MST_HOLD_TX_FIFO_EMPTY                (1UL << 7)
/*! Slave FSM Activity Status. When the Slave Finite State Machine (FSM) is not in the IDLE 
 *  state, this bit is set
 */
#define DW_IIC_STATUS_SLV_ACTIVITY                          (1UL << 6)
/*! Master FSM Activity Status. When the Master Finite State Machine (FSM) is not in the IDLE 
 *  state, this bit is set
 */
#define DW_IIC_STATUS_MST_ACTIVITY                          (1UL << 5)
/*! Receive FIFO Completely Full. When the receive FIFO is completely full, this bit is set. 
 *  When the receive FIFO contains one or more empty location, this bit is cleared
 */
#define DW_IIC_STATUS_RFF                                   (1UL << 4)
/*! Receive FIFO Not Empty. This bit is set when the receive FIFO contains one or more entries; 
 *  it is cleared when the receive FIFO is empty
 */
#define DW_IIC_STATUS_RFNE                                  (1UL << 3)
/*! Transmit FIFO Completely Empty. When the transmit FIFO is completely empty, this bit is set. 
 *  When it contains one or more valid entries, this bit is cleared. This bit field does not 
 *  request an interrupt
 */
#define DW_IIC_STATUS_TFE                                   (1UL << 2)
/*! Transmit FIFO Not Full. Set when the transmit FIFO contains one or more empty locations, 
 *  and is cleared when the FIFO is full
 */
#define DW_IIC_STATUS_TFNF                                  (1UL << 1)
/*! I2C Activity Status
 */
#define DW_IIC_STATUS_ACTIVITY                              (1UL << 0)


/***** IC_DMA_CR(IIC DMA Control Register, RW) *****/
/*! This bit enables/disables the transmit FIFO DMA channel.
 */
#define DW_IIC_DMA_CR_TDMAE                                 (1UL << 1)
/*! This bit enables/disables the receive FIFO DMA channel. 
 */
#define DW_IIC_DMA_CR_RDMAE                                 (1UL << 0)


/***** IC_DMA_TDLR(IIC DMA Transmit Data Level Register) *****/
/*! Transmit Data Level. This bit field controls the level at which a DMA request is made by the 
 *  transmit logic. It is equal to the watermark level; that is, the dma_tx_req signal is generated 
 *  when the number of valid data entries in the transmit FIFO is equal to or below this field value,
 *  and TDMAE = 1
 */
#define DW_IIC_DMA_TDLR(n)                                  (((n)&0xFF) << 0)


/***** IC_DMA_RDLR(IIC DMA Receive Data Level Register) *****/
/*! Receive Data Level. This bit field controls the level at which a DMA request is made by the 
 *  receive logic. The watermark level = DMARDL+1; that is, dma_rx_req is generated when the number 
 *  of valid data entries in the receive FIFO is equal to or more than this field value + 1, and 
 *  RDMAE = 1. For instance, when DMARDL is 0, then dma_rx_req is asserted when 1 or more data entries
 *  are present in the receive FIFO.
 */
#define DW_IIC_DMA_RDLR(n)                                  (((n)&0xFF) << 0)


/***** IC_SDA_SETUP(IIC SDA Setup Register) *****/
/*! SDA Setup. It is recommended that if the required delay is 1000ns, then for an ic_clk frequency of 
 *  10 MHz, IC_SDA_SETUP should be programmed to a value of 11. IC_SDA_SETUP must be programmed with a 
 *  minimum value of 2 
 */
#define DW_IIC_SDA_SETUP(n)                                 (((n)&0xFF) << 0)


/***** IC_ACK_GENERAL_CALL(IIC ACK General Call Register) *****/
/*! ACK General Call. When set to 1, DW_apb_i2c responds with a ACK (by asserting ic_data_oe) when 
 *  it receives a General Call. When set to 0, the DW_apb_i2c does not generate General Call interrupts 
 */
#define DW_IIC_ACK_GEN_CALL                                 (1UL << 0)


/***** IC_ENABLE_STATUS(IIC Enable Status Register) *****/
/*! Slave Received Data Lost. This bit indicates if a Slave-Receiver operation has been aborted with 
 *  at least one data byte received from an I2C transfer due to setting IC_ENABLE[0] from 1 to 0 
 */
#define DW_IIC_SLV_RX_DATA_LOST                             (1UL << 2)
/*! Slave Disabled While Busy (Transmit, Receive). This bit indicates if a potential or active Slave 
 *  operation has been aborted due to setting bit 0 of the IC_ENABLE register from 1 to 0.  
 */
#define DW_IIC_SLV_DISABLED_WHILE_BUSY                      (1UL << 1)
/*! ic_en Status. This bit always reflects the value driven on the output port ic_en. 
 */
#define DW_IIC_IC_EN                                        (1UL << 0)


/***** IC_FS_SPKLEN(IIC SS and FS Spike Suppression Limit Register) *****/
/*! This register must be set before any I2C bus transaction can take place to ensure stable operation. 
 *  This register sets the duration, measured in ic_clk cycles, of the longest spike in the SCL or SDA 
 *  lines that are filtered out by the spike suppression logic; 
 */
#define DW_IIC_IC_FS_SPKLEN(n)                              (((n)&0xFF) << 0)


/***** IC_HS_SPKLEN(IIC HS Spike Suppression Limit Register) *****/
/*! This register must be set before any I2C bus transaction can take place to ensure stable operation.
 *  This register sets the duration, measured in ic_clk cycles, of the longest spike in the SCL or SDA 
 *  lines that are filtered out by the spike suppression logic;  
 */
#define DW_IIC_IC_HS_SPKLEN(n)                              (((n)&0xFF) << 0)


/***** IC_CLR_RESTART_DET(IIC Clear RESTART_DET Interrupt Register) *****/
/*!  Read this register to clear the RESTART_DET interrupt (bit 12) of the IC_RAW_INTR_STAT register.  
 */
#define DW_IIC_CLR_RESTART_DET                              (1UL << 0)


/***** IC_COMP_PARAM_1(IIC Component Parameter Register 1) *****/
/*! The value of this register is derived from the IC_TX_BUFFER_DEPTH coreConsultant parameter.
 */
#define DW_IIC_TX_BUFFER_DEPTH(n)                           (((n)&0xFF) << 16)
/*! The value of this register is derived from the IC_RX_BUFFER_DEPTH coreConsultant parameter 
*/
#define DW_IIC_RX_BUFFER_DEPTH(n)                           (((n)&0xFF) << 8)
/*! The value of this register is derived from the IC_ADD_ENCODED_PARAMS coreConsultant parameter. 
 */
#define DW_IIC_ADD_ENCODED_PARAMS                           (1UL << 7)
/*! The value of this register is derived from the IC_HAS_DMA coreConsultant parameter. 
 */
#define DW_IIC_HAS_DMA                                      (1UL << 6)
/*! The value of this register is derived from the IC_INTR_IO coreConsultant parameter. 
 */
#define DW_IIC_INTR_IO                                      (1UL << 5)

/*! The value of this register is derived from the IC_HC_COUNT_VALUES coreConsultant parameter.  
 */
#define DW_IIC_HC_COUNT_VALUES                              (1UL << 4)

/*! The value of this register is derived from the IC_MAX_SPEED_MODE coreConsultant parameter. 
 */
#define DW_IIC_MAX_SPEED_MODE(n)                            (((n)&0x3) << 2)

/*! The value of this register is derived from the APB_DATA_WIDTH coreConsultant parameter 
 */
#define DW_IIC_APB_DATA_WIDTH(n)                            (((n)&0x3) << 0)


/***** IC_COMP_VERSION(IIC Component Version Register) *****/
/*! Specific values for this register are described in the Releases Table in the AMBA 2 release 
 *  notes 
 */
#define DW_IIC_IC_COMP_VERSION(n)                           (((n)&0xFFFFFFFF) << 0)


/***** IC_COMP_TYPE(IIC Component Type Register) *****/
/*! Designware Component Type number = 0x44_57_01_40. This assigned unique hex value is constant 
 *  and is derived from the two ASCII letters "DW" followed by a 16-bit unsigned number
 */
#define DW_IIC_ IC_COMP_TYPE(n)                             (((n)&0xFFFFFFFF) << 0)


/***** IC_SCL_STUCK_AT_LOW_TIMEOUT(IIC SCL Stuck at Low Timeout) *****/
/*! DW_apb_i2c generates the interrupt to indicate SCL stuck at low if it detects the SCL stuck 
 *  at low for the IC_SCL_STUCK_LOW_TIMEOUT in units of ic_clk period 
 */
#define DW_IIC_IC_SCL_STUCK_LOW_TIMEOUT(n)                  (((n)&0xFFFFFFFF) << 0)


/***** IC_SDA_STUCK_AT_LOW_TIMEOUT(IIC SDA Stuck at Low Timeout) *****/
/*! DW_apb_i2c initiates the recovery of SDA line through enabling the SDA_STUCK_RECOVERY_EN 
 *  (IC_ENABLE[3]) register bit, if it detects the SDA stuck at low for the IC_SDA_STUCK_LOW_TIMEOUT 
 *  in units of ic_clk period.  
 */
#define DW_IIC_IC_SDA_STUCK_LOW_TIMEOUT(n)                  (((n)&0xFFFFFFFF) << 0)


/***** IC_CLR_SCL_STUCK_DET(IIC Clear SCL Stuck at Low Detect Interrupt Register) *****/
/*! Read this register to clear the SCL_STUCK_DET interrupt (bit 14) of the IC_RAW_INTR_STAT register 
 */
#define DW_IIC_CLR_SCL_STUCK                                (1UL << 0)


/***** IC_DEVICE_ID(IIC Device ID) *****/
/*! Contains the Device-ID of the component assigned through the configuration parameter IC_DEVICE_ID_VALUE 
 */
#define DW_IIC_DEVICE_ID(n)                                 (((n)&0xFFFFFF) << 0)


/***** IC_UFM_SCL_HCNT(IIC Ultra-Fast mode IIC Clock High Count Register) *****/
/*! This register must be set before any I2C bus transaction can take place to ensure proper I/O timing.
 *  This register sets the SCL clock high-period count for Ultra-Fast speed 
 */
#define DW_IIC_IC_UFM_SCL_HCNT(n)                           (((n)&0xFFFF) << 0)


/***** IC_UFM_SCL_LCNT(IIC Ultra-Fast mode IIC Clock Low Count Register) *****/
/*! This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. 
 *  This register sets the SCL clock low-period count for Ultra-Fast speed. 
 */
#define DW_IIC_IC_UFM_SCL_LCNT(n)                           (((n)&0xFFFF) << 0)


/***** IC_UFM_SPKLEN(IIC Ultra-Fast mode Spike suppression Register) *****/
/*! This register must be set before any I2C bus transaction can occur to ensure stable operation. 
 *  This register sets the duration, measured in ic_clk cycles, of the longest spike in the SCL or SDA 
 *  lines that are filtered out by the spike suppression logic. 
 */
#define DW_IIC_IC_UFM_SPKLEN(n)                             (((n)&0xFF) << 0)


/***** IC_UFM_TBUF_CNT(IIC Ultra-Fast mode TBuf Idle Count Register) *****/
/*! This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. 
 *  This register sets the tBuf Idle time count for Ultra-Fast speed.
 */
#define DW_IIC_IC_UFM_TBUF_CNT(n)                           (((n)&0xFFFF) << 0)


/***** IC_SMBUS_CLOCK_LOW_SEXT(IIC SMBUS Slave Clock Extend Timeout Register) *****/
/*! This field is used to detect the Slave Clock Extend timeout (tLOW:SEXT) in master mode extended by 
 *  the slave device in one message from the initial START to the STOP. 
 */
#define DW_IIC_SMBUS_CLK_LOW_SEXT_TIMEOUT(n)                (((n)&0xFFFFFFFF) << 0)


/***** IC_SMBUS_CLOCK_LOW_MEXT(IIC SMBUS Master extend clock Timeout Register) *****/
/*! This field is used to detect the Master extend SMBus clock (SCL) timeout defined from START-to-ACK, 
 *  ACK-to-ACK, or ACK-to-STOP in Master mode. 
 */
#define DW_IIC_SMBUS_CLK_LOW_MEXT_TIMEOUT(n)                (((n)&0xFFFFFFFF) << 0)


/***** IC_SMBUS_THIGH_MAX_IDLE_COUNT (IIC SMBus Thigh MAX Bus-Idle count Register) *****/
/*! This field is used to set the required Bus-Idle time period used when a master has been dynamically
 *  added to the bus and may not have detected a state transition on the SMBCLK or SMBDAT lines.
 */
#define DW_IIC_SMBUS_THIGH_MAX_BUS_IDLE_CNT(n)              (((n)&0xFFFF) << 0)


/***** IC_SMBUS_INTR_STAT(IIC I2C SMBUS Interrupt Status Register) *****/
/*! See IC_SMBUS_INTR_RAW_STATUS for a detailed description of this bit. 
 */
#define DW_IIC_R_SMBUS_ALERT_DET                            (1UL << 10) 
/*! See IC_SMBUS_INTR_RAW_STATUS for a detailed description of this bit 
 */
#define DW_IIC_R_SMBUS_SUSPEND_DET                          (1UL << 9)
/*! See IC_SMBUS_INTR_RAW_STATUS for a detailed description of this bit 
 */
#define DW_IIC_R_SLV_RX_PEC_NACK                            (1UL << 8)
/*! See IC_SMBUS_INTR_RAW_STATUS for a detailed description of this bit 
 */
#define DW_IIC_R_ARP_ASSGN_ADDR_CMD_DET                     (1UL << 7)
/*! See IC_SMBUS_INTR_RAW_STATUS for a detailed description of this bit 
 */
#define DW_IIC_R_ARP_GET_UDID_CMD_DET                       (1UL << 6)
/*! See IC_SMBUS_INTR_RAW_STATUS for a detailed description of this bit 
 */
#define DW_IIC_R_ARP_RST_CMD_DET                            (1UL << 5)
/*! See IC_SMBUS_INTR_RAW_STATUS for a detailed description of this bit 
 */
#define DW_IIC_R_ARP_PREPARE_CMD_DET                        (1UL << 4)
/*! See IC_SMBUS_INTR_RAW_STATUS for a detailed description of this bit 
 */
#define DW_IIC_R_HOST_NOTIFY_MST_DET                        (1UL << 3)
/*! See IC_SMBUS_INTR_RAW_STATUS for a detailed description of this bit 
 */
#define DW_IIC_R_QUICK_CMD_DET                              (1UL << 2)
/*! See IC_SMBUS_INTR_RAW_STATUS for a detailed description of this bit 
 */
#define DW_IIC_R_MST_CLOCK_EXTND_TIMEOUT                    (1UL << 1)
/*! See IC_SMBUS_INTR_RAW_STATUS for a detailed description of this bit 
 */
#define DW_IIC_R_SLV_CLOCK_EXTND_TIMEOUT                    (1UL << 0)


/***** IC_SMBUS_INTR_MASK(IIC Interrupt Mask Register) *****/
/*! This bit masks the R_SMBUS_ALERT_DET interrupt bit in the IC_SMBUS_INTR_STAT register. This bit 
 *  is enabled only when IC_SMBUS_SUSPEND_ALERT=1.
 */
#define DW_IIC_M_SMBUS_ALERT_DET                            (1UL << 10)
/*! This bit masks the R_SMBUS_SUSPEND_DET interrupt bit in the IC_SMBUS_INTR_STAT register. This bit 
 *  is enabled only when IC_SMBUS_SUSPEND_ALERT=1.
 */
#define DW_IIC_M_SMBUS_SUSPEND_DET                          (1UL << 9)
/*! This bit masks the R_SLV_RX_PEC_NACK interrupt bit in the IC_SMBUS_INTR_STAT register. This bit 
 *  is enabled only when IC_SMBUS_SUSPEND_ALERT=1.
 */
#define DW_IIC_M_SLV_RX_PEC_NACK                            (1UL << 8)
/*! This bit masks the R_ARP_ASSGN_ADDR_CMD_DET interrupt bit in the IC_SMBUS_INTR_STAT register. 
 *  This bit is enabled only when IC_SMBUS_SUSPEND_ALERT=1.
 */
#define DW_IIC_M_ARP_ASSGN_ADDR_CMD_DET                     (1UL << 7)
/*! This bit masks the R_ARP_GET_UDID_CMD_DET interrupt bit in the IC_SMBUS_INTR_STAT register. This bit 
 *  is enabled only when IC_SMBUS_SUSPEND_ALERT=1.
 */
#define DW_IIC_M_ARP_GET_UDID_CMD_DET                       (1UL << 6)
/*! This bit masks the R_ARP_RST_CMD_DET interrupt bit in the IC_SMBUS_INTR_STAT register. This bit 
 *  is enabled only when IC_SMBUS_SUSPEND_ALERT=1.
 */
#define DW_IIC_M_ARP_RST_CMD_DET                            (1UL << 5)
/*! This bit masks the R_ARP_PREPARE_CMD_DET interrupt bit in the IC_SMBUS_INTR_STAT register. This bit 
 *  is enabled only when IC_SMBUS_SUSPEND_ALERT=1.
 */
#define DW_IIC_M_ARP_PREPARE_CMD_DET                        (1UL << 4)
/*! This bit masks the R_HOST_NOTIFY_MST_DET interrupt bit in the IC_SMBUS_INTR_STAT register. This bit 
 *  is enabled only when IC_SMBUS_SUSPEND_ALERT=1.
 */
#define DW_IIC_M_HOST_NOTIFY_MST_DET                        (1UL << 3)
/*! This bit masks the R_QUICK_CMD_DET interrupt bit in the IC_SMBUS_INTR_STAT register. This bit 
 *  is enabled only when IC_SMBUS_SUSPEND_ALERT=1.
 */
#define DW_IIC_M_QUICK_CMD_DET                              (1UL << 2)
/*! This bit masks the R_MST_CLOCK_EXTND_TIMEOUT interrupt bit in the IC_SMBUS_INTR_STAT register. 
 *  This bit is enabled only when IC_SMBUS_SUSPEND_ALERT=1.
 */
#define DW_IIC_M_MST_CLOCK_EXTND_TIMEOUT                    (1UL << 1)
/*! This bit masks the R_SLV_CLOCK_EXTND_TIMEOUT interrupt bit in the IC_SMBUS_INTR_STAT register.
 *  This bit is enabled only when IC_SMBUS_SUSPEND_ALERT=1.
 */
#define DW_IIC_M_SLV_CLOCK_EXTND_TIMEOUT                    (1UL << 0)


/***** IC_SMBUS_INTR_RAW_STATUS(IIC SMBUS Raw Interrupt Status Register) *****/
/*! Indicates whether a SMBALERT (ic_smbalert_in_n) signal is driven low by the slave 
 */
#define DW_IIC_SMBUS_ALERT_DET                              (1UL << 10)
/*! Indicates whether a SMBSUS (ic_smbsus_in_n) signal is driven low by the Host 
 */
#define DW_IIC_SMBUS_SUSPEND_DET                            (1UL << 9)
/*! Indicates whether a Slave generates a NACK for the PEC Byte of the ARP command from the slave 
 */
#define DW_IIC_SLV_RX_PEC_NACK                              (1UL << 8)
/*! Indicates whether an Assign Address ARP command has been received 
 */
#define DW_IIC_ARP_ASSGN_ADDR_CMD_DET                       (1UL << 7)
/*! Indicates whether a General or directed Get UDID ARP command has been received. 
 */
#define DW_IIC_ARP_GET_UDID_CMD_DET                         (1UL << 6)
/*! Indicates whether a General or Directed Reset ARP command has been received.
 */
#define DW_IIC_ARP_RST_CMD_DET                              (1UL << 5)
/*! Indicates whether a Prepare to ARP command has been received.
 */
#define DW_IIC_ARP_PREPARE_CMD_DET                          (1UL << 4)
/*! Indicates whether a Host Notify command has been received. 
 */
#define DW_IIC_HOST_NTFY_MST_DET                            (1UL << 3)
/*! Indicates whether a Quick command has been received on the SMBus interface regardless of whether 
 *  DW_apb_i2c is operating in slave or master mode. This bit is enabled only when IC_SMBUS=1 is set 
 *  to 1 
 */
#define DW_IIC_QUICK_CMD_DET                                (1UL << 2)
/*! Indicates whether the Master device transaction (START-to-ACK, ACK-to-ACK, or ACK-to-STOP) from 
 *  START to STOP exceeds IC_SMBUS_CLOCK_LOW_MEXT time in each byte of message.
 */
#define DW_IIC_MST_CLOCK_EXTND_TIMEOUT                      (1UL << 1)
/*! Indicates whether the transaction from Slave (that is, from START to STOP) exceeds 
 *  IC_SMBUS_CLOCK_LOW_SEXT time.
 */
#define DW_IIC_SLV_CLOCK_EXTND_TIMEOUT                      (1UL << 0)


/***** IC_CLR_SMBUS_INTR(IIC Clear SMBUS Interrupt Register) *****/
/*! Write this register to clear the SMBUS_ALERT_DET interrupt (bit 10) of the IC_SMBUS_RAW_INTR_STAT 
 *  register
 */
#define DW_IIC_CLR_SMBUS_ALERT_DET                          (1UL << 10)
/*! Write this register to clear the R_SMBUS_SUSPEND_DET interrupt (bit 9) of the IC_SMBUS_RAW_INTR_STAT 
 *  register
 */
#define DW_IIC_CLR_SMBUS_SUSPEND_DET                        (1UL << 9)
/*! Write this register to clear the SLV_RX_PEC_NACK interrupt (bit 8) of the IC_SMBUS_RAW_INTR_STAT 
 *  register.
 */
#define DW_IIC_CLR_SLV_RX_PEC_NACK                          (1UL << 8)
/*! Write this register to clear the ARP_ASSGN_ADDR_CMD_DET interrupt (bit 7) of the IC_SMBUS_RAW_INTR_STAT 
 *  register.
 */
#define DW_IIC_CLR_ARP_ASSGN_ADDR_CMD_DET                   (1UL << 7)
/*! Write this register to clear the ARP_GET_UDID_CMD_DET interrupt (bit 6) of the IC_SMBUS_RAW_INTR_STAT 
 *  register.
 */
#define DW_IIC_CLR_ARP_GET_UDID_CMD_DET                     (1UL << 6)
/*! Write this register to clear the ARP_RST_CMD_DET interrupt (bit 5) of the IC_SMBUS_RAW_INTR_STAT 
 *  register.
 */
#define DW_IIC_CLR_ARP_RST_CMD_DET                          (1UL << 5)
/*! Write this register to clear the ARP_PREPARE_CMD_DET interrupt (bit 4) of the IC_SMBUS_RAW_INTR_STAT 
 *  register
 */
#define DW_IIC_CLR_ARP_PREPARE_CMD_DET                      (1UL << 4)
/*! Write this register to clear the HOST_NOTIFY_MST_DET interrupt (bit 3) of the IC_SMBUS_RAW_INTR_STAT 
 *  register.
 */
#define DW_IIC_CLR_HOST_NTFY_MST_DET                        (1UL << 3)
/*! Write this register to clear the QUICK_CMD_DET interrupt (bit 2) of the IC_SMBUS_RAW_INTR_STAT 
 *  register.
 */
#define DW_IIC_CLR_QUICK_CMD_DET                            (1UL << 2)
/*! Write this register to clear the MST_CLOCK_EXTND_TIMEOUT interrupt (bit 1) of the IC_SMBUS_RAW_INTR_STAT 
 *  register.
 */
#define DW_IIC_CLR_MST_CLOCK_EXTND_TIMEOUT                  (1UL << 1)
/*! Write this register to clear the SLV_CLOCK_EXTND_TIMEOUT interrupt (bit 0) of the IC_SMBUS_RAW_INTR_STAT
 *  register.
 */
#define DW_IIC_CLR_SLV_CLOCK_EXTND_TIMEOUT                  (1UL << 0)


/***** IC_OPTIONAL_SAR(IIC Optional Slave Address Register) *****/
/*! Optional Slave address for DW_apb_i2c when operating as a slave in SMBus Mode.  
 */
#define DW_IIC_IC_OPTIONAL_SAR(n)                           (((n)&0x7F) << 0)


/***** IC_SMBUS_UDID_LSB(IIC SMBUS ARP UDID LSB Register) *****/
/*! This field is used to store the LSB 32 bit value of slave unique device identifier used in Address 
 *  Resolution Protocol 
 */
#define DW_IIC_IC_SMBUS_ARP_UDID_LSB(n)                     (((n)&0xFFFFFFFF) << 0)


/**
  * @}
  */

/** @defgroup IIC_LL_Exported_Constants IIC LL Exported Constants
  * @ingroup  IIC_LL_Driver
  * @brief    IIC LL external constant definition
  *
@verbatim   
  ===============================================================================
                                Exported Constants
  ===============================================================================  
  
    Exported Constants mainly restricts the partial configuration of the abstraction 
    layer by using the form of enumeration to facilitate the use and understanding of 
    the module configuration. For the specific enumeration meaning, please refer to 
    the annotation of each module.

@endverbatim
  *
  * @{
  */
  
/***** DRIVER API *****/



/***** LL API *****/


  
/***** LL API AND DRIVER API *****/

/**
  * @brief Enumeration constant for IIC speed selection
  */
enum hgi2c_dw_speed_sel {
    /*! 1: standard mode (0 to 100 Kb/s)
     */
    IIC_SPEED_STANDARD_MODE = 1, 
    /*! 2: fast mode (= 400 Kb/s) or fast mode plus (= 1000 Kb/s)
     */
    IIC_SPEED_MODE,
    /*! 3: high speed mode (= 3.4 Mb/s)
     */
    IIC_SPEED_HIGH_MODE,
};


/**
  * @}
  */

/** @defgroup IIC_LL_Exported_Struct IIC LL Exported Struct
  * @ingroup  IIC_LL_Driver
  * @brief    IIC LL external configuration structure definition
  *
@verbatim   
  ===============================================================================
                                Exported Struct
  ===============================================================================  

    Exported Struct mainly extracts the IIC registers from the API, and abstracts 
    the structure. As long as it implements the low coupling between the registers 
    and the registers, the user only needs to configure the structure of the abstraction 
    layer and call hal_iic_init. Function, you can configure the IIC module without 
    involving the configuration of the collective register.

@endverbatim
  *
  * @{
  */
  
/**
  * @brief IIC/SMBUS (IP) 
  */
struct hgi2c_dw_reg {
    __IO uint32 CON;
    __IO uint32 TAR;
    __IO uint32 SAR;
    __IO uint32 HS_MADDR;
    
    __IO uint32 DATA_CMD;
    __IO uint32 SS_SCL_HCNT;
    __IO uint32 SS_SCL_LCNT;
    __IO uint32 FS_SCL_HCNT;
    
    __IO uint32 FS_SCL_LCNT;
    __IO uint32 HS_SCL_HCNT;
    __IO uint32 HS_SCL_LCNT;
    __IO uint32 INTR_STAT;
    
    __IO uint32 INTR_MASK;
    __IO uint32 RAW_INTR_STAT;
    __IO uint32 RX_TL;
    __IO uint32 TX_TL;
    
    __IO uint32 CLR_INTR;
    __IO uint32 CLR_RX_UNDER;
    __IO uint32 CLR_RX_OVER;
    __IO uint32 CLR_TX_OVER;
    
    __IO uint32 CLR_RD_REQ;
    __IO uint32 CLR_TX_ABRT;
    __IO uint32 CLR_RX_DONE;
    __IO uint32 CLR_ACTIVITY;
    
    __IO uint32 CLR_STOP_DET;
    __IO uint32 CLR_START_DET;
    __IO uint32 CLR_GEN_CALL;
    __IO uint32 ENABLE;
    
    __IO uint32 STATUS;
    __IO uint32 TXFLR;
    __IO uint32 RXFLR;
    __IO uint32 SDA_HOLD;
    __IO uint32 TX_ABRT_SOURCE;
    __IO uint32 SLV_DATA_NACK_ONLY;
    __IO uint32 DMA_CR;
    __IO uint32 DMA_TDLR;
    __IO uint32 DMA_RDLR;
    __IO uint32 SDA_SETUP;
    __IO uint32 ACK_GENERAL_CALL;
    __IO uint32 ENABLE_STATUS;
    __IO uint32 FS_SPKLEN;
    __IO uint32 HS_SPKLEN;
    __IO uint32 CLR_RESTART_DET;
    __IO uint32 SCL_STUCK_AT_LOW_TIMEOUT;
    __IO uint32 SDA_STUCK_AT_LOW_TIMEOUT;
    __IO uint32 CLR_SCL_STUCK_DET;
    __IO uint32 DEVICE_ID;
    __IO uint32 SMBUS_CLOCK_LOW_SEXT;
    __IO uint32 SMBUS_CLOCK_LOW_MEXT;
    __IO uint32 SMBUS_THIGH_MAX_IDLE_COUNT;
    __IO uint32 SMBUS_INTR_STAT;
    __IO uint32 SMBUS_INTR_MASK;
    __IO uint32 SMBUS_INTR_RAW_STATUS;
    __IO uint32 CLR_SMBUS_INTR;
    __IO uint32 OPTIONAL_SAR;
    __IO uint32 SMBUS_UDID_LSB;
};

struct hgi2c_dw {
    struct i2c_device         dev;
    struct hgi2c_dw_reg *hw;
    i2c_irq_hdl        irq_hdl;
    uint32             irq_data;
//    struct os_mutex      tx_lock;
//    struct os_semaphore  tx_done;
    uint32               irq_num;
    uint32               opened;
};

///**
//  * @brief IIC module interrupt low layer configuration structure
//  */
//typedef struct _ll_iic_irq_cfg {
//    /*! rx buffer overflow down interrupt
//     */
//    bool rx_under_intr_en;
//    /*! rx buffer overflow up interrupt
//     */
//    bool rx_over_intr_en;
//    /*! rx buffer full interrupt
//     */
//    bool rx_full_intr_en;
//    /*! tx buffer overflow interrupt
//     */
//    bool tx_over_intr_en;
//    /*! tx buffer empty interrupt
//     */
//    bool tx_empty_intr_en;
//    /*! read request interrupt
//     */
//    bool read_req_intr_en;
//    /*! tx abrt interrupt
//     */
//    bool tx_abrt_intr_en;
//    /*! rx done interrupt
//     */
//    bool rx_done_intr_en;
//    /*! DW_apb_i2c activity interrupt
//     */
//    bool activity_intr_en;
//    /*! stop condition detect interrupt
//     */
//    bool stop_det_intr_en;
//    /*! start condition detect interrupt
//     */
//    bool start_det_intr_en;
//    /*! General Call address interrupt
//     */
//    bool gen_call_intr_en;
//    /*! RESTART condition has occurred interrupt
//     */
//    bool restart_det_intr_en;
//    /*! Indicates whether a master is holding the bus and the Tx FIFO is empty interrupt
//     */
//    bool master_on_hold_intr_en;
//    /*! Indicates whether the SCL Line is stuck at low for the 
//     *  IC_SCL_STUCK_LOW_TIMOUT number of ic_clk periods interrupt
//     */
//    bool scl_stuck_at_low_intr_en;
//} TYPE_DW_IIC_IRQ_CFG;

///**
//  * @brief IIC low layer configuration structure
//  */
//typedef struct _ll_iic_cfg {
//    /***** IC_CON *****/
//    /*! Controls whether the DW_apb_i2c master is enabled
//     */
//    TYPE_ENUM_DW_IIC_MODE_SEL  mode_sel;
//    /*! These bits control at which speed the DW_apb_i2c operates
//     */
//    TYPE_ENUM_DW_IIC_SPEED_SEL speed_sel;
//    /*! Controls whether responds to 7- or 10-bit addresses as slave/master
//     */
//    TYPE_ENUM_DW_IIC_ADDR_SEL  addr_sel;
//    /*! Determines whether RESTART conditions may be sent as a master
//     */
//    bool                       restart_en;
//    /*! Issue the STOP_DET interrupt if STOP_DET_IF_ADDRESSED = 1'b1
//     */
//    bool                       stop_det_if_addr_en;
//    /*! Controls the generation of the TX_EMPTY interrupt
//     */
//    bool                       tx_empty_ctrl;
//    /*! controls whether DW_apb_i2c should hold the buS when the Rx FIFO is 
//     *  physically full to its RX_BUFFER_DEPTH
//     */
//    bool                       rx_fifo_full_hld_ctrl;
//    /*! Issues the STOP_DET interrupt only when the master is active
//     */
//    bool                       stop_det_if_master_active;
//    /*! Bus Clear Feature is enabled as mater
//     */
//    bool                       bus_clear_feature_ctrl;
//    /*! Enables the usage of IC_OPTIONAL_SAR register
//     */
//    bool                       optional_sar_ctrl;

//    /***** IC_TAR *****/
//    /*! This is the target address for any master transaction
//     */
//    u16                        target_addr;
//                                     
//    /***** IC_SAR *****/
//    /*! The IC_SAR holds the slave address when the I2C is operating as a slave
//     */
//    u16                        slave_addr;

//    
//    /***** IC_DMA_TDLR *****/
//    /*! Transmit Data Level. This bit field controls the level at which a DMA 
//     *  request is made by the transmit logic. It is equal to the watermark level; 
//     *  that is, the dma_tx_req signal is generated when the number of valid 
//     *  data entries in the transmit FIFO is equal to or below this field value, 
//     *  and TDMAE = 1
//     */
//    u8                         dma_tx_threshold_level;
//    
//    /***** IC_DMA_RDLR *****/
//    /*! Receive Data Level. This bit field controls the level at which a DMA request 
//     *  is made by the receive logic. The watermark level = DMARDL+1; that is, 
//     *  dma_rx_req is generated when the number of valid data entries in the 
//     *  receive FIFO is equal to or more than this field value + 1, and RDMAE = 1. 
//     *  For instance, when DMARDL is 0, then dma_rx_req is asserted when 1 or 
//     *  more data entries are present in the receive FIFO. 
//     */
//    u8                         dma_rx_threshold_level;
//    
//    /***** IC_SS_SCL_CNT *****/
//    /*! Standard Speed I2C Clock SCL High Count.
//     *  This register must be set before any I2C bus transaction can take place to 
//     *  ensure proper I/O timing. This register sets the SCL clock high-period count 
//     *  for standard speed. For more information, refer to "C_CLK Frequency 
//     *  Configuration" on page 79.
//     *  High-level time in a single cycle of the IIC clk signal: (1/SYS_CLK)*ss_scl_hcnt
//     */
//    u16                        ss_scl_hcnt;
//    /*! Standard Speed I2C Clock SCL Low Count.
//     *  Low-level time in a single cycle of the IIC clk signal: (1/SYS_CLK)*ss_scl_lcnt
//     */
//    u16                        ss_scl_lcnt;

//    /***** IC_RX_TL TX_TL *****/
//    /*! I2C Receive FIFO Threshold.
//     *  The IIC DMA TX path starts from the threshold value given to the DMAC. The default 
//     *  value is 0, indicating that every 1 byte of data in the RX FIFO will be sent to 
//     *  notify the DMAC to acquire.
//     */
//    u8                         rx_threshold_level;
//    /*! I2C Transmit FIFO Threshold
//     *  The IIC DMA TX path starts from the threshold value given to the DMAC. The default 
//     *  value is 0, indicating that every 1 byte of data in the TX FIFO will be sent to 
//     *  notify the DMAC to acquire.
//     */
//    u8                         tx_threshold_level;
//} TYPE_DW_IIC_CFG;

///**
//  * @brief IIC low layer Initialization structure
//  */
//typedef struct _ll_iic_init {
//    u8 reserved;
//} TYPE_DW_IIC_INIT;

/**
  * @}
  */

/** @defgroup IIC_LL_Interrupt IIC LL Interrupt Handle function
  * @brief   IIC LL Interrupt Handle function
  *
@verbatim   
  ===============================================================================
                        Interrupt Handle function
  ===============================================================================  

    This subsection provides a set of functions allowing to manage the IIC  
    Interrupt Handle function.

    how to use?

    The IIC interrupt handler uses a callback method that reserves the interface 
    to the user in the form of a callback function. The client needs to initialize 
    the callback function when initializing the IIC in order for the interrupt to 
    be processed normally. 
   
@endverbatim
  *
  * @{
  */



/**
  * @}
  */
  
/** @defgroup IIC_LL_Inti_Cfg IIC LL Initialization And Configuration
  * @brief    IIC LL Initialization And Configuration
  *
@verbatim   
  ===============================================================================
                        Initialization And Configuration
  ===============================================================================  

    This subsection provides a set of functions allowing to manage the IIC data 
    Initialization and Configuration.
    
    how to use?

@endverbatim
  *
  * @{
  */

int32 hgi2c_dw_attach(uint32 dev_id, struct hgi2c_dw *hgi2c_s);

/**
  * @}
  */
  
/** @defgroup IIC_LL_Data_Transfers IIC LL Data transfers functions
  * @brief    IIC LL Data transfers functions 
  *
@verbatim   
  ===============================================================================
                            Data transfers functions
  ===============================================================================  

    This subsection provides a set of functions allowing to manage the IIC data 
    transfers and receive.
  
@endverbatim
  *
  * @{
  */

/**
  * @brief  Timing of IIC, send start signal + address value.
  * @param  p_iic: Select the initialized IIC group pointer
  * @param  addr : the addr of IIC slave where you want to read, 
  *                The address value is 2byte.
  * @retval None
  */
#define DW_IIC_TIMING_RESTART_ADDRESS(p_iic, addr)                             \
do {                                                                           \
    p_iic->DATA_CMD = DW_IIC_DATA_CMD_RESTART | DW_IIC_DATA_CMD_DAT(addr >> 8);\
    p_iic->DATA_CMD = DW_IIC_DATA_CMD_DAT(addr);                               \
} while(0)

/**
  * @brief  Timing of IIC, send start signal + read signal + stop signal.
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_TIMING_RESTART_READ_STOP(p_iic)  \
do {                                            \
    p_iic->DATA_CMD = DW_IIC_DATA_CMD_RESTART | \
                      DW_IIC_DATA_CMD_STOP    | \
                      DW_IIC_DATA_CMD_CMD;      \
} while(0)

/**
  * @brief  Timing of IIC, send start signal + read signal.
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_TIMING_RESTART_READ(p_iic)       \
do {                                            \
    p_iic->DATA_CMD = DW_IIC_DATA_CMD_RESTART | \
                      DW_IIC_DATA_CMD_CMD;      \
} while(0)

/**
  * @brief  Timing of IIC, send read signal.
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_TIMING_READ(p_iic)          \
do {                                       \
    p_iic->DATA_CMD = DW_IIC_DATA_CMD_CMD; \
} while(0)

/**
  * @brief  Timing of IIC, send read signal + stop signal.
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_TIMING_READ_STOP(p_iic)          \
do {                                            \
    p_iic->DATA_CMD = DW_IIC_DATA_CMD_STOP    | \
                      DW_IIC_DATA_CMD_CMD;      \
} while(0)

/**
  * @brief  Timing of IIC, send write signal.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_TIMING_WRITE(p_iic, data) \
do {                                     \
    p_iic->DATA_CMD = data;              \
} while(0)

/**
  * @brief  Timing of IIC, get read data.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : read data value.
  * @retval None
  */
#define DW_IIC_TIMING_GET_READ_DATA(p_iic, data) \
do {                                             \
    data = (uint8)p_iic->DATA_CMD;                  \
} while(0)

/**
  * @brief  Timing of IIC, send write signal + stop signal.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_TIMING_WRITE_STOP(p_iic, data)      \
do {                                               \
    p_iic->DATA_CMD = data | DW_IIC_DATA_CMD_STOP; \
} while(0)

/**
  * @brief  IIC get interrupt pending
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_GET_INTERRPT_PENDING(p_iic)                      ((p_iic)->INTR_STAT)

/**
  * @brief  IIC check recevied under interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_RX_UNDER_INTERRUPT_ENABLE(p_iic)           ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_RX_UNDER)

/**
  * @brief  IIC check rx buffer overflow up interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_RX_OVER_INTERRUPT_ENABLE(p_iic)            ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_RX_OVER)

/**
  * @brief  IIC check rx buffer full interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_RX_FULL_INTERRUPT_ENABLE(p_iic)            ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_RX_FULL)

/**
  * @brief  IIC check tx buffer overflow interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_TX_OVER_INTERRUPT_ENABLE(p_iic)            ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_TX_OVER)

/**
  * @brief  IIC check tx buffer empty interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_TX_EMPTY_INTERRUPT_ENABLE(p_iic)           ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_TX_EMPTY)

/**
  * @brief  IIC check read request interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_READ_REQ_INTERRUPT_ENABLE(p_iic)           ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_RD_REQ)

/**
  * @brief  IIC check tx abrt interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_TX_ABRT_INTERRUPT_ENABLE(p_iic)            ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_TX_ABRT)

/**
  * @brief  IIC check rx done interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_RX_DONE_INTERRUPT_ENABLE(p_iic)            ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_RX_DONE)

/**
  * @brief  IIC check DW_apb_i2c activity interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_ACTIVITY_INTERRUPT_ENABLE(p_iic)           ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_ACTIVITY)

/**
  * @brief  IIC check stop condition detect interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_STOP_DET_INTERRUPT_ENABLE(p_iic)           ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_STOP_DET)

/**
  * @brief  IIC check start condition detect interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_START_DET_INTERRUPT_ENABLE(p_iic)          ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_START_DET)

/**
  * @brief  IIC check General Call address interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_GEN_CALL_INTERRUPT_ENABLE(p_iic)           ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_GEN_CALL)

/**
  * @brief  IIC check RESTART condition interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_RESTART_DET_INTERRUPT_ENABLE(p_iic)        ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_RESTART_DET)

/**
  * @brief  IIC check master on hold interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_MST_ON_HOLD_INTERRUPT_ENABLE(p_iic)        ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_MST_ON_HOLD)

/**
  * @brief  IIC check SCL Line is stuck at low interrupt enable
  * @param  p_iic: Select the initialized IIC group pointer.
  * @param  data : data value.
  * @retval None
  */
#define DW_IIC_CHECK_SCL_STUCK_AT_LOW_INTERRUPT_ENABLE(p_iic)   ((p_iic)->INTR_MASK & DW_IIC_INTR_MASK_M_SCL_STUCK_AT_LOW)

/**
  * @brief  Low layer get IIC Activity Status.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_ACTIVITY(p_iic)                       ((p_iic)->STATUS & DW_IIC_STATUS_ACTIVITY)

/**
  * @brief  Low layer get Transmit FIFO Not Full status. Set when the transmit FIFO contains 
  *         one or more empty locations, and is cleared when the FIFO is full
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_TX_FIFO_NO_FULL(p_iic)                ((p_iic)->STATUS & DW_IIC_STATUS_TFNF)

/**
  * @brief  Low layer get IIC Transmit FIFO Completely Empty status. When the transmit FIFO is 
  *         completely empty, this bit is set. When it contains one or more valid entries, 
  *         this bit is cleared. This bit field does not request an interrupt.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_TX_FIFO_EMPTY(p_iic)                  ((p_iic)->STATUS & DW_IIC_STATUS_TFE)

/**
  * @brief  Low layer get IIC Receive FIFO Not Empty status. This bit is set when the receive 
  *         FIFO contains one or more entries; it is cleared when the receive FIFO is empty. 
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_RX_FIFO_NO_EMPTY(p_iic)               ((p_iic)->STATUS & DW_IIC_STATUS_RFNE)

/**
  * @brief  Low layer get IIC Receive FIFO Completely Full status. When the receive FIFO is 
  *         completely full, this bit is set. When the receive FIFO contains one or more 
  *         empty location, this bit is cleared.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_RX_FIFO_FULL(p_iic)                   ((p_iic)->STATUS & DW_IIC_STATUS_RFF)

/**
  * @brief  Low layer get IIC Master FSM Activity Status. When the Master Finite State Machine 
  *         (FSM) is not in the IDLE state, this bit is set.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_MST_ACTIVITY(p_iic)                   ((p_iic)->STATUS & DW_IIC_STATUS_MST_ACTIVITY)

/**
  * @brief  Low layer get IIC Slave FSM Activity Status. When the Slave Finite State Machine 
  *         (FSM) is not in the IDLE state, this bit is set
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_SLV_ACTIVITY(p_iic)                   ((p_iic)->STATUS & DW_IIC_STATUS_SLV_ACTIVITY)

/**
  * @brief  Low layer get IIC master hold tx fifo empty Status.This bit indicates the BUS hold 
  *         when the master holds the bus because of the Tx FIFO being empty, and the the 
  *         previous transferred command does not have the Stop bit set. 
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_MST_HOLD_TX_FIFO_EMPTY(p_iic)         ((p_iic)->STATUS & DW_IIC_STATUS_MST_HOLD_TX_FIFO_EMPTY)

/**
  * @brief  Low layer get IIC master hold rx fifo full Status.This bit indicates the BUS Hold 
  *         in Master mode due to Rx FIFO is Full and additional byte has been received 
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_MST_HOLD_RX_FIFO_FULL(p_iic)          ((p_iic)->STATUS & DW_IIC_STATUS_MST_HOLD_RX_FIFO_FULL)

/**
  * @brief  Low layer get IIC slave hold tx fifo_empty Status.This bit indicates the BUS Hold 
  *         in Slave mode for the Read request when the Tx FIFO is empty. The Bus is in hold 
  *         until the Tx FIFO has data to Transmit for the read request.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_SLV_HOLD_TX_FIFO_EMPTY(p_iic)         ((p_iic)->STATUS & DW_IIC_STATUS_SLV_HOLD_TX_FIFO_EMPTY)

/**
  * @brief  Low layer get IIC slave hold rx fifo full Status.This bit indicates the BUS Hold 
  *         in Slave mode due to the Rx FIFO being Full and an additional byte being received.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_SLV_HOLD_RX_FIFO_FULL(p_iic)          ((p_iic)->STATUS & DW_IIC_STATUS_SLV_HOLD_RX_FIFO_FULL)

/**
  * @brief  Low layer get IIC sda stuck no recovered Status.This bit indicates that an SDA stuck 
  *         at low is not recovered after the recovery mechanism.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_SDA_STUCK_NOT_RECOVERED(p_iic)        ((p_iic)->STATUS & DW_IIC_STATUS_SDA_STUCK_NOT_RECOVERED)

/**
  * @brief  Low layer get IIC smbus quick command bit Status.This bit indicates the R/W bit of 
  *         the Quick command received. This bit will be cleared after the user has read this bit.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_SMBUS_QUICK_CMD_BIT(p_iic)            ((p_iic)->STATUS & DW_IIC_STATUS_SMBUS_QUICK_CMD_BIT)

/**
  * @brief  Low layer get IIC smbus slave address valid Status.This bit indicates whether the 
  *         SMBus Slave address (ic_sar[6:0]) is valid or not.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_SMBUS_SLAVE_ADDR_VALID(p_iic)         ((p_iic)->STATUS & DW_IIC_STATUS_SMBUS_SLAVE_ADDR_VALID)

/**
  * @brief  Low layer get IIC smbus slave address resolved Status.This bit indicates whether 
  *         the SMBus Slave address (ic_sar[6:0]) is Resolved by ARP Master.

  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_SMBUS_SLAVE_ADDR_RESOLVED(p_iic)      ((p_iic)->STATUS & DW_IIC_STATUS_SMBUS_SLAVE_ADDR_RESOLVED)

/**
  * @brief  Low layer get IIC smbus suspend Status.This bit indicates whether the status of 
  *         the input signal is ic_smbus_sus_in_n. This signal is asserted when the SMBus 
  *         Suspend signal is asserted by the SMBus Host.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_SMBUS_SUSPEND_STATUS(p_iic)           ((p_iic)->STATUS & DW_IIC_STATUS_SMBUS_SUSPEND_STATUS)
 
/**
  * @brief  Low layer get IIC smbus alert Status.This bit indicates whether the status of the 
  *         input signal is ic_smbus_alert_in_n. This signal is asserted when the SMBus Alert 
  *         signal is asserted by the SMBus Device.
  * @param  p_iic: Select the initialized IIC group pointer.
  * @retval pending value
  */
#define DW_IIC_GET_STATUS_SMBUS_ALERT_STATUS(p_iic)             ((p_iic)->STATUS & DW_IIC_STATUS_SMBUS_ALERT_STATUS)

/**
  * @brief  IIC module get recevied under pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RX_UNDER_PENDING(p_iic)                      ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_RX_UNDER)

/**
  * @brief  IIC module get rx buffer overflow up pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RX_OVER_PENDING(p_iic)                       ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_RX_OVER)

/**
  * @brief  IIC module get rx buffer full pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RX_FULL_PENDING(p_iic)                       ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_RX_FULL)

/**
  * @brief  IIC module get tx buffer overflow pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_TX_OVER_PENDING(p_iic)                       ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_TX_OVER)

/**
  * @brief  IIC module get tx buffer empty pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_TX_EMPTY_PENDING(p_iic)                      ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_TX_EMPTY)

/**
  * @brief  IIC module get read request pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_READ_REQ_PENDING(p_iic)                      ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_RD_REQ)

/**
  * @brief  IIC module get tx abrt pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_TX_ABRT_PENDING(p_iic)                       ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_TX_ABRT)

/**
  * @brief  IIC module get rx done pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RX_DONE_PENDING(p_iic)                       ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_RX_DONE)

/**
  * @brief  IIC module get DW_apb_i2c activity pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_ACTIVITY_PENDING(p_iic)                      ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_ACTIVITY)

/**
  * @brief  IIC module get stop condition detect pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_STOP_DET_PENDING(p_iic)                      ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_STOP_DET)

/**
  * @brief  IIC module start condition detect pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_START_DET_PENDING(p_iic)                     ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_START_DET)

/**
  * @brief  IIC module get General Call address pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_GEN_CALL_PENDING(p_iic)                      ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_GEN_CALL)

/**
  * @brief  IIC module get master on hold pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_MST_ON_HOLD_PENDING(p_iic)                   ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_MST_ON_HOLD)

/**
  * @brief  IIC module get RESTART condition pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RESTART_DET_PENDING(p_iic)                   ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_RESTART_DET)

/**
  * @brief  IIC module get SCL Line is stuck at low pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_SCL_STUCK_AT_LOW_PENDING(p_iic)              ((p_iic)->INTR_STAT & DW_IIC_INTR_STAT_R_SCL_STUCK_AT_LOW)

/**
  * @brief  IIC module get recevied under pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_RX_UNDER_PENDING(p_iic)                  ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_RX_UNDER)

/**
  * @brief  IIC module get rx buffer overflow up pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_RX_OVER_PENDING(p_iic)                   ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_RX_OVER)

/**
  * @brief  IIC module get rx buffer full pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_RX_FULL_PENDING(p_iic)                   ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_RX_FULL)

/**
  * @brief  IIC module get tx buffer overflow pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_TX_OVER_PENDING(p_iic)                   ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_TX_OVER)

/**
  * @brief  IIC module get tx buffer empty pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_TX_EMPTY_PENDING(p_iic)                  ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_TX_EMPTY)

/**
  * @brief  IIC module get read request pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_READ_REQ_PENDING(p_iic)                  ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_RD_REQ)

/**
  * @brief  IIC module get tx abrt pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_TX_ABRT_PENDING(p_iic)                   ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_TX_ABRT)

/**
  * @brief  IIC module get rx done pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_RX_DONE_PENDING(p_iic)                   ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_RX_DONE)

/**
  * @brief  IIC module get DW_apb_i2c activity pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_ACTIVITY_PENDING(p_iic)                  ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_ACTIVITY)

/**
  * @brief  IIC module get stop condition detect pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_STOP_DET_PENDING(p_iic)                  ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_STOP_DET)

/**
  * @brief  IIC module get start condition detect pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_START_DET_PENDING(p_iic)                 ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_START_DET)

/**
  * @brief  IIC module get General Call address pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_GEN_CALL_PENDING(p_iic)                  ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_GEN_CALL)

/**
  * @brief  IIC module get RESTART condition pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_RESTART_DET_PENDING(p_iic)               ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_RESTART_DET)

/**
  * @brief  IIC module get master on hold pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_MST_ON_HOLD_PENDING(p_iic)               ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_MST_ON_HOLD)

/**
  * @brief  IIC module get SCL Line is stuck at low pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_GET_RAW_SCL_STUCK_AT_LOW_PENDING(p_iic)          ((p_iic)->RAW_INTR_STAT & DW_IIC_RAW_INTR_STAT_SCL_STUCK_AT_LOW)

/**
  * @brief  IIC module clear recevied under pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_RX_UNDER_PENDING(p_iic)                    ((p_iic)->CLR_RX_UNDER = (p_iic)->CLR_RX_UNDER)

/**
  * @brief  IIC module clear rx buffer overflow up pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_RX_OVER_PENDING(p_iic)                     ((p_iic)->CLR_RX_OVER = (p_iic)->CLR_RX_OVER)

/**
  * @brief  IIC module clear rx buffer full pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  * @note   RX_FULL does not have a separate CLR register. It can only be 
  *         masked or read from the data in the RX buffer. Only the RX FIFO buffer 
  *         does not reach full, and the pending will not rise again.
  */
#define DW_IIC_CLEAR_RX_FULL_PENDING(p_iic)                     

/**
  * @brief  IIC module clear tx buffer overflow pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_TX_OVER_PENDING(p_iic)                     ((p_iic)->CLR_TX_OVER = (p_iic)->CLR_TX_OVER)

/**
  * @brief  IIC module clear tx buffer empty pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  * @note   TX empty does not have a separate CLR register. It can only be 
  *         masked or read from the TX buffer. Only the TX FIFO Buffer is not empty. 
  *         This pending will not be up again.
  */
#define DW_IIC_CLEAR_TX_EMPTY_PENDING(p_iic)                    

/**
  * @brief  IIC module clear read request pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_READ_REQ_PENDING(p_iic)                    ((p_iic)->CLR_RD_REQ = (p_iic)->CLR_RD_REQ)

/**
  * @brief  IIC module clear tx abrt pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_TX_ABRT_PENDING(p_iic)                     ((p_iic)->CLR_TX_ABRT = (p_iic)->CLR_TX_ABRT)

/**
  * @brief  IIC module clear rx done pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_RX_DONE_PENDING(p_iic)                     ((p_iic)->CLR_RX_DONE = (p_iic)->CLR_RX_DONE)

/**
  * @brief  IIC module clear DW_apb_i2c activity pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_ACTIVITY_PENDING(p_iic)                    ((p_iic)->CLR_ACTIVITY = (p_iic)->CLR_ACTIVITY)

/**
  * @brief  IIC module clear stop condition detect pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_STOP_DET_PENDING(p_iic)                    ((p_iic)->CLR_STOP_DET = (p_iic)->CLR_STOP_DET)

/**
  * @brief  IIC module clear start condition detect pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_START_DET_PENDING(p_iic)                   ((p_iic)->CLR_START_DET = (p_iic)->CLR_START_DET)

/**
  * @brief  IIC module clear General Call address pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_GEN_CALL_PENDING(p_iic)                    ((p_iic)->CLR_GEN_CALL = (p_iic)->CLR_GEN_CALL)

/**
  * @brief  IIC module clear RESTART condition pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_RESTART_DET_PENDING(p_iic)                 ((p_iic)->CLR_RESTART_DET = (p_iic)->CLR_RESTART_DET)

/**
  * @brief  IIC module clear master on hold pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  * @Note   MASTER_ON_HOLD does not have a separate CLR register. It can 
  *         only be masked or read from the TX buffer. Only the TX FIFO Buffer 
  *         is not empty. This pending will not be up again. 
  */
#define DW_IIC_CLEAR_MASTER_ON_HOLD_PENDING(p_iic)              

/**
  * @brief  IIC module clear SCL Line is stuck at low pending
  * @param  p_iic: Select the initialized IIC group pointer
  * @retval None
  */
#define DW_IIC_CLEAR_STUCK_AT_LOW_PENDING(p_iic)                ((p_iic)->CLR_SCL_STUCK_DET = (p_iic)->CLR_SCL_STUCK_DET)

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

/**
  * @}
  */

/**
  * @}
  */

#endif //__HGI2C_DW_H

/*************************** (C) COPYRIGHT 2018 HUGE-IC ***** END OF FILE *****/
