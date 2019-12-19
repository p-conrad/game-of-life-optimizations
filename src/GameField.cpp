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

bool GameField::getElementAt(size_t i, size_t j) {
    return elements[indexOf(i, j)];
}

void GameField::setElementAt(size_t i, size_t j, bool value) {
    elements[indexOf(i, j)] = value;
}

size_t GameField::indexOf(size_t i, size_t j) const {
    return (i * rows) + j;
}

int GameField::sumOfNeighbors(size_t i, size_t j) {
    int sum = 0;
    for (size_t row = i - 1; row <= i + 1; row++) {
        for (size_t col = j - 1; col <= j + 1; col++) {
            sum += getElementAt(row, col);
        }
    }

    return sum - getElementAt(i, j);
}

bool GameField::nextCellState(size_t i, size_t j) {
    int neighbors = sumOfNeighbors(i, j);
    bool isAlive = getElementAt(i, j);

    if (!isAlive && neighbors == 3) {
        return true;
    } else if (isAlive && (neighbors == 2 || neighbors == 3)) {
        return true;
    }
    return false;
}

void GameField::setCentered(std::vector<std::vector<bool>> pattern) {
    size_t start_x = getColumns() / 2 - pattern.size() / 2;
    size_t start_y = getRows() / 2 - pattern[0].size() / 2;

    for (size_t i = start_x; i < pattern.size(); i++) {
        for (size_t j = start_y; j < pattern[0].size(); j++) {
            setElementAt(i, j, pattern[i][j]);
        }
    }
}

void GameField::print() {
    for (size_t i = 0; i <= getRows(); i++) {
        for (size_t j = 0; j <= getColumns(); j++) {
            auto current = getElementAt(i, j) ? "O " : "_ ";
            std::cout << current;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
