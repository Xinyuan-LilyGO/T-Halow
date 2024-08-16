#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "dev.h"
#include "osal/irq.h"
#include "dev/timer/hgtimer_v2.h"

static void hgtimer_v2_irq_handler(void *data)
{
    struct hgtimer_v2 *timer = (struct hgtimer_v2 *)data;

    if (timer->hw->TMR_CON & HGTIMER_V2_CON_TIMER_PNG) {
        if (timer->cb) {
            timer->cb(timer->cb_data);
        }
        timer->hw->TMR_CON |= HGTIMER_V2_CON_TIMER_PNG;
        if (timer->mode == TIMER_TYPE_ONCE) {
            timer->hw->TMR_CON &= ~HGTIMER_V2_CON_MODE_DIS_MASK;
        }
    }
}

static int32 hgtimer_v2_open(struct timer_device *timer, enum timer_type type, uint32 flags)
{
    int32 ret = 0;
    struct hgtimer_v2 *dev = (struct hgtimer_v2 *)timer;

    if (dev->opened) {
        return -EBUSY;
    }
    dev->flags = flags;
    dev->mode  = type;
    dev->opened = 1;
    ret = request_irq(dev->irq_num, hgtimer_v2_irq_handler, dev);
    ASSERT(ret == RET_OK);
    irq_enable(dev->irq_num);

    /*
        set hw resource busy flag
    */

    return RET_OK;
}

static int32 hgtimer_v2_close(struct timer_device *timer)
{
    struct hgtimer_v2 *dev = (struct hgtimer_v2 *)timer;

    if (!dev->opened) {
        return RET_OK;
    }

    dev->flags = 0;
    dev->mode  = TIMER_TYPE_ONCE;
    dev->opened = 0;
    irq_disable(dev->irq_num);
    /*
        release hw resource
    */
    return RET_OK;
}

static int32 hgtimer_v2_start(struct timer_device *timer, uint32 tmo_us, timer_cb_hdl cb, uint32 cb_data)
{
    uint32 i;
    struct hgtimer_v2 *dev = (struct hgtimer_v2 *)timer;
    union {
        uint32 overall;
        uint16 part[2];
    } sys_tick;

    if (!dev->opened) {
        return -ENONET;
    }

    if (tmo_us == 0) {
        return -EINVAL;
    }
    sys_tick.overall = tmo_us * (sys_get_apbclk() / 1000000);
    ASSERT(sys_tick.overall <= (1 << 16) * 128);
    for (i = 0; i < 8; i++) {
        if (sys_tick.part[1] < (1 << i)) {
            break;
        }
    }
    if (i == 8) {
        return RET_ERR;
    }

    dev->cb = cb;
    dev->cb_data = cb_data;
    if(cb) {
        dev->hw->TMR_CON |= HGTIMER_V2_CON_TMR_INTR_EN;
    } else {
        dev->hw->TMR_CON &= ~HGTIMER_V2_CON_TMR_INTR_EN;
    }
    
    dev->hw->TMR_CNT = 0x0000;
    dev->hw->TMR_PR  = (sys_tick.overall >> i) - 1;
    dev->hw->TMR_CON &= ~(HGTIMER_V2_CON_PSC_MASK       |
                          HGTIMER_V2_CON_INC_SRC_MASK   |
                          HGTIMER_V2_CON_MODE_DIS_MASK);
    dev->hw->TMR_CON |= HGTIMER_V2_CON_TIMER_PNG                             |
                        HGTIMER_V2_CON_PSC(i)                                |
                        HGTIMER_V2_CON_INC_SRC(HGTIMER_V2_SOURCE_SYS_RISING) |
                        HGTIMER_V2_CON_MODE(HGTIMER_V2_MODE_SEL_COUNTER);
    return RET_OK;
}

static int32 hgtimer_v2_stop(struct timer_device *timer)
{
    ((struct hgtimer_v2 *)timer)->hw->TMR_CON = 0x0000;
    return RET_OK;
}

static int32 hgtimer_v2_ioctl(struct timer_device *timer, uint32 cmd, uint32 param1, uint32 param2)
{
    struct hgtimer_v2 *dev = (struct hgtimer_v2 *)timer;
    uint32 diff;
    uint32 psc;
    
    switch(cmd) {
        case TIMER_GET_TIMESTAMP:
            return dev->hw->TMR_CNT;
        case TIMER_CALC_TIME_DIFF_US:
            psc = (dev->hw->TMR_CON & HGTIMER_V2_CON_PSC_MASK)>>8;
            if(param2 > param1) {
                diff = param2 - param1;
            } else {
                diff = param2 + dev->hw->TMR_PR - param1;
            }
            return (diff << psc)/(sys_get_apbclk() / 1000000);
        default:
            return RET_ERR;
    }
}

__init int32 hgtimer_v2_attach(uint32 dev_id, struct hgtimer_v2 *timer)
{
    timer->opened       = 0;
    timer->cb           = NULL;
    timer->cb_data      = NULL;
    timer->hw->TMR_CON  = 0x0000;
    timer->dev.open     = hgtimer_v2_open;
    timer->dev.close    = hgtimer_v2_close;
    timer->dev.start    = hgtimer_v2_start;
    timer->dev.stop     = hgtimer_v2_stop;
    timer->dev.ioctl    = hgtimer_v2_ioctl;
    irq_disable(timer->irq_num);
    dev_register(dev_id, (struct dev_obj *)timer);
    return RET_OK;
}

