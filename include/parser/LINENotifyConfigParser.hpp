#pragma once

#include "parser/ConfigParser.hpp"

class LINENotifyConfigParser : public ConfigParser {
public:
    static const size_t MAX_TOKEN_LEN = 43;
    static const size_t MAX_WIFI_SSID_LEN = 32;
    static const size_t MAX_WIFI_PASSWORD_LEN = 64;

    LINENotifyConfigParser(void);
    virtual ~LINENotifyConfigParser(void);

    virtual bool parse(const char* config);

    const char* const getSSID(void) const;
    const char* const getPassword(void) const;
    const char* const getToken(void) const;

protected:
    virtual const char* getTag(void) const;
    virtual bool parse(const char* config, JSONVar& o);

private:
    static const char* KEY_SSID;
    static const char* KEY_PASSWORD;
    static const char* KEY_TOKEN;

    char _ssid[MAX_WIFI_SSID_LEN + 1];
    char _password[MAX_WIFI_PASSWORD_LEN + 1];
    char _token[MAX_TOKEN_LEN + 1];
};