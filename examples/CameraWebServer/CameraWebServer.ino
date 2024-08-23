
#include <Arduino.h>
#include "utilities.h"
#include "esp_camera.h"
#include <WiFi.h>
#include <stdio.h>
#include <string.h>

const char *ssid = "dgx_admin";
const char *password = "q63=380O";

void startCameraServer();
void setupLedFlash(int pin);

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
    // config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
    config.frame_size = FRAMESIZE_240X240;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    config.fb_location = CAMERA_FB_IN_DRAM;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;

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
        if (s->id.PID == OV5640_PID)
        {
            s->set_vflip(s, 1);
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

void setup()
{
    Serial.begin(115200);

    int start_delay = 2;
    while (start_delay)
    {
        Serial.print(start_delay);
        delay(1000);
        start_delay--;
    }

    camera_init();
}

void loop()
{
    delay(100000);
}
