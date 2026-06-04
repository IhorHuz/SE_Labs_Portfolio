#pragma once
#include "ISensor.h"
#include <Adafruit_SHTC3.h>

class SHTC3Sensor : public ISensor
{
private:
    Adafruit_SHTC3 shtc3;
    float lastTemperature = 0.0f;
    float lastHumidity = 0.0f;
    bool initialized = false;

public:
    bool begin()
    {
        initialized = shtc3.begin();
        return initialized;
    }

    void read()
    {
        if (!initialized) return;
        sensors_event_t humidityEvent, temperatureEvent;
        shtc3.getEvent(&humidityEvent, &temperatureEvent);
        lastTemperature = temperatureEvent.temperature;
        lastHumidity = humidityEvent.relative_humidity;
    }

    float readTemperature() override
    {
        return lastTemperature;
    }

    float readHumidity()
    {
        return lastHumidity;
    }
};
