#include "../headers/config.h"
#include <fstream>

void Config::parseConfig() {
    const std::string full_path = std::string(config::configFilePath) + std::string(config::configFileName) + ".json";
    try {
        nlohmann::ordered_json config;
        std::ifstream config_file(full_path);

        if (!config_file.is_open()) {
            config["screenWidth"] = config::defaultScreenWidth;
            config["screenHeight"] = config::defaultScreenHeight;

            std::ofstream out(full_path);
            if (!out.is_open()) {
                throw std::runtime_error("Could not create config file: " + full_path);
            }
            out << config.dump(4);

            screenWidth = config::defaultScreenWidth;
            screenHeight = config::defaultScreenHeight;
            return;
        }
        config_file >> config;
        screenWidth = config.at("screenWidth").get<int>();
        screenHeight = config.at("screenHeight").get<int>();
    } catch (const std::exception& e) {
        throw std::runtime_error("Error parsing config file: " + std::string(e.what()));
    }
}

Config::Config() {
    parseConfig();
}

void Config::set_resolution(int width, int height) {
    screenWidth = width;
    screenHeight = height;

    const std::string full_path = std::string(config::configFilePath) + std::string(config::configFileName) + ".json";
    try {
        nlohmann::ordered_json config_json;
        config_json["screenWidth"] = screenWidth;
        config_json["screenHeight"] = screenHeight;

        std::ofstream out(full_path);
        if (out.is_open()) {
            out << config_json.dump(4);
        }
    } catch (...) {}
}
