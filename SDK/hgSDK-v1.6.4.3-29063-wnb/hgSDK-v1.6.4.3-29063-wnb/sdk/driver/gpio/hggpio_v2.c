// * @file    hggpio_v2.c
// * @author  
// * @brief   This file contains all the hggpio_v2 driver functions.
// Revision History
// V1.0.0  22/06/2019  first release
// V1.0.1  26/06/2019  fix hggpio_v2_afio
// V1.0.2  07/06/2019  change hggpio_v2_set_pull because member values of enum gpio_pull_level are changed
// V1.0.3  08/12/2019  change hggpio_v2_afio to set afr first then set mode
// V1.0.4  02/28/2020  change back2back operation to single operation

#include "typesdef.h"
#include "errno.h"
#include "list.h"
#include "dev.h"
#include "osal/irq.h"
#include "hal/gpio.h"
#include "dev/gpio/hggpio_v2.h"

static inline uint32 hggpio_v2_pin_num(struct hggpio_v2 *gpio, uint32 pin)
{
    return pin - gpio->pin_num[0];
}

static int32 hggpio_v2_set_pull(struct hggpio_v2_hw *reg, uint32 pin,enum gpio_pin_mode pull_mode, enum gpio_pull_level level)
{
    int32  ret = RET_OK;

    if (pin >= HGGPIO_V2_MAX_PINS) {
        return -EINVAL;
    }
    
    sysctrl_unlock();
    switch(pull_mode) {
        case GPIO_PULL_NONE:
        case GPIO_OPENDRAIN_PULL_NONE: 
            switch(pin / 8) {
                case 0:
                    reg->PD0EN &= ~(0xf << pin*4); 
                    reg->PU0EN &= ~(0xf << pin*4);
                    break;
                case 1:
                    reg->PD1EN &= ~(0xf << (pin - 8)*4);
                    reg->PU1EN &= ~(0xf << (pin - 8)*4);
                    break;
                case 2:
                    reg->PD2EN &= ~(0xf << (pin - 16)*4);
                    reg->PU2EN &= ~(0xf << (pin - 16)*4);
                    break;
                case 3:
                    reg->PD3EN &= ~(0xf << (pin - 24)*4);
                    reg->PU3EN &= ~(0xf << (pin - 24)*4);
                    break;
                default:
                    ret = -EINVAL;
                break;
            }
            break;
        case GPIO_PULL_UP:
        case GPIO_OPENDRAIN_PULL_UP: 
            switch(pin / 8) {
                case 0:
                    reg->PU0EN = (reg->PU0EN & ~(0xf << (pin*4))) | (level << (pin*4));
                    break;
                case 1:
                    reg->PU1EN = (reg->PU1EN & ~(0xf << ((pin - 8)*4))) | (level << ((pin - 8)*4));
                    break;
                case 2:
                    reg->PU2EN = (reg->PU2EN & ~(0xf << ((pin - 16)*4))) | (level << ((pin - 16)*4));
                    break;
                case 3:
                    reg->PU3EN = (reg->PU3EN & ~(0xf << ((pin - 24)*4))) | (level << ((pin - 24)*4));
                    break;
                default:
                    ret = -EINVAL;
                break;
            }
            break;
        case GPIO_PULL_DOWN:
        case GPIO_OPENDRAIN_PULL_DOWN: 
            switch(pin / 8) {
                case 0:
                    reg->PD0EN = (reg->PD0EN & ~(0xf << (pin*4))) | (level << (pin*4));
                    break;
                case 1:
                    reg->PD1EN = (reg->PD1EN & ~(0xf << ((pin - 8)*4))) | (level << ((pin - 8)*4));
                    break;
                case 2:
                    reg->PD2EN = (reg->PD2EN & ~(0xf << ((pin - 16)*4))) | (level << ((pin - 16)*4));
                    break;
                case 3:
                    reg->PD3EN = (reg->PD3EN & ~(0xf << ((pin - 24)*4))) | (level << ((pin - 24)*4));
                    break;
                default:
                    ret = -EINVAL;
                break;
            }
            break;
        default:
            ret = -EINVAL;
        break;
    }
    sysctrl_lock();
    
    return ret;
}

