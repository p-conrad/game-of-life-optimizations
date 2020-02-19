#ifndef GAME_OF_LIFE_PATTERN_H
#define GAME_OF_LIFE_PATTERN_H

#include <utility>
#include <vector>
#include <cstdint>


struct Pattern {
    int rows, columns;
    std::vector<uint_fast8_t> contents;
};

#endif //GAME_OF_LIFE_PATTERN_H
