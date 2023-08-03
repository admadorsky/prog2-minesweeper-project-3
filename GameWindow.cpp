#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "Tile.h"
#include "Number.h"
#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std ;
using namespace sf ;

#define within(x,min,max) (x<=max && x>=min)

vector<Tile * > getAdjacents(Minesweeper & minesweeper, int & rows, int & cols, vector<vector<Tile * >> & board, int & i, int & j) ;

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

void GameWindow::display(Minesweeper & minesweeper, float & width, float & height, sf::Font & font) {

    auto clock_start = chrono::high_resolution_clock::now() ;
    auto clock_paused = chrono::high_resolution_clock::now() ;
    auto clock_unpaused = chrono::high_resolution_clock::now() ;
    chrono::duration<double> pause_time_elapsed = (chrono::duration<double>)0 ;
    chrono::duration<double> clock_total ;
    Number seconds_ones(width - 33, (height - 50) - 16) ;
    Number seconds_tens(width - 54, (height - 50) - 16) ;
    Number minutes_ones(width - 76, (height - 50) - 16) ;
    Number minutes_tens(width - 97, (height - 50) - 16) ;
    seconds_ones.number = 0 ;
    seconds_tens.number = 0 ;
    minutes_ones.number = 0 ;
    minutes_tens.number = 0 ;

    // initialize mine counter objects
    int mines_left_counter = minesweeper.game_data.mines ;
    int nonnegative_counter ;
    Number counter_negative(12, ( height - 50 ) - 16) ;
    Number counter_ones(74, ( height - 50 ) - 16) ;
    Number counter_tens(53, ( height - 50 ) - 16) ;
    Number counter_hundreds(32, ( height - 50 ) - 16) ;
    // start the counter at total number of mines
    counter_ones.number = mines_left_counter % 10 ;
    counter_tens.number = (mines_left_counter / 10) % 10 ;
    counter_hundreds.number = (mines_left_counter / 100) % 10 ;
    counter_negative.number = -999 ;

    // initialize button sprites
    s_happy_face.setPosition(( width / 2 ) - 32,( height - 50 ) - 32) ;
    s_sad_face.setPosition(( width / 2 ) - 32,( height - 50 ) - 32) ;
    s_win_face.setPosition(( width / 2 ) - 32,( height - 50 ) - 32) ;
    s_debug_button.setPosition(( width / 2 ) + 96, ( height - 50 ) - 32) ;
    s_pause_button.setPosition(( width / 2 ) + 160, ( height - 50 ) - 32) ;
    s_play_button.setPosition(( width / 2 ) + 160, ( height - 50 ) - 32) ;
    s_leaderboard_button.setPosition(( width / 2 ) + 224, ( height - 50 ) - 32) ;

    // initialize window
    RenderWindow render_window(VideoMode(width, height), "Minesweeper", Style::Close) ;
    render_window.setFramerateLimit(60) ;

    // create & populate the board with default tiles
    vector<vector<Tile * >> board ;
    for (int i = 0; i < minesweeper.game_data.rows; i++) {
        vector<Tile * > current_row ;
        for (int j = 0; j < minesweeper.game_data.cols; j++) {
            Tile * current_tile = new Tile(j, i) ;
            current_row.push_back(current_tile) ;
        }
        board.push_back(current_row) ;
    }

    // assign random tiles to be mines
    srand(time(nullptr)) ;
    // loop until # of bombs specified in config are created
    for (int i = 0; i < minesweeper.game_data.mines; i++) {
        // set the seed to the current time (closest thing to actual random)
        bool mine_created = false ;
        // reassign tiles to be mines
        while (!mine_created) {
            int rand_row = rand() % minesweeper.game_data.rows;
            int rand_col = rand() % minesweeper.game_data.cols;
            // if the tile we want to make into a mine is already one, go next
            if (!board.at(rand_row).at(rand_col)->mine) {
                board.at(rand_row).at(rand_col)->mine = true ;
                // bust out of the loop to generate the next mine
                mine_created = true ;
            }
        }
    }

    // assign numbers to non-mine tiles
    for (int i = 0; i < minesweeper.game_data.rows; i++) {
        for (int j = 0; j < minesweeper.game_data.cols; j++) {
            // create a vector with all surrounding tiles + index error handling
            vector<Tile * > adjacent ;
            adjacent = getAdjacents(minesweeper, minesweeper.game_data.rows, minesweeper.game_data.cols, board, i, j) ;
            int mine_counter = 0 ;
            for (int m = 0; m < adjacent.size(); m++)
                if (adjacent.at(m)->mine) mine_counter++ ;
            board.at(i).at(j)->tile_num = mine_counter ;
        }
    }

    this->game_state = running ;

    // define playable space
    int x_max = minesweeper.game_data.cols * 32 ;
    int y_max = minesweeper.game_data.rows * 32 ;

    while (render_window.isOpen()) {
        // store the # of seconds that have passed since the start, making sure to subtract any time spent while paused/debugging
        auto clock_current = chrono::high_resolution_clock::now();
        chrono::duration<double> pre_paused_time = clock_current - clock_start ;
        clock_total = pre_paused_time - pause_time_elapsed ;

        // check for events
        Event event;
        bool any_left_non_bombs = false ;
        while (render_window.pollEvent(event)) {
            // if the "x" is pressed, close the window
            if (event.type == Event::Closed) {
                minesweeper.game_state = leave;
                render_window.close();
            }
            // player clicked face (restart) button
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (within(event.mouseButton.x, (width / 2) - 32, (width / 2) + 32) &&
                    within(event.mouseButton.y, (height - 50) - 32, (height - 50) + 32)) {
                    for (int i = 0; i < board.size(); i++) {
                        for (int j = 0; j < board.at(i).size(); j++) {
                            delete board.at(i).at(j);
                        }
                    }
                    board.clear();
                    render_window.close();
                    this->display(minesweeper, width, height, font);
                }
            }

            // player clicked pause button
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left &&
            within(event.mouseButton.x, ( width / 2 ) + 160, ( width / 2 ) + 160 + 64) &&
            within(event.mouseButton.y, (height - 50) - 32, (height - 50) + 32)) {
                if (this->game_state == running) {
                    clock_paused = chrono::high_resolution_clock::now() ;
                    this->game_state = paused;
                } else if (this->game_state == paused) {
                    clock_unpaused = chrono::high_resolution_clock::now() ;
                    pause_time_elapsed += clock_unpaused - clock_paused ;
                    clock_total = clock_current - clock_start ;
                    clock_total = clock_total - pause_time_elapsed ;
                    this->game_state = running;
                }
            }

            // player clicked debug button
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left &&
            within(event.mouseButton.x, ( width / 2 ) + 96, ( width / 2 ) + 96 + 64) &&
            within(event.mouseButton.y, (height - 50) - 32, (height - 50) + 32)) {
                if (this->game_state == running | this->game_state == paused) {
                    clock_paused = chrono::high_resolution_clock::now() ;
                    this->game_state = debug;
                } else if (this->game_state == debug) {
                    clock_unpaused = chrono::high_resolution_clock::now() ;
                    pause_time_elapsed += clock_unpaused - clock_paused ;
                    clock_total = clock_current - clock_start ;
                    clock_total = clock_total - pause_time_elapsed ;
                    this->game_state = running;
                }
            }

            if (this->game_state == running) {
                if (event.type == Event::MouseButtonPressed) {
                    // make sure the click event was left click and that it happened inside the window
                    if (event.mouseButton.button == Mouse::Left &&
                    within(event.mouseButton.x, 0, x_max) &&
                    within(event.mouseButton.y, 0, y_max)) {
                        // store tile indices that correspond to the player's click
                        int lclicked_tile_col = event.mouseButton.x / 32;
                        int lclicked_tile_row = event.mouseButton.y / 32;
                        // don't clear tiles that are flagged, even if the user clicks on one
                        if (board.at(lclicked_tile_row).at(lclicked_tile_col)->tile_state != flagged) {
                            // if the tile is a mine and hasn't been revealed or flagged, lose the game
                            if (board.at(lclicked_tile_row).at(lclicked_tile_col)->mine &&
                                board.at(lclicked_tile_row).at(lclicked_tile_col)->tile_state == hidden) {
                                // since the player revealed a bomb, draw the rest: they're a LOSER hahahaha
                                for (int i = 0; i < board.size(); i++) {
                                    // change all mines to exploded state
                                    for (int j = 0; j < board.at(i).size(); j++) {
                                        if (board.at(i).at(j)->mine)
                                            board.at(i).at(j)->tile_state = exploded;
                                    }
                                }
                                this->game_state = lost;
                                // set the counter to 0
                                counter_hundreds.number = 0 ;
                                counter_tens.number = 0 ;
                                counter_ones.number = 0 ;

                            } else {
                                // reveal clicked tile
                                board.at(lclicked_tile_row).at(lclicked_tile_col)->changeState(revealed);
                                vector<Tile *> adjacents;
                                adjacents = getAdjacents(minesweeper, minesweeper.game_data.rows,
                                                         minesweeper.game_data.cols,
                                                         board, lclicked_tile_row, lclicked_tile_col);
                                // find unflagged adjacent mines
                                bool mineless = true;
                                int i = 0;
                                while (mineless && i < adjacents.size()) {
                                    // if i find any mines that aren't flagged, i cannot clear adjacent tiles
                                    if (adjacents.at(i)->mine && adjacents.at(i)->tile_state != flagged) {
                                        mineless = false;
                                    }
                                    i++;
                                }
                                // clear adjacent tiles
                                if (mineless) {
                                    for (int a = 0; a < adjacents.size(); a++) {
                                        if (!adjacents.at(a)->mine) {
                                            adjacents.at(a)->changeState(revealed);
                                        }
                                    }
                                }
                                // clear all empty tiles until there are none left
                                bool none_left_to_clear = false;
                                while (!none_left_to_clear) {
                                    none_left_to_clear = true;
                                    // iterate through all tiles and find revealed empties
                                    for (int y = 0; y < board.size(); y++) {
                                        for (int x = 0; x < board.at(y).size(); x++) {
                                            if (board.at(y).at(x)->tile_state == revealed &&
                                                board.at(y).at(x)->tile_num == 0) {
                                                vector<Tile *> adjacents = getAdjacents(minesweeper,
                                                                                        minesweeper.game_data.rows,
                                                                                        minesweeper.game_data.cols,
                                                                                        board, y, x);
                                                // check whether to continue revealing
                                                for (int a = 0; a < adjacents.size(); a++) {
                                                    if (adjacents.at(a)->tile_num == 0 &&
                                                        adjacents.at(a)->tile_state == hidden)
                                                        none_left_to_clear = false;
                                                    // reveal
                                                    adjacents.at(a)->changeState(revealed);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (event.mouseButton.button == Mouse::Right &&
                    within(event.mouseButton.x, 0, x_max) &&
                    within(event.mouseButton.y, 0, y_max)) {
                        // flag the tile that the player right-clicked on, and decrease mine counter
                        int rclicked_tile_col = event.mouseButton.x / 32;
                        int rclicked_tile_row = event.mouseButton.y / 32;
                        if (board.at(rclicked_tile_row).at(rclicked_tile_col)->tile_state == hidden) {
                            board.at(rclicked_tile_row).at(rclicked_tile_col)->changeState(flagged);
                            mines_left_counter-- ;
                        } else if (board.at(rclicked_tile_row).at(rclicked_tile_col)->tile_state == flagged) {
                            board.at(rclicked_tile_row).at(rclicked_tile_col)->tile_state = hidden;
                            mines_left_counter++;
                        }
                        // assign visual counter digit objects
                        nonnegative_counter = mines_left_counter ;
                        // set the first digit to minus sign if negative
                        if (mines_left_counter < 0) {
                            nonnegative_counter = -mines_left_counter ;
                        }
                        // store each digit in its respective position
                        counter_ones.number = nonnegative_counter % 10 ;
                        counter_tens.number = (nonnegative_counter / 10) % 10 ;
                        counter_hundreds.number = (nonnegative_counter / 100) % 10 ;
                    }
                }
            }

            // check if only bombs are left hidden on the board
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board.at(i).size(); j++) {
                    if ((!board.at(i).at(j)->mine) &&
                        ((board.at(i).at(j)->tile_state == hidden) | (board.at(i).at(j)->tile_state == flagged))) {
                        any_left_non_bombs = true;
                    }
                }
            }
            // if only bombs are left hidden, draw flags on all of them and win the game
            if (any_left_non_bombs == false) {
                // win the game
                this->game_state = won;
                // set the counter to 0
                counter_hundreds.number = 0 ;
                counter_tens.number = 0 ;
                counter_ones.number = 0 ;
                // flag all mines
                for (int i = 0; i < board.size(); i++) {
                    for (int j = 0; j < board.at(i).size(); j++) {
                        if (board.at(i).at(j)->mine) {
                            board.at(i).at(j)->changeState(flagged);
                        }
                    }
                }
            }
        }

        // draw the board
        render_window.clear(Color::White) ;
        // draw mine counter
        if (mines_left_counter < 0) render_window.draw(counter_negative.getDigit()) ;
        render_window.draw(counter_hundreds.getDigit()) ;
        render_window.draw(counter_tens.getDigit()) ;
        render_window.draw(counter_ones.getDigit()) ;

        render_window.draw(s_debug_button) ;
        render_window.draw(s_leaderboard_button) ;
        if (this->game_state == running | this->game_state == paused | this->game_state == debug)
            render_window.draw(s_happy_face) ;
        else if (this->game_state == lost) render_window.draw(s_sad_face) ;
        else if (this->game_state == won) render_window.draw(s_win_face) ;
        if (this->game_state != paused) render_window.draw(s_pause_button) ;
        else render_window.draw(s_play_button) ;
        if (this->game_state == running | this->game_state == won | this->game_state == lost) {
            // draw all tiles
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board.at(i).size(); j++) {
                    // handle each tile state and draw sprites accordingly
                    if (board.at(i).at(j)->tile_state == hidden)
                        render_window.draw(board.at(i).at(j)->s_hidden);
                    else if (board.at(i).at(j)->tile_state == exploded) {
                        render_window.draw(board.at(i).at(j)->s_empty);
                        render_window.draw(board.at(i).at(j)->s_exploded, BlendAlpha);
                    } else if (board.at(i).at(j)->tile_state == flagged) {
                        render_window.draw(board.at(i).at(j)->s_hidden);
                        render_window.draw(board.at(i).at(j)->s_flagged, BlendAlpha);
                    } else if (board.at(i).at(j)->tile_state == revealed && board.at(i).at(j)->tile_num == 0)
                        render_window.draw(board.at(i).at(j)->s_empty);
                    else if (board.at(i).at(j)->tile_state == revealed && board.at(i).at(j)->tile_num == 1) {
                        render_window.draw(board.at(i).at(j)->s_empty);
                        render_window.draw(board.at(i).at(j)->s_one, BlendAlpha);
                    } else if (board.at(i).at(j)->tile_state == revealed && board.at(i).at(j)->tile_num == 2) {
                        render_window.draw(board.at(i).at(j)->s_empty);
                        render_window.draw(board.at(i).at(j)->s_two, BlendAlpha);
                    } else if (board.at(i).at(j)->tile_state == revealed && board.at(i).at(j)->tile_num == 3) {
                        render_window.draw(board.at(i).at(j)->s_empty);
                        render_window.draw(board.at(i).at(j)->s_three, BlendAlpha);
                    } else if (board.at(i).at(j)->tile_state == revealed && board.at(i).at(j)->tile_num == 4) {
                        render_window.draw(board.at(i).at(j)->s_empty);
                        render_window.draw(board.at(i).at(j)->s_four, BlendAlpha);
                    } else if (board.at(i).at(j)->tile_state == revealed && board.at(i).at(j)->tile_num == 5) {
                        render_window.draw(board.at(i).at(j)->s_empty);
                        render_window.draw(board.at(i).at(j)->s_five, BlendAlpha);
                    } else if (board.at(i).at(j)->tile_state == revealed && board.at(i).at(j)->tile_num == 6) {
                        render_window.draw(board.at(i).at(j)->s_empty);
                        render_window.draw(board.at(i).at(j)->s_six, BlendAlpha);
                    } else if (board.at(i).at(j)->tile_state == revealed && board.at(i).at(j)->tile_num == 7) {
                        render_window.draw(board.at(i).at(j)->s_empty);
                        render_window.draw(board.at(i).at(j)->s_seven, BlendAlpha);
                    } else if (board.at(i).at(j)->tile_state == revealed && board.at(i).at(j)->tile_num == 8) {
                        render_window.draw(board.at(i).at(j)->s_empty);
                        render_window.draw(board.at(i).at(j)->s_eight, BlendAlpha);
                    }
                }
            }
        } else if (this->game_state == paused) {
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board.at(i).size(); j++) {
                    render_window.draw(board.at(i).at(j)->s_empty) ;
                }
            }
        } else if (this->game_state == debug) {
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board.at(i).size(); j++) {
                    render_window.draw(board.at(i).at(j)->s_hidden) ;
                    if (board.at(i).at(j)->mine)
                        render_window.draw(board.at(i).at(j)->s_exploded, BlendAlpha) ;
                }
            }
        }

        if (this->game_state == running) {
            // store the # of seconds and minutes separately
            int seconds_total = (int) (clock_total.count()) % 60;
            int minutes_total = (int) (clock_total.count()) / 60;
            // assign each digit individually
            seconds_ones.number = seconds_total % 10;
            seconds_tens.number = (seconds_total / 10) % 10;
            minutes_ones.number = minutes_total % 10;
            minutes_tens.number = (minutes_total / 10) % 10;
        }

        // draw the timer
        render_window.draw(seconds_ones.getDigit()) ;
        render_window.draw(seconds_tens.getDigit()) ;
        render_window.draw(minutes_ones.getDigit()) ;
        render_window.draw(minutes_tens.getDigit()) ;

        render_window.display();
    }
}

