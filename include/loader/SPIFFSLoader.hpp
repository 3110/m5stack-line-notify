#pragma once

#include <FS.h>
#include <SPIFFS.h>
#include <esp_log.h>

class SPIFFSLoader {
public:
    static const char* TAG;
    SPIFFSLoader(void);
    virtual ~SPIFFSLoader(void);

    virtual bool begin(void);
    virtual bool exists(const char* path);
    virtual bool readFile(const char* path, char* buf, size_t size);
    virtual bool removeFile(const char* path);
};
