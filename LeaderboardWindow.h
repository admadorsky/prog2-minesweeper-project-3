#include <SFML/Graphics.hpp>
#include "Minesweeper.h"
#include "GameWindow.h"
using namespace std ;
using namespace sf ;

class LeaderboardWindow {
public:
    vector<string> vector_lines ;
    string str_lines ;
    LeaderboardWindow() ;
    void addWinner(string winner_data) ;
    void display(Minesweeper & minesweeper, float & width, float & height, Font & font) ;
};
