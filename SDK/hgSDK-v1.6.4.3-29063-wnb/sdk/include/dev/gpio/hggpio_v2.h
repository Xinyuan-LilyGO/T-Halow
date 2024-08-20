
#ifndef _HUGEIC_GPIO_V2_DEVICE_H_
#define _HUGEIC_GPIO_V2_DEVICE_H_
#include "hal/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HGGPIO_V2_MAX_PINS         (32)
/**
  * @breif huge-ic gpio register definition
  */
struct hggpio_v2_hw {
    __IO uint32 MODE0;
    __IO uint32 MODE1;
    __IO uint32 AFR0;
    __IO uint32 AFR1;
    __IO uint32 AFR2;
    __IO uint32 AFR3;
    __IO uint32 DATA;
    __IO uint32 DEB_EN;
    __IO uint32 INTMASK;
    __IO uint32 PU0EN;
    __IO uint32 PU1EN;
    __IO uint32 PU2EN;
    __IO uint32 PU3EN;
    __IO uint32 PD0EN;
    __IO uint32 PD1EN;
    __IO uint32 PD2EN;
    __IO uint32 PD3EN;
    __IO uint32 DR0;
    __IO uint32 DR1;
    __IO uint32 DR2;
    __IO uint32 DR3;
    __IO uint32 HY;
    __IO uint32 OD;
    __IO uint32 SR;
    __IO uint32 IEM;
    __IO uint32 PND;
} ;

struct hggpio_v2 {
    struct gpio_device dev;
    struct hggpio_v2_hw *hw;
    uint8 irq_num;
    int8 pin_state[HGGPIO_V2_MAX_PINS];
    int8 event[HGGPIO_V2_MAX_PINS];
    int32 id[HGGPIO_V2_MAX_PINS];
    gpio_irq_hdl irq_hdl[HGGPIO_V2_MAX_PINS];
    uint32 pin_num[2];
};

int32 hggpio_v2_attach(uint32 dev_id, struct hggpio_v2 *gpio);

#ifdef __cplusplus
}
#endif


#endif



