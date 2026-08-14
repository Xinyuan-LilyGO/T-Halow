<h1 align = "center">🏆 T-Halow 🏆</h1>

<p> 
  <a href="https://platformio.org/"> <img src="./hardware/image/PlatformIO_badge.png" height="20px"> </a>
  <a href="https://www.arduino.cc/en/software"> <img src="./hardware/image/Arduino_badge.png" height="20px"></a>
  <a href=""> <img src="https://img.shields.io/badge/Liiygo-T_Halow-blue" height="20px"></a>
  <a href=""> <img src="https://img.shields.io/badge/language-c++-brightgreen" height="20px"></a>
</p>

<!-- * [切换到中文版](./README_CN.md) -->

T-Halow is WiFi Halow, an optimized Wi-Fi solution for iot devices, which has a longer transmission distance while providing the same transmission power of 2.4GHz and 5GHz. T-Halow is equipped with the TX-AH module, which can operate in the 730M-950MHz band, the module can operate in the channel width of 1/2/4/8MHz, and can provide a physical throughput of 150 Kbps to 32.5Mbps.

# Project
There are two different versions of T-Halow, which differ in the way they are paired;

It is important to confirm the version of T-Halow you have.

| - | TIME | LINK | VIDEO |
| :---: | :---: | :---: | :---: |
| VER1 | V1.0 24-08-23 | [VERSION1](./docs/ver1/readme.md) | |
| VER2 | V1.0 24-04-16 | [VERSION2](./docs/ver2/readme.md) | https://www.youtube.com/watch?v=nM2GE8Imshc |

Version 1 and version 2 of T-Halow use the same [AT commands](./docs/AT_cmd.md).

Regarding the SDK of the TX-AH module, Taixin does not provide detailed API instructions. If you want to compile it yourself, you can use this project. [hgSDK](./SDK/hgSDK-v1.6.4.3-29063-wnb)

# Firmware download

If you need to download the TX AH firmware, you can use the following two methods:

| Download firmware via downloader  |[docs](./docs/Firmware_burn_1.md)|
| -------------------- | --- |
| Download firmware via esp32 flash_download_tool  | [docs](./docs/Firmware_burn_2.md) |

# Official document;
TX-AH module official documentation is in Chinese, if you can speak Chinese, this may help you;

More TX-AH module information can be found on the official website，[download](https://taixin-semi.com/en/products/modules#wifi-halow)

|           Frequency setting description           | [docs](./hardware/TX_AH/泰芯802.11AH%20Frequency%20setting%20description_20231130110312.pdf)                       |
|:-------------------------------------------------:|:------------------------------------------------------------------------------------------------------------------ |
| TX-AH-Rx00P Series module technical specification | [docs](./hardware/TX_AH/泰芯802.11ah TX-AH-Rx00P%20Series%20module%20technical%20specification_20231116174457.pdf) |
|          TX-AH-Rx00P Bridge instructions          | [docs](./hardware/TX_AH//泰芯AH%20Bridge%20instructions_20230908122753.pdf)                                        |
|    AH Module AT instruction development guide     | [docs](./hardware/TX_AH/泰芯AH%20Module%20AT%20instruction%20development%20guide_20230524100503.pdf)               |
|     AH Module development board instructions      | [docs](./hardware/TX_AH/泰芯AH%20Module%20development%20board%20instructions_20230621205234.pdf)                   |
|          AH Module hardware Design Guide          | [docs](./hardware/TX_AH/泰芯AH%20Module%20hardware%20Design%20Guide_20230621170639.pdf)                            |
|            AH Performance test method             | [docs](./hardware/TX_AH/泰芯AH%20Performance%20test%20method_20230908122816.pdf)                                   |
|           AH-RF EMC Certification guide           | [docs](./hardware/TX_AH/泰芯AH-RF EMC%20Certification%20guide_20230720140052.pdf)                                  |

# TX-AH model comparison

|        Module name       |     Front screen distinction     |    Overcertified condition     |                       remark                        |
| :----------------: | :------------: | :----------: | :---------------------------------------------: |
|    TX-AH-R900P     | Lower left P9, lower right P9  | Can pass FCC/CE certification |             Supports 860MHz to 928MHz             |
|   TX-AH-R900PNR    | Lower left P9, lower right NR |  Can pass FCC certification   | Support 902MHz ~ 928MHz, with 915M Saw to improve receiving performance |
| TX-AH-R900PNR-860M | Lower left 86, lower right NR |   Can pass CE certification   | Support 859MHz ~ 894MHz, with 875M Saw to improve reception performance |

remark:
1. The difference between the P series module and the earlier A series module is:

(1) The bottom left screen print of the P series is beginning with P, and the bottom left screen print of the A series is beginning with R;

(2) P series PIN4/5 needs power supply, A series does not;

2. The module does not have a Shield by default. The name of the module with a shield is suffix-s, where S indicates shield.

## :three: Quick Start 🎁

🟢 PlatformIO is recommended because these examples were developed on it. 🟢 

### 1、PlatformIO

1. Install [Visual Studio Code](https://code.visualstudio.com/) and [Python](https://www.python.org/), and clone or download the project;
2. Search for the `PlatformIO` plugin in the `VisualStudioCode` extension and install it;
3. After the installation is complete, you need to restart `VisualStudioCode`
4. After opening this project, PlatformIO will automatically download the required tripartite libraries and dependencies, the first time this process is relatively long, please wait patiently;
5. After all the dependencies are installed, you can open the `platformio.ini` configuration file, uncomment in `example` to select a routine, and then press `ctrl+s` to save the `.ini` configuration file;
6. Click :ballot_box_with_check: under VScode to compile the project, then plug in USB and select COM under VScode;
7. Finally, click the :arrow_right:  button to download the program to Flash;


### 2、Arduino IDE

1. Install [Arduino IDE](https://www.arduino.cc/en/software)

2. Copy all files under `this project/lib/` and paste them into the Arduion library path (generally `C:\Users\YourName\Documents\Arduino\libraries`);

3. Open the Arduion IDE and click `File->Open` in the upper left corner to open an example in `this project/example/xxx/xxx.ino` under this item;

4. Then configure Arduion. After the configuration is completed in the following way, you can click the button in the upper left corner of Arduion to compile and download;

| Arduino IDE Setting                  | Value                             |
| ------------------------------------ | --------------------------------- |
| Board                                | **ESP32S3 Dev Module**            |
| Port                                 | Your port                         |
| USB CDC On Boot                      | Enable                            |
| CPU Frequency                        | 240MHZ(WiFi)                      |
| Core Debug Level                     | None                              |
| USB DFU On Boot                      | Disable                           |
| Erase All Flash Before Sketch Upload | Disable                           |
| Events Run On                        | Core1                             |
| Flash Mode                           | QIO 80MHZ                         |
| Flash Size                           | **16MB(128Mb)**                   |
| Arduino Runs On                      | Core1                             |
| USB Firmware MSC On Boot             | Disable                           |
| Partition Scheme                     | **16M Flash(3M APP/9.9MB FATFS)** |
| PSRAM                                | **OPI PSRAM**                     |
| Upload Mode                          | **UART0/Hardware CDC**            |
| Upload Speed                         | 921600                            |
| USB Mode                             | **CDC and JTAG**                  |
