#ifndef JATEKMESTER_HPP_INCLUDED
#define JATEKMESTER_HPP_INCLUDED

#include "gameboard.hpp"

class JatekMester {
protected:
    GameBoard* board;
    CellState current_player;
    int rows, cols;
    bool game_over = false;
    CellState winner = EMPTY;
    int jatekos_szam;

public:
    JatekMester(GameBoard* b, int rows, int cols);
    void lepett(int row, int col); // egy játékos lépett
    bool ellenoriz_gyozelem(int row, int col);
    void kovetkezo_jatekos();
    void reset();
    bool is_game_over() const;
    std::string get_winner_name() const;
    void set_jatekos_szam(int szam);

};

#endif
