/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** SDL2Module
*/

#include "../includes/Display/SDL2Display.hpp"

extern "C"
{
    arcade::IDisplayModule *createDisplay()
    {
        return new arcade::SDL2Display();
    }

    void destroyDisplay(arcade::IDisplayModule *display)
    {
        delete display;
    }
}
