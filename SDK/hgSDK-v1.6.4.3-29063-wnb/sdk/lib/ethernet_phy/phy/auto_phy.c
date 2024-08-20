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
#include "lib/ethernet_phy/phy/auto_phy.h"

static int auto_phy_config_init(struct ethernet_phy_device *phydev)
{
    uint16 val = 0;
    
    if(phydev->phy_id == 0x2430c54) { // ip101gr
        phy_write(phydev, 13, 0x0007);
        phy_write(phydev, 14, 0x003C);
        phy_write(phydev, 13, 0x4007);
        phy_write(phydev, 14, 0x0000);
        os_printf("IP101GR phy two led mode \n\r");
    } else if(phydev->phy_id == 0x128) { // sz18201
        phy_write(phydev, 0x1e, 0x40c0);//config led0
        phy_write(phydev, 0x1f, 0x1300);//act
        phy_write(phydev, 0x1e, 0x40c3);//config led1
        phy_write(phydev, 0x1f, 0x30);  //link
        os_printf("SZ18201 phy two led mode \n\r");
    } else if(phydev->phy_id == 0x1cc816){ // rt8201
        phy_write(phydev, 31, 0x7);
        val = phy_read(phydev, 19);
        val &= 0xffcf;
        phy_write(phydev, 19, val);
        phy_write(phydev, 31, 0);
        os_printf("RT8201 phy two led mode \n\r");
    } else { // config as rt8201
        phy_write(phydev, 31, 0x7);
        val = phy_read(phydev, 19);
        val &= 0xffcf;
        phy_write(phydev, 19, val);
        phy_write(phydev, 31, 0);
        os_printf("This phy may not be supported! \n\r");
    }

    return genphy_config_init(phydev);
}

struct ethernet_phy_driver auto_phy_driver = {
    .features       = PHY_BASIC_FEATURES,
    .config_init    = auto_phy_config_init,
    .config_aneg    = genphy_config_aneg,
    .read_status    = genphy_read_status,
};
