#ifndef _HGSDK_OTA_H_
#define _HGSDK_OTA_H_
#ifdef __cplusplus
extern "C" {
#endif

#define ETH_P_OTA (0x4847)

enum ETH_P_OTA_STYPE{
    ETH_P_OTA_REBOOT=1,
    ETH_P_OTA_SCAN,
    ETH_P_OTA_SCAN_REPORT,
    ETH_P_OTA_FW_DATA,
    ETH_P_OTA_FW_DATA_RESP,
    ETH_P_OTA_FW_GET_PARAM,
    ETH_P_OTA_FW_GET_PARAM_RESP,
    ETH_P_OTA_FW_SET_PARAM,
    ETH_P_OTA_FW_SET_PARAM_RESP,
};

enum HGIC_OTA_RESP_ERR_CODE{
    HGIC_OTA_RESP_ERR_OK=0,
    HGIC_OTA_RESP_ERR_CHECKSUM,
    HGIC_OTA_RESP_ERR_WRITE,
};

struct eth_ota_hdr{
    uint8  dest[6];
    uint8  src[6];
    uint16 proto;
    uint8  stype, status;
};

struct eth_ota_scan_report{
    struct eth_ota_hdr hdr;
    uint32 version;
    uint16 chipid;
    uint8  mode, rev;
    uint32 svn_version;
    uint32 app_version;
};

struct eth_ota_fw_data{
    struct eth_ota_hdr hdr;
    uint32 version;
    uint32 off, tot_len;
    uint16 len, checksum;
    uint16 chipid;
    uint8  data[0];
};

struct eth_ota_fwparam{
    uint8  bss_bw;
    uint8  encrypt: 1,
           forward: 1,
           key_set: 1,
           mkey_set: 1;
    uint8  chan_cnt, resv;
    uint16 freq_start, freq_end;
    uint16 chan_list[16];
    uint8  ssid[32+2];
    uint8  key[32];
    uint8  mcast_key[32];
    uint8  tx_mcs;
};

struct eth_ota_fwparam_hdr{
    struct eth_ota_hdr hdr;
    uint16 len, checksum;
    struct eth_ota_fwparam param;
};

enum ETH_P_REBOOT_FLAGS{
    ETH_P_REBOOT_FLAGS_LOADDEF = BIT(0),
};

struct eth_ota_reboot{
    struct eth_ota_hdr hdr;
    uint32 flags;
};

struct hgic_ota_hdr{
    uint32 version;
    uint32 off;
    uint32 tot_len;
    uint16 len;
    uint16 checksum;
    uint16 chipid;
    uint16  err_code;
    uint8  data[0];
};


struct sk_buff *libota_proc(uint8 mode, struct sk_buff *skb);
uint16 libota_check_sum(uint8 *addr, int32 count);
void wnb_save_eth_fwparam(struct eth_ota_fwparam *param);
void wnb_fill_eth_fwparam(struct eth_ota_fwparam *param);

#ifdef __cplusplus
}
#endif
#endif
