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



Game::Game(Config& config) : width(config.get_screen_width()), height(config.get_screen_height()), config(config) {}

Game::~Game()
{
    unload_all_images(images);
    unload_all_sounds(sounds);
};

void Game::set_display(std::unique_ptr<Display> new_display) {
    display = std::move(new_display);
}

void Game::request_display_change(std::unique_ptr<Display> new_display) {
    pending_display = std::move(new_display);
}

void Game::revert_display() {
    pending_display = std::move(backup_display);
    reverting = true;
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

Sound Game::get_sound(std::string_view name) const {
    for (const auto& s : sounds) {
        if (s.path.find(name) != std::string::npos) {
            return s.sound;
        }
    }
    return {0};
}

void Game::init() {
    images = load_all_images("Resources/Images");
    sounds = load_all_sounds("Resources");
    std::vector<std::vector<int>> notes = {
    // 0. Mary Had a Little Lamb
    {2,1,0,1,2,2,2,1,1,1,2,4,4,
     2,1,0,1,2,2,2,1,1,1,2,4,4},

    // 1. Twinkle Twinkle Little Star
    {0,0,4,4,5,5,4,3,3,2,2,1,1,0,
     4,4,3,3,2,2,1,4,4,3,3,2,2,1},

    // 2. Row Row Row Your Boat
    {0,0,0,1,2,2,1,2,3,4,7,7,4,4,2,2,0,
     0,0,0,1,2,2,1,2,3,4,7,7,4,4,2,2,0},

    // 3. Frere Jacques
    {0,1,2,0,0,1,2,0,2,3,4,2,3,4,
     4,5,4,3,2,4,4,5,4,3,2,0},

    // 4. London Bridge
    {4,5,4,3,2,3,4,2,4,2,0,
     4,5,4,3,2,3,4,2,0,2,4},

    // 5. Baa Baa Black Sheep
    {0,0,4,4,5,5,4,3,3,2,2,1,1,0,
     4,4,3,3,2,2,1,4,4,3,3,2,2,1},

    // 6. Yankee Doodle
    {0,0,1,2,0,2,1,4,0,0,1,2,0,
     2,2,3,4,2,4,3,5,2,2,3,4,2},

    // 7. Old MacDonald
    {4,4,4,1,2,2,1,7,7,5,5,4,
     4,4,4,1,2,2,1,7,7,5,5,4},

    // 8. This Old Man
    {4,4,4,1,2,4,4,4,1,2,4,
     5,5,5,2,3,5,5,5,2,3,5},

    // 9. Skip to My Lou
    {0,2,4,4,2,0,2,4,5,4,2,0,
     0,2,4,4,2,0,2,4,5,4,2,0}
};

std::vector<std::vector<int>> durations = {
    // 0
    {50,50,50,50,50,50,100,50,50,100,50,50,100,
     50,50,50,50,50,50,100,50,50,100,50,50,150},

    // 1
    {50,50,50,50,50,50,100,50,50,50,50,50,50,100,
     50,50,50,50,50,50,100,50,50,50,50,50,50,150},

    // 2
    {50,50,100,50,50,50,50,50,50,50,100,50,50,50,50,50,100,
     50,50,100,50,50,50,50,50,50,50,100,50,50,50,50,50,150},

    // 3
    {50,50,100,100,50,50,100,100,50,50,100,50,50,150,
     50,50,50,50,50,100,50,50,50,50,50,150},

    // 4
    {50,50,50,50,50,50,100,50,50,50,150,
     50,50,50,50,50,50,100,50,50,50,150},

    // 5
    {50,50,50,50,50,50,100,50,50,50,50,50,50,100,
     50,50,50,50,50,50,100,50,50,50,50,50,50,150},

    // 6
    {50,50,50,50,50,50,50,100,50,50,50,50,150,
     50,50,50,50,50,50,50,100,50,50,50,50,150},

    // 7
    {50,50,100,50,50,50,50,50,50,50,50,150,
     50,50,100,50,50,50,50,50,50,50,50,150},

    // 8
    {50,50,100,50,100,50,50,100,50,100,150,
     50,50,100,50,100,50,50,100,50,100,150},

    // 9
    {50,50,50,100,50,50,50,100,50,50,50,150,
     50,50,50,100,50,50,50,100,50,50,50,150}
};


    interaction_objects.push_back(std::move(std::make_unique<InteractionObject>(
        940.0f, 550.0f, 100.0f,
        "GET OUT!!! IM 13 YOU PERVERT",get_texture("Sigma_salto.png"), notes[1], durations[1])));

    if (!display) {
        set_display(std::make_unique<StartDisplay>(*this));
    }
    display->init();
    int speed=1;
    // disclaimer - sequence still operates on old key T Y U...
    //sequence=std::make_unique<Sequence>(std::vector{0,2,4,4,4,4,4,5,4,2,0,2,1,0,1,2},std::vector{100/speed,100/speed,50/speed,50/speed,50/speed,50/speed,100/speed,100/speed,100/speed,100/speed,100/speed,100/speed,200/speed,100/speed,100/speed,200/speed});
    // sequence=std::make_unique<Sequence>(*this,std::vector{0,1,2},std::vector{100,100,100});
    //sequence=std::make_unique<Sequence>(std::vector{0,4,3,2,1,7,4,3,2,1,7,4,3,2,3,1},std::vector{50,50,10,10,10,50,50,10,10,10,50,50,15,15,15,100});
    //sequence=std::make_unique<Sequence>(*this,std::vector{0,1,2,1,2,3,2,1,0,0,4,0,0,0,0},std::vector{30,10,30,30,10,25,20,20,20,20,40,15,15,15,50});
    //sequence=std::make_unique<Sequence>(std::vector{0,0,4,4,5,5,4},std::vector{30,30,30,30,30,30,100});
    //sequence=std::make_unique<Sequence>(std::vector{2,2,2,4,3,2,2,2,4,3},std::vector{30,30,30,20,20,30,30,30,20,20});

    // std::cout<<sequence->completed<<std::endl;
    // std::cout<<sequence->compleation_level<<std::endl;
}


void Game::tick(){


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
        if (!reverting) backup_display = std::move(display);
        set_display(std::move(pending_display));
        if (!reverting) display->init();
        if (reverting) reverting = false, backup_display = nullptr;

    }
    delta_time = Renderer::get_delta_time() * 1000;
    Renderer::begin_drawing();
    Renderer::clear_background(Renderer::black);
    // Sound D = Renderer::load_sound("Resources/D.wav");
    // PlaySound(D);
    // sequence->check();
    //std::cout<<sequence->completed<<std::endl;
    //std::cout<<sequence->compleation_level<<std::endl;
    // sequence->play();
    // sequence->draw_progress_bar();

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
