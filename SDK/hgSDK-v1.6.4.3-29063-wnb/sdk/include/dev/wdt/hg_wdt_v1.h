#ifndef _HGWDT_32K_H
#define _HGWDT_32K_H

#include "hal/watchdog.h"

#ifdef __cplusplus
extern "C" {
#endif

/***** WDT_CON(WDT Config Register) *****/
/*! WDT_PSR Register TYPE_ENUM_LL_WDT_TIMEOUT : Wdt division factor rw registor
 * wdt reset time = 1/32K*256*psr, must write key value 0x5555 before set wdt psr value.It is 8 after reset.
 * division factor(psr)     about reset time
 * 4'h0:no     div            8ms
 * 4'h1:2      div            16ms
 * 4'h2:4      div            32ms
 * 4'h3:8      div            64ms
 * 4'h4:16     div            128ms
 * 4'h5:32     div            256ms
 * 4'h6:64     div            512ms
 * 4'h7:128    div            1024ms
 * 4'h8:256    div            2048ms
 * 4'h9:512    div            4096ms
 * 4'ha:1024   div            8192ms
 * 4'hb:2048   div            16384ms
 * 4'hc:4096   div            32768ms
 * 4'hd:8192   div            65536ms
 * 4'he:16384  div            131072ms
 * 4'hf:32768  div            262144ms
 */
#define LL_WDT_CON_PSR(n)                       (((n)&0xF) << 0)
/*! Used to indicate that wdt enable or disable.
 * 0 : disable, 1 : enable
 * rw registor : Write key value 0xCCCC start wdt,0xDDDD close wdt.
 */
#define LL_WDT_CON_WDTE                         (1UL << 4)
/*! Used to indicate that wdt int enable or disable.
 * 0 : disable, 1 : enable
 * ro registor
 */
#define LL_WDT_CON_IE                           (1UL << 5)
/*! Used to indicate that wdt int count full or not.
 * 0 : wdt count not full , 1 : wdt count full
 * ro registor : Write key value 0xAAAA to clear the pending.
 */
#define LL_WDT_CON_PENDING                      (1UL << 6)
/*! Used to indicate that wdt wakeup enable.
 * .refer to TYPE_ENUM_LL_WDT_KEY
 */
#define LL_WDT_CON_WAKEUP_EN                    (1UL << 9)

/**
  * @brief Enumeration constant for low layer wdt timeout factor( 8 * 2 ^(n))ms
  */
typedef enum {
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 0
     */
    LL_WDT_TO_8MS = 0,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 2
     */
    LL_WDT_TO_16MS,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 4
     */
    LL_WDT_TO_32MS,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 8
     */
    LL_WDT_TO_64MS,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 16
     */
    LL_WDT_TO_128MS,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 32
     */
    LL_WDT_TO_256MS,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 64
     */
    LL_WDT_TO_512MS,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 128
     */
    LL_WDT_TO_1S,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 256
     */
    LL_WDT_TO_2S,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 512
     */
    LL_WDT_TO_4S,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 1024
     */
    LL_WDT_TO_8S,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 2048
     */
    LL_WDT_TO_16S,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 4096
     */
    LL_WDT_TO_32S,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 8192
     */
    LL_WDT_TO_64S,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 16384
     */
    LL_WDT_TO_128S,
    /*! watchdog  timeout factor( 8 * 2 ^(n))ms : 32768
     */
    LL_WDT_TO_256S,
} TYPE_ENUM_LL_WDT_TIMEOUT;

/**
  * @brief Enumeration constant for low layer WDT mode selector
  */
typedef enum {
    /*! timeout watchdog response : Reset
     */
    LL_WDT_RMODE_RST = 0,
    /*! timeout watchdog response : interrupt
     */
    LL_WDT_RMODE_INT,
} TYPE_ENUM_LL_WDT_RMODE;

/**
  * @brief Enumeration constant for low layer WDT KEY selector
  */
typedef enum {
    /*! This key value is used to clear wdt pending.
     *  time out reset mode: This key value must be written at regular intervals during, otherwise a restart will be happened. will also clears the WDT
     *  time out interrupt mode: This key value be written can clear the wdt pending,when pending is 1.
     */
    LL_WDT_KEY_FEED_DOG         = 0xAAAA,
    /*! This key value is used to visit wdtpsr registor.
     *  Must write this key value before set wdt psr value.
     */
    LL_WDT_KEY_CAN_VISIT_PSR    = 0x5555,
    /*! This key value is used to start wdt.
     */
    LL_WDT_KEY_START_DOG        = 0xCCCC,
    /*! This key value is used to close wdt.
     */
    LL_WDT_KEY_CLOSE_DOG        = 0xDDDD,
    /*! This key value is used to enable wdt timeout interrupt.
     */
    LL_WDT_KEY_EN_INT           = 0x55AA,
    /*! This key value is used to disable wdt timeout interrupt, it is at wdt reset mode.
     */
    LL_WDT_KEY_DIS_INT          = 0xAA55,
    /*! This key value is used to enable wdt wakeup.
     */
    LL_WDT_KEY_EN_WAKEUP        = 0x5A5A,
    /*! This key value is used to disable wdt wakeup.
     */
    LL_WDT_KEY_DIS_WAKEUP       = 0xA5A5,
} TYPE_ENUM_LL_WDT_KEY;



/**
  * @brief  Used to indicate that get wdt int en
  * @param  p_wdt : pointer to the hardware WDT_TypeDef
  * @retval None
  */
#define LL_WDT_CHECK_INTERRUPT_ENABLE(p_wdt)           ((p_wdt)->WDTCON & LL_WDT_CON_IE)

/**
  * @brief  Used to indicate that get wdt int pending
  * @param  p_wdt : pointer to the hardware WDT_TypeDef
  * @retval None
  */
#define LL_WDT_GET_PENDING(p_wdt)                      ((p_wdt)->WDTCON & LL_WDT_CON_PENDING)

/**
  * @brief  Used to indicate that get wdt int pending
  * @param  p_wdt : pointer to the hardware WDT_TypeDef
  * @retval None
  */
#define LL_WDT_CLR_PENDING(p_wdt)                      (LL_WDT_SET_KEY(p_wdt, LL_WDT_KEY_FEED_DOG))

/**
  * @brief  Used to set watchdog key
  * @param  p_wdt : pointer to the hardware WDT_TypeDef
  * @param  key   : refer to TYPE_ENUM_LL_WDT_KEY
  * @retval None
  */
#define LL_WDT_SET_KEY(p_wdt, key)                     (((p_wdt)->WDTKEY) = key)

/**
  * @brief  Used to indicate that set psr(division factor)
  * @param  p_wdt : pointer to the hardware WDT_TypeDef
  * @retval None
  */
#define LL_WDT_SET_PSR(p_wdt, n)\
do {\
    LL_WDT_SET_KEY(p_wdt, LL_WDT_KEY_CAN_VISIT_PSR);\
    (p_wdt)->WDTCON = ((p_wdt)->WDTCON & ~(LL_WDT_CON_PSR(0xF))) | LL_WDT_CON_PSR(n);\
} while(0)

/**
  * @brief  Used to indicate that get psr(division factor)
  * @param  p_wdt : pointer to the hardware WDT_TypeDef
  * @retval None
  */
#define LL_WDT_GET_PSR(p_wdt)                          ((((p_wdt)->WDTCON)>>0) & LL_WDT_PSR(0xF))

/**
  * @brief  watchdog wakeup_enable
  * @param  p_wdt : pointer to the hardware WDT_TypeDef
  * @retval None
  */
#define LL_WDT_WAKEUP_ENABLE(p_wdt)                    (((p_wdt)->WDTKEY) = LL_WDT_KEY_EN_WAKEUP)

/**
  * @brief  watchdog wakeup disable
  * @param  p_wdt : pointer to the hardware WDT_TypeDef
  * @retval None
  */
#define LL_WDT_WAKEUP_DISABLE(p_wdt)                   (((p_wdt)->WDTKEY) = LL_WDT_KEY_DIS_WAKEUP)

/**
  * @brief  watchdog wakeup_enable state 
  * @param  p_wdt : pointer to the hardware WDT_TypeDef
  * @retval None
  */
#define LL_WDT_CHECK_WAKEUP_ENABLE(p_wdt)              ((p_wdt)->WDTCON & LL_WDT_CON_WAKEUP_EN)

/**
  * @brief  watchdog enable state 
  * @param  p_wdt : pointer to the hardware WDT_TypeDef
  * @retval None
  */
#define LL_WDT_CHECK_ENABLE(p_wdt)                     ((p_wdt)->WDTCON & LL_WDT_CON_WDTE)



struct hg_wdt_v1_hw {
    __IO uint32 WDTCON;
    __IO uint32 WDTKEY;
};

struct hg_wdt_v1 {
    struct watchdog_device  dev;
    struct hg_wdt_v1_hw    *hw;
    wdt_irq_hdl         irq_hdl;
    uint32              irq_num;
};

int32 hg_wdt_v1_attach(uint32 dev_id, struct hg_wdt_v1 *watchdog);


#ifdef __cplusplus
}
#endif


#endif
















































