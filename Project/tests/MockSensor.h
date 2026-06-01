#pragma once
#include "ISensor.h"

class MockSensor : public ISensor
{
private:
    float dummyTemp = 0.0;

public:
    void setDummyTemperature(float temp)
    {
        dummyTemp = temp;
    }

    float readTemperature() override
    {
        return dummyTemp;
    }
};