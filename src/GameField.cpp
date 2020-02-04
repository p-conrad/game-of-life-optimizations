#include <iostream>
#include "GameField.h"

GameField::GameField(int rows, int columns) :
        rows(rows),
        columns(columns),
        frontField(rows + 2, columns + 2),
        backField(rows + 2, columns + 2) {}

int GameField::getRows() const {
    return rows;
}

int GameField::getColumns() const {
    return columns;
}

int GameField::getCurrentGen() const {
    return current_gen;
}

uint_fast8_t GameField::getElementAt(int row, int column) const {
    return frontField(row + 1, column + 1);
}

void GameField::setElementAt(int row, int column, uint_fast8_t value) {
    backField.setElementAt(row + 1, column + 1, value);
}

void GameField::setCentered(const SimpleMatrix<uint_fast8_t>& values) {
    assert(getColumns() >= values.getColumns());
    assert(getRows() >= values.getRows());
    int y_start = getRows() / 2 - values.getRows() / 2;
    int x_start = getColumns() / 2 - values.getColumns() / 2;

    for (int y = 0; y < values.getRows(); y++) {
        for (int x = 0; x < values.getColumns(); x++) {
            setElementAt(y_start + y, x_start + x, values.getElementAt(y, x));
        }
    }

    flip();
}

uint_fast8_t GameField::neighborCount(int row, int column) const {
    uint_fast8_t sum = 0;
    for (int y = row - 1; y <= row + 1; y++) {
        for (int x = column - 1; x <= column + 1; x++) {
            sum += getElementAt(y, x);
        }
    }

    return sum - getElementAt(row, column);
}

uint_fast8_t GameField::nextCellState(int row, int column) const {
    uint_fast8_t neighbors = neighborCount(row, column);
    uint_fast8_t isAlive = getElementAt(row, column);

    // classic 23/3 rules
    return (!isAlive && neighbors == 3) || (isAlive && (neighbors == 2 || neighbors == 3));
}

int GameField::nextGeneration() {
    for (int i = 0; i < getRows(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            uint_fast8_t nextState = nextCellState(i, j);
            setElementAt(i, j, nextState);
        }
    }
    flip();

    return ++current_gen;
}

void GameField::flip() {
    // copies opposite edges into the padding of backField and then flips the fields
    // It's a bit messy, because now indices of GameField don't correspond to
    // indices of the underlying matrices anymore... we'll see if we can fix that later
    // The following indices are NOT out of bounds
    backField.setElementAt(0, 0, backField.getElementAt(rows, columns));
    backField.setElementAt(0, backField.getColumns()-1, backField.getElementAt(rows, 1));
    backField.setElementAt(backField.getRows()-1, 0, backField.getElementAt(1, columns));
    backField.setElementAt(backField.getRows()-1, backField.getColumns()-1, backField.getElementAt(1, 1));

    for (int x = 1; x <= columns; x++) {
        backField.setElementAt(0, x, backField.getElementAt(rows, x));
        backField.setElementAt(rows+1, x, backField.getElementAt(1, x));
    }
    for (int y = 1; y <= rows; y++) {
        backField.setElementAt(y, 0, backField.getElementAt(y, columns));
        backField.setElementAt(y, columns+1, backField.getElementAt(y, 1));
    }

    auto tempField = frontField;
    frontField = backField;
    backField = tempField;
}

void GameField::print() const {
    for (int row = 0; row < getRows(); row++) {
        for (int column = 0; column < getColumns(); column++) {
            auto current = getElementAt(row, column) ? "O " : "_ ";
            std::cout << current;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
