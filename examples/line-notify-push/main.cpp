#include <M5Unified.hpp>

#include "LINENotify.hpp"
#include "parser/LINENotifyConfigParser.hpp"

const char* CONFIG_FILE = "/line_notify.json";
const char* DEFAULT_NOTIFY_MESSAGE = "押された！";
const char* TAG = "LineNotifyPush";

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
    if (parser.hasMessage()) {
        ESP_LOGD(TAG, "Message: %s", parser.getMessage());
    } else {
        ESP_LOGD(TAG, "Message: %s", DEFAULT_NOTIFY_MESSAGE);
    }
    notify.begin(parser.getSSID(), parser.getPassword());
    notify.setToken(parser.getToken());
}

void loop(void) {
    notify.update();
    M5.update();
    if (M5.BtnA.wasClicked()) {
        if (!notify.send(parser.hasMessage() ? parser.getMessage()
                                             : DEFAULT_NOTIFY_MESSAGE)) {
            ESP_LOGE(TAG, "Failed to send notify");
        }
    }
    delay(100);
}
