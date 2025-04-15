/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** NCursesModule
*/

#include "../includes/Display/NCursesDisplay.hpp"

extern "C" {
    arcade::IDisplayModule *createDisplay()
    {
        return new arcade::NCursesDisplay();
    }
    
    void destroyDisplay(arcade::IDisplayModule *display)
    {
        delete display;
    }
}