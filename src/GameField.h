#ifndef GAME_OF_LIFE_GAMEFIELD_H
#define GAME_OF_LIFE_GAMEFIELD_H


#include <cstdlib>
#include <vector>
#include "SimpleMatrix.h"

class GameField {
public:
    GameField(size_t rows, size_t columns);

    size_t getRows();

    size_t getColumns();

    bool getElementAt(size_t row, size_t column);

    void setElementAt(size_t row, size_t column, bool value);

    bool nextCellState(size_t row, size_t column);

    void print();

private:
    size_t rows;
    size_t columns;
    SimpleMatrix<bool> elements;

    int neighborCount(size_t row, size_t column);
};


#endif //GAME_OF_LIFE_GAMEFIELD_H
