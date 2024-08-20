#ifndef _HGSDK_NETUTILS_H_
#define _HGSDK_NETUTILS_H_
#ifdef __cplusplus
extern "C" {
#endif

struct udpdata_info {
    uint8 *dest, *src;
    uint32 dest_ip, dest_port;
    uint32 src_ip, src_port;
    uint8 *data;
    uint32 len;
};

uint16 net_checksum(uint16 initcksum, uint8 *data, int32 len);
uint16 net_pseudo_checksum(uint8 proto, uint8 *data, uint16 len, uint32 *srcaddr, uint32 *destaddr);
struct sk_buff *net_setup_udpdata(struct udpdata_info *data);

#ifdef __cplusplus
}
#endif
#endif
