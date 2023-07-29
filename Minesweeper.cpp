#include "Minesweeper.h"
#include <iostream>
#include <fstream>
using namespace std ;

bool Minesweeper::readCfg() {
    // open config file and read into global variables
    ifstream config ;
    config.open("files/board_config.cfg") ;
    if (!config.is_open()) {
        cout << "Failed to open config file!" << endl ;
        return false ;
    }
    config >> this->game_data.cols ;
    config >> this->game_data.rows ;
    config >> this->game_data.mines ;
    return true ;
}
