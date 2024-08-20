#ifndef _HAL_TIMER_DEVICE_H_
#define _HAL_TIMER_DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief timer type
  */
enum timer_type {
    TIMER_TYPE_ONCE,
    TIMER_TYPE_PERIODIC,
};

enum timer_device_ioctl_cmd {
    TIMER_GET_TIMESTAMP,
    TIMER_CALC_TIME_DIFF_US,
};

typedef void (*timer_cb_hdl)(uint32 cb_data);

struct timer_device {
    struct dev_obj dev;
    int32(*open)(struct timer_device *timer, enum timer_type type, uint32 flags);
    int32(*close)(struct timer_device *timer);
    int32(*start)(struct timer_device *timer, uint32 tmo_us, timer_cb_hdl cb, uint32 cb_data);
    int32(*stop)(struct timer_device *timer);
    int32(*ioctl)(struct timer_device *timer, uint32 cmd, uint32 param1, uint32 param2);
};

static inline int32 timer_device_open(struct timer_device *timer, enum timer_type type, uint32 flags)
{
    if (timer && timer->open) {
        return timer->open(timer, type, flags);
    }
    return RET_ERR;
}

static inline int32 timer_device_close(struct timer_device *timer)
{
    if (timer && timer->close) {
        return timer->close(timer);
    }
    return RET_ERR;
}

static inline int32 timer_device_start(struct timer_device *timer, uint32 tmo_us, timer_cb_hdl cb, uint32 cb_data)
{
    if (timer && timer->start) {
        return timer->start(timer, tmo_us, cb, cb_data);
    }
    return RET_ERR;
}

static inline int32 timer_device_stop(struct timer_device *timer)
{
    if (timer && timer->stop) {
        return timer->stop(timer);
    }
    return RET_ERR;
}

static inline int32 timer_device_ioctl(struct timer_device *timer, uint32 cmd, uint32 param1, uint32 param2)
{
    if(timer && timer->ioctl) {
        return timer->ioctl(timer, cmd, param1, param2);
    }
    return RET_ERR;
}

#ifdef __cplusplus
}
#endif
#endif

