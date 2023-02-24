#include "LINENotify.hpp"

#include <Arduino_JSON.h>
#include <FS.h>
#include <SPIFFS.h>

#include "SPIFFSLoader.hpp"

const char* LINENotify::TAG = "LINE Notify";
const char* LINENotify::NOTIFY_URL = "https://notify-api.line.me/api/notify";
const char* LINENotify::CONFIG_FILENAME = "/line_notify.json";

const char* LINENotify::KEY_SSID = "ssid";
const char* LINENotify::KEY_PASSWORD = "password";
const char* LINENotify::KEY_TOKEN = "token";

LINENotify::LINENotify(void) : _token{0}, _client() {
}

LINENotify::~LINENotify(void) {
}

bool LINENotify::begin(const char* config) {
    if (config == nullptr) {
        ESP_LOGE(TAG, "config is null");
        return false;
    }
    if (!parseConfig(config)) {
        return false;
    }
    if (!connectWiFi()) {
        return false;
    }
    return true;
}

bool LINENotify::parseConfig(const char* config) {
    SPIFFSLoader loader;
    if (!loader.begin()) {
        return false;
    }
    if (!loader.exists(CONFIG_FILENAME)) {
        return false;
    }
    char buf[MAX_CONFIG_SIZE] = {0};
    if (!loader.readFile(CONFIG_FILENAME, buf, sizeof(buf))) {
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
        return false;
    }
    ESP_LOGD(TAG, "SSID: %s", this->_ssid);
    ESP_LOGD(TAG, "Password: %s", this->_password);
    ESP_LOGD(TAG, "Token: %s", this->_token);
    return true;
}

bool LINENotify::connectWiFi(void) {
    if (strlen(this->_ssid) == 0 || strlen(this->_password) == 0) {
        ESP_LOGE(TAG, "Illegal WiFi setting");
        return false;
    }
    WiFi.disconnect(true, true);
    delay(500);

    unsigned long t = millis();
    WiFi.begin(this->_ssid, this->_password);
    ESP_LOGD(TAG, "Connecting to %s", this->_ssid);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        if (millis() - t > WIFI_CONNECTION_TIMEOUT_MS) {
            ESP_LOGI(TAG, "Connection Timeout");
            break;
        }
    }
    if (WiFi.status() == WL_CONNECTED) {
        ESP_LOGI(TAG, "Connected: IP address %s", WiFi.localIP().toString());
        return true;
    }
    return false;
}

bool LINENotify::send(const char* msg) {
    if (msg == nullptr) {
        ESP_LOGE(TAG, "msg is null");
        return false;
    }
    if (strlen(this->_token) == 0) {
        ESP_LOGE(TAG, "token is null");
        return false;
    }
    this->_client.begin(NOTIFY_URL);
    this->_client.addHeader("Authorization", "Bearer " + String(this->_token));
    this->_client.addHeader("Content-Type",
                            "application/x-www-form-urlencoded");
    this->_client.POST("message=" + String(msg));

    String response = this->_client.getString();
    ESP_LOGD(TAG, "Response: %s", response.c_str());
    JSONVar o = JSON.parse(response.c_str());
    if (JSON.typeof(o) == "undefined") {
        ESP_LOGE(TAG, "Failed to parse response");
        return false;
    }
    this->_client.end();
    return (int)o["status"] == (int)HTTP_CODE_OK;
}