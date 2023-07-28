#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std ;

struct cfg_vars {
    int cols = 0 ;
    int rows = 0 ;
    int mines = 0 ;
};

void readCfg(cfg_vars & vars) {
    // open config file and read into global variables
    ifstream config ;
    config.open("files/board_config.cfg") ;
    if (!config.is_open()) {
        cout << "Failed to open config file!" << endl ;
        return ;
    }

    config >> vars.cols ;
    config >> vars.rows ;
    config >> vars.mines ;

    // DEBUG
    cout << "cols: " << vars.cols << endl ;
    cout << "rows: " << vars.rows << endl ;
    cout << "mines: " << vars.mines << endl ;
}

// create the render window
int width ;
int height ;

//initialize main font
sf::Font font ;

// initialize game states
bool welcome_screen = true ;
bool game_screen = false ;
bool leaderboard_screen = false ;

int main() {
    cfg_vars vars ;
    // read config data into window
    readCfg(vars) ;
    // load the main font
    if (!font.loadFromFile("files/font.ttf")) { cout << "cannot find font!" << endl ; } ;

    width = vars.cols * 32 ;
    height = ( vars.rows * 32 ) + 100 ;
    sf::RenderWindow render_window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close) ;

    cout << "width: " << width << endl ;
    cout << "height: " << height << endl ;

    string player_name ;
    while (render_window.isOpen()) {
        render_window.clear(sf::Color::Blue) ;
        if (welcome_screen) {
            // initialize text objects
            sf::Text welcome_title ;
            sf::Text prompt ;
            sf::Text name ;
            // set strings
            welcome_title.setString("WELCOME TO MINESWEEPER!") ;
            prompt.setString("Enter your name:") ;
            name.setString(player_name + "|") ;
            // set fonts to main font
            welcome_title.setFont(font) ;
            prompt.setFont(font) ;
            name.setFont(font) ;
            // set colors
            welcome_title.setFillColor(sf::Color::White) ;
            prompt.setFillColor(sf::Color::White) ;
            name.setFillColor(sf::Color::Yellow) ;
            // set styles
            welcome_title.setStyle(sf::Text::Bold | sf::Text::Underlined) ;
            prompt.setStyle(sf::Text::Bold) ;
            name.setStyle(sf::Text::Bold) ;
            // set sizes
            welcome_title.setCharacterSize(24) ;
            prompt.setCharacterSize(20) ;
            name.setCharacterSize(18) ;
            // create bounding rectangles
            sf::FloatRect welcome_title_boundingbox = welcome_title.getGlobalBounds() ;
            sf::FloatRect prompt_boundingbox = prompt.getGlobalBounds() ;
            sf::FloatRect name_boundingbox = name.getGlobalBounds() ;
            // set origins using center coordinates - (1/2 width or height) -> to get top left corner
            welcome_title.setPosition(( width / 2.0f ) - ( welcome_title_boundingbox.width / 2.0f ),
                                      (height / 2.0f) - ( welcome_title_boundingbox.height / 2.0f ) - 150 ) ;
            prompt.setPosition(( width / 2.0f ) - ( prompt_boundingbox.width / 2.0f ),
                               (height / 2.0f) - ( prompt_boundingbox.height / 2.0f ) - 75) ;
            name.setPosition(( width / 2.0f ) - ( name_boundingbox.width / 2.0f ),
                             ( height / 2.0f ) - ( name_boundingbox.height / 2.0f ) - 45 ) ;

            // draw the text
            render_window.draw(welcome_title) ;
            render_window.draw(prompt) ;
            render_window.draw(name) ;

            sf::Event event ;
            while (render_window.pollEvent(event)) {
                // if the "x" is pressed, close the window
                if (event.type == sf::Event::Closed) render_window.close();
                // if the user starts typing, execute the following
                else if (event.type == sf::Event::TextEntered) {
                    // make sure a letter was entered
                    if (event.text.unicode <= 122 && event.text.unicode >= 65 && player_name.length() <= 11) {
                        // if the first letter input is lowercase, capitalize it
                        if (player_name.length() == 0 && event.text.unicode >= 97 && event.text.unicode <= 122) {
                            player_name += (static_cast<char>(event.text.unicode - 32));
                        } // if the following letters input are uppercase, un-capitalize them
                        else if (player_name.length() > 0 && event.text.unicode >= 65 && event.text.unicode <= 90) {
                            player_name += (static_cast<char>(event.text.unicode + 32)) ;
                        } else
                        // otherwise, simply add what was typed
                        player_name += (static_cast<char>(event.text.unicode)) ;
                    } else if (event.text.unicode == 8 && player_name.length() > 0) {
                        player_name.pop_back() ;
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    render_window.close();
                }
            }
        }
        // end the current frame
        render_window.display();
    }

    return 0 ;
}
