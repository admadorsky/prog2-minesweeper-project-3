#pragma once

using namespace std ;

enum minesweeper_state {welcome, game, leaderboard, leave} ;

struct cfg_vars {
    int cols = 0 ;
    int rows = 0 ;
    int mines = 0 ;
};

class Minesweeper {
public:
    cfg_vars game_data ;
    minesweeper_state game_state ;
    bool readCfg() ;
};
