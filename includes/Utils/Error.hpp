/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_
#include <string>
#include <exception>

namespace arcade {

    class Error : public std::exception {
    public:
        Error(const std::string &message);
        ~Error();

        const char *what() const noexcept override;

    private:
        std::string _message;
    };

}

#endif /* !ERROR_HPP_ */
