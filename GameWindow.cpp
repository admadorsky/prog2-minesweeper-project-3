#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "Tile.h"
#include <iostream>
#include <algorithm>
using namespace std ;
using namespace sf ;

#define within(x,min,max) (x<=max && x>=min)

GameWindow::GameWindow() {
    if (!this->t_happy_face.loadFromFile("files/images/face_happy.png",IntRect(0, 0, 64, 64)))
        cout << "failed to load happy face texture!" << endl ;
    else s_happy_face.setTexture(t_happy_face) ;

    if (!this->t_sad_face.loadFromFile("files/images/face_lose.png",IntRect(0, 0, 64, 64)))
        cout << "failed to load sad face texture!" << endl ;
    else s_sad_face.setTexture(t_sad_face) ;

    if (!this->t_win_face.loadFromFile("files/images/face_win.png",IntRect(0, 0, 64, 64)))
        cout << "failed to load win face texture!" << endl ;
    else s_win_face.setTexture(t_win_face) ;

    if (!this->t_play_button.loadFromFile("files/images/play.png",IntRect(0, 0, 64, 64)))
        cout << "failed to load play button texture!" << endl ;
    else s_play_button.setTexture(t_play_button) ;

    if (!this->t_pause_button.loadFromFile("files/images/pause.png",IntRect(0, 0, 64, 64)))
        cout << "failed to load pause button texture!" << endl ;
    else s_pause_button.setTexture(t_pause_button) ;

    if (!this->t_debug_button.loadFromFile("files/images/debug.png",IntRect(0, 0, 64, 64)))
        cout << "failed to load debug button texture!" << endl ;
    else s_debug_button.setTexture(t_debug_button) ;

    if (!this->t_leaderboard_button.loadFromFile("files/images/leaderboard.png",IntRect(0, 0, 64, 64)))
        cout << "failed to load leaderboard button texture!" << endl ;
    else s_leaderboard_button.setTexture(t_leaderboard_button) ;
}

void GameWindow::display(Minesweeper & minesweeper, float width, float height, sf::Font font) {

    s_happy_face.setPosition(( width / 2 ) - 32,( height - 50 ) - 32) ;
    s_sad_face.setPosition(( width / 2 ) - 32,( height - 50 ) - 32) ;
    s_win_face.setPosition(( width / 2 ) - 32,( height - 50 ) - 32) ;
    s_debug_button.setPosition(( width / 2 ) + 96, ( height - 50 ) - 32) ;
    s_pause_button.setPosition(( width / 2 ) + 160, ( height - 50 ) - 32) ;
    s_play_button.setPosition(( width / 2 ) + 160, ( height - 50 ) - 32) ;
    s_leaderboard_button.setPosition(( width / 2 ) + 224, ( height - 50 ) - 32) ;

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

    // loop until # of bombs specified in config are created
    for (int i = 0; i < minesweeper.game_data.mines; i++) {
        // set the seed to the current time (closest thing to actual random)
        srand(time(NULL)) ;
        bool mine_created = false ;
        // reassign tiles to be mines
        while (!mine_created) {
            int rand_row = rand() % minesweeper.game_data.rows;
            int rand_col = rand() % minesweeper.game_data.cols;
            // if the tile we want to make into a mine is already one, go next
            if (!board.at(rand_row).at(rand_col).mine) {
                board.at(rand_row).at(rand_col).mine = true ;
                // bust out of the loop to generate the next mine
                mine_created = true ;
            }
        }
    }

    this->game_state = running ;

    while (render_window.isOpen()) {
        // check for events
        Event event;
        while (render_window.pollEvent(event)) {
            // if the "x" is pressed, close the window
            if (event.type == Event::Closed) {
                minesweeper.game_state = leave ;
                render_window.close() ;
            } else if (this->game_state == running) {
                if (event.type == Event::MouseButtonPressed) {
                    // store the bounds for mouse click events
                    int x_max = minesweeper.game_data.cols * 32 ;
                    int y_max = minesweeper.game_data.rows * 32 ;
                    // make sure the click event was left click and that it happened inside the window
                    if (event.mouseButton.button == Mouse::Left && within(event.mouseButton.x, 0, x_max) &&
                        within(event.mouseButton.y, 0, y_max)) {
                        // store tile indices that correspond to the player's click
                        int lclicked_tile_col = event.mouseButton.x / 32 ;
                        int lclicked_tile_row = event.mouseButton.y / 32 ;
                        // if the tile is a mine and hasn't been revealed or flagged, lose the game
                        if (board.at(lclicked_tile_row).at(lclicked_tile_col).mine &&
                            board.at(lclicked_tile_row).at(lclicked_tile_col).tile_state == hidden) {
                            // since the player revealed a bomb, draw the rest: they're a LOSER hahahaha
                            for (int i = 0; i < board.size(); i++) {
                                // change all mines to exploded state
                                for (int j = 0; j < board.at(i).size(); j++) {
                                    if (board.at(i).at(j).mine)
                                        board.at(i).at(j).tile_state = exploded ;
                                }
                            }
                            this->game_state = lost ;
                        } else board.at(lclicked_tile_row).at(lclicked_tile_col).changeState(empty) ;
                    } else if (event.mouseButton.button == Mouse::Right && within(event.mouseButton.x, 0, x_max) &&
                               within(event.mouseButton.y, 0, y_max)) {
                        // flag the tile that the player right-clicked on
                        int rclicked_tile_col = event.mouseButton.x / 32 ;
                        int rclicked_tile_row = event.mouseButton.y / 32 ;
                        board.at(rclicked_tile_row).at(rclicked_tile_col).changeState(flagged) ;
                    }
                }
            }
        }

        // draw the board
        render_window.clear(Color::White) ;
        if (this->game_state == running) render_window.draw(s_happy_face) ;
        else if (this->game_state == lost) render_window.draw(s_sad_face) ;
        else if (this->game_state == won) render_window.draw(s_win_face) ;
        render_window.draw(s_debug_button) ;
        render_window.draw(s_pause_button) ;
        render_window.draw(s_leaderboard_button) ;

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.at(i).size(); j++) {
                if (board.at(i).at(j).tile_state == hidden) render_window.draw(board.at(i).at(j).s_hidden) ;
                else if (board.at(i).at(j).tile_state == empty) render_window.draw(board.at(i).at(j).s_empty) ;
                else if (board.at(i).at(j).tile_state == exploded) {
                    render_window.draw(board.at(i).at(j).s_empty) ;
                    render_window.draw(board.at(i).at(j).s_exploded, BlendAlpha) ; }
                else if (board.at(i).at(j).tile_state == flagged) {
                    render_window.draw(board.at(i).at(j).s_hidden) ;
                    render_window.draw(board.at(i).at(j).s_flagged) ;
                }
            }
        }
        render_window.display();
    }
}