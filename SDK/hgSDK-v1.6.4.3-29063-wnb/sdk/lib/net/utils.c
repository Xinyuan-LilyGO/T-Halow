#include "typesdef.h"
#include "errno.h"
#include "list.h"
#include "dev.h"
#include "devid.h"
#include "list.h"
#include "osal/string.h"
#include "osal/mutex.h"
#include "osal/semaphore.h"
#include "osal/mutex.h"
#include "osal/task.h"
#include "osal/timer.h"
#include "hal/gpio.h"
#include "lib/skb/skb.h"
#include "lib/skb/skb_list.h"
#include "lib/net/utils.h"

uint16 net_checksum(uint16 initcksum, uint8 *data, int32 len)
{
    uint32 cksum;
    int32  idx;
    int32  odd;

    cksum = (uint32)initcksum;
    odd   = len & 1;
    len  -= odd;
    for (idx = 0; idx < len; idx += 2) {
        cksum += ((uint32) data[idx] << 8) + ((uint32) data[idx + 1]);
    }
    if (odd) { /* buffer is odd length */
        cksum += ((uint32) data[idx] << 8);
    }
    /* Fold in the carries */
    while (cksum >> 16) {
        cksum = (cksum & 0xFFFF) + (cksum >> 16);
    }
    return cksum;
}

uint16 net_pseudo_checksum(uint8 proto, uint8 *data, uint16 len, uint32 *srcaddr, uint32 *destaddr)
{
    uint8  pseudoheader[12];
    uint16 calccksum;

    os_memcpy(&pseudoheader[0], srcaddr, 4);
    os_memcpy(&pseudoheader[4], destaddr, 4);
    pseudoheader[8]  = 0;
    pseudoheader[9]  = proto;
    put_unaligned_be16(len, pseudoheader + 10);

    calccksum = net_checksum(0, pseudoheader, sizeof(pseudoheader));
    calccksum = net_checksum(calccksum, data, len);
    calccksum = ~calccksum;
    return calccksum;
}

struct sk_buff *net_setup_udpdata(struct udpdata_info *data)
{
    struct sk_buff *skb = NULL;
    uint32 len   = 0;
    uint16 cksum = 0;

    if (data == NULL) {
        return NULL;
    }

    len = data->len + 42;
    if (len > 1500) {
        len = 1500;
    }

    skb = alloc_skb(len + 256 + 32);
    if (skb) {
        skb_reserve(skb, 256);
        //ether hdr
        os_memcpy(skb->data, data->dest, 6);
        os_memcpy(skb->data + 6, data->src, 6);
        put_unaligned_be16(0x800, skb->data + 12);

        //ip hdr
        skb->data[14] = 0x45;
        skb->data[15] = 0x00;
        put_unaligned_be16(len - 14, skb->data + 16);
        skb->data[18] = 0x00;
        skb->data[19] = 0x00;
        skb->data[20] = 0x40;
        skb->data[21] = 0x00;
        skb->data[22] = 0x40;
        skb->data[23] = 0x11;
        skb->data[24] = 0x00; //ip checksum
        skb->data[25] = 0x00;
        put_unaligned_be32(data->src_ip, skb->data + 26);
        put_unaligned_be32(data->dest_ip, skb->data + 30);
        cksum = ~ net_checksum(0, skb->data + 14, 20);
        put_unaligned_be16(cksum, skb->data + 24); //ip checksum

        //udp hdr
        put_unaligned_be16(data->src_port, skb->data + 34);
        put_unaligned_be16(data->dest_port, skb->data + 36);
        put_unaligned_be16(len - 34, skb->data + 38);
        skb->data[40] = 0x00;//udp checksum
        skb->data[41] = 0x00;
        hw_memcpy(skb->data + 42, data->data, len - 42);

        cksum = net_pseudo_checksum(0x11, skb->data + 34, len - 34,
                                    (uint32 *)(skb->data + 26), (uint32 *)(skb->data + 30));
        put_unaligned_be16(cksum, skb->data + 40); //udp checksum
        skb_put(skb, len);
    } else {
        os_printf("%d: alloc skb fail\r\n", __LINE__);
    }
    return skb;
}