#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "Tile.h"
#include <iostream>
using namespace std ;
using namespace sf ;

void GameWindow::display(Minesweeper & minesweeper, float width, float height, sf::Font font) {
    RenderWindow render_window(VideoMode(width, height), "Minesweeper", Style::Close) ;
    render_window.setFramerateLimit(60) ;

    vector<vector<Tile>> board ;
    for (int i = 0; i < minesweeper.game_data.rows; i++) {
        vector<Tile> current_row ;
        for (int j = 0; j < minesweeper.game_data.cols; j++) {
            Tile current_tile(j, i) ;
            current_row.push_back(current_tile) ;
        }
        board.push_back(current_row) ;
    }

    while (render_window.isOpen()) {

        Event event;
        while (render_window.pollEvent(event)) {
            // if the "x" is pressed, close the window
            if (event.type == Event::Closed) {
                minesweeper.game_state = leave;
                render_window.close();
            }
        }

        render_window.clear(Color::White) ;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.at(i).size(); j++) {
                render_window.draw(board.at(i).at(j).s_hidden) ;
            }
        }

        render_window.display();
    }
}