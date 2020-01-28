#include <omp.h>
#include <iostream>
#include "Presets.h"
#include "GameField.h"

int main() {
    const int rows = 10;
    const int columns = 10;
    const int generations = 10;

    GameField frontField(rows, columns);
    GameField backField(rows, columns);
    frontField.setCentered(PRESET_GLIDER);
    frontField.print();

    auto start_time = omp_get_wtime();

    for (int gen = 1; gen <= generations; gen++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                bool nextState = frontField.nextCellState(i, j);
                backField.setElementAt(i, j, nextState);
            }
        }
        auto tempField = frontField;
        frontField = backField;
        backField = tempField;
    }

    frontField.print();

    auto run_time = omp_get_wtime() - start_time;
    std::cout << "Run time for field of size " << rows << "x" << columns
              << " in " << generations << " generations: " << run_time << "s" << std::endl;

    return 0;
}