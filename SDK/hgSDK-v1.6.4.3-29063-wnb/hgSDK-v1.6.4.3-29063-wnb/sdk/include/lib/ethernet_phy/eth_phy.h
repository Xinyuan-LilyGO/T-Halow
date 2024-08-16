/**
  ******************************************************************************
  * @file    sdk/include/lib/ethernet_phy/eth_phy.h
  * @author  HUGE-IC Application Team
  * @version V1.0.0
  * @date    10-10-2018
  * @brief   Framework and drivers for configuring and reading different PHYs
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 HUGE-IC</center></h2>
  *
  *
  *
  ******************************************************************************
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ETH_PHY_H__
#define __ETH_PHY_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ethtool.h"
#include "mii.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @weakgroup NETWORK_PHY
  * @{
  */

/** @defgroup NETWORK_PHY_Exported_Constants Exported Constants
  * @{
  */

#define PHY_ADAPTIVE_ADDR                       -1

#define PHY_INIT_TIMEOUT                        100000
#define PHY_STATE_TIME                          1
#define PHY_FORCE_TIMEOUT                       10
#define PHY_AN_TIMEOUT                          10

#define PHY_MAX_ADDR                            32

#define PHY_BASIC_FEATURES                     (SUPPORTED_10baseT_Half     | \
                                                SUPPORTED_10baseT_Full     | \
                                                SUPPORTED_100baseT_Half    | \
                                                SUPPORTED_100baseT_Full    | \
                                                SUPPORTED_Autoneg          | \
                                                SUPPORTED_TP               | \
                                                SUPPORTED_MII)

#define PHY_GBIT_FEATURES                      (PHY_BASIC_FEATURES         | \
                                                SUPPORTED_1000baseT_Half   | \
                                                SUPPORTED_1000baseT_Full)

/**
  * @}
  */

/** @defgroup NETWORK_PHY_Exported_Typedefs Exported Typedefs
  * @{
  */

struct netdev;
struct ethernet_phy_device;

/* PHY state machine states:
 *
 * DOWN: PHY device and driver are not ready for anything.  probe
 * should be called if and only if the PHY is in this state,
 * given that the PHY device exists.
 * - PHY driver probe function will, depending on the PHY, set
 * the state to STARTING or READY
 *
 * STARTING:  PHY device is coming up, and the ethernet driver is
 * not ready.  PHY drivers may set this in the probe function.
 * If they do, they are responsible for making sure the state is
 * eventually set to indicate whether the PHY is UP or READY,
 * depending on the state when the PHY is done starting up.
 * - PHY driver will set the state to READY
 * - start will set the state to PENDING
 *
 * READY: PHY is ready to send and receive packets, but the
 * controller is not.  By default, PHYs which do not implement
 * probe will be set to this state by phy_probe().  If the PHY
 * driver knows the PHY is ready, and the PHY state is STARTING,
 * then it sets this STATE.
 * - start will set the state to UP
 *
 * PENDING: PHY device is coming up, but the ethernet driver is
 * ready.  phy_start will set this state if the PHY state is
 * STARTING.
 * - PHY driver will set the state to UP when the PHY is ready
 *
 * UP: The PHY and attached device are ready to do work.
 * Interrupts should be started here.
 * - timer moves to AN
 *
 * AN: The PHY is currently negotiating the link state.  Link is
 * therefore down for now.  phy_timer will set this state when it
 * detects the state is UP.  config_aneg will set this state
 * whenever called with phydev->autoneg set to AUTONEG_ENABLE.
 * - If autonegotiation finishes, but there's no link, it sets
 *   the state to NOLINK.
 * - If aneg finishes with link, it sets the state to RUNNING,
 *   and calls adjust_link
 * - If autonegotiation did not finish after an arbitrary amount
 *   of time, autonegotiation should be tried again if the PHY
 *   supports "magic" autonegotiation (back to AN)
 * - If it didn't finish, and no magic_aneg, move to FORCING.
 *
 * NOLINK: PHY is up, but not currently plugged in.
 * - If the timer notes that the link comes back, we move to RUNNING
 * - config_aneg moves to AN
 * - phy_stop moves to HALTED
 *
 * FORCING: PHY is being configured with forced settings
 * - if link is up, move to RUNNING
 * - If link is down, we drop to the next highest setting, and
 *   retry (FORCING) after a timeout
 * - phy_stop moves to HALTED
 *
 * RUNNING: PHY is currently up, running, and possibly sending
 * and/or receiving packets
 * - timer will set CHANGELINK if we're polling (this ensures the
 *   link state is polled every other cycle of this state machine,
 *   which makes it every other second)
 * - irq will set CHANGELINK
 * - config_aneg will set AN
 * - phy_stop moves to HALTED
 *
 * CHANGELINK: PHY experienced a change in link state
 * - timer moves to RUNNING if link
 * - timer moves to NOLINK if the link is down
 * - phy_stop moves to HALTED
 *
 * HALTED: PHY is up, but no polling or interrupts are done. Or
 * PHY is in an error state.
 *
 * - phy_start moves to RESUMING
 *
 * RESUMING: PHY was halted, but now wants to run again.
 * - If we are forcing, or aneg is done, timer moves to RUNNING
 * - If aneg is not done, timer moves to AN
 * - phy_stop moves to HALTED
 */
