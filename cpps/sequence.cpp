#include "../headers/sequence.h"
#include <iostream>


Sequence::Sequence(std::vector<int> notes) {
    this->notes=notes;
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
    }
    if (a==0) {
        current_note=-1;
    }

}
void Sequence::progress() {
    std::cout<<"ccc";
    if (current_note>=0){

        std::cout<<current_note<<std::endl;
        std::cout<<notes[0]<<std::endl;
        if (notes[level]==current_note) {
            std::cout<<"ccc";
            level++;
            if (level==length) {
                completed=1;
                std::cout << "Completed " << completed << " pressed\n";
            }
        }
    }
};