static int32 hggpio_v2_set_driver_strength(struct hggpio_v2_hw *reg, uint32 pin, enum pin_driver_strength drive)
{
    int32 ret = RET_OK;

    if ((drive > GPIO_DS_53MA) || (pin >= HGGPIO_V2_MAX_PINS)) {
        return -EINVAL;
    }
    
    sysctrl_unlock();
    switch(pin / 8) {
        case 0:
            reg->DR0 = (reg->DR0 & ~(0xf << (pin*4))) | (drive << (pin*4));
            break;
        case 1:
            reg->DR1 = (reg->DR1 & ~(0xf << ((pin - 8)*4))) | (drive << ((pin - 8)*4));
            break;
        case 2:
            reg->DR2 = (reg->DR2 & ~(0xf << ((pin - 16)*4))) | (drive << ((pin - 16)*4));
            break;
        case 3:
            reg->DR3 = (reg->DR3 & ~(0xf << ((pin - 24)*4))) | (drive << ((pin - 24)*4));
            break;
        default:
            ret = -EINVAL;
        break;
    }
    sysctrl_lock();
    
    return ret;
}

static int32 hggpio_v2_set_mode(struct hggpio_v2_hw *reg, uint32 pin, enum gpio_pin_mode mode, enum gpio_pull_level level)
{
    uint32 pin_bit = 1UL << pin;

    if (pin >= HGGPIO_V2_MAX_PINS) {
        return -EINVAL;
    }
    
    switch (mode) {
        case GPIO_PULL_NONE:
        case GPIO_PULL_UP:
        case GPIO_PULL_DOWN:
            SYSCTRL_REG_OPT(reg->OD &= ~pin_bit);
            break;
        case GPIO_OPENDRAIN_PULL_NONE:
        case GPIO_OPENDRAIN_PULL_UP:
        case GPIO_OPENDRAIN_PULL_DOWN:
            SYSCTRL_REG_OPT(reg->OD |= pin_bit);
            break;
        default:
            return -EINVAL;
    }

    return hggpio_v2_set_pull(reg, pin, mode, level);
}

static int32 hggpio_v2_dir(struct gpio_device *gpio,uint32 pin, enum gpio_pin_direction direction)
{
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }

    pin = hggpio_v2_pin_num(dev, pin);
    if (direction > GPIO_DIR_OUTPUT) {
        return -EINVAL;
    }

    sysctrl_unlock();
    if (direction == GPIO_DIR_INPUT) {
        if(pin / 16) {
            dev->hw->MODE1 &= ~(3UL << (pin - 16)*2);
        } else {
            dev->hw->MODE0 &= ~(3UL << pin*2);
        }
    } else {
        if(pin / 16) {
            dev->hw->MODE1 = (dev->hw->MODE1 & ~(3UL << (pin - 16)*2)) | (1UL << (pin - 16)*2);
        } else {
            dev->hw->MODE0 = (dev->hw->MODE0 & ~(3UL << pin*2)) | (1UL << pin*2);
        }
    }
    sysctrl_lock();
    
    return RET_OK;
}

static int32 hggpio_v2_dir_atomic(struct gpio_device *gpio,uint32 pin, enum gpio_pin_direction direction)
{
#if defined(__CORTEX_M) && ((__CORTEX_M == 0x03) || (__CORTEX_M == 0x04))
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }

    pin = hggpio_v2_pin_num(dev, pin);

    sysctrl_unlock();
    if (GPIO_DIR_INPUT == direction) {
        REG_BIT_BAND((uint32)&dev->hw->MODE0, pin*2)   = 0;
        REG_BIT_BAND((uint32)&dev->hw->MODE0, pin*2+1) = 0;
    } else {
        REG_BIT_BAND((uint32)&dev->hw->MODE0, pin*2)   = 1;
        REG_BIT_BAND((uint32)&dev->hw->MODE0, pin*2+1) = 0;
    }
    sysctrl_lock();
