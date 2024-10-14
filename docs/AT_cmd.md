Taixin AH module supports AT command working mode, and can send AT command through uart Data setting, data communication.

Note Select the new line mode in the serial port tool, and the AT command is case insensitive.

# Basic networking commands

## `AT+MODE`

Set the working mode；AT+MODE=[param]；Supports parameter : ap / sta / group / apsta

example：

```txt
AT+MODE?		// Inquire
AT+MODE=AP      // AP mode
AT+MODE=STA  	// STA mode 
AT+MODE=GROUP	// Multicast/broadcast mode, see description of `JOINGROUP`
AT+MODE=APSTA	// In trunk mode, the device in trunk mode connects to the 
				// upper-level AP as a sta and provides connection services 
				// for other STAs as an ap. Use `at+r_ssid` and `at+r_psk` to set 
				// connection parameters for the upper AP.
```

## `AT+SSID`

Set the SSID；AT+SSID=[ssid_char]；ssid_char contains less than 32 characters

example：

```txt
AT+SSID? 				// Inquire
AT+SSID=hgic_ah_test	// Set the SSID to `hgic_ah_test`
```

## `AT+KEYMGMT`

Set encryption mode；AT+KEYMGMT=[param]；Supports parameter : WPA-PSK/NONE

example :

```txt
AT+KEYMGMT?			// Inquire
AT+KEYMGMT=WPA-PSK	// Enable encryption
AT+KEYMGMT=NONE		// Turn off encryption
```

## `AT+PSK`

Set encryption password；AT+PSK=[psk_char]；psk_char must be 64 hex characters. If the setting does not meet the length requirements, the previous will be cleared Save the PSK

example：

```txt
AT+PSK?																		// Inquire
AT+PSK=baa58569a9edd7c3a55e446bc658ef76a7173d023d256786832474d737756a82		// Set encryption password
```

## `AT+PAIR`

Pairing control；AT+PAIR=[0/1]

This command can achieve quick pairing and network configuration when the SSID is not set. When pairing starts:

1. The AP has configured the SSID and password, but the STA has not: During the pairing process, the STA will obtain the AP's SSID and password.

2. Both the AP and the STA have not configured the SSID and password: During the pairing process, the AP will generate a random password for each STA.

A PAIR SUCCESS message will be generated after the pairing is successful, but the pairing will not automatically terminate. The pairing must be stopped by executing `AT+PAIR=0`.

The connection will be established automatically after the pairing is stopped.

If both the AP and the STA have set the SSID and other parameters, the PAIR does not need to be started. The connection will be established automatically based on the SSID and other parameters.

example：

```txt
AT+PAIR=1 	// Start pairing
AT+PAIR=0 	// Stop pairing
```

## `AT+BSS_BW`

Set the BSS bandwidth；AT+BSS_BW=[bss_bw]；Supports parameter：1 / 2 / 4 / 8

```txt
AT+BSS_BW?		// Inquire
AT+BSS_BW=1		// Set the bandwidth to 1
AT+BSS_BW=2		// Set the bandwidth to 2
AT+BSS_BW=4		// Set the bandwidth to 4
AT+BSS_BW=8		// Set the bandwidth to 8
```

## `AT+FREQ_RANGE`

Set the operating frequency range；AT+FREQ_RANGE=[start,end]；

This command is used to set the frequency range for continuous use and specify the start and end center frequency. The AH module automatically calculates the frequency list.

Note：that if `AT+CHAN_LIST` is also set, the CHAN_LIST parameter takes precedence

example:

```txt
AT+FREQ_RANGE?				// Inquire
AT+FREQ_RANGE=9080,9240	 	// start freq 908Mhz, end freq 924Mhz
```

## `AT+CHAN_LIST`

Set the working frequency list；AT+CHAN_LIST=[freq1, freq2, ...]；

This command is used to set the non-continuous frequency list. Supports a maximum of 16 frequency points separated by commas (,)

```txt
AT+CHAN_LIST?					// Inquire
AT+CHAN_LIST=9080, 9160, 9240	// Set three frequency points: 908MHz,916MHz,924Mhz
```

# Status query command

## `AT+RSSI`

Check the device signal quality RSSI；AT+RSSI=[index/mac_addr]

Parameter description：

