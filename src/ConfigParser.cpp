#include "parser/ConfigParser.hpp"

#include <Arduino_JSON.h>

const char* ConfigParser::TAG = "ConfigParser";

const char* ConfigParser::CONFIG_FILENAME = "/line_notify.json";

const char* ConfigParser::KEY_SSID = "ssid";
const char* ConfigParser::KEY_PASSWORD = "password";
const char* ConfigParser::KEY_TOKEN = "token";

ConfigParser::ConfigParser(void)
    : _ssid{0}, _password{0}, _token{0}, _loader() {
}

ConfigParser::~ConfigParser(void) {
}

bool ConfigParser::parse(const char* config) {
    if (!this->_loader.begin()) {
        return false;
    }
    if (!this->_loader.exists(config)) {
        return false;
    }
    char buf[MAX_CONFIG_SIZE] = {0};
    if (!this->_loader.readFile(config, buf, sizeof(buf))) {
        return false;
    }
    JSONVar o = JSON.parse(buf);
    if (JSON.typeof(o) == "undefined") {
        ESP_LOGE(TAG, "Failed to parse the JSON content");
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
    ESP_LOGD(TAG, "SSID: %s", this->_ssid);
    ESP_LOGD(TAG, "Password: %s", this->_password);
    ESP_LOGD(TAG, "Token: %s", this->_token);
    return true;
}
