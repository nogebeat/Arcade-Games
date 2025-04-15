/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** SDL2Display
*/

#include "../includes/Display/SDL2Display.hpp"
#include <iostream>

namespace arcade {  

    SDL2Display::SDL2Display() : _window(nullptr), _renderer(nullptr), _font(nullptr)
    {
        // Map common keys to SDL key codes
        _keyMap["UP"] = SDLK_UP;
        _keyMap["DOWN"] = SDLK_DOWN;
        _keyMap["LEFT"] = SDLK_LEFT;
        _keyMap["RIGHT"] = SDLK_RIGHT;
        _keyMap["ESCAPE"] = SDLK_ESCAPE;
        _keyMap["RETURN"] = SDLK_RETURN;
        _keyMap["SPACE"] = SDLK_SPACE;
        _keyMap["R"] = SDLK_r;
        _keyMap["N"] = SDLK_n;
        _keyMap["Q"] = SDLK_q;
        _keyMap["E"] = SDLK_e;
        _keyMap["M"] = SDLK_m;
        _keyMap["F5"] = SDLK_F5;
        _keyMap["F6"] = SDLK_F6;
        _keyMap["P"] = SDLK_p;
        _keyMap["Y"] = SDLK_y;

    }

    SDL2Display::~SDL2Display()
    {
        stop();
    }

    void SDL2Display::init()
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }
        
        if (TTF_Init() < 0) {
            std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
            SDL_Quit();
            return;
        }
        
        _window = SDL_CreateWindow("Arcade SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                  WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (!_window) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            TTF_Quit();
            SDL_Quit();
            return;
        }
        
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        if (!_renderer) {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(_window);
            TTF_Quit();
            SDL_Quit();
            return;
        }
        
        _font = TTF_OpenFont("/tmp/arcade/assets/fonts/duckhunt.ttf", 24);
        if (!_font)
            std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        
        std::cout << "SDL2 initialized successfully" << std::endl;
    }

    void SDL2Display::stop()
    {
        if (_font) {
            TTF_CloseFont(_font);
            _font = nullptr;
        }
        
        if (_renderer) {
            SDL_DestroyRenderer(_renderer);
            _renderer = nullptr;
        }
        
        if (_window) {
            SDL_DestroyWindow(_window);
            _window = nullptr;
        }
        
        TTF_Quit();
        SDL_Quit();
    }

    void SDL2Display::clear()
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);
    }

    void SDL2Display::render()
    {
        clear();
        present();
    }
    
    void SDL2Display::drawText(const std::string &text, int x, int y, SDL_Color color)
    {
        if (!_font) {
            std::cerr << "Font not loaded, cannot render text" << std::endl;
            return;
        }
        
        SDL_Surface *surface = TTF_RenderText_Solid(_font, text.c_str(), color);
        if (!surface) {
            std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
            return;
        }
        
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
        if (!texture) {
            std::cerr << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(surface);
            return;
        }
        
        SDL_Rect renderRect = {x, y, surface->w, surface->h};
        
        SDL_RenderCopy(_renderer, texture, NULL, &renderRect);
        
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
    
    void SDL2Display::drawRect(int x, int y, int width, int height, SDL_Color color)
    {
        SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
        SDL_Rect rect = {x, y, width, height};
        SDL_RenderFillRect(_renderer, &rect);
    }
    
    void SDL2Display::drawCircle(int x, int y, int radius, SDL_Color color)
    {
        SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
        
        for (int dy = -radius; dy <= radius; dy++) {
            for (int dx = -radius; dx <= radius; dx++) {
                if (dx*dx + dy*dy <= radius*radius) {
                    SDL_RenderDrawPoint(_renderer, x + dx, y + dy);
                }
            }
        }
    }
    
    void SDL2Display::present()
    {
        SDL_RenderPresent(_renderer);
    }
    
    void SDL2Display::handleInput()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                _quit = true;
            }
        }
    }


    bool SDL2Display::shouldQuit() const {
        return _quit;
    }

    
    bool SDL2Display::isKeyPressed(const std::string &key)
    {
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (_keyMap.find(key) != _keyMap.end()) {
            SDL_Scancode scancode = SDL_GetScancodeFromKey(_keyMap[key]);
            return state[scancode];
        }
        return false;
    }

    // Implémentation générique

    void SDL2Display::drawRect(int x, int y, int width, int height, int r, int g, int b, int a)
    {
        SDL_Color color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a)};
        drawRect(x, y, width, height, color);
    }

    void SDL2Display::drawText(const std::string &text, int x, int y, int r, int g, int b, int a)
    {
        SDL_Color color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a)};
        drawText(text, x, y, color);
    }

    void SDL2Display::drawCircle(int x, int y, int radius, int r, int g, int b, int a)
    {
        SDL_Color color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a)};
        drawCircle(x, y, radius, color);
    }

    std::string SDL2Display::getName() const
    {
        return "SDL2";
    }

    std::string SDL2Display::getTextInput(const std::string& prompt, const std::string& initialText)
    {
        SDL_StartTextInput();
        std::string inputText = initialText;
        bool inputActive = true;
        bool escapePressed = false;

        while (inputActive) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    inputActive = false;
                    _quit = true;
                } else if (event.type == SDL_TEXTINPUT) {
                    inputText += event.text.text;
                } else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
                        inputText.pop_back();
                    } else if (event.key.keysym.sym == SDLK_RETURN) {
                        inputActive = false;
                    } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                        inputActive = false;
                        escapePressed = true;
                    }
                }
            }
            clear();
            drawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 30, 30, 50, 255);
            drawText("ARCADE MENU", WINDOW_WIDTH / 2 - 100, 30, 255, 255, 0, 255);
        
            drawRect(WINDOW_WIDTH / 2 - 190, 70, 400, 40, 60, 60, 80, 255);
            drawText(prompt + inputText, WINDOW_WIDTH / 2 - 180, 85, 255, 255, 255, 255);
            present();
            
            SDL_Delay(16);
            
            if (isKeyPressed("F6") || isKeyPressed("F5")) {
                inputActive = false;
                escapePressed = true;
            }
        }
        
        SDL_StopTextInput();
        
        if (!escapePressed) {
            bool keyReleased = false;
            while (!keyReleased) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) {
                        keyReleased = true;
                    }
                }
                SDL_Delay(10);
            }
        }
        
        return escapePressed ? initialText : inputText;
    }
}
