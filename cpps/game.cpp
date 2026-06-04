#include "game.h"
#include <utility>
#include "display.h"
#include "camera.h"
#include "start_display.h"
#include "pause_display.h"
#include "combat_display.h"
#include "map_display.h"
#include "renderer.h"
#include "assets.h"
#include <iostream>
#include <typeinfo>
#include <array>
#include <raylib.h>


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
    std::cout << "Game::init() called." << std::endl;

    // Set window icon
    std::cout << "Attempting to load icon from: Resources/Images/logo.png" << std::endl;
    Image icon = LoadImage("Resources/Images/logo.png");
    if (icon.data) {
        std::cout << "Icon loaded successfully. Setting window icon." << std::endl;
        SetWindowIcon(icon);
        UnloadImage(icon);
        std::cout << "Window icon set and image unloaded." << std::endl;
    } else {
        std::cerr << "Warning: Could not load logo.png for window icon. Check file path and existence." << std::endl;
    }

    images = load_all_images("Resources/Images");
    sounds = load_all_sounds("Resources");
    notes = {
        // 3. We Will Rock You
        {
            3,2,1,0,1,1,3,2,1,0,1,1,3,2,1,0,1,1,3,2,1,0,1,1,
        },
{
    5, 6, 7,  5, 6, 7,  5, 4, 3, 4,  5, 4, 3, 4, 5, 2,
    5, 6, 7,  5, 6, 7,  5, 4, 3, 4,  5, 4, 3, 4, 5, 2
},
        // 1. Never Gonna Give You Up
        {
            {1, 2, 3, 1, 5, 5, 4    ,0, 1, 2, 0, 4, 4, 3, 2, 1,    1, 2, 3, 1, 4, 3, 4, 2, 1, 0 ,   0, 4, 3 ,   1, 2, 3, 1, 5, 5, 4 ,   0, 1, 2, 0, 7, 2, 3, 2, 1 ,  1, 2, 3, 1, 3, 4, 2, 1, 0  ,  0, 4, 3},
        },
        // 2. All Star
        {
            4, 6, 5, 4, 7, 6, 5, 4, 6, 5, 4, 3, 4,
            4, 6, 5, 4, 7, 6, 5, 4, 6, 5, 4, 3, 4,
            3, 3, 3, 3, 2, 0, 0,       2, 2, 1, 1, 0, 1, 0,
            4, 6, 5, 4, 7, 6, 5, 4, 6, 5, 4, 3, 4,
            3, 3, 3, 3, 2, 0, 0,       2, 2, 1, 1, 0, 1, 0
        },


        // 4. Let It Be
        {
            4, 5, 4, 2, 4, 5, 4, 2,    2, 2, 1, 0, 1, 0, 0,
            4, 5, 4, 2, 4, 5, 4, 2,    2, 2, 1, 0, 1, 0, 0,
            4, 5, 4, 2, 4, 5, 4, 2,    2, 2, 1, 0, 1, 0, 0,
            4, 5, 4, 2, 4, 5, 4, 2,    2, 2, 1, 0, 1, 0, 0
        },
        // 5. Take On Me

        // 6. Sweet Caroline
        {
            0, 3, 4,    4, 5, 6,    7, 7, 6, 5, 4, 3, 4,
            0, 3, 4,    7, 7, 6, 5, 4, 3, 2,
            0, 3, 4,    4, 5, 6,    7, 7, 6, 5, 4, 3, 4,
            0, 3, 4,    7, 7, 6, 5, 4, 3, 2
        },
        // 7. Don't Stop Believin'
        {
            2, 2, 2, 3, 2, 0,    2, 2, 2, 3, 2, 1,    0, 2, 4, 5,    4, 3, 2,
            2, 2, 2, 3, 2, 0,    2, 2, 2, 3, 2, 1,    0, 2, 4, 5,    4, 3, 2
        },
        // 8. Livin' On A Prayer
        {
            4, 4, 5, 6, 6,          4, 4, 2, 1, 2,
            4, 4, 5, 6, 6, 5, 4, 5, 4, 4, 2, 1, 2,
            4, 4, 5, 6, 6,          4, 4, 2, 1, 2,
            4, 4, 5, 6, 6, 5, 4, 5, 4, 4, 2, 1, 2
        },
        // 9. I Want It That Way
        {
            4, 5, 6,    6, 6, 6, 6, 5, 4, 5,    4, 5, 6,    6, 6, 6, 6, 5, 4, 5,
            4, 5, 6,    6, 6, 6, 5, 4, 3, 2,    2, 3, 4, 4, 4,
            4, 5, 6,    6, 6, 6, 6, 5, 4, 5,    4, 5, 6,    6, 6, 6, 6, 5, 4, 5,
            4, 5, 6,    6, 6, 6, 5, 4, 3, 2,    2, 3, 4, 4, 4
        },
        // 10. I Gotta Feeling
        {
            4, 4, 4, 7,    7, 6, 5, 4, 4, 4, 5, 6,
            7, 6, 5, 4, 4, 4, 5, 6,    7, 6, 5, 4, 4, 4, 5, 4, 2,
            4, 4, 4, 7,    7, 6, 5, 4, 4, 4, 5, 6,
            7, 6, 5, 4, 4, 4, 5, 6,    7, 6, 5, 4, 4, 4, 5, 4, 2
        }
    };

    durations = {
        // 3. We Will Rock You
        {
            80, 80,80,80,40,280,80, 80,80,80,40,280,80, 80,80,80,40,280,80, 80,80,80,40,280,
        },
        // 5. Take On Me
        {
            50, 50, 100, 50, 50, 100, 50, 50, 50, 150, 50, 50, 50, 50, 50, 200,
            50, 50, 100, 50, 50, 100, 50, 50, 50, 150, 50, 50, 50, 50, 50, 200
        },
        // 1. Never Gonna Give You Up
{
    40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
    40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
    40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
    40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
    40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
    40, 40, 40, 40, 40, 40, 40,
},
        // 2. All Star
        {
            50, 50, 25, 25, 50, 50, 25, 25, 50, 50, 50, 50, 100,
            50, 50, 25, 25, 50, 50, 25, 25, 50, 50, 50, 50, 100,
            50, 50, 50, 50, 50, 50, 100,  50, 50, 50, 50, 50, 50, 100,
            50, 50, 25, 25, 50, 50, 25, 25, 50, 50, 50, 50, 100,
            50, 50, 50, 50, 50, 50, 100,  50, 50, 50, 50, 50, 50, 100
        },

        // 4. Let It Be
        {
            50, 50, 100, 100, 50, 50, 100, 100,  50, 50, 50, 50, 50, 50, 150,
            50, 50, 100, 100, 50, 50, 100, 100,  50, 50, 50, 50, 50, 50, 150,
            50, 50, 100, 100, 50, 50, 100, 100,  50, 50, 50, 50, 50, 50, 150,
            50, 50, 100, 100, 50, 50, 100, 100,  50, 50, 50, 50, 50, 50, 150
        },

        // 6. Sweet Caroline
        {
            50, 50, 150,   50, 50, 150,   50, 50, 50, 50, 50, 50, 150,
            50, 50, 150,   50, 50, 50, 50, 50, 50, 150,
            50, 50, 150,   50, 50, 150,   50, 50, 50, 50, 50, 50, 150,
            50, 50, 150,   50, 50, 50, 50, 50, 50, 150
        },
        // 7. Don't Stop Believin'
        {
            50, 50, 50, 50, 50, 150,  50, 50, 50, 50, 50, 150,  50, 50, 50, 150,  50, 50, 150,
            50, 50, 50, 50, 50, 150,  50, 50, 50, 50, 50, 150,  50, 50, 50, 150,  50, 50, 150
        },
        // 8. Livin' On A Prayer
        {
            100, 50, 50, 50, 150,  100, 50, 50, 50, 150,
            50, 50, 50, 50, 50, 50, 50, 100, 100, 50, 50, 50, 150,
            100, 50, 50, 50, 150,  100, 50, 50, 50, 150,
            50, 50, 50, 50, 50, 50, 50, 100, 100, 50, 50, 50, 150
        },
        // 9. I Want It That Way
        {
            50, 50, 100,  50, 50, 50, 50, 50, 50, 100,  50, 50, 100,  50, 50, 50, 50, 50, 50, 100,
            50, 50, 100,  50, 50, 50, 50, 50, 50, 100,  50, 50, 50, 50, 150,
            50, 50, 100,  50, 50, 50, 50, 50, 50, 100,  50, 50, 100,  50, 50, 50, 50, 50, 50, 100,
            50, 50, 100,  50, 50, 50, 50, 50, 50, 100,  50, 50, 50, 50, 150
        },
        // 10. I Gotta Feeling
        {
            50, 50, 50, 150,  50, 50, 50, 50, 50, 50, 50, 100,
            50, 50, 50, 50, 50, 50, 50, 100,  50, 50, 50, 50, 50, 50, 50, 50, 150,
            50, 50, 50, 150,  50, 50, 50, 50, 50, 50, 50, 100,
            50, 50, 50, 50, 50, 50, 50, 100,  50, 50, 50, 50, 50, 50, 50, 50, 150
        }
    };
    level=1.0f;


    interaction_objects.push_back(std::move(std::make_unique<InteractionObject>(
        700.0f, 550.0f, 100.0f, get_texture("enemy.png"), notes[level-1], durations[level-1])));


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