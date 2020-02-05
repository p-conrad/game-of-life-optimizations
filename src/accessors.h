#ifndef GAME_OF_LIFE_ACCESSORS_H
#define GAME_OF_LIFE_ACCESSORS_H


#include <cstdint>
#include <vector>

inline uint_fast8_t get(const std::vector<uint_fast8_t> &vec, int width, int y, int x) {
    return vec[(y * width) + x];
}

inline uint_fast8_t &get_mutable(std::vector<uint_fast8_t> &vec, int width, int y, int x) {
    return vec[(y * width) + x];
}

inline int raw_index(int width, int y, int x) {
    return (y * width) + x;
}


#endif //GAME_OF_LIFE_ACCESSORS_H
