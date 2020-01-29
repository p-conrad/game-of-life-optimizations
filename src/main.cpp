#include <omp.h>
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include "Presets.h"
#include "GameField.h"

class DrawX : public Fl_Widget {
public:
    DrawX(int X, int Y, int W, int H, const char*L=0) : Fl_Widget(X,Y,W,H,L) {}
    void draw() {
        fl_color(FL_BLACK);
        int x1 = x(),       y1 = y();
        int x2 = x()+w()-1, y2 = y()+h()-1;
        fl_rect(0, 0, 10, 10, FL_BLUE);
        fl_line(x1, y1, x2, y2);
        fl_line(x1, y2, x2, y1);
    }
};

int main(int argc, char **argv) {
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

    Fl_Double_Window win(200,200,"Draw X");
    DrawX draw_x(0, 0, win.w(), win.h());
    win.resizable(draw_x);
    win.show();
    return(Fl::run());

    return 0;
}