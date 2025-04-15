/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** ArcadeCore
*/

#ifndef ARCADECORE_HPP_
#define ARCADECORE_HPP_
#include <string>
#include <vector>
#include <memory>
#include "DLLoader.hpp"
#include "../Interfaces/IDisplayModule.hpp"
#include "../Interfaces/IGameModule.hpp"
#include <iostream>
#include <filesystem>
#include <algorithm>
#include "ScoreManager.hpp"
#include "../Utils/Error.hpp"

namespace arcade {

    class ArcadeCore {
    public:
        ArcadeCore(const std::string &graphicLibPath);
        ~ArcadeCore();

        void run();

    private:
        enum class CoreState {
            MENU,
            GAME,
            GAME_OVER,
            EXIT
        };

        // Méthodes pour la gestion des bibliothèques
        void loadLibraries();
        void detectGraphicLibraries();
        void detectGameLibraries();
        bool loadGraphicLibrary(const std::string &path);
        bool loadGameLibrary(const std::string &path);
        void switchNextGraphiclib();
        void switchPreviousGraphiclib();
        void switchGamelib();
        bool isDebouncedKeyPressed(const std::string &key, bool &flag);
        void refreshLibraryLists();

        std::vector<std::string> removeDuplicateGraphics(const std::vector<std::string>& paths);
        std::string extractDisplayName(const std::string &path);

        // Méthodes pour le menu et le jeu
        void displayMenu();

        void displaySDL2Menu();
        void handleSDL2MenuInputs();
        void handleSDL2UserName();
        
        void displayNCursesMenu();
        void handleNCursesMenuInputs();
        void handleNCursesUserName();


        void displaySFMLMenu();
        void handleSFMLMenuInputs();
        void handleSFMLUserName();
        void displaySFMLGameOver();


        void handleMenuInputs();
        void handleGameInputs();
        void updateGame();
        void renderGame();
        void handleUserName();
        void restartGame();
        
        // Game Over handling
        void displayGameOver();
        void handleGameOverInputs();
        void displaySDL2GameOver();
        void displayNCursesGameOver();

        void displaySDL2Pacman();
        void displaySFMLPacman();
        void displayNCursesPacman();

        void displaySDL2Snake();
        void displaySFMLSnake();
        void displayNcursesSnake();
        void displaySDL2Nibbler();
        void  displaySFMLNibbler();
        void displayNcursesNibbler();

        // Score
        std::string extractGameName(const std::string &path);

        CoreState _state;
        std::string _username;
        
        DLLoaderImpl<IDisplayModule> _displayLoader;
        DLLoaderImpl<IGameModule> _gameLoader;
        
        IDisplayModule *_displayModule;
        IGameModule *_gameModule;
        
        // EventManager _eventManager;
        ScoreManager _scoreManager;
        
        std::vector<std::string> _graphicLibPaths;
        std::vector<std::string> _gameLibPaths;
        size_t _currentGraphicIndex;
        size_t _currentGameIndex;

        bool _returnReleased = false;
        bool _escReleased = false;
        bool _pReleased = false;
        bool _mReleased = false;
        bool _rReleased = false;
        bool _nReleased = false;
        bool _spaceReleased = false;
        bool _leftReleased   = false;
        bool _rightReleased  = false;
        bool _upReleased     = false;
        bool _downReleased   = false;
        bool _f5Released     = false;
        bool _f6Released     = false;
        bool _yReleased   = false;


        const std::string GRAPHIC_LIB_DIR;
        const std::string GAME_LIB_DIR;
        const std::string GRAPHIC_LIB_PREFIX;
        const std::string GAME_LIB_PREFIX;
    };
}

#endif // ARCADE_CORE_HPP_
