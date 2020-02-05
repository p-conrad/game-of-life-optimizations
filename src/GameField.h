#ifndef GAME_OF_LIFE_GAMEFIELD_H
#define GAME_OF_LIFE_GAMEFIELD_H


#include <cstdint>
#include <cstdlib>
#include <vector>
#include "Pattern.h"

class GameField {
public:
    GameField(int rows, int columns);

    int getRows() const;

    int getColumns() const;

    int getCurrentGen() const;

    uint_fast8_t getElementAt(int row, int column) const;

    void enable(int row, int column);

    void disable(int row, int column);

    void increaseNeighbors(int row, int column);

    void decreaseNeighbors(int row, int column);

    void setCentered(const Pattern &pattern);

    int nextGeneration();

    void print() const;

    void print_debug() const;

private:
    int rows;
    int columns;
    int current_gen = 1;
    std::vector<uint_fast8_t> frontField; // read only
    std::vector<uint_fast8_t> backField; // write only

    void addToNeighbors(int row, int column, uint_fast8_t value);
};


#endif //GAME_OF_LIFE_GAMEFIELD_H
