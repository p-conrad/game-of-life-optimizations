#ifndef GAME_OF_LIFE_PRESETS_H
#define GAME_OF_LIFE_PRESETS_H

#include <vector>
#include "SimpleMatrix.h"

const auto PRESET_GLIDER = SimpleMatrix<bool>(3, 3, {
        false, true, false,
        false, false, true,
        true, true, true});

#endif //GAME_OF_LIFE_PRESETS_H