enum ethernet_phy_state {
    ETH_PHY_DOWN            = 0,
    ETH_PHY_STARTING,
    ETH_PHY_READY,
    ETH_PHY_PENDING,
    ETH_PHY_UP,
    ETH_PHY_AN,
    ETH_PHY_RUNNING,
    ETH_PHY_NOLINK,
    ETH_PHY_FORCING,
    ETH_PHY_CHANGELINK,
    ETH_PHY_HALTED,
    ETH_PHY_RESUMING
};

/* struct phy_driver: Driver structure for a particular PHY type
 *
 * phy_id: The result of reading the UID registers of this PHY
 *   type, and ANDing them with the phy_id_mask.  This driver
 *   only works for PHYs with IDs which match this field
 * name: The friendly name of this PHY type
 * phy_id_mask: Defines the important bits of the phy_id
 * features: A list of features (speed, duplex, etc) supported
 *   by this PHY
 * flags: A bitfield defining certain other features this PHY
 *   supports (like interrupts)
 *
 * The drivers must implement config_aneg and read_status.  All
 * other functions are optional. Note that none of these
 * functions should be called from interrupt time.  The goal is
 * for the bus read/write functions to be able to block when the
 * bus transaction is happening, and be freed up by an interrupt
 * (The MPC85xx has this ability, though it is not currently
 * supported in the driver).
 */
struct ethernet_phy_driver {
    uint32      features;
    
    /*
     * Called to initialize the PHY,
     * including after a reset
     */
    int (*config_init)(struct ethernet_phy_device *phydev);

    /*
     * Called during discovery.  Used to set
     * up device-specific structures, if any
     */
//    int (*probe)(struct ethernet_phy_device *phydev);

    /* PHY Power Management */
//    int (*suspend)(struct ethernet_phy_device *phydev);
//    int (*resume)(struct ethernet_phy_device *phydev);

    /*
     * Configures the advertisement and resets
     * autonegotiation if phydev->autoneg is on,
     * forces the speed to the current settings in phydev
     * if phydev->autoneg is off
     */
    int (*config_aneg)(struct ethernet_phy_device *phydev);

    /* Determines the negotiated speed and duplex */
    int (*read_status)(struct ethernet_phy_device *phydev);

    /* Clears any pending interrupts */
//    int (*ack_interrupt)(struct ethernet_phy_device *phydev);

    /* Enables or disables interrupts */
//    int (*config_intr)(struct ethernet_phy_device *phydev);

    /*
     * Checks if the PHY generated an interrupt.
     * For multi-PHY devices with shared PHY interrupt pin
     */
//    int (*did_interrupt)(struct ethernet_phy_device *phydev);

    /* Clears up any memory if needed */
//    void (*remove)(struct ethernet_phy_device *phydev);

    /* Returns true if this is a suitable driver for the given
     * phydev.  If NULL, matching is based on phy_id and
     * phy_id_mask.
     */
//    int (*match_phy_device)(struct ethernet_phy_device *phydev);

    /* Handles ethtool queries for hardware time stamping. */
//    int (*ts_info)(struct ethernet_phy_device *phydev, struct ethtool_ts_info *ti);

    /* Handles SIOCSHWTSTAMP ioctl for hardware time stamping. */
//    int  (*hwtstamp)(struct ethernet_phy_device *phydev, struct ifreq *ifr);

    /*
     * Requests a Rx timestamp for 'skb'. If the skb is accepted,
     * the phy driver promises to deliver it using netif_rx() as
     * soon as a timestamp becomes available. One of the
     * PTP_CLASS_ values is passed in 'type'. The function must
     * return true if the skb is accepted for delivery.
     */
//    bool (*rxtstamp)(struct ethernet_phy_device *dev, struct sk_buff *skb, int type);

