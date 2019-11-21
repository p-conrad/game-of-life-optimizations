#ifndef GAME_OF_LIFE_GAMEFIELD_H
#define GAME_OF_LIFE_GAMEFIELD_H


#include <cstdlib>
#include <vector>

class GameField {
public:
    GameField(size_t rows, size_t columns);

    size_t getRows() const;
    size_t getColumns() const;

    bool getElementAt(size_t i, size_t j);
    void setElementAt(size_t i, size_t j, bool value);

    int sumOfNeighbors(size_t i, size_t j);
    bool nextCellState(size_t i, size_t j);

private:
    size_t indexOf(size_t i, size_t j) const;

    const size_t rows;
    const size_t columns;
    std::vector<bool> elements;
};


#endif //GAME_OF_LIFE_GAMEFIELD_H
