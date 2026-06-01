#pragma once
#include <string>

class IAlertNotifier
{
public:
    virtual ~IAlertNotifier() = default;
    virtual void sendAlert(const std::string &message) = 0;
};