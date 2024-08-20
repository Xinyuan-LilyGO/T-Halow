/**
 * @file sleep_api.h
 * @author HUGE-IC Application Team
 * @brief Dsleep mode function library
 * @version 1.0.0
 * @date 2021-9-6
 * 
 * @copyright Copyright (c) 2021 HUGE-IC
 */
#ifndef _HGIC_SLEEP_API_H_
#define _HGIC_SLEEP_API_H_

enum sleep_setcfg_cmd {
    SLEEP_SETCFG_GPIOA_RESV,
    SLEEP_SETCFG_GPIOB_RESV,
    SLEEP_SETCFG_GPIOC_RESV,
    SLEEP_SETCFG_SLEEP_US,
    SLEEP_SETCFG_BOOT_MODE,
    SLEEP_SETCFG_DSLEEP_EN,
    SLEEP_SETCFG_WKSRC_DETECT,
    SLEEP_SETCFG_IO_LEVEL_WK,
};

void system_sleep_enter_hook(void);
void system_sleep_wakeup_hook(void);
int32 system_sleep_rxdata_hook(uint8 *data, uint32 len);
void system_sleep_config(uint32 cmd, uint32 param1, uint32 param2);
void system_sleep_reset(void);

void dsleep_gpio_set_val(uint32 pin, uint32 val);
uint32 dsleep_gpio_get_val(uint32 pin);

void dsleep_itoa(int32 n);
void dsleep_print(char *buff);

//void delay_us(uint32 n);
//uint32 io_input_meas_mv(void);

#endif // _HGIC_SLEEP_API_H_