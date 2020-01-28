#include <iostream>
#include "GameField.h"

GameField::GameField(int rows, int columns) :
        rows(rows),
        columns(columns),
        elements(rows + 2, columns + 2) {}

int GameField::getRows() {
    return rows;
}

int GameField::getColumns() {
    return columns;
}

bool GameField::getElementAt(int row, int column) {
    return elements(row + 1, column + 1);
}

void GameField::setElementAt(int row, int column, bool value) {
    elements.setElementAt(row + 1, column + 1, value);
}

bool GameField::nextCellState(int row, int column) {
    int neighbors = neighborCount(row, column);
    bool isAlive = getElementAt(row, column);

    // classic 23/3 rules
    return (!isAlive && neighbors == 3) || (isAlive && (neighbors == 2 || neighbors == 3));
}

int GameField::neighborCount(int row, int column) {
    int sum = 0;
    for (int y = row - 1; y <= row + 1; y++) {
        for (int x = column - 1; x <= column + 1; x++) {
            sum += getElementAt(y, x);
        }
    }

    return sum - getElementAt(row, column);
}

void GameField::print() {
    for (int row = 0; row <= getRows(); row++) {
        for (int column = 0; column <= getColumns(); column++) {
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
    int y_start = getColumns() / 2 - values.getColumns() / 2;
    int x_start = getRows() / 2 - values.getRows() / 2;

    for (int y = 0; y < values.getColumns(); y++) {
        for (int x = 0; x < values.getRows(); x++) {
            setElementAt(y_start + y, x_start + x, values.getElementAt(y, x));
        }
    }
}
