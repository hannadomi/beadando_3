#ifndef SCREENS_HPP_INCLUDED
#define SCREENS_HPP_INCLUDED
#include "gameboard.hpp"
#include "jatekmester.hpp"
#include "graphics.hpp"
using namespace genv;

enum class AppState {
    StartScreen,
    GameScreen,
    GameOverScreen
};

class Screens {
private:
    int screen_w, screen_h;
    int rows, cols, cell_size;
    AppState app_state;

    GameBoard board;
    JatekMester mester;

public:
    Screens(int r, int c, int cs);
    void run();
};

#endif // SCREENS_HPP_INCLUDED
