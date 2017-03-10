#include <iostream>

#include <SFML/Graphics.hpp>

#include "DisplayHandler.h"
#include <model/ModelHandler.h>
#include "ScrollableOutput.hpp"



DisplayHandler::DisplayHandler() :
    _commandMode(false)
{

}

void DisplayHandler::init(ModelHandler &model) {
    _model = &model;
}

void DisplayHandler::launch() {
    //Font importation
    sf::Font font;
    if (!font.loadFromFile("fonts/SourceCodePro-Regular.ttf")) {
        std::cerr << "Could not load the font!" << std::endl << "Exiting..." << std::endl;
        return;
    }

    //Input text
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setString("");
    inputText.setCharacterSize(16);
    inputText.setFillColor(sf::Color::White);

    //input background
    sf::RectangleShape inputRect(sf::Vector2f(50, 18));
    inputRect.setFillColor(sf::Color(0, 0, 0, 180));

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
//    backgroundSprite.setTextureRect(sf::IntRect(20,20,60,60));

    //window creation
    unsigned width = 1000;
    unsigned height = 560;
    sf::RenderWindow window(sf::VideoMode(width, height), "Vue : ");
    window.setVerticalSyncEnabled(true);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    ScrollableOutput output(window, font);

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
                        if (character >= 32 && character != 127) {//don't add special chars to the string
                            _input.push_back(character);
                            //update the visual text
                            inputText.setString("> " + _input);
                        }
                    }
                    break;

                case sf::Event::KeyPressed:

                    // find if we need to execute command input functionality or not
                    if (_commandMode) {

                        switch (event.key.code) {


                            case sf::Keyboard::Return:
                                _model->registerCommand(_input);

                                _input.clear();
                                //update the visual text
                                inputText.setString("> " + _input);
                                break;

                            case sf::Keyboard::BackSpace:
                                if (_input.size() > 0)
                                    //erase last character of the command if command is not empty
                                    _input.pop_back();
                                break;

                            case sf::Keyboard::Down:
                                output.scroll(1);
                                break;

                            case sf::Keyboard::Up:
                                output.scroll(-1);
                                break;

                        }

                        //update the visual text
                        inputText.setString("> " + _input);

                    } else {


                        switch (event.key.code) {

                            //portioning window part (4 split)
                            case sf::Keyboard::Numpad7: {
                                sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
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
                                output.setString(_help);
                                _commandMode = true;
                                inputText.setString("> ");
                                _input = "";
                                break;

                            default:
                                break;
                        }

                    }

                    if (event.key.code == sf::Keyboard::Escape) {
                        _commandMode = !_commandMode;
                        output.setString("");
                        //add the > chevron to show we are in input mode or remove it
                        if (_commandMode)
                            inputText.setString("> ");
                        else
                            inputText.setString("");
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
                    inputText.setPosition(20, height - 20 - 16);
                    inputRect.setPosition(18, height - 20 - 15);
                    inputRect.setSize(sf::Vector2f(width - 36, 18));
                    fps.setPosition(width - 70, 5);


                    output.update();

                    std::cout << width<< ":" << height << std::endl;
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
        updateBackgorund(backgroundTexture, backgroundSprite, width, height, window, desktop);

        //drawing part
        window.clear();
        window.draw(backgroundSprite);
        window.draw(fps);
        if (_commandMode) {
            window.draw(inputRect);
            window.draw(inputText);
            output.draw();
        }
        window.display();

    }

}

void DisplayHandler::updateBackgorund(const sf::Texture &backgroundTexture, sf::Sprite &backgroundSprite, unsigned int width,
                                 unsigned int height, const sf::RenderWindow &window, const sf::VideoMode &desktop) const {

    int rectWidth = width * backgroundTexture.getSize().x / desktop.width;
    int rectHeight = height * backgroundTexture.getSize().y / desktop.height;
    int rectBeginX = window.getPosition().x * backgroundTexture.getSize().x / desktop.width;
    int rectBeginY = window.getPosition().y * backgroundTexture.getSize().y / desktop.height;
    backgroundSprite.setTextureRect(sf::IntRect(rectBeginX, rectBeginY, rectBeginX + rectWidth, rectBeginY + rectHeight));
    backgroundSprite.setScale(width / (float) rectWidth, height / (float) rectHeight);

    /*std::cout << "Window position : " << window.getPosition().x << ":" << window.getPosition().y << std::endl;
    std::cout << "Windo size      : " << width << ":" << height << std::endl;
    std::cout << "Rectange sprite : (" << rectBeginX << ":" << rectBeginY << "),(" << rectBeginX + rectWidth << ":" << rectBeginY + rectHeight << ")" << std::endl;*/
}