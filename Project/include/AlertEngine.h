#pragma once
#define ALERT_ENGINE_H

class AlertEngine
{
public:
    void setThresholds(float minTemp, float maxTemp) {}
    bool checkTemperature(float currentTemp)
    {
        return true;
    }
};
