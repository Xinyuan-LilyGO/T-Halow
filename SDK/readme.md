## T-Halow SDK Description

![alt text](image.png)

The AH-V1.6-SDK package contains three AH module projects.
Each project can be compiled independently.

The AH-V1.6-SDK development environment requires the installation of the CDK environment.
For environment setup, please refer to 《泰芯TXW830x AH-SDK开发指南.pdf》.

The file descriptions are as follows:

| File                             | Description                                       |
| :------------------------------- | :------------------------------------------------ |
| hgSDK-v1.6.4.3-39706-wnb         | -wnb corresponds to the Ethernet interface        |
| hgSDK-v1.6.4.3-39706-wnb-uartp2p | -uartp2p serial port transparent transmission     |
| hgSDK-v1.6.4.5-39706-fmac        | -fmac corresponds to SDIO / UART / USB interfaces |
| 泰芯AH模组AT指令开发指南                   | AT command description                            |
| 泰芯AH网桥使用说明                       | Bridge configuration instructions                 |

`-wnb` is an Ethernet interface project. The main communication method is Ethernet communication, supporting TCP/UDP protocols with a communication speed of 90 Mbit/s.
The default serial port baud rate is 115200, which is used for sending and receiving AT commands and outputting debug information. It also supports a small amount of data transmission via the serial port.

`-uartp2p` is a serial port transparent transmission project. After successful pairing, data can be transmitted directly through the serial port. The transmission rate is affected by the serial port baud rate.
The default serial port baud rate is 115200. The baud rate can be modified by changing the `UART_P2P_BAUDRATE` definition.

Note that:

1. The packet length must be limited to 1500 bytes.

2. The baud rate should not be too high; otherwise, there is a risk of data loss. Generally, 400 kbps is recommended as an upper limit. At 921600, there is a relatively high risk of data loss.

`-fmac` is a communication project based on SDIO/SPI, UART, and USB interfaces. The primary communication methods are SDIO/SPI, UART, and USB. Taking SPI communication as an example, the data rate is approximately 25 Mbit/s.
The default serial port baud rate is 115200, which is used for sending and receiving AT commands and for outputting debug information. It also supports a small amount of data transmission via the serial port.

## T-Halow SDK Firmware Description

| File                                                  | Description                                                                                       |
| :---------------------------------------------------- | :------------------------------------------------------------------------------------------------ |
| huge-ic-ah_v1.6.4.3-39706_wnb_sta_8.bin               | **-wnb firmware**, maximum number of connected STAs is **8**, AT serial port baud rate **115200** |
| huge-ic-ah_v1.6.4.3-39706_wnb_sta_1.bin               | **-wnb firmware**, maximum number of connected STAs is **1**, AT serial port baud rate **115200** |
| huge-ic-ah_v1.6.4.3-39706_wnb_uartp2p_baud_115200.bin | **-uartp2p** serial transparent transmission, baud rate **115200**                                |
| huge-ic-ah_v1.6.4.3-39706_wnb_uartp2p_baud_230400.bin | **-uartp2p** serial transparent transmission, baud rate **230400**                                |
| huge-ic-ah_v1.6.4.3-39706_wnb_uartp2p_baud_460800.bin | **-uartp2p** serial transparent transmission, baud rate **460800**                                |
| huge-ic-ah_v1.6.4.3-39706_wnb_uartp2p_baud_921600.bin | **-uartp2p** serial transparent transmission, baud rate **921600**                                |

## T-Halow Firmware Download

There is no interface on the T-Halow board for flashing firmware to the HaLow module, so the only option is to remove the HaLow module’s flash memory, place it into a programmer to download the firmware, and then reinstall the flash back to its original position after programming is complete.

Reference:

If you need to download the TX AH firmware, you can use the following two methods:

| Download firmware via downloader  |[docs](../docs/Firmware_burn_1.md)|
| -------------------- | --- |
| Download firmware via esp32 flash_download_tool  | [docs](../docs/Firmware_burn_2.md) |

