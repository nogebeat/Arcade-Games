/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** SFMLDisplay
*/

#include "../includes/Display/SFMLDisplay.hpp"

using namespace arcade;

namespace arcade {

    SFMLDisplay::SFMLDisplay() : _window(nullptr), _quit(false) {
        _keyMap["UP"]     = sf::Keyboard::Up;
        _keyMap["DOWN"]   = sf::Keyboard::Down;
        _keyMap["LEFT"]   = sf::Keyboard::Left;
        _keyMap["RIGHT"]  = sf::Keyboard::Right;
        _keyMap["ESCAPE"] = sf::Keyboard::Escape;
        _keyMap["RETURN"] = sf::Keyboard::Enter;
        _keyMap["SPACE"]  = sf::Keyboard::Space;
        _keyMap["R"]      = sf::Keyboard::R;
        _keyMap["N"]      = sf::Keyboard::N;
        _keyMap["Q"]      = sf::Keyboard::Q;
        _keyMap["E"]      = sf::Keyboard::E;
        _keyMap["M"]      = sf::Keyboard::M;
        _keyMap["F5"] = sf::Keyboard::F5;
        _keyMap["F6"] = sf::Keyboard::F6;
        _keyMap["P"] = sf::Keyboard::P;
        _keyMap["Y"] = sf::Keyboard::Y;

    }

    SFMLDisplay::~SFMLDisplay() {
        stop();
    }

    void SFMLDisplay::init() {
        _window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arcade SFML");
        if (!_window) {
            std::cerr << "Failed to create SFML window!" << std::endl;
            return;
        }
        _window->setFramerateLimit(60);
        if (!_font.loadFromFile("/tmp/arcade/assets/fonts/duckhunt.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
        }
        _quit = false;
        std::cout << "SFML initialized successfully" << std::endl;
    }
    void SFMLDisplay::stop() {
        if (_window) {
            _window->close();
            delete _window;
            _window = nullptr;
        }
    }
    void SFMLDisplay::clear() {
        if (_window)
            _window->clear(sf::Color(0, 0, 0, 255));
    }

    void SFMLDisplay::present() {
        if (_window)
            _window->display();
    }
    
    void SFMLDisplay::render() {
        clear();
        present();
    }
    
    void SFMLDisplay::drawText(const std::string &text, int x, int y, int r, int g, int b, int a) {
        if (!_font.getInfo().family.empty()) {
            sf::Text sfText;
            sfText.setFont(_font);
            sfText.setString(text);
            sfText.setCharacterSize(24);
            sfText.setFillColor(sf::Color(r, g, b, a));
            sfText.setPosition(static_cast<float>(x), static_cast<float>(y));
            
            if (_window)
                _window->draw(sfText);
        } else {
            std::cerr << "Font not loaded, cannot render text." << std::endl;
        }
    }

    void SFMLDisplay::drawRect(int x, int y, int width, int height, int r, int g, int b, int a) {
        sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
        rectangle.setPosition(static_cast<float>(x), static_cast<float>(y));
        rectangle.setFillColor(sf::Color(r, g, b, a));
        
        if (_window)
            _window->draw(rectangle);
    }
    
    void SFMLDisplay::drawCircle(int x, int y, int radius, int r, int g, int b, int a) {
        sf::CircleShape circle(static_cast<float>(radius));
        circle.setPosition(static_cast<float>(x - radius), static_cast<float>(y - radius));
        circle.setFillColor(sf::Color(r, g, b, a));
        
        if (_window)
            _window->draw(circle);
    }

    void SFMLDisplay::handleInput() {
        if (!_window) return;
        
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _quit = true;
            }
        }
    }
    
    bool SFMLDisplay::isKeyPressed(const std::string &key) {
        if (_keyMap.find(key) != _keyMap.end()) {
            return sf::Keyboard::isKeyPressed(_keyMap[key]);
        }
        return false;
    }
    
    bool SFMLDisplay::shouldQuit() const {
        return _quit;
    }
    
    std::string SFMLDisplay::getName() const {
        return "SFML";
    }

    std::string SFMLDisplay::getTextInput(const std::string& prompt, const std::string& initialText)
    {
        std::string inputText = initialText;
        bool inputActive = true;
        bool escapePressed = false;

        if (!_window)
            return inputText;
            
        while (inputActive) {
            sf::Event event;
            while (_window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    inputActive = false;
                    _quit = true;
                } else if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\n')
                        inputText += static_cast<char>(event.text.unicode);
                } else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::BackSpace && !inputText.empty()) {
                        inputText.pop_back();
                    } else if (event.key.code == sf::Keyboard::Enter) {
                        inputActive = false;
                    } else if (event.key.code == sf::Keyboard::Escape) {
                        inputActive = false;
                        escapePressed = true;
                    }
                }
            }
            
            clear();
            drawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 30, 30, 50, 255);
            drawText("ARCADE MENU", WINDOW_WIDTH / 2 - 100, 30, 255, 255, 0, 255);
            drawRect(WINDOW_WIDTH / 2 - 190, 70, 400, 40, 60, 60, 80, 255);
            drawText(prompt + inputText, WINDOW_WIDTH / 2 - 180, 85, 255, 255, 255, 255);
            present();
            
            sf::sleep(sf::milliseconds(16));
            if (isKeyPressed("F6") || isKeyPressed("F5")) {
                inputActive = false;
                escapePressed = true;
            }
        }
        if (!escapePressed) {
            bool keyReleased = false;
            while (!keyReleased) {
                sf::Event event;
                while (_window->pollEvent(event)) {
                    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
                        keyReleased = true;
                    }
                }
                sf::sleep(sf::milliseconds(10));
            }
        }
        
        return escapePressed ? initialText : inputText;
    }
}

