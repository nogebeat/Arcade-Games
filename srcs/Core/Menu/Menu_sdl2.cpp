/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** Menu_sdl2
*/

#include "../../../includes/Core/ArcadeCore.hpp"
#include <SDL2/SDL.h>

using namespace arcade;

void ArcadeCore::displaySDL2Menu()
{
    int r;
    int g;
    int b;
    int r2;
    int g2;
    int b2;
    int y_pos = 165;
    int scoreY = 170;

    if (!_displayModule)
        return;
  
    _displayModule->clear();
    refreshLibraryLists();
    _displayModule->drawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 30, 30, 50, 255);
    
    _displayModule->drawText("ARCADE MENU", WINDOW_WIDTH / 2 - 100, 30, 255, 255, 0, 255);
    
    _displayModule->drawRect(WINDOW_WIDTH / 2 - 150, 70, 320, 40, 60, 60, 80, 255);
    _displayModule->drawText("Username: " + _username, WINDOW_WIDTH / 2 - 140, 85, 255, 255, 255, 255);
    
    _graphicLibPaths = removeDuplicateGraphics(_graphicLibPaths);
    _displayModule->drawRect(40, 120, 320, 40 + _graphicLibPaths.size() * 30, 60, 60, 80, 255);
    _displayModule->drawText("Available Graphics:", 50, 135, 255, 255, 255, 255);
    
    for (size_t i = 0; i < _graphicLibPaths.size(); ++i) {
        std::string filename = std::filesystem::path(_graphicLibPaths[i]).filename().string();
        std::string display_text = filename.substr(filename.find("arcade_") + 7);
        display_text = display_text.substr(0, display_text.find(".so"));
        
        if (i == _currentGraphicIndex)
            _displayModule->drawRect(45, y_pos - 5, 310, 25, 100, 100, 160, 255);
        
        r = (i == _currentGraphicIndex) ? 255 : 200;
        g = (i == _currentGraphicIndex) ? 255 : 200;
        b = (i == _currentGraphicIndex) ? 0 : 200;
        
        _displayModule->drawText(display_text, 70, y_pos, r, g, b, 255);
        y_pos += 30;
    }
    
    // Games libraries section
    y_pos = y_pos + 20;
    _displayModule->drawRect(40, y_pos - 15, 320, 40 + _gameLibPaths.size() * 30, 60, 60, 80, 255);
    _displayModule->drawText("Available Games:", 50, y_pos, 255, 255, 255, 255);
    y_pos += 30;
    
    for (size_t i = 0; i < _gameLibPaths.size(); ++i) {
        std::string filename = std::filesystem::path(_gameLibPaths[i]).filename().string();
        std::string display_text = filename.substr(filename.find("arcade_") + 7);
        display_text = display_text.substr(0, display_text.find(".so"));
        
        if (i == _currentGameIndex)
            _displayModule->drawRect(45, y_pos - 5, 310, 25, 100, 100, 160, 255);
        
        r2 = (i == _currentGameIndex) ? 255 : 200;
        g2 = (i == _currentGameIndex) ? 255 : 200;
        b2 = (i == _currentGameIndex) ? 0 : 200;
        
        _displayModule->drawText(display_text, 70, y_pos, r2, g2, b2, 255);
        y_pos += 30;
    }
    
    // Controls information
    y_pos += 20;
    _displayModule->drawRect(40, y_pos - 15, 560, 220, 60, 60, 80, 255);

    _displayModule->drawText("Controls:", 50, y_pos, 255, 255, 255, 255);
    y_pos += 25;
    _displayModule->drawText("- F6: Switch to Next graphic library", 70, y_pos, 200, 200, 200, 255);
    y_pos += 25;
    _displayModule->drawText("- F5: Switch to Previous graphic library", 70, y_pos, 200, 200, 200, 255);
    y_pos += 25;
    _displayModule->drawText("- Enter: Start selected game", 70, y_pos, 200, 200, 200, 255);
    y_pos += 25;
    _displayModule->drawText("- Left/Right: Select game", 70, y_pos, 200, 200, 200, 255);
    y_pos += 25;
    _displayModule->drawText("- Up/Down: Select graphic lib", 70, y_pos, 200, 200, 200, 255);
    y_pos += 25;
    _displayModule->drawText("- N: Edit username", 70, y_pos, 200, 200, 200, 255);
    y_pos += 25;
    _displayModule->drawText("- ESC: Exit", 70, y_pos, 200, 200, 200, 255);
    


    _displayModule->drawRect(440, 120, 320, 230, 60, 60, 80, 255);
    _displayModule->drawText("Best Scores:", 450, 135, 255, 255, 255, 255);
    
    for (size_t i = 0; i < _gameLibPaths.size() && i < 3; ++i) {
        std::string gameName = extractGameName(_gameLibPaths[i]);
        auto [playerName, highScore] = _scoreManager.getHighScore(gameName);
        
        std::string scoreText = "- " + gameName + ": " + playerName + " (" + std::to_string(highScore) + ")";
        _displayModule->drawText(scoreText, 470, scoreY, 255, 255, 255, 255);
        scoreY += 30;
    }

    _displayModule->present();

}

