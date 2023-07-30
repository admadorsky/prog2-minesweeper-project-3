#pragma once

#include <SFML/Graphics.hpp>
using namespace std ;
using namespace sf ;

enum tile_states {hidden, empty, exploded, flagged};

class Tile {
private:
    // texture objects
    Texture t_hidden ;
    Texture t_empty ;
    Texture t_exploded ;
    Texture t_flagged ;
public:
    // member variables
    tile_states tile_state ;
    bool mine ;
    // constructor
    Tile(int x, int y) ;
    // member functions
    void changeState(tile_states new_state) ;
    // sprite objects
    Sprite s_hidden ;
    Sprite s_empty ;
    Sprite s_exploded ;
    Sprite s_flagged ;
};