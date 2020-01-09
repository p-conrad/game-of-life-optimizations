#include <iostream>
#include "GameField.h"

GameField::GameField(const size_t rows, const size_t columns) : rows(rows), columns(columns) {
    elements = std::vector<bool>((rows + 2) * (columns + 2), false); // padding at each side of the field
}

size_t GameField::getRows() const {
    return rows;
}

size_t GameField::getColumns() const {
    return columns;
}

bool GameField::getElementAt(size_t row, size_t column) {
    return elements[(row + 1) * rows + (column + 1)];
}

void GameField::setElementAt(size_t row, size_t column, bool value) {
    elements[(row + 1) * rows + (column + 1)] = value;
}

bool GameField::nextCellState(size_t row, size_t column) {
    int neighbors = neighborCount(row, column);
    bool isAlive = getElementAt(row, column);

    // classic 23/3 rules
    return (!isAlive && neighbors == 3) || (isAlive && (neighbors == 2 || neighbors == 3));
}

int GameField::neighborCount(size_t row, size_t column) {
    int sum = 0;
    for (size_t y = row - 1; y <= row + 1; y++) {
        for (size_t x = column - 1; x <= column + 1; x++) {
            sum += getElementAt(y, x);
        }
    }

    return sum - getElementAt(row, column);
}

void GameField::print() {
    for (size_t row = 0; row <= getRows(); row++) {
        for (size_t column = 0; column <= getColumns(); column++) {
            auto current = getElementAt(row, column) ? "O " : "_ ";
            std::cout << current;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
