#ifndef GAME_OF_LIFE_PATTERN_H
#define GAME_OF_LIFE_PATTERN_H

#include <utility>
#include <vector>
#include <cstdint>


struct Pattern {
    Pattern(int rows, int columns, std::vector<uint_fast8_t> contents)
            : rows(rows), columns(columns),
              contents(std::move(contents)) {}

    const int rows, columns;
    const std::vector<uint_fast8_t> contents;
};

#endif //GAME_OF_LIFE_PATTERN_H
