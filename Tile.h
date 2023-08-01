#pragma once

#include <SFML/Graphics.hpp>
using namespace std ;
using namespace sf ;

enum tile_states {hidden, revealed, exploded, flagged};

class Tile {
private:
    // texture objects
    Texture t_hidden ;
    Texture t_empty ;
    Texture t_exploded ;
    Texture t_flagged ;
    Texture t_one ;
    Texture t_two ;
    Texture t_three ;
    Texture t_four ;
    Texture t_five ;
    Texture t_six ;
    Texture t_seven ;
    Texture t_eight ;

public:
    // member variables
    tile_states tile_state ;
    bool mine ;
    int tile_num ;
    // constructor
    Tile(int x, int y) ;
    // member functions
    void changeState(tile_states new_state) ;
    // sprite objects
    Sprite s_hidden ;
    Sprite s_empty ;
    Sprite s_exploded ;
    Sprite s_flagged ;
    Sprite s_one ;
    Sprite s_two ;
    Sprite s_three ;
    Sprite s_four ;
    Sprite s_five ;
    Sprite s_six ;
    Sprite s_seven ;
    Sprite s_eight ;
};