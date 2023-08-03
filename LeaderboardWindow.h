#include <SFML/Graphics.hpp>
#include "Minesweeper.h"
#include "GameWindow.h"
using namespace std ;
using namespace sf ;

class LeaderboardWindow {
public:
    void display(Minesweeper & minesweeper, float & width, float & height, Font & font) ;
};
