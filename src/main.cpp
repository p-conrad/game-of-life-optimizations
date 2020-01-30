#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "Presets.h"
#include "GameWidget.h"

int main(int argc, char **argv) {
    const int rows = 50;
    const int columns = 50;

    Fl_Double_Window win(400,400,"Game Of Life");
    GameWidget game(0, 0, win.w(), win.h(), 0, rows, columns);
    game.getField().setCentered(PRESET_GLIDER);
    win.show();
    return(Fl::run());
}