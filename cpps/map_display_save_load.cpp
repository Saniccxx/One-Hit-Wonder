#include "map_display.h"
#include "utils.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

void MapDisplay::resolveMapDataPath() {
    if (!mapDataFullPath.empty()) {
        return;
    }

    mapDataFullPath = utils::getRootFilePath("map_data.json");
}

void MapDisplay::saveMapToJson() {
    resolveMapDataPath();

    nlohmann::ordered_json json;

    for (auto & coll_object : coll_objects) {
        for (const auto & j : coll_object) {
            if (!j) continue;
            auto params = j->get_parameters();
            json["coll_objects"].push_back({
                {"x", params[0]},
                {"y", params[1]},
                {"width", params[2]},
                {"height", params[3]},
                {"id", params[4]},
                {"file", j->get_filename()}
            });
        }
    }

    std::ofstream file(mapDataFullPath);
    if (!file.is_open()) {
        std::cerr << "Could not open file for writing: " << mapDataFullPath << std::endl;
        return;
    }

    file << json.dump(4);
    std::cout << "Saved " << mapDataFullPath << std::endl;
}

void MapDisplay::loadMapFromJson() {
    resolveMapDataPath();

    std::ifstream file(mapDataFullPath);
    if (!file.is_open()) {
        return;
    }

    nlohmann::ordered_json json;
    try {
        file >> json;
    } catch (const nlohmann::json::parse_error&) {
        return;
    }

    if (!json.contains("coll_objects") || !json["coll_objects"].is_array()) {
        return;
    }

    for (const auto& obj : json["coll_objects"]) {
        int x = obj["x"];
        int y = obj["y"];
        int id = obj["id"];
        std::string file_str = obj.value("file", "decorative_cracks_walls.png");
        place_block(x, y, 1, id, file_str);
    }
}