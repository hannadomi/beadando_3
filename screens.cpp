#include "screens.hpp"

using namespace genv;

Screens::Screens(int r, int c, int cs)
    : rows(r), cols(c), cell_size(cs),
      screen_w(c * cs), screen_h(r * cs),
      board(0, 0, cs, r, c),
      mester(&board, r, c),
      app_state(AppState::StartScreen)
{
    gout.open(screen_w, screen_h);
}

void Screens::run() {
    event ev;

    while (gin >> ev && ev.keycode != key_escape) {
        gout << move_to(0, 0) << color(0, 0, 0) << box(screen_w, screen_h);

        if (app_state == AppState::StartScreen) {
            gout << move_to(100, 100) << color(255, 255, 255)
                 << text("Amõba játék - Kattints a kezdéshez!");
            if (ev.type == ev_mouse && ev.button == btn_left) {
                app_state = AppState::GameScreen;
            }

        } else if (app_state == AppState::GameScreen) {
            board.handle(ev);
            board.draw();

            if (mester.is_game_over()) {
                app_state = AppState::GameOverScreen;
            }

        } else if (app_state == AppState::GameOverScreen) {
            gout << move_to(100, 100) << color(255, 255, 255)
                 << text("Játék vége!");
            gout << move_to(100, 140) << text("Nyertes: ")
                 << text(mester.get_winner_name());
            gout << move_to(100, 180) << text("Kattints új játékhoz.");
            if (ev.type == ev_mouse && ev.button == btn_left) {
                mester.reset();
                app_state = AppState::StartScreen;
            }
        }

        gout << refresh;
    }
}
