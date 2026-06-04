#pragma once
#define ALERT_ENGINE_H

class AlertEngine
{
private:
    float minimumTemp = 0.0;
    float maximumTemp = 0.0;
    bool wasOutOfRange = false;

public:
    void setThresholds(float minTemp, float maxTemp)
    {
        minimumTemp = minTemp;
        maximumTemp = maxTemp;
    }

    bool checkTemperature(float currentTemp)
    {
        bool currentlyOutOfRange = (currentTemp > maximumTemp || currentTemp < minimumTemp);

        if (currentlyOutOfRange && !wasOutOfRange)
        {
            wasOutOfRange = true;
            return true;
        }

        if (!currentlyOutOfRange)
        {
            wasOutOfRange = false;
        }

        return false;
    }
};
