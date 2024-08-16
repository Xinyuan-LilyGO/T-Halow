#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "dev.h"
#include "osal/string.h"
#include "osal/irq.h"
#include "hal/watchdog.h"
#include "dev/wdt/hg_wdt_v1.h"

static void hg_wdt_v1_clear_pending(struct hg_wdt_v1 *wdt)
{
    LL_WDT_CLR_PENDING(wdt->hw);
}

static uint32 hg_wdt_v1_time_out_cycle(struct hg_wdt_v1 *wdt, uint32 time_out)
{
    int time_cycle = 6;     /* 7 for 1S  */
    uint32 act_timeout = 1;

    /* ronud up */
    if (time_out & 0x1) {
        time_out--;
        time_cycle++;
    }
    while (time_out) {
        time_cycle++;
        time_out >>= 1;
        act_timeout <<= 1;
    }
    
    LL_WDT_SET_PSR(wdt->hw, time_cycle);

    return act_timeout;
}

static void hg_wdt_v1_irq_handle(void *data)
{
    struct hg_wdt_v1 *wdt = (struct hg_wdt_v1 *)data;
    if (wdt->irq_hdl != NULL) {
        if (wdt->irq_hdl()) {
            hg_wdt_v1_clear_pending(wdt);
        }
    }
}

static void hg_wdt_v1_open(struct watchdog_device *watchdog, uint32 flags)
{
    struct hg_wdt_v1 *wdt = (struct hg_wdt_v1 *)watchdog;
    //sysctrl_wdt_reset();
    LL_WDT_SET_KEY(wdt->hw, LL_WDT_KEY_CLOSE_DOG);
    LL_WDT_SET_KEY(wdt->hw, LL_WDT_KEY_DIS_INT);
}

static void hg_wdt_v1_feed(struct watchdog_device *watchdog)
{
    struct hg_wdt_v1 *wdt = (struct hg_wdt_v1 *)watchdog;
    LL_WDT_SET_KEY(wdt->hw, LL_WDT_KEY_FEED_DOG);
}

static uint32 hg_wdt_v1_start(struct watchdog_device *watchdog, uint32 timeout_s)
{
    struct hg_wdt_v1 *wdt = (struct hg_wdt_v1 *)watchdog;
    uint32 timeout_sec;
    
    timeout_sec = hg_wdt_v1_time_out_cycle(wdt, timeout_s);
    hg_wdt_v1_clear_pending(wdt);
    hg_wdt_v1_feed(watchdog);
    
    LL_WDT_SET_KEY(wdt->hw, LL_WDT_KEY_START_DOG);

    return timeout_sec;
}

static void hg_wdt_v1_stop(struct watchdog_device *watchdog)
{
    struct hg_wdt_v1 *wdt = (struct hg_wdt_v1 *)watchdog;
    LL_WDT_SET_KEY(wdt->hw, LL_WDT_KEY_CLOSE_DOG);
}

int32 hg_wdt_v1_request_irq(struct watchdog_device *watchdog, wdt_irq_hdl irq_hdl)
{
    struct hg_wdt_v1 *wdt = (struct hg_wdt_v1 *)watchdog;
    wdt->irq_hdl = irq_hdl;
    
    LL_WDT_SET_KEY(wdt->hw, LL_WDT_KEY_EN_INT);
    request_irq(wdt->irq_num, hg_wdt_v1_irq_handle, wdt);
    irq_enable(wdt->irq_num);
    return RET_OK;
}

__init int32 hg_wdt_v1_attach(uint32 dev_id, struct hg_wdt_v1 *watchdog)
{
    watchdog->irq_hdl       = NULL;
    watchdog->dev.open      = hg_wdt_v1_open;
    watchdog->dev.start     = hg_wdt_v1_start;
    watchdog->dev.stop      = hg_wdt_v1_stop;
    watchdog->dev.feed      = hg_wdt_v1_feed;
    watchdog->dev.request_irq = hg_wdt_v1_request_irq;
    irq_disable(watchdog->irq_num);
    dev_register(dev_id, (struct dev_obj *)watchdog);
    return RET_OK;
}

