/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_
#include "../../../includes/Interfaces/IGameModule.hpp"
#include <vector>
#include <deque>
#include <random>
#include <chrono>
#include <memory>
#include <array>
#include <queue>

using namespace arcade;

struct Position {
    int x;
    int y;
    
    bool operator==(const Position &other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Position &other) const {
        return !(*this == other);
    }
};
struct Ghost {
    Position pos;
    Direction dir;
    Direction nextDir;
    bool isBlue;
    bool isDead;
    int respawnTimer;
    int blueTimer;
};
class Pacman : public IGameModule {
    public:
        Pacman();
        ~Pacman() = default;
        void init() override;
        void update() override;
        void processEvent(GameEvent event) override;
        bool isGameOver() const override { return _gameOver; }
        int getScore() const override { return _score; }
        std::string getName() const override { return "Pacman"; }
        bool isPaused() const override { return _isPaused; }
        std::vector<std::vector<Cell>> getGrid() const override;
        void reset() override;

        std::vector<GameEntity> getEntities() const
        {
            std::vector<GameEntity> entities;
            for (int y = 0; y < GRID_HEIGHT; y++) {
                for (int x = 0; x < GRID_WIDTH; x++) {
                    if (_map[y][x] == CellType::WALL)
                        entities.push_back({EntityType::WALL, x, y, 1, Direction::NONE});
                    else if (_map[y][x] == CellType::DOT)
                        entities.push_back({EntityType::DOT, x, y, 7, Direction::NONE});
                    else if (_map[y][x] == CellType::POWER_DOT)
                        entities.push_back({EntityType::POWER_DOT, x, y, 5, Direction::NONE});
                }
            }
            entities.push_back({EntityType::PACMAN, _pacman.x, _pacman.y, 3, _direction});
            for (size_t i = 0; i < _ghosts.size(); i++) {
                if (!_ghosts[i].isDead) {
                    int ghostColor = _frightenedMode && _ghosts[i].isBlue ? 6 : (i + 2);
                    entities.push_back({EntityType::GHOST, _ghosts[i].pos.x, _ghosts[i].pos.y, ghostColor, _ghosts[i].dir});
                }
            }
            
            return entities;
        }
    private:
        static const int GRID_WIDTH = 28;
        static const int GRID_HEIGHT = 31;
        // Game state
        bool _isPaused;
        bool _gameOver;
        bool _gameWon;
        int _score;
        int _lives;
        int _level;
        int _dotsEaten;
        int _ghostReleasedCount;
        int _ghostReleaseTimer;
        bool _frightenedMode;
        int _frightenedTimer;
        // Pacman state
        Position _pacman;
        Direction _direction;
        Direction _nextDirection;
        // Ghosts
        std::array<Ghost, 4> _ghosts;
        Position _ghostHomePos;
        // Map
        std::vector<std::vector<CellType>> _map;
        int _totalDots;
        std::vector<Position> _powerDots;
        // Timing
        std::chrono::steady_clock::time_point _lastUpdateTime;
        std::chrono::steady_clock::time_point _lastGhostUpdateTime;
        double _pacmanSpeed;
        double _ghostSpeed;
        // RNG
        mutable std::mt19937 _rng;
        // Methods
        void initMap();
        void spawnPacman();
        void spawnGhosts();
        void movePacman();
        void moveGhosts();
        bool canMove(const Position &pos, Direction dir) const;
        Position getNextPosition(const Position &pos, Direction dir) const;
        void checkCollisions();
        void checkGhostCollisions();
        void releaseGhost();
        void startFrightenedMode();
        bool isAllDotsEaten() const;
        bool isValidPosition(const Position &pos) const;
        Direction getRandomDirection(const Position &pos, Direction currentDir) const;
        Direction calculateGhostDirection(int ghostIndex);
        Position wrapPosition(Position pos) const;
        std::vector<Direction> getPossibleDirections(const Position &pos, Direction currentDir) const;
};


#endif 