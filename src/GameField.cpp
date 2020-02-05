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
