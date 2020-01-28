#include <iostream>
#include "GameField.h"

GameField::GameField(size_t rows, size_t columns) :
        rows(rows),
        columns(columns),
        elements(rows + 2, columns + 2) {}

size_t GameField::getRows() {
    return rows;
}

size_t GameField::getColumns() {
    return columns;
}

bool GameField::getElementAt(size_t row, size_t column) {
    return elements(row + 1, column + 1);
}

void GameField::setElementAt(size_t row, size_t column, bool value) {
    elements.setElementAt(row + 1, column + 1, value);
}

bool GameField::nextCellState(size_t row, size_t column) {
    int neighbors = neighborCount(row, column);
    bool isAlive = getElementAt(row, column);

    // classic 23/3 rules
    return (!isAlive && neighbors == 3) || (isAlive && (neighbors == 2 || neighbors == 3));
}

int GameField::neighborCount(size_t row, size_t column) {
    int sum = 0;
    // NOTE: x/y overflow when row or column are 0 but this still works because we have padding
    // and getElementAt will use the proper indices. Perhaps there is a better way to handle this
    // which doesn't involve relying on undefined behaviour (ssize_t?)
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

void GameField::setCentered(SimpleMatrix<bool> values) {
    assert(getColumns() >= values.getColumns());
    assert(getRows() >= values.getRows());
    size_t y_start = getColumns() / 2 - values.getColumns() / 2;
    size_t x_start = getRows() / 2 - values.getRows() / 2;

    for (size_t y = 0; y < values.getColumns(); y++) {
        for (size_t x = 0; x < values.getRows(); x++) {
            setElementAt(y_start + y, x_start + x, values.getElementAt(y, x));
        }
    }
}
