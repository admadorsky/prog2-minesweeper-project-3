#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "LeaderboardWindow.h"
using namespace std ;
using namespace sf ;

LeaderboardWindow::LeaderboardWindow() {
    // initialize infile stream
    ifstream inFile("files/leaderboard.txt") ;
    if (!inFile.is_open()) cout << "failed to open leaderboard.txt file!" << endl ;
    // read leaderboard.txt into vectors
    string current_line ;
    string current_time ;
    string current_name ;
    for (int i = 0; i < 5; i++) {
        getline(inFile, current_line) ;
        current_time = current_line.substr(0, current_line.find(',')) ;
        current_name = current_line.substr(current_line.find(',') + 1) ;
        string row = current_time + "," + current_name ;
        this->vector_lines.push_back(row) ;

        this->str_lines += to_string(i + 1) + ".\t" + row.substr(0, row.find(',')) + "\t" + row.substr(row.find(',') + 1) + "\n\n" ;
    }
}

void LeaderboardWindow::addWinner(string winner_data) {
    fstream outFile("files/leaderboard.txt") ;
    if (!outFile.is_open()) cout << "failed writing to leaderboard.txt file!" << endl ;

    // add winner, sort list, delete last place
    this->vector_lines.push_back(winner_data) ;
    sort(this->vector_lines.begin(), this->vector_lines.end()) ;
    if (this->vector_lines.size() > 5) this->vector_lines.pop_back() ;

    // format the string for display
    this->str_lines.clear() ;
    for (int i = 0; i < this->vector_lines.size(); i++) {
        str_lines += to_string(i + 1) + ".\t" + this->vector_lines.at(i).substr(0, this->vector_lines.at(i).find(',')) + "\t" + this->vector_lines.at(i).substr(this->vector_lines.at(i).find(',') + 1) + "\n\n" ;
    }

    outFile.clear() ;
    for (int i = 0; i < this->vector_lines.size(); i++) {
        outFile << this->vector_lines.at(i) + "\n" ;
    }

}

void LeaderboardWindow::display(Minesweeper & minesweeper, float & width, float & height, Font & font) {
    // initialize text objects
    Text leaderboard_title ;
    Text players ;
    // set text strings for both
    leaderboard_title.setString("LEADERBOARD") ;
    players.setString(this->str_lines) ;
    // set style for both
    leaderboard_title.setStyle(Text::Bold | Text::Underlined) ;
    players.setStyle(Text::Bold) ;
    // set fonts for both
    leaderboard_title.setFont(font) ;
    players.setFont(font) ;
    // set color to white for both
    leaderboard_title.setFillColor(Color::White) ;
    players.setFillColor(Color::White) ;
    // set sizes for both
    leaderboard_title.setCharacterSize(20) ;
    players.setCharacterSize(18) ;
    // make bounding boxes for both text objects
    FloatRect leaderboard_title_box = leaderboard_title.getGlobalBounds() ;
    FloatRect players_box = players.getGlobalBounds() ;
    // set positions based on center... found by subtracting (boundingbox.size / 2)
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