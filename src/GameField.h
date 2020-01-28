#ifndef GAME_OF_LIFE_GAMEFIELD_H
#define GAME_OF_LIFE_GAMEFIELD_H


#include <cstdlib>
#include <vector>
#include "SimpleMatrix.h"

class GameField {
public:
    GameField(int rows, int columns);

    int getRows();

    int getColumns();

    bool getElementAt(int row, int column);

    void setElementAt(int row, int column, bool value);

    void setCentered(SimpleMatrix<bool> values);

    bool nextCellState(int row, int column);

    void print();

private:
    int rows;
    int columns;
    SimpleMatrix<bool> elements;

    int neighborCount(int row, int column);
};


#endif //GAME_OF_LIFE_GAMEFIELD_H
