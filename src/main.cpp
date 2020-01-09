#include <omp.h>
#include <iostream>
#include "Presets.h"
#include "GameField.h"

int main() {
    const size_t rows = 10;
    const size_t columns = 10;
    const size_t generations = 10;

    auto *frontField = new GameField(rows, columns);
    auto *backField = new GameField(rows, columns);
//    frontField->setCentered(PRESET_GLIDER);
    frontField->print();

    auto start_time = omp_get_wtime();

    for (size_t gen = 1; gen <= generations; gen++) {
        for (size_t i = 1; i <= rows; i++) {
            for (size_t j = 1; j <= columns; j++) {
                bool nextState = frontField->nextCellState(i, j);
                backField->setElementAt(i, j, nextState);
            }
        }
        auto tempField = frontField;
        frontField = backField;
        backField = tempField;
    }

    frontField->print();

    auto run_time = omp_get_wtime() - start_time;
    std::cout << "Run time for field of size " << rows << "x" << columns
            << " in " << generations <<" generations: " << run_time << "s" << std::endl;

    return 0;
}