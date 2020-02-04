#ifndef GAME_OF_LIFE_ACCESSORS_H
#define GAME_OF_LIFE_ACCESSORS_H


#include <cstdint>
#include <vector>

inline uint_fast8_t get(const std::vector<uint_fast8_t> &vec, int width, int y, int x) {
    return vec[(y * width) + x];
}

inline uint_fast8_t get_padded(const std::vector<uint_fast8_t> &vec, int width, int y, int x) {
    return get(vec, width + 2, y + 1, x + 1);
}

inline void set(std::vector<uint_fast8_t> &vec, int width, int y, int x, uint_fast8_t value) {
    vec[(y * width) + x] = value;
}

inline void set_padded(std::vector<uint_fast8_t> &vec, int width, int y, int x, uint_fast8_t value) {
    set(vec, width + 2, y + 1, x + 1, value);
}


#endif //GAME_OF_LIFE_ACCESSORS_H
