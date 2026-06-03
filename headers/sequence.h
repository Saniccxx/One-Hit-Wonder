#pragma once
#include <array>
#include <vector>
#include "renderer.h"
#include <unordered_map>
class Game;

class Sequence {
    public:
    int completed;
    float compleation_level;
    int level;
    void progress();

    void play();
    void draw_progress_bar();
    void check();
    Game& game;
    std::unordered_map<int, Sound> plays ;
    std::unordered_map<int, float> volumes;
    std::vector<int> notes;
    std::vector<int> durations;

    void draw_falling_keys();

    Sequence(Game& game,std::vector<int> notes,std::vector<int> durations);
    ~Sequence() = default;
    private:

    int global_timer;
    std::vector<int> target_times;

    int i;

    int offset;
    int timer;
    int length;

    float flevel;
    int current_note;

    int current;
    int end;

    Sound C;
    Sound D;
    Sound E ;
    Sound F ;
    Sound G ;
    Sound A ;
    Sound B ;
    Sound C2 ;
    std::unordered_map<int, int> keys={{KEY_A,0},{KEY_S,1},{KEY_D,2},{KEY_F,3},{KEY_J,4},{KEY_K,5},{KEY_L,6},{KEY_SEMICOLON,7}};
    float bar_progress;
    int bar_changing=0;
    float d_bar=0.0f;
    float bar_change_speed=10;
    int bar_width=200;
    int bar_height=30;
    Color bar_color=GREEN;


    void test();
    void add_level();
    void get_key();





};


