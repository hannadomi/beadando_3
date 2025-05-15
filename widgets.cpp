#include "widgets.hpp"

Widget::Widget(int x_, int y_, int w_, int h_) : x(x_), y(y_), width(w_), height(h_) {}

bool Widget::is_selected(int mx, int my) {
    return mx > x && mx < x + width && my > y && my < y + height;
}
