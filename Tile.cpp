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
    this->tile_num = 0 ;

    if (!this->t_hidden.loadFromFile("files/images/tile_hidden.png",IntRect(0, 0, 32, 32))) cout << "failed to load hidden tile texture!" << endl ;
    else setTandP(this->s_hidden, t_hidden, x, y) ;

    if (!this->t_empty.loadFromFile("files/images/tile_revealed.png",IntRect(0, 0, 32, 32))) cout << "failed to load empty tile texture!" << endl ;
    else setTandP(this->s_empty, t_empty, x, y) ;

    if (!t_exploded.loadFromFile("files/images/mine.png", IntRect(0, 0, 32, 32))) cout << "failed to load mine texture!" << endl ;
    else setTandP(s_exploded, t_exploded, x, y) ;

    if (!t_flagged.loadFromFile("files/images/flag.png", IntRect(0, 0, 32, 32))) cout << "failed to load flag texture!" << endl ;
    else setTandP(s_flagged, t_flagged, x, y) ;

    if (!t_one.loadFromFile("files/images/number_1.png", IntRect(0, 0, 32, 32))) cout << "failed to load #1 texture!" << endl ;
    else setTandP(s_one, t_one, x, y) ;

    if (!t_two.loadFromFile("files/images/number_2.png", IntRect(0, 0, 32, 32))) cout << "failed to load #2 texture!" << endl ;
    else setTandP(s_two, t_two, x, y) ;

    if (!t_three.loadFromFile("files/images/number_3.png", IntRect(0, 0, 32, 32))) cout << "failed to load #3 texture!" << endl ;
    else setTandP(s_three, t_three, x, y) ;

    if (!t_four.loadFromFile("files/images/number_4.png", IntRect(0, 0, 32, 32))) cout << "failed to load #4 texture!" << endl ;
    else setTandP(s_four, t_four, x, y) ;

    if (!t_five.loadFromFile("files/images/number_5.png", IntRect(0, 0, 32, 32))) cout << "failed to load #5 texture!" << endl ;
    else setTandP(s_five, t_five, x, y) ;

    if (!t_six.loadFromFile("files/images/number_6.png", IntRect(0, 0, 32, 32))) cout << "failed to load #6 texture!" << endl ;
    else setTandP(s_six, t_six, x, y) ;

    if (!t_seven.loadFromFile("files/images/number_7.png", IntRect(0, 0, 32, 32))) cout << "failed to load #7 texture!" << endl ;
    else setTandP(s_seven, t_seven, x, y) ;

    if (!t_eight.loadFromFile("files/images/number_8.png", IntRect(0, 0, 32, 32))) cout << "failed to load #8 texture!" << endl ;
    else setTandP(s_eight, t_eight, x, y) ;
}

void Tile::changeState(tile_states new_state) {
    this->tile_state = new_state ;
}