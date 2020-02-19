#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "Pattern.h"
#include "GameWidget.h"
#include "FieldBenchmark.h"
#include "GameSettings.h"
#include "RLE.h"

int main(int argc, char **argv) {
    GameSettings settings;
    Pattern pattern;
    try {
        settings = parseArgs(argc, argv);
        pattern = readRLE(settings.filename);

        if (settings.fieldWidth < pattern.columns || settings.fieldHeight < pattern.rows) {
            throw std::invalid_argument("The field is too small to hold the provided pattern");
        }
    } catch (const std::invalid_argument &ia) {
        std::cout << "Failed to initialize the game. Error message: " << std::endl;
        std::cout << "  " << ia.what() << std::endl;
        return (1);
    }
    GameField field(settings.fieldHeight, settings.fieldWidth);
    field.setCentered(pattern);

    if (settings.doBenchmark) {
        FieldBenchmark benchmark(field);
        benchmark.run(settings.generations, settings.logFrequency);
    } else {
        Fl_Double_Window win(settings.winWidth, settings.winHeight, "Game Of Life");
        GameWidget game(0, 0, win.w(), win.h(), nullptr, field);
        std::cout << "Press space to run/pause the game" << std::endl;
        win.show();
        return (Fl::run());
    }
}