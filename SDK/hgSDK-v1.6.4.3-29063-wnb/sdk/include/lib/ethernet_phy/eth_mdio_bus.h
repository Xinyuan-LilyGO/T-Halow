#ifndef __ETH_MDIO_BUS_H_
#define __ETH_MDIO_BUS_H_

struct netdev;

/*
 * The Bus class for PHYs.  Devices which provide access to
 * PHYs should register using this structure
 */
struct ethernet_mdio_bus {
    struct dev_obj  dev;
    
    void           *priv;
    int (*read)(void *priv, uint16 phy_addr, uint16 regnum);
    void (*write)(void *priv, uint16 phy_addr, uint16 regnum, uint16 val);

    /*
     * A lock to ensure that only one thing can read/write
     * the MDIO bus at a time
     */
//    struct mutex mdio_lock;
};

int32 eth_mdio_bus_attach(uint32 dev_id, struct ethernet_mdio_bus *p_mii_bus);
int32 eth_mdio_bus_open(struct ethernet_mdio_bus *p_mii_bus, struct netdev *p_netdev);
int32 eth_mdio_bus_close(struct ethernet_mdio_bus *p_mii_bus);
void eth_mdio_bus_write(struct ethernet_mdio_bus *p_mii_bus, uint16 phy_addr, uint16 reg_addr, uint16 data);
int32 eth_mdio_bus_read(struct ethernet_mdio_bus *p_mii_bus, uint16 phy_addr, uint16 reg_addr);

#endif
