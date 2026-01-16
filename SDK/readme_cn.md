## T-Halow SDK 说明

![alt text](image.png)

AH-V1.6-SDK 文件里面共包含三个 ah 模块的项目，每个项目可以独立编译；

AH-V1.6-SDK 编程环境需要安装 CDK 环境，环境搭建参考《泰芯TXW830x AH-SDK开发指南.pdf》

文件说明如下；

| 文件                               | 说明                        |
| :------------------------------- | :------------------------ |
| hgSDK-v1.6.4.3-39706-wnb         | -wnb 对应以太网接口              |
| hgSDK-v1.6.4.3-39706-wnb-uartp2p | -uartp2p 串口透传             |
| hgSDK-v1.6.4.5-39706-fmac        | -fmac 对应 sdio uart usb 接口 |
| 泰芯AH模组AT指令开发指南                   | AT 指令说明                   |
| 泰芯AH网桥使用说明                       | 网桥配置说明                    |

`-wnb` 为以太网接口项目，主要通信方式为以太网通信，支持 tcp/upd 协议，通信速率为90mbit/s；默认串口波特率为 115200 用于收发 AT 指令，和输出调试信息，支持少量数据通过串口传输；

`-uartp2p` 为串口透传项目，配对成功后，可以直接通过串口传输数据，传输速率受串口波特率影响；串口默认波特率为 115200，可以更改 UART_P2P_BAUDRATE 定义来更改波特率；需要注意的是：

1. 包长要受限于1500字节。
2. 波特率不能太高，否则会有丢数风险，一般建议400k就不敢更高了，921600是有比较大丢数风险的

`-fmac` 为 sdio/spi、uart、usb 接口通信项目，主要通信方式为sdio/spi、uart、usb，以spi通信为例，通信速率为25mbit/s左右； 默认串口波特率为 115200 用于收发 AT 指令，和输出调试信息，支持少量数据通过串口传输；

## T-Halow SDK 固件说明

| 文件                                                    | 说明                                |
| :---------------------------------------------------- | :-------------------------------- |
| huge-ic-ah_v1.6.4.3-39706_wnb_sta_8.bin               | -wnb 固件，连接sta最大数量为8，at串口波特率115200 |
| huge-ic-ah_v1.6.4.3-39706_wnb_sta_1.bin               | -wnb 固件，连接sta最大数量为1，at串口波特率115200 |
| huge-ic-ah_v1.6.4.3-39706_wnb_uartp2p_baud_115200.bin | -uartp2p 串口透传，波特率为 115200         |
| huge-ic-ah_v1.6.4.3-39706_wnb_uartp2p_baud_230400.bin | -uartp2p 串口透传，波特率为 230400         |
| huge-ic-ah_v1.6.4.3-39706_wnb_uartp2p_baud_460800.bin | -uartp2p 串口透传，波特率为 460800         |
| huge-ic-ah_v1.6.4.3-39706_wnb_uartp2p_baud_921600.bin | -uartp2p 串口透传，波特率为 921600         |

## T-Halow 固件下载

T-Halow 上面没有为 Halow 模块烧录固件的接口，所以只能将 Halow 模块的flash 去下，放入烧录器中下载程序，烧录完程序后再将 flash 放回原来的位置；

参考：

If you need to download the TX AH firmware, you can use the following two methods:

| Download firmware via downloader  |[docs](../docs/Firmware_burn_1.md)|
| -------------------- | --- |
| Download firmware via esp32 flash_download_tool  | [docs](../docs/Firmware_burn_2.md) |

