#ifndef DROPDOWNWIDGET_HPP_INCLUDED
#define DROPDOWNWIDGET_HPP_INCLUDED
#include "widgets.hpp"
#include <vector>
#include <string>

class DropdownWidget : public Widget {
    std::vector<std::string> options;
    int selected_index;
    bool expanded;
    int visible_items;
    void drawDownArrow(int x, int y, int size);
public:
    DropdownWidget(int x, int y, int w, int h, const std::vector<std::string>& opts, int visible);
    void draw() override;
    void handle(genv::event ev) override;
    std::string get_string_value() override;
    std::string get_selected_text() const;

};

#endif // DROPDOWNWIDGET_HPP_INCLUDED
