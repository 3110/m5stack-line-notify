#include <M5Unified.h>

#include "LINENotify.hpp"
#include "parser/ConfigParser.hpp"

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
    notify.send(WiFi.localIP().toString().c_str());
}

void loop(void) {
    vTaskDelay(1);
    M5.update();
    notify.update();
}