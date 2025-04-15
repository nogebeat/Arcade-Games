/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "../../../includes/Interfaces/IGameModule.hpp"
#include <vector>
#include <deque>
#include <random>
#include <chrono>
#include <memory>

namespace arcade {

    // enum class Direction {
    //     UP,
    //     DOWN,
    //     LEFT,
    //     RIGHT
    // };

    // enum class CellType {
    //     EMPTY,
    //     SNAKE_HEAD,
    //     SNAKE_BODY,
    //     FOOD
    // };

    struct Position {
        int x;
        int y;
        
        bool operator==(const Position &other) const {
            return x == other.x && y == other.y;
        }
    };

    class Snake : public IGameModule {
    public:
        Snake();
        ~Snake() = default;

        void init();
        void update();
        void render();
        void handleInput();
        
        void processEvent(GameEvent event);
        
        bool isGameOver() const { return _gameOver; }
        int getScore() const { return _score; }
        
        const std::deque<Position>& getSnake() const { return _snake; }
        const Position& getFood() const { return _food; }
        int getGridWidth() const { return GRID_WIDTH; }
        int getGridHeight() const { return GRID_HEIGHT; }
        std::string getName() const override { return "Snake"; }
        bool isPaused() const override { return _isPaused; }
        std::vector<std::vector<Cell>> getGrid() const;
        std::vector<GameEntity> getEntities() const {}
        
        
    private:
        bool _isPaused = false;
        static const int GRID_WIDTH = 20;
        static const int GRID_HEIGHT = 15;
        static const int CELL_SIZE = 40;
        
        std::deque<Position> _snake;
        Position _food;
        Direction _direction;
        Direction _pendingDirection;
        
        bool _gameOver;
        int _score;
        double _speed;
        std::chrono::steady_clock::time_point _lastUpdateTime;
        
        std::mt19937 _rng;
        
        void spawnFood();
        bool isValidPosition(const Position &pos) const;
        void moveSnake();
        bool checkCollision(const Position &pos) const;
        void growSnake();
        void reset();
    };

}

#endif /* !SNAKE_HPP_ */
