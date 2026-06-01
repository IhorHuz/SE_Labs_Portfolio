#pragma once

class DataLogger
{
private:
    float readings[100];
    int writeIndex = 0;
    int totalCount = 0;

public:
    void addReading(float temperature)
    {
        readings[writeIndex] = temperature;

        writeIndex = (writeIndex + 1) % 100;

        if (totalCount < 100)
        {
            totalCount++;
        }
    }

    int getLogCount()
    {
        return totalCount;
    }

    float getReading(int index)
    {
        return readings[index];
    }
};