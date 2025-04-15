/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** EventManager
*/

#include "../../includes/Core/ArcadeCore.hpp"


using namespace arcade;

void ArcadeCore::handleGameInputs()
    {
        if (_displayModule && _gameModule) {
         if (isDebouncedKeyPressed("ESCAPE", _escReleased)) {
            if (_gameModule->isPaused()) {
                bool quit_game = false;
            
                while (true) {
                    _displayModule->clear();
                    _displayModule->drawText("Quit the game ? Your score and your progression will be lost", WINDOW_WIDTH / 2 - 400, WINDOW_HEIGHT / 2, 255, 0, 0, 200);
                    _displayModule->drawText("(Y/N) ?", WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 50, 255, 0, 0, 200);

                    _displayModule->present();
                    
                    if (isDebouncedKeyPressed("Y", _yReleased)) {
                        quit_game = true;
                        break;
                    }
                    else if (isDebouncedKeyPressed("N", _nReleased)) {
                        quit_game = false;
                        break;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                
                if (quit_game) {
                    _state = CoreState::MENU;
                }
        }
        else
            _state = CoreState::MENU;
        }

        if (isDebouncedKeyPressed("F6", _f6Released))
                switchNextGraphiclib();
        if (isDebouncedKeyPressed("F5", _f5Released))
                switchPreviousGraphiclib();
        if (isDebouncedKeyPressed("N", _nReleased))
                switchGamelib();
        if (isDebouncedKeyPressed("R", _rReleased))
                _gameModule->reset();
        if (isDebouncedKeyPressed("M", _mReleased))
                _state = CoreState::MENU;
        if (isDebouncedKeyPressed("P", _pReleased))
            _gameModule->processEvent(GameEvent::PAUSE);
        if (!_gameModule->isPaused())
                _gameModule->processEvent(GameEvent::ACTION);
        if (isDebouncedKeyPressed("UP", _upReleased))
                _gameModule->processEvent(GameEvent::UP);
        else if (isDebouncedKeyPressed("DOWN", _downReleased))
                _gameModule->processEvent(GameEvent::DOWN);
        else if (isDebouncedKeyPressed("LEFT", _leftReleased))
                _gameModule->processEvent(GameEvent::LEFT);
        else if (isDebouncedKeyPressed("RIGHT", _rightReleased))
                _gameModule->processEvent(GameEvent::RIGHT);
        else if (isDebouncedKeyPressed("SPACE", _spaceReleased))
                _gameModule->processEvent(GameEvent::ACTION);
        }
    }

void ArcadeCore::handleGameOverInputs()
{
    if ((_displayModule && _displayModule->getName() == "SDL2") ||
        (_displayModule && _displayModule->getName() == "SFML") ||
        (_displayModule && _displayModule->getName() == "NCurses")) {
        if (_displayModule->isKeyPressed("R")) {
            if (_gameModule) {
                _gameModule->reset();
                _state = CoreState::GAME;
            }
        } else if (_displayModule->isKeyPressed("M"))
            _state = CoreState::MENU;
         else if (_displayModule->isKeyPressed("Q") && _displayModule->getName() == "NCurses") {
                _displayModule->stop();
                _state = CoreState::EXIT;
         }
          else if (_displayModule->isKeyPressed("ESCAPE") && _displayModule->getName() == "NCurses") {
                _displayModule->stop();
                _state = CoreState::EXIT;
         }
        else if (_displayModule->isKeyPressed("ESCAPE") || _displayModule->isKeyPressed("Q"))
            _state = CoreState::EXIT;
    }
}
