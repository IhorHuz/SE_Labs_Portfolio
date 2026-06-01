#include <gtest/gtest.h>
// #include "ClimateStation.h"
#include "MockSensor.h"
#include "MockAlertNotifier.h"
#include "DataLogger.h"
#include "AlertEngine.h"

TEST(ClimateStationTest, UpdatesAndLogsNormalTemperature)
{
    MockSensor sensor;
    MockAlertNotifier notifier;
    DataLogger logger;
    AlertEngine engine;

    engine.setThresholds(18.0, 25.0);
    sensor.setDummyTemperature(22.0);

    // ClimateStation station(sensor, notifier, logger, engine);

    // station.update();

    EXPECT_EQ(1, logger.getLogCount());
    EXPECT_FLOAT_EQ(22.0, logger.getReading(0));
    EXPECT_EQ(false, notifier.alertSent);
}