void ArcadeCore::handleSDL2MenuInputs()
{
     if (!_displayModule)
        return;

    _graphicLibPaths = removeDuplicateGraphics(_graphicLibPaths);
    if (isDebouncedKeyPressed("RETURN", _returnReleased)) {
        if (!_graphicLibPaths.empty()) {
            loadGraphicLibrary(_graphicLibPaths[_currentGraphicIndex]);
        }
        if (!_gameLibPaths.empty()) {
            loadGameLibrary(_gameLibPaths[_currentGameIndex]);
            _state = CoreState::GAME;
        }
    }
    if (isDebouncedKeyPressed("F6", _f6Released))
        switchNextGraphiclib();

    if (isDebouncedKeyPressed("F5", _f5Released))
        switchPreviousGraphiclib();

    if (isDebouncedKeyPressed("LEFT", _leftReleased)) {
        if (!_gameLibPaths.empty()) {
            _currentGameIndex = (_currentGameIndex + _gameLibPaths.size() - 1) % _gameLibPaths.size();
        }
    }
    if (isDebouncedKeyPressed("RIGHT", _rightReleased)) {
        if (!_gameLibPaths.empty()) {
            _currentGameIndex = (_currentGameIndex + 1) % _gameLibPaths.size();
        }
    }

    if (isDebouncedKeyPressed("UP", _upReleased)) {
        if (!_graphicLibPaths.empty()) {
            _currentGraphicIndex = (_currentGraphicIndex + _graphicLibPaths.size() - 1) % _graphicLibPaths.size();
        }
    }
    if (isDebouncedKeyPressed("DOWN", _downReleased)) {
        if (!_graphicLibPaths.empty()) {
            _currentGraphicIndex = (_currentGraphicIndex + 1) % _graphicLibPaths.size();
        }
    }

    if (isDebouncedKeyPressed("N", _nReleased)) {
        handleSDL2UserName();
        displaySDL2Menu();
        _state = CoreState::MENU;
    }
    
    if ((isDebouncedKeyPressed("ESCAPE", _escReleased)))
        _state = CoreState::EXIT;
}

void ArcadeCore::handleSDL2UserName()
{
    if (!_displayModule)
    return;

    std::string newusername = _displayModule->getTextInput("Enter your username: ", _username);

    if (!newusername.empty())
        _username = newusername;
    _state = CoreState::MENU;
}

void ArcadeCore::displaySDL2GameOver()
{
    if (!_displayModule)
        return;
    
    _displayModule->clear();
    
    _displayModule->drawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 200);

    _displayModule->drawText("GAME OVER", WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 50, 255, 0, 0, 255);
    
    std::string scoreText = "Score: " + std::to_string(_gameModule->getScore());
    _displayModule->drawText(scoreText, WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2, 255, 255, 255, 255);
    
    _displayModule->drawText("Press R to Restart", WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 + 50, 200, 200, 200, 255);
    _displayModule->drawText("Press M to Return to Menu", WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 + 80, 200, 200, 200, 255);

    _displayModule->present();
}