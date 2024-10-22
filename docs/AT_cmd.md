# AT 命令

Taixin AH module supports AT command working mode, and can send AT command through uart Data setting, data communication.

Note Select the new line mode in the serial port tool, and the AT command is case insensitive.

# Basic networking commands

## `AT+MODE`​

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

## `AT+SSID`​

Set the SSID；AT+SSID=[ssid_char]；ssid_char contains less than 32 characters

example：

```txt
AT+SSID? 				// Inquire
AT+SSID=hgic_ah_test	// Set the SSID to `hgic_ah_test`
```

## `AT+KEYMGMT`​

Set encryption mode；AT+KEYMGMT=[param]；Supports parameter : WPA-PSK/NONE

example :

```txt
AT+KEYMGMT?			// Inquire
AT+KEYMGMT=WPA-PSK	// Enable encryption
AT+KEYMGMT=NONE		// Turn off encryption
```

## `AT+PSK`​

Set encryption password；AT+PSK=[psk_char]；psk_char must be 64 hex characters. If the setting does not meet the length requirements, the previous will be cleared Save the PSK

example：

```txt
AT+PSK?																		// Inquire
AT+PSK=baa58569a9edd7c3a55e446bc658ef76a7173d023d256786832474d737756a82		// Set encryption password
```

## `AT+PAIR`​

Pairing control；AT+PAIR=[0/1]

This command can achieve quick pairing and network configuration when the SSID is not set. When pairing starts:

1. The AP has configured the SSID and password, but the STA has not: During the pairing process, the STA will obtain the AP's SSID and password.

2. Both the AP and the STA have not configured the SSID and password: During the pairing process, the AP will generate a random password for each STA.

A PAIR SUCCESS message will be generated after the pairing is successful, but the pairing will not automatically terminate. The pairing must be stopped by executing `AT+PAIR=0`​.

The connection will be established automatically after the pairing is stopped.

If both the AP and the STA have set the SSID and other parameters, the PAIR does not need to be started. The connection will be established automatically based on the SSID and other parameters.

example：

```txt
AT+PAIR=1 	// Start pairing
AT+PAIR=0 	// Stop pairing
```

## `AT+BSS_BW`​

Set the BSS bandwidth；AT+BSS_BW=[bss_bw]；Supports parameter：1 / 2 / 4 / 8

```txt
AT+BSS_BW?		// Inquire
AT+BSS_BW=1		// Set the bandwidth to 1
AT+BSS_BW=2		// Set the bandwidth to 2
AT+BSS_BW=4		// Set the bandwidth to 4
AT+BSS_BW=8		// Set the bandwidth to 8
```

## `AT+FREQ_RANGE`​

Set the operating frequency range；AT+FREQ_RANGE=[start,end]；

This command is used to set the frequency range for continuous use and specify the start and end center frequency. The AH module automatically calculates the frequency list.

Note：that if `AT+CHAN_LIST`​ is also set, the CHAN_LIST parameter takes precedence

example:

```txt
AT+FREQ_RANGE?				// Inquire
AT+FREQ_RANGE=9080,9240	 	// start freq 908Mhz, end freq 924Mhz
```

## `AT+CHAN_LIST`​

Set the working frequency list；AT+CHAN_LIST=[freq1, freq2, ...]；

This command is used to set the non-continuous frequency list. Supports a maximum of 16 frequency points separated by commas (,)

```txt
AT+CHAN_LIST?					// Inquire
AT+CHAN_LIST=9080, 9160, 9240	// Set three frequency points: 908MHz,916MHz,924Mhz
```

# Status query command

## `AT+RSSI`​

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

## `AT+CONN_STATE`​

View connection status；

example：

```txt
AT+CONN_STATE
```

## `AT+WNBCFG`​

View device parameters；

example：

```txt
AT+WNBCFG
```

## `AT+SCAN_AP`​

Scan for AP information；

This command is executed in STA mode to scan for AP information.

After scanning, query the results with the following BSSLIST command.

example：

```txt
AT+SCAN_AP=2
```

## `AT+BSSLIST`​

Get the list of scanned aps;

After running the scan_ap command, you can use this command to obtain the AP list to be scanned. (The ap can be scanned only after ssid is set.)

example：

```txt
AT+BSSLIST
```

# Advanced networking commands

## `AT+TXPOWER`​

Set the maximum transmit power；AT+TXPOWER=[txpower]；The range of txpower is [6 , 20]

example：

```txt
AT+TXPOWER?		// Inquire
AT+TXPOWER=20	// Set transmit power 20dbm
```

## `AT+ACKTMO`​

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

## `AT+TX_MCS`​

Set the TX MCS；AT+TX_MCS=255；Default value is 255, auto MCS；The value ranges [0, 7]

Parameter description：

Set tx mcs. When the value ranges from 0 to 7 or 1M, 10 indicates that the mcs is fixed. Other values indicate that the mcs is automatically adjusted.

Modified value Power-off Save.

example：

```txt
AT+TX_MCS?		// Inquire
AT+TX_MCS=2 	// The MCS for fixed transmission is 2
```

## `AT+HEART_INT`​

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

## `AT+UNPAIR`​

Set unpair a specified STA；AT+UNPAIR=[mac_addr]；mac_addr is the mac address of the peer；

example：

```txt
AT+MAC_ADDR=?					// View the MAC address of the device
AT+UNPAIR=f6:de:09:75:a3:61		// Unpair
```

# Debugging command

## `AT+LOADDEF`​

factory data reset；

example：

```txt
AT+LOADDEF=1
```

## `AT+SYSDBG`​

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

## `AT+JOINGROUP`​

