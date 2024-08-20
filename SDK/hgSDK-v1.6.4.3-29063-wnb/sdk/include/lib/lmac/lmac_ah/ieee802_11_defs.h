/*
 * IEEE 802.11 Frame type definitions
 * Copyright (c) 2002-2015, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2007-2008 Intel Corporation
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef IEEE802_11_DEFS_H
#define IEEE802_11_DEFS_H

#if 1
#include "typesdef.h"

#define ETH_ALEN    6       /* Octets in one ethernet addr   */
#define le_to_host16(v) (v)
#define cpu_to_le16(v)  (v)

#ifndef STRUCT_PACKED
#define STRUCT_PACKED __attribute__ ((__packed__))
#endif

typedef unsigned short        le16;       // used by ieee802_11_defs.h
typedef unsigned int        le32;       // used by ieee802_11_defs.h

typedef uint64_t   u64;
typedef uint32_t   u32;
typedef uint16_t   u16;
typedef uint8_t    u8;

typedef int64_t   s64;
typedef int32_t   s32;
typedef int16_t   s16;
typedef int8_t    s8;

#endif

/* IEEE 802.11 defines */

#define WLAN_FC_PVER		0x0003
#define WLAN_FC_FTYPE		0x000c
#define WLAN_FC_STYPE		0x00f0
#define WLAN_FC_TODS		0x0100
#define WLAN_FC_FROMDS		0x0200
#define WLAN_FC_MOREFRAG	0x0400
#define WLAN_FC_RETRY		0x0800
#define WLAN_FC_PWRMGT		0x1000
#define WLAN_FC_MOREDATA	0x2000
#define WLAN_FC_ISWEP		0x4000
#define WLAN_FC_ORDER		0x8000

#define IEEE80211_FCTL_VERS_0		0x0000
#define IEEE80211_FCTL_VERS_1		0x0001
#define WLAN_PV1_FC_PVER			0x0003
#define WLAN_PV1_FC_FROMDS			0x0100
#define WLAN_PV1_FC_MOREFRAG		0x0200
#define WLAN_PV1_FC_PWRMGT			0x0400
#define WLAN_PV1_FC_MOREDATA		0x0800
#define WLAN_PV1_FC_PROTECTED_FRAME	0x1000
#define WLAN_PV1_FC_END_SERV_PERIOD 0x2000
#define WLAN_PV1_FC_RELAYED_FRAME	0x4000
#define WLAN_PV1_FC_ACK_POLICY		0x8000

#define WLAN_FTYPE_MGMT		0x0000
#define WLAN_FTYPE_CTL		0x0004
#define WLAN_FTYPE_DATA		0x0008
#define WLAN_FTYPE_EXT		0x000c

#define WLAN_STYPE_DATA			0x0000
#define WLAN_STYPE_NULLFUNC		0x0040
#define WLAN_STYPE_QOS_DATA		0x0080
#define WLAN_STYPE_QOS_NULL	    0x00C0

#define WLAN_PV1_FC_ISWEP		0x4000
#define WLAN_PV1_FC_ORDER		0x8000

#define WLAN_STYPE_PSPOLL		0x00A0

#define WLAN_STYPE_ACTION		0x00D0


#define WLAN_FC_GET_TYPE(fc)	(((fc) & 0x000c) >> 2)
#define WLAN_FC_GET_STYPE(fc)	(((fc) & 0x00f0) >> 4)
#define WLAN_PV1_FC_GET_TYPE(fc)	(((fc) & 0x001c) >> 2)
#define WLAN_PV1_FC_GET_STYPE(fc)	(((fc) & 0x00e0) >> 5)

#define WLAN_INVALID_MGMT_SEQ   0xFFFF

#define WLAN_GET_SEQ_FRAG(seq) ((seq) & (BIT(3) | BIT(2) | BIT(1) | BIT(0)))
#define WLAN_GET_SEQ_SEQ(seq) \
	(((seq) & (~(BIT(3) | BIT(2) | BIT(1) | BIT(0)))) >> 4)

#define WLAN_FC_TYPE_MGMT		0
#define WLAN_FC_TYPE_CTRL		1
#define WLAN_FC_TYPE_DATA		2
#define WLAN_FC_TYPE_EXT		3

/* PV1 FRAME TYPE */
#define WLAN_PV1_FC_TYPE_QOS_DATA_ONE 	0
#define WLAN_PV1_FC_TYPE_MGMT			1
#define WLAN_PV1_FC_TYPE_CTRL			2
#define WLAN_PV1_FC_TYPE_QOS_DATA_TWO	3

/* PV1 CTRL FC */
#define WLAN_PV1_CTRL_FC_PVER			0x0003
#define WLAN_PV1_CTRL_FC_BW_IND			0x0700
#define WLAN_PV1_CTRL_FC_DYN_IND		0x0800
#define WLAN_PV1_CTRL_FC_PWRMGT			0x1000
#define WLAN_PV1_CTRL_FC_MOREDATA		0x2000
#define WLAN_PV1_CTRL_FC_FLOW_CTRL		0x4000
#define WLAN_PV1_CTRL_FC_NEXT_TWT_INFO	0x8000

/* PV1 control subtype */
#define WLAN_PV1_CTRL_STYPE_STACK		0
#define WLAN_PV1_CTRL_STYPE_BAT			1

/* PV1 Management frame subtypes */
#define WLAN_PV1_FC_STYPE_ACTION				0
#define WLAN_PV1_FC_STYPE_ACTION_NO_ACK			1
#define WLAN_PV1_FC_STYPE_PROBE_RESP			2
#define WLAN_PV1_FC_STYPE_RESOURCE_ALLOCATION	3


/* management */
#define WLAN_FC_STYPE_ASSOC_REQ		0
#define WLAN_FC_STYPE_ASSOC_RESP	1
#define WLAN_FC_STYPE_REASSOC_REQ	2
#define WLAN_FC_STYPE_REASSOC_RESP	3
#define WLAN_FC_STYPE_PROBE_REQ		4
#define WLAN_FC_STYPE_PROBE_RESP	5
#define WLAN_FC_STYPE_BEACON		8
#define WLAN_FC_STYPE_ATIM			9
#define WLAN_FC_STYPE_DISASSOC		10
#define WLAN_FC_STYPE_AUTH			11
#define WLAN_FC_STYPE_DEAUTH		12
#define WLAN_FC_STYPE_ACTION		13

/* control */
#define WLAN_FC_STYPE_S1G_TACK		3
#define WLAN_FC_STYPE_PSPOLL		10
#define WLAN_FC_STYPE_RTS			11
#define WLAN_FC_STYPE_CTS			12
#define WLAN_FC_STYPE_ACK			13
#define WLAN_FC_STYPE_CFEND			14
#define WLAN_FC_STYPE_CFENDACK		15

/* data */
#define WLAN_FC_STYPE_DATA		0
#define WLAN_FC_STYPE_DATA_CFACK	1
#define WLAN_FC_STYPE_DATA_CFPOLL	2
#define WLAN_FC_STYPE_DATA_CFACKPOLL	3
#define WLAN_FC_STYPE_NULLFUNC		4
#define WLAN_FC_STYPE_CFACK		5
#define WLAN_FC_STYPE_CFPOLL		6
#define WLAN_FC_STYPE_CFACKPOLL		7
#define WLAN_FC_STYPE_QOS_DATA		8
#define WLAN_FC_STYPE_QOS_DATA_CFACK	9
#define WLAN_FC_STYPE_QOS_DATA_CFPOLL	10
#define WLAN_FC_STYPE_QOS_DATA_CFACKPOLL	11
#define WLAN_FC_STYPE_QOS_NULL		12
#define WLAN_FC_STYPE_QOS_CFPOLL	14
#define WLAN_FC_STYPE_QOS_CFACKPOLL	15

/*WLAN_FC_TYPE_EXT*/
#define WLAN_FC_STYPE_DMG_BEACON		0
#define WLAN_FC_STYPE_S1G_BEACON		1
#define WLAN_FC_STYPE_VS_QA 		0x0f 

/* Authentication algorithms */
#define WLAN_AUTH_OPEN			0
#define WLAN_AUTH_SHARED_KEY		1
#define WLAN_AUTH_FT			2
#define WLAN_AUTH_SAE			3
#define WLAN_AUTH_LEAP			128

#define WLAN_AUTH_CHALLENGE_LEN 128

#define WLAN_CAPABILITY_ESS BIT(0)
#define WLAN_CAPABILITY_IBSS BIT(1)
#define WLAN_CAPABILITY_CF_POLLABLE BIT(2)
#define WLAN_CAPABILITY_CF_POLL_REQUEST BIT(3)
#define WLAN_CAPABILITY_PRIVACY BIT(4)
#define WLAN_CAPABILITY_SHORT_PREAMBLE BIT(5)
#define WLAN_CAPABILITY_PBCC BIT(6)
/*for support S1G compatibility element*/
#define	WLAN_CAPABILITY_TSF_ROLLOVER	BIT(6)
#define WLAN_CAPABILITY_CHANNEL_AGILITY BIT(7)
#define WLAN_CAPABILITY_SPECTRUM_MGMT BIT(8)
#define WLAN_CAPABILITY_QOS BIT(9)
#define WLAN_CAPABILITY_SHORT_SLOT_TIME BIT(10)
#define WLAN_CAPABILITY_APSD BIT(11)
#define WLAN_CAPABILITY_RADIO_MEASUREMENT BIT(12)
#define WLAN_CAPABILITY_DSSS_OFDM BIT(13)
#define WLAN_CAPABILITY_DELAYED_BLOCK_ACK BIT(14)
#define WLAN_CAPABILITY_IMM_BLOCK_ACK BIT(15)

/* Status codes (IEEE 802.11-2007, 7.3.1.9, Table 7-23) */
#define WLAN_STATUS_SUCCESS 0
#define WLAN_STATUS_UNSPECIFIED_FAILURE 1
#define WLAN_STATUS_TDLS_WAKEUP_ALTERNATE 2
#define WLAN_STATUS_TDLS_WAKEUP_REJECT 3
#define WLAN_STATUS_SECURITY_DISABLED 5
#define WLAN_STATUS_UNACCEPTABLE_LIFETIME 6
#define WLAN_STATUS_NOT_IN_SAME_BSS 7
#define WLAN_STATUS_CAPS_UNSUPPORTED 10
#define WLAN_STATUS_REASSOC_NO_ASSOC 11
#define WLAN_STATUS_ASSOC_DENIED_UNSPEC 12
#define WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG 13
#define WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION 14
#define WLAN_STATUS_CHALLENGE_FAIL 15
#define WLAN_STATUS_AUTH_TIMEOUT 16
#define WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA 17
#define WLAN_STATUS_ASSOC_DENIED_RATES 18
/* IEEE 802.11b */
#define WLAN_STATUS_ASSOC_DENIED_NOSHORT 19
#define WLAN_STATUS_ASSOC_DENIED_NOPBCC 20
#define WLAN_STATUS_ASSOC_DENIED_NOAGILITY 21
/* IEEE 802.11h */
#define WLAN_STATUS_SPEC_MGMT_REQUIRED 22
#define WLAN_STATUS_PWR_CAPABILITY_NOT_VALID 23
#define WLAN_STATUS_SUPPORTED_CHANNEL_NOT_VALID 24
/* IEEE 802.11g */
#define WLAN_STATUS_ASSOC_DENIED_NO_SHORT_SLOT_TIME 25
#define WLAN_STATUS_ASSOC_DENIED_NO_DSSS_OFDM 26
#define WLAN_STATUS_ASSOC_DENIED_NO_HT 27
#define WLAN_STATUS_R0KH_UNREACHABLE 28
#define WLAN_STATUS_ASSOC_DENIED_NO_PCO 29
/* IEEE 802.11w */
#define WLAN_STATUS_ASSOC_REJECTED_TEMPORARILY 30
#define WLAN_STATUS_ROBUST_MGMT_FRAME_POLICY_VIOLATION 31
#define WLAN_STATUS_UNSPECIFIED_QOS_FAILURE 32
#define WLAN_STATUS_REQUEST_DECLINED 37
#define WLAN_STATUS_INVALID_PARAMETERS 38
/* IEEE 802.11i */
#define WLAN_STATUS_INVALID_IE 40
#define WLAN_STATUS_GROUP_CIPHER_NOT_VALID 41
#define WLAN_STATUS_PAIRWISE_CIPHER_NOT_VALID 42
#define WLAN_STATUS_AKMP_NOT_VALID 43
#define WLAN_STATUS_UNSUPPORTED_RSN_IE_VERSION 44
#define WLAN_STATUS_INVALID_RSN_IE_CAPAB 45
#define WLAN_STATUS_CIPHER_REJECTED_PER_POLICY 46
#define WLAN_STATUS_TS_NOT_CREATED 47
#define WLAN_STATUS_DIRECT_LINK_NOT_ALLOWED 48
#define WLAN_STATUS_DEST_STA_NOT_PRESENT 49
#define WLAN_STATUS_DEST_STA_NOT_QOS_STA 50
#define WLAN_STATUS_ASSOC_DENIED_LISTEN_INT_TOO_LARGE 51
/* IEEE 802.11r */
#define WLAN_STATUS_INVALID_FT_ACTION_FRAME_COUNT 52
#define WLAN_STATUS_INVALID_PMKID 53
#define WLAN_STATUS_INVALID_MDIE 54
#define WLAN_STATUS_INVALID_FTIE 55
#define WLAN_STATUS_GAS_ADV_PROTO_NOT_SUPPORTED 59
#define WLAN_STATUS_NO_OUTSTANDING_GAS_REQ 60
#define WLAN_STATUS_GAS_RESP_NOT_RECEIVED 61
#define WLAN_STATUS_STA_TIMED_OUT_WAITING_FOR_GAS_RESP 62
#define WLAN_STATUS_GAS_RESP_LARGER_THAN_LIMIT 63
#define WLAN_STATUS_REQ_REFUSED_HOME 64
#define WLAN_STATUS_ADV_SRV_UNREACHABLE 65
#define WLAN_STATUS_REQ_REFUSED_SSPN 67
#define WLAN_STATUS_REQ_REFUSED_UNAUTH_ACCESS 68
#define WLAN_STATUS_INVALID_RSNIE 72
#define WLAN_STATUS_ANTI_CLOGGING_TOKEN_REQ 76
#define WLAN_STATUS_FINITE_CYCLIC_GROUP_NOT_SUPPORTED 77
#define WLAN_STATUS_TRANSMISSION_FAILURE 79
#define WLAN_STATUS_REJECTED_WITH_SUGGESTED_BSS_TRANSITION 82
#define WLAN_STATUS_PENDING_ADMITTING_FST_SESSION 86
#define WLAN_STATUS_QUERY_RESP_OUTSTANDING 95
#define WLAN_STATUS_DENIED_WITH_SUGGESTED_BAND_AND_CHANNEL 99
#define WLAN_STATUS_ASSOC_DENIED_NO_VHT 104
/*NEED TO CHECK S1G ERROR CODE*/
#define WLAN_STATUS_ASSOC_DENIED_NO_S1G 105

/* Reason codes (IEEE 802.11-2007, 7.3.1.7, Table 7-22) */
#define WLAN_REASON_UNSPECIFIED 1
#define WLAN_REASON_PREV_AUTH_NOT_VALID 2
#define WLAN_REASON_DEAUTH_LEAVING 3
#define WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY 4
#define WLAN_REASON_DISASSOC_AP_BUSY 5
#define WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA 6
#define WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA 7
#define WLAN_REASON_DISASSOC_STA_HAS_LEFT 8
#define WLAN_REASON_STA_REQ_ASSOC_WITHOUT_AUTH 9
/* IEEE 802.11h */
#define WLAN_REASON_PWR_CAPABILITY_NOT_VALID 10
#define WLAN_REASON_SUPPORTED_CHANNEL_NOT_VALID 11
/* IEEE 802.11i */
#define WLAN_REASON_INVALID_IE 13
#define WLAN_REASON_MICHAEL_MIC_FAILURE 14
#define WLAN_REASON_4WAY_HANDSHAKE_TIMEOUT 15
#define WLAN_REASON_GROUP_KEY_UPDATE_TIMEOUT 16
#define WLAN_REASON_IE_IN_4WAY_DIFFERS 17
#define WLAN_REASON_GROUP_CIPHER_NOT_VALID 18
#define WLAN_REASON_PAIRWISE_CIPHER_NOT_VALID 19
#define WLAN_REASON_AKMP_NOT_VALID 20
#define WLAN_REASON_UNSUPPORTED_RSN_IE_VERSION 21
#define WLAN_REASON_INVALID_RSN_IE_CAPAB 22
#define WLAN_REASON_IEEE_802_1X_AUTH_FAILED 23
#define WLAN_REASON_CIPHER_SUITE_REJECTED 24
#define WLAN_REASON_TDLS_TEARDOWN_UNREACHABLE 25
#define WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED 26
/* IEEE 802.11e */
#define WLAN_REASON_DISASSOC_LOW_ACK 34
/* IEEE 802.11s */
#define WLAN_REASON_MESH_PEERING_CANCELLED 52
#define WLAN_REASON_MESH_MAX_PEERS 53
#define WLAN_REASON_MESH_CONFIG_POLICY_VIOLATION 54
#define WLAN_REASON_MESH_CLOSE_RCVD 55
#define WLAN_REASON_MESH_MAX_RETRIES 56
#define WLAN_REASON_MESH_CONFIRM_TIMEOUT 57
#define WLAN_REASON_MESH_INVALID_GTK 58
#define WLAN_REASON_MESH_INCONSISTENT_PARAMS 59
#define WLAN_REASON_MESH_INVALID_SECURITY_CAP 60


