#pragma once
#define ALERT_ENGINE_H

class AlertEngine
{
private:
    float minimumTemp = 0.0;
    float maximumTemp = 0.0;

public:
    void setThresholds(float minTemp, float maxTemp)
    {
        minimumTemp = minTemp;
        maximumTemp = maxTemp;
    }

    bool checkTemperature(float currentTemp)
    {
        return (currentTemp > maximumTemp || currentTemp < minimumTemp);
    }
};
