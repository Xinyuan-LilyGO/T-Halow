#ifndef _HGIC_UMAC_CONFIG_H_
#define _HGIC_UMAC_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define UMAC_CHAN_MAX (32)
struct umac_config_wpas {
    unsigned char  ssid[32];
    unsigned char  bssid[6];
    unsigned short frequency;
    unsigned char  key_mgmt, bgrssi, tx_power, bssid_set, psk_set;
    unsigned char  psk[32];
};

struct umac_config_apd {
    unsigned char  ssid[32];
    unsigned short beacon_interval, ap_max_inactivity;
    unsigned char  key_mgmt, channel, bgrssi, tx_power, acs, acs_tm;
    unsigned char  psk[32];
};

struct umac_config {
    unsigned int   crc;
    unsigned short freq_start, freq_end;
    unsigned short chan_list[UMAC_CHAN_MAX];
    unsigned char  bss_bw, tx_mcs, primary_chan, chan_cnt;
    unsigned char  mac_addr[6];
    unsigned short rts_threshold, tx_power;
    struct umac_config_apd  apd;
    struct umac_config_wpas wpas;
};

struct umac_config *umac_configs(void);

#ifdef __cplusplus
}
#endif

#endif

