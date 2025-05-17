#include "gamecell.hpp"
#include "graphics.hpp"
#include <cmath>
using namespace genv;

GameCell::GameCell(int x, int y, int w, int h)
    : Widget(x, y, w, h), _state(EMPTY), _highlighted(false) {}

void draw_fake_circle(int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            if (x*x + y*y <= radius*radius) {
                gout << move_to(cx + x, cy + y) << dot;
            }
        }
    }
}


void GameCell::draw() {
    // háttér

    gout << move_to(x, y)
         << color(0, 0, 64) << box(width, height);
         // Keret a cella köré
    gout << move_to(x, y)
         << color(255, 255, 255)
         << line(width, 0)               // felső oldal
         << line(0, height)              // jobb oldal
         << line(-width, 0)              // alsó oldal
         << line(0, -height);            // bal oldal (vissza az elejére)


    if (_highlighted) {
        gout << move_to(x+1, y+1)
             << color(255, 255, 0) << box(width-2, height-2);
    }

    // X vagy O
    if (_state == X) {
        gout << color(255, 0, 0);
        gout << move_to(x+5, y+5) << line(width-10, height-10);
        gout << move_to(x+width-5, y+5) << line(-width+10, height-10);
    } else if (_state == O) {
        gout << color(0, 255, 0);
        draw_fake_circle(x + width / 2, y + height / 2, width / 3);
    }
}



void GameCell::handle(event ev) {
    // ezt inkább a board vagy a JatekMester fogja kezelni, de biztosítjuk az interface-t
}

void GameCell::set_state(CellState s) {
    _state = s;
}

CellState GameCell::get_state() const {
    return _state;
}

void GameCell::highlight(bool h) {
    _highlighted = h;
}