Adding a multicast network；AT+JOINGROUP=group_addr,AID；

Notice the JOINGROUP command can be configured only after the `AT+MODE=GROUP`​ mode is set.

Parameter description：

* group_addr：Specifies the address of the multicast network to be added
* AID：The AID value of the device in the multicast network ranges from 1 to N (N is the maximum number of STAs supported by the firmware). The AID of each device on the network should be unique.

  * Set valid AID: The WiFi module will periodically send a heartbeat in the multicast network to announce its existence to other WiFi modules
  * Invalid AID: The WiFi module does not send a heartbeat or notify other WiFi modules. **If AID is set to 0 for all devices, there is no limit to the maximum number of STAs supported by the firmware**.

After setting the working mode of the WiFi module to group, you can run this command to add the WiFi module to a multicast network.

After joining a multicast network, the WiFi module will only receive data from that multicast network.

All data communications are communicated at multicast addresses. If the working mode is set to group, but the multicast network is not added, all data communication is transmitted in broadcast mode

example：

```txt
AT+JOINGROUP=11:22:33:44:55:66,3	// group_addr=11:22:33:44:55:66
									// AID=3
```

# Relay station commands

## `AT+R_SSID`​

Set relay station SSID；AT+R_SSID=repeater_ssid；Set the relay to connect to the SSID of the upper-level AP；

Note：Currently only supports the first-level relay

example：

```txt
AT+R_SSID?					// Inquire
AT+R_SSID=repeater_ssid		// Set the relay to connect to the SSID of the upper-level AP
```

## `AT+R_PSK`​

Set the relay encryption password；AT+R_PSK=psk_char；

Parameter description：

The password for the relay to connect to the upper AP. psk_char must be 64 hex characters.

example：

```txt
AT+R_PSK? 		// Inquire
AT+R_PSK=baa58569a9edd7c3a55e446bc658ef76a7173d023d256786832474d737756a82 		//must be 64 hex characters
```

# Roaming related commands

## `AT+ROAM`​

Set the roaming enable；AT+ROAM=0/1；

Roaming only needs to be enabled on the STA side. The SSID of the AP in the roaming network can be set by full word matching or fuzzy matching.

Full word matching: The SSID of all APs is set to the same SSID. The SSID length is not limited, and it can be no more than 32 characters. STAs are also set to this SSID.

Fuzzy matching: The last 3 characters of the SSID of different APs are different. The total length of the SSID must be greater than 8 characters, and it consists of a common string (at the beginning of the SSID string) and a 3-character ID (at the end of the string). For example, if the common string is HUGE_IC_AH, then the SSID of AP1 can be set to HUGE_IC_AH001, the SSID of AP2 can be set to HUGE_IC_AH002, and so on.  
The STA's SSID must be set to be the same as the SSID of one of the APs.

example：

```txt
AT+ROAM?		// Inquire
AT+ROAM=0		// Disable
AT+ROAM=1		// Enable
```

# Hibernation related commands

## `AT+PS_MODE`​

Set STA sleep mode；AT+PS_MODE=0/1/2/3/4；

Parameter description：

* 0:  No sleep mode is set, the effect is the same as mode 3.

* 1: When the module enters sleep, it keeps alive with the server (the module keeps alive with the server itself).

* 2: When the module enters sleep, it keeps alive with the server (the AP keeps alive with the server instead of the module, with the lowest power consumption).

* 3: When the module enters sleep, it only maintains a connection with the AP, and any unicast packet can wake up the module.

* 4: When the module enters sleep, it only keeps alive with the AP, and can only be awakened by the AP input: `AT+WAKEUP`​.

example：

```txt
AT+PS_MODE?
```

# Other Command

## `AT+VERSION=?`

View the firmware version.

## `AT+MAC_ADDR=?`

View the MAC address of the device.

## `AT+TXDATA`

Send data instruction；AT+TXDATA\=[length,txbw,txmcs,priority]；

Parameter description：

* length: the length of the data to be sent [required]

* txbw: specifies the tx bandwidth of the data [optional]

* txmcs: specifies the tx mcs of the data [optional]

* priority: specifies the priority of the data, 0~7 [optional]

This command is used to send data through the serial port when the UART is in non-transparent mode.

Execution steps:

1. First execute the AT+TXDATA command to set the parameters for data transmission.
2. After executing the at+txdata command and it returns OK, data transmission starts. The length of the transmitted data must meet the length specified by the parameter.

The default firmware is 1-to-many mode. In 1-to-many mode, AT+TXDATA cannot send the original data directly. It needs to add 14Byte Ethernet frame header before the original data and then send it. The length setting should also include the Ethernet frame header length.

example：

### Test 1: Simple test

Send the command `at+txdata=24` first, then send the data `111111000000001234567890` after receiving OK.

```txt
at+txdata=24 					// 14 byte Ethernet frame header + 10 byte data
111111000000001234567890		// The actual data sent
```

* 111111: 	Ethernet destination address

* 000000: 	Ethernet source address

* 00:	Ethernet protocol type, Can be filled with 0

* 0123456789:	Data to be sent

Write in hex: 31 31 31 31 31 31 30 30 30 30 30 30 30 30 31 32 33 34 35 36 37 38 39 30

### Test 2: Specify the MAC address of the device to send data

Assumption:

* Destination MAC: 4a:06:59:a5:81:98

* Source address MAC: 4a:06:59:7b:6c:98

* Sent data: 1234567890

```txt
at+txdata=24 		// 14 byte Ethernet frame header + 10 byte data
4A 06 59 A5 81 98 4A 06 59 7B 6C 98 30 30 31 32 33 34 35 36 37 38 39 30		// The actual data sent
```