
#include "typesdef.h"
#include "list.h"
#include "dev.h"
#include "devid.h"
#include "osal/string.h"
#include "osal/mutex.h"
#include "osal/task.h"
#include "osal/semaphore.h"
#include "lib/skb/skb.h"
#include "lib/mac_bus.h"

__init struct mac_bus *mac_bus_attach(int bus_type, mac_bus_recv recv, void *priv)
{
    struct mac_bus *bus = NULL;
    switch (bus_type) {
#ifdef MACBUS_SDIO
        case MAC_BUS_TYPE_SDIO:
            bus = mac_bus_sdio_attach(recv, priv);
            break;
#endif
#ifdef MACBUS_USB
        case MAC_BUS_TYPE_USB:
            bus = mac_bus_usb_attach(recv, priv);
            break;
#endif
#ifdef MACBUS_UART
        case MAC_BUS_TYPE_UART:
            bus = mac_bus_uart_attach(recv, priv);
            break;
#endif
#ifdef MACBUS_GMAC
        case MAC_BUS_TYPE_EMAC:
            bus = mac_bus_gmac_attach(recv, priv);
            break;
#endif
#ifdef MACBUS_QA_GMAC
        case MAC_BUS_TYPE_EMAC:
            bus = mac_bus_qa_gmac_attach(recv, priv);
            break;
#endif
#ifdef QC_TEST
        case MAC_BUS_TYPE_QC:
            bus = mac_bus_qc_attach(recv, priv);
            break;
#endif
#ifdef MACBUS_NDEV
        case MAC_BUS_TYPE_NDEV:
            bus = mac_bus_ndev_attach(recv, priv);
            break;
#endif
        case MAC_BUS_TYPE_NONE:
            return 0;
#ifdef MACBUS_COMBI
        case MAC_BUS_TYPE_COMBI:
            bus = mac_bus_combi_attach(recv, priv);
            break;
#endif
        default:
            ASSERT(0);
            break;
    }
    ASSERT(bus);
    return bus;
}

