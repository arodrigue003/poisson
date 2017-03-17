#include "Input.hpp"

Input::Input(sf::RenderWindow &window, sf::Font font) :
        _history(), _input(), _window(window), _font(font), _disabled(false) {

    //_history
    _history.resize(_historySize);
    _current = _history.begin();

    //Input text
    _inputText.setFont(_font);
    _inputText.setString("");
    _inputText.setCharacterSize(16);
    _inputText.setFillColor(sf::Color::White);

    //input background
    _inputBackground.setFillColor(sf::Color(0, 0, 0, 180));
}

void Input::update() {
    unsigned width = _window.getSize().x;
    unsigned height = _window.getSize().y;

    _inputText.setPosition(20, height - 20 - 16);
    _inputBackground.setPosition(18, height - 20 - 15);
    _inputBackground.setSize(sf::Vector2f(width - 36, 18));
}

void Input::draw() {
    if (!_disabled)
        _inputText.setString("> " + _input);

    _window.draw(_inputBackground);
    _window.draw(_inputText);
}

void Input::addChar(char c) {
    if (!_disabled && c >= 32 && c != 127) {
        //don't add special chars to the string

        _input.push_back(c);

        //update the visual text
        _inputText.setString("> " + _input);
    }
}

void Input::removeChar() {
    if (!_disabled && _input.size() > 0)
        //erase last character of the command if command is not empty
        _input.pop_back();
}


void Input::clear() {
    _input.clear();
    _inputText.setString(">");
}

void Input::validateString() {
    _history.push_front(_input);
    _history.resize(_historySize);
    _current = _history.begin();
    _last = true;
}

void Input::goUp() {
    if (_last) {
        _input = *_current;
        _inputText.setString("> " + _input);
        _last = false;
    }
    else if (_current != _history.end()) {
        _current++;
        _input = *_current;
        _inputText.setString("> " + _input);
    }
}

void Input::goDown() {
    if (_current != _history.begin()) {
        _current--;
        _input = *_current;
        _inputText.setString("> " + _input);
    }
    else {
        _input = "";
        _inputText.setString(">");
        _last = true;
    }
}

void Input::disable() {
    _disabled = true;
    _inputText.setString("Disabled in help mode");
}

void Input::enable() {
    _disabled = false;
}

std::string Input::getString() {
    return _input;
}

long Input::getLength() {
    return _input.length();
}