/* Information Element IDs */
#define WLAN_EID_SSID                   0
#define WLAN_EID_SUPP_RATES             1
#define WLAN_EID_FH_PARAMS              2
#define WLAN_EID_DS_PARAMS              3
#define WLAN_EID_CF_PARAMS              4
#define WLAN_EID_TIM                    5
#define WLAN_EID_IBSS_PARAMS            6
#define WLAN_EID_COUNTRY                7
#define WLAN_EID_BSS_LOAD               11
#define WLAN_EID_EDCA_PARAMETER_SET     12
#define WLAN_EID_CHALLENGE              16
/* EIDs defined by IEEE 802.11h - START */
#define WLAN_EID_PWR_CONSTRAINT 32
#define WLAN_EID_PWR_CAPABILITY 33
#define WLAN_EID_TPC_REQUEST 34
#define WLAN_EID_TPC_REPORT 35
#define WLAN_EID_SUPPORTED_CHANNELS 36
#define WLAN_EID_CHANNEL_SWITCH 37
#define WLAN_EID_MEASURE_REQUEST 38
#define WLAN_EID_MEASURE_REPORT 39
#define WLAN_EID_QUITE 40
#define WLAN_EID_IBSS_DFS 41
/* EIDs defined by IEEE 802.11h - END */
#define WLAN_EID_ERP_INFO 42
#define WLAN_EID_HT_CAP 45
#define WLAN_EID_QOS 46
#define WLAN_EID_RSN 48
#define WLAN_EID_EXT_SUPP_RATES 50
#define WLAN_EID_NEIGHBOR_REPORT 52
#define WLAN_EID_MOBILITY_DOMAIN 54
#define WLAN_EID_FAST_BSS_TRANSITION 55
#define WLAN_EID_TIMEOUT_INTERVAL 56
#define WLAN_EID_RIC_DATA 57
#define WLAN_EID_SUPPORTED_OPERATING_CLASSES 59
#define WLAN_EID_EXT_CHANSWITCH_ANN 60
#define WLAN_EID_HT_OPERATION 61
#define WLAN_EID_SECONDARY_CHANNEL_OFFSET 62
#define WLAN_EID_WAPI 68
#define WLAN_EID_TIME_ADVERTISEMENT 69
#define WLAN_EID_RRM_ENABLED_CAPABILITIES 70
#define WLAN_EID_20_40_BSS_COEXISTENCE 72
#define WLAN_EID_20_40_BSS_INTOLERANT 73
#define WLAN_EID_OVERLAPPING_BSS_SCAN_PARAMS 74
#define WLAN_EID_MMIE 76
#define WLAN_EID_SSID_LIST 84
#define WLAN_EID_BSS_MAX_IDLE_PERIOD 90
#define WLAN_EID_TFS_REQ 91
#define WLAN_EID_TFS_RESP 92
#define WLAN_EID_WNMSLEEP 93
#define WLAN_EID_TIME_ZONE 98
#define WLAN_EID_LINK_ID 101
#define WLAN_EID_INTERWORKING 107
#define WLAN_EID_ADV_PROTO 108
#define WLAN_EID_QOS_MAP_SET 110
#define WLAN_EID_ROAMING_CONSORTIUM 111
#define WLAN_EID_MESH_CONFIG 113
#define WLAN_EID_MESH_ID 114
#define WLAN_EID_PEER_MGMT 117
#define WLAN_EID_EXT_CAPAB 127
#define WLAN_EID_AMPE 139
#define WLAN_EID_MIC 140
#define WLAN_EID_CCKM 156
#define WLAN_EID_MULTI_BAND 158
#define WLAN_EID_SESSION_TRANSITION 164
#define WLAN_EID_VHT_CAP 191
#define WLAN_EID_VHT_OPERATION 192
#define WLAN_EID_VHT_EXTENDED_BSS_LOAD 193
#define WLAN_EID_VHT_WIDE_BW_CHSWITCH  194
#define WLAN_EID_VHT_TRANSMIT_POWER_ENVELOPE 195
#define WLAN_EID_VHT_CHANNEL_SWITCH_WRAPPER 196
#define WLAN_EID_VHT_AID 197
#define WLAN_EID_VHT_QUIET_CHANNEL 198
#define WLAN_EID_VHT_OPERATING_MODE_NOTIFICATION 199
#define WLAN_EID_VENDOR_SPECIFIC 221

/*s1g related IEs*/
#define WLAN_EID_S1G_OPEN_LOOP                      	(207)
#define WLAN_EID_S1G_RPS                                (208)
#define WLAN_EID_S1G_PAGE_SLICE                         (209)
#define WLAN_EID_S1G_AID_REQUEST                        (210)
#define WLAN_EID_S1G_AID_RESPONSE                       (211)
#define WLAN_EID_S1G_SECTOR_OPERATION               	(212)
#define WLAN_EID_S1G_BEACON_COMPATIBILITY           	(213)
#define WLAN_EID_S1G_SHORT_BEACON_INTERVAL              (214)
#define WLAN_EID_S1G_CHANGE_SEQUENCE                    (215)
#define WLAN_EID_S1G_TWT                                (216)
#define WLAN_EID_S1G_CAPABILITIES                   	(217)
// 218 to 219 are reserved in P802.11ah_D4.0
#define WLAN_EID_S1G_SUBCHANNEL_SELECTIVE_TRANSMISSION  (220)
//#define WLAN_EID_S1G_VENDOR_SPECIFIC                  (221)
#define WLAN_EID_S1G_AUTHENTICATION_CONTROL             (222)
#define WLAN_EID_S1G_TSF_TIMER_ACCURACY                 (223)
#define WLAN_EID_S1G_RELAY                              (224)
#define WLAN_EID_S1G_RECHABLE_ADDRESS                   (225)
#define WLAN_EID_S1G_RELAY_DISCOVERY                    (226)
// 227 is reserved in P802.11ah_D4.0
#define WLAN_EID_S1G_AID_ANNOUNCEMENT                   (228)
#define WLAN_EID_S1G_SHORT_PROBE_RESPONSE_OPTION        (229)
#define WLAN_EID_S1G_ACTIVITY_SPECIFICATION             (230)
#define WLAN_EID_S1G_SECTORIZED_GROUP_ID_LIST           (231)
#define WLAN_EID_S1G_OPERATION                      	(232)
#define WLAN_EID_S1G_HEADER_COMPRESSION                 (233)
#define WLAN_EID_S1G_SST_OPERATION                      (234)
#define WLAN_EID_S1G_MAD                                (235)
#define WLAN_EID_S1G_RELAY_ACTIVATION                   (236)

#define S1G_RX_NSS_MAX_STREAMS			   				 4

/* Action frame categories (IEEE 802.11-2007, 7.3.1.11, Table 7-24) */
#define WLAN_ACTION_SPECTRUM_MGMT 0
#define WLAN_ACTION_QOS 1
#define WLAN_ACTION_DLS 2
#define WLAN_ACTION_BLOCK_ACK 3
#define WLAN_ACTION_PUBLIC 4
#define WLAN_ACTION_RADIO_MEASUREMENT 5
#define WLAN_ACTION_FT 6
#define WLAN_ACTION_HT 7
#define WLAN_ACTION_SA_QUERY 8
#define WLAN_ACTION_PROTECTED_DUAL 9
#define WLAN_ACTION_WNM 10
#define WLAN_ACTION_UNPROTECTED_WNM 11
#define WLAN_ACTION_TDLS 12
#define WLAN_ACTION_SELF_PROTECTED 15
#define WLAN_ACTION_WMM 17 /* WMM Specification 1.1 */
#define WLAN_ACTION_FST 18
#define	WLAN_CATEGORY_UNPROT_DMG 20
#define	WLAN_CATEGORY_VHT  21
#define	WLAN_CATEGORY_UNPROTECTED_S1G  22
#define WLAN_CATEGORY_S1G_UNPROTECTED  WLAN_CATEGORY_UNPROTECTED_S1G
#define	WLAN_CATEGORY_S1G_RELAY  23
#define	WLAN_CATEGORY_S1G_FLOW_CONTROL  24
#define	WLAN_CATEGORY_S1G_CONTROL_RESP_MCS_NGT 25
#define	WLAN_CATEGORY_VENDOR_SPECIFIC_PROTECTED  126
#define WLAN_ACTION_VENDOR_SPECIFIC 127

/* Public action codes */
#define WLAN_PA_20_40_BSS_COEX 0
#define WLAN_PA_VENDOR_SPECIFIC 9
#define WLAN_PA_GAS_INITIAL_REQ 10
#define WLAN_PA_GAS_INITIAL_RESP 11
#define WLAN_PA_GAS_COMEBACK_REQ 12
#define WLAN_PA_GAS_COMEBACK_RESP 13
#define WLAN_TDLS_DISCOVERY_RESPONSE 14

/* Protected Dual of Public Action frames */
#define WLAN_PROT_DSE_ENABLEMENT 1
#define WLAN_PROT_DSE_DEENABLEMENT 2
#define WLAN_PROT_EXT_CSA 4
#define WLAN_PROT_MEASUREMENT_REQ 5
#define WLAN_PROT_MEASUREMENT_REPORT 6
#define WLAN_PROT_DSE_POWER_CONSTRAINT 8
#define WLAN_PROT_VENDOR_SPECIFIC 9
#define WLAN_PROT_GAS_INITIAL_REQ 10
#define WLAN_PROT_GAS_INITIAL_RESP 11
#define WLAN_PROT_GAS_COMEBACK_REQ 12
#define WLAN_PROT_GAS_COMEBACK_RESP 13

/* unprotected s1g action codes */
enum ieee80211_unprotected_s1g_actioncode {
	WLAN_UNPROTECTED_S1G_ACTION_AID_SW_REQ = 0,
	WLAN_UNPROTECTED_S1G_ACTION_AID_SW_RESP,
	WLAN_UNPROTECTED_S1G_ACTION_SYNC_CTRL,
	WLAN_UNPROTECTED_S1G_ACTION_STA_INFO_ANN,
	WLAN_UNPROTECTED_S1G_ACTION_EDCA_PARM_SET,
	WLAN_UNPROTECTED_S1G_ACTION_EL_OPERATION,
	WLAN_UNPROTECTED_S1G_ACTION_TWT_SETUP,
	WLAN_UNPROTECTED_S1G_ACTION_TWT_TEARDOWN,
	WLAN_UNPROTECTED_S1G_ACTION_SECTORIZED_GRP_ID_LIST,
	WLAN_UNPROTECTED_S1G_ACTION_SECTOR_ID_FEEDBACK,
	WLAN_UNPROTECTED_S1G_ACTION_TWT_INFO = 11,
};

/*s1g relay action codes*/
enum ieee80211_s1g_relay_actioncode {
	WLAN_S1G_RELAY_ACTION_REACHABLE_ADDRESS_UPDATE = 0,
	WLAN_S1G_RELAY_ACTION_RELAY_ACTIVATION_REQ,
	WLAN_S1G_RELAY_ACTION_RELAY_ACTIVATION_RESP,
	WLAN_S1G_RELAY_ACTION_HEADER_COMPRESSION_UPDATE,
};

/*	WLAN_CATEGORY_S1G_FLOW_CONTROL action codes*/
enum ieee80211_s1g_flow_control_actioncode {
	WLAN_S1G_FLOW_CONTROL_ACTION_FLOW_SUSPENSION = 0,
	WLAN_S1G_FLOW_CONTROL_ACTION_Flow_RESUMPTION,
};

/*  WLAN_CATEGORY_S1G_CONTROL_RESP_MCS_NGT action codes*/
enum ieee80211_s1g_control_resp_mcs_ngt_actioncode {
	WLAN_S1G_CATEGORY_CONTROL_RESP_MCS_NGT_ACTION_REQ = 0,
	WLAN_S1G_CATEGORY_CONTROL_RESP_MCS_NGT_ACTION_RESP,
};

/* SA Query Action frame (IEEE 802.11w/D8.0, 7.4.9) */
#define WLAN_SA_QUERY_REQUEST 0
#define WLAN_SA_QUERY_RESPONSE 1

#define WLAN_SA_QUERY_TR_ID_LEN 2

/* TDLS action codes */
#define WLAN_TDLS_SETUP_REQUEST 0
#define WLAN_TDLS_SETUP_RESPONSE 1
#define WLAN_TDLS_SETUP_CONFIRM 2
#define WLAN_TDLS_TEARDOWN 3
#define WLAN_TDLS_PEER_TRAFFIC_INDICATION 4
#define WLAN_TDLS_CHANNEL_SWITCH_REQUEST 5
#define WLAN_TDLS_CHANNEL_SWITCH_RESPONSE 6
#define WLAN_TDLS_PEER_PSM_REQUEST 7
#define WLAN_TDLS_PEER_PSM_RESPONSE 8
#define WLAN_TDLS_PEER_TRAFFIC_RESPONSE 9
#define WLAN_TDLS_DISCOVERY_REQUEST 10

/* Radio Measurement Action codes */
#define WLAN_RRM_RADIO_MEASUREMENT_REQUEST 0
#define WLAN_RRM_RADIO_MEASUREMENT_REPORT 1
#define WLAN_RRM_LINK_MEASUREMENT_REQUEST 2
#define WLAN_RRM_LINK_MEASUREMENT_REPORT 3
#define WLAN_RRM_NEIGHBOR_REPORT_REQUEST 4
#define WLAN_RRM_NEIGHBOR_REPORT_RESPONSE 5

/* Radio Measurement capabilities (from RRM Capabilities IE) */
/* byte 1 (out of 5) */
#define WLAN_RRM_CAPS_LINK_MEASUREMENT BIT(0)
#define WLAN_RRM_CAPS_NEIGHBOR_REPORT BIT(1)
/* byte 2 (out of 5) */
#define WLAN_RRM_CAPS_LCI_MEASUREMENT BIT(4)
/* byte 5 (out of 5) */
#define WLAN_RRM_CAPS_FTM_RANGE_REPORT BIT(2)

/*
 * IEEE P802.11-REVmc/D5.0, 9.4.2.21.19 (Fine Timing Measurement Range
 * request) - Minimum AP count
 */
#define WLAN_RRM_RANGE_REQ_MAX_MIN_AP 15

/* Timeout Interval Type */
#define WLAN_TIMEOUT_REASSOC_DEADLINE 1
#define WLAN_TIMEOUT_KEY_LIFETIME 2
#define WLAN_TIMEOUT_ASSOC_COMEBACK 3

/* Interworking element (IEEE 802.11u) - Access Network Options */
#define INTERWORKING_ANO_ACCESS_NETWORK_MASK 0x0f
#define INTERWORKING_ANO_INTERNET 0x10
#define INTERWORKING_ANO_ASRA 0x20
#define INTERWORKING_ANO_ESR 0x40
#define INTERWORKING_ANO_UESA 0x80

#define INTERWORKING_ANT_PRIVATE 0
#define INTERWORKING_ANT_PRIVATE_WITH_GUEST 1
#define INTERWORKING_ANT_CHARGEABLE_PUBLIC 2
#define INTERWORKING_ANT_FREE_PUBLIC 3
#define INTERWORKING_ANT_PERSONAL_DEVICE 4
#define INTERWORKING_ANT_EMERGENCY_SERVICES 5
#define INTERWORKING_ANT_TEST 6
#define INTERWORKING_ANT_WILDCARD 15

/* Advertisement Protocol ID definitions (IEEE Std 802.11u-2011) */
enum adv_proto_id {
	ACCESS_NETWORK_QUERY_PROTOCOL = 0,
	MIH_INFO_SERVICE = 1,
	MIH_CMD_AND_EVENT_DISCOVERY = 2,
	EMERGENCY_ALERT_SYSTEM = 3,
	ADV_PROTO_VENDOR_SPECIFIC = 221
};

/* Access Network Query Protocol info ID definitions (IEEE Std 802.11u-2011) */
enum anqp_info_id {
	ANQP_QUERY_LIST = 256,
	ANQP_CAPABILITY_LIST = 257,
	ANQP_VENUE_NAME = 258,
	ANQP_EMERGENCY_CALL_NUMBER = 259,
	ANQP_NETWORK_AUTH_TYPE = 260,
	ANQP_ROAMING_CONSORTIUM = 261,
	ANQP_IP_ADDR_TYPE_AVAILABILITY = 262,
	ANQP_NAI_REALM = 263,
	ANQP_3GPP_CELLULAR_NETWORK = 264,
	ANQP_AP_GEOSPATIAL_LOCATION = 265,
	ANQP_AP_CIVIC_LOCATION = 266,
	ANQP_AP_LOCATION_PUBLIC_URI = 267,
	ANQP_DOMAIN_NAME = 268,
	ANQP_EMERGENCY_ALERT_URI = 269,
	ANQP_TDLS_CAPABILITY = 270,
	ANQP_EMERGENCY_NAI = 271,
	ANQP_NEIGHBOR_REPORT = 272,
	ANQP_VENUE_URL = 277,
	ANQP_ADVICE_OF_CHARGE = 278,
	ANQP_LOCAL_CONTENT = 279,
	ANQP_VENDOR_SPECIFIC = 56797
};

/* NAI Realm list - EAP Method subfield - Authentication Parameter ID */
enum nai_realm_eap_auth_param {
	NAI_REALM_EAP_AUTH_EXPANDED_EAP_METHOD = 1,
	NAI_REALM_EAP_AUTH_NON_EAP_INNER_AUTH = 2,
	NAI_REALM_EAP_AUTH_INNER_AUTH_EAP_METHOD = 3,
	NAI_REALM_EAP_AUTH_EXPANDED_INNER_EAP_METHOD = 4,
	NAI_REALM_EAP_AUTH_CRED_TYPE = 5,
	NAI_REALM_EAP_AUTH_TUNNELED_CRED_TYPE = 6,
	NAI_REALM_EAP_AUTH_VENDOR_SPECIFIC = 221
};

enum nai_realm_eap_auth_inner_non_eap {
	NAI_REALM_INNER_NON_EAP_PAP = 1,
	NAI_REALM_INNER_NON_EAP_CHAP = 2,
	NAI_REALM_INNER_NON_EAP_MSCHAP = 3,
	NAI_REALM_INNER_NON_EAP_MSCHAPV2 = 4
};

