#include "jatekmester.hpp"
#include <iostream>

JatekMester::JatekMester(GameBoard* b, int r, int c)
    : board(b), current_player(X), rows(r), cols(c)
{
    board->set_mester(this);
}
void JatekMester::set_jatekos_szam(int szam) {
    jatekos_szam = szam; // egy osztálytagot be kell vezetned pl. int jatekos_szam;
}


void JatekMester::lepett(int row, int col) {
    if (game_over) return;

    auto cell = board->get_cell(row, col);
    if (cell->get_state() != EMPTY) return;

    cell->set_state(current_player);

    if (ellenoriz_gyozelem(row, col)) {
        winner = current_player;
        game_over = true;
        std::cout << (current_player == X ? "X" : "O") << " nyert!\n";


    } else {
        kovetkezo_jatekos();
    }
}

void JatekMester::kovetkezo_jatekos() {
    current_player = (current_player == X) ? O : X;
}

bool JatekMester::ellenoriz_gyozelem(int row, int col) {
    const int directions[4][2] = {{1,0},{0,1},{1,1},{1,-1}};
    CellState me = current_player;

    for (auto& [dx, dy] : directions) {
        int count = 1;
        for (int dir = -1; dir <= 1; dir += 2) {
            int r = row + dir * dx;
            int c = col + dir * dy;
            while (r >= 0 && r < rows && c >= 0 && c < cols &&
                   board->get_cell(r,c)->get_state() == me) {
                count++;
                r += dir * dx;
                c += dir * dy;
            }
        }
        if (count >= 5) return true;
    }

    return false;
}
bool JatekMester::is_game_over() const {
    return game_over;
}


std::string JatekMester::get_winner_name() const {
    if (winner == X) return "X";
    if (winner == O) return "O";
    return "Nincs";
}


void JatekMester::reset() {
    board->reset();
    current_player = X;
    game_over = false;
}

