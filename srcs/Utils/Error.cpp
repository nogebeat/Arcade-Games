/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** Error
*/

#include "../../includes/Utils/Error.hpp"
namespace arcade {
    Error::Error(const std::string &message) : _message(message)
    {

    }

    Error::~Error() = default;

    const char * Error::what() const noexcept
    {
        return _message.c_str();
    }

}