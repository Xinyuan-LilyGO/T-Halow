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
#include "lib/ethernet_phy/phy/ip101g.h"

static int ip101g_config_init(struct ethernet_phy_device *phydev)
{
    /* Disalbe 100BASE-TX EEE capability. Fix the problem of a large number of
     * symbol errors in the communication between IP101GRI and Realtek RTL8168
     * network card.
     */
    phy_write(phydev, 13, 0x0007);
    phy_write(phydev, 14, 0x003C);
    phy_write(phydev, 13, 0x4007);
    phy_write(phydev, 14, 0x0000);
    
    return genphy_config_init(phydev);
}

struct ethernet_phy_driver ip101g_driver = {
    .features       = PHY_BASIC_FEATURES,
    .config_init    = ip101g_config_init,
    .config_aneg    = genphy_config_aneg,
    .read_status    = genphy_read_status,
};
