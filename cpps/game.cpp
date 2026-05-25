#include "../headers/game.h"
#include <utility>
#include "../headers/display.h"
#include "../headers/camera.h"
#include "../headers/start_display.h"
#include "../headers/game_display.h"
#include "../headers/renderer.h"
#include "../headers/assets.h"
#include <iostream>
#include <typeinfo>
#include <array>
#include "../headers/sequence.h"

Game::Game(int width, int height): width(width), height(height)
{
    images = load_all_images("Resources/Images");
}

Game::~Game()
{
    unload_all_images(images);
};

void Game::set_display(std::unique_ptr<Display> new_display) {
    display = std::move(new_display);
}

void Game::request_display_change(std::unique_ptr<Display> new_display) {
    pending_display = std::move(new_display);
}

Display* Game::get_display() const {
    return display.get();
}

GameCamera* Game::get_camera() const {
    return camera.get();
}

double Game::get_delta_time() const {
    return delta_time;
}

void Game::init() {
    if (!camera) {
        camera = std::make_unique<GameCamera>(width, height);
    }

    if (!display) {
        set_display(std::make_unique<StartDisplay>(*this));
    }
    display->init();
    images = load_all_images("Resources/Images");
    sequence=std::make_unique<Sequence>(std::vector{1,2,3});

}

double delta_time = 0.0f;



void Game::tick(){
    sequence->test();
    sequence->get_key();
    sequence->progress();


    if (pending_display) {
        set_display(std::move(pending_display));
        display->init();

    }
    delta_time = Renderer::get_delta_time() * 1000;
    Renderer::begin_drawing();
    camera->begin_mode();
    Renderer::clear_background(Renderer::black);

    if (!images.empty() && images[0].tex.id != 0) {
        Renderer::DrawImage(images[0].tex, 100, 100);
    } else {
        DrawText("No images loaded", 20, 20, 20, RED);
    }

    if (display) {
        display->tick();
    }
    Vector2 m= Renderer::get_mouse_pos();
    std::cout<<m.x<<" "<<m.y<<std::endl;
    std::array<int,3> clicks{};
    clicks = Renderer::get_mouse_clicks();
    std::cout<<clicks[0]<<" "<<clicks[1]<<" "<<clicks[2]<<std::endl;
    Renderer::draw_fps(10, 10);

    GameCamera::end_mode();

#ifndef NDEBUG
    Renderer::draw_text(typeid(*display).name(), 200, 10, 20, Renderer::white );

#endif
    Renderer::end_drawing();
};
