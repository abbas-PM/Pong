#pragma once 
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class RenderWindow
{
    public:
        RenderWindow(const char* title, int width, int height);
        SDL_Renderer* getRenderer();
        void renderText(float px, float py, const char* ptext, TTF_Font* font, SDL_Color textColor);
        void cleanUp();
        void clear();
        void display();
        
    private: 
        SDL_Window* window; 
        SDL_Renderer* renderer; 
};