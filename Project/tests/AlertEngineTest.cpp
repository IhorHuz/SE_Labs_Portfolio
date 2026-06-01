#include <gtest/gtest.h>
#include "AlertEngine.h"

// Test 1 (Student A): Normal temperature should NOT trigger alert
TEST(AlertEngineTest, NormalTemperatureTriggersNoAlert)
{
    AlertEngine engine;
    engine.setThresholds(18.0, 25.0);
    EXPECT_EQ(false, engine.checkTemperature(22.0));
}