#ifndef  _HAL_WATCHDOG_H_
#define  _HAL_WATCHDOG_H_

#ifdef __cplusplus
extern "C" {
#endif

enum wdt_mode {
    WDT_MODE_1 = 0,
    WDT_MODE_2 = 1
};

typedef int32(*wdt_irq_hdl)(void);

struct watchdog_device {
    struct dev_obj dev;
    void(*open)(struct watchdog_device *watchdog, uint32 flags);
    uint32(*start)(struct watchdog_device *watchdog, uint32 timeout_s);
    void(*stop)(struct watchdog_device *watchdog);
    void(*feed)(struct watchdog_device *watchdog);
    int32(*request_irq)(struct watchdog_device *watchdog, wdt_irq_hdl irqhdl);
};

static inline void watchdog_device_open(struct watchdog_device *watchdog, uint32 flags)
{
    if (watchdog && watchdog->open) {
        watchdog->open(watchdog, flags);
    }
}
static inline uint32 watchdog_device_start(struct watchdog_device *watchdog, uint32 timeout_s)
{
    if (watchdog && watchdog->start) {
        return watchdog->start(watchdog, timeout_s);
    }
    return 0;
}
static inline void watchdog_device_stop(struct watchdog_device *watchdog)
{
    if (watchdog && watchdog->stop) {
        watchdog->stop(watchdog);
    }
}
static inline void watchdog_device_feed(struct watchdog_device *watchdog)
{
    if (watchdog && watchdog->feed) {
        watchdog->feed(watchdog);
    }
}
static inline int32 watchdog_device_request_irq(struct watchdog_device *watchdog, wdt_irq_hdl irqhdl)
{
    if (watchdog && watchdog->request_irq) {
        return watchdog->request_irq(watchdog, irqhdl);
    }
    return RET_ERR;
}

#ifdef __cplusplus
}
#endif
#endif

