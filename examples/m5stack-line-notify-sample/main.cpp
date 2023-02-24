#include <M5Unified.hpp>

#include "LINENotify.hpp"
#include "parser/ConfigParser.hpp"

const char* NOTIFY_MESSAGE = "押された！";

ConfigParser parser;
LINENotify notify;

void setup(void) {
    M5.begin();
    if (!parser.parse()) {
        ESP_LOGE("main", "Failed to parse config file");
        while (true) {
            vTaskDelay(100);
        }
    }
    notify.begin(parser.getSSID(), parser.getPassword());
}

void loop(void) {
    vTaskDelay(1);
    notify.update();
    M5.update();
    if (M5.BtnA.wasClicked()) {
        if (!notify.send(parser.getToken(), NOTIFY_MESSAGE)) {
            ESP_LOGE("main", "Failed to send notify: %s", NOTIFY_MESSAGE);
        }
    }
}
