#include "parser/ConfigParser.hpp"

#include "loader/SPIFFSLoader.hpp"

ConfigParser::ConfigParser(void) : _loader() {
}

ConfigParser::~ConfigParser(void) {
}

const char* ConfigParser::getTag(void) const {
    return "ConfigParser";
}

bool ConfigParser::parse(const char* config, JSONVar& o) {
    if (!this->_loader.begin()) {
        return false;
    }
    if (!this->_loader.exists(config)) {
        return false;
    }
    char buf[this->_loader.size(config)] = {0};
    if (!this->_loader.readFile(config, buf, sizeof(buf))) {
        return false;
    }
    o = JSON.parse(buf);
    if (JSON.typeof(o) == "undefined") {
        ESP_LOGE(getTag(), "Failed to parse the JSON content");
        return false;
    } else {
        return true;
    }
}
