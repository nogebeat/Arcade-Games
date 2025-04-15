    /*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** SDL2Display
*/

// SDL2Display.hpp

#ifndef SDL2DISPLAY_HPP_
#define SDL2DISPLAY_HPP_
#include "../includes/Interfaces/IDisplayModule.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>

namespace arcade {

    class SDL2Display : public IDisplayModule {
    public:
        SDL2Display();
        ~SDL2Display() override;
    
        void init() override;
        void stop() override;
        void clear() override;
        void render() override;
        void present() override;
        bool isKeyPressed(const std::string &key) override;
        std::string getName() const override;
    
        // Méthodes génériques de l'interface
        void drawRect(int x, int y, int width, int height, int r, int g, int b, int a) override;
        void drawText(const std::string &text, int x, int y, int r, int g, int b, int a) override;
        void drawCircle(int x, int y, int radius, int r, int g, int b, int a) override;
        
        // Méthodes spécifiques à SDL2 (usage interne uniquement)
        void drawRect(int x, int y, int width, int height, SDL_Color color);
        void drawText(const std::string &text, int x, int y, SDL_Color color);
        void drawCircle(int x, int y, int radius, SDL_Color color);
        void handleInput();
        bool shouldQuit() const;
        bool _quit = false;

        std::string getTextInput(const std::string& prompt, const std::string& initialText = "") override;

    
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        TTF_Font *_font;
        std::map<std::string, bool> _keyStates;
        std::map<std::string, SDL_Keycode> _keyMap;
    };
}
#endif
