#pragma once

#include <random>

namespace randomizer {
    inline int get_random_int(int a, int b) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(a, b);
        return distrib(gen);
    }
}
