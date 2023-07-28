#include <SFML/Graphics.hpp>
#include "WelcomeWindow.h"
#include "GameWindow.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std ;
using namespace sf ;

struct cfg_vars {
    int cols = 0 ;
    int rows = 0 ;
    int mines = 0 ;
};

bool readCfg(cfg_vars & vars) ;

enum minesweeper_state {running, leave};
minesweeper_state game_state = running ;

int main() {
    WelcomeWindow welcome_window ;
    GameWindow game_window ;

    cfg_vars vars ;
    // read config data into window
    if (!readCfg(vars)) return 1 ; ;
    //initialize main font
    Font font ;
    // load the main font
    if (!font.loadFromFile("files/font.ttf")) { cout << "cannot find font!" << endl ; } ;

    int width = vars.cols * 32 ;
    int height = ( vars.rows * 32 ) + 100 ;

    while (game_state != leave) {
        welcome_window.display(width, height, font) ;
        if (welcome_window.go_to_game_screen) {
            game_window.display(width, height, font) ;
        }
        return 0;
    }
}


bool readCfg(cfg_vars & vars) {
    // open config file and read into global variables
    ifstream config ;
    config.open("files/board_config.cfg") ;
    if (!config.is_open()) {
        cout << "Failed to open config file!" << endl ;
        return false ;
    }
    config >> vars.cols ;
    config >> vars.rows ;
    config >> vars.mines ;
    return true ;
}
