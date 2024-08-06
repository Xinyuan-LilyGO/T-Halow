
<h1 align = "center">🏆 T-Halow 🏆</h1>

<p> 
  <a href="https://platformio.org/"> <img src="./hardware/image/PlatformIO_badge.png" height="20px"> </a>
  <a href="https://www.arduino.cc/en/software"> <img src="./hardware/image/Arduino_badge.png" height="20px"></a>
  <a href=""> <img src="https://img.shields.io/badge/Liiygo-T_Halow-blue" height="20px"></a>
  <a href=""> <img src="https://img.shields.io/badge/language-c++-brightgreen" height="20px"></a>
</p>

* [Switch to English](./README.md)

❗❗❗ 更多 TX-AH 模块资料可参考官网，[资料下载地址](https://www.taixin-semi.com/Product?prouctSubClass=33)；❗❗❗

T-Halow 是作为物联网设备的优化 Wi-Fi 解决方案 WiFi Halow，在提供 2.4GHz、5GHz 相同的发射功率下有着更远的传输距离。T-Halow 搭载 TX-AH 模组，该模组可以工作在 730M-950MHz 频段，模组可工作的信道宽度为 1/2/4/8MHz，可提供 150 Kbps 到 32.5Mbps 的物理吞吐量。

T-Halow 的两种工作模式：

![alt text](./hardware/image/image.png)

固件烧录：
~~~
MODE1：通过 ESP32  向 TX-AH 发送 AT 指令控制
    TX-AH：下载 huge-ic-ah_v1.6.3.5-25403_2023.10.20_TAIXIN-usb.bin
    ESP32：下载 AP 或 STA

MODE2：通过 micro-USB 发送 AT 指令控制
    TX-AH：下载 huge-ic-ah_v1.6.3.3-26347_2023.11.29_TAIXIN-WNB.bin
    ESP32：不用下载固件
~~~

![alt text](./hardware/image/image-1.png)

## 1、TX-AH 模块固件下载

1. 通过下载器下载固件，[点击](./docs/Firmware_burn_1.md)

2. 通过esp32下载固件, [click](./docs/Firmware_burn_1.md)

## 2、TX-AH 型号对比

|        模组名称        |     正面丝印区分     |    过认证情况     |                       备注                        |
| :----------------: | :------------: | :----------: | :---------------------------------------------: |
|    TX-AH-R900P     | 左下角 P9，右下角 P9  | 可过 FCC/CE 认证 |             支持 860MHz ~  <br>928MHz             |
|   TX-AH-R900PNR    | 左下角 P9， 右下角 NR |  可过 FCC 认证   | 支持 902MHz ~ <br>928MHz， 带 915M Saw  <br>改善接收性能 |
| TX-AH-R900PNR-860M | 左下角 86， 右下角 NR |   可过 CE 认证   | 支持 859MHz ~  <br>894MHz， 带 875M Saw  <br>改善接收性能 |

备注：
1. P 系列模组与早期的 A 系列模组的区别是：

    （1） P 系列的左下角丝印是 P 开头， A 系列的左下角丝印是 R 开头；

    （2） P 系列的 PIN4/5 需要供电， A 系列不需要；

2. 模组默认不带屏蔽罩， 带屏蔽罩在上述模组名称带后缀-S，S 表示（Shield，屏蔽罩）。

## 3、TX-AH 配对文档

对两块泰芯 TX-AH-Rx00P 进行配对时，需要按照一下步骤：

1. 检查模组右下角的丝印，7P 表示 700M、868 表示 868M、9P 表示 900M，只有发射频率相同的模组才能配备成功；
2. 假设使用两块下载了开发板 USB 固件 7P 的模组，把两块模组接入到串口，使用 AT+MODE=ap 指令将一台设备设置为 ap 模式，使用 AT+mode=sta 指令将另一台设备设置为 sta 模式
3. 配对时，需要 AP 设备和 STA 设备同时使用 AT+PAIR=1 指令，配对成功后依次使用 AT+PAIR=0 指令停止配对
4. 注意：USB 固件的打印串口时 A10/A11，其他固件的打印串口是 A12/A13


