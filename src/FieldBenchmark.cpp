#include <omp.h>
#include <iostream>
#include <cmath>
#include "FieldBenchmark.h"

FieldBenchmark::FieldBenchmark(const GameField &field) : field(field) {
    filename = "benchmark_" + std::to_string(field.getColumns())
            + "x" + std::to_string(field.getRows()) + ".csv";
    outfile = fopen(filename.c_str(), "w+");
}

void FieldBenchmark::run(int generations) {
    fprintf(outfile, "gen,avg,gps\n");
    double sum_of_run_times = 0;

    while (field.getCurrentGen() <= generations) {
        auto start_time = omp_get_wtime();
        field.nextGeneration();
        auto run_time = omp_get_wtime() - start_time;
        sum_of_run_times += run_time;

        std::string line;

        // TODO: maybe not hard-code the number 50?
        if (field.getCurrentGen() % 50 == 0) {
            int progress = (int)round(((double) field.getCurrentGen() / generations) * 100);
            std::cout << "\r" << std::string(line.length(), ' ') << "\r";
            line = "Generation: " +
                   std::to_string(field.getCurrentGen()) + "/" + std::to_string(generations)
                   + " (" + std::to_string(progress) + "% done)";
            std::cout << line << std::flush;

            auto average = sum_of_run_times / 50;
            auto per_second = 60 / average;
            fprintf(outfile, "%d,%f,%.2f\n", field.getCurrentGen(), average, per_second);
            sum_of_run_times = 0;
        }
    }

    std::cout << std::endl << "Output written to " << filename << std::endl;
}

FieldBenchmark::~FieldBenchmark() {
    if (outfile) {
        fclose(outfile);
    }
}
