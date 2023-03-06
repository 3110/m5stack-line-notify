#include "loader/SPIFFSLoader.hpp"

static const bool FORMAT_SPIFFS_IF_FAILED = true;

const char* SPIFFSLoader::TAG = "SPIFFSLoader";

SPIFFSLoader::SPIFFSLoader(void) {
}

SPIFFSLoader::~SPIFFSLoader(void) {
}

bool SPIFFSLoader::begin(void) {
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        ESP_LOGE(TAG, "Failed to mount SPIFFS");
        return false;
    }
    return true;
}

bool SPIFFSLoader::exists(const char* path) {
    if (path == nullptr) {
        ESP_LOGE(TAG, "path is null");
        return false;
    }
    return SPIFFS.exists(path);
}

size_t SPIFFSLoader::size(const char* path) const {
    if (path == nullptr) {
        ESP_LOGE(TAG, "path is null");
        return 0;
    }
    File f = SPIFFS.open(path, "r");
    if (!f) {
        ESP_LOGE(TAG, "Can't open file: %s", path);
        return 0;
    }
    const size_t s = f.size();
    f.close();
    return s;
}

bool SPIFFSLoader::readFile(const char* path, char* buf, size_t size) {
    if (path == nullptr) {
        ESP_LOGE(TAG, "path is null");
        return false;
    }
    File f = SPIFFS.open(path, "r");
    if (!f) {
        ESP_LOGE(TAG, "Can't open file: %s", path);
        return false;
    }
    size_t fileSize = f.size();
    ESP_LOGD(TAG, "File Size: %d", fileSize);
    if (fileSize > size) {
        ESP_LOGE(TAG, "Exceed the buffer size %d < %d", size, fileSize);
        f.close();
        return false;
    }
    f.read((uint8_t*)buf, size);
    f.close();
    return true;
}

bool SPIFFSLoader::removeFile(const char* path) {
    if (path == nullptr) {
        ESP_LOGE(TAG, "path is null");
        return false;
    }
    if (!SPIFFS.remove(path)) {
        ESP_LOGE(TAG, "Failed to remove %s", path);
        return false;
    }
    return true;
}
