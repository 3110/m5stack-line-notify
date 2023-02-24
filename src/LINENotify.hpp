#pragma once

#include <WiFiClientSecure.h>
#include <esp_log.h>

#include "SPIFFSLoader.hpp"

class LINENotify {
public:
    static const char* TAG;

    static const uint16_t HTTPS_PORT = 443;
    static const char* HOST;
    static const char* NOTIFY_API;
    static const char* MESSAGE_HEADER;
    static const size_t MAX_CONFIG_SIZE = 256;
    static const char* CONFIG_FILE;
    static const size_t MAX_TOKEN_LEN = 43 + 1;

    static const unsigned long WIFI_CONNECTION_TIMEOUT_MS = 30000;

    LINENotify(void);
    virtual ~LINENotify(void);

    virtual bool begin(const char* config = CONFIG_FILE);
    virtual bool send(const char* msg);

protected:
    virtual bool connect(void);
    virtual bool connectWiFi(void);

private:
    static const char* KEY_SSID;
    static const char* KEY_PASSWORD;
    static const char* KEY_TOKEN;

    char _config[MAX_CONFIG_SIZE];
    char _token[MAX_TOKEN_LEN];
    SPIFFSLoader _loader;
    WiFiClientSecure _client;
};