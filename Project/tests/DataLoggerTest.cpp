#include <gtest/gtest.h>
#include "DataLogger.h"

TEST(DataLoggerTest, NewLoggerIsEmpty)
{
    DataLogger logger;
    EXPECT_EQ(0, logger.getLogCount());
}