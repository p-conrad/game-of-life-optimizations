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

uint_fast8_t GameField::getElementAt(int row, int column) const {
    return get(frontField, columns, row, column) & 1u;
}

void GameField::enable(int row, int column) {
    get_mutable(backField, columns, row, column) |= 1u;
    increaseNeighbors(row, column);
}

void GameField::disable(int row, int column) {
    get_mutable(backField, columns, row, column) &= ~1u;
    decreaseNeighbors(row, column);
}

void GameField::increaseNeighbors(int row, int column) {
    addToNeighbors(row, column, 2);
}

void GameField::decreaseNeighbors(int row, int column) {
    addToNeighbors(row, column, -2);
}

void GameField::addToNeighbors(int row, int column, uint_fast8_t value) {
    int rawIndex = raw_index(columns, row, column);
    int diffAbove, diffBelow, diffLeft, diffRight;

    if (row == 0) {
        diffAbove = raw_index(columns, rows - 1, column) - rawIndex;
    } else {
        diffAbove = raw_index(columns, row - 1, column) - rawIndex;
    }
    if (column == 0) {
        diffLeft = columns - 1;
    } else {
        diffLeft = -1;
    }
    if (row == rows - 1) {
        diffBelow = raw_index(columns, 0, column) - rawIndex;
    } else {
        diffBelow = raw_index(columns, row + 1, column) - rawIndex;
    }
    if (column == columns - 1) {
        diffRight = -(columns - 1);
    } else {
        diffRight = 1;
    }

    backField[rawIndex + diffAbove + diffLeft] += value;
    backField[rawIndex + diffAbove] += value;
    backField[rawIndex + diffAbove + diffRight] += value;
    backField[rawIndex + diffLeft] += value;
    backField[rawIndex + diffRight] += value;
    backField[rawIndex + diffBelow + diffLeft] += value;
    backField[rawIndex + diffBelow] += value;
    backField[rawIndex + diffBelow + diffRight] += value;
}

void GameField::setCentered(const Pattern &pattern) {
    assert(columns >= pattern.rows);
    assert(rows >= pattern.columns);
    int y_start = rows / 2 - pattern.rows / 2;
    int x_start = columns / 2 - pattern.columns / 2;

    for (int y = 0; y < pattern.rows; y++) {
        for (int x = 0; x < pattern.columns; x++) {
            if (get(pattern.contents, pattern.columns, y, x)) {
                enable(y_start + y, x_start + x);
            }
        }
    }

    frontField = backField;
}

int GameField::nextGeneration() {
    backField = frontField;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            uint_fast8_t value = get(frontField, columns, i, j);
            if (!value) continue;
            uint_fast8_t alive = value & 1u;
            int neighbors = value >> 1u;
            if (alive) {
                if (neighbors != 2 && neighbors != 3) {
                    disable(i, j);
                }
            } else {
                if (neighbors == 3) {
                    enable(i, j);
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
            auto current = getElementAt(row, column) ? "       O " : "________ ";
            std::cout << current;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void GameField::print_debug() const {
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            std::bitset<8> bits(get(frontField, columns, row, column));
            std::cout << bits << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