    /*
     * Requests a Tx timestamp for 'skb'. The phy driver promises
     * to deliver it using skb_complete_tx_timestamp() as soon as a
     * timestamp becomes available. One of the PTP_CLASS_ values
     * is passed in 'type'.
     */
//    void (*txtstamp)(struct ethernet_phy_device *dev, struct sk_buff *skb, int type);

    /* Some devices (e.g. qnap TS-119P II) require PHY register changes to
     * enable Wake on LAN, so set_wol is provided to be called in the
     * ethernet driver's set_wol function. */
//    int (*set_wol)(struct ethernet_phy_device *dev, struct ethtool_wolinfo *wol);

    /* See set_wol, but for checking whether Wake on LAN is enabled. */
//    void (*get_wol)(struct ethernet_phy_device *dev, struct ethtool_wolinfo *wol);
};

/* phy_device: An instance of a PHY
 *
 * p_emac_dev: Pointer to the bus this PHY is on
 * phy_id: UID for this device found during discovery
 * state: state of the PHY for management purposes
 * addr: Bus address of PHY
 * link_timeout: The number of timer firings to wait before the
 * giving up on the current attempt at acquiring a link
 * adjust_link: Callback for the enet controller to respond to
 * changes in the link state.
 * adjust_state: Callback for the enet driver to respond to
 * changes in the state machine.
 *
 * speed, duplex, pause, supported, advertising, and
 * autoneg are used like in mii_if_info
 *
 * interrupts currently only supports enabled or disabled,
 * but could be changed in the future to support enabling
 * and disabling specific interrupts
 *
 * Contains some infrastructure for polling and interrupt
 * handling, as well as handling shifts in PHY hardware state
 */
struct ethernet_phy_device {
    struct dev_obj                  dev;
    
    /* Bus address of the PHY (0-31) */
    int16                           addr;
    /* phy driver pointer */
    struct ethernet_phy_driver     *drv;
    
    struct ethernet_mdio_bus       *bus;
    
    struct netdev                  *ndev;
    
    uint32                          phy_id;

    enum ethernet_phy_state         state;

    /*
     * forced speed & duplex (no autoneg)
     * partner speed & duplex & pause (autoneg)
     */
    int16                           speed;
    int16                           duplex;
    int16                           pause;
    int16                           asym_pause;

    /* The most recently read link state */
    int16                           link;
    
    /* Union of PHY and Attached devices' supported modes */
    /* See mii.h for more info */
    uint32                          supported;
    uint32                          advertising;

    uint32                          autoneg;

    uint32                          link_timeout;

    /* last state */
    int16                           last_speed;
    int16                           last_duplex;
    int16                           last_link;
   
    struct os_task                  task;
};

/**
  * @}
  */

/** @defgroup NETWORK_PHY_Exported_Functions Exported Functions
  * @{
  */

extern struct ethernet_phy_driver genphy_driver;

uint16 phy_read(struct ethernet_phy_device *phydev, uint16 reg);
void phy_write(struct ethernet_phy_device *phydev, uint16 reg, uint16 val);

void eth_phy_device_create(struct ethernet_phy_device *dev);
uint8 eth_get_phy_device(struct ethernet_phy_device *dev);
int32 eth_phy_connect_direct(struct ethernet_phy_device *phydev);
uint8 eth_phy_start_aneg(struct ethernet_phy_device *phydev);

int genphy_config_init(struct ethernet_phy_device *phydev);
int genphy_restart_aneg(struct ethernet_phy_device *phydev);
int genphy_config_aneg(struct ethernet_phy_device *phydev);
int genphy_update_link(struct ethernet_phy_device *phydev);
int genphy_read_status(struct ethernet_phy_device *phydev);
void eth_phy_state_machine(struct ethernet_phy_device *phydev);
void eth_phy_start_machine(struct ethernet_phy_device *phydev);

int32 eth_phy_open(struct ethernet_phy_device *phydev, struct ethernet_mdio_bus *mdio_bus, struct netdev *ndev);
void eth_phy_close(struct ethernet_phy_device *phydev);
void eth_phy_attach(uint32 dev_id, struct ethernet_phy_device *phydev);

/**
  * @}
  */ 

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif //__ETH_PHY_H__

/*************************** (C) COPYRIGHT 2018 HUGE-IC ***** END OF FILE *****/
