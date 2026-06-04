#include "../headers/map_display.h"

#include <format>
#include <iostream>
#include "../headers/camera.h"
#include "../headers/game.h"
#include "../headers/map_player.h"
#include "../headers/renderer.h"
#include "../headers/combat_display.h"

MapDisplay::MapDisplay(Game& game): game(game) {}

MapDisplay::~MapDisplay() = default;

void MapDisplay::init() {
    if (!camera) {
        camera = std::make_unique<GameCamera>(game.width, game.height);
    }
    Renderer::init_lighting_shader("Resources/shaders/lights.fs");
    player = std::make_unique<MapPlayer>(
        1300.0f,
        550.0f,
        game.get_texture("front.png"),
        game.get_texture("back.png"),
        game.get_texture("side.png")

    );

    light.color = Renderer::white;
    light.position_radius = {
        player->get_x() + static_cast<float>(player->size) * 0.5f,
        player->get_y() + static_cast<float>(player->size) * 0.5f,
        500.0f
    };


    player_particles = std::make_unique<ParticleGenerator>(
        &particle_system,
        player->get_x(), player->get_y(),
        0.0f, 0.0f, // vx, vy
        0.0f,       // angle
        20.0f,      // speed
        60.0f,      // lifespan
        4,          // size
        WHITE,      // color
        60.0f,       // rate
        30.0f, //variance of x
        20.0f, //variance of y
        1.0f, //variance of vx
        1.0f //variance of vy
    );
    particle_system.add_generator(player_particles.get());

    for (int i = 1; i <= 6; i++) {
        std::string name = "note_" + std::to_string(i) + ".png";
        Texture2D tex = game.get_texture(name);
        if (tex.id != 0) {
            player_particles->owned_textures.push_back(tex);
        }
    }
    for (auto& t : player_particles->owned_textures) {
        player_particles->textures.push_back(&t);
    }
    loadMapFromJson();

}

void MapDisplay::tick() {
    if (camera) camera->begin_mode();
    if (debug) {

        if (Renderer::is_key_down(340) ){
            Vector2 mousePos = Renderer::get_mouse_pos();
            mousePos = Renderer::get_screen_to_world_2d(mousePos, camera->get_camera());
            place_block(mousePos.x, mousePos.y, current_block);
        }
        if (Renderer::is_mouse_button_down(1)) {
            Vector2 mousePos = Renderer::get_mouse_pos();
            mousePos = Renderer::get_screen_to_world_2d(mousePos, camera->get_camera());
            place_block(mousePos.x, mousePos.y, -1);
        }

        for (int i = 48; i <= 57; i++) {
            if (Renderer::is_key_down(i)) {
                current_block = i - 48;
                break;
            }
        }

        if (Renderer::is_key_pressed(KEY_ENTER)) {
            saveMapToJson();
            std::cout << "clicked enter";
        }
        if (Renderer::is_key_pressed(KEY_BACKSPACE)) {
            loadMapFromJson();
            std::cout << "clicked backspace";
        }
    }
    Renderer::draw_rectangle(0, 0, 1920, 1080, Renderer::blue);

    /////////////////////////////////////////////// light stuff
    Vector2 light_world_pos{light.position_radius.x, light.position_radius.y};
    light_world_pos = {
            player->get_x() + static_cast<float>(player->size) * 0.5f,
            player->get_y() + static_cast<float>(player->size) * 0.5f
        };
    const Vector2 light_screen_pos = GetWorldToScreen2D(light_world_pos, camera->get_camera());
    light.position_radius = {light_screen_pos.x, light_screen_pos.y, light.position_radius.z};


    const Vector3 light_positions[1] = {light.position_radius};
    const Vector4 light_colours[1] = {ColorNormalize(light.color)};
    const int num_lights = 1;
    const float ambient = 0.0f; //how much stuff is visible when not in tadius of light
    Renderer::set_lighting_uniforms(light_positions, light_colours, num_lights, ambient);


    int viable_tiles[9][2] = {};
    int tile_index = 0;
    const std::array<int, 2> tile_pos = player -> get_tile(tile_size);
    for (int i = 0; i < height_in_tiles; i++) {
        for (int j = 0; j < width_in_tiles; j++) {
            if (!coll_objects[i][j]) continue;

            coll_objects[i][j]->tick(game.get_delta_time());
            if (!coll_objects[i][j] -> has_collision) continue;
            if (tile_pos[0] -1 > j || j > tile_pos[0] +1) continue; //only check collision if player is close to the tile
            if (tile_pos[1] -1 > i || i > tile_pos[1] +1) continue;
            // Renderer::draw_rectangle(j*tile_size, i*tile_size, tile_size, tile_size, ColorAlpha(BLUE, 0.5f));
            viable_tiles[tile_index][0] = i;
            viable_tiles[tile_index][1] = j;
            tile_index++;
        };
    }
    int max_overlap = 0;
    int max_tile[2] ={};
    const std::array<int, 3> pos = player -> get_pos();

    if (max_overlap == 0) player->update_archive();
    for (int k = 0; k < tile_index; k++) {
        int i = viable_tiles[k][0];
        int j = viable_tiles[k][1];
        handle_collision(i, j);

    }


    for (const auto& interact_obj : game.interaction_objects) {
        if (interact_obj && player) {
            DialogResult res = interact_obj->tick(player->get_x(), player->get_y(), game.get_delta_time(), camera ? &camera->get_camera() : nullptr);
            if (res == DialogResult::No) {
                auto display = std::make_unique<CombatDisplay>(game, interact_obj.get());
                game.request_display_change(std::move(display));
            }
            else if (res == DialogResult::Yes) {
                player->collision_nudge(2, 1200);
            }
        }
    }

    if (player) {
        player->tick(static_cast<float>(game.get_delta_time()));
        if (camera) camera->set_target({player->get_x(), player->get_y()});

        auto mv = Renderer::get_movement();
        if (mv.first != 0 || mv.second != 0) {
            player_particles->start();
            player_particles->edit(player->get_x() + player->size/2, player->get_y() + player->size/2, 0, 0);
        } else {
            player_particles->stop();
        }
    }

    particle_system.update(static_cast<float>(game.get_delta_time()));


    if (player) {
        particle_system.draw();
    }

#ifndef NDEBUG
    const int light_center_x = light_world_pos.x;
    const int light_center_y = light_world_pos.y;
    const float light_radius = light.position_radius.z/2;

    Renderer::draw_circle_lines(light_center_x, light_center_y, light_radius, ColorAlpha(YELLOW, 0.9f));
#endif

    if (camera) {
        camera->update(static_cast<float>(game.get_delta_time()));
        GameCamera::end_mode();
    }
}

