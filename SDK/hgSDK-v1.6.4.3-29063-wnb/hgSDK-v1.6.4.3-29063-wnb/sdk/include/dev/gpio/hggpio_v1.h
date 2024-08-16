
#ifndef _HUGEIC_GPIO_V1_DEVICE_H_
#define _HUGEIC_GPIO_V1_DEVICE_H_
#include "hal/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HGGPIO_V1_MAX_PINS         (32)
/**
  * @breif huge-ic gpio register definition
  */
struct hggpio_v1_hw {
    __IO uint32 DR;
    __IO uint32 DIOE;
    __IO uint32 DIR;
    __IO uint32 INTMASK;
    __IO uint32 PU0EN;
    __IO uint32 PU1EN;
    __IO uint32 PU2EN;
    __IO uint32 PD0EN;
    __IO uint32 PD1EN;
    __IO uint32 PD2EN;
    __IO uint32 DS0;
    __IO uint32 DS1;
    __IO uint32 DS2;
    __IO uint32 HY;
    __IO uint32 OD;
    __IO uint32 SR;
} ;

struct hggpio_v1 {
    struct gpio_device dev;
    struct hggpio_v1_hw *hw;
    uint8 irq_num;
    int8 pin_state[HGGPIO_V1_MAX_PINS];
    int8 event[HGGPIO_V1_MAX_PINS];
    int32 id[HGGPIO_V1_MAX_PINS];
    gpio_irq_hdl irq_hdl[HGGPIO_V1_MAX_PINS];
    uint32 pin_num[2];
};

int32 hggpio_v1_attach(uint32 dev_id, struct hggpio_v1 *gpio);

#ifdef __cplusplus
}
#endif


#endif



