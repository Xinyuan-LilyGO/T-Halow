/**
  ******************************************************************************
  * @file    sdk/include/lib/ethernet_phy/ethtool.h
  * @author  HUGE-IC Application Team
  * @version V1.0.0
  * @date    10-10-2018
  * @brief   Defines for Linux ethtool
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
#ifndef __ETHTOOL_H__
#define __ETHTOOL_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @weakgroup NETWORK
  * @{
  */

/** @defgroup NETWORK_ETHTOOL Ethtool
  * @brief Defines for Linux ethtool
  * @{
  */ 

/** @defgroup NETWORK_ETHTOOL_Exported_Constants Exported Constants
  * @{
  */

/* Indicates what features are supported by the interface.                      */
#define SUPPORTED_10baseT_Half          (1 << 0)
#define SUPPORTED_10baseT_Full          (1 << 1)
#define SUPPORTED_100baseT_Half         (1 << 2)
#define SUPPORTED_100baseT_Full         (1 << 3)
#define SUPPORTED_1000baseT_Half        (1 << 4)
#define SUPPORTED_1000baseT_Full        (1 << 5)
#define SUPPORTED_Autoneg               (1 << 6)
#define SUPPORTED_TP                    (1 << 7)
#define SUPPORTED_AUI                   (1 << 8)
#define SUPPORTED_MII                   (1 << 9)
#define SUPPORTED_FIBRE                 (1 << 10)
#define SUPPORTED_BNC                   (1 << 11)
#define SUPPORTED_10000baseT_Full       (1 << 12)
#define SUPPORTED_Pause                 (1 << 13)
#define SUPPORTED_Asym_Pause            (1 << 14)
#define SUPPORTED_2500baseX_Full        (1 << 15)
#define SUPPORTED_Backplane             (1 << 16)
#define SUPPORTED_1000baseKX_Full       (1 << 17)
#define SUPPORTED_10000baseKX4_Full     (1 << 18)
#define SUPPORTED_10000baseKR_Full      (1 << 19)
#define SUPPORTED_10000baseR_FEC        (1 << 20)
#define SUPPORTED_20000baseMLD2_Full    (1 << 21)
#define SUPPORTED_20000baseKR2_Full     (1 << 22)
#define SUPPORTED_40000baseKR4_Full     (1 << 23)
#define SUPPORTED_40000baseCR4_Full     (1 << 24)
#define SUPPORTED_40000baseSR4_Full     (1 << 25)
#define SUPPORTED_40000baseLR4_Full     (1 << 26)

/* Indicates what features are advertised by the interface.                     */
#define ADVERTISED_10baseT_Half         (1 << 0)
#define ADVERTISED_10baseT_Full         (1 << 1)
#define ADVERTISED_100baseT_Half        (1 << 2)
#define ADVERTISED_100baseT_Full        (1 << 3)
#define ADVERTISED_1000baseT_Half       (1 << 4)
#define ADVERTISED_1000baseT_Full       (1 << 5)
#define ADVERTISED_Autoneg              (1 << 6)
#define ADVERTISED_TP                   (1 << 7)
#define ADVERTISED_AUI                  (1 << 8)
#define ADVERTISED_MII                  (1 << 9)
#define ADVERTISED_FIBRE                (1 << 10)
#define ADVERTISED_BNC                  (1 << 11)
#define ADVERTISED_10000baseT_Full      (1 << 12)
#define ADVERTISED_Pause                (1 << 13)
#define ADVERTISED_Asym_Pause           (1 << 14)
#define ADVERTISED_2500baseX_Full       (1 << 15)
#define ADVERTISED_Backplane            (1 << 16)
#define ADVERTISED_1000baseKX_Full      (1 << 17)
#define ADVERTISED_10000baseKX4_Full    (1 << 18)
#define ADVERTISED_10000baseKR_Full     (1 << 19)
#define ADVERTISED_10000baseR_FEC       (1 << 20)
#define ADVERTISED_20000baseMLD2_Full   (1 << 21)
#define ADVERTISED_20000baseKR2_Full    (1 << 22)
#define ADVERTISED_40000baseKR4_Full    (1 << 23)
#define ADVERTISED_40000baseCR4_Full    (1 << 24)
#define ADVERTISED_40000baseSR4_Full    (1 << 25)
#define ADVERTISED_40000baseLR4_Full    (1 << 26)

/* The following are all involved in forcing a particular link mode for the
 * device for setting things.  When getting the devices settings, these
 * indicate the current mode and whether it was forced up into this mode or
 * autonegotiated.
 */

/* The forced speed, 10Mb, 100Mb, gigabit, 2.5Gb, 10GbE.                        */
#define SPEED_10                        10
#define SPEED_100                       100
#define SPEED_1000                      1000
#define SPEED_2500                      2500
#define SPEED_10000                     10000
#define SPEED_UNKNOWN                   -1

/* Duplex, half or full.                                                        */
#define DUPLEX_HALF                     0x00
#define DUPLEX_FULL                     0x01
#define DUPLEX_UNKNOWN                  0xff

/* Which connector port.                                                        */
#define PORT_TP                         0x00
#define PORT_AUI                        0x01
#define PORT_MII                        0x02
#define PORT_FIBRE                      0x03
#define PORT_BNC                        0x04
#define PORT_DA                         0x05
#define PORT_NONE                       0xEF
#define PORT_OTHER                      0xFF

/* Which transceiver to use.                                                    */
#define XCVR_INTERNAL                   0x00
#define XCVR_EXTERNAL                   0x01
#define XCVR_DUMMY1                     0x02
#define XCVR_DUMMY2                     0x03
#define XCVR_DUMMY3                     0x04

/* Enable or disable autonegotiation.  If this is set to enable, the forced
 * link modes above are completely ignored.
 */
#define AUTONEG_DISABLE                 0x00
#define AUTONEG_ENABLE                  0x01

  
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif //__ETHTOOL_H__

/*************************** (C) COPYRIGHT 2018 HUGE-IC ***** END OF FILE *****/
