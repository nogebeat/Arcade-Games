/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_
#include "../my.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace arcade {
    class IDisplayModule {
    public:
        virtual ~IDisplayModule() = default;
        virtual void init() = 0;
        virtual void stop() = 0;
        virtual void clear() = 0;
        virtual void render() = 0;
        virtual void present() = 0;
        virtual bool isKeyPressed(const std::string &key) = 0;
        virtual std::string getName() const = 0;
        virtual void handleInput() = 0;
        virtual std::string getTextInput(const std::string& prompt, const std::string& initialText = "") = 0;
        virtual bool shouldQuit() const = 0;
        virtual void drawRect(int x, int y, int width, int height, int r, int g, int b, int a) = 0;
        virtual void drawText(const std::string& text, int x, int y, int r, int g, int b, int a) = 0;
        virtual void drawCircle(int x, int y, int radius, int r, int g, int b, int a) = 0;

    };
}

#endif /* !IDISPLAYMODULE_HPP_ */
