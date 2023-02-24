#include "LINENotify.hpp"

#include <Arduino_JSON.h>
#include <FS.h>
#include <SPIFFS.h>

static const bool FORMAT_SPIFFS_IF_FAILED = true;
static const char* HTTP_HEADER_LINE_BREAK = "\r\n";

const char* LINENotify::TAG = "LINE Notify";

const char* LINENotify::HOST = "notify-api.line.me";
const char* LINENotify::NOTIFY_API = "/api/notify";

const char* LINENotify::MESSAGE_HEADER = "message=";

const char* LINENotify::CONFIG_FILE = "/line_notify.json";

const char* LINENotify::KEY_SSID = "ssid";
const char* LINENotify::KEY_PASSWORD = "password";
const char* LINENotify::KEY_TOKEN = "token";

LINENotify::LINENotify(void) : _config{0}, _token{0}, _loader(), _client() {
}

LINENotify::~LINENotify(void) {
}

bool LINENotify::begin(const char* config) {
    if (config == nullptr) {
        ESP_LOGE(TAG, "config is null");
        return false;
    }
    if (!connectWiFi()) {
        return false;
    }
    return true;
}

bool LINENotify::connect(void) {
    this->_client.setInsecure();
    if (!this->_client.connect(HOST, HTTPS_PORT)) {
        return false;
    }
    return true;
}

bool LINENotify::connectWiFi(void) {
    if (!this->_loader.begin()) {
        return false;
    }
    if (!this->_loader.exists(CONFIG_FILE)) {
        return false;
    }
    char buf[1024] = {0};
    if (!this->_loader.readFile(CONFIG_FILE, buf, sizeof(buf))) {
        return false;
    }
    JSONVar o = JSON.parse(buf);
    if (JSON.typeof(o) == "undefined") {
        ESP_LOGE(TAG, "Failed to parse the JSON content");
        return false;
    }
    const char* ssid = o[KEY_SSID];
    const char* password = o[KEY_PASSWORD];
    const char* token = o[KEY_TOKEN];
    if (ssid == nullptr || password == nullptr || token == nullptr) {
        return false;
    }
    snprintf(this->_token, sizeof(this->_token), "%s", token);

    ESP_LOGD(TAG, "SSID: %s", ssid);
    ESP_LOGD(TAG, "Password: %s", password);
    ESP_LOGD(TAG, "Token: %s", token);

    WiFi.disconnect(true, true);
    delay(500);

    unsigned long t = millis();
    WiFi.begin(ssid, password);
    ESP_LOGD(TAG, "Connecting");
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
    if (this->_token == nullptr) {
        ESP_LOGE(TAG, "token is null");
        return false;
    }
    if (!connect()) {
        ESP_LOGE(TAG, "Failed to connect to %s", HOST);
        return false;
    }
    const String query = String(MESSAGE_HEADER) + msg;
    const String request =
        String("") + "POST " + NOTIFY_API + " HTTP/1.1" +
        HTTP_HEADER_LINE_BREAK + "Host: " + HOST + HTTP_HEADER_LINE_BREAK +
        "Authorization: Bearer " + this->_token + HTTP_HEADER_LINE_BREAK +
        "Content-Length: " + String(query.length()) + HTTP_HEADER_LINE_BREAK +
        "Content-Type: application/x-www-form-urlencoded" +
        HTTP_HEADER_LINE_BREAK + HTTP_HEADER_LINE_BREAK + query +
        HTTP_HEADER_LINE_BREAK;
    ESP_LOGI(TAG, "%s", request.c_str());
    this->_client.print(request);
    String response = this->_client.readString();
    ESP_LOGD(TAG, "%s", response.c_str());
    this->_client.stop();
    return true;
}