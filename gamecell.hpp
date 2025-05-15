#ifndef GAMECELL_HPP_INCLUDED
#define GAMECELL_HPP_INCLUDED

#include "widgets.hpp"

enum CellState { EMPTY, X, O };

class GameCell : public Widget {
protected:
    CellState _state;
    bool _highlighted;
public:
    GameCell(int x, int y, int w, int h);
    virtual void draw();
    virtual void handle(genv::event ev);
    void set_state(CellState s);
    CellState get_state() const;
    void highlight(bool h);
};

#endif
