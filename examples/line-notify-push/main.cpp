#include <M5Unified.hpp>

#include "LINENotify.hpp"
#include "parser/LINENotifyConfigParser.hpp"

const char* CONFIG_FILE = "/line_notify.json";

const char* NOTIFY_MESSAGE = "押された！";

LINENotify notify;

void setup(void) {
    M5.begin();
    LINENotifyConfigParser parser;
    if (!parser.parse(CONFIG_FILE)) {
        ESP_LOGE("main", "Failed to parse config file");
        while (true) {
            delay(100);
        }
    }
    notify.begin(parser.getSSID(), parser.getPassword());
    notify.setToken(parser.getToken());
}

void loop(void) {
    notify.update();
    M5.update();
    if (M5.BtnA.wasClicked()) {
        if (!notify.send(NOTIFY_MESSAGE)) {
            ESP_LOGE("main", "Failed to send notify: %s", NOTIFY_MESSAGE);
        }
    }
    delay(100);
}
