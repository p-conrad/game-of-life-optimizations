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

const auto PRESET_GLIDER = Pattern(3, 3, {
        0, 1, 0,
        0, 0, 1,
        1, 1, 1
});

const auto PRESET_RPENTOMINO = Pattern(3, 3, {
        0, 1, 1,
        1, 1, 0,
        0, 1, 0
});

const auto PRESET_DIEHARD = Pattern(3, 8, {
        0, 0, 0, 0, 0, 0, 1, 0,
        1, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 1, 1, 1
});

const auto PRESET_ACORN = Pattern(3, 7, {
        0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0,
        1, 1, 0, 0, 1, 1, 1
});

const auto PRESET_EVE = Pattern(10, 16, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
});

#endif //GAME_OF_LIFE_PATTERN_H
