/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** DisplayGames
*/


#include "../../includes/Core/ArcadeCore.hpp"

using namespace arcade;

void ArcadeCore::displaySDL2Pacman()
{

    auto entities = _gameModule->getEntities();
    
    int cellSize = std::min(WINDOW_WIDTH / GRID_WIDTH, WINDOW_HEIGHT / GRID_HEIGHT);
    int offsetX = (WINDOW_WIDTH - GRID_WIDTH * cellSize) / 2;
    int offsetY = (WINDOW_HEIGHT - GRID_HEIGHT * cellSize) / 2;
    _displayModule->drawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 255);
    
    for (const auto& entity : entities) {
        int r = 0, g = 0, b = 0, a = 255;
        
        switch (entity.type) {
            case EntityType::WALL:
                r = 0; g = 0; b = 255;
                _displayModule->drawRect(
                    offsetX + entity.x * cellSize,
                    offsetY + entity.y * cellSize,
                    cellSize, cellSize,
                    r, g, b, a
                );
                break;
            case EntityType::DOT:
                r = 255; g = 255; b = 255;
                _displayModule->drawCircle(
                    offsetX + entity.x * cellSize + cellSize/2,
                    offsetY + entity.y * cellSize + cellSize/2,
                    cellSize/6,
                    r, g, b, a
                );
                break;
            case EntityType::POWER_DOT:
                r = 255; g = 0; b = 255;
                _displayModule->drawCircle(
                    offsetX + entity.x * cellSize + cellSize/2,
                    offsetY + entity.y * cellSize + cellSize/2,
                    cellSize/3,
                    r, g, b, a
                );
                break;
            case EntityType::PACMAN:
                r = 255; g = 255; b = 0;
                _displayModule->drawCircle(
                    offsetX + entity.x * cellSize + cellSize/2,
                    offsetY + entity.y * cellSize + cellSize/2,
                    cellSize/2 - 2,
                    r, g, b, a
                );
                break;
            case EntityType::GHOST:
                switch (entity.color) {
                    case 2:
                        r = 255; g = 0; b = 0;
                        break;
                    case 3:
                        r = 255; g = 184; b = 255;
                        break;
                    case 4:
                        r = 0; g = 255; b = 255;
                        break;
                    case 5:
                        r = 255; g = 184; b = 82;
                        break;
                    case 6:
                        r = 0; g = 0; b = 255;
                        break;
                }
                _displayModule->drawRect(
                    offsetX + entity.x * cellSize,
                    offsetY + entity.y * cellSize,
                    cellSize, cellSize,
                    r, g, b, a
                );
                break;
        }
    }
    
    std::string scoreText = "Score: " + std::to_string(_gameModule->getScore());
    _displayModule->drawText(scoreText, 10, WINDOW_HEIGHT - 30, 255, 255, 255, 255);
    
    _displayModule->present();
}

