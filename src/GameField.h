#ifndef GAME_OF_LIFE_GAMEFIELD_H
#define GAME_OF_LIFE_GAMEFIELD_H


#include <cstdint>
#include <cstdlib>
#include <vector>
#include "SimpleMatrix.h"
#include "Pattern.h"

class GameField {
public:
    GameField(int rows, int columns);

    int getRows() const;

    int getColumns() const;

    int getCurrentGen() const;

    uint_fast8_t getElementAt(int row, int column) const;

    void setElementAt(int row, int column, uint_fast8_t value);

    void setCentered(const Pattern &pattern);

    uint_fast8_t nextCellState(int row, int column) const;

    int nextGeneration();

    void flip();

    void print() const;

private:
    int rows;
    int columns;
    int current_gen = 1;
    std::vector<uint_fast8_t> frontField; // read only
    std::vector<uint_fast8_t> backField; // write only

    uint_fast8_t neighborCount(int row, int column) const;
};


#endif //GAME_OF_LIFE_GAMEFIELD_H
