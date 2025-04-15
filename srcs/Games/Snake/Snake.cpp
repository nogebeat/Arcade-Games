/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** Snake
*/

#include "Snake.hpp"
#include <iostream>
#include <algorithm>

namespace arcade {

    Snake::Snake() : 
        _direction(Direction::RIGHT),
        _pendingDirection(Direction::RIGHT),
        _gameOver(false),
        _score(0),
        _speed(5.0)
    {
        std::random_device rd;
        _rng = std::mt19937(rd());
    }

    void Snake::init()
    {
        reset();
        std::cout << "Snake game initialized" << std::endl;
    }

    void Snake::reset()
    {
        _snake.clear();
        _gameOver = false;
        _score = 0;
        _speed = 5.0;
        
        int startX = GRID_WIDTH / 2;
        int startY = GRID_HEIGHT / 2;
        
        _snake.push_front({startX, startY});         
        _snake.push_back({startX - 1, startY});      
        _snake.push_back({startX - 2, startY});
        
        _direction = Direction::RIGHT;
        _pendingDirection = Direction::RIGHT;
        
        spawnFood();
        
        _lastUpdateTime = std::chrono::steady_clock::now();
    }

    void Snake::update()
    {
        if (_isPaused) return;
        if (_gameOver) return;
        
        auto currentTime = std::chrono::steady_clock::now();
        double deltaTime = std::chrono::duration<double>(currentTime - _lastUpdateTime).count();
        
        if (deltaTime >= 1.0 / _speed) {
            _direction = _pendingDirection;
            moveSnake();
            _lastUpdateTime = currentTime;
        }
    }

    void Snake::processEvent(GameEvent event)
    {
        if (event == GameEvent::PAUSE) {
            _isPaused = !_isPaused;
            return; 
    }
    if (_isPaused) return; 
        if (_gameOver) {
            if (event == GameEvent::RESTART) {
                reset();
            }
            return;
        }
        switch (event) {
            case GameEvent::UP:
                if (_direction != Direction::DOWN)
                    _pendingDirection = Direction::UP;
                break;
            case GameEvent::DOWN:
                if (_direction != Direction::UP)
                    _pendingDirection = Direction::DOWN;
                break;
            case GameEvent::LEFT:
                if (_direction != Direction::RIGHT)
                    _pendingDirection = Direction::LEFT;
                break;
            case GameEvent::RIGHT:
                if (_direction != Direction::LEFT)
                    _pendingDirection = Direction::RIGHT;
                break;
            case GameEvent::RESTART:
                reset();
                break;
            default:
                break;
        }
    }

    std::vector<std::vector<Cell>> Snake::getGrid() const {
        std::vector<std::vector<Cell>> grid(GRID_HEIGHT, std::vector<Cell>(GRID_WIDTH, {CellType::EMPTY, 0}));
        
        grid[_food.y][_food.x] = {CellType::FOOD, 1};  
        if (!_snake.empty()) {
            grid[_snake.front().y][_snake.front().x] = {CellType::SNAKE_HEAD, 3};
        }
        for (size_t i = 1; i < _snake.size(); ++i) {
            grid[_snake[i].y][_snake[i].x] = {CellType::SNAKE_BODY, 3};
        }
        return grid;
    }

    void Snake::spawnFood()
    {
        if (_snake.size() >= GRID_WIDTH * GRID_HEIGHT) {
            return;
        }
        
        std::uniform_int_distribution<int> distX(0, GRID_WIDTH - 1);
        std::uniform_int_distribution<int> distY(0, GRID_HEIGHT - 1);
        
        do {
            _food = {distX(_rng), distY(_rng)};
        } while (std::find_if(_snake.begin(), _snake.end(), [this](const Position &pos) {
            return pos.x == _food.x && pos.y == _food.y;
        }) != _snake.end());
    }

    bool Snake::isValidPosition(const Position &pos) const
    {
        return pos.x >= 0 && pos.x < GRID_WIDTH && pos.y >= 0 && pos.y < GRID_HEIGHT;
    }

    void Snake::moveSnake()
    {
        Position newHead = _snake.front();
        
        switch (_direction) {
            case Direction::UP:
                newHead.y--;
                break;
            case Direction::DOWN:
                newHead.y++;
                break;
            case Direction::LEFT:
                newHead.x--;
                break;
            case Direction::RIGHT:
                newHead.x++;
                break;
        }
        
        if (!isValidPosition(newHead) || checkCollision(newHead)) {
            _gameOver = true;
            return;
        }
        
        _snake.push_front(newHead);
        
        if (newHead.x == _food.x && newHead.y == _food.y) {
            _score += 10;
            _speed += 0.2;
            spawnFood();
        } else {
            _snake.pop_back();
        }
    }

    bool Snake::checkCollision(const Position &pos) const
    {
        auto it = _snake.begin();
        ++it;
        
        for (; it != _snake.end(); ++it) {
            if (pos.x == it->x && pos.y == it->y) {
                return true;
            }
        }
        
        return false;
    }
}
