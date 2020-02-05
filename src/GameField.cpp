#include <iostream>
#include <cassert>
#include <bitset>
#include "GameField.h"
#include "accessors.h"
#include "Pattern.h"

GameField::GameField(int rows, int columns) :
        rows(rows),
        columns(columns),
        frontField(rows * columns),
        backField(frontField) {}

int GameField::getRows() const {
    return rows;
}

int GameField::getColumns() const {
    return columns;
}

int GameField::getCurrentGen() const {
    return current_gen;
}

uint_fast8_t GameField::cellState(int row, int column) const {
    return get(frontField, columns, row, column) & 1u;
}

void GameField::enable(int row, int column) {
    getMutable(backField, columns, row, column) |= 1u;
    increaseNeighbors(row, column);
}

void GameField::disable(int row, int column) {
    getMutable(backField, columns, row, column) &= ~1u;
    decreaseNeighbors(row, column);
}

void GameField::increaseNeighbors(int row, int column) {
    addToNeighbors(row, column, 2);
}

void GameField::decreaseNeighbors(int row, int column) {
    addToNeighbors(row, column, -2);
}

void GameField::addToNeighbors(int row, int column, uint_fast8_t value) {
    // Adds a value to all fields around a given index
    // This is a generalized method which should only be called from increaseNeighbors
    // and decreaseNeighbors. The only valid inputs for value would probably be
    // 2 and -2 (which increases/decreases neighbors by one preserving the cell states)
    // We're using 'raw' indices to point into the field directly, which saves us
    // from having to check the bounds for each assignment and should gain us a
    // little speed advantage
    int index = rawIndex(columns, row, column);
    int diffAbove, diffBelow, diffLeft, diffRight;

    if (row == 0) {
        diffAbove = rawIndex(columns, rows - 1, column) - index;
    } else {
        diffAbove = rawIndex(columns, row - 1, column) - index;
    }
    if (column == 0) {
        diffLeft = columns - 1;
    } else {
        diffLeft = -1;
    }
    if (row == rows - 1) {
        diffBelow = rawIndex(columns, 0, column) - index;
    } else {
        diffBelow = rawIndex(columns, row + 1, column) - index;
    }
    if (column == columns - 1) {
        diffRight = -(columns - 1);
    } else {
        diffRight = 1;
    }

    backField[index + diffAbove + diffLeft] += value;
    backField[index + diffAbove] += value;
    backField[index + diffAbove + diffRight] += value;
    backField[index + diffLeft] += value;
    backField[index + diffRight] += value;
    backField[index + diffBelow + diffLeft] += value;
    backField[index + diffBelow] += value;
    backField[index + diffBelow + diffRight] += value;
}

void GameField::setCentered(const Pattern &pattern) {
    assert(columns >= pattern.rows);
    assert(rows >= pattern.columns);
    int row_start = rows / 2 - pattern.rows / 2;
    int column_start = columns / 2 - pattern.columns / 2;

    for (int row = 0; row < pattern.rows; row++) {
        for (int column = 0; column < pattern.columns; column++) {
            if (get(pattern.contents, pattern.columns, row, column)) {
                enable(row_start + row, column_start + column);
            }
        }
    }
    frontField = backField;
}

int GameField::nextGeneration() {
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            uint_fast8_t value = get(frontField, columns, row, column);
            if (!value) continue;
            uint_fast8_t alive = value & 1u;
            int neighbors = value >> 1u;
            if (alive) {
                if (neighbors != 2 && neighbors != 3) {
                    disable(row, column);
                }
            } else {
                if (neighbors == 3) {
                    enable(row, column);
                }
            }
        }
    }
    frontField = backField;

    return ++current_gen;
}

void GameField::print() const {
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            auto current = cellState(row, column) ? "O " : "_ ";
            std::cout << current;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
