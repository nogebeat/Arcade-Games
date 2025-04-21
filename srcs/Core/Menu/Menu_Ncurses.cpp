/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** Menu_Ncurses
*/

#include "../../../includes/Core/ArcadeCore.hpp"

using namespace arcade;

void ArcadeCore::displayNCursesMenu() {
    
    if (!_displayModule) {
        std::cerr << "Display module not loaded!" << std::endl;
        return;
    }
    _displayModule->init();
    _displayModule->clear();
    refreshLibraryLists();


    std::string title = "====================================";
    _displayModule->drawText(title, 5, 2, 255, 255, 255, 255);
    
    std::string titleText = "           ARCADE MENU           ";
    _displayModule->drawText(titleText, 5, 3, 255, 255, 255, 255);
    _displayModule->drawText(title, 5, 4, 255, 255, 255, 255);

    std::string usernameText = "Username: " + _username;
    _displayModule->drawText(usernameText, 5, 5, 255, 255, 255, 255);

    _graphicLibPaths = removeDuplicateGraphics(_graphicLibPaths);

    _displayModule->drawText("Available Graphics Libraries:", 5, 7, 255, 255, 255, 255);
    for (size_t i = 0; i < _graphicLibPaths.size(); ++i) {
        std::string libName = (i == _currentGraphicIndex ? "> " : "  ") + _graphicLibPaths[i];
        _displayModule->drawText(libName, 5, 8 + i, 255, 255, 255, 255);
    }

    _displayModule->drawText("Available Games:", 5, 10 + _graphicLibPaths.size(), 255, 255, 255, 255);
    for (size_t i = 0; i < _gameLibPaths.size(); ++i) {
        std::string gameName = (i == _currentGameIndex ? "> " : "  ") + _gameLibPaths[i];
        _displayModule->drawText(gameName, 5, 11 + _graphicLibPaths.size() + i, 255, 255, 255, 255);
    }

    _displayModule->drawText("Controls:", 5, 13 + _graphicLibPaths.size() + _gameLibPaths.size(), 255, 255, 255, 255);
    _displayModule->drawText("- F6: Switch to Next graphic library",  5, 14 + _graphicLibPaths.size() + _gameLibPaths.size(), 255, 255, 255, 255);
    _displayModule->drawText("- F5: Switch to Previous graphic library",  5, 15 + _graphicLibPaths.size() + _gameLibPaths.size(), 255, 255, 255, 255);
    _displayModule->drawText(" - Enter: Start selected game", 5, 16 + _graphicLibPaths.size() + _gameLibPaths.size(), 255, 255, 255, 255);
    _displayModule->drawText(" - Left/Right: Select game", 5, 17 + _graphicLibPaths.size() + _gameLibPaths.size(), 255, 255, 255, 255);
    _displayModule->drawText(" - ESC: Exit", 5, 18 + _graphicLibPaths.size() + _gameLibPaths.size(), 255, 255, 255, 255);

    _displayModule->drawText("====================================", 5, 18 + _graphicLibPaths.size() + _gameLibPaths.size(), 255, 255, 255, 255);

    _displayModule->present();
}


void arcade::ArcadeCore::handleNCursesMenuInputs()
{
      if (!_displayModule)
        return;

    _graphicLibPaths = removeDuplicateGraphics(_graphicLibPaths);
    if (isDebouncedKeyPressed("ENTER", _returnReleased)) {
         if (!_graphicLibPaths.empty()) {
            _displayModule->clear();
            loadGraphicLibrary(_graphicLibPaths[_currentGraphicIndex]);
        }
        if (!_gameLibPaths.empty()) {
            loadGameLibrary(_gameLibPaths[_currentGameIndex]);
            _state = CoreState::GAME;
        }
    }
    if (isDebouncedKeyPressed("F6", _f6Released)) {
        _displayModule->clear();
        switchNextGraphiclib();
    }

    if (isDebouncedKeyPressed("F5", _f5Released)) {
        _displayModule->clear();
        switchPreviousGraphiclib();
    }
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
        handleNCursesUserName();
        displayNCursesMenu();
        _state = CoreState::MENU;
    }
    
    if ((isDebouncedKeyPressed("ESCAPE", _escReleased))) {
        _displayModule->stop();
        _state = CoreState::EXIT;
    }
}

void ArcadeCore::handleNCursesUserName()
{
    if (!_displayModule)
        return;

    std::string newuser = _displayModule->getTextInput("Enter your username: ", _username);

    if (!newuser.empty())
        _username = newuser;
    _state = CoreState::MENU;
}

void ArcadeCore::displayNCursesGameOver() {
    if (!_displayModule)
        return;

    _displayModule->clear();

    int center_y = 22 / 2;
    int center_x = 228 / 2;

    std::string gameOverText = "GAME OVER";
    _displayModule->drawText(gameOverText, center_x - gameOverText.length() / 2, center_y - 2, 255, 0, 0, 255);

    std::string scoreText = "Score: " + std::to_string(_gameModule->getScore());
    _displayModule->drawText(scoreText, center_x - scoreText.length() / 2, center_y, 255, 255, 255, 255);

    std::string restartText = "Press R to Restart";
    _displayModule->drawText(restartText, center_x - restartText.length() / 2, center_y + 2, 200, 200, 200, 255);

    std::string menuText = "Press M to Return to Menu";
    _displayModule->drawText(menuText, center_x - menuText.length() / 2, center_y + 3, 200, 200, 200, 255);

    std::string quitText = "Press Q to Quit";
    _displayModule->drawText(quitText, center_x - quitText.length() / 2, center_y + 4, 200, 200, 200, 255);

    _displayModule->present();
}