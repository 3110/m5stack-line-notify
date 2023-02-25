#pragma once

#include <Arduino_JSON.h>

#include <loader/SPIFFSLoader.hpp>

class ConfigParser {
public:
    ConfigParser(void);
    virtual ~ConfigParser(void);

    virtual bool parse(const char* config);

protected:
    virtual const char* getTag(void) const;
    virtual bool parse(const char* config, JSONVar& o);

private:
    SPIFFSLoader _loader;
};