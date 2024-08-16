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
#include "lib/ethernet_phy/phy/sz18201.h"

static int sz18201_config_init(struct ethernet_phy_device *phydev)
{
    /* LED config */
#ifdef LED1_SINGLE_LED_MODE
    phy_write(phydev, 0x1e, 0x40c3);//config led1
    phy_write(phydev, 0x1f, 0x320); //link+ack(default value)
    os_printf("phy led1 - single led mode \n\r");
#endif
#ifdef LED0_SINGLE_LED_MODE
    phy_write(phydev, 0x1e, 0x40c0);//config led0
    phy_write(phydev, 0x1f, 0x320); //link+ack
    os_printf("phy led0 - single led mode \n\r");
#endif
#ifdef SINGLE_LED_MODE
    phy_write(phydev, 0x1e, 0x40c3);//config led1
    phy_write(phydev, 0x1f, 0x320); //link+ack(default value)
    phy_write(phydev, 0x1e, 0x40c0);//config led0
    phy_write(phydev, 0x1f, 0x320); //link+ack
    os_printf("phy single led mode \n\r");
#endif
//#ifdef TWO_LED_MODE //used as default mode
    phy_write(phydev, 0x1e, 0x40c0);//config led0
    phy_write(phydev, 0x1f, 0x1300);//act
    phy_write(phydev, 0x1e, 0x40c3);//config led1
    phy_write(phydev, 0x1f, 0x30);  //link
    os_printf("SZ18201 phy two led mode \n\r");
//#endif
#ifdef TWO_LED_MODE2
    phy_write(phydev, 0x1e, 0x40c3);//config led1
    phy_write(phydev, 0x1f, 0x1300);//act
    phy_write(phydev, 0x1e, 0x40c0);//config led0
    phy_write(phydev, 0x1f, 0x30);  //link
    os_printf("phy two led mode2 \n\r");
#endif
#ifdef TEST_LED_MODE
    //phy_write(phydev, 0x1e, 0x40c3);//config led1
    //phy_write(phydev, 0x1f, 0x20);  //link ok
    //phy_write(phydev, 0x1f, 0x1300);//act ok
    //phy_write(phydev, 0x1f, 0x1320);//link+act ok
    //phy_write(phydev, 0x1e, 0x40c0);//config led0
    //phy_write(phydev, 0x1f, 0x31);  //link 20/21/311/321/320 err 30
    //phy_write(phydev, 0x1f, 0x1320);//act 1300 err
    //os_printf("\n\rphy test led \n\r\n\r");
#endif
    return genphy_config_init(phydev);
}

struct ethernet_phy_driver sz18201_driver = {
    .features       = PHY_BASIC_FEATURES,
    .config_init    = sz18201_config_init,
    .config_aneg    = genphy_config_aneg,
    .read_status    = genphy_read_status,
};
