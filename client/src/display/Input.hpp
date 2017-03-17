#ifndef FREEPOISSON_CLIENT_INPUT_HPP
#define FREEPOISSON_CLIENT_INPUT_HPP

#include <iostream>
#include <list>

#include <SFML/Graphics.hpp>

class Input {
private:
    static constexpr unsigned _historySize = 128;
    std::list<std::string> _history;
    std::list<std::string>::iterator _current;
    bool _last = true;

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

    void validateString();
    void goUp(); //TODO: un meilleur nom pour cette fonction qui ramnène le message un pas en arrière dans le temps
    void goDown();

    void disable();
    void enable();

    std::string getString();
    long getLength();
};


#endif //FREEPOISSON_CLIENT_INPUT_HPP
