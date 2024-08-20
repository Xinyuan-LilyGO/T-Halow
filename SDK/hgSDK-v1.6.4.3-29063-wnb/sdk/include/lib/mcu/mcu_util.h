#ifndef _MCU_UTIL_H_
#define _MCU_UTIL_H_

int32 mcu_init(void);
int32 mcu_pir_sensor_set(uint8 level);
uint8 mcu_pir_sensor_get(void);
uint8 mcu_battery_soc_get(void);

#endif