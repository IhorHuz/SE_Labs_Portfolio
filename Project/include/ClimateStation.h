#pragma once
#include "ISensor.h"
#include "IAlertNotifier.h"
#include "DataLogger.h"
#include "AlertEngine.h"
#include <string>

class ClimateStation
{
private:
    ISensor &sensor;
    IAlertNotifier &notifier;
    DataLogger &logger;
    AlertEngine &engine;

public:
    ClimateStation(ISensor &s, IAlertNotifier &n, DataLogger &dl, AlertEngine &ae)
        : sensor(s), notifier(n), logger(dl), engine(ae) {}

    void update()
    {
        float currentTemp = sensor.readTemperature();

        logger.addReading(currentTemp);

        if (engine.checkTemperature(currentTemp))
        {
            notifier.sendAlert("ALERT: Extreme temperature detected: " + std::to_string(currentTemp) + "C");
        }
    }
};