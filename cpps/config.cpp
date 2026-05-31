#include "../headers/config.h"
#include <fstream>

void Config::parseConfig() {
    try {
        nlohmann::json config;
        std::ifstream config_file(file_name);
        if (!config_file.is_open()) {
            throw std::runtime_error("Could not open config file: " + file_name);
        }
        config_file >> config;
        screenWidth = config.at("screenWidth").get<int>();
        screenHeight = config.at("screenHeight").get<int>();
    } catch (const std::exception& e) {
        throw std::runtime_error("Error parsing config file: " + std::string(e.what()));
    }
}

Config::Config(std::string_view file_name) : file_name(file_name) {
    parseConfig();
}