enum nai_realm_eap_cred_type {
	NAI_REALM_CRED_TYPE_SIM = 1,
	NAI_REALM_CRED_TYPE_USIM = 2,
	NAI_REALM_CRED_TYPE_NFC_SECURE_ELEMENT = 3,
	NAI_REALM_CRED_TYPE_HARDWARE_TOKEN = 4,
	NAI_REALM_CRED_TYPE_SOFTOKEN = 5,
	NAI_REALM_CRED_TYPE_CERTIFICATE = 6,
	NAI_REALM_CRED_TYPE_USERNAME_PASSWORD = 7,
	NAI_REALM_CRED_TYPE_NONE = 8,
	NAI_REALM_CRED_TYPE_ANONYMOUS = 9,
	NAI_REALM_CRED_TYPE_VENDOR_SPECIFIC = 10
};

/*
 * IEEE P802.11-REVmc/D5.0 Table 9-81 - Measurement type definitions for
 * measurement requests
 */
enum measure_type {
	MEASURE_TYPE_BASIC = 0,
	MEASURE_TYPE_CCA = 1,
	MEASURE_TYPE_RPI_HIST = 2,
	MEASURE_TYPE_CHANNEL_LOAD = 3,
	MEASURE_TYPE_NOISE_HIST = 4,
	MEASURE_TYPE_BEACON = 5,
	MEASURE_TYPE_FRAME = 6,
	MEASURE_TYPE_STA_STATISTICS = 7,
	MEASURE_TYPE_LCI = 8,
	MEASURE_TYPE_TRANSMIT_STREAM = 9,
	MEASURE_TYPE_MULTICAST_DIAG = 10,
	MEASURE_TYPE_LOCATION_CIVIC = 11,
	MEASURE_TYPE_LOCATION_ID = 12,
	MEASURE_TYPE_DIRECTIONAL_CHAN_QUALITY = 13,
	MEASURE_TYPE_DIRECTIONAL_MEASURE = 14,
	MEASURE_TYPE_DIRECTIONAL_STATS = 15,
	MEASURE_TYPE_FTM_RANGE = 16,
	MEASURE_TYPE_MEASURE_PAUSE = 255,
};

/* IEEE Std 802.11-2012 Table 8-71 - Location subject definition */
enum location_subject {
	LOCATION_SUBJECT_LOCAL = 0,
	LOCATION_SUBJECT_REMOTE = 1,
	LOCATION_SUBJECT_3RD_PARTY = 2,
};

/*
 * IEEE P802.11-REVmc/D5.0 Table 9-94 - Optional subelement IDs for LCI request
 */
enum lci_req_subelem {
	LCI_REQ_SUBELEM_AZIMUTH_REQ = 1,
	LCI_REQ_SUBELEM_ORIGINATOR_MAC_ADDR = 2,
	LCI_REQ_SUBELEM_TARGET_MAC_ADDR = 3,
	LCI_REQ_SUBELEM_MAX_AGE = 4,
};

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif /* _MSC_VER */

struct ieee80211_hdr {
	le16 frame_control;
	le16 duration_id;
	u8 addr1[6];
	u8 addr2[6];
	u8 addr3[6];
	le16 seq_ctrl;
	/* followed by 'u8 addr4[6];' if ToDS and FromDS is set in data frame
	 */
} STRUCT_PACKED;

#define IEEE80211_DA_FROMDS addr1
#define IEEE80211_BSSID_FROMDS addr2
#define IEEE80211_SA_FROMDS addr3

#define IEEE80211_HDRLEN (sizeof(struct ieee80211_hdr))

#define IEEE80211_FC(type, stype) host_to_le16((type << 2) | (stype << 4))
#define IEEE80211_PV1_FC(type, stype) host_to_le16((type << 2) | (stype << 4) | 0x1)

struct ieee80211_mgmt {
	le16 frame_control;
	le16 duration;
	u8 da[6];
	u8 sa[6];
	u8 bssid[6];
	le16 seq_ctrl;
	union {
		struct {
			le16 auth_alg;
			le16 auth_transaction;
			le16 status_code;
			/* possibly followed by Challenge text */
			u8 variable[];
		} STRUCT_PACKED auth;
		struct {
			le16 reason_code;
			u8 variable[];
		} STRUCT_PACKED deauth;
		struct {
			le16 capab_info;
			le16 listen_interval;
			/* followed by SSID and Supported rates */
			u8 variable[];
		} STRUCT_PACKED assoc_req;
		struct {
			le16 capab_info;
			le16 status_code;
			le16 aid;
			/* followed by Supported rates */
			u8 variable[];
		} STRUCT_PACKED assoc_resp, reassoc_resp;
		struct {
			le16 capab_info;
			le16 status_code;
			/* followed by Supported rates */
			u8 variable[];
		} STRUCT_PACKED s1g_assoc_resp, s1g_reassoc_resp;
		struct {
			le16 capab_info;
			le16 listen_interval;
			u8 current_ap[6];
			/* followed by SSID and Supported rates */
			u8 variable[];
		} STRUCT_PACKED reassoc_req;
		struct {
			le16 reason_code;
			u8 variable[];
		} STRUCT_PACKED disassoc;
		struct {
			u8 timestamp[8];
			le16 beacon_int;
			le16 capab_info;
			/* followed by some of SSID, Supported rates,
			 * FH Params, DS Params, CF Params, IBSS Params, TIM */
			u8 variable[];
		} STRUCT_PACKED beacon;
		/* probe_req: only variable items: SSID, Supported rates */
		struct {
			u8 timestamp[8];
			le16 beacon_int;
			le16 capab_info;
			/* followed by some of SSID, Supported rates,
			 * FH Params, DS Params, CF Params, IBSS Params */
			u8 variable[];
		} STRUCT_PACKED probe_resp;
		struct {
			u8 category;
			union {
			#if 0
				/*unprotected_s1g_action*/
				struct {
					u8 action_code;
					u8 variable[0];
				} STRUCT_PACKED unprotected_s1g_action;
				/*s1g_relay_action*/
				struct {
					u8 action_code;
					u8 variable[0];
				} STRUCT_PACKED s1g_relay_action;
				/*s1g_flow_control_action*/
				struct {
					u8 action_code;
					u8 variable[0];
				} STRUCT_PACKED s1g_flow_control_action;
				/*control_resp_mcs_ngt_action*/
				struct {
					u8 action_code;
					u8 variable[0];
				} STRUCT_PACKED control_resp_mcs_ngt_action;
			#endif
				struct {
					u8 action_code;
					u8 dialog_token;
					u8 status_code;
					u8 variable[];
				} STRUCT_PACKED wmm_action;
				struct{
					u8 action_code;
					u8 element_id;
					u8 length;
					u8 switch_mode;
					u8 new_chan;
					u8 switch_count;
				} STRUCT_PACKED chan_switch;
				struct {
					u8 action;
					u8 sta_addr[ETH_ALEN];
					u8 target_ap_addr[ETH_ALEN];
					u8 variable[]; /* FT Request */
				} STRUCT_PACKED ft_action_req;
				struct {
					u8 action;
					u8 sta_addr[ETH_ALEN];
					u8 target_ap_addr[ETH_ALEN];
					le16 status_code;
					u8 variable[]; /* FT Request */
				} STRUCT_PACKED ft_action_resp;
				struct {
					u8 action;
					u8 trans_id[WLAN_SA_QUERY_TR_ID_LEN];
				} STRUCT_PACKED sa_query_req;
				struct {
					u8 action; /* */
					u8 trans_id[WLAN_SA_QUERY_TR_ID_LEN];
				} STRUCT_PACKED sa_query_resp;
				struct {
					u8 action;
					u8 dialogtoken;
					u8 variable[];
				} STRUCT_PACKED wnm_sleep_req;
				struct {
					u8 action;
					u8 dialogtoken;
					le16 keydata_len;
					u8 variable[];
				} STRUCT_PACKED wnm_sleep_resp;
				struct {
					u8 action;
					u8 variable[];
				} STRUCT_PACKED public_action;
				struct {
					u8 action; /* 9 */
					u8 oui[3];
					/* Vendor-specific content */
					u8 variable[];
				} STRUCT_PACKED vs_public_action;
				struct {
					u8 action; /* 7 */
					u8 dialog_token;
					u8 req_mode;
					le16 disassoc_timer;
					u8 validity_interval;
					/* BSS Termination Duration (optional),
					 * Session Information URL (optional),
					 * BSS Transition Candidate List
					 * Entries */
					u8 variable[];
				} STRUCT_PACKED bss_tm_req;
				struct {
					u8 action; /* 8 */
					u8 dialog_token;
					u8 status_code;
					u8 bss_termination_delay;
					/* Target BSSID (optional),
					 * BSS Transition Candidate List
					 * Entries (optional) */
					u8 variable[];
				} STRUCT_PACKED bss_tm_resp;
				struct {
					u8 action; /* 6 */
					u8 dialog_token;
					u8 query_reason;
					/* BSS Transition Candidate List
					 * Entries (optional) */
					u8 variable[];
				} STRUCT_PACKED bss_tm_query;
				struct {
					u8 action; /* 15 */
					u8 variable[];
				} STRUCT_PACKED slf_prot_action;
				struct {
					u8 action;
					u8 variable[];
				} STRUCT_PACKED fst_action;
				struct {
					u8 action;
					u8 dialog_token;
					u8 variable[];
				} STRUCT_PACKED rrm;
			} u;
		} STRUCT_PACKED action;
	} u;
} STRUCT_PACKED;

struct ieee80211_pv1_ctrl {
	le16 frame_control;
	u8 da[2];
	union {
		struct {
			u8 sa[2];
			u8 timestamp[4];
			u8 fcs[4];
		}STRUCT_PACKED stack;
		struct {
			u8 sa[6];
			u8 beacon_seq;
			u8 timestamp[5];
			u8 next_twt_info[3];
			u8 starting_seq_control[2];
			u8 bat_bitmap[4];
			u8 fcs[4];
		}STRUCT_PACKED bat;
	}u;
};

/*Note: changed it from 11ah standard so that it is easier for coding
  ORIG:	EOM Indicator/GID Slot/ Start Offset / Reserved
  NOW:	EOM Indicator/GID Slot / Reserved / Start Offset
*/
typedef struct slot_assign_mu_mode0 {
	u8 		eom_indicator : 	1,
	   		gid_slot :			6,
	   		reserved :			1;
	le16 	start_offset;
}STRUCT_PACKED RA_SLOT_ASSIGN_MU_MODE0;

/*Note: changed it from 11ah standard so that it is easier for coding
  ORIG:	Partial AID/ Slot Start Offset / Reserved
  NOW:	Partial AID/ Reserved / Slot Start Offset
*/
typedef struct slot_assign_sta_mode0 {
	le16	partial_aid 	: 		9,
	   		reserved 		:		7;
	le16 	start_offset;
}STRUCT_PACKED RA_SLOT_ASSIGN_STA_MODE0;

typedef struct slot_assign_indication {
	u8 slot_assign_bitmap[0];
}RA_SLOT_ASSIGN_INDICATION_MODE1;


struct ieee80211_pv1_mgmt {
	le16 frame_control;
	union {
		/* probe_req: only variable items: SSID, Supported rates */
		struct {
			u8 da[6];
			u8 sa[6];
			u8 timestamp[4];
			u8 change_sequence;
			/* followed by Next TBTT, compressed SSID, Access Network Options
			 * and optional IEs
			 */
			u8 variable[];
		} STRUCT_PACKED probe_resp;
		struct {
			u8 da[2]; //A1 2 bytes
			u8 sa[6]; //bssid
			u8 raw_group[3];
			u8 raw_duration[2];
			/* followed by Slot Assignment 1..N
			 */
			u8 variable[];
		} STRUCT_PACKED resource_alloc;
		struct {
			union {
					struct {
						u8 da[ETH_ALEN];
						le16 sid;
					} STRUCT_PACKED fd0;
					struct {
						le16 sid;
						u8 sa[ETH_ALEN];
					} STRUCT_PACKED fd1;
			}STRUCT_PACKED addr;
			le16 seq_ctrl;
			u8 addr3[0]; //will force not to set it in the field of sid.
			u8 category;
			union {
				/*unprotected_s1g_action*/
				struct {
					u8 action_code;
					u8 variable[0];
				} STRUCT_PACKED unprotected_s1g_action;
				/*s1g_relay_action*/
				struct {
					u8 action_code;
					u8 variable[0];
				} STRUCT_PACKED s1g_relay_action;
				/*s1g_flow_control_action*/
				struct {
					u8 action_code;
					u8 variable[0];
				} STRUCT_PACKED s1g_flow_control_action;
				/*control_resp_mcs_ngt_action*/
				struct {
					u8 action_code;
					u8 variable[0];
				} STRUCT_PACKED control_resp_mcs_ngt_action;
			} STRUCT_PACKED u;
		} STRUCT_PACKED action;
	} u;
} STRUCT_PACKED;

struct ieee80211_s1g_ctrl_tack {
	le16 frame_control;
	le16 duration;
	u8 ra[6];
	u8 ta[6];
	u8 timestamp[5];
	/*Next TWT Info or Suspend Duration	(0 or 6)*/
	u8 variable[0];
}STRUCT_PACKED;

/**
 * ieee80211_is_mgmt - check if type is WLAN_FTYPE_MGMT
 * @fc: frame control bytes in little-endian byteorder
 */
static inline u8 ieee80211_is_mgmt(le16 fc)
{
	return (fc & cpu_to_le16(WLAN_FC_FTYPE | WLAN_FC_PVER)) ==
	       cpu_to_le16(WLAN_FTYPE_MGMT);
}

/**
 * ieee80211_is_ctl - check if type is WLAN_FTYPE_CTL
 * @fc: frame control bytes in little-endian byteorder
 */
static inline u8 ieee80211_is_ctl(le16 fc)
{
	return (fc & cpu_to_le16(WLAN_FC_FTYPE | WLAN_FC_PVER)) ==
	       cpu_to_le16(WLAN_FTYPE_CTL);
}

/**
 * ieee80211_is_action - check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_ACTION
 * @fc: frame control bytes in little-endian byteorder
 */
static inline int ieee80211_is_action(le16 fc)
{
    return (fc & cpu_to_le16(WLAN_FC_FTYPE | WLAN_FC_STYPE)) ==
           cpu_to_le16(WLAN_FTYPE_MGMT | WLAN_STYPE_ACTION);
}


#if 0
/**
 * ieee80211_is_data - check if type is WLAN_FTYPE_DATA
 * @fc: frame control bytes in little-endian byteorder
 */
static inline u8 ieee80211_is_data(le16 fc)
{
	return (fc & cpu_to_le16(WLAN_FC_FTYPE | WLAN_FC_PVER)) ==
	       cpu_to_le16(WLAN_FTYPE_DATA);
}
#else
uint8 ieee80211_is_data(uint16 frame_control);
#endif

static inline u8 ieee80211_is_s1g_beacon(le16 fc)
{
	fc = le_to_host16(fc);

	return (WLAN_FC_GET_TYPE(fc) ==  WLAN_FC_TYPE_EXT &&
	        WLAN_FC_GET_STYPE(fc) == WLAN_FC_STYPE_S1G_BEACON && 
		    (fc & WLAN_PV1_CTRL_FC_PVER) == 0);
}

static inline u8 ieee80211_is_s1g_tack(le16 fc)
{
	fc = le_to_host16(fc);

	return (WLAN_FC_GET_TYPE(fc) ==  WLAN_FC_TYPE_CTRL && 
		    WLAN_FC_GET_STYPE(fc) == WLAN_FC_STYPE_S1G_TACK && 
		    (fc & WLAN_PV1_CTRL_FC_PVER) != 0);
}

static inline u8 ieee80211_is_pv1(le16 fc)
{
	fc = le_to_host16(fc);

	return ((fc & WLAN_PV1_CTRL_FC_PVER) == 0x01);//fixed hu,181112
}
/*
 * PV1 Management frame subtypes
 */
static inline u8 ieee80211_is_pv1_mgmt(le16 fc)
{
	fc = le_to_host16(fc);

	return ((fc & WLAN_PV1_CTRL_FC_PVER) != 0 &&
		    (WLAN_PV1_FC_GET_TYPE(fc) ==  WLAN_PV1_FC_TYPE_MGMT));
}

static inline u8 ieee80211_is_pv1_probe_resp(le16 fc)
{
	fc = le_to_host16(fc);

	return ((fc & WLAN_PV1_CTRL_FC_PVER) != 0 &&
		    (WLAN_PV1_FC_GET_TYPE(fc) ==  WLAN_PV1_FC_TYPE_MGMT) &&
	        (WLAN_PV1_FC_GET_STYPE(fc) == WLAN_PV1_FC_STYPE_PROBE_RESP));
}

static inline u8 ieee80211_is_pv1_action(le16 fc)
{
	fc = le_to_host16(fc);

	return ((fc & WLAN_PV1_CTRL_FC_PVER) != 0 &&
		    (WLAN_PV1_FC_GET_TYPE(fc) ==  WLAN_PV1_FC_TYPE_MGMT) &&
	        (WLAN_PV1_FC_GET_STYPE(fc) == WLAN_PV1_FC_STYPE_ACTION));
}

static inline u8 ieee80211_is_pv1_action_no_ack(le16 fc)
{
	fc = le_to_host16(fc);

	return ((fc & WLAN_PV1_CTRL_FC_PVER) != 0 &&
		    (WLAN_PV1_FC_GET_TYPE(fc) ==  WLAN_PV1_FC_TYPE_MGMT) &&
	        (WLAN_PV1_FC_GET_STYPE(fc) == WLAN_PV1_FC_STYPE_ACTION_NO_ACK));
}

static inline u8 ieee80211_is_pv1_resr_alloc(le16 fc)
{
	fc = le_to_host16(fc);

	return ((fc & WLAN_PV1_CTRL_FC_PVER) != 0 &&
		    (WLAN_PV1_FC_GET_TYPE(fc) ==  WLAN_PV1_FC_TYPE_MGMT) &&
	        (WLAN_PV1_FC_GET_STYPE(fc) == WLAN_PV1_FC_STYPE_RESOURCE_ALLOCATION));
}