void ArcadeCore::displaySFMLPacman()
{
    auto entities = _gameModule->getEntities();
    
    int cellSize = std::min(WINDOW_WIDTH / GRID_WIDTH, WINDOW_HEIGHT / GRID_HEIGHT);
    int offsetX = (WINDOW_WIDTH - GRID_WIDTH * cellSize) / 2;
    int offsetY = (WINDOW_HEIGHT - GRID_HEIGHT * cellSize) / 2;
    _displayModule->drawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 255);
    
    for (const auto& entity : entities) {
        int r = 0, g = 0, b = 0, a = 255;
        
        switch (entity.type) {
            case EntityType::WALL:
                r = 0; g = 0; b = 255;
                _displayModule->drawRect(
                    offsetX + entity.x * cellSize,
                    offsetY + entity.y * cellSize,
                    cellSize, cellSize,
                    r, g, b, a
                );
                break;
            case EntityType::DOT:
                r = 255; g = 255; b = 255;
                _displayModule->drawCircle(
                    offsetX + entity.x * cellSize + cellSize/2,
                    offsetY + entity.y * cellSize + cellSize/2,
                    cellSize/6,
                    r, g, b, a
                );
                break;
            case EntityType::POWER_DOT:
                r = 255; g = 0; b = 255;
                _displayModule->drawCircle(
                    offsetX + entity.x * cellSize + cellSize/2,
                    offsetY + entity.y * cellSize + cellSize/2,
                    cellSize/3,
                    r, g, b, a
                );
                break;
            case EntityType::PACMAN:
                r = 255; g = 255; b = 0;
                _displayModule->drawCircle(
                    offsetX + entity.x * cellSize + cellSize/2,
                    offsetY + entity.y * cellSize + cellSize/2,
                    cellSize/2 - 2,
                    r, g, b, a
                );
                break;
            case EntityType::GHOST:
                switch (entity.color) {
                    case 2:
                        r = 255; g = 0; b = 0;
                        break;
                    case 3:
                        r = 255; g = 184; b = 255;
                        break;
                    case 4:
                        r = 0; g = 255; b = 255;
                        break;
                    case 5:
                        r = 255; g = 184; b = 82;
                        break;
                    case 6:
                        r = 0; g = 0; b = 255;
                        break;
                }
                _displayModule->drawRect(
                    offsetX + entity.x * cellSize,
                    offsetY + entity.y * cellSize,
                    cellSize, cellSize,
                    r, g, b, a
                );
                break;
        }
    }
    
    std::string scoreText = "Score: " + std::to_string(_gameModule->getScore());
    _displayModule->drawText(scoreText, 10, WINDOW_HEIGHT - 30, 255, 255, 255, 255);
    
    _displayModule->present();
}

void ArcadeCore::displayNCursesPacman()
{
    _displayModule->clear();
    
    auto grid = _gameModule->getGrid();
    for (int x = 0; x < GRID_WIDTH + 2; x++) {
        _displayModule->drawText("#", x, 0, 0, 0, 255, 255);
        _displayModule->drawText("#", x, GRID_HEIGHT + 1, 0, 0, 255, 255); 
    }
    for (int y = 0; y < GRID_HEIGHT + 2; y++) {
        _displayModule->drawText("#", 0, y, 0, 0, 255, 255); 
        _displayModule->drawText("#", GRID_WIDTH + 1, y, 0, 0, 255, 255); 
    }
    for (std::size_t y = 0; y < grid.size(); y++) {
        for (std::size_t x = 0; x < grid[y].size(); x++) {
            int displayX = x + 1;
            int displayY = y + 1;
            int r = 255, g = 255, b = 255;
            std::string displayChar = " ";
            
            switch (grid[y][x].type) {
                case CellType::WALL:
                    displayChar = "#";
                    r = 0; g = 0; b = 255;
                    break;
                case CellType::DOT:
                    displayChar = ".";
                    r = 255; g = 255; b = 255;
                    break;
                case CellType::POWER_DOT:
                    displayChar = "O";
                    r = 255; g = 0; b = 255;
                    break;
                case CellType::PACMAN:
                    displayChar = "C";
                    r = 255; g = 255; b = 0;
                    break;
                case CellType::GHOST:
                    displayChar = "M";
                    switch (grid[y][x].color) {
                        case 2:
                            r = 255; g = 0; b = 0;
                            break;
                        case 5:
                            r = 255; g = 0; b = 255;
                            break;
                        case 6:
                            r = 0; g = 255; b = 255;
                            break;
                        case 4:
                            r = 255; g = 165; b = 0;
                            break;
                    }
                    break;
                case CellType::EMPTY:
                default:
                    displayChar = " ";
                    break;
            }
            
            _displayModule->drawText(displayChar, displayX, displayY, r, g, b, 255);
        }
    }
    std::string scoreText = "Score: " + std::to_string(_gameModule->getScore());
    _displayModule->drawText(scoreText, 1, GRID_HEIGHT + 2, 255, 255, 255, 255);
    _displayModule->present();
}

