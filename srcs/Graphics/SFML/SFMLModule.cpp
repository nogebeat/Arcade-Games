/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** SDL2Module
*/

#include "../includes/Display/SFMLDisplay.hpp"

extern "C" {
    arcade::IDisplayModule *createDisplay()
    {
        return new arcade::SFMLDisplay();
    }
    
    void destroyDisplay(arcade::IDisplayModule *display)
    {
        delete display;
    }
}

