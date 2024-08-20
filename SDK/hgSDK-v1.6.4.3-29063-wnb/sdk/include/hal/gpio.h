/**
 * @file gpio.h
 * @author HUGE-IC Application Team
 * @brief GPIO HAL driver
 * @version 1.0.0
 * @date 2021-9-8
 * 
 * @copyright Copyright (c) 2021 HUGE-IC
 */
#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int32 gpio_enable(uint32 pin, uint8 enable);
extern struct gpio_device *gpio_get(uint32 pin);

/**
  * @brief Enumeration constant for GPIO pin direction select
  * @note : this enum must mapping to OS @PinDirection
  */
enum gpio_pin_direction {
    /*! Set GPIO to input mode.
     */
    GPIO_DIR_INPUT,
    /*! Set GPIO to output mode.
     */
    GPIO_DIR_OUTPUT
};

/**
  * @breif : enum of GPIO pin mode
  * @note : this enum must mapping to OS @PinMode
  */
enum gpio_pin_mode {
    /*! gpio mode : push-pull & pull none
     */
    GPIO_PULL_NONE,
    /*! gpio mode : push-pull & pull up
     */
    GPIO_PULL_UP,
    /*! gpio mode : push-pull & pull down
     */
    GPIO_PULL_DOWN,
    /*! gpio mode : open-drain & pull up
     */
    GPIO_OPENDRAIN_PULL_UP,
    /*! gpio mode : open-drain & pull none
     */
    GPIO_OPENDRAIN_PULL_NONE,
    /*! gpio mode : open-drain & pull down
     */
    GPIO_OPENDRAIN_PULL_DOWN,
};

/**
  * @breif : enum of GPIO afio set
  */
enum gpio_afio_set {
    GPIO_AF_0  = 0,
    GPIO_AF_1,
    GPIO_AF_2,
    GPIO_AF_3,
    GPIO_AF_4,
    GPIO_AF_5,
    GPIO_AF_6,
    GPIO_AF_7,
    GPIO_AF_8,
    GPIO_AF_9,
    GPIO_AF_10,
    GPIO_AF_11,
    GPIO_AF_12,
    GPIO_AF_13,
    GPIO_AF_14,
    GPIO_AF_15,
};

/**
  * @breif : enum of GPIO pull level
  */
enum gpio_pull_level {
    /*! gpio pull level : NONE
     */
    GPIO_PULL_LEVEL_NONE = 0,
    /*! gpio pull level : 100K
     */
    GPIO_PULL_LEVEL_100K = 1,
    /*! gpio pull level : 10K
     */
    GPIO_PULL_LEVEL_10K  = 2,
    /*! gpio pull level : 3.4k
     */
    GPIO_PULL_LEVEL_3_4K = 6,
};

/**
  * @breif : enum of GPIO driver strength
  */
enum pin_driver_strength {
    GPIO_DS_7MA = 0, //6.8mA in mars
    GPIO_DS_14MA,    //13.5mA in mars
    GPIO_DS_21MA,    //20mA in mars
    GPIO_DS_28MA,    //27mA in mars
    GPIO_DS_33MA,
    GPIO_DS_40MA,
    GPIO_DS_47MA,
    GPIO_DS_53MA
} ;

enum gpio_irq_event {
    GPIO_IRQ_EVENT_NONE = 0,
    GPIO_IRQ_EVENT_RISE = 0x1,
    GPIO_IRQ_EVENT_FALL = 0x2,
    GPIO_IRQ_EVENT_ALL = GPIO_IRQ_EVENT_RISE | GPIO_IRQ_EVENT_FALL,
};

/**
  * @breif : enum of io control cmd
  */
enum gpio_ioctl_cmd {
    /*! switch GPIO input delay on or off
     */
    GPIO_INPUT_DELAY_ON_OFF,
    /*! Atomic operation in GPIO direction.
     */
    GPIO_DIR_ATOMIC,
    /*! Atomic operation in GPIO vaule.
     */
    GPIO_VALUE_ATOMIC,
};

/**
  * @breif : enum of GPIO speed
  */
enum gpio_speed_en {
    /*! gpio speed low
     */
    GPIO_SPEED_LOW = 0,
    /*! gpio speed high
     */
    GPIO_SPEED_HIGH = 1,
};

typedef void (*gpio_irq_hdl)(int32 id, enum gpio_irq_event event);

struct gpio_device {
    struct dev_obj dev;
    int32(*mode)(struct gpio_device *gpio, uint32 pin, enum gpio_pin_mode mode, enum gpio_pull_level level);
    int32(*dir)(struct gpio_device *gpio, uint32 pin, enum gpio_pin_direction direction);
    int32(*set)(struct gpio_device *gpio, uint32 pin, int32 val);
    int32(*get)(struct gpio_device *gpio, int32 pin);
    int32(*anolog)(struct gpio_device *gpio, uint32 pin, int32 enable);
    int32(*speed)(struct gpio_device *gpio, uint32 pin, int32 speed);
    int32(*driver_strength)(struct gpio_device *gpio, uint32 pin, enum pin_driver_strength strength);
    int32(*request_pin_irq)(struct gpio_device *gpio, uint32 pin, gpio_irq_hdl handler, uint32 data, enum gpio_irq_event evt);
    int32(*release_pin_irq)(struct gpio_device *gpio, uint32 pin, enum gpio_irq_event evt);
    int32(*irq_en)(struct gpio_device *gpio, uint32 pin, uint32 enable);
    int32(*ioctl)(struct gpio_device *gpio, uint32 pin, int32 cmd, int32 val);
    int32(*afio)(struct gpio_device *gpio, uint32 pin, enum gpio_afio_set afio);
};


