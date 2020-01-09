#ifndef GAME_OF_LIFE_GAMEFIELD_H
#define GAME_OF_LIFE_GAMEFIELD_H


#include <cstdlib>
#include <vector>

class GameField {
public:
    GameField(size_t rows, size_t columns);

    size_t getRows() const;
    size_t getColumns() const;

    bool getElementAt(size_t row, size_t column);
    void setElementAt(size_t row, size_t column, bool value);

    bool nextCellState(size_t row, size_t column);

    void print();

private:
    const size_t rows;
    const size_t columns;
    std::vector<bool> elements;
    int neighborCount(size_t row, size_t column);
};


#endif //GAME_OF_LIFE_GAMEFIELD_H
