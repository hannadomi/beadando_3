#include "gameboard.hpp"
#include "jatekmester.hpp"
#include "graphics.hpp"
using namespace genv;

GameBoard::GameBoard(int x_, int y_, int cell_size_, int rows_, int cols_)
    : Widget(x_, y_, cols_ * cell_size_, rows_ * cell_size_),
      rows(rows_), cols(cols_), cell_size(cell_size_), mester(nullptr)
{
    for (int i = 0; i < rows; ++i) {
        std::vector<std::shared_ptr<GameCell>> row;
        for (int j = 0; j < cols; ++j) {
            int cx = x + j * cell_size;
            int cy = y + i * cell_size;
            row.push_back(std::make_shared<GameCell>(cx, cy, cell_size, cell_size));
        }
        cells.push_back(row);
    }
}

void GameBoard::draw() {
    for (auto& row : cells) {
        for (auto& cell : row) {
            cell->draw();
        }
    }
}

void GameBoard::handle(event ev) {
      for (auto& row_vec : cells) {
        for (auto& cell : row_vec) {
            cell->highlight(false);
        }
    }
     if (ev.type == ev_mouse) {
        int col = (ev.pos_x - x) / cell_size;
        int row = (ev.pos_y - y) / cell_size;

        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            cells[row][col]->highlight(true);
        }

        // Ha kattint�s is t�rt�nt, akkor l�p�s
        if (ev.button == btn_left && mester) {
            mester->lepett(row, col);
        }
    }
}

void GameBoard::set_mester(JatekMester* jm) {
    mester = jm;
}

void GameBoard::reset() {
    for (auto& row : cells) {
        for (auto& cell : row) {
            cell->set_state(EMPTY);
        }
    }
}

std::shared_ptr<GameCell> GameBoard::get_cell(int row, int col) {
    return cells[row][col];
}
CellState GameBoard::get(int row, int col) const {
    return cells[row][col]->get_state();
}


