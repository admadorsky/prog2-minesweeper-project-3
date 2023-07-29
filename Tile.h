#pragma once

#include <SFML/Graphics.hpp>
using namespace std ;
using namespace sf ;

class Tile {
private:
    Texture t_hidden ;
    Texture t_revealed ;
public:
    Sprite s_hidden ;
    Sprite s_revealed ;
    Tile(int x, int y) ;
};