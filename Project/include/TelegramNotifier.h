#pragma once
#include "IAlertNotifier.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

class TelegramNotifier : public IAlertNotifier
{
private:
    WiFiClientSecure client;
    UniversalTelegramBot bot;
    String chatId;

public:
    TelegramNotifier(const String &token, const String &chatId)
        : bot(token, client), chatId(chatId)
    {
        client.setInsecure();
    }

    void sendAlert(const std::string &message) override
    {
        bot.sendMessage(chatId, message.c_str(), "");
    }

    UniversalTelegramBot &getBot()
    {
        return bot;
    }
};
