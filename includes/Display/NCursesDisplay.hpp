/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** NCursesDisplay
*/

#ifndef NCURSESDISPLAY_HPP_
#define NCURSESDISPLAY_HPP_
#include "../includes/my.hpp"
#include "../includes/Interfaces/IDisplayModule.hpp"
#include <ncurses.h>

namespace arcade {

    class NCursesDisplay : public IDisplayModule {
        public:
            NCursesDisplay() = default;
            ~NCursesDisplay() override = default;
            void init() override;
            void stop() override;
            void render() override;
            void clear() override;
            void present() override;
            bool isKeyPressed(const std::string &key) override;
            std::string getName() const override;
            void handleInput() override;
            bool shouldQuit()  const override;
            void drawRect(int x, int y, int width, int height, int r, int g, int b, int a) override;
            void drawText(const std::string& text, int x, int y, int r, int g, int b, int a) override;
            void drawCircle(int x, int y, int radius, int r, int g, int b, int a) ;
            void handleNCursesUserName();

            std::string getTextInput(const std::string& prompt, const std::string& initialText = "") override;
            private:
            int _ch;

    };
}

#endif /* !NCURSESDISPLAY_HPP_ */
