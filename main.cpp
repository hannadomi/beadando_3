#include "gameboard.hpp"
#include "jatekmester.hpp"
#include "screens.hpp"
#include <vector>

using namespace genv;




int main()
{
    int cell_size = 30;
    int rows = 15, cols = 15;
    int screen_w = cols * cell_size;
    int screen_h = rows * cell_size;
    Screens app(15, 15, 30);
    app.run();


    gout.open(screen_w, screen_h);

    GameBoard board(0, 0, cell_size, rows, cols);
    JatekMester mester(&board, rows, cols);

    event ev;
    while(gin >> ev && ev.keycode != key_escape) {
        board.handle(ev);

        gout << move_to(0,0) << color(0,0,0) << box(screen_w, screen_h);
        board.draw();

        gout << refresh;
    }

    return 0;
}
