#pragma once
#include <SFML/Graphics.hpp>
#include "Minesweeper.h"
using namespace std ;
using namespace sf ;

enum game_states {running, won, lost, paused, debug, leaderboard};

class GameWindow {
private:
    Texture t_happy_face ;
    Texture t_sad_face ;
    Texture t_win_face ;
    Texture t_play_button ;
    Texture t_pause_button ;
    Texture t_debug_button ;
    Texture t_leaderboard_button ;

public:
    game_states game_state ;

    Sprite s_happy_face ;
    Sprite s_sad_face ;
    Sprite s_win_face ;
    Sprite s_play_button ;
    Sprite s_pause_button ;
    Sprite s_debug_button ;
    Sprite s_leaderboard_button ;

    GameWindow() ;
    void display(Minesweeper & minesweeper, float & width, float & height, Font & font) ;
};
