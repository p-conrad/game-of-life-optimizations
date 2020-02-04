#ifndef GAME_OF_LIFE_PRESETS_H
#define GAME_OF_LIFE_PRESETS_H

#include <vector>
#include <cstdint>
#include "SimpleMatrix.h"

const auto PRESET_GLIDER = SimpleMatrix<uint_fast8_t>(3, 3, {
        0, 1, 0,
        0, 0, 1,
        1, 1, 1
});

const auto PRESET_RPENTOMINO = SimpleMatrix<uint_fast8_t>(3, 3, {
        0, 1, 1,
        1, 1, 0,
        0, 1, 0
});

const auto PRESET_DIEHARD = SimpleMatrix<uint_fast8_t>(3, 8, {
        0, 0, 0, 0, 0, 0, 1, 0,
        1, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 1, 1, 1
});

const auto PRESET_ACORN = SimpleMatrix<uint_fast8_t>(3, 7, {
        0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0,
        1, 1, 0, 0, 1, 1, 1
});

const auto PRESET_EVE = SimpleMatrix<uint_fast8_t>(10, 16, {
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

#endif //GAME_OF_LIFE_PRESETS_H
