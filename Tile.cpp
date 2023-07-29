#include "Tile.h"
#include <iostream>

void setTandP(Sprite & sprite, Texture & texture, int & x, int & y) {
    sprite.setTexture(texture) ;
    sprite.setPosition(x * 32, y * 32) ;
}

Tile::Tile(int x, int y) {
    if (!t_hidden.loadFromFile("files/images/tile_hidden.png",IntRect(0, 0, 32, 32))) {
        cout << "failed to load hidden tile texture!" << endl ;
    } else {
        setTandP(this->s_hidden, t_hidden, x, y) ;
    }

    if (!t_revealed.loadFromFile("files/images/tile_revealed.png",IntRect(0, 0, 32, 32))) {
        cout << "failed to load revealed tile texture!" << endl ;
    } else {
        setTandP(this->s_revealed, t_revealed, x, y) ;
    }
}