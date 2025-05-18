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
     std::vector<std::string> player_options = {"1 j�t�kos", "2 j�t�kos"};
    player_selector = new DropdownWidget(100, 200, 150, 30, player_options, 2);
}
Screens::~Screens(){
    delete player_selector;
    }

void Screens::run() {
    event ev;

    while (gin >> ev && ev.keycode != key_escape) {

        if (app_state == AppState::StartScreen) {
                gout << move_to(0, 0) << color(0, 0, 139) << box(screen_w, screen_h); // s�t�tk�k h�tt�r

        gout << move_to(100, 100) << color(255, 255, 255)<< text("Am�ba j�t�k - V�lassz j�t�kos sz�mot!");

            // Dropdown megjelen�t�se, kezel�se
            player_selector->handle(ev);
            player_selector->draw();

            int btn_x = 100, btn_y = 260, btn_w = 150, btn_h = 40;
            gout << move_to(btn_x, btn_y) << color(255, 255, 255) << box(btn_w, btn_h);
            gout << move_to(btn_x + 20, btn_y + 25) << color(0, 0, 0) << text("Start j�t�k");

            if (ev.type == ev_mouse && ev.button == btn_left &&
                ev.pos_x >= btn_x && ev.pos_x <= btn_x + btn_w &&
                ev.pos_y >= btn_y && ev.pos_y <= btn_y + btn_h) {

                if (player_selector->get_string_value() == "1 j�t�kos") {
                    jatekos_szam = 1;
                } else {
                    jatekos_szam = 2;
                }
                app_state = AppState::GameScreen;
            }

        } else if (app_state == AppState::GameScreen) {
            if (mester.get_current_player() == X || jatekos_szam == 2) {
                board.handle(ev);
            }

            while (jatekos_szam == 1 && mester.get_current_player() == O && !mester.is_game_over()) {
                    mester.lepes_geppel();
            }
            board.draw();

            if (mester.is_game_over()) {
                app_state = AppState::GameOverScreen;
            }

        } else if (app_state == AppState::GameOverScreen) {
    // H�tt�r letakar�sa (pl. s�t�tsz�rke)
    gout << move_to(0, 0) << color(50, 50, 50) << box(screen_w, screen_h);

    // Sz�vegek
    gout << move_to(100, 100) << color(255, 255, 255) << text("J�t�k v�ge!");
    gout << move_to(100, 140) << text("Nyertes: ") << text(mester.get_winner_name());
    gout << move_to(100, 180) << text("Kattints �j j�t�khoz.");

    // Visszat�r�s a kezd�k�perny�re
    if (ev.type == ev_mouse && ev.button == btn_left) {
        mester.reset();
        app_state = AppState::StartScreen;
    }
}
        gout << refresh;
    }
}

