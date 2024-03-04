
#include <Arduino.h>
#include "utilities.h"
#include "esp_camera.h"
#include <WiFi.h>
#include <stdio.h>
#include <string.h>

const char *ssid = "xinyuandianzi";
const char *password = "AA15994823428";

void startCameraServer();
camera_config_t config;
void camera_init(void)
{
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = CAMERA_PIN_Y2;
    config.pin_d1 = CAMERA_PIN_Y3;
    config.pin_d2 = CAMERA_PIN_Y4;
    config.pin_d3 = CAMERA_PIN_Y5;
    config.pin_d4 = CAMERA_PIN_Y6;
    config.pin_d5 = CAMERA_PIN_Y7;
    config.pin_d6 = CAMERA_PIN_Y8;
    config.pin_d7 = CAMERA_PIN_Y9;
    config.pin_xclk = CAMERA_PIN_XCLK;
    config.pin_pclk = CAMERA_PIN_PCLK;
    config.pin_vsync = CAMERA_PIN_VSYNC;
    config.pin_href = CAMERA_PIN_HREF;
    config.pin_sccb_sda = CAMERA_PIN_SIOD;
    config.pin_sccb_scl = CAMERA_PIN_SIOC;
    config.pin_pwdn = CAMERA_PIN_PWDN;
    config.pin_reset = CAMERA_PIN_RESET;
    config.xclk_freq_hz = XCLK_FREQ_HZ;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_96X96;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    config.fb_location = CAMERA_FB_IN_DRAM;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;

    if (config.pixel_format == PIXFORMAT_JPEG)
    {
        if (psramFound())
        {
            config.jpeg_quality = 10;
            config.fb_count = 2;
            config.grab_mode = CAMERA_GRAB_LATEST;
        }
        else
        {
            // Limit the frame size when PSRAM is not available
            config.frame_size = FRAMESIZE_SVGA;
            config.fb_location = CAMERA_FB_IN_DRAM;
        }
    }

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }

    sensor_t *s = esp_camera_sensor_get();
    if (s)
    {
        Serial.print("camera id:");
        Serial.println(s->id.PID);
        camera_sensor_info_t *sinfo = esp_camera_sensor_get_info(&(s->id));
        if (sinfo)
        {
            Serial.print("camera model:");
            Serial.println(sinfo->name);
        }
        if (s->id.PID == GC0308_PID)
        {
            s->set_vflip(s, 0);
            s->set_hmirror(s, 0);
        }
    }

    // Wifi
    WiFi.begin(ssid, password);
    WiFi.setSleep(false);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    startCameraServer();

    log_i("Camera Ready! Use 'http://");
    Serial.print(WiFi.localIP());
    Serial.println("' to connect");
}



#define AH_Rx00P_ALL_CMD "A+"
#define AH_Rx00P_SYSDBG "AT+SYSDBG=LMAC,0";

#define AH_Rx00P_RESPONE_OK    1
#define AH_Rx00P_RESPONE_ERROR 2


String str_at = "";
String str_dbg= "";

uint8_t target_addr[6] = {0xba, 0x04, 0x59, 0xa0, 0x7a, 0x68};
uint8_t source_addr[6] = {0xba, 0x04, 0x59, 0x8c, 0x94, 0x68};
uint8_t protocol_type[2] = {0xff, 0xff};

char protocol_head[14]={
    0xba, 0x04, 0x59, 0xa0, 0x7a, 0x68,
    0xba, 0x04, 0x59, 0x8c, 0x94, 0x68, 
    0xff, 0xff
};

char protocol_head_1[14] = {
    0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 
    0x30, 0x30
};

char send_buf[128];

