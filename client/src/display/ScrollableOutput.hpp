#ifndef FREEPOISSON_CLIENT_SCROLLABLEOUTPUT_HPP
#define FREEPOISSON_CLIENT_SCROLLABLEOUTPUT_HPP

#include <iostream>

#include <SFML/Graphics.hpp>


class ScrollableOutput {
private:
    static unsigned constexpr lineLimit = 7;
    const std::string _help = "ESC : toggle modes (current : input)\n"
            "----INPUT MODE----\n"
            "arrow key : scroll in the inout history\n"
            "mouse wheel : scroll in the output show\n"
            "RET : validate the input\n"
            "BS  : remove the last character\n"
            "---COMMAND MODE---\n"
            "h   : display this help\n"
            "q   : quit\n"
            "f   : toggle FPS\n"
            "Numpad 1-2-3-4-6-7-8-9 : set window position\n";


    sf::RenderWindow &_window;
    std::string _text;
    unsigned _helpLinesNumber;
    unsigned _stringLinesNumber;
    unsigned _cursor;
    sf::Font _font; //need to copy the font in order to prevent memory issues
    sf::Text _printedText;
    sf::RectangleShape _background;
    sf::RectangleShape _scrollBar;

    bool _displayHelp = false;

    void setPosition(int pos);

public:
    ScrollableOutput(sf::RenderWindow &window, sf::Font font);

    void update();
    void draw();

    void setString(std::string);
    std::string getString() const;
    void append(std::string newText);

    void scroll(int lines);
    void toggleHelp(bool mode);
    void SetPrintedText(int pos, unsigned linesNumber, const std::string& text);
};


#endif //FREEPOISSON_CLIENT_SCROLLABLEOUTPUT_HPP
