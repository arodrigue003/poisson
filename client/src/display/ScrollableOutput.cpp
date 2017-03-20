#include "ScrollableOutput.hpp"

#include <algorithm>
#include <iostream>

#include <SFML/Graphics.hpp>

void ScrollableOutput::SetPrintedText(int pos, unsigned linesNumber, const std::string &text) {
    if (pos < 0)
        pos = 0;
    if (pos > linesNumber - lineLimit)
        if (linesNumber >= lineLimit)
            pos = linesNumber - lineLimit;
        else
            pos = 0;
    _cursor = (unsigned) pos;

    unsigned lineOccurrence = 0;
    unsigned begin = 0;
    bool beginSet = false;
    unsigned length = 0;
    for (unsigned i = 0; i < text.length(); i++) {
        if (lineOccurrence == _cursor && !beginSet) {
            begin = i;
            beginSet = true;
        }

        if (text[i] == '\n')
            lineOccurrence++;

        if (lineOccurrence == _cursor + lineLimit)
            break;

        if (beginSet)
            length++;
    }

    _printedText.setString(text.substr(begin, length));
}

void ScrollableOutput::setPosition(int pos) {
    if (_displayHelp)
        SetPrintedText(pos, _helpLinesNumber, _help);
    else
        SetPrintedText(pos, _stringLinesNumber, _text);
}

ScrollableOutput::ScrollableOutput(sf::RenderWindow &window, sf::Font font) :
        _window(window), _text(""), _cursor(0), _font(font), _stringLinesNumber(0) {
    _printedText.setFont(_font);
    _printedText.setString("");
    _printedText.setCharacterSize(16);
    _printedText.setFillColor(sf::Color::White);
    _background.setFillColor(sf::Color(0, 0, 0, 180));
    _scrollBar.setFillColor(sf::Color(155, 155, 155, 180));
    _helpLinesNumber = (unsigned) std::count(_help.begin(), _help.end(), '\n') + 1;
}

void ScrollableOutput::update() {
    unsigned width = _window.getSize().x;
    unsigned height = _window.getSize().y;

    _background.setSize(sf::Vector2f(width / 4 * 3 - 18, 20 * lineLimit));
    _background.setPosition(18, height - 20 - 15 - 5 - _background.getSize().y);
    _printedText.setPosition(18 + 7 + 2 + 4, height - 20 - 16 - 5 - _background.getSize().y);
    _scrollBar.setSize(sf::Vector2f(7, 20 * lineLimit - 4));
    _scrollBar.setPosition(20, height - 20 - 15 - 5 - _background.getSize().y + 2);
}

void ScrollableOutput::draw() {
    _window.draw(_background);
    _window.draw(_printedText);

    if (!_displayHelp && _stringLinesNumber > lineLimit) {
        int scrollBarHeight = 20 * lineLimit - 4;
        scrollBarHeight = (int) (scrollBarHeight * lineLimit) / _stringLinesNumber;
        _scrollBar.setSize(sf::Vector2f(7, scrollBarHeight));
        int scrollBarMaxPos = 20 * lineLimit - 4 - scrollBarHeight;
        scrollBarMaxPos = (int) (scrollBarMaxPos * _cursor) / (_stringLinesNumber - lineLimit);
        _scrollBar.setPosition(20, _window.getSize().y - 20 - 15 - 5 - _background.getSize().y + 2 + scrollBarMaxPos);

        _window.draw(_scrollBar);
    }
    else if (_displayHelp && _helpLinesNumber > lineLimit) {
        int scrollBarHeight = 20 * lineLimit - 4;
        scrollBarHeight = (int) (scrollBarHeight * lineLimit) / _helpLinesNumber;
        _scrollBar.setSize(sf::Vector2f(7, scrollBarHeight));
        int scrollBarMaxPos = 20 * lineLimit - 4 - scrollBarHeight;
        scrollBarMaxPos = (int) (scrollBarMaxPos * _cursor) / (_helpLinesNumber - lineLimit);
        _scrollBar.setPosition(20, _window.getSize().y - 20 - 15 - 5 - _background.getSize().y + 2 + scrollBarMaxPos);

        _window.draw(_scrollBar);
    }
}

void ScrollableOutput::set(std::string text) {
    _text = text;
    if (_text != "")
        _stringLinesNumber = (unsigned) std::count(_text.begin(), _text.end(), '\n') + 1;
    else
        _stringLinesNumber = 0;
    setPosition(0);
}


std::string ScrollableOutput::get() const {
    return _text;
}

void ScrollableOutput::append(std::string newText) {
    if (newText != "") {
        unsigned oldLines = _stringLinesNumber;
        if (_text != "")
            _text.append("\n");
        _text.append(newText);
        _stringLinesNumber = (unsigned) std::count(_text.begin(), _text.end(), '\n') + 1;

        if (_stringLinesNumber - _cursor > lineLimit) {
            // if the line number of the newText is greater than the height of the output
            setPosition(oldLines);
        }
        else
            if (oldLines == 0)
                setPosition(0);
            else
                setPosition(_cursor);
    }
}

void ScrollableOutput::scroll(int lines) {
    setPosition(_cursor + lines);
}

void ScrollableOutput::toggleHelp(bool mode) {
    _displayHelp = mode;
    if (mode)
        setPosition(0);
}