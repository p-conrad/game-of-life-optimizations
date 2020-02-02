#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "Presets.h"
#include "GameWidget.h"
#include "FieldBenchmark.h"

int main(int argc, char **argv) {
    const int rows = 300;
    const int columns = 300;
    const bool output_graphics = false;

    GameField field(rows, columns);
    field.setCentered(PRESET_ACORN);
    if (output_graphics) {
        Fl_Double_Window win(900,900,"Game Of Life");
        GameWidget game(0, 0, win.w(), win.h(), 0, field);
        win.show();
        return(Fl::run());
    } else {
        // assume we're benchmarking
        const int max_generation = 30000;
        FieldBenchmark benchmark(field);
        benchmark.run(max_generation);
    }
}