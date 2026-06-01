#include <gtest/gtest.h>
#include "AlertEngine.h"

TEST(AlertEngineTest, NormalTemperatureTriggersNoAlert)
{
    AlertEngine engine;
    engine.setThresholds(18.0, 25.0);
    EXPECT_EQ(false, engine.checkTemperature(22.0));
}

TEST(AlertEngineTest, HighTemperatureTriggersAlert)
{
    AlertEngine engine;
    engine.setThresholds(18.0, 25.0);
    EXPECT_EQ(true, engine.checkTemperature(30.0));
}

TEST(AlertEngineTest, LowTemperatureTriggersAlert)
{
    AlertEngine engine;
    engine.setThresholds(18.0, 25.0);
    EXPECT_EQ(true, engine.checkTemperature(10.0));
}