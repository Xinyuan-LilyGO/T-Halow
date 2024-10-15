

#define SERIALTX_AH_RXD 4
#define SERIALTX_AH_TXD 5

#define SerialMon Serial
#define SerialTX_AH Serial2

#define BOARD_LED 38        // Running status light
TaskHandle_t led_handle;

void led_task(void *param)
{
    while (1)
    {
        digitalWrite(BOARD_LED, !digitalRead(BOARD_LED));
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void setup(void)
{
    SerialMon.begin(115200);
    SerialTX_AH.begin(115200, SERIAL_8N1, SERIALTX_AH_RXD, SERIALTX_AH_TXD);

    pinMode(BOARD_LED, OUTPUT);

    xTaskCreate(led_task, "led_task", 1024 * 3, NULL, 1, &led_handle);

    delay(1500);
}

void loop(void)
{
    while (SerialTX_AH.available())
    {
        SerialMon.write(SerialTX_AH.read());
    }
    while (SerialMon.available())
    {
        SerialTX_AH.write(SerialMon.read());
    }
}