* index：Specify the device index to be queried, starting from 1
* mac_addr：Specify the mac address of the device to be queried

example：

```txt
AT+RSSI?  					// Query the rssi of the first device
AT+RSSI=1					// Query the rssi of the first device
AT+RSSI=f4:de:09:68:6c:20	// Query the RSSI by MAC address
```

## `AT+CONN_STATE`

View connection status；

example：

```txt
AT+CONN_STATE
```

## `AT+WNBCFG`

View device parameters；

example：

```txt
AT+WNBCFG
```

## `AT+SCAN_AP`

Scan for AP information；

This command is executed in STA mode to scan for AP information.

After scanning, query the results with the following BSSLIST command.

example：

```txt
AT+SCAN_AP=2
```

## `AT+BSSLIST`

Get the list of scanned aps;

After running the scan_ap command, you can use this command to obtain the AP list to be scanned. (The ap can be scanned only after ssid is set.)

example：

```txt
AT+BSSLIST
```

# Advanced networking commands

## `AT+TXPOWER`

Set the maximum transmit power；AT+TXPOWER=[txpower]；The range of txpower is [6 , 20]

example：

```txt
AT+TXPOWER?		// Inquire
AT+TXPOWER=20	// Set transmit power 20dbm
```

## `AT+ACKTMO`

Set the ACK TIMEOUT period；AT+ACKTMO=0；Default value. No additional ACK timeout period is added

Parameter description：

Set the WiFi protocol parameter ack timeout value of the AH module. The unit is microsecond. The default value is 0.

You need to set this parameter only when the communication exceeds 1km.

The formula is 10* (distance in kilometers -1), for example 2km set acktmo=10.

Modified value Power-off Save.

example：

```txt
AT+ACKTMO?		// Inquire
AT+ACKTMO=10	// Increase the ACK packet timeout period by 10us
```

## `AT+TX_MCS`

Set the TX MCS；AT+TX_MCS=255；Default value is 255, auto MCS；The value ranges [0, 7]

Parameter description：

Set tx mcs. When the value ranges from 0 to 7 or 1M, 10 indicates that the mcs is fixed. Other values indicate that the mcs is automatically adjusted.

Modified value Power-off Save.

example：

```txt
AT+TX_MCS?		// Inquire
AT+TX_MCS=2 	// The MCS for fixed transmission is 2
```

## `AT+HEART_INT`

Set the heartbeat packet interval；AT+HEART_INT=500；Default value is 500；

Parameter description：

Set the heartbeat packet interval (unit: mS) to 500. The larger the number of STAs, the larger the recommended heartbeat packet interval. The approximate length of heartbeat packets is STA_count x 50

V1.6.2 As long as the AP heartbeat packet interval can be set, the AP will automatically synchronize to the STA, this command is invalid for the STA

Modified value Power-off Save.

example：

```txt
AT+HEART_INT?			// Inquire
AT+HEART_INT=2000		// Set the heartbeat packet interval to 2S
```

## `AT+UNPAIR`

Set unpair a specified STA；AT+UNPAIR=[mac_addr]；mac_addr is the mac address of the peer；

example：

```txt
AT+MAC_ADDR=?					// View the MAC address of the device
AT+UNPAIR=f6:de:09:75:a3:61		// Unpair
```

# Debugging command

## `AT+LOADDEF`

factory data reset；

example：

```txt
AT+LOADDEF=1
```

## `AT+SYSDBG`

Set print debugging information；AT+SYSDBG=XXX,VALE；

Parameter description：

* XXX：Optional value LMAC / WNB

  * LMAC：Air interface statistics
  * WNB：Network layer statistics
* VALE：Optional value 0 / 1

  * 0：Close corresponding print
  * 1：Opencorresponding print

example：

```txt
AT+SYSDBG=LMAC,0	// Disable LMAC printing
```

# Multicast related commands
 
 0. AT+ACS_START= 
 1. AT+ACK_TO= 
 2. AT+ADC_DUMP= 
 3. AT+AP_SLEEP_MODE= 
 4. AT+ANT_DUAL= 
 5. AT+ANT_CTRL= 
 6. AT+ANT_AUTO= 
 7. AT+ANT_DEF= 
 8. AT+BGRSSI_MARGIN= 
 9. AT+BGRSSI_MAX= 
