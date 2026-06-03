#pragma once
#include <array>
#include <memory>
#include <vector>
#include "renderer.h"
#include <unordered_map>
class Game;

class Sequence {
    public:
    int completed;
    float compleation_level;
    int level;
    int combo = 0;
    int score = 0;
    std::size_t next_note_to_hit = 0;
    int perfect_count = 0;
    int great_count = 0;
    int good_count = 0;
    int miss_count = 0;

    struct FloatingRating {
        std::string text;
        Color color;
        Vector2 pos;
        Vector2 vel;
        float alpha;
        float scale;
        float life;
    };
    std::vector<FloatingRating> ratings;

    void spawn_rating(const std::string& text, Color color, float x, float y);

    void progress();

    void play();
    void draw_progress_bar();
    void draw_progress_bar_chords(int x,int y,int w,int h);
    void check();
    Game& game;
    std::unordered_map<int, Sound> plays ;
    std::unordered_map<int, float> volumes;
    std::vector<int> notes;
    std::vector<int> durations;

    void draw_falling_keys();

    Sequence(Game& game,std::vector<int> notes,std::vector<int> durations);
    ~Sequence() = default;
    Sequence()=default;
    private:

    float global_timer;
    std::vector<int> target_times;

    int i;

    int offset;
    float timer;
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

class Queue {
    public:
    Game& game;
    std::vector<std::vector<std::vector<int>>> songs;
    Sequence currrent_sequence;
    int completed=0;

    Queue(Game& game,std::vector<std::vector<std::vector<int>>>songs);
};

