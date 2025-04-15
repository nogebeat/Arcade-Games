/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-[...]
** File description:
** Nibbler
*/

#include "Nibbler.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include <deque>


namespace arcade {

    Direction leftOf(Direction d) {
        switch(d) {
            case Direction::UP:    return Direction::LEFT;
            case Direction::DOWN:  return Direction::RIGHT;
            case Direction::LEFT:  return Direction::DOWN;
            case Direction::RIGHT: return Direction::UP;
        }
        return Direction::UP; 
    }

    Direction rightOf(Direction d) {
        switch(d) {
            case Direction::UP:    return Direction::RIGHT;
            case Direction::DOWN:  return Direction::LEFT;
            case Direction::LEFT:  return Direction::UP;
            case Direction::RIGHT: return Direction::DOWN;
        }
        return Direction::UP;
    }

    Nibbler::Nibbler() :
        _direction(Direction::RIGHT),
        _pendingDirection(Direction::RIGHT),
        _gameOver(false),
        _isPaused(false),
        _score(0),
        _speed(5.0)
    {
        std::random_device rd;
        _rng = std::mt19937(rd());
    }

    void Nibbler::init() {
        reset();
        std::cout << "Nibbler game initialized" << std::endl;
    }

    void Nibbler::reset() {
        _snake.clear();
        _gameOver = false;
        _score = 0;
        _speed = 5.0;

        initMazeAndFood();

        int startX = GRID_WIDTH / 2;
        int startY = GRID_HEIGHT - 2;
        if(isWall({startX, startY})) {
            startX = 1;
            startY = GRID_HEIGHT - 2;
        }
        _snake.push_front({startX, startY});
        _snake.push_back({startX - 1, startY});
        _snake.push_back({startX - 2, startY});

        _direction = Direction::RIGHT;
        _pendingDirection = Direction::RIGHT;

        for(const auto &pos : _snake) {
            if(isValidPosition(pos))
                _foodMap[pos.y][pos.x] = false;
        }

        _lastUpdateTime = std::chrono::steady_clock::now();
    }

    void Nibbler::initMazeAndFood() {
        _maze.assign(GRID_HEIGHT, std::vector<bool>(GRID_WIDTH, false));
        _foodMap.assign(GRID_HEIGHT, std::vector<bool>(GRID_WIDTH, true));

        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                if (y == 0 || y == GRID_HEIGHT - 1 || x == 0 || x == GRID_WIDTH - 1) {
                    _maze[y][x] = true;
                    _foodMap[y][x] = false;
                }
            }
        }

        int midX = GRID_WIDTH / 2;
        for (int y = 2; y < GRID_HEIGHT - 2; y++) {
            _maze[y][midX] = true;
            _foodMap[y][midX] = false;
        }

        int midY = GRID_HEIGHT / 2;
        for (int x = 2; x < GRID_WIDTH - 2; x++) {
            _maze[midY][x] = true;
            _foodMap[midY][x] = false;
        }
        
    }

    bool Nibbler::isValidPosition(const Position &pos) const {
        return pos.x >= 0 && pos.x < GRID_WIDTH && pos.y >= 0 && pos.y < GRID_HEIGHT;
    }

    bool Nibbler::isWall(const Position &pos) const {
        if (!isValidPosition(pos))
            return true;
        return _maze[pos.y][pos.x];
    }

    bool Nibbler::isFood(const Position &pos) const {
        if (!isValidPosition(pos))
            return false;
        return _foodMap[pos.y][pos.x];
    }

    void Nibbler::eatFoodAt(const Position &pos) {
        if(isValidPosition(pos) && _foodMap[pos.y][pos.x]) {
            _foodMap[pos.y][pos.x] = false;
            _score += 10;
            _speed += 0.2;
        }
    }

    bool Nibbler::foodRemaining() const {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                if (_foodMap[y][x])
                    return true;
            }
        }
        return false;
    }

    void Nibbler::update() {
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

    void Nibbler::processEvent(GameEvent event) {
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

    bool Nibbler::checkCollision(const Position &pos) const {
        auto it = _snake.begin();
        ++it;
        for (; it != _snake.end(); ++it) {
            if (pos.x == it->x && pos.y == it->y)
                return true;
        }
        return false;
    }

    void Nibbler::moveSnake() {
        Position newHead = _snake.front();

        switch (_direction) {
            case Direction::UP:    newHead.y--; break;
            case Direction::DOWN:  newHead.y++; break;
            case Direction::LEFT:  newHead.x--; break;
            case Direction::RIGHT: newHead.x++; break;
        }

        if (isWall(newHead)) {
            Direction leftDir = leftOf(_direction);
            Direction rightDir = rightOf(_direction);
            Position leftPos = _snake.front();
            Position rightPos = _snake.front();

            switch (leftDir) {
                case Direction::UP:    leftPos.y--; break;
                case Direction::DOWN:  leftPos.y++; break;
                case Direction::LEFT:  leftPos.x--; break;
                case Direction::RIGHT: leftPos.x++; break;
            }
            switch (rightDir) {
                case Direction::UP:    rightPos.y--; break;
                case Direction::DOWN:  rightPos.y++; break;
                case Direction::LEFT:  rightPos.x--; break;
                case Direction::RIGHT: rightPos.x++; break;
            }

            bool canTurnLeft = isValidPosition(leftPos) && !isWall(leftPos);
            bool canTurnRight = isValidPosition(rightPos) && !isWall(rightPos);

            if (canTurnLeft && _pendingDirection == leftDir) {
                _direction = leftDir;
                newHead = leftPos;
            } else if (canTurnRight && _pendingDirection == rightDir) {
                _direction = rightDir;
                newHead = rightPos;
            } else if (canTurnLeft && !canTurnRight) {
                _direction = leftDir;
                newHead = leftPos;
            } else if (canTurnRight && !canTurnLeft) {
                _direction = rightDir;
                newHead = rightPos;
            } else if (canTurnLeft && canTurnRight) {
                _direction = leftDir;
                newHead = leftPos;
            } else {
                return;
            }
        }

        if (checkCollision(newHead)) {
            _gameOver = true;
            return;
        }

        _snake.push_front(newHead);

        if (isFood(newHead)) {
            eatFoodAt(newHead);
        } else {
            _snake.pop_back();
        }

        if (!foodRemaining()) {
            std::cout << "Level complete! Score: " << _score << std::endl;
            reset();
        }
    }

    std::vector<std::vector<Cell>> Nibbler::getGrid() const {
        std::vector<std::vector<Cell>> grid(GRID_HEIGHT, std::vector<Cell>(GRID_WIDTH, {CellType::EMPTY, 0}));

        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                if (_maze[y][x]) {
                    grid[y][x] = {CellType::WALL, 7};
                } else if (_foodMap[y][x]) {
                    grid[y][x] = {CellType::FOOD, 2};
                }
            }
        }

        if (!_snake.empty()) {
            grid[_snake.front().y][_snake.front().x] = {CellType::SNAKE_HEAD, 3};
        }
        for (size_t i = 1; i < _snake.size(); i++) {
            grid[_snake[i].y][_snake[i].x] = {CellType::SNAKE_BODY, 3};
        }
        return grid;
    }

}
