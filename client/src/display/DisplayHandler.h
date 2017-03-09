#ifndef FREEPOISSON_CLIENT_DISPLAYHANDLER_H
#define FREEPOISSON_CLIENT_DISPLAYHANDLER_H

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

class ModelHandler;

class DisplayHandler {
// TODO - Complete this class basis

private:
    ModelHandler* _model;
    bool _commandMode;
    std::string _input;
    static constexpr const char *_help = "q   : quit\n"
            "h : display this help\n"
            "arrow key or mouse wheel : scroll in the output show\n"
            "ESC : enter and exit the command mode\n"
            "Numpad 1-2-3-4-6-7-8-9 : set window position\n"
            "test\n"
            "test";

public:
    DisplayHandler();

    void init(ModelHandler& model);
    void launch();

    void updateBackgorund(const sf::Texture &backgroundTexture, sf::Sprite &backgroundSprite, unsigned int width,
                          unsigned int height, const sf::RenderWindow &window, const sf::VideoMode &desktop) const;
};


#endif //FREEPOISSON_CLIENT_DISPLAYHANDLER_H
