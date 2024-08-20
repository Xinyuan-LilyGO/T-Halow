/**
  ******************************************************************************
  * @file    sdk/lib/ethernet_phy/eth_phy.c
  * @author  HUGE-IC Application Team
  * @version V1.0.0
  * @date    10-10-2018
  * @brief   Framework for configuring and reading PHY devices
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 HUGE-IC</center></h2>
  *
  *
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "typesdef.h"
#include "errno.h"
#include "list.h"
#include "dev.h"
#include "osal/task.h"
#include "osal/sleep.h"
#include "ethernet_phy/eth_phy.h"
#include "hal/netdev.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define MAX_NUM_SETTINGS                ARRAY_SIZE(settings)
/* Private variables ---------------------------------------------------------*/
/**
  * @brief A structure for mapping a particular speed and duplex combination
  *        to a particular SUPPORTED and ADVERTISED value
  */
struct __phy_setting {
    int16   speed;
    int16   duplex;
    uint32  setting;
};

/**
  * @brief A mapping of all SUPPORTED settings to speed/duplex
  */
static const struct __phy_setting settings[] = {
    {
        .speed   = SPEED_1000,
        .duplex  = DUPLEX_FULL,
        .setting = SUPPORTED_1000baseT_Full,
    },
    {
        .speed   = SPEED_1000,
        .duplex  = DUPLEX_HALF,
        .setting = SUPPORTED_1000baseT_Half,
    },
    {
        .speed   = SPEED_100,
        .duplex  = DUPLEX_FULL,
        .setting = SUPPORTED_100baseT_Full,
    },
    {
        .speed   = SPEED_100,
        .duplex  = DUPLEX_HALF,
        .setting = SUPPORTED_100baseT_Half,
    },
    {
        .speed   = SPEED_10,
        .duplex  = DUPLEX_FULL,
        .setting = SUPPORTED_10baseT_Full,
    },
    {
        .speed   = SPEED_10,
        .duplex  = DUPLEX_HALF,
        .setting = SUPPORTED_10baseT_Half,
    },
};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @addtogroup NETWORK
  * @{
  */

/** @defgroup NETWORK_PHY PHY Framework
  * @brief    Framework for finding and configuring PHYs.  
  *           Also contains generic PHY driver
  * @{
  */ 
  
/**
  * @brief  return auto-negotiation status
  * @param  phydev : target phy_device struct
  * @retval auto-negotiation status
  * @note   Reads the status register and returns 0 either if 
  *         auto-negotiation is incomplete, or if there was an error.
  *         Returns BMSR_ANEGCOMPLETE if auto-negotiation is done.
  */
static inline int eth_phy_aneg_done(struct ethernet_phy_device *phydev)
{
    int retval;

    retval = phy_read(phydev, MII_BMSR);

    return (retval < 0) ? retval : (retval & BMSR_ANEGCOMPLETE);
}

/**
  * @brief  find a PHY settings array entry that matches speed & duplex
  * @param  advertising  :
  * @retval the index of that setting
  * @note   Searches the settings array for the setting which matches the
  *         desired speed and duplex, and returns the index of that setting.
  *         Returns the index of the last setting if none of the others
  *         match.
  */
static inline int eth_phy_find_setting(uint32 advertising)
{
    int idx = 0;

    while(idx < ARRAY_SIZE(settings) && (!(advertising & settings[idx].setting))) {
        idx++;
    }
    return idx < MAX_NUM_SETTINGS ? idx : MAX_NUM_SETTINGS - 1;
}

/**
  * @brief  find a PHY setting that matches the requested features mask
  * @param  idx : The first index in settings[] to search
  * @retval the index of the first valid setting
  * @note   Returns the index of the first valid setting less than or equal
  *         to the one pointed to by idx, as determined by the mask in
  *         features. Returns the index of the last setting if nothing else
  *         matches.
  */
static inline int eth_phy_find_valid(int idx, uint32 features)
{
    while(idx < MAX_NUM_SETTINGS && !(settings[idx].setting & features)) {
        idx++;
    }

    return idx < MAX_NUM_SETTINGS ? idx : MAX_NUM_SETTINGS - 1;
}

/**
  * @brief  make sure the PHY is set to supported speed and duplex
  * @param  phydev : the target phy_device struct
  * @retval None
  * @note   Make sure the PHY is set to supported speeds and duplexes. Drop
  *         down by one in this order:  
  *         1000/FULL, 1000/HALF, 100/FULL, 100/HALF, 10/FULL, 10/HALF.
  */
static void eth_phy_sanitize_settings(struct ethernet_phy_device *phydev)
{
    uint32 features = phydev->supported;
    int idx;

    /* Sanitize settings based on PHY capabilities */
    if ((features & SUPPORTED_Autoneg) == 0) {
        phydev->autoneg = AUTONEG_DISABLE;
    }
    idx = eth_phy_find_valid(eth_phy_find_setting(phydev->advertising), features);

    phydev->speed  = settings[idx].speed;
    phydev->duplex = settings[idx].duplex;
}

/**
  * @brief  start auto-negotiation for this PHY device
  * @param  phydev : the phy_device struct
  * @retval Returning 0 means that the PHY does not support
  *         auto-negotiation.
  * @note   Sanitizes the settings (if we're not autonegotiating them), and
  *         then calls the driver's config_aneg function. If the PHYCONTROL
  *         Layer is operating, we change the state to reflect the beginning
  *         of Auto-negotiation or forcing.
  */
uint8 eth_phy_start_aneg(struct ethernet_phy_device *phydev)
{
    int err;

    if (AUTONEG_DISABLE == phydev->autoneg)
        eth_phy_sanitize_settings(phydev);

    err = phydev->drv->config_aneg(phydev);

    if (err < 0)
        return 0;

    if (phydev->state != ETH_PHY_HALTED) {
        if (AUTONEG_ENABLE == phydev->autoneg) {
            phydev->state = ETH_PHY_AN;
        } else {
            phydev->state = ETH_PHY_FORCING;
        }
    }
    return 1;
}

/**
  * @brief  start PHY state machine tracking
  * @param  phydev  : the phy_device struct
  * @param  handler : callback function for state change notifications
  * @retval None
  * @note   The PHY infrastructure can run a state machine which tracks
  *         whether the PHY is starting up, negotiating, etc. This function
  *         starts the timer which tracks the state of the PHY. If you want
  *         to be notified when the state changes, pass in the callback
  *         @handler, otherwise, pass NULL. If you want to maintain your own
  *         state machine, do not call this function.
  */
void eth_phy_start_machine(struct ethernet_phy_device *phydev)
{
    //phydev->adjust_state = handler;
}

/**
  * @brief  Handle the state machine
  * @param  phydev : target phy_device struct
  * @retval None
  */
void eth_phy_state_machine(struct ethernet_phy_device *phydev)
{
    int needs_aneg = 0;
    int err = 0;
    
    //if(phydev->adjust_state) {
    //    phydev->adjust_state(phydev);
    //}
    switch(phydev->state) {
        case ETH_PHY_DOWN:
        case ETH_PHY_STARTING:
        case ETH_PHY_READY:
        case ETH_PHY_PENDING:
            break;
        
        case ETH_PHY_UP:
            needs_aneg = 1;
            break;
        
        case ETH_PHY_AN:
            err = phydev->drv->read_status(phydev);

            if(err < 0) {
                break;
            }
            /* If the link is down, give up on
             * negotiation for now */
            if(!phydev->link) {
                phydev->state = ETH_PHY_NOLINK;
                phydev->ndev->phy_event(phydev, NETDEV_PHY_EVENT_LINK_CHANGED, phydev->link, 0);
                break;
            }

            /* Check if negotiation is done.  Break
             * if there's an error */
            err = eth_phy_aneg_done(phydev);
            if(err < 0) {
                break;
            }
            /* If AN is done, we're running */
            if(err > 0) {
                phydev->state = ETH_PHY_RUNNING;
                phydev->ndev->phy_event(phydev, NETDEV_PHY_EVENT_LINK_CHANGED, phydev->link, 0);
            } else if(0 == phydev->link_timeout--) {
                needs_aneg = 1;
            }
            break;
            
        case ETH_PHY_NOLINK:
            err = phydev->drv->read_status(phydev);

            if(err) {
                break;
            }
            if(phydev->link) {
                phydev->state = ETH_PHY_RUNNING;
                phydev->ndev->phy_event(phydev, NETDEV_PHY_EVENT_LINK_CHANGED, phydev->link, 0);
            }
            break;
            
        case ETH_PHY_FORCING:
            err = genphy_update_link(phydev);

            if(err) {
                break;
            }
            if(phydev->link) {
                phydev->state = ETH_PHY_RUNNING;
            } else {
                if (0 == phydev->link_timeout--) {
                    needs_aneg = 1;
                }
            }

            phydev->ndev->phy_event(phydev, NETDEV_PHY_EVENT_LINK_CHANGED, phydev->link, 0);
            break;
            
        case ETH_PHY_RUNNING:
            err = phydev->drv->read_status(phydev);

            if(err) {
                break;
            }
            if(phydev->link) {
                phydev->state = ETH_PHY_RUNNING;
            } else {
                phydev->state = ETH_PHY_NOLINK;
            }
            phydev->ndev->phy_event(phydev, NETDEV_PHY_EVENT_LINK_CHANGED, phydev->link, 0);
            break;
            
        case ETH_PHY_HALTED:
            if(phydev->link) {
                phydev->link = 0;
                phydev->ndev->phy_event(phydev, NETDEV_PHY_EVENT_LINK_CHANGED, phydev->link, 0);
            }
            break;
            
        default:
                break;
    }

    if(needs_aneg) {
        err = eth_phy_start_aneg(phydev);
    }
}

/**
  * @brief  Handle the state machine thread
  * @param  phydev : target phy_device struct
  * @retval None
  */
static void eth_phy_state_machine_thread(void *argument)
{
    struct ethernet_phy_device *phydev = (struct ethernet_phy_device *)argument;
    while(1) {
        eth_phy_state_machine(phydev);
        /* Execute every 200ms */
        os_sleep_ms(200);
    }
}


int32 eth_phy_open(struct ethernet_phy_device *phydev, struct ethernet_mdio_bus *mdio_bus, struct netdev *ndev)
{
    uint32 feature_supproted = phydev->drv->features;

    if(!phydev || !mdio_bus) {
        return RET_ERR;
    }
    
    phydev->ndev = ndev;
    ASSERT(ndev);
    phydev->bus  = mdio_bus;
    ASSERT(mdio_bus);
    
    if(eth_get_phy_device(phydev)) {
        phydev->state = ETH_PHY_READY;
    } else {
        return RET_ERR;
    }

    /* attach the mac to the phy */
    if(eth_phy_connect_direct(phydev) == RET_ERR) {
        return RET_ERR;
    }
    
    /* Only support features that we can support */
    phydev->advertising &= feature_supproted;
    if(feature_supproted & SUPPORTED_Autoneg) {
        phydev->autoneg = AUTONEG_ENABLE;
    } else {
        phydev->autoneg = AUTONEG_DISABLE;
    }

    /* Initial invalid value */
    phydev->last_link   = 0;
    phydev->last_speed  = 0;
    phydev->last_duplex = -1;
    
    /* start */
    phydev->state = ETH_PHY_UP;
    
    OS_TASK_INIT("eth machine", &phydev->task, eth_phy_state_machine_thread, (uint32)phydev, OS_TASK_PRIORITY_BELOW_NORMAL, 512);
    
    return RET_OK;
}

void eth_phy_close(struct ethernet_phy_device *phydev)
{
    os_task_del(&phydev->task);
}

__init void eth_phy_attach(uint32 dev_id, struct ethernet_phy_device *phydev)
{
    dev_register(dev_id, (struct dev_obj *)phydev);
}

/**
  * @}
  */

/**
  * @}
  */

/*************************** (C) COPYRIGHT 2018 HUGE-IC ***** END OF FILE *****/
