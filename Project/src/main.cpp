#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include "SPIFFS.h"
#include "env.h"

#include "SHTC3Sensor.h"
#include "TelegramNotifier.h"
#include "DataLogger.h"
#include "AlertEngine.h"
#include "ClimateStation.h"

#define BUTTON_PIN 4
#define MAX_READINGS 288

float tempHistory[MAX_READINGS];
float humHistory[MAX_READINGS];
int historyIndex = 0;
bool displayOn = true;

unsigned long lastSensorRead = 0;
unsigned long lastHistorySave = 0;
const unsigned long sensorInterval = 2000;
const unsigned long historyInterval = 300000;

SHTC3Sensor sensor;
TelegramNotifier notifier(SECRET_BOT_TOKEN, SECRET_CHAT_ID);
DataLogger logger;
AlertEngine engine;
ClimateStation station(sensor, notifier, logger, engine);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void saveHistory()
{
    File f = SPIFFS.open("/history.bin", FILE_WRITE);
    if (!f) return;
    f.write((const uint8_t *)tempHistory, sizeof(tempHistory));
    f.write((const uint8_t *)humHistory, sizeof(humHistory));
    f.close();
}

void loadHistory()
{
    if (!SPIFFS.exists("/history.bin")) return;
    File f = SPIFFS.open("/history.bin", FILE_READ);
    if (!f) return;
    f.read((uint8_t *)tempHistory, sizeof(tempHistory));
    f.read((uint8_t *)humHistory, sizeof(humHistory));
    f.close();
}

void setup()
{
    Serial.begin(115200);
    Wire.begin(21, 22);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();

    if (!sensor.begin())
    {
        lcd.print("Sensor Error!");
        while (1) delay(100);
    }

    if (!SPIFFS.begin(true))
        Serial.println("SPIFFS mount failed");
    else
        loadHistory();

    engine.setThresholds(18.0, 25.0);

    WiFi.begin(SECRET_SSID, SECRET_PASS);
    lcd.clear();
    lcd.print("Connecting WiFi");
    while (WiFi.status() != WL_CONNECTED)
        delay(500);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connected!");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
    delay(3000);
    lcd.clear();
}

void loop()
{
    if (digitalRead(BUTTON_PIN) == LOW)
    {
        delay(50);
        displayOn = !displayOn;
        if (displayOn)
        {
            lcd.backlight();
            lcd.display();
        }
        else
        {
            lcd.noBacklight();
            lcd.noDisplay();
        }
        while (digitalRead(BUTTON_PIN) == LOW) delay(10);
        delay(50);
    }

    if (millis() - lastSensorRead > sensorInterval)
    {
        lastSensorRead = millis();
        sensor.read();

        station.update();

        if (displayOn)
        {
            lcd.setCursor(0, 0);
            lcd.print("Temp: ");
            lcd.print(sensor.readTemperature());
            lcd.print(" C   ");
            lcd.setCursor(0, 1);
            lcd.print("Hum: ");
            lcd.print(sensor.readHumidity());
            lcd.print(" %   ");
        }
    }

    if (millis() - lastHistorySave > historyInterval)
    {
        lastHistorySave = millis();
        tempHistory[historyIndex] = sensor.readTemperature();
        humHistory[historyIndex] = sensor.readHumidity();
        historyIndex = (historyIndex + 1) % MAX_READINGS;
        saveHistory();
    }
}
