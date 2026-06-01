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

TEST(DataLoggerTest, RetrievesCorrectTemperature)
{
    DataLogger logger;
    logger.addReading(22.5);

    EXPECT_FLOAT_EQ(22.5, logger.getReading(0));
}

TEST(DataLoggerTest, BufferWrapsAroundAtLimit)
{
    DataLogger logger;

    for (int i = 0; i < 100; i++)
    {
        logger.addReading(20.0);
    }

    logger.addReading(99.9);

    EXPECT_EQ(100, logger.getLogCount());

    EXPECT_FLOAT_EQ(99.9, logger.getReading(0));
}