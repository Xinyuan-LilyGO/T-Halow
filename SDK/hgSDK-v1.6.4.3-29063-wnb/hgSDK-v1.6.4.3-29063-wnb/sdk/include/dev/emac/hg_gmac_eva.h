#ifndef _HG_GMAC_EVA_H_
#define _HG_GMAC_EVA_H_

#include "osal/task.h"
#include "lib/ethernet_phy/eth_phy.h"
#include "hal/netdev.h"

#ifdef __cplusplus
extern "C" {
#endif

#define gmac_dbg(fmt, ...)                  os_printf(fmt, ##__VA_ARGS__)

/*! When GMAC rx has a bug, reset GMAC.This fix is not recommended.
 *  When a GMAC rx bug appears, it is usually a glitch on the 50M clock. 
 *  In this case, the right thing to do is to fix the 50M clock issue in
 *  hardware, and only use a software fix when there is really no way to do
 *  it. This fix is not recommended. One of the reasons is that it will
 *  cause a drop in hit traffic, and the other reason cannot fix the GMAC
 *  tx bug.
 */
#define HG_GMAC_FIX_BUG_RESET_EN            0

/*! The minimum number of TX descriptors
 */
#define HG_GMAC_TX_MIN_NUM                  1
/*! The size of each TX buf
 */
#define HG_GMAC_TX_PER_BUF_SIZE             1516

/*! The minimum number of RX descriptors
 */
#define HG_GMAC_RX_MIN_NUM                  2
/*! The size of each TX buf
 */
#define HG_GMAC_RX_PER_BUF_SIZE             172
/*! The size of each TX buf
 */
#define HG_GMAC_RX_FRAME_MAX_SIZE           (1516+4)
/*! TX minimum buffer size
 */
#define HG_GMAC_TX_MIN_BUF_SIZE             ((sizeof(struct hg_gmac_descriptor) + HG_GMAC_TX_PER_BUF_SIZE) * HG_GMAC_TX_MIN_NUM)
/*! RX minimum buffer size.
 */
#define HG_GMAC_RX_MIN_BUF_SIZE             (((sizeof(struct hg_gmac_descriptor) + HG_GMAC_RX_PER_BUF_SIZE) * HG_GMAC_RX_MIN_NUM) + HG_GMAC_RX_FRAME_MAX_SIZE - HG_GMAC_RX_PER_BUF_SIZE)


#if HG_GMAC_TX_PER_BUF_SIZE < 1516
    #error "GMAC ERR: The size of each TX buf must not be less than 1516 bytes."
#endif
#if HG_GMAC_TX_PER_BUF_SIZE%4
    #error "GMAC ERR: The size of each TX buf must be a multiple of four."
#endif
#if HG_GMAC_RX_PER_BUF_SIZE%4
    #error "GMAC ERR: The size of each RX buf must be a multiple of four."
#endif
#if HG_GMAC_RX_FRAME_MAX_SIZE%4
    #error "GMAC ERR: The maximum frame size must be a multiple of four."
#endif
#if HG_GMAC_RX_FRAME_MAX_SIZE < 1520
    #error "GMAC ERR: The maximum frame size cannot be less than 1520 bytes."
#endif
#if HG_GMAC_RX_MIN_NUM < 2
    #error "GMAC ERR: The number of RX descriptors must be greater than one."
#endif
    
/*! MDIO&MDC GPIO SET
 */
#ifdef HG_GMAC_IO_SIMULATION
    #define HG_GMAC_MDIO_SET_OUTPUT(p_gmac)     (gpio_ioctl(p_gmac->mdio_pin, GPIO_DIR_ATOMIC, GPIO_DIR_OUTPUT))
    #define HG_GMAC_MDIO_SET_INPUT(p_gmac)      (gpio_ioctl(p_gmac->mdio_pin, GPIO_DIR_ATOMIC, GPIO_DIR_INPUT))
    #define HG_GMAC_MDIO_HIGH(p_gmac)           (gpio_ioctl(p_gmac->mdio_pin, GPIO_VALUE_ATOMIC, 1))
    #define HG_GMAC_MDIO_LOW(p_gmac)            (gpio_ioctl(p_gmac->mdio_pin, GPIO_VALUE_ATOMIC, 0))
    #define HG_GMAC_MDIO_GET(p_gmac)            (gpio_get_val(p_gmac->mdio_pin))
    #define HG_GMAC_MDC_HIGH(p_gmac)            (gpio_ioctl(p_gmac->mdc_pin, GPIO_VALUE_ATOMIC, 1))
    #define HG_GMAC_MDC_LOW(p_gmac)             (gpio_ioctl(p_gmac->mdc_pin, GPIO_VALUE_ATOMIC, 0))
    #define HG_GMAC_DELAY(p_gmac)               os_sleep_us(0)
#else
    #define HG_GMAC_MDIO_SET_OUTPUT(p_gmac)     HG_GMAC_V2_REG_OPT((p_gmac)->hw->CSR9 |= BIT(18))
    #define HG_GMAC_MDIO_SET_INPUT(p_gmac)      HG_GMAC_V2_REG_OPT((p_gmac)->hw->CSR9 &= ~BIT(18))
    #define HG_GMAC_MDIO_HIGH(p_gmac)           HG_GMAC_V2_REG_OPT((p_gmac)->hw->CSR9 |= BIT(17))
    #define HG_GMAC_MDIO_LOW(p_gmac)            HG_GMAC_V2_REG_OPT((p_gmac)->hw->CSR9 &= ~BIT(17))
    #define HG_GMAC_MDIO_GET(p_gmac)            ((p_gmac)->hw->CSR9 & BIT(19))
    #define HG_GMAC_MDC_HIGH(p_gmac)            HG_GMAC_V2_REG_OPT((p_gmac)->hw->CSR9 |= BIT(16))
    #define HG_GMAC_MDC_LOW(p_gmac)             HG_GMAC_V2_REG_OPT((p_gmac)->hw->CSR9 &= ~BIT(16))
    #define HG_GMAC_DELAY(p_gmac)               os_sleep_us(0)
#endif


/**
  * @brief Ethernet GMAC controller (IP modify)
  */
struct hg_gmac_eva_hw {
    __IO uint32 CSR0;
         uint32 RESERVED0;
    __IO uint32 CSR1;
         uint32 RESERVED1;
    __IO uint32 CSR2;
         uint32 RESERVED2;
    __IO uint32 CSR3;
         uint32 RESERVED3;
    __IO uint32 CSR4;
         uint32 RESERVED4;
    __IO uint32 CSR5;
         uint32 RESERVED5;
    __IO uint32 CSR6;
         uint32 RESERVED6;
    __IO uint32 CSR7;
         uint32 RESERVED7;
    __IO uint32 CSR8;
         uint32 RESERVED8;
    __IO uint32 CSR9;
         uint32 RESERVED9;
    __IO uint32 CSR10;
         uint32 RESERVED10;
    __IO uint32 CSR11;
         uint32 RESERVED11;
    __IO uint32 CSR12;
         uint32 RESERVED12;
    __IO uint32 CSR13;
         uint32 RESERVED13;
    __IO uint32 CSR14;
         uint32 RESERVED14;
    __IO uint32 CSR15;
         uint32 RESERVED15;
    __IO uint32 CSR16;
         uint32 RESERVED16;
    __IO uint32 CSR17;
         uint32 RESERVED17;
    __IO uint32 CSR18;
         uint32 RESERVED18;
    __IO uint32 CSR19;
         uint32 RESERVED19;
    __IO uint32 CSR20;
         uint32 RESERVED20;
};

/**
  * @brief GMAC descriptor generic structure
  */
struct hg_gmac_descriptor {
    uint32 reg0;
    uint32 reg1;
    uint32 reg2;
    uint32 reg3;
};

/**
  * @brief GMAC RX descriptor structure
  */
struct hg_gmac_rx_descriptor {
    /*! This bit is reset for the frames with the legal length. When set,
     *  indicates that the frame was truncated due to the receive FIFO
     *  overflow.
     */
    uint32  zero                : 1,
    /*! This bit is valid only when the last_descriptor is set.
     *  Additionally, the CE is not valid when the received frame is a
     *  runt frame.
     */
            crc_err             : 1,
    /*! This bit is valid only when the last_descriptor is set.
     */
            dribbling_bit       : 1,
    /*! This bit is valid only when the last_descriptor is set.
     */
            mii_err             : 1,
            reserved0           : 1,
    /*! When set, indicates that the frame has the length field greater
     *  then 1500 (Ethernet type frame). When cleared, indicates the
     *  802.3 type frame.  
     *  This bit is valid only when the last_descriptor is set.
     *  Additionally, the FT is invalid for the runt frames of a length
     *  shorter then 14 bytes.
     */
            frame_type          : 1,
    /*! This bit is valid only when the last_descriptor is set.
     */
            collision_seen      : 1,
    /*! This bit is valid only when the last_descriptor is set.
     */
            frame_too_long      : 1,
            last_descriptor     : 1,
            first_descriptor    : 1,
    /*! This bit is valid only when the last_descriptor is set.
     */
            multicast_frame     : 1,
    /*! This bit is valid only when the last_descriptor is set.
     */
            runt_frame          : 1,
            reserved1           : 2,
    /*! This bit is valid only when the last_descriptor is set.
     */
            descriptor_err      : 1,
    /*! This bit is valid only when the last_descriptor is set.
     */
            err_summary         : 1,
    /*! This bit is valid only when the last_descriptor is set and
     *  descriptor_err is cleared.
     */
            frame_len           : 14,
    /*! This bit is valid only for the last descriptor of the frame,
     *  when the CSR6.30 (receive all) bit is set, and the frame is at
     *  least 64 bytes long.
     */
            filtering_fail      : 1,
            own                 : 1;
    /*! Indicates the size, in bytes, of memory space used by the first
     *  data buffer. This number must be a multiple of 4.
     */
    uint32  buf_1_size          : 11,
    /*! Useless, please set to 0.
     */
            buf_2_size          : 11,
            reserved2           : 2,
    /*! When set, indicates that the second buffer's address points to
     *  the next descriptor and not to the data buffer.
     * @note Note that the end_of_ring takes precedence over the
     *       second_addr_chained.
     */
            second_addr_chained : 1,
    /*! When set, indicates that this is the last descriptor in the
     *  receive descriptor ring.
     */
            end_of_ring         : 2;
    /*! Indicates the length, in bytes, of memory allocated for the
     *  first receive buffer. This number must be 64 byte aligned.
     *  @note rx_buf_addr_1 are aligned in 4 bytes and can only be located
     *        in SRAM3.  
     *        Statement example:  
     *         static u8 buf[1024] __attribute__((aligned(4),section("SRAM3")));
     */
    uint32  rx_buf_addr_1;
    /*! A pointer to the next rx descriptor.
     */
    struct  hg_gmac_rx_descriptor *p_next;
};

/**
  * @brief GMAC TX descriptor structure type
  */
struct hg_gmac_tx_descriptor {
    /*! When set, indicates that the frame was deferred befor
     *  transmission. Deferring occurs if the carrier is detected when
     *  the transmission is ready to start.  
     *  This bit is valid only when last_descriptor is set.
     */
    uint32  deferred            : 1,
    /*! This bit is valid only when last_descriptor is set.
     */
            underflow_err       : 1,
            reserved0           : 1,
    /*! This value is not valid when excessive_collisions is set. This
     *  bit is valid only when last_descriptor is set.
     */
            collision_cnt       : 4,
            reserved1           : 1,
    /*! This bit is valid only when last_descriptor is set.
     */
            excessive_collision : 1,
    /*! This bit is not valid when underflow_err is set. This bit is
     *  valid only when last_descriptor is set.
     */
            late_collision      : 1,
    /*! This bit is valid only when last_descriptor is set.
     */
            no_carrier          : 1,
    /*! This bit is valid only when last_descriptor is set.
     */
            loss_of_carrier     : 1,
            reserved2           : 3,
    /*! This bit is valid only when last_descriptor is set.
     */
            err_summary         : 1,
            reserved3           : 15,
            own                 : 1;
    /*! Indicates the size, in bytes, of memory space used by the first
     *  data buffer. 
     */
    uint32  buf_1_size          : 11,
    /*! Useless, please set to 0.
     */
            buf_2_size          : 11,
    /*! This bit is valid only for the setup frames.
     */
            filtering_type_0    : 1,
    /*! When set, automatic byte padding is disabled.
     */
            disable_padding     : 1,
    /*! When set, indicates that the second descriptor's address points
     *  to the next descriptor and not to the data buffer.  
     *  This bit is valid only when end_of_ring is 0.
     */
            second_addr_chained : 1,
    /*! When set, indicates the last descriptor in the descriptors ring.
     */
            end_of_ring         : 1,
            crc_disable         : 1,
    /*! When set, indicates that this is a setup frame descriptor.
     */
            setup_packet        : 1,
    /*! This bit is valid only for the setup frames.
     */
            filtering_type_1    : 1,
            first_descriptor    : 1,
            last_descriptor     : 1,
    /*! Interrupt on completion.  
     *  Setting this flag instructs the GMAC to set CSR5.0 (transmit
     *  interrupt) immediately after processing a current frame.  
     *  This bit is valid when last_descriptor is set, or for a setup
     *  packet.
     */
            int_on_completion   : 1;
    /*! Contains the address of the first data buffer. For the setup
     *  frame this address must be 64 byte aligned. In all other cases
     *  there are no restrictions on buffer alignment.
     *  @note tx_buf_addr_1 are aligned in 4 bytes and can only be located
     *        in SRAM2.  
     *        Statement example:  
     *         static u8 buf[1024] __attribute__((aligned(4),section("SRAM2")));
     */
    uint32 tx_buf_addr_1;
    /*! A pointer to the next tx descriptor.
     */
    struct hg_gmac_tx_descriptor *p_next;
};

/**
  * @brief GMAC Hash table setup frame buffer format
  */
struct hg_gmac_setup_hash_table {
    /*! Multicast address hash table
     */
    uint32 hash_filter[32];
    uint32 reserved[7];
    /* 1 mac address */
    
    /*! MAC address 0bit~15bit
     */
    uint32 addr_15_00;
    /*! MAC address 16bit~31bit
     */
    uint32 addr_31_16;
    /*! MAC address 32bit~47bit
     */
    uint32 addr_47_32;
};

/**
  * @brief GMAC Perfect filtering setup frame buffer format
  */
struct hg_gmac_setup_perfect_filter {
    /*! 16 MAC address
     */
    struct {
        /*! MAC address 0bit~15bit
         */
        uint32 addr_15_00;
        /*! MAC address 16bit~31bit
         */
        uint32 addr_31_16;
        /*! MAC address 32bit~47bit
         */
        uint32 addr_47_32;
    } mac_addr[16];
};

/**
  * @brief GMAC setup frame union type
  */
union hg_gmac_setup_frame {
    /*! perfect filter
     */
    struct hg_gmac_setup_perfect_filter perfect_filter;
    /*! hash table filter
     */
    struct hg_gmac_setup_hash_table     hash_table_filter;
};

struct hg_gmac_data {
    struct hg_gmac_rx_descriptor volatile  *p_rx_des;
    struct hg_gmac_tx_descriptor volatile  *p_tx_des;
    
    uint8                                  *p_rx_malloc;
    uint8                                  *p_tx_malloc;
    
    /*! In order not to splicing buf, the buf of the last RX descriptor
     *  should be able to fill one frame.
     */
    /*!
     *      struct hg_gmac_tx_descriptor  rx_des[rx_des_num];
     *      uint8                         rx_buf[rx_des_num-1][HG_GMAC_RX_PER_BUF_SIZE];
     *      uint8                         last_rx_buf[HG_GMAC_RX_FRAME_MAX_SIZE];
     */
    uint32                                  rx_des_num;
    struct hg_gmac_rx_descriptor           *p_rx_des_buf;
    uint8                                  *p_rx_buf;
    /*!
     *      struct hg_gmac_tx_descriptor  tx_des[tx_des_num];
     *      uint8                         tx_buf[tx_des_num][HG_GMAC_TX_PER_BUF_SIZE];
     */
    uint32                                  tx_des_num;
    struct hg_gmac_tx_descriptor           *p_tx_des_buf;
    uint8                                  *p_tx_buf;
#if HG_GMAC_FIX_BUG_RESET_EN
    /* The following 4 variables are only used to fix GMAC bugs. */
    uint32                                  miss_frame_cnt;
    uint8                                   reset_flag  :   1,
                                            tx_flag     :   1,
                                            rx_flag     :   1;
#endif
};

struct hg_gmac_eva_statistics {
    uint32                          tx_cnt;
    uint32                          rx_cnt;
    uint32                          ru_pending_cnt;
    uint32                          rx_err_cnt;
#if HG_GMAC_FIX_BUG_RESET_EN
    uint32                          crc_err_cnt;
    uint32                          miss_err_cnt;
    uint32                          rx_err_reset_cnt;
#endif
};

struct hg_gmac_eva {
    struct netdev                   dev;
    struct hg_gmac_eva_hw          *hw;
    uint32 modbus_devid, phy_devid, crc_devid;
    struct crc_dev *crcdev;
    uint32                          mdio_pin;
    uint32                          mdc_pin;
    uint32                          irq_num;
    uint32                          opened;
    struct hg_gmac_data             ctrl_data;
    uint8                           mac_addr[6];
    netdev_input_cb                 input_cb;
    uint32                          tx_buf_size;
    uint32                          rx_buf_size;
    struct os_task                  receive_task;
    
    /* Save link information */
    int32                           speed;
    int32                           duplex;
    int32                           link_status;
    
#if HG_GMAC_FIX_BUG_RESET_EN
    struct os_task                  check_task;         //check gmac bug
#endif
    struct os_semaphore             receive_sema;
    struct os_mutex                 mdio_mutex;
    struct os_mutex                 send_mutex;
    
    struct hg_gmac_eva_statistics   statistics;
};

/**
  * @brief GMAC register operation
  * @param expression: expression.
  */
#define HG_GMAC_REG_OPT(expression) \
do {                               \
    expression;                    \
    __ASM volatile ("nop");        \
} while(0)

/** @brief GMAC register constant table definition
  * @{
  */

/***** CSR0(The bus mode register) *****/
/*! Transmit automatic polling interval setting.
 */
#define HG_GMAC_CSR0_TAP_SET(n)                      (((n)&0x07) << 17)
#define HG_GMAC_CSR0_TAP_MASK                        (0x07UL << 17)
/*! Specifies the maximum number of words that can be transferred within one
 *  DMA transaction.
 *  @note PBL cannot be 0, the recommended setting is 16
 */
#define HG_GMAC_CSR0_PBL_SET(n)                      (((n)&0x3F) << 8)
/*! Specifies the number of 128-bit words between two consecutive unchained
 *  descriptors.
 */
#define HG_GMAC_CSR0_DSL_SET(n)                      (((n)&0x1F) << 2)
/*! Software reset.
 */
#define HG_GMAC_CSR0_SWR_EN                          (1UL << 0)


/***** CSR5(The status register) *****/
/*! Transmit process state.
 */
#define HG_GMAC_CSR5_TS_GET(n)                       (((n) >> 20) & 0x07)
/*! Receive process state .
 */
#define HG_GMAC_CSR5_RS_GET(n)                       (((n) >> 17) & 0x07)
/*! Normal interrupt summary.
 */
#define HG_GMAC_CSR5_NIS_PENDING                     (1UL << 16)
/*! Abnormal interrupt summary.
 */
#define HG_GMAC_CSR5_AIS_PENDING                     (1UL << 15)
/*! Early receive interrupt.
 */
#define HG_GMAC_CSR5_ERI_PENDING                     (1UL << 14)
/*! General-purpose timer expiration.
 */
#define HG_GMAC_CSR5_GTI_PENDING                     (1UL << 11)
/*! Early transmit interrupt.
 */
#define HG_GMAC_CSR5_ETI_PENDING                     (1UL << 10)
/*! Receive process stopped.
 */
#define HG_GMAC_CSR5_RPS_PENDING                     (1UL << 8)
/*! Receive buffer unavailable.
 */
#define HG_GMAC_CSR5_RU_PENDING                      (1UL << 7)
/*! Receive interrupt.
 */
#define HG_GMAC_CSR5_RI_PENDING                      (1UL << 6)
/*! Transmit underflow.
 */
#define HG_GMAC_CSR5_UNF_PENDING                     (1UL << 5)
/*! Transmit buffer unavailable.
 */
#define HG_GMAC_CSR5_TU_PENDING                      (1UL << 2)
/*! Transmit process stopped.
 */
#define HG_GMAC_CSR5_TPS_PENDING                     (1UL << 1)
/*! Transmit interrupt.
 */
#define HG_GMAC_CSR5_TI_PENDING                      (1UL << 0)


/***** CSR6(The operation mode register) *****/
/*! Receive all.
 */
#define HG_GMAC_CSR6_RA_EN                           (1UL << 30)
/*! mask output of mac module.
 */
#define HG_GMAC_CSR6_MASK_EN                         (1UL << 29)
/*! Write 1 to reset txfifo & tx buffer addr, auto clear.
 */
#define HG_GMAC_CSR6_CPU_RST_TX                      (1UL << 28)
/*! Write 1 to reset rxfifo & rx buffer addr, auto clear.
 */
#define HG_GMAC_CSR6_CPU_RST_RX                      (1UL << 27)
/*! auto reset txfifo & tx buffer addr, if chained frame finished and the
 *  next frame is not chained.
 */
#define HG_GMAC_CSR6_TCH_RST_EN                      (1UL << 26)
/*! auto reset rxfifo & rx buffer addr, if chained frame finished and the
 *  next frame is not chained.
 */
#define HG_GMAC_CSR6_RCH_RST_EN                      (1UL << 25)
/*! auto reset rxfifo & rx buffer addr, if receive buffer unavailable.
 */
#define HG_GMAC_CSR6_RU_RST_EN                       (1UL << 24)
/*! auto disable RX if receive buffer unavailable.
 */
#define HG_GMAC_CSR6_RU_DIS_EN                       (1UL << 23)
/*! Transmit threshold mode.
 */
#define HG_GMAC_CSR6_TTM_EN                          (1UL << 22)
/*! When set, the transmission starts after a full packet is written into
 *  the transmit FIFO, regardless of the current FIFO threshold level.
 */
#define HG_GMAC_CSR6_SF_EN                           (1UL << 21)
/*! RX_ER enable
 */
#define HG_GMAC_CSR6_RX_ER_EN                        (1UL << 20)
/*! Ethernet Speed Selection.
 */
#define HG_GMAC_CSR6_SPEED_SET(n)                    (((n)&0x03) << 16)
#define HG_GMAC_CSR6_SPEED_MASK                      (0x03UL << 16)
/*! Threshold control bits.
 */
#define HG_GMAC_CSR6_TR_SET(n)                       (((n)&0x03) << 14)
/*! Start/stop transmit command.
 */
#define HG_GMAC_CSR6_ST_EN                           (1UL << 13)
/*! Full duplex mode.
 */
#define HG_GMAC_CSR6_FD                              (1UL << 9)
/*! Pass all multicast.
 */
#define HG_GMAC_CSR6_PM_EN                           (1UL << 7)
/*! Promiscuous mode.
 */
#define HG_GMAC_CSR6_PR_EN                           (1UL << 6)
/*! Inverse filtering.
 */
#define HG_GMAC_CSR6_IF                              (1UL << 4)
/*! Pass bad frames.
 */
#define HG_GMAC_CSR6_PB_EN                           (1UL << 3)
/*! Hash only filtering mode.
 */
#define HG_GMAC_CSR6_HO                              (1UL << 2)
/*! Start/stop receive command.
 */
#define HG_GMAC_CSR6_SR_EN                           (1UL << 1)
/*! Hash/perfect receive filtering mode.
 */
#define HG_GMAC_CSR6_HP                              (1UL << 0)


/***** CSR7(The interrupt enable register) *****/
/*! Normal interrupt summary enable.
 */
#define HG_GMAC_CSR7_NIE_EN                          (1UL << 16)
/*! Abnormal interrupt summary enable.
 */
#define HG_GMAC_CSR7_AIE_EN                          (1UL << 15)
/*! Early receive interrupt enable.
 */
#define HG_GMAC_CSR7_ERE_EN                          (1UL << 14)
/*! General-purpose timer overflow enable.
 */
#define HG_GMAC_CSR7_GTE_EN                          (1UL << 11)
/*! Early transmit interrupt enable.
 */
#define HG_GMAC_CSR7_ETE_EN                          (1UL << 10)
/*! Receive stopped enable.
 */
#define HG_GMAC_CSR7_RSE_EN                          (1UL << 8)
/*! Receive buffer unavailable enable.
 */
#define HG_GMAC_CSR7_RUE_EN                          (1UL << 7)
/*! Receive interrupt enable.
 */
#define HG_GMAC_CSR7_RIE_EN                          (1UL << 6)
/*! Underflow interrupt enable.
 */
#define HG_GMAC_CSR7_UNE_EN                          (1UL << 5)
/*! Transmit buffer unavailable enable.
 */
#define HG_GMAC_CSR7_TUE_EN                          (1UL << 2)
/*! Transmit stopped enable.
 */
#define HG_GMAC_CSR7_TSE_EN                          (1UL << 1)
/*! Transmit interrupt enable.
 */
#define HG_GMAC_CSR7_TIE_EN                          (1UL << 0)


/***** CSR8(The missed frames counter register) *****/
/*! Missed frame overflow.
 */
#define HG_GMAC_CSR8_MFO_PENDING                     (1UL << 16)
/*! Missed frame counter.
 */
#define HG_GMAC_CSR8_MFC(n)                          (((n)&0xFFFF) >> 0)


/***** CSR9(The serial ROM/Software MII Serial Management register) *****/
/*! MII management data in signal.
 */
#define HG_GMAC_CSR9_MDI_GET(n)                      (((n) >> 19) & 0x01)
/*! MII management interface mode.
 */
#define HG_GMAC_CSR9_MII_SET(n)                      (((n)&0x01) << 18)
/*! MII management write data.
 */
#define HG_GMAC_CSR9_MDO_SET(n)                      (((n)&0x01) << 17)
/*! MII management clock.
 */
#define HG_GMAC_CSR9_MDC_SET(n)                      (((n)&0x01) << 16)
/*! Serial ROM data output.
 */
#define HG_GMAC_CSR9_SDO_SET(n)                      (((n)&0x01) << 3)
/*! Serial ROM data input.
 */
#define HG_GMAC_CSR9_SDI_GET(n)                      (((n) >> 2) & 0x01)
/*! Serial ROM clock.
 */
#define HG_GMAC_CSR9_SCLK_SET(n)                     (((n)&0x01) << 1)
/*! Serial ROM chip select.
 */
#define HG_GMAC_CSR9_SCS_SET(n)                      (((n)&0x01) << 0)


/***** CSR10(The MII serial management register) *****/
/*! START/BUSY.
 */
#define HG_GMAC_CSR10_SB                             (1UL << 31)
/*! clock divider settings.
 */
#define HG_GMAC_CSR10_CLKDIV_SET(n)                  (((n)&0x07) << 28)
/*! MIISM operation code.
 */
#define HG_GMAC_CSR10_OPCODE_SET(n)                  (((n)&0x03) << 26)
/*! Physical layer address for current transfer.
 */
#define HG_GMAC_CSR10_PHYADD_SET(n)                  (((n)&0x1F) << 21)
/*! Register address for the current transfer.
 */
#define HG_GMAC_CSR10_REGADD_SET(n)                  (((n)&0x1F) << 16)
/*! Register data.
 */
#define HG_GMAC_CSR10_DATA(n)                        (((n)&0xFFFF) << 0)


/***** CSR11(Timer and interrupt mitigation control) *****/
/*! Controls the time units for the transmit and receive timers.
 */
#define HG_GMAC_CSR11_CS_SET(n)                      (((n)&0x01) << 31)
/*! Controls the time that must elapse between the end of a transmit
 *  operation and issuing the transmit interrupt.
 */
#define HG_GMAC_CSR11_TT_SET(n)                      (((n)&0x0F) << 27)
/*! Controls the number of the frames transmitted before issuing the
 *  transmit interrupt.
 */
#define HG_GMAC_CSR11_NTP_SET(n)                     (((n)&0x07) << 24)
/*! Controls the time that must elapse between the end of a receive
 *  operation and issuing the receive interrupt.
 */
#define HG_GMAC_CSR11_RT_SET(n)                      (((n)&0x0F) << 20)
/*! Controls the number of the received frames before issuing the receive
 *  interrupt.
 */
#define HG_GMAC_CSR11_NRP_SET(n)                     (((n)&0x07) << 17)
/*! Continuous mode.
 */
#define HG_GMAC_CSR11_CON_EN                         (1UL << 16)
/*! Contains the number of iterations of the general-purpose timer.
 */
#define HG_GMAC_CSR11_TIM_SET(n)                     (((n)&0xFFFF) << 0)

/**
  * @}
  */
    
/** @brief GMAC external constant definition
  * @{
  */
    
/**
  * @brief Programmable burst length for data buffer access
  * @note  PBL cannot be 0, GMAC_PBL_16 is recommended.
  */
enum hg_gmac_pbl_sel {
    HG_GMAC_PBL_0                = 0,
    HG_GMAC_PBL_1                = 1,
    HG_GMAC_PBL_2                = 2,
    HG_GMAC_PBL_4                = 4,
    HG_GMAC_PBL_8                = 8,
    HG_GMAC_PBL_16               = 16,
    HG_GMAC_PBL_32               = 32,
};

/**
  * @brief MAC Ethernet speed selection
  */
enum hg_gmac_speed_sel {
    HG_GMAC_ETHERNET_100M        = 0,
    HG_GMAC_ETHERNET_1G          = 1,
    HG_GMAC_ETHERNET_10M         = 2,
};

/**
  * @brief MAC MIISM operation code
  */
enum hg_gmac_miim_opcode {
    HG_GMAC_DISABLE_CLK          = 0,
    HG_GMAC_REG_WRITE            = 1,
    HG_GMAC_REG_READ             = 2,
    HG_GMAC_CLK_DIVIDER_SET      = 3,
};

/**
  * @brief MAC filter type selection
  */
enum hg_gmac_addr_filter {
    /*! Setup frame buffer is interpreted as a set of 16 48-bit physical
     *  addresses.
     * @note Whitelist mode
     */
    HG_GMAC_PERFECT_FILTER = 0,
    /*! Setup frame buffer contains 512-bit hash table plus a single 48-bit
     *  physical address.
     * @note Whitelist mode. The hash table is only valid for multicast
     *       addresses.
     */
    HG_GMAC_HASH_FILTER,
    /*! Setup frame buffer is interpreted as a set of 16 48-bit physical
     *  addresses.
     * @note Blacklist mode
     */
    HG_GMAC_INVERSE_FILTER,
    /*! Setup frame buffer is interpreted as a 512-bit hash table.
     * @note Whitelist mode. The hash table is only valid for multicast
     *       addresses.
     */
    HG_GMAC_HASH_ONLY_FILTER,
};

/**
  * @brief frame tx/rx status
  */
enum hg_gmac_frame_status {
    /*! frame transfer completed
     */
    HG_GMAC_FRAME_COMPLETE = 0,
    /*! frame transmission error
     */
    HG_GMAC_FRAME_ERR,
    /*! frame waiting for transmission completed
     */
    HG_GMAC_FRAME_WAITTING_COMPLETE,
};

/**
  * @}
  */

//To fix gmac bugs
void gmac_csr_dv_disable(int dev_id);
void gmac_csr_dv_enable(int dev_id);
void hg_gmac_reset(struct netdev *ndev);
void hg_gmac_bug_reset(struct netdev *ndev);

int32 hg_gmac_attach(uint32 dev_id, struct hg_gmac_eva *gmac);
int32 hg_gmac_has_received_frame(struct netdev *ndev);
int32 hg_gmac_receive_data(struct netdev *emac_dev);
int32 hg_gmac_has_received_frame(struct netdev *ndev);

#ifdef __cplusplus
}
#endif

#endif
