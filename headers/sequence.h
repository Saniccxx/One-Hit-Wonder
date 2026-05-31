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
    Sequence(Game& game,std::vector<int> notes,std::vector<int> durations);
    ~Sequence() = default;
    private:

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
    std::unordered_map<int, int> keys={{KEY_T,0},{KEY_Y,1},{KEY_U,2},{KEY_I,3},{KEY_O,4},{KEY_P,5},{KEY_LEFT_BRACKET,6},{KEY_RIGHT_BRACKET,7}};
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


