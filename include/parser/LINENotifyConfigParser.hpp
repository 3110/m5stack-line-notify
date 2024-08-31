#pragma once

#include "parser/ConfigParser.hpp"

class LINENotifyConfigParser : public ConfigParser {
public:
    static constexpr size_t MAX_TOKEN_LEN = 43;
    static constexpr size_t MAX_WIFI_SSID_LEN = 32;
    static constexpr size_t MAX_WIFI_PASSWORD_LEN = 64;
    static constexpr size_t MAX_MESSAGE_LEN =
        48 * 4;  // UTF-8 の最大 4 バイトで 48 文字分。3 バイトなら 64 文字

    LINENotifyConfigParser(void);
    virtual ~LINENotifyConfigParser(void) = default;

    virtual bool parse(const char* config);

    virtual bool hasMessage(void) const;
    virtual const char* const getSSID(void) const;
    virtual const char* const getPassword(void) const;
    virtual const char* const getToken(void) const;
    virtual const char* const getMessage(void) const;

protected:
    virtual const char* getTag(void) const;
    virtual bool parse(const char* config, JSONVar& o);

private:
    static const char* KEY_SSID;
    static const char* KEY_PASSWORD;
    static const char* KEY_TOKEN;
    static const char* KEY_MESSAGE;

    char _ssid[MAX_WIFI_SSID_LEN + 1];
    char _password[MAX_WIFI_PASSWORD_LEN + 1];
    char _token[MAX_TOKEN_LEN + 1];
    char _message[MAX_MESSAGE_LEN + 1];
};