#ifndef _HGTIMER_V2_H_
#define _HGTIMER_V2_H_
#include "hal/timer_device.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief TIMER register structure
  * @{
  */
struct hgtimer_v2_hw {
    __IO uint32 TMR_CON;
    __IO uint32 TMR_PR;
    __IO uint32 TMR_CNT;
    __IO uint32 TMR_PWM;
};

struct hgtimer_v2 {
    struct timer_device dev;
    struct hgtimer_v2_hw *hw;
    uint32 irq_num;
    timer_cb_hdl cb;
    uint32       cb_data;
    enum timer_type mode;
    uint32 flags;
    uint32 opened;
};

/**
  * @}
  */

/** @defgroup TIMER_Register_Constants TIMER Register Constants
  * @ingroup  TIMER_Driver
  * @brief    TIMER register constant table definition
  * @{
  */

/***** TMRx_CON *****/
/*! RW, TIMERx pending, write 1 clear pending
 */
#define HGTIMER_V2_CON_TIMER_PNG                 (1UL << 15)
/*! RW, TIMERx capture pending, write 1 clear pending
 */
#define HGTIMER_V2_CON_CAPTURE_PNG               (1UL << 14)
/*! RW, TIMERx timer mode interrupt enable
 */
#define HGTIMER_V2_CON_TMR_INTR_EN               (1UL << 13)
/*! RW, TIMERx capture mode interrupt enable
 */
#define HGTIMER_V2_CON_CAP_INTR_EN               (1UL << 12)
/*! RW, TIMERx timer's prescaler setting
 */
#define HGTIMER_V2_CON_PSC(n)                    (((n)&0x7) << 8)
#define HGTIMER_V2_CON_PSC_MASK                  (0x07UL << 8)
/*! RW, TIMERx capture mode edge select
 */
#define HGTIMER_V2_CON_CAP_EDGE(n)               (((n)&0x3) << 6)
/*! RW, TIMERx mode select
 */
#define HGTIMER_V2_CON_MODE(n)                   (((n)&0x3) << 4)
#define HGTIMER_V2_CON_MODE_DIS_MASK             (0x03UL << 4)
/*! RW, TIMERx timer counter source select
 */
#define HGTIMER_V2_CON_INC_SRC(n)                (((n)&0x7) << 0)
#define HGTIMER_V2_CON_INC_SRC_MASK              (0x07UL << 0)


/***** TMRx_PR *****/
/*! RW, TIMERx Prescaler register
 */
#define HGTIMER_V2_TIMER_PR(n)                   (((n)&0xFFFF) << 0)


/***** TMRx_CNT *****/
/*! RW, TIMERx Count register
 */
#define HGTIMER_V2_TIMER_CNT(n)                  (((n)&0xFFFF) << 0)


/***** TMRx_PWM *****/
/*! RW, TIMERx Pulse width modulation
 */
#define HGTIMER_V2_TIMER_PWM(n)                  (((n)&0xFFFF) << 0)

/**
  * @}
  */

/** @defgroup TIMER_Exported_Constants TIMER Exported Constants
  * @ingroup  TIMER_Driver
  * @brief    TIMER external constant definition
  * @{
  */

/**
  * @brief Enumeration constant for low layer TIMER Prescaler for timer
  */
enum hgtimer_v2_psc {
    /*! Timer clock source 0 prescaler
     */
    HGTIMER_V2_TIMER_PSC_0 = 0,
    /*! Timer clock source 2 prescaler
     */
    HGTIMER_V2_TIMER_PSC_2,
    /*! Timer clock source 4 prescaler
     */
    HGTIMER_V2_TIMER_PSC_4,
    /*! Timer clock source 8 prescaler
     */
    HGTIMER_V2_TIMER_PSC_8,
    /*! Timer clock source 16 prescaler
     */
    HGTIMER_V2_TIMER_PSC_16,
    /*! Timer clock source 32 prescaler
     */
    HGTIMER_V2_TIMER_PSC_32,
    /*! Timer clock source 64 prescaler
     */
    HGTIMER_V2_TIMER_PSC_64,
    /*! Timer clock source 128 prescaler
     */
    HGTIMER_V2_TIMER_PSC_128,
};

/**
  * @brief Enumeration constant for low layer TIMER clock source
  */
enum hgtimer_v2_src_sel {
    /*! Timer clock source selection: pin rising
     */
    HGTIMER_V2_SOURCE_PIN_RISING = 0,
    /*! Timer clock source selection: pin falling
     */
    HGTIMER_V2_SOURCE_PIN_FALLING,
    /*! Timer clock source selection: half of 26M
     */
    HGTIMER_V2_SOURCE_HALF_26M,
    /*! Timer clock source selection: half of 13K
     */
    HGTIMER_V2_SOURCE_HALF_32K,
    /*! Timer clock source selection: the rising of sys clk
     */
    HGTIMER_V2_SOURCE_SYS_RISING,
};

/**
  * @brief Enumeration constant for low layer TIMER the pattern of the timer
  */
enum hgtimer_v2_mode_sel {
    /*! Timer mode selection: disable
     */
    HGTIMER_V2_MODE_SEL_DISABLE = 0,
    /*! Timer mode selection: counter mode
     */
    HGTIMER_V2_MODE_SEL_COUNTER,
//    /*! Timer mode selection: PWM mode
//     */
//    HGTIMER_V2_MODE_SEL_PWM,
//    /*! Timer mode selection: capture mode
//     */
//    HGTIMER_V2_MODE_SEL_CAPTURE,
};

/**
  * @}
  */

int32 hgtimer_v2_attach(uint32 dev_id, struct hgtimer_v2 *timer);

#ifdef __cplusplus
}
#endif

#endif /* _HGTIMER_V2_H_ */
