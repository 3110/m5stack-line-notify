#include <M5Unified.hpp>

#include "LINENotify.hpp"
#include "parser/ConfigParser.hpp"

const char* NOTIFY_MESSAGE = "押された！";

LINENotify notify;

void setup(void) {
    M5.begin();
    ConfigParser parser;
    if (!parser.parse()) {
        ESP_LOGE("main", "Failed to parse config file");
        while (true) {
            vTaskDelay(100);
        }
    }
    notify.begin(parser.getSSID(), parser.getPassword());
    notify.setToken(parser.getToken());
}

void loop(void) {
    vTaskDelay(1);
    notify.update();
    M5.update();
    if (M5.BtnA.wasClicked()) {
        if (!notify.send(NOTIFY_MESSAGE)) {
            ESP_LOGE("main", "Failed to send notify: %s", NOTIFY_MESSAGE);
        }
    }
}
