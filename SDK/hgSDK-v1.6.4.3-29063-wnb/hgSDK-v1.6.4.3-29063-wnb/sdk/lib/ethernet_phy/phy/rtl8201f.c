#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "dev.h"
#include "osal/string.h"
#include "osal/semaphore.h"
#include "osal/mutex.h"
#include "osal/task.h"
#include "hal/netdev.h"
#include "lib/ethernet_phy/eth_mdio_bus.h"
#include "lib/ethernet_phy/eth_phy.h"
#include "lib/ethernet_phy/phy/rtl8201f.h"

static int rtl8201f_config_init(struct ethernet_phy_device *phydev)
{
    uint16 val = 0;

    /* LED config */
    phy_write(phydev, 31, 0x7);
    val = phy_read(phydev, 19);
    val &= 0xffcf;
    phy_write(phydev, 19, val);
    phy_write(phydev, 31, 0);

    return genphy_config_init(phydev);
}

struct ethernet_phy_driver rtl8201f_driver = {
    .features       = PHY_BASIC_FEATURES,
    .config_init    = rtl8201f_config_init,
    .config_aneg    = genphy_config_aneg,
    .read_status    = genphy_read_status,
};
