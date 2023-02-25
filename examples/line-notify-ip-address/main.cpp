#include <M5Unified.h>

#include "LINENotify.hpp"
#include "parser/LINENotifyConfigParser.hpp"

const char* CONFIG_FILE = "/line_notify.json";

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
    notify.send(WiFi.localIP().toString().c_str());
}

void loop(void) {
    M5.update();
    notify.update();
    delay(100);
}