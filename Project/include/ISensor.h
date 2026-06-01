#pragma once

class ISensor
{
public:
    virtual ~ISensor() = default;
    virtual float readTemperature() = 0;
};