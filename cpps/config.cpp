#include "config.h"
#include "utils.h" // Załączamy nasz nowy plik pomocniczy
#include <fstream>
#include <stdexcept>

inline constexpr std::string_view configFileName = "config";

void Config::parseConfig() {
    const std::string fileName = std::string(configFileName) + ".json";

    configFullPath = utils::getRootFilePath(fileName);

    try {
        nlohmann::ordered_json config_json;
        std::ifstream config_file(configFullPath);

        if (!config_file.is_open()) {
            config_json["screenWidth"] = config::defaultScreenWidth;
            config_json["screenHeight"] = config::defaultScreenHeight;

            std::ofstream out(configFullPath);
            if (!out.is_open()) {
                throw std::runtime_error("Could not create config file: " + configFullPath);
            }
            out << config_json.dump(4);

            screenWidth = config::defaultScreenWidth;
            screenHeight = config::defaultScreenHeight;
            return;
        }

        config_file >> config_json;
        screenWidth = config_json.at("screenWidth").get<int>();
        screenHeight = config_json.at("screenHeight").get<int>();

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

    try {
        nlohmann::ordered_json config_json;
        config_json["screenWidth"] = screenWidth;
        config_json["screenHeight"] = screenHeight;

        std::ofstream out(configFullPath);
        if (out.is_open()) {
            out << config_json.dump(4);
        }
    } catch (...) {}
}