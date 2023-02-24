#include "LINENotify.hpp"

#include <Arduino_JSON.h>

const char* LINENotify::TAG = "LINENotify";
const char* LINENotify::NOTIFY_URL = "https://notify-api.line.me/api/notify";

LINENotify::LINENotify(void) : _client() {
    this->_client.setReuse(false);
}

LINENotify::~LINENotify(void) {
}

bool LINENotify::begin(const char* ssid, const char* password,
                       unsigned long timeout) {
    if (ssid == nullptr) {
        ESP_LOGE(TAG, "ssid is null");
        return false;
    }
    if (password == nullptr) {
        ESP_LOGE(TAG, "password is null");
        return false;
    }
    return connectWiFi(ssid, password, timeout);
}

bool LINENotify::update(void) {
    if (WiFi.status() != WL_CONNECTED) {
        ESP_LOGI(TAG, "WiFi disconnected. Reconnecting...");
        WiFi.disconnect(true, true);
        bool result = WiFi.reconnect();
        ESP_LOGI(TAG, "%s", result ? "done." : "failed.");
        return result;
    }
    return true;
}

bool LINENotify::connectWiFi(const char* ssid, const char* password,
                             unsigned long timeout) {
    WiFi.disconnect(true, true);
    delay(500);

    unsigned long t = millis();
    WiFi.begin(ssid, password);
    ESP_LOGD(TAG, "Connecting...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        if (millis() - t > timeout) {
            ESP_LOGI(TAG, "Connection Timeout %lu", timeout);
            break;
        }
    }
    if (WiFi.status() == WL_CONNECTED) {
        ESP_LOGI(TAG, "Connected: IP address %s", WiFi.localIP().toString());
        return true;
    } else {
        return false;
    }
}

bool LINENotify::send(const char* token, const char* msg) {
    if (token == nullptr) {
        ESP_LOGE(TAG, "token is null");
        return false;
    }
    if (msg == nullptr) {
        ESP_LOGE(TAG, "msg is null");
        return false;
    }

    this->_client.begin(NOTIFY_URL);
    this->_client.addHeader("Authorization", "Bearer " + String(token));
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