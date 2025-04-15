/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** NCursesDisplay
*/


#include "../includes/Display/NCursesDisplay.hpp"
#include <unordered_map>

void arcade::NCursesDisplay::init() {
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    nodelay(stdscr, TRUE); 
    noecho();
    keypad(stdscr, TRUE);
}

void arcade::NCursesDisplay::stop() {
    clear();
    refresh();
    endwin();
}

void arcade::NCursesDisplay::clear() {
    erase();
}

void arcade::NCursesDisplay::present() {
    refresh();
}

void arcade::NCursesDisplay::render() {}

bool arcade::NCursesDisplay::isKeyPressed(const std::string &key) {
    if (key == "F5" && _ch == KEY_F(5))
        return true;
    if (key == "F6" && _ch == KEY_F(6))
        return true;
    if (key == "P" && _ch == 'p')
        return true;
    if (key == "N" && _ch == 'n')
        return true;
    if (key == "Y" && _ch == 'y')
        return true;
    if (key == "ESCAPE" && _ch == 27)
        return true;
    if (key == "ENTER" && _ch == 10)
        return true;
    if (key == "LEFT" && _ch == KEY_LEFT)
        return true;
    if (key == "RIGHT" && _ch == KEY_RIGHT)
        return true;
    if (key == "UP" && _ch == KEY_UP)
        return true;
    if (key == "DOWN" && _ch == KEY_DOWN)
        return true;
    if (key == "F6" && _ch == 246)
        return true;
    if (key.length() == 1 && _ch == key[0])
        return true;

    return false;
}

std::string arcade::NCursesDisplay::getName() const {
    return "NCurses";
}

void arcade::NCursesDisplay::handleInput()
{
    _ch = getch();
}

bool arcade::NCursesDisplay::shouldQuit() const
{
    return false;
}           

void arcade::NCursesDisplay::drawRect(int x, int y, int width, int height, int r, int g, int b, int a)
{
    (void)r;
    (void)g;
    (void)b;
    (void)a;
    for (int i = 0; i < height; ++i) {
        mvhline(y + i, x, ' ', width);
    }
}


void arcade::NCursesDisplay::drawText(const std::string& text, int x, int y, int r, int g, int b, int a)
{
    (void)r;
    (void)g;
    (void)b;
    (void)a;
    int pair = 0;

    if (g == 255)
        pair = 1;
    else if (r == 255)
        pair = 2;
    else
        pair = 3;
    
    attron(COLOR_PAIR(pair));
    mvprintw(y, x, "%s", text.c_str());
    attroff(COLOR_PAIR(pair));
   
}

void arcade::NCursesDisplay::drawCircle(int x, int y, int radius, int r, int g, int b, int a)
{
    (void)r;
    (void)g;
    (void)b;
    (void)a;
    (void)x;
    (void)y;
    (void)radius;
}

std::string arcade::NCursesDisplay::getTextInput(const std::string& prompt, const std::string& initialText)
{
    int ch;
    bool done = false;
    int startX = COLS/2 - prompt.length()/2 + prompt.length();
    int startY = LINES/2;
    std::string inputText = initialText;
    int maxLength = 20;

    nodelay(stdscr, FALSE);
    echo();
    
    
    clear();
    mvprintw(LINES/2 - 2, COLS/2 - 10, "ARCADE MENU ncurces");
    mvprintw(LINES/2, COLS/2 - prompt.length()/2, "%s", prompt.c_str());
    refresh();
    
    move(startY, startX);
    addstr(inputText.c_str());
    
    
    while (!done) {
        ch = getch();
        
        if (ch == '\n' || ch == KEY_ENTER)
            done = true;
        else if (ch == 27) {
            inputText = initialText;
            done = true;
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (!inputText.empty()) {
                inputText.pop_back();
                mvaddch(startY, startX + inputText.length(), ' ');
                move(startY, startX + inputText.length());
                refresh();
            }
        } else if (isprint(ch) && inputText.length() < maxLength)
            inputText += ch;
        move(startY, startX);
        clrtoeol();
        addstr(inputText.c_str());
        refresh();
    }
    nodelay(stdscr, TRUE);
    noecho();
    
    return inputText;
}
