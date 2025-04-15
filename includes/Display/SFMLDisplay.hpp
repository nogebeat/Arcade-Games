/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** SFMLDisplay
*/

#ifndef SFMLDISPLAY_HPP_
#define SFMLDISPLAY_HPP_
#include "../includes/my.hpp"
#include <SFML/Graphics.hpp>
#include "../includes/Interfaces/IDisplayModule.hpp"
namespace arcade {

class SFMLDisplay : public IDisplayModule {
    public:
        SFMLDisplay();
        virtual ~SFMLDisplay();
        void init() override;
        void stop() override;
        void clear() override;
        void render() override;
        void present() override;

        void drawRect(int x, int y, int width, int height, int r, int g, int b, int a) override;
        void drawText(const std::string &text, int x, int y, int r, int g, int b, int a) override;
        void drawCircle(int x, int y, int radius, int r, int g, int b, int a) override;
        
        bool isKeyPressed(const std::string &key) override;
        sf::RenderWindow* getWindow() {
        return _window;
    }
    std::string getName() const override;
    void handleInput() override;
    bool shouldQuit() const override;
    // void drawCircle(int x, int y, int radius, int r, int g, int b, int a);

    std::string getTextInput(const std::string& prompt, const std::string& initialText = "") override;

    protected:
    private:
    sf::RenderWindow* _window;
    bool _quit;
    sf::Font _font;    
    std::unordered_map<std::string, sf::Keyboard::Key> _keyMap;
};
}

#endif /* !SFMLDISPLAY_HPP_ */
