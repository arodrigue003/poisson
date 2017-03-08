#include <iostream>

#include <SFML/Graphics.hpp>

#include "DisplayHandler.h"


DisplayHandler::DisplayHandler(ModelHandler *model) :
        _model(model), _commandMode(false), _input() {

}

void DisplayHandler::launch() {
    //Font importation
    sf::Font font;

    if (!font.loadFromFile("fonts/SourceCodePro-Black.ttf")) {
        std::cerr << "Could not load the font!" << std::endl << "Exiting..." << std::endl;
        //TODO : call exit to the model
        return;
    }

    //Input text
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setString("");
    inputText.setCharacterSize(16);
    inputText.setFillColor(sf::Color::White);

    //window creation
    int width = 800;
    int height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Vue : ");
    window.setVerticalSyncEnabled(true);

    //main loop
    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {

            switch (event.type) {

                case sf::Event::Closed:
                    window.close();
                    //TODO : call exit to the model
                    break;

                    //gestion of the entered text in order to send it after to the server
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

                    // find if we need to execute command input functionnality or not
                    if (_commandMode) {
                        if (event.key.code == sf::Keyboard::Return) {
                            //TODO : send the command to the server
                            std::cout << _input << std::endl;
                            _input.clear();
                            //update the visual text
                            inputText.setString("> " + _input);
                        } else if (event.key.code == sf::Keyboard::BackSpace && _input.size() > 0)
                            //erase last character of the command if command is not empty
                            _input.pop_back();
                        //update the visual text
                        inputText.setString("> " + _input);

                    } else {
                        if (event.key.code == sf::Keyboard::Q) {
                            window.close();
                            //TODO : call exit to the model
                        }

                    }

                    if (event.key.code == sf::Keyboard::Escape) {
                        _commandMode = !_commandMode;
                        //add the > chevron to show we are in input mode or remove it
                        if (_commandMode)
                            inputText.setString("> ");
                        else
                            inputText.setString("");
                    }
                    break;

                    //resize event
                case sf::Event::Resized: {
                    int newWidth = event.size.width;
                    int newHeight = event.size.height;
                    /*if (height != newHeight || width != newWidth) {
                        width = newWidth;
                        height = newHeight;
                        window.create(sf::VideoMode(width, height), "Vue : ");
                    }*/
                    std::cout << "new width: " << event.size.width << std::endl;
                    std::cout << "new height: " << event.size.height << std::endl;
                }
                    break;

                default:
                    break;
            }

        }

        window.clear();
        window.draw(inputText);
        window.display();

    }

}