/* PV1 control subtype */
static inline u8 ieee80211_is_pv1_ctrl(le16 fc)
{
	fc = le_to_host16(fc);

	return ((fc & WLAN_PV1_CTRL_FC_PVER) != 0 &&
		    (WLAN_PV1_FC_GET_TYPE(fc) ==  WLAN_PV1_FC_TYPE_CTRL));
}

static inline u8 ieee80211_is_pv1_stack(le16 fc)
{
	fc = le_to_host16(fc);

	return ((fc & WLAN_PV1_CTRL_FC_PVER) != 0 &&
		    (WLAN_PV1_FC_GET_TYPE(fc) ==  WLAN_PV1_FC_TYPE_CTRL) &&
	        (WLAN_PV1_FC_GET_STYPE(fc) == WLAN_PV1_CTRL_STYPE_STACK));
}

static inline u8 ieee80211_is_pv1_bat(le16 fc)
{
	fc = le_to_host16(fc);

	return ((fc & WLAN_PV1_CTRL_FC_PVER) != 0 &&
		    (WLAN_PV1_FC_GET_TYPE(fc) ==  WLAN_PV1_FC_TYPE_CTRL) &&
	        (WLAN_PV1_FC_GET_STYPE(fc) == WLAN_PV1_CTRL_STYPE_BAT));
}

/*Either A1 or A2 is an SID*/
static inline u8 ieee80211_is_pv1_qos_data1(le16 fc)
{
	fc = le_to_host16(fc);

	return ((fc & WLAN_PV1_CTRL_FC_PVER) != 0 &&
		    (WLAN_PV1_FC_GET_TYPE(fc) ==  WLAN_PV1_FC_TYPE_QOS_DATA_ONE));
}

/*Both A1 and A2 fields contain MAC addresses*/
static inline u8 ieee80211_is_pv1_qos_data2(le16 fc)
{
	fc = le_to_host16(fc);

	return ((fc & WLAN_PV1_CTRL_FC_PVER) != 0 &&
		    (WLAN_PV1_FC_GET_TYPE(fc) ==  WLAN_PV1_FC_TYPE_QOS_DATA_TWO));
}

static inline u8 ieee80211_has_pm(uint16 fc)
{
	return (fc & (WLAN_FC_PWRMGT | WLAN_FC_PVER)) == cpu_to_le16(WLAN_FC_PWRMGT);
}

static inline u8 ieee80211_is_nullfunc(uint16 fc)
{
	return (fc & (WLAN_FC_FTYPE | WLAN_FC_STYPE | WLAN_FC_PVER)) ==
	             (WLAN_FTYPE_DATA | WLAN_STYPE_NULLFUNC);
}

static inline u8 ieee80211_is_qos_nullfunc(uint16 fc)
{
	return (fc & (WLAN_FC_FTYPE | WLAN_FC_STYPE | WLAN_FC_PVER)) ==
	             (WLAN_FTYPE_DATA | WLAN_STYPE_QOS_NULL);
}

static inline bool ieee80211_is_pspoll(uint16 fc)
{
	return (fc & (WLAN_FC_FTYPE | WLAN_FC_STYPE | WLAN_FC_PVER))==(WLAN_FTYPE_CTL | WLAN_STYPE_PSPOLL);
}

struct ieee80211_s1g_beacon {
	le16 frame_control;
	le16 duration;
	u8 sa[ETH_ALEN];
	u8 timestamp[4];
	u8 change_sequence;
	u8 variable[0];
} STRUCT_PACKED;

struct ieee80211_pspoll {
	le16 frame_control;
	le16 aid;
	u8 bssid[6];
	u8 ta[6];
} STRUCT_PACKED;

/* added for support S1G capability, data structures and IEs for 11ah*/
typedef union ieee80211_frame_control{
	struct {
		le16 		  	 protol_version	:		2,
						 type	: 				2,
						 subtype	: 			4,
						 tods	: 				1,
						 fromds	: 				1,
						 more_fragments	:		1,
						 retry	: 				1,
						 power_management	:	1,
						 more_data	: 			1,
						 protected_frame	: 	1,
						 order_htc	: 		    1;
	}frame_control_no_s1g;
	struct {
		le16 			 protol_version	:		2,
						 type	: 				2,
						 subtype	: 			4,
						 tods	: 				1,
						 fromds	: 				1,
						 more_fragments	:		1,
						 retry	: 				1,
						 power_management	:	1,
						 more_data	: 			1,
						 protected_frame	: 	1,
						 order_htc	: 		    1;
	}frame_control_s1g_data_mgm;
	struct {
		le16 			 protol_version	:	    	2,
						 type	: 					2,
						 subtype	: 				4,
						 bandwidth_indication	: 	3,
						 dynamic_indication	: 		1,
						 power_management	:		1,
						 more_data	: 				1,
						 protected_frame	: 		1,
						 order	:					1;
	}frame_control_s1g_control;
	struct {
		le16 			 protol_version	:	    	2,
						 type	: 					2,
						 subtype	: 				4,
						 bandwidth_indication	: 	3,
						 dynamic_indication	: 		1,
						 power_management	:		1,
						 more_data	: 				1,
						 flow_control	: 			1,
						 next_TWT_info_present	:	1;
	}frame_control_s1g_control_tack; //9.2.4.1.3 Type and Subtype subfields(tack frame should be PV0, not PV1 control frame)

	struct {
		le16 			 protol_version	:	    	2,
						 type	: 					3,
						 subtype	: 				3,
						 bandwidth_indication	: 	3,
						 dynamic_indication	: 		1,
						 power_management	:		1,
						 more_data	: 				1,
						 flow_control	: 			1,
						 next_TWT_info_present	:	1;
	}frame_control_pv1_control_frame; //9.8.4 PV1 Control frames (STACK and BAT frames)
	
	struct {
		le16 			 protol_version	:			2,
						 type	: 					2,
						 subtype	: 				4,
						 bandwidth_indication	: 	3,
						 dynamic_indication	: 		1,
						 power_management	:		1,
						 more_data	: 				1,
						 poll_type	: 				2;
	}frame_control_s1g_control_pspoll;
	struct {
		le16 			 protol_version	:			2,
						 type	: 					2,
						 subtype	: 				4,
						 next_TBTT_present	: 		1,
						 compressed_SSID_present : 	1,
						 ANO_present :	 		  	1,
						 BSS_BW	: 					3,
						 security	: 				1,
						 AP_PM	: 					1;
	}frame_control_s1g_ext_beacon;
	struct {
		le16 			 protol_version	:			2,
						 type	: 					3,
						 subtype	: 				3,
						 fromds	: 					1,
						 more_fragments	:			1,
						 power_management	:		1,
						 more_data	: 				1,
						 protected_frame	: 		1,
						 end_of_service_period	: 	1,
						 relayed_frame :			1,
						 ack_policy	:				1;
	}pv1_frame_control;
	struct {
		le16 			 protol_version	:				2,
						 type	: 						3,
						 subtype	: 					3,
						 next_TBTT_present	: 			1,
						 full_SSID_present : 			1,
						 ANO_present :	 		  		1,
						 BSS_BW	: 						3,
						 security	: 					1,
						 oneMHz_Pri_chan_location 	: 	1;
	}pv1_probe_resp_frame_control;
	struct {
		le16 		 	 protol_version	:				2,
						 type	: 						3,
						 subtype	: 					3,
						 slot_assign_mode	: 			1,
						 more_fragments		:			1,
						 power_management	:			1,
						 group_indicator	:			1,
						 protected_frame	: 			1,
						 end_of_service_period	: 		1,
						 relayed_frame :				1,
						 ack_policy	:					1;
	}pv1_ra_frame_control;
	le16 frame_control;
}IEEE80211_FRAME_CONTROL;


/**
 * refer to Table 9-257z—S1G Operation Information field which is different from VHT
 * enum ieee80211_s1g_chanwidth - S1G channel width
 * @IEEE80211_S1G_CHANWIDTH_1MHZ: 1 MHz bandwidth
 * @IEEE80211_S1G_CHANWIDTH_2MHZ: 2 MHz bandwidth
 * @IEEE80211_S1G_CHANWIDTH_4MHZ: 4 MHz bandwidth
 * @IEEE80211_S1G_CHANWIDTH_8MHZ: 8 MHz bandwidth
 * @IEEE80211_S1G_CHANWIDTH_8MHZ: 16 MHz bandwidth
 * @IEEE80211_S1G_LOCATION_1MHZ_PRI_CHAN:
 *  B5 bits indicates the location of 1 MHz primary channel within the 2 MHz primary channel
 *	— B5 is set to 0 to indicate that is located at the lower side of 2 MHz primary channel.
 *  — B5 is set to 1 to indicate that is located at the upper side of 2 MHz primary channel.
 * @IEEE80211_S1G_NOT_SUPPORT_MCS10: B7 is set to 1 to indicate that it is recommended that a STA does not use MCS10.
 */
typedef enum ieee80211_s1g_chanwidth {
	IEEE80211_S1G_CHANWIDTH_1MHZ			= BIT(0),
	IEEE80211_S1G_CHANWIDTH_2MHZ			= BIT(1),
	IEEE80211_S1G_CHANWIDTH_4MHZ			= BIT(2),
	IEEE80211_S1G_CHANWIDTH_8MHZ			= BIT(3),
	IEEE80211_S1G_CHANWIDTH_16MHZ			= BIT(4),
	IEEE80211_S1G_LOCATION_1MHZ_PRI_CHAN	= BIT(5),
	IEEE80211_S1G_NOT_SUPPORT_MCS10			= BIT(7),
}S1G_OPER_CHWIDTH;

#if 0
typedef enum {
	S1G_1M = 0,
	S1G_2M = 1,
	S1G_4M = 2,
	S1G_8M = 3,
	S1G_16M = 4,
	MAX_S1G_BW_NUM = 5,
}S1G_BANDWIDTH_INDICATION;
#endif

typedef enum {
	STATIC = 0,
	DYNAMIC = 1,
}S1G_DYNAMIC_INDICATION;

#define IEEE80211_MAX_MMPDU_SIZE 2304

/* Rx MCS bitmask is in the first 77 bits of supported_mcs_set */
#define IEEE80211_HT_MCS_MASK_LEN 10

/* HT Capabilities element */
struct ieee80211_ht_capabilities {
	le16 ht_capabilities_info;
	u8 a_mpdu_params; /* Maximum A-MPDU Length Exponent B0..B1
			   * Minimum MPDU Start Spacing B2..B4
			   * Reserved B5..B7 */
	u8 supported_mcs_set[16];
	le16 ht_extended_capabilities;
	le32 tx_bf_capability_info;
	u8 asel_capabilities;
} STRUCT_PACKED;


/* HT Operation element */
struct ieee80211_ht_operation {
	u8 primary_chan;
	/* Five octets of HT Operation Information */
	u8 ht_param; /* B0..B7 */
	le16 operation_mode; /* B8..B23 */
	le16 param; /* B24..B39 */
	u8 basic_mcs_set[16];
} STRUCT_PACKED;


struct ieee80211_obss_scan_parameters {
	le16 scan_passive_dwell;
	le16 scan_active_dwell;
	le16 width_trigger_scan_interval;
	le16 scan_passive_total_per_channel;
	le16 scan_active_total_per_channel;
	le16 channel_transition_delay_factor;
	le16 scan_activity_threshold;
} STRUCT_PACKED;


struct ieee80211_vht_capabilities {
	le32 vht_capabilities_info;
	struct {
		le16 rx_map;
		le16 rx_highest;
		le16 tx_map;
		le16 tx_highest;
	} vht_supported_mcs_set;
} STRUCT_PACKED;

struct ieee80211_vht_operation {
	u8 vht_op_info_chwidth;
	u8 vht_op_info_chan_center_freq_seg0_idx;
	u8 vht_op_info_chan_center_freq_seg1_idx;
	le16 vht_basic_mcs_set;
} STRUCT_PACKED;

/* S1G related 11ah Information Elements
 * 9.4.2.6 TIM element definition is different from non s1g tim element
 * 9.4.2.188 RPS element 
 * DSLOT = 500 + CSLOT × 120
 * DRAW = DSLOT × NRAW
 * DSLOT is the RAW slot duration, in microseconds
 * NRAW is the value of the Number of Slots subfield
 */
typedef struct raw_slot_def {
	union {
		struct u00 {
				le16 slot_def_format_ind 	: 	1,
			 		cross_slot_boundary 	:  	1,
		 	 		slot_duration_count 	: 	8,
			 		number_of_slots 	 	:  	6;
			}u0;	
		struct u11 {
			le16 slot_def_format_ind 	: 	1,
			 	cross_slot_boundary 	:  	1,
		 	 	slot_duration_count 	: 	11,
			 	number_of_slots 	 	:  	3;
			
		}u1;
		le16 slot_definition; 
	}u;
}STRUCT_PACKED RAW_SLOT_DEF; 

typedef struct raw_control {
	union {
		u8 	raw_type 				: 2,
			raw_type_options 		: 2,
			start_time_ind			: 1,
			raw_group_ind			: 1,
			channel_ind_presence 	: 1,
			Periodic_RAW_ind		: 1;
		u8 	control;
	}u;
}STRUCT_PACKED RAW_CONTROL;

struct raw_group {
	u8 	page_index 			: 2,
		raw_start_aid0_5 	: 6;
	u8 	raw_start_aid6_10 	: 5,
		raw_end_aid0_2 		: 3;
	u8 	raw_end_aid3_10;
}STRUCT_PACKED;

struct  raw_channel_indication {
	le16 channel_activity_bitmap 		: 	8,
	     maximum_transmission_width 	:  	2,
		 ul_activity 					: 	1,
	     dl_activity 	 				:  	1,
	     reserved                     	: 	4;
}STRUCT_PACKED;

struct periodic_operation_param {
	u8 praw_periodicity;
	u8 praw_validity;
	u8 praw_start_offset;
}STRUCT_PACKED;

struct raw_Channel_Indication {
	u16 channel_activity_bitmap 	: 	8,
		maximum_transmission_width	:	2,	
		ul_activity:					1,
		dl_activity:					1,
		reserved:						4;
}STRUCT_PACKED;

typedef enum raw_type {
	GENERIC_RAW = 0,
	SOUNDING_RAW,
	SIMPLEX_RAW,
	TRIGGERING_FRAME_RAW,
}RAW_TYPE;

typedef enum raw_type_options {
	SST_SOUNDING_RAW = 0,
	SST_REPORT_RAW = 1,
	SECTOR_SOUNDING_RAW = 2,
	SECTOR_REPORT_RAW = 3,
	AP_PM_RAW = 0,
	NON_TIM_RAW = 1, 
	OMNI_RAW = 2,
}RAW_TYPE_OPTIONS;

struct ieee80211_s1g_rps_ie {
	u8 	raw_type 				: 2,
		raw_type_options 		: 2,
		start_time_ind			: 1,
		raw_group_ind			: 1,
		channel_ind_presence 	: 1,
		Periodic_RAW_ind		: 1;
		RAW_SLOT_DEF slot_def;
	/*RAW Start Time, RAW Group, Channel Indication, Periodic Operation Parameters */
	u8 variable[0];
} STRUCT_PACKED;

/*9.4.2.189 Page Slice element*/
/*Element ID, Length, Page Period, Page Slice Control, Page Bitmap*/
struct ieee80211_s1g_page_slice_ie {
	u8 period;
	u8 slice_control[3];
	/*Page Bitmap 0 ~4*/
	u8 variable[0];
} STRUCT_PACKED;

/*9.4.2.190 AID Request element*/
/*Element ID, Length, AID Request Mode,  AID Request Interval (Optional),
 *Peer STA Address (Optional),Service Characteris tic (Optional), Group Address (Optional)
 */
struct ieee80211_s1g_aid_req_ie {
	u8 mode;
/*AID Request Interval (Optional), Peer STA Address (Optional),
 *Service Characteris tic (Optional), Group Address (Optional)
 */
	u8 variable[0];
} STRUCT_PACKED;

/*9.4.2.191 AID Response element*/
struct ieee80211_s1g_aid_resp_ie {
	le16 aid;
	u8 switch_count;
	le16 	unscaled_interval		: 14,
			unified_scaling_factor 	: 2;
} STRUCT_PACKED;

/*9.4.2.192 S1G Sector Operation element*/
struct ieee80211_s1g_sector_operation_ie {
	u8 sectorization_type : 	1,
	   period : 				6,
	   omni : 					1;
	/*
	u8 Sector_id (3bits);
	Number_of_Groups (4 bits == 15 grps);
	GrpID0, GrpID1....GrpID14 (each 6 bits) = 15*6= 90 bits
	Sector Duration (6bits)
	padding (1, 3, 5, or 7) ==> at max : 104 bits = 13 bytes*/
	u8 variable[0];
	/*
		u8  	type 				: 	1,
				variable_by_type 	:	7;
		*/
} STRUCT_PACKED;

/*9.4.2.193 S1G Beacon Compatibility element*/
struct ieee80211_s1g_compatibility_ie {
	le16 compatibility_info;
	le16 beacon_interval;
	le32 tsf_completion;
} STRUCT_PACKED;

/*Change Sequence element format*/
struct ieee80211_s1g_change_sequence_ie {
	u8 change_sequence;//initialized to 0 in beacon frame.
} STRUCT_PACKED;

typedef enum {
	REQUEST_TWT = 0,
	SUGGEST_TWT,
	DEMAND_TWT,
	TWT_GROUPING,
	ACCEPT_TWT,
	ALTERNATE_TWT,
	DICTATE_TWT,
	REJECT_TWT,
	MAX_TWT_SETUP_COMMAND,
}TWT_SETUP_COMMAND;

