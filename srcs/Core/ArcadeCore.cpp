/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** ArcadeCore
*/

#include "../../includes/Core/ArcadeCore.hpp"

namespace arcade {

    ArcadeCore::ArcadeCore(const std::string &graphicLibPath) : _state(CoreState::MENU),
        _username("Player"),
        _currentGraphicIndex(0),
        _currentGameIndex(0),
        GRAPHIC_LIB_DIR("./lib/"),
        GAME_LIB_DIR("./lib/"),
        GRAPHIC_LIB_PREFIX("arcade_"),
        GAME_LIB_PREFIX("arcade_")
        
        {
            try {
                loadLibraries();
                if (!loadGraphicLibrary(graphicLibPath)) {
                throw Error("Failed to load initial graphic library: " + graphicLibPath);
            }
            _scoreManager.loadAllScores(_gameLibPaths);
        } catch (const Error &e) {

            std::cerr << "Error: " << e.what() << std::endl;
            _state = CoreState::EXIT;
        }
    }

    ArcadeCore::~ArcadeCore()
    {

    }

    void ArcadeCore::run()
    {
        while (_state != CoreState::EXIT) {
            _displayLoader.getInstance()->handleInput();
            if (_displayLoader.getInstance()->shouldQuit()) {
                _state = CoreState::EXIT;
                _displayLoader.getInstance()->stop();
            }  
            switch (_state) {
                case CoreState::MENU:
                    displayMenu();
                    handleMenuInputs();
                    break;
                case CoreState::GAME:
                if (_gameModule->isPaused()) {
                     _displayModule->clear();
                    _displayModule->drawText("PAUSED", WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2, 255, 0, 0, 200);
                    _displayModule->present();
                    handleGameInputs();
                }
                else {   
                    updateGame();
                    renderGame();
                    handleGameInputs();
                }
                break;
                case CoreState::GAME_OVER:
                    displayGameOver();
                    handleGameOverInputs();
                    break;
                case CoreState::EXIT:
                    break;
            }
        }
    }

    void ArcadeCore::loadLibraries()
    {
        detectGraphicLibraries();
        detectGameLibraries();
        
        if (_graphicLibPaths.empty()) {
            throw Error("No graphic libraries found in " + GRAPHIC_LIB_DIR);
        }
        
        if (_gameLibPaths.empty()) {
            throw Error("No game libraries found in " + GAME_LIB_DIR);
        }
    }

    void ArcadeCore::detectGraphicLibraries()
    {
        _graphicLibPaths.clear();
        
        try {
            for (const auto &entry : std::filesystem::directory_iterator(GRAPHIC_LIB_DIR)) {
                std::string path = entry.path().string();
                std::string filename = entry.path().filename().string();
                if (filename.find(GRAPHIC_LIB_PREFIX) == 0 &&
                    (filename.find("arcade_ncurses.so") != std::string::npos
                    || filename.find("arcade_sdl2.so") != std::string::npos
                    || filename.find("arcade_sfml.so") != std::string::npos)
                    && filename.find(".so") != std::string::npos)
                    _graphicLibPaths.push_back(path);
            }
        } catch (const Error &e) {
            throw Error("Failed to access directory: " + std::string(e.what()));
        }
    }

    void ArcadeCore::detectGameLibraries()
    {
        _gameLibPaths.clear();
        
        try {
            for (const auto &entry : std::filesystem::directory_iterator(GAME_LIB_DIR)) {
                std::string path = entry.path().string();
                std::string filename = entry.path().filename().string();
                if (filename.find(GAME_LIB_PREFIX) == 0 && 
                    filename.find(".so") != std::string::npos &&
                    filename.find("arcade_ncurses.so") == std::string::npos &&
                    filename.find("arcade_sdl2.so") == std::string::npos &&
                    filename.find("arcade_sfml.so") == std::string::npos)
                    _gameLibPaths.push_back(path);
            }
        } catch (const Error &e) {
            throw Error("Failed to access directory: " + std::string(e.what()));
        }
    }

