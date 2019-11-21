#include <omp.h>
#include <iostream>
#include "GameField.h"

int main() {
    const size_t rows = 1000;
    const size_t columns = 1000;
    const size_t generations = 100;

    auto *frontField = new GameField(rows, columns);
    auto *backField = new GameField(rows, columns);

    auto start_time = omp_get_wtime();

    // We use padding at each side of our field to eliminate the need for conditionals
    // This allows/requires us to start our indices at 1
    for (size_t gen = 1; gen <= generations; gen++) {
        for (size_t i = 1; i <= rows; i++) {
            for (size_t j = 1; j <= columns; j++) {
                bool nextState = frontField->nextCellState(i, j);
                backField->setElementAt(i, j, nextState);
            }
        }
    }

    auto run_time = omp_get_wtime() - start_time;
    std::cout << "Run time for field of size " << rows << "x" << columns
            << " in " << generations <<" generations: " << run_time << "s" << std::endl;

    return 0;
}