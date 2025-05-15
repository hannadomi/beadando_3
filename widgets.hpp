#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED


#include "graphics.hpp"

class Widget {
protected:
    int x, y, width, height;
public:
    Widget(int x, int y, int w, int h);
    virtual void draw() = 0;
    virtual void handle(genv::event ev) = 0;
    virtual bool is_selected(int mx, int my);
    virtual std::string get_string_value() { return ""; }
    virtual int get_int_value() { return 0; }
    virtual ~Widget() {}
};



#endif // WIDGETS_HPP_INCLUDED