vector<Tile * > getAdjacents(Minesweeper & minesweeper, int & rows, int & cols, vector<vector<Tile * >> & board, int & i, int & j) {
    int top = 0 ;
    int bottom = minesweeper.game_data.rows - 1 ;
    int left = 0 ;
    int right = minesweeper.game_data.cols - 1 ;
    vector<Tile * > adjacent ;
    // add left tile
    if (j > left) adjacent.push_back(board.at(i).at(j - 1)) ;
    // add top left tile
    if (j > left && i > top) adjacent.push_back(board.at(i - 1).at(j - 1)) ;
    // add top tile
    if (i > top) adjacent.push_back(board.at(i - 1).at(j)) ;
    // add top right tile
    if (i > top && j < right) adjacent.push_back(board.at(i - 1).at(j + 1)) ;
    // add right tile
    if (j < right) adjacent.push_back(board.at(i).at(j + 1)) ;
    // add bottom right tile
    if (i < bottom && j < right) adjacent.push_back(board.at(i + 1).at(j + 1)) ;
    // add bottom tile
    if (i < bottom) adjacent.push_back(board.at(i + 1).at(j)) ;
    // add bottom left tile
    if (j > left && i < bottom) adjacent.push_back(board.at(i + 1).at(j - 1)) ;

    return adjacent ;
}