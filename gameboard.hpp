#ifndef GAMEBOARD_HPP_INCLUDED
#define GAMEBOARD_HPP_INCLUDED

#include "widgets.hpp"
#include "gamecell.hpp"
#include <vector>
#include <memory>

class JatekMester; // el�re deklar�ljuk

class GameBoard : public Widget {
protected:
    int rows, cols;
    int cell_size;
    std::vector<std::vector<std::shared_ptr<GameCell>>> cells;
    JatekMester* mester; // nem saj�t tulajdon � k�v�lr�l �ll�tjuk be
public:
    GameBoard(int x, int y, int cell_size, int rows, int cols);
    void draw() override;
    void handle(genv::event ev) override;
    void set_mester(JatekMester* jm);
    void reset();
    std::shared_ptr<GameCell> get_cell(int row, int col);
};

#endif
