#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "Presets.h"
#include "GameWidget.h"

int main(int argc, char **argv) {
    const int rows = 300;
    const int columns = 300;
    const bool output_graphics = true;

    GameField field(rows, columns);
    field.setCentered(PRESET_ACORN);
    if (output_graphics) {
        Fl_Double_Window win(900,900,"Game Of Life");
        GameWidget game(0, 0, win.w(), win.h(), 0, field);
        win.show();
        return(Fl::run());
    } else {
        // assume we're benchmarking, so we set a max generation here
        const int gen_max = 30000;
        while (field.getCurrentGen() <= gen_max) {
            field.nextGeneration();
        }
    }
}