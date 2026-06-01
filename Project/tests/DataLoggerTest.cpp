#include <gtest/gtest.h>
#include "DataLogger.h"

TEST(DataLoggerTest, NewLoggerIsEmpty)
{
    DataLogger logger;
    EXPECT_EQ(0, logger.getLogCount());
}

TEST(DataLoggerTest, AddingReadingIncreasesCount)
{
    DataLogger logger;
    logger.addReading(22.5);
    EXPECT_EQ(1, logger.getLogCount());
}