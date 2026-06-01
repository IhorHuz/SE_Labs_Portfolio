#pragma once
#include "IAlertNotifier.h"
#include <string>

class MockAlertNotifier : public IAlertNotifier
{
public:
    bool alertSent = false;
    std::string lastMessage = "";

    void sendAlert(const std::string &message) override
    {
        alertSent = true;
        lastMessage = message;
    }
};