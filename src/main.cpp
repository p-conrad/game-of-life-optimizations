#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "Pattern.h"
#include "GameWidget.h"
#include "FieldBenchmark.h"

int main(int argc, char **argv) {
    const int rows = 500;
    const int columns = 500;
    const bool output_graphics = false;

    GameField field(rows, columns);
    field.setCentered(PRESET_EVE);
    if (output_graphics) {
        Fl_Double_Window win(1000,1000,"Game Of Life");
        GameWidget game(0, 0, win.w(), win.h(), nullptr, field);
        win.show();
        return(Fl::run());
    } else {
        // assume we're benchmarking
        const int max_generation = 30000;
        FieldBenchmark benchmark(field);
        benchmark.run(max_generation);
    }
}