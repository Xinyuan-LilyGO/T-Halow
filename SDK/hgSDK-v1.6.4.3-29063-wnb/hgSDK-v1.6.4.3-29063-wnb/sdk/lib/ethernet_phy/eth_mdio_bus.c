#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "dev.h"
#include "osal/string.h"
#include "osal/semaphore.h"
#include "osal/mutex.h"
#include "osal/task.h"
#include "hal/netdev.h"
#include "lib/ethernet_phy/eth_phy.h"
#include "lib/ethernet_phy/eth_mdio_bus.h"

__init int32 eth_mdio_bus_attach(uint32 dev_id, struct ethernet_mdio_bus *p_mdio_bus)
{
    dev_register(dev_id, (struct dev_obj *)p_mdio_bus);
    return RET_OK;
}

int32 eth_mdio_bus_open(struct ethernet_mdio_bus *p_mdio_bus, struct netdev *p_netdev)
{
    if(!(p_netdev && p_netdev->mdio_read && p_netdev->mdio_write && p_mdio_bus)) {
        return RET_ERR;
    }
    
    p_mdio_bus->priv  = p_netdev;
    p_mdio_bus->read  = (int (*)(void *, uint16, uint16))p_netdev->mdio_read;
    p_mdio_bus->write = (void (*)(void *, uint16, uint16, uint16))p_netdev->mdio_write;
    
    return RET_OK;
}

int32 eth_mdio_bus_close(struct ethernet_mdio_bus *p_mdio_bus)
{
    return RET_OK;
}

void eth_mdio_bus_write(struct ethernet_mdio_bus *p_mdio_bus, uint16 phy_addr, uint16 reg_addr, uint16 data)
{
    if(p_mdio_bus && p_mdio_bus->write) {
        p_mdio_bus->write(p_mdio_bus->priv, phy_addr, reg_addr, data);
    }
}

int32 eth_mdio_bus_read(struct ethernet_mdio_bus *p_mdio_bus, uint16 phy_addr, uint16 reg_addr)
{
    if(p_mdio_bus && p_mdio_bus->read) {
        return p_mdio_bus->read(p_mdio_bus->priv, phy_addr, reg_addr);
    }
    
    return 0;
}