void ArcadeCore::displaySDL2Snake()
{
    auto grid = _gameModule->getGrid();
            
    int cellWidth = WINDOW_WIDTH / GRID_WIDTH;
    int cellHeight = WINDOW_HEIGHT / GRID_HEIGHT;
    
    for (std::size_t y = 0; y < GRID_HEIGHT && y < grid.size(); y++) {
        for (std::size_t x = 0; x < GRID_WIDTH && x < grid[y].size(); x++) {
            CellType cellType = grid[y][x].type;
            int r, g, b, a = 255;
            
            switch (cellType) {
                case CellType::EMPTY:
                    r = 0; g = 0; b = 0;
                    break;
                case CellType::SNAKE_HEAD:
                    r = 0; g = 255; b = 0;
                    break;
                case CellType::SNAKE_BODY:
                    r = 0; g = 200; b = 0;
                    break;
                case CellType::FOOD:
                    r = 255; g = 0; b = 0;
                    break;
                default:
                    r = 128; g = 128; b = 128;
            }
            
            _displayModule->drawRect(x * cellWidth, y * cellHeight, cellWidth, cellHeight, r, g, b, a);
        }
    }
    std::string scoreText = "Score: " + std::to_string(_gameModule->getScore());
    _displayModule->drawText(scoreText, 10, 10, 255, 255, 255, 255);
    _displayModule->present();
}


void ArcadeCore::displaySFMLSnake() 
{
    auto grid = _gameModule->getGrid();

    int cellWidth = WINDOW_WIDTH / GRID_WIDTH;
    int cellHeight = WINDOW_HEIGHT / GRID_HEIGHT;

 
    for (std::size_t y = 0; y < GRID_HEIGHT && y < grid.size(); y++) {
        for (std::size_t x = 0; x < GRID_WIDTH && x < grid[y].size(); x++) {
            CellType cellType = grid[y][x].type;
            int r, g, b, a = 255;

            switch (cellType) {
                case CellType::EMPTY:
                    r = 0; g = 0; b = 0;
                    break;
                case CellType::SNAKE_HEAD:
                    r = 0; g = 0; b = 240;
                    break;
                case CellType::SNAKE_BODY:
                    r = 0; g = 0; b = 255;
                    break;
                case CellType::FOOD:
                    r = 255; g = 0; b = 0;
                    break;
                default:
                    r = 128; g = 128; b = 128;
                    break;      
                }
                
            _displayModule->drawRect(x * cellWidth, y * cellHeight, cellWidth, cellHeight, r, g, b, a);
        }
    }

    std::string scoreText = "Score: " + std::to_string(_gameModule->getScore());
    _displayModule->drawText(scoreText, 10, 10, 255,255, 255, 255);
    _displayModule->present();
}


void ArcadeCore::displayNcursesSnake()
{
    auto grid = _gameModule->getGrid();
    std::string libName = _displayModule->getName();

    for (int x = 0; x < GRID_WIDTH + 2; x++) {
        _displayModule->drawText("#", x, 0, 255, 255, 255, 255);
        _displayModule->drawText("#", x, GRID_HEIGHT + 1, 255, 255, 255, 255); 
    }
    for (int y = 0; y < GRID_HEIGHT + 2; y++) {
        _displayModule->drawText("#", 0, y, 255, 255, 255, 255); 
        _displayModule->drawText("#", GRID_WIDTH + 1, y, 255, 255, 255, 255); 
    }

    for (std::size_t y = 0; y < GRID_HEIGHT && y < grid.size(); y++) {
        for (std::size_t x = 0; x < GRID_WIDTH && x < grid[y].size(); x++) {
            int displayX = x + 1;
            int displayY = y + 1;
            
            switch (grid[y][x].type) {
                case CellType::SNAKE_HEAD:
                    _displayModule->drawText("O", displayX, displayY, 0, 255, 0, 255);
                    break;
                case CellType::SNAKE_BODY:
                    _displayModule->drawText("o", displayX, displayY, 0, 200, 0, 255);
                    break;
                case CellType::FOOD:
                    _displayModule->drawText("8", displayX, displayY, 255, 0, 0, 255);
                    break;
                case CellType::EMPTY:
                    _displayModule->drawText(" ", displayX, displayY, 50, 50, 50, 255);
                    break;
                default:
                    break;
            }
        }
    }

    std::string scoreText = "Score: " + std::to_string(_gameModule->getScore());
    _displayModule->drawText(scoreText, 1, GRID_HEIGHT + 2, 255, 255, 255, 255);
    
    _displayModule->present();
}


