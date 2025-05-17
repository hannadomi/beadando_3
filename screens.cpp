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
     std::vector<std::string> player_options = {"1 játékos", "2 játékos"};
    player_selector = new DropdownWidget(100, 200, 150, 30, player_options, 2);
}
Screens::~Screens(){
    delete player_selector;
    }

void Screens::run() {
    event ev;

    while (gin >> ev && ev.keycode != key_escape) {
        gout << move_to(0, 0) << color(0, 0, 139) << box(screen_w, screen_h); // sötétkék háttér

        if (app_state == AppState::StartScreen) {
            // Dropdown megjelenítése, kezelése
            player_selector->draw();
            player_selector->handle(ev);

            gout << move_to(100, 100) << color(255, 255, 255)<< text("Amõba játék - Válassz játékos számot!");
            if (ev.type == ev_mouse && ev.button == btn_left) {
                // Itt olvasd ki a kiválasztott játékos számot és állítsd be
                if (player_selector->get_string_value() == "1 játékos") {
                    jatekos_szam = 1;
                } else {
                    jatekos_szam = 2;
                }
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

