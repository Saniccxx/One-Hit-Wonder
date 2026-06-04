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
    notes = {

        // 0. Mary Had a Little Lamb
        {2,1,0,1,2,2,2,1,1,1,2,4,4},
        {   // Line 1: "Twinkle, twinkle, little star"
        0, 0, 4, 4, 5, 5, 4,
        // Line 2: "How I wonder what you are"
        3, 3, 2, 2, 1, 1, 0,
        // Line 3: "Up above the world so high, like a diamond in the sky"
        4, 4, 3, 3, 2, 2, 1
    },

    // ── 1. Happy Birthday To You (Traditional, public domain) ────────────────
    {   // Line 1: "Happy birthday to you"
        0, 0, 1, 0, 3, 2,
        // Line 2: "Happy birthday to you"
        0, 0, 1, 0, 4, 3,
        // Line 3: "Happy birthday, dear [Name] — happy birthday to you"
        0, 0, 7, 5, 3, 2, 1
    },

    // ── 2. Jingle Bells (J.L. Pierpont, 1857, public domain) — chorus ────────
    {   // Line 1: "Jingle bells, jingle bells,"
        2, 2, 2, 2, 2, 2,
        // Line 2: "Jingle all the way!"
        2, 4, 0, 1, 2,
        // Line 3: "Oh what fun it is to ride in a one-horse open sleigh!"
        3, 3, 2, 2, 1, 4
    },

    // ── 3. Ode to Joy (Beethoven, 1824, public domain) — main theme ──────────
    {   // Line 1: first phrase  (E E F G | G F E D)
        2, 2, 3, 4, 4, 3, 2, 1,
        // Line 2: resolution   (C C D E | E D D)
        0, 0, 1, 2, 2, 1, 1,
        // Line 3: third phrase (D D E C | D E F E D C)
        1, 1, 2, 0, 1, 2, 3, 2, 1, 0
    },

    // ── 4. Amazing Grace (John Newton, 1772, public domain) ──────────────────
    {   // Line 1: "Amazing grace, how sweet the sound"
        0, 4, 4, 2, 4, 2, 0,
        // Line 2: "That saved a wretch like me"
        0, 4, 4, 5, 4, 2,
        // Line 3: "I once was lost but now am found, was blind but now I see"
        2, 0, 2, 4, 2, 0
    },

    // ── 5. Mary Had a Little Lamb (Traditional, public domain) ───────────────
    {   // Line 1: "Mary had a little lamb"
        2, 1, 0, 1, 2, 2, 2,
        // Line 2: "Little lamb, little lamb"
        1, 1, 1, 2, 4, 4,
        // Line 3: "Mary had a little lamb, its fleece was white as snow"
        2, 1, 0, 1, 2, 2, 2, 1, 1, 2, 1, 0
    },

    // ── 6. Row, Row, Row Your Boat (Traditional, public domain) ──────────────
    {   // Line 1: "Row, row, row your boat"
        0, 0, 0, 1, 2,
        // Line 2: "Gently down the stream"
        2, 1, 2, 3, 4,
        // Line 3: "Merrily merrily merrily merrily, life is but a dream"
        7, 7, 7, 4, 4, 4, 2, 2, 2, 0, 4, 3, 2, 1, 0
    },

    // ── 7. When the Saints Go Marching In (Traditional, public domain) ────────
    {   // Line 1: "Oh when the saints"
        0, 2, 3, 4,
        // Line 2: "Oh when the saints"
        0, 2, 3, 4,
        // Line 3: "Go marching in — oh Lord, I want to be in that number"
        0, 2, 3, 4, 2, 0, 2, 4, 3, 2
    },

    // ── 8. Yankee Doodle (Traditional, public domain) — transposed to C ───────
    // Original key: G major.  Mapping: G→C(0) A→D(1) B→E(2) C→F(3) D→G(4) F#→B(6)
    {   // Line 1: "Yankee Doodle went to town, a-riding on a pony"
        0, 0, 1, 6, 0, 1, 2, 0,
        // Line 2: "Stuck a feather in his cap and called it macaroni"
        1, 2, 3, 2, 1, 0, 6, 0, 1, 2, 3, 1, 0,
        // Line 3: "Yankee Doodle keep it up, Yankee Doodle dandy"
        2, 2, 2, 0, 1, 2, 3
    },

    // ── 9. London Bridge is Falling Down (Traditional, public domain) ─────────
    {   // Line 1: "London Bridge is falling down"
        4, 5, 4, 3, 2, 3, 4,
        // Line 2: "Falling down, falling down"
        1, 2, 3, 2, 3, 4,
        // Line 3: "London Bridge is falling down, my fair lady"
        4, 5, 4, 3, 2, 4, 2, 0
    },
{
    // "Never gonna give you up, never gonna let you down"
    4,4,5,4,3,2, 4,4,5,4,3,1,
    // "Never gonna run around and desert you"
    4,4,5,4,3,2,3, 2,1,0,
    // "Never gonna make you cry, never gonna say goodbye"
    4,4,5,4,3,2, 4,4,5,4,3,1,
    // "Never gonna tell a lie and hurt you"
    4,4,5,4,3,2,3, 2,1,0,

    // --- repeat ---
    4,4,5,4,3,2, 4,4,5,4,3,1,
    4,4,5,4,3,2,3, 2,1,0,
    4,4,5,4,3,2, 4,4,5,4,3,1,
    4,4,5,4,3,2,3, 2,1,0,

    // --- bridge ---
    5,4,3,4,5,4,3,2,
    5,4,3,4,5,4,3,2,
    3,4,5,4,3,2,1,0,
    2,3,4,3,2,1,0
}
    };

    durations = {

        // 0
        {50,50,50,50,50,50,100,50,50,100,50,50,100},
        {   // Line 1
        50, 50, 50, 50, 50, 50, 100,
        // Line 2
        50, 50, 50, 50, 50, 50, 100,
        // Line 3
        50, 50, 50, 50, 50, 50, 100
    },

    // ── 1. Happy Birthday To You ─────────────────────────────────────────────
    {   // Line 1  (dotted-eighth + sixteenth pickup)
        37, 13, 50, 50, 50, 100,
        // Line 2
        37, 13, 50, 50, 50, 100,
        // Line 3
        37, 13, 50, 50, 75, 25, 150
    },

    // ── 2. Jingle Bells ──────────────────────────────────────────────────────
    {   // Line 1
        50, 50, 100, 50, 50, 100,
        // Line 2
        50, 50, 50, 50, 200,
        // Line 3
        50, 50, 50, 50, 50, 100
    },

    // ── 3. Ode to Joy ────────────────────────────────────────────────────────
    {   // Line 1
        50, 50, 50, 50, 50, 50, 50, 100,
        // Line 2
        50, 50, 50, 75, 25, 50, 100,
        // Line 3
        50, 50, 50, 50, 50, 50, 50, 50, 50, 100
    },

    // ── 4. Amazing Grace (3/4 time) ──────────────────────────────────────────
    {   // Line 1
        50, 100, 75, 25, 100, 50, 150,
        // Line 2
        50, 100, 75, 25, 100, 150,
        // Line 3
        100, 50, 50, 150, 50, 200
    },

    // ── 5. Mary Had a Little Lamb ────────────────────────────────────────────
    {   // Line 1
        50, 50, 50, 50, 50, 50, 100,
        // Line 2
        50, 50, 100, 50, 50, 100,
        // Line 3
        50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 100
    },

    // ── 6. Row, Row, Row Your Boat ───────────────────────────────────────────
    {   // Line 1
        100, 100, 75, 25, 100,
        // Line 2
        75, 25, 75, 25, 200,
        // Line 3  (eighth-note triplet merrily run → quarter-note cadence)
        25, 25, 25, 25, 25, 25, 25, 25, 25, 50, 50, 50, 50, 50, 100
    },

    // ── 7. When the Saints Go Marching In ────────────────────────────────────
    {   // Line 1
        50, 50, 50, 100,
        // Line 2
        50, 50, 50, 100,
        // Line 3
        50, 50, 50, 100, 50, 50, 50, 50, 50, 100
    },

    // ── 8. Yankee Doodle ─────────────────────────────────────────────────────
    {   // Line 1
        50, 50, 50, 50, 50, 50, 50, 100,
        // Line 2
        50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 100,
        // Line 3
        50, 50, 50, 50, 50, 50, 100
    },

    // ── 9. London Bridge is Falling Down ─────────────────────────────────────
    {   // Line 1
        50, 50, 50, 50, 50, 50, 100,
        // Line 2
        50, 50, 100, 50, 50, 100,
        // Line 3
        50, 50, 50, 50, 100, 50, 50, 200
    },

{
    // "Never gonna give you up, never gonna let you down"
    20,20,20,20,20,50, 20,20,20,20,20,60,
    // "Never gonna run around and desert you"
    20,20,20,20,20,20,20, 30,30,60,
    // "Never gonna make you cry, never gonna say goodbye"
    20,20,20,20,20,50, 20,20,20,20,20,60,
    // "Never gonna tell a lie and hurt you"
    20,20,20,20,20,20,20, 30,30,60,

    // --- repeat ---
    20,20,20,20,20,50, 20,20,20,20,20,60,
    20,20,20,20,20,20,20, 30,30,60,
    20,20,20,20,20,50, 20,20,20,20,20,60,
    20,20,20,20,20,20,20, 30,30,80,

    // --- bridge ---
    30,30,30,30,30,30,30,60,
    30,30,30,30,30,30,30,60,
    30,30,30,30,30,30,30,60,
    30,30,30,30,30,30,200
}
};


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