void ArcadeCore::displaySFMLNibbler() 
{
    auto grid = _gameModule->getGrid(); 

    int cellWidth = WINDOW_WIDTH / GRID_WIDTH;
    int cellHeight = WINDOW_HEIGHT / GRID_HEIGHT;

    for (std::size_t y = 0; y < GRID_HEIGHT && y < grid.size(); y++) {
        for (std::size_t x = 0; x < GRID_WIDTH && x < grid[y].size(); x++) {
            CellType cellType = grid[y][x].type;
            int r, g, b, a = 255;

            switch (cellType) {
                case CellType::EMPTY:
                    r = 0; g = 0; b = 0; 
                    break;
                case CellType::WALL:
                    r = 128; g = 128; b = 128;
                    break;
                case CellType::SNAKE_HEAD:
                    r = 0; g = 255; b = 0;
                    break;
                case CellType::SNAKE_BODY:
                    r = 0; g = 200; b = 0; 
                    break;
                case CellType::FOOD:
                    r = 255; g = 100; b = 0;
                    break;
                default:
                    r = 128; g = 128; b = 128; 
                    break;
            }
            
            _displayModule->drawRect(x * cellWidth, y * cellHeight, cellWidth, cellHeight, r, g, b, a);
        }
    }

    std::string scoreText = "Score: " + std::to_string(_gameModule->getScore());
    _displayModule->drawText(scoreText, 10, 10, 255, 255, 255, 255);


    _displayModule->present(); 
}

void ArcadeCore::displaySDL2Nibbler()
{
    displaySFMLNibbler();
} 


void ArcadeCore::displayNcursesNibbler()
{
    auto grid = _gameModule->getGrid();
    std::string libName = _displayModule->getName();

    for (int x = 0; x < GRID_WIDTH + 2; x++) {
        _displayModule->drawText("#", x, 0, 255, 255, 255, 255);
        _displayModule->drawText("#", x, GRID_HEIGHT + 1, 255, 255, 255, 255); 
    }
    for (int y = 0; y < GRID_HEIGHT + 2; y++) {
        _displayModule->drawText("#", 0, y, 255, 255, 255, 255); 
        _displayModule->drawText("#", GRID_WIDTH + 1, y, 255, 255, 255, 255); 
    }

    for (std::size_t y = 0; y < GRID_HEIGHT && y < grid.size(); y++) {
        for (std::size_t x = 0; x < GRID_WIDTH && x < grid[y].size(); x++) {
            int displayX = x + 1;
            int displayY = y + 1;
            
            switch (grid[y][x].type) {
                case CellType::SNAKE_HEAD:
                    _displayModule->drawText("O", displayX, displayY, 0, 255, 0, 255);
                    break;
                case CellType::SNAKE_BODY:
                    _displayModule->drawText("o", displayX, displayY, 0, 200, 0, 255);
                    break;
                case CellType::FOOD:
                    _displayModule->drawText("8", displayX, displayY, 255, 0, 0, 255);
                    break;
                case CellType::EMPTY:
                    _displayModule->drawText(" ", displayX, displayY, 50, 50, 50, 255);
                    break;
                default:
                    break;
            }
        }
    }

    std::string scoreText = "Score: " + std::to_string(_gameModule->getScore());
    _displayModule->drawText(scoreText, 1, GRID_HEIGHT + 2, 255, 255, 255, 255);
    
    _displayModule->present();
}

