#ifndef GAME_OF_LIFE_ACCESSORS_H
#define GAME_OF_LIFE_ACCESSORS_H


#include <cstdint>
#include <vector>

inline uint_fast8_t get(const std::vector<uint_fast8_t> &vec, int width, int y, int x) {
    return vec[(y * width) + x];
}

inline uint_fast8_t &getMutable(std::vector<uint_fast8_t> &vec, int width, int y, int x) {
    return vec[(y * width) + x];
}

inline int rawIndex(int width, int y, int x) {
    return (y * width) + x;
}

inline void set(std::vector<uint_fast8_t> &vec, int width, int y, int x, uint_fast8_t value) {
    vec[(y * width) + x] = value;
}


#endif //GAME_OF_LIFE_ACCESSORS_H