#else
    uint32 flags = disable_irq();
    hggpio_v2_dir(gpio, pin, direction);
    enable_irq(flags);
#endif
    return RET_OK;
}

static int32 hggpio_v2_mode(struct gpio_device *gpio, uint32 pin,enum gpio_pin_mode mode, enum gpio_pull_level level)
{
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }

    pin = hggpio_v2_pin_num(dev, pin);
    return hggpio_v2_set_mode(dev->hw, pin, mode, level);
}

static int32 hggpio_v2_driver_strength(struct gpio_device *gpio,uint32 pin, enum pin_driver_strength drive)
{
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }

    pin = hggpio_v2_pin_num(dev, pin);
    return hggpio_v2_set_driver_strength(dev->hw, pin, drive);
}

static int32 hggpio_v2_get(struct gpio_device *gpio, int32 pin)
{
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }

    pin = hggpio_v2_pin_num(dev, pin);
    return (dev->hw->DATA & (1UL << pin)) ? 1 : 0;
}

static int32 hggpio_v2_set(struct gpio_device *gpio, uint32 pin, int32 value)
{
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }
    pin = hggpio_v2_pin_num(dev, pin);
    if (value) {
        dev->hw->DATA |= (1UL << pin);
    } else {
        dev->hw->DATA &= ~(1UL << pin);
    }

    return RET_OK;
}

static int32 hggpio_v2_set_atomic(struct gpio_device *gpio, uint32 pin, int32 value)
{
#if defined(__CORTEX_M) && ((__CORTEX_M == 0x03) || (__CORTEX_M == 0x04))
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }
    pin = hggpio_v2_pin_num(dev, pin);
    REG_BIT_BAND((uint32)&dev->hw->DATA, pin) = value;
#else
    uint32 flags = disable_irq();
    hggpio_v2_set(gpio, pin, value);
    enable_irq(flags);
#endif
    return RET_OK;
}


/**********************************************************************************/
/*******************     GPIO EXTERNAL FUNCTIONAL     *****************************/
/**********************************************************************************/

static int32 hggpio_v2_anolog_en(struct gpio_device *gpio, uint32 pin, int32 value)
{
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }

    pin = hggpio_v2_pin_num(dev, pin);
    
    sysctrl_unlock();
    if (value) {
        if(pin / 16) {
            dev->hw->MODE1 |= (3UL << (pin - 16)*2);
        } else {
            dev->hw->MODE0 |= (3UL << pin*2);
        }
    } else {
        if(pin / 16) {
            dev->hw->MODE1 = (dev->hw->MODE1 & ~(3UL << (pin - 16)*2)) | (1UL << (pin - 16)*2);
        } else {
            dev->hw->MODE0 = (dev->hw->MODE0 & ~(3UL << pin*2)) | (1UL << pin*2);
        }
    }
    sysctrl_lock();
    
    return RET_OK;
}

static int32 hggpio_v2_input_delay_en(struct hggpio_v2 *gpio, uint32 pin, int32 value)
{
    if ((pin >= HGGPIO_V2_MAX_PINS)) {
        return -EINVAL;
    }

    sysctrl_unlock();
    if (value) {
        gpio->hw->HY |= (1UL << pin);
    } else {
        gpio->hw->HY &= ~(1UL << pin);
    }
    sysctrl_lock();
    
    return RET_OK;
}

static int32 hggpio_v2_speed(struct gpio_device *gpio, uint32 pin, int32 state)
{
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }

    pin = hggpio_v2_pin_num(dev, pin);
    
    sysctrl_unlock();
    if (state) {
        dev->hw->SR |= (1UL << pin);
    } else {
        dev->hw->SR &= ~(1UL << pin);
    }
    sysctrl_lock();
    
    return RET_OK;
}

