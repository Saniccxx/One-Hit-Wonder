#include "../headers/map_display.h"
#include "nlohmann/json.hpp"
#include <fstream>

void MapDisplay::saveMapToJson() {
    nlohmann::ordered_json json;
    // json["width_in_tiles"] = width_in_tiles;
    // json["height_in_tiles"] = height_in_tiles;
    // json["tile_size"] = tile_size;

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

    std::ofstream file("../map_data.json");
    file << json.dump(4);
    std::cout << "Saved map data.json" << std::endl;
}

void MapDisplay::loadMapFromJson() {
    std::ifstream file("../map_data.json");
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

    // int width_in_tiles = json["width_in_tiles"];
    // int height_in_tiles = json["height_in_tiles"];
    // int tile_size = json["tile_size"];

    for (const auto& obj : json["coll_objects"]) {
        int x = obj["x"];
        int y = obj["y"];
        int id = obj["id"];
        std::string file = obj.value("file", "decorative_cracks_walls.png");
        place_block(x, y, 1, id, file);
    }
}