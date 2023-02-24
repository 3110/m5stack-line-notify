#pragma once

#include <HTTPClient.h>
#include <esp_log.h>

class LINENotify {
public:
    static const char* TAG;
    static const char* NOTIFY_URL;

    static const size_t MAX_TOKEN_LEN = 43;
    static const unsigned long WIFI_CONNECTION_TIMEOUT_MS = 30000;

    LINENotify(void);
    virtual ~LINENotify(void);

    virtual bool begin(const char* ssid, const char* password,
                       unsigned long timeout = WIFI_CONNECTION_TIMEOUT_MS);
    virtual bool update(void);
    virtual bool setToken(const char* token);
    virtual bool send(const char* msg);

protected:
    virtual bool connectWiFi(const char* ssid, const char* password,
                             unsigned long timeout);
    virtual HTTPClient& getClient(void) {
        return this->_client;
    }

private:
    char _token[MAX_TOKEN_LEN + 1];
    HTTPClient _client;
};