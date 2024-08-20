#ifndef _TICKER_H_
#define _TICKER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TIMER0_BASE             (APB1_BASE + 0x5000)
#define TIMER0                  ((struct hgtimer_v2_hw *) TIMER0_BASE)

#if DEFAULT_SYS_CLK < 2000000
    #define HW_TIMER_PSC        0//HGTIMER_V2_TIMER_PSC_0
#elif DEFAULT_SYS_CLK < 4000000
    #define HW_TIMER_PSC        1//HGTIMER_V2_TIMER_PSC_2
#elif DEFAULT_SYS_CLK < 8000000
    #define HW_TIMER_PSC        2//HGTIMER_V2_TIMER_PSC_4
#elif DEFAULT_SYS_CLK < 16000000
    #define HW_TIMER_PSC        3//HGTIMER_V2_TIMER_PSC_8
#elif DEFAULT_SYS_CLK < 32000000
    #define HW_TIMER_PSC        4//HGTIMER_V2_TIMER_PSC_16
#elif DEFAULT_SYS_CLK < 64000000
    #define HW_TIMER_PSC        5//HGTIMER_V2_TIMER_PSC_32
#elif DEFAULT_SYS_CLK < 128000000
    #define HW_TIMER_PSC        6//HGTIMER_V2_TIMER_PSC_64
#else
    #define HW_TIMER_PSC        7//HGTIMER_V2_TIMER_PSC_128
#endif

/**
  * @brief  Time(us) to timer tick
  * @param  n : Time in us
  * @retval Time(us) to timer tick
  */
#define HW_TIMER_T2C(n)         (((n)*(DEFAULT_SYS_CLK/1000000)) >> (HW_TIMER_PSC))
/**
  * @brief  timer tick to Time(us)
  * @param  n : timer tick
  * @retval timer tick to Time(us)
  */
#define HW_TIMER_C2T(n)         ((n)*(1 << HW_TIMER_PSC)/(DEFAULT_SYS_CLK/1000000))

/**
  * @brief  The tick timer is initialized.
  * @param  None
  * @retval None
  * @note   Use the lowest priority interrupt.
  */
void hw_timer_init(void);

/**
  * @brief  get the tick of the timer.
  * @param  None
  * @retval None
  */
uint32 hw_timer_get_tick(void);

/**
  * @brief  tick timer interrupt handler.
  * @param  None
  * @retval None
  */
void hw_timer_irq_handler(void);

#ifdef __cplusplus
}
#endif
#endif