struct ieee80211_s1g_twt_ie {
	//u8 control;
	u8 ndp_paging_indicator : 1,
	   responder_pm_mode 	: 1,
	   reserved 			: 6;
	//le16 request_type;
	le16 request 			: 	1,
		 twt_setup_command 	:	3,
 		 reserved1 			:	1,
 		 implicit 			:	1,
 		 flow_type			:	1, // Flow Type  = 0, STA WILL SEND PS POLL BEFORE TWT response to request...
 		 twt_flow_identifier	:	3,
 		 twt_wake_interval_exponent	: 5,
 		 twt_protection		:	1;
	/*TWT(0 or 8), TWTGroup(9, or 3, or 0), normalMinTWTduration(1), TWT interval Mantissa(2), TWT channel(1), NDP paging(0 or 4)*/
	u8 variable[0];
} STRUCT_PACKED;

#define MAX_TWT_FLOW_IDENTIFIER		8
#define WLAN_SA_TWT_RESPONSE 		0
#define WLAN_SA_TWT_REQUEST 		1

struct ieee80211_s1g_twt_info {
		u8 	ndp_paging_indicator 	: 1,
	   		responder_pm_mode 		: 1,
	   		setup_flag 				: 1, //1: setup; 0: teardown
	   		pad0 					: 5;
	   	u8 	twt_channel;
	   	u8 	nominal_minimum_twt_wake_duration;
	   	u8 	twt_group_assignment[9];
		u16 request 					: 	1,
		 	twt_setup_command 			:	3,
 		 	pad1 						:	1,
 		 	implicit 					:	1,
 		 	flow_type					:	1, // flow type  = 0, sta will send ps poll before twt response to request...
 		 	twt_flow_identifier			:	3,
 		 	twt_wake_interval_exponent	: 	5,
 		 	twt_protection				:	1;
 		u16 twt_wake_interval_mantissa;
 		u32 ndp_paging;
 		u64 target_wake_time;
 		//struct ieee80211_s1g_twt_info *next;
}STRUCT_PACKED;

struct s1g_capabilities_info {
	u8 				s1g_long : 			1,
					s1g_short_GI_1M : 	1,
					s1g_short_GI_2M : 	1,
					s1g_short_GI_4M : 	1,
					s1g_short_GI_8M : 	1,
					s1g_short_GI_16M : 	1,
					Supported_BW :		2;
	u8				Rx_LDPC		 :		1,
					Tx_STBC		 :		1,
					Rx_STBC 	 :		1,
					su_bfmer_cap :		1,
					su_bfmee_cap :		1,
					bfmee_STS_cap :		3;
	u8 				num_sound_d :		3,
					mu_bfmer_cap : 		1,
					mu_bfmee_cap : 		1,
					htc_vht_cap : 		1,
					traveling_pilot :	2;
	u8 				rd_responder  :		1,
					ht_delayed_block_ack :		 	1,
					max_MPDU_len_set :  	 		1,
					max_AMPDU_len_exp : 	 		2,
					min_MPDU_Start_spacing : 		3;
	u8 				uplink_sync_cap	:		 		1,
					dynamic_AID		:		 		1,
					BAT_support 	:		 		1,
					TIM_ADE_support : 		 		1,
					non_TIM_support	:		 		1,
					group_AID_support :		 		1,
					STA_type 	:			 		2;
	u8 				centralized_auth :		 		1,
					distributed_auth :		 		1,
					AMSDU_supported	 : 		      	1,
					AMPDU_supported	 :      	 	1,
					Asym_block_ack	 :		 		1,
					flow_control 	 :		 		1,
					Sectorized_Beam_cap :    		2;
	u8 				OBSS_mitigation_support : 		1,
					fragment_BA_support	:	  		1,
					NDP_PS_poll_support :  	  		1,
					RAW_operation_support :   		1,
					page_slicing_support :    		1,
					TXOP_sharing_implicit_ack : 	1,
					VHT_link_Adaptation_cap : 		2;
	u8 				TACK_PS_poll_resp_support :		1,
					duplicate_1MHZ_support :		1,
					MCS_Negotiation_support :		1,
					One_MHz_ctrl_resp_preamble :	1,
					NDP_Bfming_report_poll :		1,
					Unsolicite_Dynamic_AID :		1,
					sector_training_operation : 	1,
					Temporary_ps_mode_switch :		1;
	u8 				TWT_grouping_support :			1,
					BDT_capble :					1,
					COLOR :							3,
					TWT_requester_support :			1,
					TWT_responder_support :			1,
					PV1_frame_support :				1;
	u8				link_adapt_per_norm_ctrl_resp_cap : 1,
					reserved 	:						7;
};

struct s1g_mcs_nss_set {
	le32			Rx_Max_S1G_MCS_1SS : 					 2,
					Rx_Max_S1G_MCS_2SS : 					 2,
					Rx_Max_S1G_MCS_3SS : 					 2,
					Rx_Max_S1G_MCS_4SS : 					 2,
					Rx_Highest_Supported_Long_GI_Data_Rate : 9,
					Tx_Max_S1G_MCS_1SS : 					 2,
					Tx_Max_S1G_MCS_2SS : 					 2,
					Tx_Max_S1G_MCS_3SS :    				 2,
					Tx_Max_S1G_MCS_4SS : 					 2,
					Tx_Highest_Supported_Long_GI_Data_Rate_0_6 : 	7;
	u8 				Tx_Highest_Supported_Long_GI_Data_Rate_7_8 : 	2,
				 	Rx_Single_SS_S1G_MCS_1MHZ : 				  	2,
				 	Tx_Single_SS_S1G_MCS_1MHZ : 				  	2,
				 	Reserved :									  	2;
} STRUCT_PACKED;

struct ieee80211_s1g_capabilities {
/*9.4.2.197.2 S1G Capabilities Information field
	 capabilities_info[10];*/
	union {
		struct s1g_capabilities_info capabilities_info;
		u8 s1g_cap_info[10];
	}s1g_capabilities_info;

	union {
		struct s1g_mcs_nss_set mcs_nss_set;
		u8 s1g_mcs_nss_set[5];
	}supported_s1g_mcs_nss_set;
} STRUCT_PACKED;

struct ieee80211_s1g_operation {

	u8 channel_width;
	u8 operating_class;
	u8 pri_channel_number;
	u8 channel_center_freq;

	union {
		struct {
			le16				Min_S1g_MCS_1SS : 2,
								Max_S1g_MCS_1SS : 2,
								Min_S1g_MCS_2SS : 2,
								Max_S1g_MCS_2SS : 2,
								Min_S1g_MCS_3SS : 2,
								Max_S1g_MCS_3SS : 2,
								Min_S1g_MCS_4SS : 2,
								Max_S1g_MCS_4SS : 2;
		} STRUCT_PACKED mcs_nss_set;
		le16 b_mcs_nss_set;
	}basic_s1g_mcs_nss_set;
} STRUCT_PACKED;


/*
*hushifei:option bitmap bitmap0 bitmap1~bitmap5
**/
typedef union pv1_probe_resp_option_bitmap{
	struct {
		u8 	full_SSID_present 					: 	1,
				next_TBTT_present				:	1,
				ANO_present 					:	1,
				s1g_beacon_compatibility 		:	1,
				support_rates 					:	1,
				s1g_capabilities_info       	:	1,
				s1g_operation_info       		:	1,
				rsn_support  					:	1;
	}bitmap0;
	struct {
		u8 		rps_present 					: 	1,
				page_slice_present				:	1,
				tsf_timer_accuracy 				:	1,
				s1g_relay_discovery 			:	1,
				s1g_sector_operation       		:	1,
				short_beacon_interval       	:	1,
				reserved  						:	2;
	}bitmap1;
	struct {
		u8 bitmap;
	}bitmap2;
	struct {
		u8 bitmap;
	}bitmap3;
	struct {
		u8 bitmap;
	}bitmap4;
	struct {
		u8 bitmap;
	}bitmap5;
	struct {
		u8 bitmap;
	}bitmap6;
	struct {
		u8 bitmap;
	}bitmap7;
	u8 bitmap;
}PV1_PROBE_RESP_BIT_MAP;

/*9.4.2.198 Subchannel Selective Transmission (SST) element*/
struct ieee80211_s1g_sst_ie {
	/* Channel Activity Schedule (Sounding Option = 0 or 1) */
	le32 channel_activity_schedule;
} STRUCT_PACKED;

/*9.4.2.199 Authentication Control element*/
struct ieee80211_s1g_auth_control_ie {
	/* centralized_auth_ctrl_param: 16 bits for Control subfield equal to 0; 24bits for Control subfield equal to 1 */
	le16 authentication_control_parameters;
	u8 minimum_transmission_interval[0];
} STRUCT_PACKED;

/* 9.4.2.200 TSF Timer Accuracy element*/
struct ieee80211_s1g_tsf_timer_accuracy_ie {
	u8 tsf_timer_accuracy;
} STRUCT_PACKED;

/*9.4.2.201 S1G Relay element*/
struct ieee80211_s1g_relay_ie {
	u8 relay_control;
	/*RootAP BSSID (0 or 6)*/
	u8 bssid[0];
} STRUCT_PACKED;

/*9.4.2.202 Reachable Address element*/
struct ieee80211_s1g_reachable_address_ie {
	u8 mac[6];
	u8 addr_count;
	/*Reachable Addresses*/
	u8 variable[0];
} STRUCT_PACKED;

/*9.4.2.203 S1G Relay Activation element*/
struct ieee80211_s1g_relay_activation_ie {
	u8 function;
	/*Number of STAs*/
	u8 variable[0];
} STRUCT_PACKED;

/*9.4.2.204 S1G Relay Discovery element*/
struct ieee80211_s1g_relay_discovery_ie {
	u8 control;
	/*UL/DL data rate; delay bound req or channel utilization; Min Phy Rate req or relay station count*/
	u8 variable[0];
} STRUCT_PACKED;

/*9.4.2.205 AID Announcement element*/
struct ieee80211_s1g_AID_announ_ie {
	/*8xn AID entry --STA MAC[6]+AID[2]*/
	u8 variable[0];
}	STRUCT_PACKED;

/*9.4.2.206 PV1 Probe Response Option element --- TBD*/
/*Probe Response Group Bitmap (optional)Probe Response Option Bitmaps*/
struct ieee80211_pv1_probe_resp_option_ie {
/*Probe Response Group Bitmap (optional)Probe Response Option Bitmaps*/
	union {
		struct {
			u8 group_bitmap;
			u8 variable[0];
		}g;
		u8 variable[0];
	}u;

} STRUCT_PACKED;

/*9.4.2.207 EL Operation element*/
struct ieee80211_s1g_el_operation_ie {
	le16 max_away_duration;
	le16 recovery_time_duration;
} STRUCT_PACKED;

/*9.4.2.208 Sectorized Group ID List element*/
struct ieee80211_s1g_sectorized_grp_id_list_ie {
	/*Sectorized Group ID Type(4bits)+ Sectorized Group IDs(variable) + Pad*/
	u8 variable[0];
} STRUCT_PACKED;

/*9.4.2.210 Header Compression element*/
struct ieee80211_s1g_header_compression_ie {
	u8 control;
	u8 variable[0];
} STRUCT_PACKED;

/*99.4.2.211 SST Operation element*/
struct ieee80211_s1g_sst_operation_ie {
	u8 sst_enabled_chan_bitmap;
	u8 pri_chan_offset 		: 	3,
	   sst_chan_unit 		: 	1,
	   reserved				:	4;
} STRUCT_PACKED;

/*9.4.2.212 MAD element*/
struct ieee80211_s1g_mad_ie {
	le16 max_away_duration;
} STRUCT_PACKED;

/*9.4.2.194 Short Beacon Interval element*/
struct ieee80211_s1g_short_beacon_interval_ie {
	le16 short_beacon_interval;
} STRUCT_PACKED;

/*9.4.2.29 EDCA Parameter Set element*/
struct ieee80211_edca_param_set_ie {
    struct {
        u8      edca_param_set_update_cnt   : 4,
                q_ack                       : 1,
                queue_request               : 1,
                txop_request                : 1,
                reserved                    : 1;
    } qos_info;
    u8 reserved;
    struct {
        u8      aifsn                       : 4,
                acm                         : 1,
                aci                         : 2,
                reserved                    : 1;
        u8      ecwmin                      : 4,
                ecwmax                      : 4;
        le16    txop_limit;
    } param_record[4];
} STRUCT_PACKED;

struct ieee80211_ampe_ie {
	u8 selected_pairwise_suite[4];
	u8 local_nonce[32];
	u8 peer_nonce[32];
	/* Followed by
	 * Key Replay Counter[8] (optional)
	 *	(only in Mesh Group Key Inform/Acknowledge frames)
	 * GTKdata[variable] (optional)
	 *	(MGTK[variable] || Key RSC[8] || GTKExpirationTime[4])
	 * IGTKdata[variable] (optional)
	 *	(Key ID[2], IPN[6], IGTK[variable] in IGTK KDE format)
	 */
} STRUCT_PACKED;

#ifdef _MSC_VER
#pragma pack(pop)
#endif /* _MSC_VER */

#define ERP_INFO_NON_ERP_PRESENT BIT(0)
#define ERP_INFO_USE_PROTECTION BIT(1)
#define ERP_INFO_BARKER_PREAMBLE_MODE BIT(2)

#define OVERLAPPING_BSS_TRANS_DELAY_FACTOR 5

/* S1G Capabilities Info field within S1G Capabilities element */
#define OUI_SUSHIMAC11AH							0x006688 /* SUSHI MAC FOR 11AH OUI */
#define VENDOR_S1G_TYPE								0x99
#define VENDOR_S1G_SUBTYPE						    0x88
/* s1g_capab[0] */
#define S1G_CAP_INFO_LONG 							((u8) BIT(0))
#define S1G_CAP_INFO_SHORT_GI_4M 					((u8) BIT(1))
#define S1G_CAP_INFO_SHORT_GI_2M 					((u8) BIT(2))
#define S1G_CAP_INFO_SHORT_GI_8M 					((u8) BIT(3))
#define S1G_CAP_INFO_SHORT_GI_1M 					((u8) BIT(4))
#define S1G_CAP_INFO_SHORT_GI_16M 					((u8) BIT(5))
#define S1G_CAP_INFO_SUPPORTED_BW 					((u8) BIT(6)| BIT(7))
#define S1G_CAP_INFO_SUPPORTED_BW_2M				((u8) BIT(6))
#define S1G_CAP_INFO_SUPPORTED_BW_1					((u8) BIT(7))
#define S1G_CAP_INFO_SUPPORTED_BW_2					((u8) BIT(6)| BIT(7))
#define S1G_CAP_INFO_SUPPORTED_BW 					((u8) BIT(6)| BIT(7))
/* s1g_capab[1] */
#define S1G_CAP_INFO_RX_LDPC		 				((u8) BIT(0))
#define S1G_CAP_INFO_TX_STBC		 				((u8) BIT(1))
#define S1G_CAP_INFO_RX_STBC 	 					((u8) BIT(2))
#define S1G_CAP_INFO_SU_BFMER_CAP 					((u8) BIT(3))
#define S1G_CAP_INFO_SU_BFMEE_CAP 					((u8) BIT(4))
#define S1G_CAP_INFO_BFMEE_STS_CAP 					((u8) BIT(5) | BIT(6) | BIT(7))
/* s1g_capab[2] */
#define S1G_CAP_INFO_NUM_SOUND_D 					((u8) BIT(0) | BIT(1) | BIT(2))
#define S1G_CAP_INFO_MU_BFMER_CAP 					((u8) BIT(3))
#define S1G_CAP_INFO_MU_BFMEE_CAP 					((u8) BIT(4))
#define S1G_CAP_INFO_HTC_VHT_CAPABLE				((u8) BIT(5))
#define S1G_CAP_INFO_TRAVELING_PILOT 				((u8) BIT(6) | BIT(7))
/* s1g_capab[3] */
#define S1G_CAP_INFO_RD_RESPONDER  					((u8) BIT(0))
#define S1G_CAP_INFO_HT_DELAYED_BLOCK_ACK 	 		((u8) BIT(1))
#define S1G_CAP_INFO_MAX_MPDU_LEN_SET  	 			((u8) BIT(2))
#define S1G_CAP_INFO_MAX_AMPDU_LEN_EXP 	 			((u8) BIT(3) | BIT(4))
#define S1G_CAP_INFO_MIN_MPDU_START_SPACING 		((u8) BIT(5) | BIT(6) | BIT(7))
/* s1g_capab[4] */
#define S1G_CAP_INFO_UPLINK_SYNC_CAP		 		((u8) BIT(0))
#define S1G_CAP_INFO_DYNAMIC_AID			 		((u8) BIT(1))
#define S1G_CAP_INFO_BAT_SUPPORT 		 			((u8) BIT(2))
#define S1G_CAP_INFO_TIM_ADE_SUPPORT 		 		((u8) BIT(3))
#define S1G_CAP_INFO_NON_TIM_SUPPORT		 		((u8) BIT(4))
#define S1G_CAP_INFO_GROUP_AID_SUPPORT 	 			((u8) BIT(5))
#define S1G_CAP_INFO_STA_TYPE 			 			((u8) BIT(6) | BIT(7))
/* s1g_capab[5] */
#define S1G_CAP_INFO_CENTRALIZED_AUTH 	 			((u8) BIT(0))
#define S1G_CAP_INFO_DISTRIBUTED_AUTH 	 			((u8) BIT(1))
#define S1G_CAP_INFO_AMSDU_SUPPORTED	 		    ((u8) BIT(2))
#define S1G_CAP_INFO_AMPDU_SUPPORTED	      	 	((u8) BIT(3))
#define S1G_CAP_INFO_ASYM_BLOCK_ACK	 	 			((u8) BIT(4))
#define S1G_CAP_INFO_FLOW_CONTROL 	 	 			((u8) BIT(5))
#define S1G_CAP_INFO_SECTORIZED_BEAM_CAP    		((u8) BIT(6) | BIT(7))
/* s1g_capab[6] */
#define S1G_CAP_INFO_OBSS_MITIGATION_SUPPORT  		((u8) BIT(0))
#define S1G_CAP_INFO_FRAGMENT_BA_SUPPORT	  		((u8) BIT(1))
#define S1G_CAP_INFO_NDP_PS_POLL_SUPPORT  	  		((u8) BIT(2))
#define S1G_CAP_INFO_RAW_OPERATION_SUPPORT   		((u8) BIT(3))
#define S1G_CAP_INFO_PAGE_SLICING_SUPPORT    		((u8) BIT(4))
#define S1G_CAP_INFO_TXOP_SHARING_IMPLICIT_ACK 		((u8) BIT(5))
#define S1G_CAP_INFO_VHT_LINK_ADAPTATION_CAP 		((u8) BIT(6) | BIT(7))
/* s1g_capab[7] */
#define S1G_CAP_INFO_TACK_PS_POLL_RESP_SUPPORT 		((u8) BIT(0))
#define S1G_CAP_INFO_DUPLICATE_1MHZ_SUPPORT 		((u8) BIT(1))
#define S1G_CAP_INFO_MCS_NEGOTIATION_SUPPORT 		((u8) BIT(2))
#define S1G_CAP_INFO_ONE_MHZ_CTRL_RESP_PREAMBLE 	((u8) BIT(3))
#define S1G_CAP_INFO_NDP_BFMING_REPORT_POLL 		((u8) BIT(4))
#define S1G_CAP_INFO_UNSOLICITE_DYNAMIC_AID 		((u8) BIT(5))
#define S1G_CAP_INFO_SECTOR_TRAINING_OPERATION 		((u8) BIT(6))
#define S1G_CAP_INFO_TEMPORARY_PS_MODE_SWITCH 		((u8) BIT(7))
/* s1g_capab[8] */
#define S1G_CAP_INFO_TWT_GROUPING_SUPPORT 			((u8) BIT(0))
#define S1G_CAP_INFO_BDT_CAPBLE 					((u8) BIT(1))
#define S1G_CAP_INFO_COLOR 							((u8) BIT(2) | BIT(3) | BIT(4))
#define S1G_CAP_INFO_TWT_REQUESTER_SUPPORT 			((u8) BIT(5))
#define S1G_CAP_INFO_TWT_RESPONDER_SUPPORT 			((u8) BIT(6))
#define S1G_CAP_INFO_PV1_FRAME_SUPPORT 				((u8) BIT(7))
/* s1g_capab[9] */
#define S1G_CAP_INFO_LINK_ADAPT_PER_NORM_CTRL_RESP_CAP 		((u8) BIT(0))

