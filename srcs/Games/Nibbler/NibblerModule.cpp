/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** NibblerModule
*/

#include "Nibbler.hpp"

extern "C" {
    arcade::IGameModule *createGame()
    {
        return new arcade::Nibbler();
    }
    
    void destroyGame(arcade::IGameModule *game)
    {
        delete game;
    }
}
