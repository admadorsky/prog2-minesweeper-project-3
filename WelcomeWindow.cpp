#include "WelcomeWindow.h"
#include <iostream>
using namespace std ;

void WelcomeWindow::display(int width, int height, sf::Font font) {
    RenderWindow render_window(VideoMode(width, height), "Minesweeper", Style::Close) ;
    while (render_window.isOpen()) {
        render_window.clear(Color::Blue);
        // initialize text objects
        Text welcome_title;
        Text prompt;
        Text name;
        // set strings
        welcome_title.setString("WELCOME TO MINESWEEPER!");
        prompt.setString("Enter your name:");
        name.setString(this->player_name + "|");
        // set fonts to main font
        welcome_title.setFont(font);
        prompt.setFont(font);
        name.setFont(font);
        // set colors
        welcome_title.setFillColor(Color::White);
        prompt.setFillColor(Color::White);
        name.setFillColor(Color::Yellow);
        // set styles
        welcome_title.setStyle(Text::Bold | Text::Underlined);
        prompt.setStyle(Text::Bold);
        name.setStyle(Text::Bold);
        // set sizes
        welcome_title.setCharacterSize(24);
        prompt.setCharacterSize(20);
        name.setCharacterSize(18);
        // create bounding rectangles
        FloatRect welcome_title_boundingbox = welcome_title.getGlobalBounds();
        FloatRect prompt_boundingbox = prompt.getGlobalBounds();
        FloatRect name_boundingbox = name.getGlobalBounds();
        // set origins using center coordinates - (1/2 width or height) -> to get top left corner
        welcome_title.setPosition((width / 2.0f) - (welcome_title_boundingbox.width / 2.0f),
                                  (height / 2.0f) - (welcome_title_boundingbox.height / 2.0f) - 150);
        prompt.setPosition((width / 2.0f) - (prompt_boundingbox.width / 2.0f),
                           (height / 2.0f) - (prompt_boundingbox.height / 2.0f) - 75);
        name.setPosition((width / 2.0f) - (name_boundingbox.width / 2.0f),
                         (height / 2.0f) - (name_boundingbox.height / 2.0f) - 45);

        // draw the text
        render_window.draw(welcome_title);
        render_window.draw(prompt);
        render_window.draw(name);

        Event event;
        while (render_window.pollEvent(event)) {
            // if the "x" is pressed, close the window
            if (event.type == Event::Closed) render_window.close();
                // if the user starts typing, execute the following
            else if (event.type == Event::TextEntered) {
                // make sure a letter was entered
                if (event.text.unicode <= 122 && event.text.unicode >= 65 && this->player_name.length() <= 11) {
                    // if the first letter input is lowercase, capitalize it
                    if (this->player_name.length() == 0 && event.text.unicode >= 97 && event.text.unicode <= 122) {
                        this->player_name += (static_cast<char>(event.text.unicode - 32));
                    } // if the following letters input are uppercase, un-capitalize them
                    else if (this->player_name.length() > 0 && event.text.unicode >= 65 && event.text.unicode <= 90) {
                        this->player_name += (static_cast<char>(event.text.unicode + 32));
                    } else
                        // otherwise, simply add what was typed
                        this->player_name += (static_cast<char>(event.text.unicode));
                } else if (event.text.unicode == 8 && this->player_name.length() > 0) {
                    this->player_name.pop_back();
                }
            } else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                render_window.close() ;
                this->go_to_game_screen = true ;
            }
        }
        render_window.display();
    }
}