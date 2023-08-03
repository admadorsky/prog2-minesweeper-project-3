#include "Number.h"
#include <iostream>
using namespace std ;
using namespace sf ;

// helper function: sets texture and position of a sprite passed by reference
void setNumberTandP(Sprite & sprite, Texture & texture, int & x, int & y) {
    sprite.setTexture(texture) ;
    sprite.setPosition(x, y) ;
}

Number::Number(int x, int y) {
    this->number = 0 ;

    if (!this->t_0.loadFromFile("files/images/digits.png",IntRect(0, 0, 21, 32))) cout << "failed to load digits texture!" << endl ;
    else setNumberTandP(this->s_0, t_0, x, y) ;

    if (!this->t_1.loadFromFile("files/images/digits.png",IntRect(21, 0, 21, 32))) cout << "failed to load digits texture!" << endl ;
    else setNumberTandP(this->s_1, t_1, x, y) ;

    if (!this->t_2.loadFromFile("files/images/digits.png",IntRect(42, 0, 21, 32))) cout << "failed to load digits texture!" << endl ;
    else setNumberTandP(this->s_2, t_2, x, y) ;

    if (!this->t_3.loadFromFile("files/images/digits.png",IntRect(63, 0, 21, 32))) cout << "failed to load digits texture!" << endl ;
    else setNumberTandP(this->s_3, t_3, x, y) ;

    if (!this->t_4.loadFromFile("files/images/digits.png",IntRect(84, 0, 21, 32))) cout << "failed to load digits texture!" << endl ;
    else setNumberTandP(this->s_4, t_4, x, y) ;

    if (!this->t_5.loadFromFile("files/images/digits.png",IntRect(105, 0, 21, 32))) cout << "failed to load digits texture!" << endl ;
    else setNumberTandP(this->s_5, t_5, x, y) ;

    if (!this->t_6.loadFromFile("files/images/digits.png",IntRect(126, 0, 21, 32))) cout << "failed to load digits texture!" << endl ;
    else setNumberTandP(this->s_6, t_6, x, y) ;

    if (!this->t_7.loadFromFile("files/images/digits.png",IntRect(147, 0, 21, 32))) cout << "failed to load digits texture!" << endl ;
    else setNumberTandP(this->s_7, t_7, x, y) ;

    if (!this->t_8.loadFromFile("files/images/digits.png",IntRect(168, 0, 21, 32))) cout << "failed to load digits texture!" << endl ;
    else setNumberTandP(this->s_8, t_8, x, y) ;

    if (!this->t_9.loadFromFile("files/images/digits.png",IntRect(189, 0, 21, 32))) cout << "failed to load digits texture!" << endl ;
    else setNumberTandP(this->s_9, t_9, x, y) ;

    if (!this->t_minus.loadFromFile("files/images/digits.png",IntRect(210, 0, 21, 32))) cout << "failed to load digits texture!" << endl ;
    else setNumberTandP(this->s_minus, t_minus, x, y) ;
}

Sprite Number::getDigit() {
    if (this->number == -999) return s_minus ;
    else if (this->number == 0) return s_0 ;
    else if (this->number == 1) return s_1 ;
    else if (this->number == 2) return s_2 ;
    else if (this->number == 3) return s_3 ;
    else if (this->number == 4) return s_4 ;
    else if (this->number == 5) return s_5 ;
    else if (this->number == 6) return s_6 ;
    else if (this->number == 7) return s_7 ;
    else if (this->number == 8) return s_8 ;
    else if (this->number == 9) return s_9 ;
    else return s_0 ;
}