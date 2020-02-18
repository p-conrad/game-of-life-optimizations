#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "Pattern.h"
#include "GameWidget.h"
#include "FieldBenchmark.h"
#include "GameSettings.h"
#include "RLE.h"

int main(int argc, char **argv) {
    auto settings = parseArgs(argc, argv);
    GameField field(settings.fieldHeight, settings.fieldWidth);
    auto pattern = readRLE(settings.filename);
    field.setCentered(pattern);

    if (settings.doBenchmark) {
        FieldBenchmark benchmark(field);
        benchmark.run(settings.generations);
    } else {
        Fl_Double_Window win(settings.winWidth, settings.winHeight, "Game Of Life");
        GameWidget game(0, 0, win.w(), win.h(), nullptr, field);
        std::cout << "Press space to run/pause the game" << std::endl;
        win.show();
        return (Fl::run());
    }
}