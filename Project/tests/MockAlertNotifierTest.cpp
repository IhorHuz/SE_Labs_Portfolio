#include <gtest/gtest.h>
#include "MockAlertNotifier.h"

TEST(MockAlertNotifierTest, RecordsSentAlert)
{
    MockAlertNotifier notifier;

    notifier.sendAlert("Danger: High Temp!");

    EXPECT_EQ(true, notifier.alertSent);
    EXPECT_EQ("Danger: High Temp!", notifier.lastMessage);
}