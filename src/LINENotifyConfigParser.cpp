#include "parser/LINENotifyConfigParser.hpp"

const char* LINENotifyConfigParser::KEY_SSID = "ssid";
const char* LINENotifyConfigParser::KEY_PASSWORD = "password";
const char* LINENotifyConfigParser::KEY_TOKEN = "token";

LINENotifyConfigParser::LINENotifyConfigParser(void) {
}

LINENotifyConfigParser::~LINENotifyConfigParser(void) {
}

bool LINENotifyConfigParser::parse(const char* config) {
    return ConfigParser::parse(config);
}

const char* const LINENotifyConfigParser::getSSID(void) const {
    return this->_ssid;
}
const char* const LINENotifyConfigParser::getPassword(void) const {
    return this->_password;
}
const char* const LINENotifyConfigParser::getToken(void) const {
    return this->_token;
}

const char* LINENotifyConfigParser::getTag(void) const {
    return "LINENotifyConfigParser";
}

bool LINENotifyConfigParser::parse(const char* config, JSONVar& o) {
    if (!ConfigParser::parse(config, o)) {
        return false;
    }
    snprintf(this->_ssid, sizeof(this->_ssid), "%s", (const char*)o[KEY_SSID]);
    snprintf(this->_password, sizeof(this->_password), "%s",
             (const char*)o[KEY_PASSWORD]);
    snprintf(this->_token, sizeof(this->_token), "%s",
             (const char*)o[KEY_TOKEN]);
    if (strlen(this->_ssid) == 0 || strlen(this->_password) == 0 ||
        strlen(this->_token) == 0) {
        memset(this->_ssid, 0, sizeof(this->_ssid));
        memset(this->_password, 0, sizeof(this->_password));
        memset(this->_token, 0, sizeof(this->_token));
        return false;
    }
    ESP_LOGD(getTag(), "SSID: %s", this->_ssid);
    ESP_LOGD(getTag(), "Password: %s", this->_password);
    ESP_LOGD(getTag(), "Token: %s", this->_token);
    return true;
}
