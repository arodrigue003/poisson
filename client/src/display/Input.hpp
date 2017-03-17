#ifndef FREEPOISSON_CLIENT_INPUT_HPP
#define FREEPOISSON_CLIENT_INPUT_HPP

#include <iostream>

#include <SFML/Graphics.hpp>

class Input {
private:
    std::string _input;

    sf::RenderWindow &_window;
    sf::Font _font; //need to copy the font in order to prevent memory issues
    sf::Text _inputText;
    sf::RectangleShape _inputBackground;

    bool _disabled;

public:
    Input(sf::RenderWindow &window, sf::Font font);

    void update();
    void draw();

    void addChar(char c);
    void removeChar();
    void clear();

    void disable();
    void enable();

    std::string getString();
    long getLength();
};


#endif //FREEPOISSON_CLIENT_INPUT_HPP
