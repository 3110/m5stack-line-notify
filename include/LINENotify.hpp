#pragma once

#include <HTTPClient.h>
#include <esp_log.h>

class LINENotify {
public:
    static const char* TAG;
    static const char* NOTIFY_URL;

    static const unsigned long WIFI_CONNECTION_TIMEOUT_MS = 30000;

    LINENotify(void);
    virtual ~LINENotify(void);

    virtual bool begin(const char* ssid, const char* password,
                       unsigned long timeout = WIFI_CONNECTION_TIMEOUT_MS);
    virtual bool update(void);
    virtual bool send(const char* token, const char* msg);

protected:
    virtual bool connectWiFi(const char* ssid, const char* password,
                             unsigned long timeout);

private:
    HTTPClient _client;
};