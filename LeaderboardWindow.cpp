#include <fstream>
#include <iostream>
#include <vector>
#include "LeaderboardWindow.h"
using namespace std ;
using namespace sf ;

void LeaderboardWindow::display(Minesweeper & minesweeper, float & width, float & height, Font & font) {
    // initialize infile stream
    ifstream inFile("files/leaderboard.txt") ;
    if (!inFile.is_open()) cout << "failed to open leaderboard.txt file!" << endl ;
    // read leaderboard.txt into vectors
    string rows = "" ;
    string current_line ;
    string current_time ;
    string current_name ;
    for (int i = 0; i < 5; i++) {
        getline(inFile, current_line) ;
        current_time = current_line.substr(0, current_line.find(',')) ;
        current_name = current_line.substr(current_line.find(',') + 1) ;
        string row = to_string(i + 1) + ".\t" + current_time + "\t" + current_name + "\n\n" ;
        rows += row ;
    }

    Text leaderboard_title ;
    Text players ;

    leaderboard_title.setString("LEADERBOARD") ;
    players.setString(rows) ;

    leaderboard_title.setStyle(Text::Bold | Text::Underlined) ;
    players.setStyle(Text::Bold) ;

    leaderboard_title.setFont(font) ;
    players.setFont(font) ;

    leaderboard_title.setFillColor(Color::White) ;
    players.setFillColor(Color::White) ;

    leaderboard_title.setCharacterSize(20) ;
    players.setCharacterSize(18) ;

    FloatRect leaderboard_title_box = leaderboard_title.getGlobalBounds() ;
    FloatRect players_box = players.getGlobalBounds() ;

    leaderboard_title.setPosition(( width / 4.0f ) - ( leaderboard_title_box.width / 2 ),
                                  ( height / 4.0f ) - 120 - ( leaderboard_title_box.height / 2 )) ;
    players.setPosition(( width / 4.0f ) - ( players_box.width / 2 ),
                        ( height / 4.0f ) + 20 - ( players_box.height / 2 )) ;


    // initialize window
    RenderWindow render_window(VideoMode(width / 2, height / 2), "Minesweeper", Style::Close) ;
    render_window.setFramerateLimit(60) ;

    // allow the player to close the window
    while (render_window.isOpen()) {
        Event event ;
        while (render_window.pollEvent(event)) {
            // if the "x" is pressed, close the window
            if (event.type == Event::Closed) {
                render_window.close();
            }
        }
        // draw text objects
        render_window.clear(Color::Blue) ;
        render_window.draw(leaderboard_title) ;
        render_window.draw(players) ;
        render_window.display() ;
    }
}