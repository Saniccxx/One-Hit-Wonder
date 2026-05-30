#include "../headers/sequence.h"
#include "../headers/renderer.h"
#include <iostream>


Sequence::Sequence(std::vector<int> notes,std::vector<int> durations) {
    this->notes=notes;
    this->durations=durations;
    for (i=0; i<notes.size(); i++) {
        volumes[i]=0;
    }
    current=0;
    end=0;
    offset=20;
    compleation_level=0.0f;
    C = Renderer::load_sound("../Resources/C.wav");
    D = Renderer::load_sound("../Resources/D.wav");
    E = Renderer::load_sound("../Resources/E.wav");
    F = Renderer::load_sound("../Resources/F.wav");
    G = Renderer::load_sound("../Resources/G.wav");
    A = Renderer::load_sound("../Resources/A.wav");
    B = Renderer::load_sound("../Resources/B.wav");
    C2 = Renderer::load_sound("../Resources/C2.wav");
    plays = {
        {0, Renderer::load_sound("../Resources/C.wav")},
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
            std::cout<<"Upgrade"<<compleation_level<<level<<length<<std::endl;
            if (level==length) {
                completed=1;
                std::cout << "Completed ";
            }
        }
        else if (level >= length) {}
        else {
            std::cout << "Wrong note, reset";
            level=0;
        }
    }
    else if (current_note==-2) {
        std::cout << "Reset";
        level=0;
    }
};
void Sequence::check() {
    get_key();
    progress();
}
void Sequence::play() {


    if (end==0) {
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