#include "../headers/sequence.h"
#include "../headers/renderer.h"
#include <iostream>
#include "raylib.h"
#include "../headers/game.h"
#include <cmath>

Sequence::Sequence(Game& game,std::vector<int> notes,std::vector<int> durations): game(game),notes(notes),durations(durations)   {

    for (i=0; i<notes.size(); i++) {
        volumes[i]=0;
    }
    current=0;
    end=0;
    offset=20;
    compleation_level=0.0f;
    C = game.get_sound("C.wav");
    D = game.get_sound("D.wav");
    E = game.get_sound("E.wav");
    F = game.get_sound("F.wav");
    G = game.get_sound("G.wav");
    A = game.get_sound("A.wav");
    B = game.get_sound("B.wav");
    C2 = game.get_sound("C2.wav");
    plays = {
        {0, C},
        {1, D},
        {2, E},
        {3, F},
        {4, G},
        {5, A},
        {6, B},
        {7, C2}
    };
    length=notes.size();
    level=0;
    current_note=-1;
    completed=0;
    timer=0;


    global_timer = 0;
    int acc = 0;
    for (int d : durations) {
        target_times.push_back(acc);
        acc += d;
    }

}
void Sequence::test() {


}
void Sequence::add_level() {
    level+=1;
}
void Sequence::get_key() {
    int a=0;
    for (auto& pair : keys) {
        if (Renderer::is_key_pressed(pair.first)) {
            int index = pair.second;
            std::cout << "Key index " << index << " pressed\n";
            a=1;
            current_note=index;
        }
    if (Renderer::is_key_pressed(KEY_BACKSPACE)) {
        a=1;
        current_note=-2;
    }





    }
    if (a==0) {
        current_note=-1;
    }

}
void Sequence::progress() {

    if (current_note>=0){

        std::cout<<current_note<<std::endl;
        if (notes.size() > 0) std::cout<<notes[0]<<std::endl;

        if (level < length && notes[level]==current_note) {

            level++;
            flevel=level;
            compleation_level=flevel/length;
            std::cout<<"Upgrade, compleation_level"<<compleation_level<<std::endl;
            if (level==length) {
                completed=1;
                std::cout << "Completed ";
            }
        }
        else if (level >= length) {}
        else {
            std::cout << "Wrong note, reset";
            level=0;
            compleation_level=0;
        }
    }
    else if (current_note==-2) {
        std::cout << "Reset";
        level=0;
        compleation_level=0;
    }
};
void Sequence::check() {
    get_key();
    progress();
}
void Sequence::play() {


    if (end==0) {
        global_timer++;

        if (timer==0) {

            Renderer::set_sound_volume(plays[notes[current]], volumes[notes[current]]);
            Renderer::play_sound(plays[notes[current]]);

        }
        if (timer<=offset and timer>0) {
            volumes[notes[current]]+=1.0f/offset;
            //std::cout<<"change"<<std::endl;
            Renderer::set_sound_volume(plays[notes[current]], volumes[notes[current]]);
        }
        if (timer<durations[current]+offset and timer>=durations[current]-offset) {
            volumes[notes[current]]-=1.0f/offset;
            Renderer::set_sound_volume(plays[notes[current]], volumes[notes[current]]);
        }
        //std::cout<<volumes[notes[current]]<<std::endl;
        if (timer==durations[current]) {

            timer=-1;

            Renderer::stop_sound(plays[notes[current]]);

            current+=1;



            if (current>=length) {

                end=1;
            }
        }
        timer++;
    }



}

void Sequence::draw_progress_bar() {

    if (std::abs(bar_progress-compleation_level)>0.01 and bar_changing==0) {
        bar_changing=1;
        d_bar=(compleation_level-bar_progress)/bar_change_speed;
        if (compleation_level==0) {
            bar_color=RED;
        }

    }
    if (bar_changing>0) {
        bar_progress+=d_bar;
        bar_changing++;
        if (bar_changing>=bar_change_speed+1) {
            bar_changing=0;
            if (compleation_level==1) {
                bar_progress=1;
            }
            else if (compleation_level==0) {
                bar_progress=0;
                bar_color=GREEN;
            }

        }
    }
    std::cout<<bar_progress<<" "<<bar_changing<<std::endl;
    DrawRectangle(100,100,bar_width,bar_height,LIGHTGRAY);
    DrawRectangle(100,100,bar_width*bar_progress,bar_height,bar_color);

}
void Sequence::draw_falling_keys() {
    const int hit_y = 500;
    const int start_x = 250;
    const int key_width = 40;
    const float speed = 3.0f;

    DrawRectangle(start_x, hit_y, 8 * key_width, 5, RAYWHITE);

    for (size_t j = 0; j < notes.size(); j++) {
        int time_diff = target_times[j] - global_timer;

        float key_height = durations[j] * speed;

        if (time_diff > -durations[j] - 30 && time_diff < 200) {
            int x = start_x + (notes[j] * key_width);

            float bottom_y = hit_y - (time_diff * speed);

            float top_y = bottom_y - key_height;

            DrawRectangle(x, static_cast<int>(top_y), key_width, static_cast<int>(key_height), SKYBLUE);
        }
    }
}
