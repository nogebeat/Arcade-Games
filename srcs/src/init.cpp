/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** init
*/

#include "../../includes/my.hpp"
#include "../../includes/Core/ArcadeCore.hpp"
#include "../../includes/Utils/Error.hpp"
#include <iostream>

int main_second(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <graphic_library_path>" << std::endl;
        return 84;
    }

    try {
        arcade::ArcadeCore arcadeCore(av[1]);
        arcadeCore.run();
        return 0;
    } catch (const arcade::Error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
}