void MapDisplay::place_block(int x, int y, int type, const std::optional<int> id, const std::string& file) {
    int tile_x = x / tile_size;
    int tile_y = y / tile_size;
    if (tile_x >= 0 && tile_x < width_in_tiles && tile_y >= 0 && tile_y < height_in_tiles) {
        if (type == -1) {
            coll_objects[tile_y][tile_x].reset();
        } else {
            Texture2D tilesheet = game.get_texture(file);
            coll_objects[tile_y][tile_x] = std::make_unique<CollisionObject>(
                tile_x * tile_size, tile_y * tile_size, tile_size, tile_size, id.value_or(current_block), tilesheet, file, *this);
        }
    }
}

void MapDisplay::handle_collision(int i, int j)
{
    const std::array<int, 3> pos = player->get_pos();

    CollisionObject* obj = coll_objects[i][j].get();

    if (!obj->collision(pos[0], pos[1], pos[2]))
        return;

    auto params = obj->get_parameters();

    int tile_x = params[0];
    int tile_y = params[1];
    int tile_w = params[2];
    int tile_h = params[3];

    int player_x = pos[0];
    int player_y = pos[1];
    int player_size = pos[2];

    int player_left   = player_x;
    int player_right  = player_x + player_size;
    int player_top    = player_y;
    int player_bottom = player_y + player_size;

    int tile_left   = tile_x;
    int tile_right  = tile_x + tile_w;
    int tile_top    = tile_y;
    int tile_bottom = tile_y + tile_h;

    int overlap_left   = player_right  - tile_left;
    int overlap_right  = tile_right    - player_left;
    int overlap_top    = player_bottom - tile_top;
    int overlap_bottom = tile_bottom   - player_top;

    int min_overlap = overlap_left;
    int direction = 0;

    if (overlap_right < min_overlap) {
        min_overlap = overlap_right;
        direction = 1;
    }

    if (overlap_top < min_overlap) {
        min_overlap = overlap_top;
        direction = 2;
    }

    if (overlap_bottom < min_overlap) {
        min_overlap = overlap_bottom;
        direction = 3;
    }

    switch (direction)
    {
        case 0: // push left
            player->collision_nudge(2, tile_left);
            break;

        case 1: // push right
            player->collision_nudge(3, tile_right);
            break;

        case 2: // push up
            player->collision_nudge(0, tile_top);
            break;

        case 3: // push down
            player->collision_nudge(1, tile_bottom);
            break;
    }
}

