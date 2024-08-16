#include "tx_platform.h"
#include "txw4002ack803/ticker.h"
#include "osal/irq.h"
#include "list.h"
#include "dev.h"
#include "dev/timer/hgtimer_v2.h"

static volatile uint32 hw_timer_intr_cnt;

/**
  * @brief  The tick timer is initialized.
  * @param  None
  * @retval None
  * @note   Use the lowest priority interrupt.
  */
void hw_timer_init(void)
{
    hw_timer_intr_cnt = 0;
    
    TIMER0->TMR_CNT = 0;
    TIMER0->TMR_PR  = 0xFFFF;
    TIMER0->TMR_CON = HGTIMER_V2_CON_TIMER_PNG                              |
                      HGTIMER_V2_CON_TMR_INTR_EN                            |
                      HGTIMER_V2_CON_PSC(HW_TIMER_PSC)                      |
                      HGTIMER_V2_CON_MODE(HGTIMER_V2_MODE_SEL_COUNTER)      |
                      HGTIMER_V2_CON_INC_SRC(HGTIMER_V2_SOURCE_SYS_RISING);
    
    /* Highest priority */
    NVIC_SetPriority(TIM0_IRQn, 0);
    irq_enable(TIM0_IRQn);
}

/**
  * @brief  get the tick of the timer.
  * @param  None
  * @retval None
  */
uint32 hw_timer_get_tick(void)
{
    uint32 cnt, reg;
    
    uint32 flags = disable_irq();
    
    //stop timer
    reg = TIMER0->TMR_CON;
    TIMER0->TMR_CON = 0;
    //Counting interrupts
    cnt = hw_timer_intr_cnt;
    if(reg & HGTIMER_V2_CON_TIMER_PNG) {
        cnt++;
    }
    //calculating time
    cnt = (cnt << 16) | TIMER0->TMR_CNT;
    //Reopen timer
    TIMER0->TMR_CON = reg & 0x7FFFFFFF;
    
    enable_irq(flags);
    
    return cnt;
    
}

/**
  * @brief  tick timer interrupt handler.
  * @param  None
  * @retval None
  */
void hw_timer_irq_handler(void)
{
    if(TIMER0->TMR_CON & HGTIMER_V2_CON_TIMER_PNG) {
        __disable_irq();
        TIMER0->TMR_CON |= HGTIMER_V2_CON_TIMER_PNG;
        hw_timer_intr_cnt++;
        __enable_irq();
    }
}

/**
  * @brief  Use the CPU precision delay function
  * @param  n :
  * @retval None
  * @note   for CK803 : period_count = 3*n+1
  */
__attribute__((noinline, naked, section(".dsleep_text"))) void __delay_asm(uint32 n)
{
    __asm__("                   \
delay_asm_L1:                   \
    DECGT32 R0, R0, 1         \n\
    BT32 delay_asm_L1         \n\
    rts                       \n\
    ");
}

/**
  * @brief  Use the CPU to delay approximately us
  * @param  n : the number of us to delay
  * @retval None
  * @note   only work for SYS_CLK
  */
__at_section(".dsleep_text") void delay_us(uint32 n)
{
    uint32 temp = sys_get_sysclk()/1000000*n;
    
    if(temp > 47) {
        __delay_asm((temp - 47)/3);
    }
}

