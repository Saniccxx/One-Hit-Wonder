#pragma once
#include <array>
#include <vector>
#include "renderer.h"
#include <unordered_map>
class Game;

class Sequence {
    public:
    int i;
    Game& game;
    int offset;
    int timer;
    int length;
    int level;
    float flevel;
    int current_note;
    int completed;
    int current;
    int end;
    float compleation_level;
    Sound C;
    Sound D;
    Sound E ;
    Sound F ;
    Sound G ;
    Sound A ;
    Sound B ;
    Sound C2 ;
    std::unordered_map<int, int> keys={{KEY_T,0},{KEY_Y,1},{KEY_U,2},{KEY_I,3},{KEY_O,4},{KEY_P,5},{KEY_LEFT_BRACKET,6},{KEY_RIGHT_BRACKET,7}};
    std::unordered_map<int, Sound> plays ;
    std::unordered_map<int, float> volumes;
    std::vector<int> notes;
    std::vector<int> durations;
    Sequence(Game& game,std::vector<int> notes,std::vector<int> durations);
    void test();
    void add_level();
    ~Sequence() = default;
    void get_key();
    void progress();
    void check();
    void play();

};


