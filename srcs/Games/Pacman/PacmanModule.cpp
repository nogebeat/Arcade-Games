/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** PacmanModule
*/

#include "Pacman.hpp"

extern "C" {
    IGameModule *createGame()
    {
        return new Pacman();
    }
    
    void destroyGame(arcade::IGameModule *game)
    {
        delete game;
    }
}
