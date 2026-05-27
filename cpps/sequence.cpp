#include "../headers/sequence.h"
#include <iostream>
#include "raylib.h"


Sequence::Sequence(std::vector<int> notes) {
    this->notes=notes;
    C = LoadSound("../Resources/C.wav");
    D = LoadSound("../Resources/D.wav");
    E = LoadSound("../Resources/E.wav");
    F = LoadSound("../Resources/F.wav");
    G = LoadSound("../Resources/G.wav");
    A = LoadSound("../Resources/A.wav");
    B = LoadSound("../Resources/B.wav");
    C2 = LoadSound("../Resources/C2.wav");
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



}
void Sequence::test() {


}
void Sequence::add_level() {
    level+=1;
}
void Sequence::get_key() {
    int a=0;
    for (auto& pair : keys) {
        if (IsKeyPressed(pair.first)) {
            int index = pair.second;
            std::cout << "Key index " << index << " pressed\n";
            a=1;
            current_note=index;
        }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        a=1;
        current_note=-2;
    }





    }
    if (a==0) {
        current_note=-1;
    }

}
void Sequence::progress() {
    std::cout<<"ccc";
    if (current_note>=0){

        std::cout<<current_note<<std::endl;
        if (notes.size() > 0) std::cout<<notes[0]<<std::endl;

        if (level < length && notes[level]==current_note) {
            std::cout<<"ccc";
            level++;
            if (level==length) {
                completed=1;
                std::cout << "Completed " << completed << " pressed\n";
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
    if (timer==0) {
        std::cout<<"start-play";
        PlaySound(C);
        timer++;
    }
    else {
        timer++;
    }


    std::cout<<"play";
}