/**
 * @brief GPIO set mode
 * 
 * @param pin  GPIO pin
 * @param mode  GPIO mode
 * @param level  GPIO pull resistor level
 * @return int32
 * 
 */
static inline int32 gpio_set_mode(uint32 pin, enum gpio_pin_mode mode, enum gpio_pull_level level)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->mode) {
        return gpio->mode(gpio, pin, mode, level);
    }

    return -EINVAL;
}

/**
 * @brief GPIO set direction
 * 
 * @param pin  GPIO pin
 * @param direction  GPIO input/output
 * @return int32
 * 
 */
static inline int32 gpio_set_dir(uint32 pin, enum gpio_pin_direction direction)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->dir) {
        return gpio->dir(gpio, pin, direction);
    }
    return -EINVAL;
}

/**
 * @brief GPIO set ouput logic value
 * 
 * @param pin  GPIO pin
 * @param value  GPIO output value
 * @return int32
 * 
 */
static inline int32 gpio_set_val(uint32 pin, int32 value)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->set) {
        return gpio->set(gpio, pin, value);
    }
    return -EINVAL;
}

/**
 * @brief GPIO get input logic value
 * 
 * @param pin  GPIO pin
 * @return int32
 * @retval GPIO input logic value
 * 
 */
static inline int32 gpio_get_val(uint32 pin)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->get) {
        return gpio->get(gpio, pin);
    }
    return -EINVAL;
}

/**
 * @brief GPIO anolog function
 * 
 * @param pin  GPIO pin
 * @param enable  Enable anolog function
 * @return int32
 * 
 */
static inline int32 gpio_anolog(uint32 pin, int32 enable)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->anolog) {
        return gpio->anolog(gpio, pin, enable);
    }
    return -EINVAL;
}

/**
 * @brief GPIO config IO rise and fall slope
 * 
 * @param pin  GPIO pin
 * @param speed  Signal rise and fall slope
 * @return int32
 * 
 */
static inline int32 gpio_speed(uint32 pin, int32 speed)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->speed) {
        return gpio->speed(gpio, pin, speed);
    }
    return -EINVAL;
}

/**
 * @brief GPIO config driver power
 * 
 * @param pin  GPIO pin
 * @param strength  GPIO driver strength
 * @return int32
 * 
 */
static inline int32 gpio_driver_strength(uint32 pin, enum pin_driver_strength strength)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->driver_strength) {
        return gpio->driver_strength(gpio, pin, strength);
    }
    return -EINVAL;
}

/**
 * @brief GPIO request IRQ
 * 
 * @param pin  GPIO pin
 * @param handler  IRQ handler
 * @param data  IRQ handler data
 * @param evt  Trigger edge
 * @return int32
 * 
 */
static inline int32 gpio_request_pin_irq(uint32 pin, gpio_irq_hdl handler, uint32 data, enum gpio_irq_event evt)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->request_pin_irq) {
        return gpio->request_pin_irq(gpio, pin, handler, data, evt);
    }
    return -EINVAL;
}

/**
 * @brief GPIO release IRQ
 * 
 * @param pin  GPIO pin
 * @param evt  Trigger edge
 * @return int32
 * 
 */
static inline int32 gpio_release_pin_irq(uint32 pin, enum gpio_irq_event evt)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->release_pin_irq) {
        return gpio->release_pin_irq(gpio, pin, evt);
    }
    return -EINVAL;
}

/**
 * @brief GPIO enable IRQ
 * 
 * @param pin  GPIO pin
 * @param enable  
 * @return int32
 * 
 */
static inline int32 gpio_enable_irq(uint32 pin, int32 enable)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->irq_en) {
        return gpio->irq_en(gpio, pin, enable);
    }
    return -EINVAL;
}

static inline int32 gpio_request(uint32 pin)
{
    return gpio_enable(pin, 1);
}

static inline int32 gpio_release(uint32 pin)
{
    return gpio_enable(pin, 0);
}

/**
 * @brief GPIO input/output control
 * 
 * @param pin  GPIO pin
 * @param cmd 
 * @param val 
 * @return int32
 * 
 */
static inline int32 gpio_ioctl(uint32 pin, int32 cmd, int32 val)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->ioctl) {
        return gpio->ioctl(gpio, pin, cmd, val);
    }
    return -EINVAL;
}

static inline int32 gpio_set_altnt_func(uint32 pin, enum gpio_afio_set afio)
{
    struct gpio_device *gpio = gpio_get(pin);

    if (gpio && gpio->afio) {
        return gpio->afio(gpio, pin, afio);
    }
    return -EINVAL;
}

#ifdef __cplusplus
}
#endif
#endif