static int32 hggpio_v2_afio(struct gpio_device *gpio, uint32 pin, enum gpio_afio_set af_sel)
{
    uint32 pin_mode, afrl, afrh, afr, pin_bits;
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }
    pin = hggpio_v2_pin_num(dev, pin);
    pin_bits = 1UL << pin;
    
    sysctrl_unlock();
    if (pin <= 15) {
        //pin[0:15]
        pin_mode = ((pin_bits & 0xFF00)     << 8) | (pin_bits & 0x00FF);
        pin_mode = ((pin_mode & 0x00F000F0) << 4) | (pin_mode & 0x000F000F);
        pin_mode = ((pin_mode & 0x0C0C0C0C) << 2) | (pin_mode & 0x03030303);
        pin_mode = ((pin_mode & 0x22222222) << 1) | (pin_mode & 0x11111111);

        afr  = (pin_mode >> 15)          | pin_mode;
        afr  = ((afr & 0xFF00) << 8)     | (afr & 0x00FF);
        afr  = ((afr & 0x00F000F0) << 4) | (afr & 0x000F000F);
        afr  = ((afr & 0x0C0C0C0C) << 2) | (afr & 0x03030303);
        afrl = afr & 0x11111111;
        afrh = (afr >> 1) & 0x11111111;

        dev->hw->AFR0 = (dev->hw->AFR0 & ~(afrl * 0x0F)) | (afrl * af_sel);
        dev->hw->AFR1 = (dev->hw->AFR1 & ~(afrh * 0x0F)) | (afrh * af_sel);
        
        /* set alternate function mode */
        dev->hw->MODE0 = (dev->hw->MODE0 & ~pin_mode) | (pin_mode << 1);
    } else {
        //pin[16:31]
        pin_mode = (((pin_bits>>16) & 0xFF00)   << 8) | ((pin_bits>>16) & 0x00FF);
        pin_mode = ((pin_mode & 0x00F000F0)     << 4) | (pin_mode & 0x000F000F);
        pin_mode = ((pin_mode & 0x0C0C0C0C)     << 2) | (pin_mode & 0x03030303);
        pin_mode = ((pin_mode & 0x22222222)     << 1) | (pin_mode & 0x11111111);

        afr  = (pin_mode >> 15)          | pin_mode;
        afr  = ((afr & 0xFF00) << 8)     | (afr & 0x00FF);
        afr  = ((afr & 0x00F000F0) << 4) | (afr & 0x000F000F);
        afr  = ((afr & 0x0C0C0C0C) << 2) | (afr & 0x03030303);
        afrl = afr & 0x11111111;
        afrh = (afr >> 1) & 0x11111111;

        dev->hw->AFR2 = (dev->hw->AFR2 & ~(afrl * 0x0F)) | (afrl * af_sel);
        dev->hw->AFR3 = (dev->hw->AFR3 & ~(afrh * 0x0F)) | (afrh * af_sel);
        
        /* set alternate function mode */
        dev->hw->MODE1 = (dev->hw->MODE1 & ~pin_mode) | (pin_mode << 1);
    }
    sysctrl_lock();
    
    return RET_OK;
}

static int32 hggpio_v2_int_en(struct hggpio_v2 *gpio, uint32 pin, int32 value)
{
    if ((pin >= HGGPIO_V2_MAX_PINS)) {
        return -EINVAL;
    }

    sysctrl_unlock();
    if (value) {
        gpio->hw->INTMASK |= (1UL << pin);
    } else {
        gpio->hw->INTMASK &= ~(1UL << pin);
    }
    sysctrl_lock();
    
    return RET_OK;
}

static int32 hggpio_v2_ioctl(struct gpio_device *gpio, uint32 pin, int32 cmd, int32 value)
{
    int32 ret_val = RET_OK;
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }

    pin = hggpio_v2_pin_num(dev, pin);
    switch (cmd) {
        case GPIO_INPUT_DELAY_ON_OFF:
            ret_val = hggpio_v2_input_delay_en(dev, pin, value);
            break;
        case GPIO_VALUE_ATOMIC:
            ret_val = hggpio_v2_set_atomic(gpio, pin, value);
            break;
        case GPIO_DIR_ATOMIC:
            ret_val = hggpio_v2_dir_atomic(gpio, pin, value);
            break;
        default:
            ret_val = -ENOTSUPP;
            break;
    }
    return ret_val;
}

