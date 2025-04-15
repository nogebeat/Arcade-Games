/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** Types
*/

#ifndef TYPES_HPP_
#define TYPES_HPP_
#include <vector>

namespace arcade {
    
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 625;
    const int GRID_WIDTH = 20;
    const int GRID_HEIGHT = 15;

    enum class GameEvent {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ACTION,
        QUIT,
        PAUSE,
        RESTART
    };

    enum class CellType {
        EMPTY,
        WALL,
        DOT,
        POWER_DOT,
        PACMAN,
        GHOST,
        SNAKE_HEAD,
        SNAKE_BODY,
        FOOD,
    };

    enum class EntityType {
        WALL,
        DOT,
        POWER_DOT,
        PACMAN,
        GHOST
    };

    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };
    
    struct Cell {
        CellType type;
        char character;
        int colorIndex;
        int color;

        Cell(CellType t = CellType::EMPTY, char c = ' ', int color = 0) 
            : type(t), character(c), colorIndex(color) {}
    };

    struct GameEntity {
        EntityType type; // enum personnalisé: WALL, PACMAN, GHOST, DOT, POWER_DOT
        int x, y;
        int color;
        Direction dir; // Pour l'animation
    };

    struct Color {
        unsigned char r, g, b, a;

        Color(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0, unsigned char alpha = 255)
            : r(red), g(green), b(blue), a(alpha) {}
    };
}

#endif /* !TYPES_HPP_ */
