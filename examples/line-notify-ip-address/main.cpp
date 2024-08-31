#include <M5Unified.h>

#include "LINENotify.hpp"
#include "parser/LINENotifyConfigParser.hpp"

const char* CONFIG_FILE = "/line_notify.json";
const char* TAG = "LineNotifyIPAddress";

LINENotify notify;
LINENotifyConfigParser parser;

void setup(void) {
    M5.begin();
    if (!parser.parse(CONFIG_FILE)) {
        ESP_LOGE(TAG, "Failed to parse config file");
        while (true) {
            delay(100);
        }
    }
    ESP_LOGD(TAG, "SSID: %s", parser.getSSID());
    ESP_LOGD(TAG, "Password: %s", parser.getPassword());
    notify.begin(parser.getSSID(), parser.getPassword());
    notify.setToken(parser.getToken());
    notify.send(WiFi.localIP().toString().c_str());
}

void loop(void) {
    M5.update();
    notify.update();
    delay(100);
}