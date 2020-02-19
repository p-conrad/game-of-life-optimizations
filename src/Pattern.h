#ifndef GAME_OF_LIFE_PATTERN_H
#define GAME_OF_LIFE_PATTERN_H

#include <vector>
#include <cstdint>
#include <string>


struct Pattern {
    int rows, columns;
    std::vector<uint_fast8_t> contents;
    std::string name;
    std::string author;
    std::vector<std::string> comments;
};

#endif //GAME_OF_LIFE_PATTERN_H