    bool ArcadeCore::loadGraphicLibrary(const std::string &path)
    {
        try {
            std::cout << "Loading graphic library: " << path << std::endl;
            
            auto it = std::find(_graphicLibPaths.begin(), _graphicLibPaths.end(), path);
            if (it != _graphicLibPaths.end())
                _currentGraphicIndex = std::distance(_graphicLibPaths.begin(), it);
            else {
                _graphicLibPaths.push_back(path);
                _currentGraphicIndex = _graphicLibPaths.size() - 1;
            }
            
            if (_displayModule) {
                _displayLoader.unload();
                _displayModule = nullptr;
            }
            
            if (!_displayLoader.load(path, "createDisplay"))
                throw Error("Failed to load graphic library: " + path);
            
            _displayModule = _displayLoader.getInstance();
            if (!_displayModule)
                throw Error("Failed to create display instance from: " + path);
            
            _displayModule->init();
            return true;
        } catch (const Error &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        } 
    }

    bool ArcadeCore::loadGameLibrary(const std::string &path)
    {
        try {
            std::cout << "Loading game library: " << path << std::endl;
            
            auto it = std::find(_gameLibPaths.begin(), _gameLibPaths.end(), path);
            if (it != _gameLibPaths.end())
                _currentGameIndex = std::distance(_gameLibPaths.begin(), it);
            else {
                _gameLibPaths.push_back(path);
                _currentGameIndex = _gameLibPaths.size() - 1;
            }
            
            if (_gameModule) {
                _gameLoader.unload();
                _gameModule = nullptr;
            }
            
            if (!_gameLoader.load(path, "createGame"))
                throw Error("Failed to load game library: " + path);
            _gameModule = _gameLoader.getInstance();
            if (!_gameModule)
                throw Error("Failed to create game instance from: " + path);
            _gameModule->init();
            
            return true;
        } catch (const Error &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
    }

    void ArcadeCore::switchNextGraphiclib()
    {
        if (_graphicLibPaths.empty())
            return;
        _graphicLibPaths = removeDuplicateGraphics(_graphicLibPaths);
        _currentGraphicIndex = (_currentGraphicIndex + 1) % _graphicLibPaths.size();
        loadGraphicLibrary(_graphicLibPaths[_currentGraphicIndex]);
    }

    void ArcadeCore::switchPreviousGraphiclib()
    {
        if (_graphicLibPaths.empty())
            return;
        _graphicLibPaths = removeDuplicateGraphics(_graphicLibPaths);
        _currentGraphicIndex = (_currentGraphicIndex + _graphicLibPaths.size() - 1) % _graphicLibPaths.size();
        loadGraphicLibrary(_graphicLibPaths[_currentGraphicIndex]);
    }

    bool ArcadeCore::isDebouncedKeyPressed(const std::string &key, bool &flag)
    {
    if (!_displayModule->isKeyPressed(key)) {
        flag = true;
        return false;
    }
    else if (_displayModule->isKeyPressed(key) && flag) {
        flag = false; 
        return true;
    }
    return false;
}

    void ArcadeCore::switchGamelib()
    {
        if (_gameLibPaths.empty())
            return;
        
        _currentGameIndex = (_currentGameIndex + 1) % _gameLibPaths.size();
        loadGameLibrary(_gameLibPaths[_currentGameIndex]);
    }

    void ArcadeCore::refreshLibraryLists()
    {
        std::string currentGraphicPath = _graphicLibPaths.empty() ? "" : _graphicLibPaths[_currentGraphicIndex];
        std::string currentGamePath = _gameLibPaths.empty() ? "" : _gameLibPaths[_currentGameIndex];

        detectGraphicLibraries();
        detectGameLibraries();

        if (!currentGraphicPath.empty()) {
            auto it = std::find(_graphicLibPaths.begin(), _graphicLibPaths.end(), currentGraphicPath);
            _currentGraphicIndex = (it != _graphicLibPaths.end()) ? 
                                std::distance(_graphicLibPaths.begin(), it) : 0;
        }
        
        if (!currentGamePath.empty()) {
            auto it = std::find(_gameLibPaths.begin(), _gameLibPaths.end(), currentGamePath);
            _currentGameIndex = (it != _gameLibPaths.end()) ? 
                            std::distance(_gameLibPaths.begin(), it) : 0;
        }
    }

    void ArcadeCore::displayMenu()
    {
        if (_displayModule && _displayModule->getName() == "SDL2") {
            displaySDL2Menu();
        } else if (_displayModule && _displayModule->getName() == "NCurses") {
            displayNCursesMenu();
        } else if (_displayModule && _displayModule->getName() == "SFML")
        {
            displaySFMLMenu();
        }
    }

    void ArcadeCore::handleMenuInputs()
    {
        if (_displayModule && _displayModule->getName() == "SDL2") {
            handleSDL2MenuInputs();
        } else if (_displayModule && _displayModule->getName() == "NCurses") {
            handleNCursesMenuInputs();
        } else if (_displayModule && _displayModule->getName() == "SFML") {
            handleSFMLMenuInputs();
        }
    }


    void ArcadeCore::updateGame()
    {
        if (_gameModule) {
            _gameModule->update();
            if (_gameModule->isGameOver()) {
                if (_gameModule->getScore() > 0) {
                    std::string gameName = extractGameName(_gameLibPaths[_currentGameIndex]);
                    _scoreManager.addScore(gameName, _username, _gameModule->getScore());
                }
                _state = CoreState::GAME_OVER;
            }
        }
    }
 void ArcadeCore::renderGame()
    {
        _displayModule->clear();
        std::string gameName = extractGameName(_gameLibPaths[_currentGameIndex]);
        std::string libName = _displayModule->getName();
        
        if (gameName == "pacman") {
            if (libName == "SDL2")
                displaySDL2Pacman();
            else if (libName == "SFML")
                displaySFMLPacman();
            else if (libName == "NCurses")
                displayNCursesPacman();
        } else if (gameName == "snake") {
            if (libName == "SDL2")
                displaySDL2Snake();
            else if (libName == "SFML")
                displaySFMLSnake();
            else if (libName == "NCurses")
                displayNcursesSnake();
        } else if (gameName == "nibbler") {
            if (libName == "SFML")
                displaySFMLNibbler();
            else if (libName == "SDL2")
                displaySDL2Nibbler();
            else if (libName == "NCurses")
                displayNcursesNibbler();
        }
    }
    
    void ArcadeCore::handleUserName()
    {
        std::cout << "Enter your username: ";
        std::cin >> _username;
    }

    void ArcadeCore::restartGame()
    {
        std::cout << "Restarting game..." << std::endl;
    }


    void ArcadeCore::displayGameOver()
    {
        handleGameOverInputs();
        if (_displayModule && _displayModule->getName() == "SDL2")
            displaySDL2GameOver();
        else if (_displayModule && _displayModule->getName() == "NCurses")
            displayNCursesGameOver();
        else if (_displayModule && _displayModule->getName() == "SFML")
            displaySFMLGameOver();
    }

    std::string ArcadeCore::extractDisplayName(const std::string &path)
    {
        std::filesystem::path p(path);
        std::string filename = p.filename().string();
        size_t pos = filename.find("arcade_");
        if (pos != std::string::npos) {
            filename = filename.substr(pos + std::string("arcade_").size());
        }
        pos = filename.find(".so");
        if (pos != std::string::npos) {
            filename = filename.substr(0, pos);
        }
        return filename;
    }

    std::vector<std::string> ArcadeCore::removeDuplicateGraphics(const std::vector<std::string> &paths)
    {
        std::vector<std::string> filtered;
        std::set<std::string> seenNames;
        for (const auto &path : paths) {
            std::string name = extractDisplayName(path);
            if (seenNames.find(name) == seenNames.end()) {
                seenNames.insert(name);
                filtered.push_back(path);
            }
        }
        return filtered;
    }

    std::string ArcadeCore::extractGameName(const std::string &path)
    {
        std::filesystem::path p(path);
        std::string filename = p.filename().string();
        size_t pos = filename.find("arcade_");
        if (pos != std::string::npos) {
            filename = filename.substr(pos + std::string("arcade_").size());
        }
        pos = filename.find(".so");
        if (pos != std::string::npos) {
            filename = filename.substr(0, pos);
        }
        return filename;
    }
}

