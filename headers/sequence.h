#pragma once
#include <array>
#include <vector>

class Sequence {
    public:
    int a;
    std::vector<int> notes;
    Sequence(std::vector<int> notes, int a);
    void test();

    ~Sequence() = default;
};