/**********************************************************************************/
/*******************     GPIO    IRQ   FUNCTIONAL     *****************************/
/**********************************************************************************/
static void hggpio_v2_irq_handler(void *data)
{
    int32 i = 0;
    enum gpio_irq_event evt;
    struct hggpio_v2 *dev = (struct hggpio_v2 *)data;
    
    uint32 pending = dev->hw->PND;
    dev->hw->PND = 0;

    for (i = 0; i < HGGPIO_V2_MAX_PINS; i++) {
        if(pending & BIT(i)) {
            //evt = dev->pin_state[i] ? GPIO_IRQ_EVENT_FALL : GPIO_IRQ_EVENT_RISE;
            evt = (dev->hw->DATA & BIT(i)) ? GPIO_IRQ_EVENT_RISE : GPIO_IRQ_EVENT_FALL;
            //dev->pin_state[i] = !dev->pin_state[i];
            if (dev->irq_hdl[i] && (dev->event[i] & (evt))) {
                dev->irq_hdl[i](dev->id[i], evt);
            }
        }
    }
}

static int32 hggpio_v2_request_pin_irq(struct gpio_device *gpio, uint32 pin,gpio_irq_hdl handler, uint32 data, enum gpio_irq_event evt)
{
    int32 ret = RET_OK;
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }

    pin = hggpio_v2_pin_num(dev, pin);
    dev->irq_hdl[pin] = handler;
    dev->id[pin] = data;
    dev->event[pin] = evt;
    dev->pin_state[pin] = (dev->hw->DATA & (1UL << pin)) ? 1 : 0;
    ret = request_irq(dev->irq_num, hggpio_v2_irq_handler, (void *)dev);
    ASSERT(ret == RET_OK);
    hggpio_v2_int_en(dev, pin, 1);
    irq_enable(dev->irq_num);
    return RET_OK;
}

static int32 hggpio_v2_release_pin_irq(struct gpio_device *gpio, uint32 pin,enum gpio_irq_event evt)
{
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }
    pin = hggpio_v2_pin_num(dev, pin);
    dev->event[pin] &= ~evt;
    if (dev->event[pin]) {
        return RET_OK;
    }
    dev->irq_hdl[pin] = NULL;
    return hggpio_v2_int_en(dev, pin, 0);
}

static int32 hggpio_v2_enable_irq(struct gpio_device *gpio, uint32 pin, uint32 enable)
{
    struct hggpio_v2 *dev = (struct hggpio_v2 *)gpio;

    if (pin < dev->pin_num[0] || pin > dev->pin_num[1]) {
        return -EINVAL;
    }

    pin = hggpio_v2_pin_num(dev, pin);
    if (enable) {
        irq_enable(dev->irq_num);
    } else {
        irq_disable(dev->irq_num);
    }
    return RET_OK;
}

__init int32 hggpio_v2_attach(uint32 dev_id, struct hggpio_v2 *gpio)
{
    int32 i = 0;

    gpio->dev.dir = hggpio_v2_dir;
    gpio->dev.mode = hggpio_v2_mode;
    gpio->dev.afio = hggpio_v2_afio;
    gpio->dev.get = hggpio_v2_get;
    gpio->dev.set = hggpio_v2_set;
    gpio->dev.anolog = hggpio_v2_anolog_en;
    gpio->dev.speed = hggpio_v2_speed;
    gpio->dev.driver_strength = hggpio_v2_driver_strength;
    gpio->dev.ioctl = hggpio_v2_ioctl;
    gpio->dev.request_pin_irq = hggpio_v2_request_pin_irq;
    gpio->dev.release_pin_irq = hggpio_v2_release_pin_irq;
    gpio->dev.irq_en = hggpio_v2_enable_irq;

    for (i = 0; i < HGGPIO_V2_MAX_PINS; i++) {
        gpio->irq_hdl[i] = NULL;
    }
    irq_disable(gpio->irq_num);
    dev_register(dev_id, (struct dev_obj *)gpio);
    
    return RET_OK;
}

