#include "GameWindow.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std ;

void GameWindow::display(int width, int height, sf::Font font) {
    RenderWindow render_window(VideoMode(width, height), "Minesweeper", Style::Close) ;
    cout << "entered game screen!" << endl ;
}