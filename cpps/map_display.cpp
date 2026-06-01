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
        500.0f,
        200.0f,
        game.get_texture("front.png"),
        game.get_texture("back.png"),
        game.get_texture("side.png")

    );

    interact_obj = std::make_unique<InteractionObject>(600.0f, 300.0f, false, 100.0f, "GET OUT!!! IM 13 YOU PERVERT",  game.get_texture("Sigma_salto.png"));

    light.color = Renderer::blue;
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
        GREEN,      // color
        60.0f       // rate
    );
    particle_system.add_generator(player_particles.get());
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
            place_block(mousePos.x, mousePos.y, 0);
        }
    }
    // Renderer::draw_rectangle(0, 0, 1920, 1080, Renderer::white);

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
    /////////////////////////////////////////////

    bool collided = false;

    for (int i = 0; i < height_in_tiles; i++) {
        for (int j = 0; j < width_in_tiles; j++) {
            if (!coll_objects[i][j]) continue;

            coll_objects[i][j]->tick(game.get_delta_time());
            if (!coll_objects[i][j] -> has_collision) continue;

            if (handle_collision(i, j)) collided = true;
        }
    }
    if (!collided) player->update_archive();



    if (interact_obj && player) {
        DialogResult res = interact_obj->tick(player->get_x(), player->get_y(), game.get_delta_time(), camera ? &camera->get_camera() : nullptr);
        if (res == DialogResult::No) {
            auto display = std::make_unique<CombatDisplay>(game);
            game.request_display_change(std::move(display));
        }
        else if (res == DialogResult::Yes) {
            player->collision_nudge(0, 1000);
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

void MapDisplay::place_block(int x, int y, int type) {
    int tile_x = x / tile_size;
    int tile_y = y / tile_size;
    if (tile_x >= 0 && tile_x < width_in_tiles && tile_y >= 0 && tile_y < height_in_tiles) {
        if (type == 0) {
            coll_objects[tile_y][tile_x].reset();
        } else {
            Texture2D tilesheet = game.get_texture("tekstury.png");
            coll_objects[tile_y][tile_x] = std::make_unique<CollisionObject>(
                tile_x * tile_size, tile_y * tile_size, tile_size, tile_size, tile_x, tilesheet, *this);
        }
    }

}

bool MapDisplay::handle_collision(int i, int j) {
    const std::array<int, 3> pos = player -> get_pos();
    const std::array<int, 3> arch_pos = player -> get_archive();
    if (!coll_objects[i][j] -> collision(pos[0], pos[1], pos[2])) return false;

    if (coll_objects[i][j] -> collision(arch_pos[0], pos[1], arch_pos[2])) { //verical
        if (pos[1] > arch_pos[1]) player->collision_nudge(0, coll_objects[i][j] -> get_parameters()[1]);
        else player->collision_nudge(1, coll_objects[i][j] -> get_parameters()[1] + coll_objects[i][j] -> get_parameters()[3]);
    }
    else if (coll_objects[i][j] -> collision(pos[0], arch_pos[1], pos[2])) { //horizontal
        if (pos[0] > arch_pos[0]) player->collision_nudge(2, coll_objects[i][j] -> get_parameters()[0]);
        else player->collision_nudge(3, coll_objects[i][j] -> get_parameters()[0] + coll_objects[i][j] -> get_parameters()[2]);
    }
    else player -> rollback_archive();
    return true;
}

