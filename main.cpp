#include <SFML/Graphics.hpp>
#include "Minesweeper.h"
#include "WelcomeWindow.h"
#include "GameWindow.h"
#include "LeaderboardWindow.h"
#include <iostream>
using namespace std ;
using namespace sf ;

Minesweeper minesweeper ;

int main() {
    // create window class instances
    WelcomeWindow welcome_window ;
    GameWindow game_window ;

    // read config data into window, return 1 if it fails
    if (!minesweeper.readCfg()) return 1 ;
    // initialize main font
    Font font ;
    // load the main font
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "cannot find font!" << endl ;
        return 1 ;
    }

    // calculate window width and height
    float width = minesweeper.game_data.cols * 32 ;
    float height = ( minesweeper.game_data.rows * 32 ) + 100 ;

    // start with the welcome window
    minesweeper.game_state = welcome ;

    // run the game until the user exits
    while (minesweeper.game_state != leave) {
        if (minesweeper.game_state == welcome) welcome_window.display(minesweeper, width, height, font) ;
        else if (minesweeper.game_state == game) game_window.display(minesweeper, width, height, font) ;
    }

    return 0;
}