#define S1G_CAP_INFO_RX_MAX_S1G_MCS_1SS  					 		((u32) BIT(0)| BIT(1))
#define S1G_CAP_INFO_RX_MAX_S1G_MCS_2SS  					 		((u32) BIT(2)| BIT(3))
#define S1G_CAP_INFO_RX_MAX_S1G_MCS_3SS  					 		((u32) BIT(4)| BIT(5))
#define S1G_CAP_INFO_RX_MAX_S1G_MCS_4SS  					 		((u32) BIT(6)| BIT(7))
#define S1G_CAP_INFO_RX_HIGHEST_SUPPORTED_LONG_GI_DATA_RATE   		((u32) BIT(8)| BIT(9)| BIT(10)| BIT(11)| BIT(12)| BIT(13)| BIT(14)| BIT(15)| BIT(16))
#define S1G_CAP_INFO_TX_MAX_S1G_MCS_1SS  					 		((u32) BIT(17)| BIT(18))
#define S1G_CAP_INFO_TX_MAX_S1G_MCS_2SS  					 		((u32) BIT(19)| BIT(20))
#define S1G_CAP_INFO_TX_MAX_S1G_MCS_3SS     				      	((u32) BIT(21)| BIT(22))
#define S1G_CAP_INFO_TX_MAX_S1G_MCS_4SS  					 		((u32) BIT(23)| BIT(24))
#define S1G_CAP_INFO_TX_HIGHEST_SUPPORTED_LONG_GI_DATA_RATE_0_6  	((u32) BIT(25)| BIT(26)| BIT(27)| BIT(28)| BIT(29)| BIT(30)| BIT(31))
#define S1G_CAP_INFO_TX_HIGHEST_SUPPORTED_LONG_GI_DATA_RATE_7_8  	((u8) BIT(0)| BIT(1))
#define S1G_CAP_INFO_RX_SINGLE_SS_S1G_MCS_1MHZ  				  	((u8) BIT(2)| BIT(3))
#define S1G_CAP_INFO_TX_SINGLE_SS_S1G_MCS_1MHZ  				  	((u8) BIT(4)| BIT(5))

/* Info field within S1G operation elements*/
#define S1G_OPER_MIN_S1G_MCS_1SS  ((u16) BIT(0) | BIT(1))
#define S1G_OPER_MAX_S1G_MCS_1SS  ((u16) BIT(2) | BIT(3))
#define S1G_OPER_MIN_S1G_MCS_2SS  ((u16) BIT(4) | BIT(5))
#define S1G_OPER_MAX_S1G_MCS_2SS  ((u16) BIT(6) | BIT(7))
#define S1G_OPER_MIN_S1G_MCS_3SS  ((u16) BIT(8) | BIT(9))
#define S1G_OPER_MAX_S1G_MCS_3SS  ((u16) BIT(10) | BIT(11))
#define S1G_OPER_MIN_S1G_MCS_4SS  ((u16) BIT(12) | BIT(13))
#define S1G_OPER_MAX_S1G_MCS_4SS  ((u16) BIT(14) | BIT(15))

/* HT Capabilities Info field within HT Capabilities element */
#define HT_CAP_INFO_LDPC_CODING_CAP		((u16) BIT(0))
#define HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET	((u16) BIT(1))
#define HT_CAP_INFO_SMPS_MASK			((u16) (BIT(2) | BIT(3)))
#define HT_CAP_INFO_SMPS_STATIC			((u16) 0)
#define HT_CAP_INFO_SMPS_DYNAMIC		((u16) BIT(2))
#define HT_CAP_INFO_SMPS_DISABLED		((u16) (BIT(2) | BIT(3)))
#define HT_CAP_INFO_GREEN_FIELD			((u16) BIT(4))
#define HT_CAP_INFO_SHORT_GI20MHZ		((u16) BIT(5))
#define HT_CAP_INFO_SHORT_GI40MHZ		((u16) BIT(6))
#define HT_CAP_INFO_TX_STBC				((u16) BIT(7))
#define HT_CAP_INFO_RX_STBC_MASK		((u16) (BIT(8) | BIT(9)))
#define HT_CAP_INFO_RX_STBC_1			((u16) BIT(8))
#define HT_CAP_INFO_RX_STBC_12			((u16) BIT(9))
#define HT_CAP_INFO_RX_STBC_123			((u16) (BIT(8) | BIT(9)))
#define HT_CAP_INFO_DELAYED_BA			((u16) BIT(10))
#define HT_CAP_INFO_MAX_AMSDU_SIZE		((u16) BIT(11))
#define HT_CAP_INFO_DSSS_CCK40MHZ		((u16) BIT(12))
/* B13 - Reserved (was PSMP support during P802.11n development) */
#define HT_CAP_INFO_40MHZ_INTOLERANT		((u16) BIT(14))
#define HT_CAP_INFO_LSIG_TXOP_PROTECT_SUPPORT	((u16) BIT(15))

/* HT Extended Capabilities field within HT Capabilities element */
#define EXT_HT_CAP_INFO_PCO			((u16) BIT(0))
#define EXT_HT_CAP_INFO_PCO_TRANS_TIME_MASK	((u16) (BIT(1) | BIT(2)))
#define EXT_HT_CAP_INFO_TRANS_TIME_OFFSET	1
/* B3..B7 - Reserved */
#define EXT_HT_CAP_INFO_MCS_FEEDBACK_MASK	((u16) (BIT(8) | BIT(9)))
#define EXT_HT_CAP_INFO_MCS_FEEDBACK_OFFSET	8
#define EXT_HT_CAP_INFO_HTC_SUPPORT		((u16) BIT(10))
#define EXT_HT_CAP_INFO_RD_RESPONDER		((u16) BIT(11))
/* B12..B15 - Reserved */

/* Transmit Beanforming Capabilities within HT Capabilities element */
#define TX_BF_CAP_IMPLICIT_TXBF_RX_CAP ((u32) BIT(0))
#define TX_BF_CAP_RX_STAGGERED_SOUNDING_CAP ((u32) BIT(1))
#define TX_BF_CAP_TX_STAGGERED_SOUNDING_CAP ((u32) BIT(2))
#define TX_BF_CAP_RX_NDP_CAP ((u32) BIT(3))
#define TX_BF_CAP_TX_NDP_CAP ((u32) BIT(4))
#define TX_BF_CAP_IMPLICIT_TX_BF_CAP ((u32) BIT(5))
#define TX_BF_CAP_CALIBRATION_MASK ((u32) (BIT(6) | BIT(7))
#define TX_BF_CAP_CALIB_OFFSET 6
#define TX_BF_CAP_EXPLICIT_CSI_TXBF_CAP ((u32) BIT(8))
#define TX_BF_CAP_EXPLICIT_NONCOMPR_STEERING_CAP ((u32) BIT(9))
#define TX_BF_CAP_EXPLICIT_COMPR_STEERING_CAP ((u32) BIT(10))
#define TX_BF_CAP_EXPLICIT_TX_BF_CSI_FEEDBACK_MASK ((u32) (BIT(10) | BIT(11)))
#define TX_BF_CAP_EXPLICIT_BF_CSI_FEEDBACK_OFFSET 11
#define TX_BF_CAP_EXPLICIT_UNCOMPR_STEERING_MATRIX_FEEDBACK_OFFSET 13
#define TX_BF_CAP_EXPLICIT_COMPRESSED_STEERING_MATRIX_FEEDBACK_OFFSET 15
#define TX_BF_CAP_MINIMAL_GROUPING_OFFSET 17
#define TX_BF_CAP_CSI_NUM_BEAMFORMER_ANT_OFFSET 19
#define TX_BF_CAP_UNCOMPRESSED_STEERING_MATRIX_BEAMFORMER_ANT_OFFSET 21
#define TX_BF_CAP_COMPRESSED_STEERING_MATRIX_BEAMFORMER_ANT_OFFSET 23
#define TX_BF_CAP_SCI_MAX_OF_ROWS_BEANFORMER_SUPPORTED_OFFSET 25
#define TX_BF_CAP_CHANNEL_ESTIMATION_CAP_MASK ((u32) (BIT(27) | BIT(28)))
#define TX_BF_CAP_CHANNEL_ESTIMATION_CAP_OFFSET 27
/* B29..B31 - Reserved */

/* ASEL Capability field within HT Capabilities element */
#define ASEL_CAP_ASEL_CAPABLE ((u8) BIT(0))
#define ASEL_CAP_EXPLICIT_CSI_FEEDBACK_BASED_TX_AS_CAP ((u8) BIT(1))
#define ASEL_CAP_ANT_INDICES_FEEDBACK_BASED_TX_AS_CAP ((u8) BIT(2))
#define ASEL_CAP_EXPLICIT_CSI_FEEDBACK_CAP ((u8) BIT(3))
#define ASEL_CAP_ANT_INDICES_FEEDBACK_CAP ((u8) BIT(4))
#define ASEL_CAP_RX_AS_CAP ((u8) BIT(5))
#define ASEL_CAP_TX_SOUNDING_PPDUS_CAP ((u8) BIT(6))
/* B7 - Reserved */

/* First octet of HT Operation Information within HT Operation element */
#define HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK	((u8) BIT(0) | BIT(1))
#define HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE		((u8) BIT(0))
#define HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW		((u8) BIT(0) | BIT(1))
#define HT_INFO_HT_PARAM_STA_CHNL_WIDTH			((u8) BIT(2))
#define HT_INFO_HT_PARAM_RIFS_MODE			((u8) BIT(3))
/* B4..B7 - Reserved */

/* HT Protection (B8..B9 of HT Operation Information) */
#define HT_PROT_NO_PROTECTION           0
#define HT_PROT_NONMEMBER_PROTECTION    1
#define HT_PROT_20MHZ_PROTECTION        2
#define HT_PROT_NON_HT_MIXED            3
/* Bits within ieee80211_ht_operation::operation_mode (BIT(0) maps to B8 in
 * HT Operation Information) */
#define HT_OPER_OP_MODE_HT_PROT_MASK ((u16) (BIT(0) | BIT(1))) /* B8..B9 */
#define HT_OPER_OP_MODE_NON_GF_HT_STAS_PRESENT	((u16) BIT(2)) /* B10 */
/* BIT(3), i.e., B11 in HT Operation Information field - Reserved */
#define HT_OPER_OP_MODE_OBSS_NON_HT_STAS_PRESENT	((u16) BIT(4)) /* B12 */
/* BIT(5)..BIT(15), i.e., B13..B23 - Reserved */

/* Last two octets of HT Operation Information (BIT(0) = B24) */
/* B24..B29 - Reserved */
#define HT_OPER_PARAM_DUAL_BEACON			((u16) BIT(6))
#define HT_OPER_PARAM_DUAL_CTS_PROTECTION		((u16) BIT(7))
#define HT_OPER_PARAM_STBC_BEACON			((u16) BIT(8))
#define HT_OPER_PARAM_LSIG_TXOP_PROT_FULL_SUPP		((u16) BIT(9))
#define HT_OPER_PARAM_PCO_ACTIVE			((u16) BIT(10))
#define HT_OPER_PARAM_PCO_PHASE				((u16) BIT(11))
/* B36..B39 - Reserved */

#define BSS_MEMBERSHIP_SELECTOR_VHT_PHY 126
#define BSS_MEMBERSHIP_SELECTOR_HT_PHY 	127
#define BSS_MEMBERSHIP_SELECTOR_S1G_PHY 125

/* VHT Defines */
#define VHT_CAP_MAX_MPDU_LENGTH_7991                ((u32) BIT(0))
#define VHT_CAP_MAX_MPDU_LENGTH_11454               ((u32) BIT(1))
#define VHT_CAP_MAX_MPDU_LENGTH_MASK                ((u32) BIT(0) | BIT(1))
#define VHT_CAP_MAX_MPDU_LENGTH_MASK_SHIFT          0
#define VHT_CAP_SUPP_CHAN_WIDTH_160MHZ              ((u32) BIT(2))
#define VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ     ((u32) BIT(3))
#define VHT_CAP_SUPP_CHAN_WIDTH_MASK                ((u32) BIT(2) | BIT(3))
#define VHT_CAP_RXLDPC                              ((u32) BIT(4))
#define VHT_CAP_SHORT_GI_80                         ((u32) BIT(5))
#define VHT_CAP_SHORT_GI_160                        ((u32) BIT(6))
#define VHT_CAP_TXSTBC                              ((u32) BIT(7))
#define VHT_CAP_RXSTBC_1                            ((u32) BIT(8))
#define VHT_CAP_RXSTBC_2                            ((u32) BIT(9))
#define VHT_CAP_RXSTBC_3                            ((u32) BIT(8) | BIT(9))
#define VHT_CAP_RXSTBC_4                            ((u32) BIT(10))
#define VHT_CAP_RXSTBC_MASK                         ((u32) BIT(8) | BIT(9) | \
							   BIT(10))
#define VHT_CAP_RXSTBC_MASK_SHIFT                   8
#define VHT_CAP_SU_BEAMFORMER_CAPABLE               ((u32) BIT(11))
#define VHT_CAP_SU_BEAMFORMEE_CAPABLE               ((u32) BIT(12))
#define VHT_CAP_BEAMFORMEE_STS_MAX                  ((u32) BIT(13) | \
							   BIT(14) | BIT(15))
#define VHT_CAP_BEAMFORMEE_STS_MAX_SHIFT            13
#define VHT_CAP_BEAMFORMEE_STS_OFFSET               13
#define VHT_CAP_SOUNDING_DIMENSION_MAX              ((u32) BIT(16) | \
							   BIT(17) | BIT(18))
#define VHT_CAP_SOUNDING_DIMENSION_MAX_SHIFT        16
#define VHT_CAP_SOUNDING_DIMENSION_OFFSET           16
#define VHT_CAP_MU_BEAMFORMER_CAPABLE               ((u32) BIT(19))
#define VHT_CAP_MU_BEAMFORMEE_CAPABLE               ((u32) BIT(20))
#define VHT_CAP_VHT_TXOP_PS                         ((u32) BIT(21))
#define VHT_CAP_HTC_VHT                             ((u32) BIT(22))

#define VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_1        ((u32) BIT(23))
#define VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_2        ((u32) BIT(24))
#define VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_3        ((u32) BIT(23) | BIT(24))
#define VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_4        ((u32) BIT(25))
#define VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_5        ((u32) BIT(23) | BIT(25))
#define VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_6        ((u32) BIT(24) | BIT(25))
#define VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MAX      ((u32) BIT(23) | \
							   BIT(24) | BIT(25))
#define VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MAX_SHIFT 23
#define VHT_CAP_VHT_LINK_ADAPTATION_VHT_UNSOL_MFB   ((u32) BIT(27))
#define VHT_CAP_VHT_LINK_ADAPTATION_VHT_MRQ_MFB     ((u32) BIT(26) | BIT(27))
#define VHT_CAP_RX_ANTENNA_PATTERN                  ((u32) BIT(28))
#define VHT_CAP_TX_ANTENNA_PATTERN                  ((u32) BIT(29))

#define VHT_OPMODE_CHANNEL_WIDTH_MASK		    ((u8) BIT(0) | BIT(1))
#define VHT_OPMODE_CHANNEL_RxNSS_MASK		    ((u8) BIT(4) | BIT(5) | \
						     BIT(6))
#define VHT_OPMODE_NOTIF_RX_NSS_SHIFT		    4

#define VHT_RX_NSS_MAX_STREAMS			    8

/* VHT channel widths */
#define VHT_CHANWIDTH_USE_HT	0
#define VHT_CHANWIDTH_80MHZ	1
#define VHT_CHANWIDTH_160MHZ	2
#define VHT_CHANWIDTH_80P80MHZ	3

