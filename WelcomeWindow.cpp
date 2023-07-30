#include "WelcomeWindow.h"
#include <iostream>
using namespace std ;

#define within(x,min,max) (x<=max && x>=min)

void WelcomeWindow::display(Minesweeper & minesweeper, float width, float height, sf::Font font) {
    RenderWindow render_window(VideoMode(width, height), "Minesweeper", Style::Close) ;
    render_window.setFramerateLimit(60) ;
    // initialize text objects
    Text welcome_title;
    Text prompt;
    Text name;
    welcome_title.setString("WELCOME TO MINESWEEPER!");
    prompt.setString("Enter your name:");
    welcome_title.setFont(font);
    prompt.setFont(font);
    name.setFont(font);
    welcome_title.setFillColor(Color::White);
    prompt.setFillColor(Color::White);
    name.setFillColor(Color::Yellow);
    welcome_title.setStyle(Text::Bold | Text::Underlined);
    prompt.setStyle(Text::Bold);
    name.setStyle(Text::Bold);
    welcome_title.setCharacterSize(24);
    prompt.setCharacterSize(20);
    name.setCharacterSize(18);
    FloatRect welcome_title_boundingbox = welcome_title.getGlobalBounds();
    FloatRect prompt_boundingbox = prompt.getGlobalBounds();
    // set text positions using center coordinates - (1/2 width or height) -> to get top left corner
    welcome_title.setPosition((width / 2.0f) - (welcome_title_boundingbox.width / 2.0f),
                              (height / 2.0f) - (welcome_title_boundingbox.height / 2.0f) - 150);
    prompt.setPosition((width / 2.0f) - (prompt_boundingbox.width / 2.0f),
                       (height / 2.0f) - (prompt_boundingbox.height / 2.0f) - 75);

    while (render_window.isOpen()) {
        name.setString(this->player_name + "|");
        FloatRect name_boundingbox = name.getGlobalBounds();
        name.setPosition((width / 2.0f) - (name_boundingbox.width / 2.0f),
                         (height / 2.0f) - (name_boundingbox.height / 2.0f) - 45);

        Event event;
        while (render_window.pollEvent(event)) {
            // if the "x" is pressed, close the window
            if (event.type == Event::Closed) {
                minesweeper.game_state = leave ;
                render_window.close();
            }
            // if the user starts typing, execute the following
            else if (event.type == Event::TextEntered) {
                // make sure a letter was entered

                if (within(event.text.unicode,'a','z') | within(event.text.unicode, 'A', 'Z') && this->player_name.length() <= 9) {
                    // if the first letter input is lowercase, capitalize it
                    if (this->player_name.length() == 0 && within(event.text.unicode, 'a', 'z')) {
                        this->player_name += (static_cast<char>(event.text.unicode - 32)) ;
                    } // if the following letters input are uppercase, un-capitalize them
                    else if (this->player_name.length() > 0 && within(event.text.unicode, 'A', 'Z')) {
                        this->player_name += (static_cast<char>(event.text.unicode + 32)) ;
                    } else
                        // otherwise, simply add what was typed
                        this->player_name += (static_cast<char>(event.text.unicode)) ;
                } else if (event.text.unicode == 8 && this->player_name.length() > 0) {
                    this->player_name.pop_back() ;
                }

            } else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                minesweeper.game_state = game ;
                render_window.close() ;
            }
        }
        render_window.clear(Color::Blue);
        // draw the text
        render_window.draw(welcome_title);
        render_window.draw(prompt);
        render_window.draw(name);
        render_window.display();
    }
}