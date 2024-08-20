
#include "typesdef.h"
#include "list.h"
#include "dev.h"
#include "devid.h"
#include "osal/string.h"
#include "osal/mutex.h"
#include "osal/task.h"
#include "osal/semaphore.h"
#include "osal/timer.h"
#include "hal/netdev.h"
#include "hal/dma.h"
#include "lib/skb/skb.h"
#include "lib/mac_bus.h"

struct mac_bus_gmac {
    struct mac_bus              bus;
    struct os_mutex             tx_lock;
    struct netdev              *dev;
};

static void gmac_bus_input_cb(struct netdev *ndev, void *data, uint32 size)
{
//    int32 err = -1;
    struct sk_buff *skb = NULL;
    struct mac_bus_gmac *gmac_bus = (struct mac_bus_gmac *)ndev->priv_data;

    skb = alloc_tx_skb(size + 256 + 32); // 32 bytes prepare for encrypt
    if (skb) {
        skb_reserve(skb, 256);
        hw_memcpy(skb->data, data, size);
        gmac_bus->bus.recv(&gmac_bus->bus, skb, size);
    } else {
        gmac_bus->bus.rxerr++;
    }
}

static int32 gmac_bus_write(struct mac_bus *bus, uint8 *buff, int32 len)
{
    int32 ret = RET_OK;
    struct mac_bus_gmac *gmac_bus = container_of(bus, struct mac_bus_gmac, bus);

    ret = os_mutex_lock(&gmac_bus->tx_lock, 500);
    if (ret) {
        os_printf("gmac bus write wait tx_lock timeout, ret:%d\r\n", ret);
        gmac_bus->bus.txerr++;
        return RET_ERR;
    }
    ret = netdev_send_data(gmac_bus->dev, (void *)buff, len);
    os_mutex_unlock(&gmac_bus->tx_lock);
    if(ret) gmac_bus->bus.txerr++;
    return ret;
}

__init struct mac_bus *mac_bus_gmac_attach(mac_bus_recv recv, void *priv)
{
    int ret = RET_OK;
    struct mac_bus_gmac *gmac_bus = os_zalloc(sizeof(struct mac_bus_gmac));
    ASSERT(gmac_bus && recv);
    gmac_bus->bus.write = gmac_bus_write;
    gmac_bus->bus.type  = MAC_BUS_TYPE_EMAC;
    gmac_bus->bus.recv  = recv;
    gmac_bus->bus.priv  = priv;
    os_mutex_init(&gmac_bus->tx_lock);
    gmac_bus->dev = (struct netdev *)dev_get(HG_GMAC_DEVID);
    ASSERT(gmac_bus->dev);
    gmac_bus->dev->priv_data = gmac_bus;
    ret = netdev_open(gmac_bus->dev, (netdev_input_cb)gmac_bus_input_cb);
    ASSERT(!ret);
    return &gmac_bus->bus;
}

__init void mac_bus_gmac_detach(struct mac_bus *bus)
{
    ASSERT(bus);
    struct mac_bus_gmac *gmac_bus = container_of(bus, struct mac_bus_gmac, bus);
    netdev_close(gmac_bus->dev);
    os_mutex_del(&gmac_bus->tx_lock);
    os_free(gmac_bus);
}

