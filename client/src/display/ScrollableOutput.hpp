#ifndef FREEPOISSON_CLIENT_SCROLLABLEOUTPUT_HPP
#define FREEPOISSON_CLIENT_SCROLLABLEOUTPUT_HPP

#include <iostream>

#include <SFML/Graphics.hpp>


class ScrollableOutput {
private:
    static unsigned constexpr lineLimit = 5;

    sf::RenderWindow &_window;
    std::string _text;
    unsigned _linesNumber;
    unsigned _cursor;
    sf::Font _font; //need to copy the font in order to prevent memory issues
    sf::Text _printedText;
    sf::RectangleShape _background;
    sf::RectangleShape _scrollBar;

    void setPosition(int pos);

public:
    ScrollableOutput(sf::RenderWindow &window, sf::Font font);

    void update();

    void draw();

    void setString(std::string);

    void scroll(int lines);
};


#endif //FREEPOISSON_CLIENT_SCROLLABLEOUTPUT_HPP
