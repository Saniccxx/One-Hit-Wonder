#include "../headers/game.h"
#include <utility>
#include "../headers/display.h"
#include "../headers/camera.h"
#include "../headers/start_display.h"
#include "../headers/pause_display.h"
#include "../headers/combat_display.h"
#include "../headers/map_display.h"
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

double Game::get_delta_time() const {
    return delta_time;
}

Texture2D Game::get_texture(std::string_view name) const {
    for (const auto& img : images) {
        if (img.path.find(name) != std::string::npos) {
            return img.tex;
        }
    }
    return {0};
}

void Game::init() {
    if (!display) {
        set_display(std::make_unique<StartDisplay>(*this));
    }
    display->init();
    images = load_all_images("Resources/Images");
    int speed=1;
    //sequence=std::make_unique<Sequence>(std::vector{0,2,4,4,4,4,4,5,4,2,0,2,1,0,1,2},std::vector{100/speed,100/speed,50/speed,50/speed,50/speed,50/speed,100/speed,100/speed,100/speed,100/speed,100/speed,100/speed,200/speed,100/speed,100/speed,200/speed});
    //sequence=std::make_unique<Sequence>(std::vector{0,1},std::vector{100,100});
    //sequence=std::make_unique<Sequence>(std::vector{0,4,3,2,1,7,4,3,2,1,7,4,3,2,3,1},std::vector{50,50,10,10,10,50,50,10,10,10,50,50,15,15,15,100});
    sequence=std::make_unique<Sequence>(*this,std::vector{0,1,2,1,2,3,2,1,0,0,4,0,0,0,0},std::vector{30,10,30,30,10,25,20,20,20,20,40,15,15,15,50});
    //sequence=std::make_unique<Sequence>(std::vector{0,0,4,4,5,5,4},std::vector{30,30,30,30,30,30,100});
    //sequence=std::make_unique<Sequence>(std::vector{2,2,2,4,3,2,2,2,4,3},std::vector{30,30,30,20,20,30,30,30,20,20});

    std::cout<<sequence->completed<<std::endl;
    std::cout<<sequence->compleation_level<<std::endl;
}


void Game::tick(){
    // Sound D = Renderer::load_sound("Resources/D.wav");
    // PlaySound(D);
    sequence->check();
    //std::cout<<sequence->completed<<std::endl;
    //std::cout<<sequence->compleation_level<<std::endl;
    sequence->play();

    if (Renderer::is_key_pressed(KEY_ESCAPE)) {
        if (paused_display && dynamic_cast<PauseDisplay*>(display.get()) != nullptr) {
            set_display(std::move(paused_display));
        } else if (!paused_display && display &&
                   (dynamic_cast<CombatDisplay*>(display.get()) != nullptr ||
                    dynamic_cast<MapDisplay*>(display.get()) != nullptr)) {
            paused_display = std::move(display);
            set_display(std::make_unique<PauseDisplay>(*this));
            display->init();
        }
    }

    if (pending_display) {
        set_display(std::move(pending_display));
        display->init();

    }
    delta_time = Renderer::get_delta_time() * 1000;
    Renderer::begin_drawing();
    Renderer::clear_background(Renderer::black);

    if (display) {
        display->tick();
    }

#ifdef NDEBUG
    Renderer::draw_text("Release mode", 67, 67, 20, Renderer::white);
#else
    Renderer::draw_text("Debug mode", 67, 67, 20, Renderer::white);
    Renderer::draw_fps(10, 10);
#endif

#ifndef NDEBUG
    Renderer::draw_text(typeid(*display).name(), 200, 10, 20, Renderer::white );

#endif
    Renderer::end_drawing();
};
