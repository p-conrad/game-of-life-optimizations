#include <iostream>
#include "GameField.h"
#include "accessors.h"
#include "Pattern.h"

GameField::GameField(int rows, int columns) :
        rows(rows),
        columns(columns),
        frontField((rows + 2) * (columns + 2)),
        backField((rows + 2) * (columns + 2)) {}

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
    return get_padded(frontField, columns, row, column);
}

void GameField::setElementAt(int row, int column, uint_fast8_t value) {
    set_padded(backField, columns, row, column, value);
}

void GameField::setCentered(const Pattern &pattern) {
    assert(getColumns() >= pattern.rows);
    assert(getRows() >= pattern.columns);
    int y_start = rows / 2 - pattern.rows / 2;
    int x_start = columns / 2 - pattern.columns / 2;

    for (int y = 0; y < pattern.rows; y++) {
        for (int x = 0; x < pattern.columns; x++) {
            set_padded(backField, columns, y_start + y, x_start + x,
                       get(pattern.contents, pattern.columns, y, x));
        }
    }

    flip();
}

uint_fast8_t GameField::neighborCount(int row, int column) const {
    uint_fast8_t sum = 0;
    for (int y = row - 1; y <= row + 1; y++) {
        for (int x = column - 1; x <= column + 1; x++) {
            sum += get_padded(frontField, columns, y, x);
        }
    }

    return sum - get_padded(frontField, columns, row, column);
}

uint_fast8_t GameField::nextCellState(int row, int column) const {
    uint_fast8_t neighbors = neighborCount(row, column);
    uint_fast8_t isAlive = get_padded(frontField, columns, row, column);

    // classic 23/3 rules
    return (!isAlive && neighbors == 3) || (isAlive && (neighbors == 2 || neighbors == 3));
}

int GameField::nextGeneration() {
    for (int i = 0; i < getRows(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            uint_fast8_t nextState = nextCellState(i, j);
            set_padded(backField, columns, i, j, nextState);
        }
    }
    flip();

    return ++current_gen;
}

void GameField::flip() {
    // copies opposite corners and edges into the padding of backField and then flips the fields
    auto w = columns + 2;
    set(backField, w, 0,        0,           get_padded(backField, columns, rows - 1, columns - 1));
    set(backField, w, 0,        columns + 1, get_padded(backField, columns, rows - 1, 0));
    set(backField, w, rows + 1, 0,           get_padded(backField, columns, 0,      columns - 1));
    set(backField, w, rows + 1, columns + 1, get_padded(backField, columns, 0,      0));

    for (int x = 0; x < columns; x++) {
        set(backField, w, 0,        x + 1, get_padded(backField, columns, rows - 1, x));
        set(backField, w, rows + 1, x + 1, get_padded(backField, columns, 0, x));
    }
    for (int y = 0; y < rows; y++) {
        set(backField, w, y + 1, 0,           get_padded(backField, columns, y, columns - 1));
        set(backField, w, y + 1, columns + 1, get_padded(backField, columns, y, 0));
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