#define OUI_MICROSOFT 0x0050f2 /* Microsoft (also used in Wi-Fi specs)
				* 00:50:F2 */
#define WPA_IE_VENDOR_TYPE 0x0050f201
#define WMM_IE_VENDOR_TYPE 0x0050f202
#define WPS_IE_VENDOR_TYPE 0x0050f204
#define OUI_WFA 0x506f9a
#define P2P_IE_VENDOR_TYPE 0x506f9a09
#define WFD_IE_VENDOR_TYPE 0x506f9a0a
#define WFD_OUI_TYPE 10
#define HS20_IE_VENDOR_TYPE 0x506f9a10
#define OSEN_IE_VENDOR_TYPE 0x506f9a12
#define MBO_IE_VENDOR_TYPE 0x506f9a16
#define MBO_OUI_TYPE 22

#define WMM_OUI_TYPE 2
#define WMM_OUI_SUBTYPE_INFORMATION_ELEMENT 0
#define WMM_OUI_SUBTYPE_PARAMETER_ELEMENT 1
#define WMM_OUI_SUBTYPE_TSPEC_ELEMENT 2
#define WMM_VERSION 1

#define WMM_ACTION_CODE_ADDTS_REQ 0
#define WMM_ACTION_CODE_ADDTS_RESP 1
#define WMM_ACTION_CODE_DELTS 2

#define WMM_ADDTS_STATUS_ADMISSION_ACCEPTED 0
#define WMM_ADDTS_STATUS_INVALID_PARAMETERS 1
/* 2 - Reserved */
#define WMM_ADDTS_STATUS_REFUSED 3
/* 4-255 - Reserved */

/* WMM TSPEC Direction Field Values */
#define WMM_TSPEC_DIRECTION_UPLINK 0
#define WMM_TSPEC_DIRECTION_DOWNLINK 1
/* 2 - Reserved */
#define WMM_TSPEC_DIRECTION_BI_DIRECTIONAL 3

/*
 * WMM Information Element (used in (Re)Association Request frames; may also be
 * used in Beacon frames)
 */
struct wmm_information_element {
	/* Element ID: 221 (0xdd); Length: 7 */
	/* required fields for WMM version 1 */
	u8 oui[3]; /* 00:50:f2 */
	u8 oui_type; /* 2 */
	u8 oui_subtype; /* 0 */
	u8 version; /* 1 for WMM version 1.0 */
	u8 qos_info; /* AP/STA specific QoS info */

} STRUCT_PACKED;

#define WMM_QOSINFO_AP_UAPSD 0x80

#define WMM_QOSINFO_STA_AC_MASK 0x0f
#define WMM_QOSINFO_STA_SP_MASK 0x03
#define WMM_QOSINFO_STA_SP_SHIFT 5

#define WMM_AC_AIFSN_MASK 0x0f
#define WMM_AC_AIFNS_SHIFT 0
#define WMM_AC_ACM 0x10
#define WMM_AC_ACI_MASK 0x60
#define WMM_AC_ACI_SHIFT 5

#define WMM_AC_ECWMIN_MASK 0x0f
#define WMM_AC_ECWMIN_SHIFT 0
#define WMM_AC_ECWMAX_MASK 0xf0
#define WMM_AC_ECWMAX_SHIFT 4

struct wmm_ac_parameter {
	u8 aci_aifsn; /* AIFSN, ACM, ACI */
	u8 cw; /* ECWmin, ECWmax (CW = 2^ECW - 1) */
	le16 txop_limit;
}  STRUCT_PACKED;

/*
 * WMM Parameter Element (used in Beacon, Probe Response, and (Re)Association
 * Response frmaes)
 */
struct wmm_parameter_element {
	/* Element ID: 221 (0xdd); Length: 24 */
	/* required fields for WMM version 1 */
	u8 oui[3]; /* 00:50:f2 */
	u8 oui_type; /* 2 */
	u8 oui_subtype; /* 1 */
	u8 version; /* 1 for WMM version 1.0 */
	u8 qos_info; /* AP/STA specific QoS info */
	u8 reserved; /* 0 */
	struct wmm_ac_parameter ac[4]; /* AC_BE, AC_BK, AC_VI, AC_VO */

} STRUCT_PACKED;

/* WMM TSPEC Element */
struct wmm_tspec_element {
	u8 eid; /* 221 = 0xdd */
	u8 length; /* 6 + 55 = 61 */
	u8 oui[3]; /* 00:50:f2 */
	u8 oui_type; /* 2 */
	u8 oui_subtype; /* 2 */
	u8 version; /* 1 */
	/* WMM TSPEC body (55 octets): */
	u8 ts_info[3];
	le16 nominal_msdu_size;
	le16 maximum_msdu_size;
	le32 minimum_service_interval;
	le32 maximum_service_interval;
	le32 inactivity_interval;
	le32 suspension_interval;
	le32 service_start_time;
	le32 minimum_data_rate;
	le32 mean_data_rate;
	le32 peak_data_rate;
	le32 maximum_burst_size;
	le32 delay_bound;
	le32 minimum_phy_rate;
	le16 surplus_bandwidth_allowance;
	le16 medium_time;
} STRUCT_PACKED;


/* Access Categories / ACI to AC coding */
enum wmm_ac {
	WMM_AC_BE = 0 /* Best Effort */,
	WMM_AC_BK = 1 /* Background */,
	WMM_AC_VI = 2 /* Video */,
	WMM_AC_VO = 3 /* Voice */,
	WMM_AC_NUM = 4
};


#define HS20_INDICATION_OUI_TYPE 16
#define HS20_ANQP_OUI_TYPE 17
#define HS20_OSEN_OUI_TYPE 18
#define HS20_STYPE_QUERY_LIST 1
#define HS20_STYPE_CAPABILITY_LIST 2
#define HS20_STYPE_OPERATOR_FRIENDLY_NAME 3
#define HS20_STYPE_WAN_METRICS 4
#define HS20_STYPE_CONNECTION_CAPABILITY 5
#define HS20_STYPE_NAI_HOME_REALM_QUERY 6
#define HS20_STYPE_OPERATING_CLASS 7
#define HS20_STYPE_OSU_PROVIDERS_LIST 8
#define HS20_STYPE_ICON_REQUEST 10
#define HS20_STYPE_ICON_BINARY_FILE 11

#define HS20_DGAF_DISABLED 0x01
#define HS20_PPS_MO_ID_PRESENT 0x02
#define HS20_ANQP_DOMAIN_ID_PRESENT 0x04
#define HS20_VERSION 0x10 /* Release 2 */

/* WNM-Notification WFA vendors specific subtypes */
#define HS20_WNM_SUB_REM_NEEDED 0
#define HS20_WNM_DEAUTH_IMMINENT_NOTICE 1

#define HS20_DEAUTH_REASON_CODE_BSS 0
#define HS20_DEAUTH_REASON_CODE_ESS 1

/* MBO v0.0_r19, 4.2: MBO Attributes */
/* Table 4-5: MBO Attributes */
enum mbo_attr_id {
	MBO_ATTR_ID_AP_CAPA_IND = 1,
	MBO_ATTR_ID_NON_PREF_CHAN_REPORT = 2,
	MBO_ATTR_ID_CELL_DATA_CAPA = 3,
	MBO_ATTR_ID_ASSOC_DISALLOW = 4,
	MBO_ATTR_ID_CELL_DATA_PREF = 5,
	MBO_ATTR_ID_TRANSITION_REASON = 6,
	MBO_ATTR_ID_TRANSITION_REJECT_REASON = 7,
	MBO_ATTR_ID_ASSOC_RETRY_DELAY = 8,
};

/* MBO v0.0_r19, 4.2.1: MBO AP Capability Indication Attribute */
/* Table 4-7: MBO AP Capability Indication Field Values */
#define MBO_AP_CAPA_CELL_AWARE BIT(6)

/* MBO v0.0_r19, 4.2.2: Non-preferred Channel Report Attribute */
/* Table 4-10: Reason Code Field Values */
enum mbo_non_pref_chan_reason {
	MBO_NON_PREF_CHAN_REASON_UNSPECIFIED = 0,
	MBO_NON_PREF_CHAN_REASON_RSSI = 1,
	MBO_NON_PREF_CHAN_REASON_EXT_INTERFERENCE = 2,
	MBO_NON_PREF_CHAN_REASON_INT_INTERFERENCE = 3,
};

/* MBO v0.0_r19, 4.2.3: Cellular Data Capabilities Attribute */
/* Table 4-13: Cellular Data Connectivity Field */
enum mbo_cellular_capa {
	MBO_CELL_CAPA_AVAILABLE = 1,
	MBO_CELL_CAPA_NOT_AVAILABLE = 2,
	MBO_CELL_CAPA_NOT_SUPPORTED = 3,
};

/* MBO v0.0_r19, 4.2.4: Association Disallowed Attribute */
/* Table 4-15: Reason Code Field Values */
enum mbo_assoc_disallow_reason {
	MBO_ASSOC_DISALLOW_REASON_UNSPECIFIED = 1,
	MBO_ASSOC_DISALLOW_REASON_MAX_STA = 2,
	MBO_ASSOC_DISALLOW_REASON_AIR_INTERFERENCE = 3,
	MBO_ASSOC_DISALLOW_REASON_AUTH_SERVER_OVERLOAD = 4,
	MBO_ASSOC_DISALLOW_REASON_LOW_RSSI = 5,
};

/* MBO v0.0_r19, 4.2.5: Cellular Data Connection Preference Attribute */
/* Table 4-17: Cellular Preference Field Values */
enum mbo_cell_pref {
	MBO_CELL_PREF_EXCLUDED = 0,
	MBO_CELL_PREF_NO_USE = 1,
	MBO_CELL_PREF_USE = 255
};

/* MBO v0.0_r19, 4.2.6: Transition Reason Code Attribute */
/* Table 4-19: Transition Reason Code Field Values */
enum mbo_transition_reason {
	MBO_TRANSITION_REASON_UNSPECIFIED = 0,
	MBO_TRANSITION_REASON_FRAME_LOSS = 1,
	MBO_TRANSITION_REASON_DELAY = 2,
	MBO_TRANSITION_REASON_BANDWIDTH = 3,
	MBO_TRANSITION_REASON_LOAD_BALANCE = 4,
	MBO_TRANSITION_REASON_RSSI = 5,
	MBO_TRANSITION_REASON_RETRANSMISSIONS = 6,
	MBO_TRANSITION_REASON_INTERFERENCE = 7,
	MBO_TRANSITION_REASON_GRAY_ZONE = 8,
	MBO_TRANSITION_REASON_PREMIUM_AP = 9,
};

/* MBO v0.0_r19, 4.2.7: Transition Rejection Reason Code Attribute */
/* Table 4-21: Transition Rejection Reason Code Field Values */
enum mbo_transition_reject_reason {
	MBO_TRANSITION_REJECT_REASON_UNSPECIFIED = 0,
	MBO_TRANSITION_REJECT_REASON_FRAME_LOSS = 1,
	MBO_TRANSITION_REJECT_REASON_DELAY = 2,
	MBO_TRANSITION_REJECT_REASON_QOS_CAPACITY = 3,
	MBO_TRANSITION_REJECT_REASON_RSSI = 4,
	MBO_TRANSITION_REJECT_REASON_INTERFERENCE = 5,
	MBO_TRANSITION_REJECT_REASON_SERVICES = 6,
};

/* MBO v0.0_r19, 4.4: WNM-Notification vendor subelements */
enum wfa_wnm_notif_subelem_id {
	WFA_WNM_NOTIF_SUBELEM_NON_PREF_CHAN_REPORT = 2,
	WFA_WNM_NOTIF_SUBELEM_CELL_DATA_CAPA = 3,
};

/* MBO v0.0_r25, 4.3: MBO ANQP-elements */
#define MBO_ANQP_OUI_TYPE 0x12
#define MBO_ANQP_SUBTYPE_CELL_CONN_PREF 1

/* Wi-Fi Direct (P2P) */

#define P2P_OUI_TYPE 9

enum p2p_attr_id {
	P2P_ATTR_STATUS = 0,
	P2P_ATTR_MINOR_REASON_CODE = 1,
	P2P_ATTR_CAPABILITY = 2,
	P2P_ATTR_DEVICE_ID = 3,
	P2P_ATTR_GROUP_OWNER_INTENT = 4,
	P2P_ATTR_CONFIGURATION_TIMEOUT = 5,
	P2P_ATTR_LISTEN_CHANNEL = 6,
	P2P_ATTR_GROUP_BSSID = 7,
	P2P_ATTR_EXT_LISTEN_TIMING = 8,
	P2P_ATTR_INTENDED_INTERFACE_ADDR = 9,
	P2P_ATTR_MANAGEABILITY = 10,
	P2P_ATTR_CHANNEL_LIST = 11,
	P2P_ATTR_NOTICE_OF_ABSENCE = 12,
	P2P_ATTR_DEVICE_INFO = 13,
	P2P_ATTR_GROUP_INFO = 14,
	P2P_ATTR_GROUP_ID = 15,
	P2P_ATTR_INTERFACE = 16,
	P2P_ATTR_OPERATING_CHANNEL = 17,
	P2P_ATTR_INVITATION_FLAGS = 18,
	P2P_ATTR_OOB_GO_NEG_CHANNEL = 19,
	P2P_ATTR_SERVICE_HASH = 21,
	P2P_ATTR_SESSION_INFORMATION_DATA = 22,
	P2P_ATTR_CONNECTION_CAPABILITY = 23,
	P2P_ATTR_ADVERTISEMENT_ID = 24,
	P2P_ATTR_ADVERTISED_SERVICE = 25,
	P2P_ATTR_SESSION_ID = 26,
	P2P_ATTR_FEATURE_CAPABILITY = 27,
	P2P_ATTR_PERSISTENT_GROUP = 28,
	P2P_ATTR_VENDOR_SPECIFIC = 221
};

#define P2P_MAX_GO_INTENT 15

/* P2P Capability - Device Capability bitmap */
#define P2P_DEV_CAPAB_SERVICE_DISCOVERY BIT(0)
#define P2P_DEV_CAPAB_CLIENT_DISCOVERABILITY BIT(1)
#define P2P_DEV_CAPAB_CONCURRENT_OPER BIT(2)
#define P2P_DEV_CAPAB_INFRA_MANAGED BIT(3)
#define P2P_DEV_CAPAB_DEVICE_LIMIT BIT(4)
#define P2P_DEV_CAPAB_INVITATION_PROCEDURE BIT(5)

/* P2P Capability - Group Capability bitmap */
#define P2P_GROUP_CAPAB_GROUP_OWNER BIT(0)
#define P2P_GROUP_CAPAB_PERSISTENT_GROUP BIT(1)
#define P2P_GROUP_CAPAB_GROUP_LIMIT BIT(2)
#define P2P_GROUP_CAPAB_INTRA_BSS_DIST BIT(3)
#define P2P_GROUP_CAPAB_CROSS_CONN BIT(4)
#define P2P_GROUP_CAPAB_PERSISTENT_RECONN BIT(5)
#define P2P_GROUP_CAPAB_GROUP_FORMATION BIT(6)
#define P2P_GROUP_CAPAB_IP_ADDR_ALLOCATION BIT(7)

/* P2PS Coordination Protocol Transport Bitmap */
#define P2PS_FEATURE_CAPAB_UDP_TRANSPORT BIT(0)
#define P2PS_FEATURE_CAPAB_MAC_TRANSPORT BIT(1)

struct p2ps_feature_capab {
	u8 cpt;
	u8 reserved;
} STRUCT_PACKED;

/* Invitation Flags */
#define P2P_INVITATION_FLAGS_TYPE BIT(0)

/* P2P Manageability */
#define P2P_MAN_DEVICE_MANAGEMENT BIT(0)
#define P2P_MAN_CROSS_CONNECTION_PERMITTED BIT(1)
#define P2P_MAN_COEXISTENCE_OPTIONAL BIT(2)

enum p2p_status_code {
	P2P_SC_SUCCESS = 0,
	P2P_SC_FAIL_INFO_CURRENTLY_UNAVAILABLE = 1,
	P2P_SC_FAIL_INCOMPATIBLE_PARAMS = 2,
	P2P_SC_FAIL_LIMIT_REACHED = 3,
	P2P_SC_FAIL_INVALID_PARAMS = 4,
	P2P_SC_FAIL_UNABLE_TO_ACCOMMODATE = 5,
	P2P_SC_FAIL_PREV_PROTOCOL_ERROR = 6,
	P2P_SC_FAIL_NO_COMMON_CHANNELS = 7,
	P2P_SC_FAIL_UNKNOWN_GROUP = 8,
	P2P_SC_FAIL_BOTH_GO_INTENT_15 = 9,
	P2P_SC_FAIL_INCOMPATIBLE_PROV_METHOD = 10,
	P2P_SC_FAIL_REJECTED_BY_USER = 11,
	P2P_SC_SUCCESS_DEFERRED = 12,
};

enum p2p_role_indication {
	P2P_DEVICE_NOT_IN_GROUP = 0x00,
	P2P_CLIENT_IN_A_GROUP = 0x01,
	P2P_GO_IN_A_GROUP = 0x02,
};

#define P2P_WILDCARD_SSID "DIRECT-"
#define P2P_WILDCARD_SSID_LEN 7

/* P2P action frames */
enum p2p_act_frame_type {
	P2P_NOA = 0,
	P2P_PRESENCE_REQ = 1,
	P2P_PRESENCE_RESP = 2,
	P2P_GO_DISC_REQ = 3
};

/* P2P public action frames */
enum p2p_action_frame_type {
	P2P_GO_NEG_REQ = 0,
	P2P_GO_NEG_RESP = 1,
	P2P_GO_NEG_CONF = 2,
	P2P_INVITATION_REQ = 3,
	P2P_INVITATION_RESP = 4,
	P2P_DEV_DISC_REQ = 5,
	P2P_DEV_DISC_RESP = 6,
	P2P_PROV_DISC_REQ = 7,
	P2P_PROV_DISC_RESP = 8
};

