#pragma once

class DataLogger
{
private:
    float readings[100];
    int currentCount = 0;

public:
    void addReading(float temperature)
    {
        readings[currentCount] = temperature;
        currentCount++;
    }

    int getLogCount()
    {
        return currentCount;
    }

    float getReading(int index)
    {
        return readings[index];
    }
};