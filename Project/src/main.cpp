#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
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
unsigned long lastTelegram = 0;
unsigned long lastBotCheck = 0;

const unsigned long sensorInterval = 2000;
const unsigned long historyInterval = 300000;
const unsigned long telegramInterval = 900000;
const unsigned long botCheckInterval = 1000;

SHTC3Sensor sensor;
TelegramNotifier notifier(SECRET_BOT_TOKEN, SECRET_CHAT_ID);
DataLogger logger;
AlertEngine engine;
ClimateStation station(sensor, notifier, logger, engine);

LiquidCrystal_I2C lcd(0x27, 16, 2);
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://code.highcharts.com/highcharts.js"></script>
  <title>Climate Dashboard</title>
  <style>
    body{font-family:Arial;text-align:center;background:#f4f4f4;margin:0;padding:20px;}
    .chart{height:300px;width:95%;max-width:800px;margin:20px auto;background:white;border-radius:8px;padding:10px;box-shadow:0 4px 6px rgba(0,0,0,0.1);}
  </style>
</head><body>
  <h2>24-Hour Climate Trend</h2>
  <div id="t" class="chart"></div><div id="h" class="chart"></div>
<script>
var chartT = new Highcharts.Chart({chart:{renderTo:'t',type:'line'},title:{text:'Temperature (24h)'},xAxis:{type:'datetime'},yAxis:{title:{text:'Celsius'}},series:[{name:'Temp',data:[],color:'#ff4444'}],credits:{enabled:false}});
var chartH = new Highcharts.Chart({chart:{renderTo:'h',type:'line'},title:{text:'Humidity (24h)'},xAxis:{type:'datetime'},yAxis:{title:{text:'%'}},series:[{name:'Hum',data:[],color:'#4444ff'}],credits:{enabled:false}});

fetch('/history').then(r=>r.json()).then(data=>{
  const now = new Date().getTime();
  const interval = 5 * 60 * 1000;
  data.temp.forEach((v,i)=>{if(v>0) chartT.series[0].addPoint([now-(data.temp.length-i)*interval,v],false);});
  data.hum.forEach((v,i)=>{if(v>0) chartH.series[0].addPoint([now-(data.hum.length-i)*interval,v],false);});
  chartT.redraw(); chartH.redraw();
});

setInterval(function(){
  fetch('/temperature').then(r=>r.text()).then(v=>{chartT.series[0].addPoint([(new Date()).getTime(),parseFloat(v)],true,chartT.series[0].data.length>300);});
  fetch('/humidity').then(r=>r.text()).then(v=>{chartH.series[0].addPoint([(new Date()).getTime(),parseFloat(v)],true,chartH.series[0].data.length>300);});
},30000);
</script></body></html>)rawliteral";

void saveHistory()
{
    File f = SPIFFS.open("/history.bin", FILE_WRITE);
    if (!f)
        return;
    f.write((const uint8_t *)tempHistory, sizeof(tempHistory));
    f.write((const uint8_t *)humHistory, sizeof(humHistory));
    f.close();
}

void loadHistory()
{
    if (!SPIFFS.exists("/history.bin"))
        return;
    File f = SPIFFS.open("/history.bin", FILE_READ);
    if (!f)
        return;
    f.read((uint8_t *)tempHistory, sizeof(tempHistory));
    f.read((uint8_t *)humHistory, sizeof(humHistory));
    f.close();
}

void handleNewMessages(int numNewMessages)
{
    auto &bot = notifier.getBot();
    for (int i = 0; i < numNewMessages; i++)
    {
        String chat_id = String(bot.messages[i].chat_id);
        if (chat_id != SECRET_CHAT_ID)
            continue;

        String text = bot.messages[i].text;
        if (text == "/status")
        {
            String msg = "Current Status:\nTemperature: " + String(sensor.readTemperature()) + " C\nHumidity: " + String(sensor.readHumidity()) + " %";
            bot.sendMessage(SECRET_CHAT_ID, msg, "");
        }
        else if (text == "/light_on")
        {
            displayOn = true;
            lcd.backlight();
            lcd.display();
            bot.sendMessage(SECRET_CHAT_ID, "LCD ON", "");
        }
        else if (text == "/light_off")
        {
            displayOn = false;
            lcd.noBacklight();
            lcd.noDisplay();
            bot.sendMessage(SECRET_CHAT_ID, "LCD OFF", "");
        }
        else if (text == "/restart")
        {
            bot.sendMessage(SECRET_CHAT_ID, "Rebooting now...", "");
            bot.getUpdates(bot.last_message_received + 1);
            delay(500);
            ESP.restart();
        }
    }
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
        while (1)
            delay(100);
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

    if (MDNS.begin("climate"))
        Serial.println("mDNS: http://climate.local");

    server.on("/", WebRequestMethod::HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/html", index_html); });

    server.on("/temperature", WebRequestMethod::HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(sensor.readTemperature())); });

    server.on("/humidity", WebRequestMethod::HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(sensor.readHumidity())); });

    server.on("/history", WebRequestMethod::HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String json = "{\"temp\":[";
        for (int i = 0; i < MAX_READINGS; i++)
        {
            json += String(tempHistory[(historyIndex + i) % MAX_READINGS]);
            if (i < MAX_READINGS - 1) json += ",";
        }
        json += "],\"hum\":[";
        for (int i = 0; i < MAX_READINGS; i++)
        {
            json += String(humHistory[(historyIndex + i) % MAX_READINGS]);
            if (i < MAX_READINGS - 1) json += ",";
        }
        json += "]}";
        request->send(200, "application/json", json); });

    ArduinoOTA.begin();
    server.begin();
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
        while (digitalRead(BUTTON_PIN) == LOW)
            delay(10);
        delay(50);
    }

    ArduinoOTA.handle();

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

    if (millis() - lastBotCheck > botCheckInterval)
    {
        int numNewMessages = notifier.getBot().getUpdates(notifier.getBot().last_message_received + 1);
        while (numNewMessages)
        {
            handleNewMessages(numNewMessages);
            numNewMessages = notifier.getBot().getUpdates(notifier.getBot().last_message_received + 1);
        }
        lastBotCheck = millis();
    }

    if (millis() - lastTelegram > telegramInterval)
    {
        lastTelegram = millis();
        String message = "Room Report:\n";
        message += "Temperature: " + String(sensor.readTemperature()) + " C\n";
        message += "Humidity: " + String(sensor.readHumidity()) + " %";
        notifier.getBot().sendMessage(SECRET_CHAT_ID, message, "");
    }
}
