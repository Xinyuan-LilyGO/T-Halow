#ifndef _HUGEIC_DHCPD_H_
#define _HUGEIC_DHCPD_H_

struct dhcpd_param {
    uint32 lease_time; /*unit: seconds*/
    uint32 start_ip, end_ip; /*network byteorder*/
    uint32 netmask; /*network byteorder*/
    uint32 router;  /*network byteorder*/
    uint32 dns1;    /*network byteorder*/
    uint32 dns2;    /*network byteorder*/
};

int32 dhcpd_start(char *ifname, struct dhcpd_param *param);
void dhcpd_stop(char *ifname);

#endif