10. AT+BGRSSI_SPUR= 
11. AT+BSS_BW= 
12. AT+BUS_WT= 
13. AT+CCA_OBSV= 
14. AT+CCA_CE= 
15. AT+CCMP_SUPPORT= 
16. AT+CHAN_SCAN= 
17. AT+CS_CNT= 
18. AT+CS_EN= 
19. AT+CS_NUM= 
20. AT+CS_PERIOD= 
21. AT+CS_TH= 
22. AT+CTS_DUP= 
23. AT+EDCA_AIFS= 
24. AT+EDCA_CW= 
25. AT+EDCA_TXOP= 
26. AT+EVM_MARGIN= 
27. AT+FREQ_LIST= 
28. AT+FT_ATT= 
29. AT+LMAC_DBGSEL= 
30. AT+LO_FREQ= 
31. AT+LOADDEF= 
32. AT+MAC_ADDR= 
33. AT+MCAST_DUP= 
34. AT+MCAST_REORDER= 
35. AT+MCAST_BW= 
36. AT+MCAST_MCS= 
37. AT+MCAST_RTS= 
38. AT+NOR_RD= 
39. AT+OBSS_CCA_DIFF= 
40. AT+OBSS_EDCA= 
41. AT+OBSS_NAV_DIFF= 
42. AT+OBSS_SWITCH= 
43. AT+OBSS_TH= 
44. AT+OBSS_PER= 
45. AT+PCF_EN= 
46. AT+PCF_PERCENT= 
47. AT+PCF_PERIOD= 
48. AT+PHY_RESET= 
49. AT+PRI_CHAN= 
50. AT+PRINT_PERIOD= 
51. AT+QA_ATT= 
52. AT+QA_CFG= 
53. AT+QA_RESULTS= 
54. AT+QA_RXTHD= 
55. AT+QA_START= 
56. AT+QA_TXTHD= 
57. AT+RC_NEW= 
58. AT+REG_RD= 
59. AT+REG_WT= 
60. AT+RF_RESET= 
61. AT+RTS_DUP= 
62. AT+RX_AGC= 
63. AT+RX_ERR= 
64. AT+RX_EVM= 
65. AT+RX_PKTS= 
66. AT+RX_REORDER= 
67. AT+RX_RSSI= 
68. AT+SET_AGC= 
69. AT+SET_AGC_TH= 
70. AT+SET_BGRSSI= 
71. AT+SET_BGRSSI_AVG= 
72. AT+SET_RTS= 
73. AT+SET_VDD13= 
74. AT+SHORT_GI= 
75. AT+SHORT_TH= 
76. AT+SLEEP_EN= 
77. AT+T_SENSOR= 
78. AT+TEST_START= 
79. AT+TX_AGG_AUTO= 
80. AT+TX_ATTN= 
81. AT+TX_BW= 
82. AT+TX_BW_DYNAMIC= 
83. AT+TX_CNT_MAX= 
84. AT+TX_CONT= 
85. AT+TX_DELAY= 
86. AT+TX_DST_ADDR= 
87. AT+TX_FAIL= 
88. AT+TX_FC= 
89. AT+TX_FLAGS= 
90. AT+TX_LEN= 
91. AT+TX_MAX_AGG= 
92. AT+TX_MAX_SYMS= 
93. AT+TX_MCS= 
94. AT+TX_MCS_MAX= 
95. AT+TX_MCS_MIN= 
96. AT+TX_ORDERED= 
97. AT+TX_PHA_AMP= 
98. AT+TX_PKTS= 
99. AT+TX_PWR_AUTO= 
100. AT+TX_PWR_MAX= 
101. AT+TX_PWR_SUPER= 
102. AT+TX_PWR_SUPER_TH= 
103. AT+TX_RATE_FIXED= 
104. AT+TX_START= 
105. AT+TX_STEP= 
106. AT+TX_TRIG= 
107. AT+TX_TYPE= 
108. AT+TXOP_EN= 
109. AT+WAKE_EN= 
110. AT+XO_CS= 
111. AT+XO_CS_AUTO= 
112. AT+LO_TABLE= 
113. AT+PS_CHECK= 
114. AT+RADIO_ONOFF= 
115. AT+STA_INFO= 
116. AT+STA_PSK= 