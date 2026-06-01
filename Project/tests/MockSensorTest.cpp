#include <gtest/gtest.h>
#include "MockSensor.h"

TEST(MockSensorTest, ReturnsSetTemperature)
{
    MockSensor sensor;

    sensor.setDummyTemperature(25.5);

    EXPECT_FLOAT_EQ(25.5, sensor.readTemperature());
}