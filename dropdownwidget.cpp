#include "dropdownwidget.hpp"
#include "graphics.hpp"
using namespace genv;

DropdownWidget::DropdownWidget(int x, int y, int w, int h, const std::vector<std::string>& opts, int visible)
    : Widget(x, y, w, h), options(opts), selected_index(0), expanded(false), visible_items(visible) {}


void DropdownWidget::drawDownArrow(int x, int y, int size) {
    gout << move_to(x, y) << line_to(x + size, y)
         << line_to(x + size/2, y + size) << line_to(x, y);
}
void DropdownWidget::draw() {
    // H�tt�r kirajzol�sa
    gout << move_to(x, y) << color(220, 220, 220) << box(width, height);

    // Sz�veg k�z�pre igaz�t�sa (v�zszintes �s f�gg�leges)
    std::string current_text = options[selected_index];
    int text_width = gout.twidth(current_text);
    int text_height = gout.cascent() + gout.cdescent(); // Sz�veg magass�ga
    int text_x = x + (width - text_width) / 2;
    int text_y = y + (height - text_height) / 2 + gout.cascent(); // Pontos f�gg�leges k�z�pre

    gout << move_to(text_x, text_y) << color(0, 0, 0) << text(current_text);
    int arrow_size = 10;
    int arrow_x = x + width - 13;

    // Felfel� ny�l (fels� fel�ben)
    gout << color(255, 0, 0); // Piros
    drawDownArrow(arrow_x, y+15, arrow_size);
    /*
    // Ny�l poz�ci�ja (f�gg�legesen k�z�pre igaz�tva)
    int arrow_x = x + width - 15;
    int arrow_y = y + (height - gout.cascent()) / 2;
    gout << move_to(arrow_x, arrow_y) << text("v");*/

    // Leg�rd�l� lista megjelen�t�se
    if (expanded) {
        for (int i = 0; i < visible_items && i < options.size(); ++i) {
            int item_y = y + height * (i + 1);
            gout << move_to(x, item_y) << color(240, 240, 240) << box(width, height);

            // Listaelem sz�veg k�z�pre igaz�t�sa
            std::string item_text = options[i];
            int item_text_width = gout.twidth(item_text);
            int item_text_height = gout.cascent() + gout.cdescent();
            int item_text_x = x + (width - item_text_width) / 2;
            int item_text_y = item_y + (height - item_text_height) / 2 + gout.cascent();

            gout << move_to(item_text_x, item_text_y)
                 << color(0, 0, 0) << text(item_text);
        }
    }
}

void DropdownWidget::handle(event ev) {
    // Kattint�s a lenyit�sra
    if (ev.type == ev_mouse && ev.button == btn_left) {
        if (is_selected(ev.pos_x, ev.pos_y)) {
            expanded = !expanded;
        } else if (expanded) {
            // Kiv�laszt�s a leg�rd�l� list�b�l
            for (int i = 0; i < visible_items && i < options.size(); i++) {
                int item_y = y + height * (i + 1);
                if (ev.pos_x > x && ev.pos_x < x + width &&
                    ev.pos_y > item_y && ev.pos_y < item_y + height) {
                    selected_index = i;
                    expanded = false;
                    break;
                }
            }
        } else {
            expanded = false;
        }
    }


    if (ev.type == ev_key && expanded) {
        if (ev.keycode == key_up && selected_index > 0) {
            selected_index--;
        }
        if (ev.keycode == key_down && selected_index < options.size() - 1) {
            selected_index++;
        }
    }


    if (ev.type == ev_mouse && expanded) {
        if (ev.button == btn_wheelup && selected_index > 0) {
            selected_index--;
        }
        if (ev.button == btn_wheeldown && selected_index < options.size() - 1) {
            selected_index++;
        }
    }
}



std::string DropdownWidget::get_string_value() {
    return options[selected_index];
}
