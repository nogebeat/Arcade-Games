/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** Pacman
*/

#include "Pacman.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>

    Pacman::Pacman() : 
        _isPaused(false),
        _gameOver(false),
        _gameWon(false),
        _score(0),
        _lives(3),
        _level(1),
        _dotsEaten(0),
        _ghostReleasedCount(0),
        _ghostReleaseTimer(0),
        _frightenedMode(false),
        _frightenedTimer(0),
        _direction(Direction::NONE),
        _nextDirection(Direction::NONE),
        _pacmanSpeed(5.0),
        _ghostSpeed(4.0)
    {
        std::random_device rd;
        _rng = std::mt19937(rd());
        init();
    }

    void Pacman::init()
    {
        reset();
    }

    void Pacman::reset()
    {
        _gameOver = false;
        _gameWon = false;
        _score = 0;
        _lives = 3;
        _level = 1;
        _dotsEaten = 0;
        _ghostReleasedCount = 0;
        _ghostReleaseTimer = 0;
        _frightenedMode = false;
        _frightenedTimer = 0;
        _pacmanSpeed = 5.0;
        _ghostSpeed = 4.0;

        spawnPacman();
        initMap();
        spawnGhosts();
        _lastUpdateTime = std::chrono::steady_clock::now();
        _lastGhostUpdateTime = std::chrono::steady_clock::now();
    }

    void Pacman::initMap()
    {
        _map.resize(GRID_HEIGHT, std::vector<CellType>(GRID_WIDTH, CellType::EMPTY));
        _totalDots = 0;
        _powerDots.clear();
        
        for (int x = 0; x < GRID_WIDTH; x++) {
            _map[0][x] = CellType::WALL;
            _map[GRID_HEIGHT - 1][x] = CellType::WALL;
        }
        
        for (int y = 0; y < GRID_HEIGHT; y++) {
            _map[y][0] = CellType::WALL;
            _map[y][GRID_WIDTH - 1] = CellType::WALL;
        }
        
        for (int x = 2; x < GRID_WIDTH - 2; x += 4) {
            for (int y = 2; y < GRID_HEIGHT - 2; y += 3) {
                if (x % 8 == 2 && y % 6 == 2) {
                    for (int dx = 0; dx < 2; dx++) {
                        for (int dy = 0; dy < 2; dy++) {
                            _map[y + dy][x + dx] = CellType::WALL;
                        }
                    }
                } else {
                    _map[y][x] = CellType::WALL;
                }
            }
        }
        
        _ghostHomePos = {GRID_WIDTH / 2, GRID_HEIGHT / 2};
        for (int y = _ghostHomePos.y - 2; y <= _ghostHomePos.y + 2; y++) {
            for (int x = _ghostHomePos.x - 3; x <= _ghostHomePos.x + 3; x++) {
                if (y == _ghostHomePos.y - 2 || y == _ghostHomePos.y + 2 || 
                    x == _ghostHomePos.x - 3 || x == _ghostHomePos.x + 3) {
                    _map[y][x] = CellType::WALL;
                } else {
                    _map[y][x] = CellType::EMPTY;
                }
            }
        }
        
        _map[_ghostHomePos.y - 2][_ghostHomePos.x] = CellType::EMPTY;
        std::vector<Position> avoidPositions = {
            _pacman,
            {_pacman.x, _pacman.y - 1},
            {_pacman.x, _pacman.y + 1},
            {_pacman.x - 1, _pacman.y},
            {_pacman.x + 1, _pacman.y}
        };
        for (int y = 1; y < GRID_HEIGHT - 1; y++) {
            for (int x = 1; x < GRID_WIDTH - 1; x++) {
                if (_map[y][x] == CellType::EMPTY) {
                    bool shouldAvoid = false;
                    for (const auto &avoidPos : avoidPositions) {
                        if (x == avoidPos.x && y == avoidPos.y) {
                            shouldAvoid = true;
                            break;
                        }
                    }
                    
                    if (!shouldAvoid) {
                        _map[y][x] = CellType::DOT;
                        _totalDots++;
                    }
                }
            }
        }
        
        std::vector<Position> powerDotPositions = {
            {2, 2}, {GRID_WIDTH - 3, 2}, 
            {2, GRID_HEIGHT - 3}, {GRID_WIDTH - 3, GRID_HEIGHT - 3}
        };
        
        for (const auto &pos : powerDotPositions) {
            if (_map[pos.y][pos.x] == CellType::DOT) {
                _map[pos.y][pos.x] = CellType::POWER_DOT;
                _powerDots.push_back(pos);
                _totalDots--;
            }
        }
    }

    void Pacman::spawnPacman()
    {
        _pacman = {GRID_WIDTH / 2, GRID_HEIGHT / 2 + 4};
        _direction = Direction::NONE;
        _nextDirection = Direction::NONE;
    }

    void Pacman::spawnGhosts()
    {
        for (int i = 0; i < 4; i++) {
            _ghosts[i].pos = {_ghostHomePos.x - 2 + i, _ghostHomePos.y};
            _ghosts[i].dir = Direction::NONE;
            _ghosts[i].nextDir = Direction::NONE;
            _ghosts[i].isBlue = false;
            _ghosts[i].isDead = false;
            _ghosts[i].respawnTimer = 0;
            _ghosts[i].blueTimer = 0;
        }
        _ghostReleasedCount = 1;
        _ghosts[0].pos = {_ghostHomePos.x, _ghostHomePos.y - 3};
    }

    void Pacman::update()
    {
        if (_isPaused || _gameOver || _gameWon)
            return;
        
        auto currentTime = std::chrono::steady_clock::now();
        double deltaTime = std::chrono::duration<double>(currentTime - _lastUpdateTime).count();
        double ghostDeltaTime = std::chrono::duration<double>(currentTime - _lastGhostUpdateTime).count();
        if (deltaTime >= 1.0 / _pacmanSpeed) {
            movePacman();
            checkCollisions();
        
        _lastUpdateTime = currentTime;
        }
        
        if (ghostDeltaTime >= 1.0 / _ghostSpeed) {
            moveGhosts();
            checkGhostCollisions();
            _lastGhostUpdateTime = currentTime;
            
            if (_ghostReleasedCount < 4) {
                _ghostReleaseTimer++;
                if (_ghostReleaseTimer >= 50) {
                    releaseGhost();
                    _ghostReleaseTimer = 0;
                }
            }
        }
        
        if (_frightenedMode) {
            _frightenedTimer--;
            if (_frightenedTimer <= 0) {
                _frightenedMode = false;
                for (auto &ghost : _ghosts) {
                    ghost.isBlue = false;
                }
            }
        }
        
        if (isAllDotsEaten()) {
            _level++;
            initMap();
            spawnPacman();
            spawnGhosts();
            _pacmanSpeed += 0.5;
            _ghostSpeed += 0.3;
        }
    }

    void Pacman::movePacman()
{
    if (_nextDirection != Direction::NONE && canMove(_pacman, _nextDirection)) {
        _direction = _nextDirection;
        _nextDirection = Direction::NONE;
    }
    if (_direction != Direction::NONE && canMove(_pacman, _direction)) {
        _pacman = getNextPosition(_pacman, _direction);
        _pacman = wrapPosition(_pacman);
    }
}

    void Pacman::moveGhosts()
    {
        for (size_t i = 0; i < _ghosts.size(); i++) {
            Ghost &ghost = _ghosts[i];
            if (i >= static_cast<size_t>(_ghostReleasedCount) || ghost.isDead) {
                if (ghost.isDead) {
                    ghost.respawnTimer--;
                    if (ghost.respawnTimer <= 0) {
                        ghost.isDead = false;
                        ghost.pos = {_ghostHomePos.x, _ghostHomePos.y - 3};
                        ghost.dir = Direction::NONE;
                        ghost.nextDir = Direction::NONE;
                    }
                }
                continue;
            }
            Direction nextDir;
            if (_frightenedMode && ghost.isBlue)
                nextDir = getRandomDirection(ghost.pos, ghost.dir);
            else
                nextDir = calculateGhostDirection(i);

            if (nextDir != Direction::NONE)
                ghost.dir = nextDir;

            if (ghost.dir != Direction::NONE && canMove(ghost.pos, ghost.dir)) {
                ghost.pos = getNextPosition(ghost.pos, ghost.dir);
                ghost.pos = wrapPosition(ghost.pos);
            } else {
                std::vector<Direction> possibleDirs = getPossibleDirections(ghost.pos, ghost.dir);
                if (!possibleDirs.empty()) {
                    std::uniform_int_distribution<int> dist(0, possibleDirs.size() - 1);
                    ghost.dir = possibleDirs[dist(_rng)];
                }
            }
        }
    }

    bool Pacman::canMove(const Position &pos, Direction dir) const
{
    Position nextPos = getNextPosition(pos, dir);
    nextPos = wrapPosition(nextPos);
    
    if (!isValidPosition(nextPos))
        return false;
    bool canMove = _map[nextPos.y][nextPos.x] != CellType::WALL;
    return canMove;
}

    Position Pacman::getNextPosition(const Position &pos, Direction dir) const
    {
        Position nextPos = pos;
        
        switch (dir) {
            case Direction::UP:
                nextPos.y--;
                break;
            case Direction::DOWN:
                nextPos.y++;
                break;
            case Direction::LEFT:
                nextPos.x--;
                break;
            case Direction::RIGHT:
                nextPos.x++;
                break;
            default:
                break;
        }
        
        return nextPos;
    }

    Position Pacman::wrapPosition(Position pos) const
    {
        if (pos.x < 0)
            pos.x = GRID_WIDTH - 1;
        else if (pos.x >= GRID_WIDTH)
            pos.x = 0;
        if (pos.y < 0)
            pos.y = GRID_HEIGHT - 1;
        else if (pos.y >= GRID_HEIGHT)
            pos.y = 0;
            
        return pos;
    }

    void Pacman::checkGhostCollisions()
    {
        for (auto &ghost : _ghosts) {
            if (ghost.isDead || ghost.pos != _pacman)
                continue;
                
            if (_frightenedMode && ghost.isBlue) {
                _score += 200;
                ghost.isDead = true;
                ghost.respawnTimer = 100;
            } else {
                _lives--;
                if (_lives <= 0) {
                    _gameOver = true;
                } else {
                    spawnPacman();
                }
                break;
            }
        }
    }

    void Pacman::releaseGhost()
    {
        if (_ghostReleasedCount < 4) {
            _ghostReleasedCount++;
            _ghosts[_ghostReleasedCount - 1].pos = {_ghostHomePos.x, _ghostHomePos.y - 3};
        }
    }

    void Pacman::startFrightenedMode()
    {
        _frightenedMode = true;
        _frightenedTimer = 100;
        
        for (auto &ghost : _ghosts) {
            if (!ghost.isDead) {
                ghost.isBlue = true;
                ghost.blueTimer = 100;
                
                switch (ghost.dir) {
                    case Direction::UP:
                        ghost.dir = Direction::DOWN;
                        break;
                    case Direction::DOWN:
                        ghost.dir = Direction::UP;
                        break;
                    case Direction::LEFT:
                        ghost.dir = Direction::RIGHT;
                        break;
                    case Direction::RIGHT:
                        ghost.dir = Direction::LEFT;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    bool Pacman::isAllDotsEaten() const
    {
        return _dotsEaten >= _totalDots;
    }

    bool Pacman::isValidPosition(const Position &pos) const
    {
        return pos.x >= 0 && pos.x < GRID_WIDTH && pos.y >= 0 && pos.y < GRID_HEIGHT;
    }

    Direction Pacman::getRandomDirection(const Position &pos, Direction currentDir) const
    {
        std::vector<Direction> possibleDirs = getPossibleDirections(pos, currentDir);
        
        if (possibleDirs.empty())
            return Direction::NONE;
            
        std::uniform_int_distribution<int> dist(0, possibleDirs.size() - 1);
        return possibleDirs[dist(_rng)];
    }

    std::vector<Direction> Pacman::getPossibleDirections(const Position &pos, Direction currentDir) const
    {
        std::vector<Direction> possibleDirs;
    
        for (Direction dir : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT}) {
            if ((dir == Direction::UP && currentDir == Direction::DOWN) ||
                (dir == Direction::DOWN && currentDir == Direction::UP) ||
                (dir == Direction::LEFT && currentDir == Direction::RIGHT) ||
                (dir == Direction::RIGHT && currentDir == Direction::LEFT)) {
                continue;
            }
            
            if (canMove(pos, dir)) {
                possibleDirs.push_back(dir);
            }
        }
        
        return possibleDirs;
    }

    Direction Pacman::calculateGhostDirection(int ghostIndex)
    {
        Ghost &ghost = _ghosts[ghostIndex];
        Position target;

        switch (ghostIndex) {
            case 0:
                target = _pacman;
                break;
            case 1:
                target = _pacman;
                for (int i = 0; i < 4; i++)
                    target = getNextPosition(target, _direction);
                break;
            case 2:
                target = _pacman;
                for (int i = 0; i < 2; i++)
                    target = getNextPosition(target, _direction);
                target.x = target.x + (target.x - _ghosts[0].pos.x);
                target.y = target.y + (target.y - _ghosts[0].pos.y);
                break;
            case 3:
                {
                    int distToPacman = std::abs(ghost.pos.x - _pacman.x) + std::abs(ghost.pos.y - _pacman.y);
                    if (distToPacman > 8)
                        target = _pacman;
                    else
                        target = {2, GRID_HEIGHT - 3};
                }
                break;
        }
        
        std::vector<Direction> possibleDirs = getPossibleDirections(ghost.pos, ghost.dir);
        if (possibleDirs.empty())
            return Direction::NONE;
            
        Direction bestDir = possibleDirs[0];
        int bestDistance = INT_MAX;
        
        for (Direction dir : possibleDirs) {
            Position nextPos = getNextPosition(ghost.pos, dir);
            nextPos = wrapPosition(nextPos);
            
            int distance = std::abs(nextPos.x - target.x) + std::abs(nextPos.y - target.y);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestDir = dir;
            }
        }
        
        return bestDir;
    }

    void Pacman::processEvent(GameEvent event)
{
    if (event == GameEvent::PAUSE) {
        _isPaused = !_isPaused;
        return;
    }
    
    if (_isPaused || _gameOver || _gameWon)
        return;
        
    switch (event) {
        case GameEvent::UP:
            _nextDirection = Direction::UP;
            break;
        case GameEvent::DOWN:
            _nextDirection = Direction::DOWN;
            break;
        case GameEvent::LEFT:
            _nextDirection = Direction::LEFT;
            break;
        case GameEvent::RIGHT:
            _nextDirection = Direction::RIGHT;
            break;
        case GameEvent::RESTART:
            reset();
            break;
        default:
            break;
    }
}

    std::vector<std::vector<Cell>> Pacman::getGrid() const
    {
        std::vector<std::vector<Cell>> grid(GRID_HEIGHT, std::vector<Cell>(GRID_WIDTH, {CellType::EMPTY, 0}));

        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                grid[y][x].type = _map[y][x];
                
                switch (_map[y][x]) {
                    case CellType::WALL:
                        grid[y][x].color = 1;
                        break;
                    case CellType::DOT:
                        grid[y][x].color = 7;
                        break;
                    case CellType::POWER_DOT:
                        grid[y][x].color = 5;
                        break;
                    default:
                        grid[y][x].color = 0;
                        break;
                }
            }
        }
        
        grid[_pacman.y][_pacman.x].type = CellType::PACMAN;
        grid[_pacman.y][_pacman.x].color = 3;
        
        for (size_t i = 0; i < _ghosts.size(); i++) {
            const Ghost &ghost = _ghosts[i];
            if (ghost.isDead)
                continue;
                
            grid[ghost.pos.y][ghost.pos.x].type = CellType::GHOST;
            
            if (_frightenedMode && ghost.isBlue)
                grid[ghost.pos.y][ghost.pos.x].color = 6;
            else
                switch (i) {
                    case 0:
                        grid[ghost.pos.y][ghost.pos.x].color = 2;
                        break;
                    case 1:
                        grid[ghost.pos.y][ghost.pos.x].color = 5;
                        break;
                    case 2:
                        grid[ghost.pos.y][ghost.pos.x].color = 6;
                        break;
                    case 3:
                        grid[ghost.pos.y][ghost.pos.x].color = 4;
                        break;
                }
        }
        return grid;
    }
    
    void Pacman::checkCollisions()
    {
        if (!isValidPosition(_pacman))
            return;
        CellType previousCell = _map[_pacman.y][_pacman.x];
        // if (previousCell == CellType::DOT) {
        //     _map[_pacman.y][_pacman.x] = CellType::EMPTY; c'est ici qui ne marche pas bien 
        //     _score += 10;
        //     _dotsEaten++;
        // }
        if (previousCell == CellType::POWER_DOT) {
            _map[_pacman.y][_pacman.x] = CellType::EMPTY;
            _score += 50;
            _dotsEaten++;
            startFrightenedMode();
        }
    }
