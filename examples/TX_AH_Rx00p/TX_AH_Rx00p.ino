
#include <Arduino.h>
#include "utilities.h"
#include <stdio.h>
#include <string.h>

#include "FS.h"
#include "SD.h"
#include "SPI.h"


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


char sendTestBuf[] =    "The above, if you register, allows you down the bottom of "
                        "that page to download hgSDK-v1.6.3.6-25403-IoT-NDEV which is"
                        " the SDK (source code) for this module. Don't get too excited,"
                        " though - the \"RF\" side of things is inside a binary .a blob"
                        " (libtxw4002a.a) which is linked at linking time. The header "
                        "for the RF bits is \"libwnb.h\"."
                        "The above, if you register, allows you down the bottom of "
                        "that page to download hgSDK-v1.6.3.6-25403-IoT-NDEV which is"
                        " the SDK (source code) for this module. Don't get too excited,"
                        " though - the \"RF\" side of things is inside a binary .a blob"
                        " (libtxw4002a.a) which is linked at linking time. The header "
                        "for the RF bits is \"libwnb.h\"."
                        "The above, if you register, allows you down the bottom of "
                        "that page to download hgSDK-v1.6.3.6-25403-IoT-NDEV which is"
                        " the SDK (source code) for this module. Don't get too excited,"
                        " though - the \"RF\" side of things is inside a binary .a blob"
                        " (libtxw4002a.a) which is linked at linking time. The header "
                        "for the RF bits is \"libwnb.h\".";
void sendTest(const char *buf, uint32_t len)
{
    String cmd = "+TXDATA=";
    cmd.concat(len+14);
    SerialMon.println(cmd);
    sendAT(cmd);
    int ret = waitResponse();
    if(ret == AH_Rx00P_RESPONE_OK){
        SerialAT.write((const char*)protocol_head_1, 14);
        SerialAT.write((const char*)buf, len);
    }else if(ret == AH_Rx00P_RESPONE_ERROR) {
        SerialMon.println("AT+TXDATA send value error!");
    }
}

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
            // sendValue(buf, len);
            sendTest(sendTestBuf, strlen(sendTestBuf));
            break;
        }
        default:
            break;
        }
        inStr = "";
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

uint32_t last_tick = 0;
bool led_flag = 0;

void loop()
{
    // GetSerialCmd();

    // while (SerialAT.available()) {
    //     str_at += SerialAT.read();
    // }
    // while (Serial.available()) {
    //     str_dbg += SerialMon.read();
    // }
    if (millis() - last_tick > 1000)
    {
        last_tick = millis();
        digitalWrite(BOARD_LED, led_flag);
        led_flag = !led_flag;
    }


    while (SerialAT.available()) {
        Serial.write(SerialAT.read());
    }
    while (Serial.available()) {
        SerialAT.write(Serial.read());
    }
    delay(1);
}
