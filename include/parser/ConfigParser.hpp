#pragma once

#include <Arduino_JSON.h>

#include <loader/SPIFFSLoader.hpp>

class ConfigParser {
public:
    ConfigParser(void);
    virtual ~ConfigParser(void);

    virtual bool parse(const char* config) = 0;

protected:
    virtual const char* getTag(void) const;
    virtual bool parse(const char* config, JSONVar& o);

private:
    SPIFFSLoader _loader;
};