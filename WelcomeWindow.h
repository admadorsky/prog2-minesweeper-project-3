#ifndef PROJECT3_WELCOMEWINDOW_H
#define PROJECT3_WELCOMEWINDOW_H
#include <string>
#include <SFML/Graphics.hpp>
using namespace std ;
using namespace sf ;

class WelcomeWindow {
public :
    string player_name ;
    bool go_to_game_screen = false ;
    void display(int width, int height, Font font) ;
};

#endif //PROJECT3_WELCOMEWINDOW_H
