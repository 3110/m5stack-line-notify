#pragma once

#include <HTTPClient.h>
#include <esp_log.h>

class LINENotify {
public:
    static const char* TAG;
    static const char* NOTIFY_URL;
    static const char* CONFIG_FILENAME;

    static const size_t MAX_CONFIG_SIZE = 256;
    static const size_t MAX_TOKEN_LEN = 43;
    static const size_t MAX_WIFI_SSID_LEN = 32;
    static const size_t MAX_WIFI_PASSWORD_LEN = 64;

    static const unsigned long WIFI_CONNECTION_TIMEOUT_MS = 30000;

    LINENotify(void);
    virtual ~LINENotify(void);

    virtual bool begin(const char* config = CONFIG_FILENAME);
    virtual bool send(const char* msg);

protected:
    virtual bool parseConfig(const char* config);
    virtual bool connectWiFi(void);

private:
    static const char* KEY_SSID;
    static const char* KEY_PASSWORD;
    static const char* KEY_TOKEN;

    char _ssid[MAX_WIFI_SSID_LEN + 1];
    char _password[MAX_WIFI_PASSWORD_LEN + 1];
    char _token[MAX_TOKEN_LEN + 1];

    HTTPClient _client;
};