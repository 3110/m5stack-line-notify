#pragma once

#include "loader/SPIFFSLoader.hpp"

class ConfigParser {
public:
    static const char* TAG;
    static const char* CONFIG_FILENAME;

    static const size_t MAX_CONFIG_SIZE = 256;
    static const size_t MAX_TOKEN_LEN = 43;
    static const size_t MAX_WIFI_SSID_LEN = 32;
    static const size_t MAX_WIFI_PASSWORD_LEN = 64;

    ConfigParser(void);
    virtual ~ConfigParser(void);

    virtual bool parse(const char* config = CONFIG_FILENAME);

    const char* const getSSID(void) const {
        return this->_ssid;
    }
    const char* const getPassword(void) const {
        return this->_password;
    }
    const char* const getToken(void) const {
        return this->_token;
    }

private:
    static const char* KEY_SSID;
    static const char* KEY_PASSWORD;
    static const char* KEY_TOKEN;

    char _ssid[MAX_WIFI_SSID_LEN + 1];
    char _password[MAX_WIFI_PASSWORD_LEN + 1];
    char _token[MAX_TOKEN_LEN + 1];

    SPIFFSLoader _loader;
};