#include <M5Unified.hpp>

#include "LINENotify.hpp"

const char* NOTIFY_MESSAGE = "押された！";
LINENotify notify;

void setup(void) {
    M5.begin();
    notify.begin();
}

void loop(void) {
    vTaskDelay(1);
    M5.update();
    if (M5.BtnA.wasClicked()) {
        if (!notify.send(NOTIFY_MESSAGE)) {
            ESP_LOGE("main", "Failed to send notify: %s", NOTIFY_MESSAGE);
        }
    }
}
