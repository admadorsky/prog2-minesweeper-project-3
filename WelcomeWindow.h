#include <SFML/Graphics.hpp>
#include "Minesweeper.h"
using namespace std ;
using namespace sf ;

class WelcomeWindow {
public :
    string player_name ;
    void display(Minesweeper & minesweeper, float width, float height, Font font) ;
};