enum p2p_service_protocol_type {
	P2P_SERV_ALL_SERVICES = 0,
	P2P_SERV_BONJOUR = 1,
	P2P_SERV_UPNP = 2,
	P2P_SERV_WS_DISCOVERY = 3,
	P2P_SERV_WIFI_DISPLAY = 4,
	P2P_SERV_P2PS = 11,
	P2P_SERV_VENDOR_SPECIFIC = 255
};

enum p2p_sd_status {
	P2P_SD_SUCCESS = 0,
	P2P_SD_PROTO_NOT_AVAILABLE = 1,
	P2P_SD_REQUESTED_INFO_NOT_AVAILABLE = 2,
	P2P_SD_BAD_REQUEST = 3
};


enum wifi_display_subelem {
	WFD_SUBELEM_DEVICE_INFO = 0,
	WFD_SUBELEM_ASSOCIATED_BSSID = 1,
	WFD_SUBELEM_AUDIO_FORMATS = 2,
	WFD_SUBELEM_VIDEO_FORMATS = 3,
	WFD_SUBELEM_3D_VIDEO_FORMATS = 4,
	WFD_SUBELEM_CONTENT_PROTECTION = 5,
	WFD_SUBELEM_COUPLED_SINK = 6,
	WFD_SUBELEM_EXT_CAPAB = 7,
	WFD_SUBELEM_LOCAL_IP_ADDRESS = 8,
	WFD_SUBELEM_SESSION_INFO = 9
};

/* 802.11s */
#define MESH_SYNC_METHOD_NEIGHBOR_OFFSET 1
#define MESH_SYNC_METHOD_VENDOR		255
#define MESH_PATH_PROTOCOL_HWMP		1
#define MESH_PATH_PROTOCOL_VENDOR	255
#define MESH_PATH_METRIC_AIRTIME	1
#define MESH_PATH_METRIC_VENDOR		255
/* IEEE 802.11s - Mesh Capability */
#define MESH_CAP_ACCEPT_ADDITIONAL_PEER	BIT(0)
#define MESH_CAP_MCCA_SUPPORTED		BIT(1)
#define MESH_CAP_MCCA_ENABLED		BIT(2)
#define MESH_CAP_FORWARDING		BIT(3)
#define MESH_CAP_MBCA_ENABLED		BIT(4)
#define MESH_CAP_TBTT_ADJUSTING		BIT(5)
#define MESH_CAP_MESH_PS_LEVEL		BIT(6)

enum plink_action_field {
	PLINK_OPEN = 1,
	PLINK_CONFIRM,
	PLINK_CLOSE
};

#define OUI_BROADCOM 0x00904c /* Broadcom (Epigram) */
#define VENDOR_VHT_TYPE		0x04
#define VENDOR_VHT_SUBTYPE	0x08
#define VENDOR_VHT_SUBTYPE2	0x00

#define VENDOR_HT_CAPAB_OUI_TYPE 0x33 /* 00-90-4c:0x33 */

/* cipher suite selectors */
#define WLAN_CIPHER_SUITE_USE_GROUP	0x000FAC00
#define WLAN_CIPHER_SUITE_WEP40		0x000FAC01
#define WLAN_CIPHER_SUITE_TKIP		0x000FAC02
/* reserved: 				0x000FAC03 */
#define WLAN_CIPHER_SUITE_CCMP		0x000FAC04
#define WLAN_CIPHER_SUITE_WEP104	0x000FAC05
#define WLAN_CIPHER_SUITE_AES_CMAC	0x000FAC06
#define WLAN_CIPHER_SUITE_NO_GROUP_ADDR	0x000FAC07
#define WLAN_CIPHER_SUITE_GCMP		0x000FAC08
#define WLAN_CIPHER_SUITE_GCMP_256	0x000FAC09
#define WLAN_CIPHER_SUITE_CCMP_256	0x000FAC0A
#define WLAN_CIPHER_SUITE_BIP_GMAC_128	0x000FAC0B
#define WLAN_CIPHER_SUITE_BIP_GMAC_256	0x000FAC0C
#define WLAN_CIPHER_SUITE_BIP_CMAC_256	0x000FAC0D

#define WLAN_CIPHER_SUITE_SMS4		0x00147201

#define WLAN_CIPHER_SUITE_CKIP		0x00409600
#define WLAN_CIPHER_SUITE_CKIP_CMIC	0x00409601
#define WLAN_CIPHER_SUITE_CMIC		0x00409602
#define WLAN_CIPHER_SUITE_KRK		0x004096FF /* for nl80211 use only */

/* AKM suite selectors */
#define WLAN_AKM_SUITE_8021X		0x000FAC01
#define WLAN_AKM_SUITE_PSK		0x000FAC02
#define WLAN_AKM_SUITE_FT_8021X		0x000FAC03
#define WLAN_AKM_SUITE_FT_PSK		0x000FAC04
#define WLAN_AKM_SUITE_8021X_SHA256	0x000FAC05
#define WLAN_AKM_SUITE_PSK_SHA256	0x000FAC06
#define WLAN_AKM_SUITE_8021X_SUITE_B	0x000FAC11
#define WLAN_AKM_SUITE_8021X_SUITE_B_192	0x000FAC12
#define WLAN_AKM_SUITE_CCKM		0x00409600
#define WLAN_AKM_SUITE_OSEN		0x506f9a01


/* IEEE 802.11v - WNM Action field values */
enum wnm_action {
	WNM_EVENT_REQ = 0,
	WNM_EVENT_REPORT = 1,
	WNM_DIAGNOSTIC_REQ = 2,
	WNM_DIAGNOSTIC_REPORT = 3,
	WNM_LOCATION_CFG_REQ = 4,
	WNM_LOCATION_CFG_RESP = 5,
	WNM_BSS_TRANS_MGMT_QUERY = 6,
	WNM_BSS_TRANS_MGMT_REQ = 7,
	WNM_BSS_TRANS_MGMT_RESP = 8,
	WNM_FMS_REQ = 9,
	WNM_FMS_RESP = 10,
	WNM_COLLOCATED_INTERFERENCE_REQ = 11,
	WNM_COLLOCATED_INTERFERENCE_REPORT = 12,
	WNM_TFS_REQ = 13,
	WNM_TFS_RESP = 14,
	WNM_TFS_NOTIFY = 15,
	WNM_SLEEP_MODE_REQ = 16,
	WNM_SLEEP_MODE_RESP = 17,
	WNM_TIM_BROADCAST_REQ = 18,
	WNM_TIM_BROADCAST_RESP = 19,
	WNM_QOS_TRAFFIC_CAPAB_UPDATE = 20,
	WNM_CHANNEL_USAGE_REQ = 21,
	WNM_CHANNEL_USAGE_RESP = 22,
	WNM_DMS_REQ = 23,
	WNM_DMS_RESP = 24,
	WNM_TIMING_MEASUREMENT_REQ = 25,
	WNM_NOTIFICATION_REQ = 26,
	WNM_NOTIFICATION_RESP = 27
};

/* IEEE 802.11v - BSS Transition Management Request - Request Mode */
#define WNM_BSS_TM_REQ_PREF_CAND_LIST_INCLUDED BIT(0)
#define WNM_BSS_TM_REQ_ABRIDGED BIT(1)
#define WNM_BSS_TM_REQ_DISASSOC_IMMINENT BIT(2)
#define WNM_BSS_TM_REQ_BSS_TERMINATION_INCLUDED BIT(3)
#define WNM_BSS_TM_REQ_ESS_DISASSOC_IMMINENT BIT(4)

/* IEEE Std 802.11-2012 - Table 8-253 */
enum bss_trans_mgmt_status_code {
	WNM_BSS_TM_ACCEPT = 0,
	WNM_BSS_TM_REJECT_UNSPECIFIED = 1,
	WNM_BSS_TM_REJECT_INSUFFICIENT_BEACON = 2,
	WNM_BSS_TM_REJECT_INSUFFICIENT_CAPABITY = 3,
	WNM_BSS_TM_REJECT_UNDESIRED = 4,
	WNM_BSS_TM_REJECT_DELAY_REQUEST = 5,
	WNM_BSS_TM_REJECT_STA_CANDIDATE_LIST_PROVIDED = 6,
	WNM_BSS_TM_REJECT_NO_SUITABLE_CANDIDATES = 7,
	WNM_BSS_TM_REJECT_LEAVING_ESS = 8
};

/*
 * IEEE P802.11-REVmc/D5.0 Table 9-150 - Optional subelement IDs for
 * neighbor report
 */
#define WNM_NEIGHBOR_TSF                         1
#define WNM_NEIGHBOR_CONDENSED_COUNTRY_STRING    2
#define WNM_NEIGHBOR_BSS_TRANSITION_CANDIDATE    3
#define WNM_NEIGHBOR_BSS_TERMINATION_DURATION    4
#define WNM_NEIGHBOR_BEARING                     5
#define WNM_NEIGHBOR_WIDE_BW_CHAN                6
#define WNM_NEIGHBOR_MEASUREMENT_REPORT         39
#define WNM_NEIGHBOR_HT_CAPAB                   45
#define WNM_NEIGHBOR_HT_OPER                    61
#define WNM_NEIGHBOR_SEC_CHAN_OFFSET            62
#define WNM_NEIGHBOR_MEASUREMENT_PILOT          66
#define WNM_NEIGHBOR_RRM_ENABLED_CAPABILITIES   70
#define WNM_NEIGHBOR_MULTIPLE_BSSID             71
#define WNM_NEIGHBOR_VHT_CAPAB                 191
#define WNM_NEIGHBOR_VHT_OPER                  192

/* QoS action */
enum qos_action {
	QOS_ADDTS_REQ = 0,
	QOS_ADDTS_RESP = 1,
	QOS_DELTS = 2,
	QOS_SCHEDULE = 3,
	QOS_QOS_MAP_CONFIG = 4,
};

/* IEEE Std 802.11-2012, 8.4.2.62 20/40 BSS Coexistence element */
#define WLAN_20_40_BSS_COEX_INFO_REQ            BIT(0)
#define WLAN_20_40_BSS_COEX_40MHZ_INTOL         BIT(1)
#define WLAN_20_40_BSS_COEX_20MHZ_WIDTH_REQ     BIT(2)
#define WLAN_20_40_BSS_COEX_OBSS_EXEMPT_REQ     BIT(3)
#define WLAN_20_40_BSS_COEX_OBSS_EXEMPT_GRNT    BIT(4)

struct ieee80211_2040_bss_coex_ie {
	u8 element_id;
	u8 length;
	u8 coex_param;
} STRUCT_PACKED;

struct ieee80211_2040_intol_chan_report {
	u8 element_id;
	u8 length;
	u8 op_class;
	u8 variable[0];	/* Channel List */
} STRUCT_PACKED;

/* IEEE 802.11v - WNM-Sleep Mode element */
struct wnm_sleep_element {
	u8 eid;     /* WLAN_EID_WNMSLEEP */
	u8 len;
	u8 action_type; /* WNM_SLEEP_ENTER/WNM_SLEEP_MODE_EXIT */
	u8 status;
	le16 intval;
} STRUCT_PACKED;

#define WNM_SLEEP_MODE_ENTER 0
#define WNM_SLEEP_MODE_EXIT 1

enum wnm_sleep_mode_response_status {
	WNM_STATUS_SLEEP_ACCEPT = 0,
	WNM_STATUS_SLEEP_EXIT_ACCEPT_GTK_UPDATE = 1,
	WNM_STATUS_DENIED_ACTION = 2,
	WNM_STATUS_DENIED_TMP = 3,
	WNM_STATUS_DENIED_KEY = 4,
	WNM_STATUS_DENIED_OTHER_WNM_SERVICE = 5
};

/* WNM-Sleep Mode subelement IDs */
enum wnm_sleep_mode_subelement_id {
	WNM_SLEEP_SUBELEM_GTK = 0,
	WNM_SLEEP_SUBELEM_IGTK = 1
};

/* Channel Switch modes (802.11h) */
#define CHAN_SWITCH_MODE_ALLOW_TX	0
#define CHAN_SWITCH_MODE_BLOCK_TX	1

struct tpc_report {
	u8 eid;
	u8 len;
	u8 tx_power;
	u8 link_margin;
} STRUCT_PACKED;

#define RRM_CAPABILITIES_IE_LEN 5

/* IEEE Std 802.11-2012, 8.5.7.4 - Link Measurement Request frame format */
struct rrm_link_measurement_request {
	u8 dialog_token;
	s8 tx_power;
	s8 max_tp;
	u8 variable[0];
} STRUCT_PACKED;

/* IEEE Std 802.11-2012, 8.5.7.5 - Link Measurement Report frame format */
struct rrm_link_measurement_report {
	u8 dialog_token;
	struct tpc_report tpc;
	u8 rx_ant_id;
	u8 tx_ant_id;
	u8 rcpi;
	u8 rsni;
	u8 variable[0];
} STRUCT_PACKED;

/* IEEE Std 802.11ad-2012 - Multi-band element */
struct multi_band_ie {
	u8 eid; /* WLAN_EID_MULTI_BAND */
	u8 len;
	u8 mb_ctrl;
	u8 band_id;
	u8 op_class;
	u8 chan;
	u8 bssid[ETH_ALEN];
	le16 beacon_int;
	u8 tsf_offs[8];
	u8 mb_connection_capability;
	u8 fst_session_tmout;
	/* Optional:
	 *   STA MAC Address
	 *   Pairwise Cipher Suite Count
	 *   Pairwise Cipher Suite List
	 */
	u8 variable[0];
} STRUCT_PACKED;

enum mb_ctrl_sta_role {
	MB_STA_ROLE_AP = 0,
	MB_STA_ROLE_TDLS_STA = 1,
	MB_STA_ROLE_IBSS_STA = 2,
	MB_STA_ROLE_PCP = 3,
	MB_STA_ROLE_NON_PCP_NON_AP = 4
};

#define MB_CTRL_ROLE_MASK (BIT(0) | BIT(1) | BIT(2))
#define MB_CTRL_ROLE(ctrl) ((u8) ((ctrl) & MB_CTRL_ROLE_MASK))
#define MB_CTRL_STA_MAC_PRESENT ((u8) (BIT(3)))
#define MB_CTRL_PAIRWISE_CIPHER_SUITE_PRESENT ((u8) (BIT(4)))

enum mb_band_id {
	MB_BAND_ID_WIFI_2_4GHZ = 2, /* 2.4 GHz */
	MB_BAND_ID_WIFI_5GHZ = 4, /* 4.9 and 5 GHz */
	MB_BAND_ID_WIFI_60GHZ = 5, /* 60 GHz */
};

#define MB_CONNECTION_CAPABILITY_AP ((u8) (BIT(0)))
#define MB_CONNECTION_CAPABILITY_PCP ((u8) (BIT(1)))
#define MB_CONNECTION_CAPABILITY_DLS ((u8) (BIT(2)))
#define MB_CONNECTION_CAPABILITY_TDLS ((u8) (BIT(3)))
#define MB_CONNECTION_CAPABILITY_IBSS ((u8) (BIT(4)))

/* IEEE Std 802.11ad-2014 - FST Action field */
enum fst_action {
	FST_ACTION_SETUP_REQUEST = 0,
	FST_ACTION_SETUP_RESPONSE = 1,
	FST_ACTION_TEAR_DOWN = 2,
	FST_ACTION_ACK_REQUEST = 3,
	FST_ACTION_ACK_RESPONSE = 4,
	FST_ACTION_ON_CHANNEL_TUNNEL = 5,
};

/* IEEE Std 802.11ac-2013, Annex C - dot11PHYType */
enum phy_type {
	PHY_TYPE_UNSPECIFIED = 0,
	PHY_TYPE_FHSS = 1,
	PHY_TYPE_DSSS = 2,
	PHY_TYPE_IRBASEBAND = 3,
	PHY_TYPE_OFDM = 4,
	PHY_TYPE_HRDSSS = 5,
	PHY_TYPE_ERP = 6,
	PHY_TYPE_HT = 7,
	PHY_TYPE_DMG = 8,
	PHY_TYPE_VHT = 9,
	PHY_TYPE_S1G = 10,
};

/* IEEE P802.11-REVmc/D5.0, 9.4.2.37 - Neighbor Report element */
/* BSSID Information Field */
#define NEI_REP_BSSID_INFO_AP_NOT_REACH BIT(0)
#define NEI_REP_BSSID_INFO_AP_UNKNOWN_REACH BIT(1)
#define NEI_REP_BSSID_INFO_AP_REACHABLE (BIT(0) | BIT(1))
#define NEI_REP_BSSID_INFO_SECURITY BIT(2)
#define NEI_REP_BSSID_INFO_KEY_SCOPE BIT(3)
#define NEI_REP_BSSID_INFO_SPECTRUM_MGMT BIT(4)
#define NEI_REP_BSSID_INFO_QOS BIT(5)
#define NEI_REP_BSSID_INFO_APSD BIT(6)
#define NEI_REP_BSSID_INFO_RM BIT(7)
#define NEI_REP_BSSID_INFO_DELAYED_BA BIT(8)
#define NEI_REP_BSSID_INFO_IMM_BA BIT(9)
#define NEI_REP_BSSID_INFO_MOBILITY_DOMAIN BIT(10)
#define NEI_REP_BSSID_INFO_HT BIT(11)
#define NEI_REP_BSSID_INFO_VHT BIT(12)
#define NEI_REP_BSSID_INFO_FTM BIT(13)

/*
 * IEEE P802.11-REVmc/D5.0 Table 9-152 - HT/VHT Operation Information
 * subfields.
 * Note: These definitions are not the same as other VHT_CHANWIDTH_*.
 */
enum nr_chan_width {
	NR_CHAN_WIDTH_20 = 0,
	NR_CHAN_WIDTH_40 = 1,
	NR_CHAN_WIDTH_80 = 2,
	NR_CHAN_WIDTH_160 = 3,
	NR_CHAN_WIDTH_80P80 = 4,
};

#endif /* IEEE802_11_DEFS_H */
