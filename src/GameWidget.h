#ifndef GAME_OF_LIFE_GAMEWIDGET_H
#define GAME_OF_LIFE_GAMEWIDGET_H

#include <FL/Fl_Box.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "GameField.h"

class GameWidget : public Fl_Box {
    GameField field;
    const int rows, columns;

    void draw() override {
        Fl_Box::draw();

        int cell_pixel_width = w() / columns;
        int cell_pixel_height = h() / rows;

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < columns; col++) {
                if (field.getElementAt(row, col)) {
                    fl_draw_box(FL_FLAT_BOX,
                                col * cell_pixel_width, row * cell_pixel_height,
                                cell_pixel_width, cell_pixel_height,
                                FL_GREEN);
                }
            }
        }
        field.nextGeneration();
    }

    static void Timer_CB(void *userdata) {
        auto *gw = (GameWidget*) userdata;
        gw->redraw();
        Fl::repeat_timeout(1.0 / 30.0, Timer_CB, userdata);
    }

public:
    GameWidget(int x, int y, int w, int h, const char *l, const int rows, const int columns) :
            Fl_Box(x, y, w, h, l),
            field(rows, columns),
            rows(rows), columns(columns) {
        box(FL_FLAT_BOX);
        color(FL_BLACK);
        Fl::add_timeout(1.0 / 30.0, Timer_CB, (void*) this);
    }

    GameField &getField() {
        return field;
    }
};

#endif //GAME_OF_LIFE_GAMEWIDGET_H