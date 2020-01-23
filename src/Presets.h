#ifndef GAME_OF_LIFE_PRESETS_H
#define GAME_OF_LIFE_PRESETS_H

#include <vector>

const std::vector<std::vector<bool>> PRESET_GLIDER = {
        {false, true,  false},
        {false, false, true},
        {true,  true,  true}
};

#endif //GAME_OF_LIFE_PRESETS_H
