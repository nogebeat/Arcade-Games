/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_
#include "../my.hpp"

namespace arcade {
    class IGameModule {
    public:
        virtual ~IGameModule() = default;
        virtual void init() = 0;
        virtual void processEvent(GameEvent event) = 0;
        virtual void update() = 0;
        virtual bool isGameOver() const = 0;
        virtual std::string getName() const = 0;
        virtual int getScore() const = 0;
        virtual bool isPaused() const = 0;
        virtual void reset() = 0;
        virtual std::vector<std::vector<Cell>> getGrid() const = 0;
        virtual std::vector<GameEntity> getEntities() const = 0;
        
    };
}

#endif /* !IGAMEMODULE_HPP_ */