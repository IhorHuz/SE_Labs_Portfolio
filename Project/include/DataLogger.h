#pragma once

class DataLogger
{
private:
    int currentCount = 0;

public:
    void addReading(float temperature)
    {
        currentCount++;
    }

    int getLogCount()
    {
        return currentCount;
    }
};