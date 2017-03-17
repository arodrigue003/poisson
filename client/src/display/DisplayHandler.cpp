#include <iostream>

#include <SFML/Graphics.hpp>

#include "DisplayHandler.h"
#include <model/ModelHandler.h>
#include "ScrollableOutput.hpp"
#include "Input.hpp"



DisplayHandler::DisplayHandler() :
    _commandMode(false)
{

}

void DisplayHandler::init(ModelHandler &model) {
    _model = &model;
}

void DisplayHandler::launch() {
    bool drawFPS = false;
    bool waitingData = false;

    //Font importation
    sf::Font font;
    if (!font.loadFromFile("fonts/SourceCodePro-Regular.ttf")) {
        std::cerr << "Could not load the font!" << std::endl << "Exiting..." << std::endl;
        return;
    }

    //FPS
    sf::Text fps;
    fps.setFont(font);
    fps.setString("");
    fps.setCharacterSize(16);
    fps.setFillColor(sf::Color::White);

    //backgroundTexture image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("textures/background.jpg")) {
        std::cerr << "Could not load the texture!" << std::endl << "Exiting..." << std::endl;
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    //window creation
    unsigned width = 1000;
    unsigned height = 560;
    sf::RenderWindow window(sf::VideoMode(width, height), "Vue : ");
    window.setVerticalSyncEnabled(true);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    ScrollableOutput output(window, font);
    Input input(window, font);

    //main loop
    sf::Clock clock;
    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {

            switch (event.type) {

                case sf::Event::Closed:
                    window.close();
                    break;

                    //management of the entered text in order to send it after to the server
                case sf::Event::TextEntered:
                    if (_commandMode) {
                        char character = static_cast<char>(event.text.unicode);
                        input.addChar(character);
                    }
                    break;

                case sf::Event::KeyPressed:

                    // find if we need to execute command input functionality or not
                    if (_commandMode) {

                        switch (event.key.code) {


                            case sf::Keyboard::Return:
                                if (input.getLength() > 0) {
                                    _model->registerCommand(input.getString());

                                    input.validateString();
                                    input.clear();
                                    output.toggleHelp(false);
                                    waitingData = true;
                                }
                                break;

                            case sf::Keyboard::BackSpace:
                                input.removeChar();
                                break;

                            case sf::Keyboard::Down:
                                input.goDown();
                                break;

                            case sf::Keyboard::Up:
                                input.goUp();
                                break;

                            default:
                                break;

                        }

                    } else {


                        switch (event.key.code) {

                            //portioning window part (4 split)
                            case sf::Keyboard::Numpad7: {
                                window.setSize(sf::Vector2u(desktop.width / 2 - 12, desktop.height / 2 - 50));
                                window.setPosition(sf::Vector2i(12, 50));
                            }
                                break;

                            case sf::Keyboard::Numpad9: {
                                window.setSize(sf::Vector2u(desktop.width / 2 - 12, desktop.height / 2 - 50));
                                window.setPosition(sf::Vector2i(desktop.width / 2, 50));
                            }
                                break;

                            case sf::Keyboard::Numpad1: {
                                window.setSize(sf::Vector2u(desktop.width / 2 - 12, desktop.height / 2 - 50));
                                window.setPosition(sf::Vector2i(12, desktop.height / 2));
                            }
                                break;

                            case sf::Keyboard::Numpad3: {
                                window.setSize(sf::Vector2u(desktop.width / 2 - 12, desktop.height / 2 - 50));
                                window.setPosition(sf::Vector2i(desktop.width / 2, desktop.height / 2));
                            }
                                break;

                                //portioning window part (2 vertical)
                            case sf::Keyboard::Numpad8: {
                                window.setSize(sf::Vector2u(desktop.width - 24, desktop.height / 2 - 50));
                                window.setPosition(sf::Vector2i(12, 50));
                            }
                                break;

                            case sf::Keyboard::Numpad2: {
                                window.setSize(sf::Vector2u(desktop.width - 24, desktop.height / 2 - 50));
                                window.setPosition(sf::Vector2i(12, desktop.height / 2));
                            }
                                break;

                                //portioning window part (2 horizontal)
                            case sf::Keyboard::Numpad4: {
                                window.setSize(sf::Vector2u(desktop.width / 2 - 12, desktop.height - 100));
                                window.setPosition(sf::Vector2i(12, 50));
                            }
                                break;

                            case sf::Keyboard::Numpad6: {
                                window.setSize(sf::Vector2u(desktop.width / 2 - 12, desktop.height - 100));
                                window.setPosition(sf::Vector2i(desktop.width / 2, 50));
                            }
                                break;


                            case sf::Keyboard::Q:
                                window.close();
                                break;

                            case sf::Keyboard::H:
                                output.toggleHelp(true);
                                _commandMode = true;
                                input.clear();
                                input.disable();
                                break;

                            case sf::Keyboard::F:
                                drawFPS = !drawFPS;
                                break;

                            default:
                                break;
                        }

                    }

                    if (event.key.code == sf::Keyboard::Escape) {
                        _commandMode = !_commandMode;
                        output.setString("");
                        input.clear();
                        //add the > chevron to show we are in input mode or remove it
                        if (!_commandMode) {
                            output.toggleHelp(false);
                            input.enable();
                        }
                    }
                    break;

                    //mouse scroll event
                case sf::Event::MouseWheelScrolled:
                    if (_commandMode)
                        output.scroll(- (int) event.mouseWheelScroll.delta);
                    break;

                    //resize event
                case sf::Event::Resized: {
                    // update the view to correspond to the new window size
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                    width = window.getSize().x;
                    height = window.getSize().y;
                    fps.setPosition(width - 70, 5);
                    input.update();
                    output.update();

                }
                    break;

                default:
                    break;
            }

        }

        //updating part
        sf::Time frameTime = clock.restart();
        int frameMillis = frameTime.asMilliseconds();
        fps.setString(((frameMillis == 0) ? "0" : std::to_string(1000 / frameMillis)) + " FPS");

        // TODO adapt this code portion
        /*std::string data;
        if (waitingData && _model->getRespond(data)) {
            output.setString(data);
        }*/

        //update background view box
        int rectWidth = width * backgroundTexture.getSize().x / desktop.width;
        int rectHeight = height * backgroundTexture.getSize().y / desktop.height;
        int rectBeginX = window.getPosition().x * backgroundTexture.getSize().x / desktop.width;
        int rectBeginY = window.getPosition().y * backgroundTexture.getSize().y / desktop.height;
        backgroundSprite.setTextureRect(
                sf::IntRect(rectBeginX, rectBeginY, rectBeginX + rectWidth, rectBeginY + rectHeight));
        backgroundSprite.setScale(width / (float) rectWidth, height / (float) rectHeight);

        //drawing part
        window.clear();
        window.draw(backgroundSprite);
        if (drawFPS)
            window.draw(fps);
        if (_commandMode) {
            input.draw();
            output.draw();
        }
        window.display();

    }

}