void sendValue(const char *buf, uint32_t len)
{
    String cmd = "+TXDATA=";
    cmd.concat(len+14);
    SerialMon.println(cmd);
    sendAT(cmd);
    int ret = waitResponse();
    if(ret == AH_Rx00P_RESPONE_OK){
        SerialAT.write((const char*)protocol_head_1, 14);
        SerialAT.write((const char*)buf, len);

        // memcpy((void*)send_buf, (const void*)protocol_head_1, 14);
        // memcpy((void*)(send_buf+14), (const void*)buf, len);
        // SerialAT.write((const char *)send_buf, 14+len);
        // SerialMon.write((const char *)send_buf, 14+len);
        // for(int i = 0; i < 24; i++){
        //     SerialMon.print(send_buf[i]);
        // }

        ret = waitResponse();
        if(ret == AH_Rx00P_RESPONE_OK){
            SerialMon.println("AT+TXDATA send value OK!");
        }else if(ret == AH_Rx00P_RESPONE_ERROR){
            SerialMon.println("AT+TXDATA send value ERROR!");
        }
    } else if(ret == AH_Rx00P_RESPONE_ERROR) {
        SerialMon.println("AT+TXDATA send value error!");
    }
}

void sendAT(String s)
{
    s = "AT" + s;
    SerialAT.write(s.c_str());
}

int8_t waitResponse(uint32_t timeouts, String& data, const char *r1 = "OK", const char *r2 = "ERROR")
{
    int index = 0;
    uint32_t start_tick = millis();
    do{
        while (SerialAT.available() > 0) {
            int a = SerialAT.read();
            if(a < 0) continue; // Skip 0x00 bytes, just in case

            data.reserve(1024);
            data += static_cast<char>(a);
            
            if(data.endsWith(r1)){
                index = 1;
                goto finish;
            } else if(data.endsWith(r2)){
                index = 2;
                goto finish;
            }
        }
    }while(millis() - start_tick < timeouts);
    
finish:
    return index;
}   

int8_t waitResponse(uint32_t timeouts)
{
    String data;
    return waitResponse(timeouts, data);
}

int8_t waitResponse(void)
{
    return waitResponse(1000);
}


String inStr = "";
String atStr = "";
void GetSerialCmd()
{
        while (Serial.available()) {
            inStr += (char)Serial.read();
        }
        while (SerialAT.available()) {
            atStr += (char)SerialAT.read();
        }

    if(atStr != ""){
        SerialMon.println(atStr);
        atStr = "";
    }
    
    if (inStr != "") {
        // Serial.print("input: ");
        // Serial.println(inStr);

        switch ((byte)inStr[0])
        {
        case '1':{
            sendAT("+MODE");
            if(waitResponse() == 1) Serial.println("AT+MODE SUCCEED");
            else Serial.println("AT+MODE FAILD");
            break;
        }
        case '2':{
            String data;
            sendAT("+CONN_STATE");
            int8_t r = waitResponse(1000, data, "+CONNECTED", "+DISCONNECT");
            Serial.println("+CONN_STATE" + data);
            break;
        }
        case '3':{
            String data;
            sendAT("+MAC_ADDR=?");
            int8_t r = waitResponse(100, data);
            Serial.println(data);
            break;
        }
        case '4':{
            const char *buf = inStr.c_str();
            int len = strlen(buf);
            sendValue(buf, len);
            inStr = "";
            break;
        }
        default:
            break;
        }
    }
}


void AH_RX00P_init(void)
{
    sendAT("+SYSDBG=LMAC,0");
    if(waitResponse() == 1) SerialMon.println("AT+SYSDBG SUCCEED");
    else SerialMon.println("AT+SYSDBG ERROR");

    sendAT("+BSS_BW=8");
    if(waitResponse() == 1) SerialMon.println("AT+BSS_BW SUCCEED");
    else SerialMon.println("AT+BSS_BW FAILD");
}

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    SerialAT.begin(115200, SERIAL_8N1, SERIAL_AT_TXD, SERIAL_AT_RXD);

    int start_delay = 2;
    while (start_delay)
    {
        Serial.print(start_delay);
        delay(1000);
        start_delay--;
    }

    AH_RX00P_init();
}

void loop()
{
    GetSerialCmd();

    // while (SerialAT.available()) {
    //     str_at += SerialAT.read();
    // }
    // while (Serial.available()) {
    //     str_dbg += SerialMon.read();
    // }

    // while (SerialAT.available()) {
    //     Serial.write(SerialAT.read());
    // }
    // while (Serial.available()) {
    //     SerialAT.write(Serial.read());
    // }
}
