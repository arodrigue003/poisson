#include "ScrollableOutput.hpp"

#include <algorithm>
#include <iostream>

#include <SFML/Graphics.hpp>

void ScrollableOutput::setPosition(int pos) {
    if (pos<0)
        pos=0;
    if (pos > _linesNumber - lineLimit)
        if (_linesNumber >= lineLimit)
            pos = _linesNumber - lineLimit;
        else
            pos = 0;
    _cursor = (unsigned) pos;

    unsigned lineOccurence = 0;
    unsigned begin = 0;
    bool beginSet = false;
    unsigned length = 0;
    for (unsigned i=0; i<_text.length(); i++) {
        if (lineOccurence == _cursor && !beginSet) {
            begin = i;
            beginSet = true;
        }

        if (_text[i] == '\n')
            lineOccurence++;

        if (lineOccurence == _cursor + lineLimit)
            break;

        if (beginSet)
            length++;
    }

    _printedText.setString(_text.substr(begin, length));

}

ScrollableOutput::ScrollableOutput(sf::RenderWindow &window, sf::Font font) :
        _window(window), _text(""), _cursor(0), _font(font), _linesNumber(0) {
    _printedText.setFont(_font);
    _printedText.setString("");
    _printedText.setCharacterSize(16);
    _printedText.setFillColor(sf::Color::White);
    _background.setFillColor(sf::Color(0, 0, 0, 180));
    _scrollBar.setFillColor(sf::Color(155,155,155,180));
}

void ScrollableOutput::update() {
    unsigned width = _window.getSize().x;
    unsigned height = _window.getSize().y;

    _background.setSize(sf::Vector2f(width / 4 * 3 - 18, 20 * lineLimit));
    _background.setPosition(18, height - 20 - 15 - 5 - _background.getSize().y);
    _printedText.setPosition(18+7+2+4, height - 20 -16 - 5 - _background.getSize().y);
    _scrollBar.setSize(sf::Vector2f(7,20 * lineLimit - 4));
    _scrollBar.setPosition(20, height-20-15-5-_background.getSize().y+2);
}

void ScrollableOutput::draw() {
    _window.draw(_background);
    _window.draw(_printedText);
    if (_linesNumber>lineLimit)
        _window.draw(_scrollBar);
}

void ScrollableOutput::setString(std::string text) {
    _text = text;
    _linesNumber = std::count(_text.begin(), _text.end(), '\n') + 1;
    setPosition(0);
}

void ScrollableOutput::scroll(int lines) {
    setPosition(_cursor+lines);
}
