#include "Tile.h"
#include <iostream>

// helper function: sets texture and position of a sprite passed by reference
void setTandP(Sprite & sprite, Texture & texture, int & x, int & y) {
    sprite.setTexture(texture) ;
    sprite.setPosition(x * 32, y * 32) ;
}

// constructor
Tile::Tile(int x, int y) {
    this->tile_state = hidden ;
    this->mine = false ;

    if (!this->t_hidden.loadFromFile("files/images/tile_hidden.png",IntRect(0, 0, 32, 32))) cout << "failed to load hidden tile texture!" << endl ;
    else setTandP(this->s_hidden, t_hidden, x, y) ;

    if (!this->t_empty.loadFromFile("files/images/tile_revealed.png",IntRect(0, 0, 32, 32))) cout << "failed to load empty tile texture!" << endl ;
    else setTandP(this->s_empty, t_empty, x, y) ;

    if (!t_exploded.loadFromFile("files/images/mine.png", IntRect(0, 0, 32, 32))) cout << "failed to load mine texture!" << endl ;
    else setTandP(s_exploded, t_exploded, x, y) ;

    if (!t_flagged.loadFromFile("files/images/flag.png", IntRect(0, 0, 32, 32))) cout << "failed to load flag texture!" << endl ;
    else setTandP(s_flagged, t_flagged, x, y) ;
}

void Tile::changeState(tile_states new_state) {
    this->tile_state = new_state ;
}